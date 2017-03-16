/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#ifndef JUCER_PROJECTSAVER_H_INCLUDED
#define JUCER_PROJECTSAVER_H_INCLUDED

#include "jucer_ResourceFile.h"

//==============================================================================
class ProjectSaver
{
public:
    ProjectSaver (Project& p, const File& file)
        : project (p),
          projectFile (file),
          generatedCodeFolder (project.getGeneratedCodeFolder()),
          generatedFilesGroup (Project::Item::createGroup (project, getJuceCodeGroupName(), "__generatedcode__")),
          hasBinaryData (false)
    {
        generatedFilesGroup.setID (getGeneratedGroupID());
    }

    struct SaveThread  : public ThreadWithProgressWindow
    {
    public:
        SaveThread (ProjectSaver& ps)
            : ThreadWithProgressWindow ("Saving...", true, false),
              saver (ps), result (Result::ok())
        {}

        void run() override
        {
            setProgress (-1);
            result = saver.save (false);
        }

        ProjectSaver& saver;
        Result result;

        JUCE_DECLARE_NON_COPYABLE (SaveThread)
    };

    Result save (bool showProgressBox)
    {
        if (showProgressBox)
        {
            SaveThread thread (*this);
            thread.runThread();
            return thread.result;
        }

        const String appConfigUserContent (loadUserContentFromAppConfig());

        const File oldFile (project.getFile());
        project.setFile (projectFile);

        writeMainProjectFile();

        if (errors.size() == 0) writeBinaryDataFiles();

        if (errors.size() == 0 && generatedCodeFolder.exists())
            writeReadmeFile();

        if (generatedCodeFolder.exists())
            deleteUnwantedFilesIn (generatedCodeFolder);

        if (errors.size() > 0)
        {
            project.setFile (oldFile);
            return Result::fail (errors[0]);
        }

        project.updateModificationTime();

        return Result::ok();
    }

    Result saveResourcesOnly()
    {
        writeBinaryDataFiles();

        if (errors.size() > 0)
            return Result::fail (errors[0]);

        return Result::ok();
    }

    Project::Item saveGeneratedFile (const String& filePath, const MemoryOutputStream& newData)
    {
        if (! generatedCodeFolder.createDirectory())
        {
            addError ("Couldn't create folder: " + generatedCodeFolder.getFullPathName());
            return Project::Item (project, ValueTree());
        }

        const File file (generatedCodeFolder.getChildFile (filePath));

        if (replaceFileIfDifferent (file, newData))
            return addFileToGeneratedGroup (file);

        return Project::Item (project, ValueTree());
    }

    Project::Item addFileToGeneratedGroup (const File& file)
    {
        Project::Item item (generatedFilesGroup.findItemForFile (file));

        if (item.isValid())
            return item;

        generatedFilesGroup.addFileAtIndex (file, -1, true);
        return generatedFilesGroup.findItemForFile (file);
    }

    void setExtraAppConfigFileContent (const String& content)
    {
        extraAppConfigContent = content;
    }

    static void writeAutoGenWarningComment (OutputStream& out)
    {
        out << "/*" << newLine << newLine
            << "    IMPORTANT! This file is auto-generated each time you save your" << newLine
            << "    project - if you alter its contents, your changes may be overwritten!" << newLine
            << newLine;
    }

    static const char* getGeneratedGroupID() noexcept               { return "__jucelibfiles"; }
    Project::Item& getGeneratedCodeGroup()                          { return generatedFilesGroup; }

    static String getJuceCodeGroupName()                            { return "Juce Library Code"; }

    File getGeneratedCodeFolder() const                             { return generatedCodeFolder; }

    bool replaceFileIfDifferent (const File& f, const MemoryOutputStream& newData)
    {
        filesCreated.add (f);

        if (! FileHelpers::overwriteFileWithNewDataIfDifferent (f, newData))
        {
            addError ("Can't write to file: " + f.getFullPathName());
            return false;
        }

        return true;
    }

    static bool shouldFolderBeIgnoredWhenCopying (const File& f)
    {
        return f.getFileName() == ".git" || f.getFileName() == ".svn" || f.getFileName() == ".cvs";
    }

    bool copyFolder (const File& source, const File& dest)
    {
        if (source.isDirectory() && dest.createDirectory())
        {
            Array<File> subFiles;
            source.findChildFiles (subFiles, File::findFiles, false);

            for (int i = 0; i < subFiles.size(); ++i)
            {
                const File f (subFiles.getReference(i));
                const File target (dest.getChildFile (f.getFileName()));
                filesCreated.add (target);

                if (! f.copyFileTo (target))
                    return false;
            }

            Array<File> subFolders;
            source.findChildFiles (subFolders, File::findDirectories, false);

            for (int i = 0; i < subFolders.size(); ++i)
            {
                const File f (subFolders.getReference(i));

                if (! shouldFolderBeIgnoredWhenCopying (f))
                    if (! copyFolder (f, dest.getChildFile (f.getFileName())))
                        return false;
            }

            return true;
        }

        return false;
    }

    Project& project;
    SortedSet<File> filesCreated;

private:
    const File projectFile, generatedCodeFolder;
    Project::Item generatedFilesGroup;
    String extraAppConfigContent;
    StringArray errors;
    CriticalSection errorLock;

    File appConfigFile;
    bool hasBinaryData;

    // Recursively clears out any files in a folder that we didn't create, but avoids
    // any folders containing hidden files that might be used by version-control systems.
    bool deleteUnwantedFilesIn (const File& parent)
    {
        bool folderIsNowEmpty = true;
        DirectoryIterator i (parent, false, "*", File::findFilesAndDirectories);
        Array<File> filesToDelete;

        bool isFolder;
        while (i.next (&isFolder, nullptr, nullptr, nullptr, nullptr, nullptr))
        {
            const File f (i.getFile());

            if (filesCreated.contains (f) || shouldFileBeKept (f.getFileName()))
            {
                folderIsNowEmpty = false;
            }
            else if (isFolder)
            {
                if (deleteUnwantedFilesIn (f))
                    filesToDelete.add (f);
                else
                    folderIsNowEmpty = false;
            }
            else
            {
                filesToDelete.add (f);
            }
        }

        for (int j = filesToDelete.size(); --j >= 0;)
            filesToDelete.getReference(j).deleteRecursively();

        return folderIsNowEmpty;
    }

    static bool shouldFileBeKept (const String& filename)
    {
        static const char* filesToKeep[] = { ".svn", ".cvs", "CMakeLists.txt" };

        for (int i = 0; i < numElementsInArray (filesToKeep); ++i)
            if (filename == filesToKeep[i])
                return true;

        return false;
    }

    void writeMainProjectFile()
    {
        ScopedPointer<XmlElement> xml (project.getProjectRoot().createXml());
        jassert (xml != nullptr);

        if (xml != nullptr)
        {
            MemoryOutputStream mo;
            xml->writeToStream (mo, String());
            replaceFileIfDifferent (projectFile, mo);
        }
    }

    File getAppConfigFile() const   { return generatedCodeFolder.getChildFile (project.getAppConfigFilename()); }

    String loadUserContentFromAppConfig() const
    {
        StringArray lines, userContent;
        lines.addLines (getAppConfigFile().loadFileAsString());
        bool foundCodeSection = false;

        for (int i = 0; i < lines.size(); ++i)
        {
            if (lines[i].contains ("[BEGIN_USER_CODE_SECTION]"))
            {
                for (int j = i + 1; j < lines.size() && ! lines[j].contains ("[END_USER_CODE_SECTION]"); ++j)
                    userContent.add (lines[j]);

                foundCodeSection = true;
                break;
            }
        }

        if (! foundCodeSection)
        {
            userContent.add (String());
            userContent.add ("// (You can add your own code in this section, and the Editoar will not overwrite it)");
            userContent.add (String());
        }

        return userContent.joinIntoString (newLine) + newLine;
    }

    void writeBinaryDataFiles()
    {
        const File binaryDataH (project.getBinaryDataHeaderFile());

        ResourceFile resourceFile (project);

        if (resourceFile.getNumFiles() > 0)
        {
            auto dataNamespace = project.binaryDataNamespace().toString().trim();
            if (dataNamespace.isEmpty())
                dataNamespace = "BinaryData";

            resourceFile.setClassName (dataNamespace);

            Array<File> binaryDataFiles;

            int maxSize = project.getMaxBinaryFileSize().getValue();
            if (maxSize <= 0)
                maxSize = 10 * 1024 * 1024;

            Result r (resourceFile.write (binaryDataFiles, maxSize));

            if (r.wasOk())
            {
                hasBinaryData = true;

                for (int i = 0; i < binaryDataFiles.size(); ++i)
                {
                    const File& f = binaryDataFiles.getReference(i);

                    filesCreated.add (f);
                    generatedFilesGroup.addFileRetainingSortOrder (f, ! f.hasFileExtension (".h"));
                }
            }
            else
            {
                addError (r.getErrorMessage());
            }
        }
        else
        {
            for (int i = 20; --i >= 0;)
                project.getBinaryDataCppFile (i).deleteFile();

            binaryDataH.deleteFile();
        }
    }

    void writeReadmeFile()
    {
        MemoryOutputStream out;
        out << newLine
            << " Important Note!!" << newLine
            << " ================" << newLine
            << newLine
            << "The purpose of this folder is to contain files that are auto-generated by the Editoar," << newLine
            << "and ALL files in this folder will be mercilessly DELETED and completely re-written whenever" << newLine
            << "the Editoar saves your project." << newLine
            << newLine
            << "Therefore, it's a bad idea to make any manual changes to the files in here, or to" << newLine
            << "put any of your own files in here if you don't want to lose them. (Of course you may choose" << newLine
            << "to add the folder's contents to your version-control system so that you can re-merge your own" << newLine
            << "modifications after the Editoar has saved its changes)." << newLine;

        replaceFileIfDifferent (generatedCodeFolder.getChildFile ("ReadMe.txt"), out);
    }

    void addError (const String& message)
    {
        const ScopedLock sl (errorLock);
        errors.add (message);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProjectSaver)
};


#endif   // JUCER_PROJECTSAVER_H_INCLUDED

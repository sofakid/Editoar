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

#ifndef JUCER_PROJECTTYPE_H_INCLUDED
#define JUCER_PROJECTTYPE_H_INCLUDED

class Project;
class ProjectExporter;

//==============================================================================
class ProjectType
{
public:
    //==============================================================================
    virtual ~ProjectType();

    const String& getType() const noexcept          { return type; }
    const String& getDescription() const noexcept   { return desc; }

    //==============================================================================
    static Array<ProjectType*> getAllTypes();
    static const ProjectType* findType (const String& typeCode);

    //==============================================================================
    virtual bool isGUIApplication() const       { return false; }

protected:
    ProjectType (const String& type, const String& desc);

private:
    const String type, desc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProjectType)
};

//==============================================================================
inline ProjectType::ProjectType (const String& t, const String& d)
  : type (t), desc (d)
{
}

inline ProjectType::~ProjectType()
{
    getAllTypes().removeFirstMatchingValue (this);
}

inline const ProjectType* ProjectType::findType (const String& typeCode)
{
    const Array<ProjectType*>& types = getAllTypes();

    for (int i = types.size(); --i >= 0;)
        if (types.getUnchecked(i)->getType() == typeCode)
            return types.getUnchecked(i);

    jassertfalse;
    return nullptr;
}

//==============================================================================
struct ProjectType_GUIApp  : public ProjectType
{
    ProjectType_GUIApp()  : ProjectType (getTypeName(), "GUI Application") {}

    static const char* getTypeName() noexcept   { return "guiapp"; }
    bool isGUIApplication() const  override     { return true; }
};

//==============================================================================
inline Array<ProjectType*> ProjectType::getAllTypes()
{
    static ProjectType_GUIApp guiApp;
    static ProjectType* allTypes[] = { &guiApp, nullptr };

    return  Array<ProjectType*> (allTypes);
}

#endif   // JUCER_PROJECTTYPE_H_INCLUDED

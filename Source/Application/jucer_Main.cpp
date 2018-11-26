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

#include "../jucer_Headers.h"

#include "jucer_Application.h"
#include "jucer_OpenDocumentManager.h"
#include "../Code Editor/jucer_SourceCodeEditor.h"
#include "../Utility/jucer_FilePathPropertyComponent.h"
#include "../Project/jucer_TreeItemTypes.h"
#include "../Utility/jucer_FloatingToolWindow.h"
#include "../Utility/jucer_DialogLookAndFeel.h"

#include "jucer_EulaDialogue.h"
#include "jucer_CommandLine.h"

#include "../Project/jucer_ProjectContentComponent.cpp"
#include "jucer_Application.cpp"

START_JUCE_APPLICATION (EditoarApplication)

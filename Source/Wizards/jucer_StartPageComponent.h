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

class StartPageComponent    : public Component
{
public:
    StartPageComponent()
    {
        wiz.reset(new WizardComp());
        addAndMakeVisible (wiz.get());

        setSize (900, 650);
    }

    void paint (Graphics& g) override
    {
        EditoarLookAndFeel::fillWithBackgroundTexture (*this, g);
    }

    void resized() override
    {
        wiz->setBounds (getLocalBounds());
    }

private:
    std::unique_ptr<WizardComp> wiz;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StartPageComponent)
};

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "SkoarASTComponent.h"
#include "SkoarProjectionComponent.h"

class DebuggoarToolbar: 
    public Component,
    public Button::Listener,
    public ComboBox::Listener
{
public:
    //==============================================================================
    DebuggoarToolbar ();
    ~DebuggoarToolbar();

    //==============================================================================
    class AwesomeButtonsLNF : public LookAndFeel_V3
    {
        Font getTextButtonFont (TextButton&, int buttonHeight) override
        {
            auto fontawesome = Typeface::createSystemTypefaceFor (BinaryData::fontawesomewebfont_ttf, BinaryData::fontawesomewebfont_ttfSize);
            auto size = jmin (15.0f, buttonHeight * 0.6f);
            auto font = Font (fontawesome);
            font.setHeight (size);
            return font;
        }
    };

    AwesomeButtonsLNF awesome;
    void updateTabs ();
    String getVoice ();
    SkoarpionPtr getSkoarpion ();
    void loadSkoar (Skoar*);
    static DebuggoarToolbar* getInstance ();
    void selectSkoarpion (SkoarpionPtr skoarpion, String voice);

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

private:
    Array<SkoarpionPtr> skoarpions;
    Array<String> voices;

    //==============================================================================
    ScopedPointer<TextButton> stepInButton;
    ScopedPointer<TextButton> stepOverButton;
    ScopedPointer<TextButton> stepOutButton;
    ScopedPointer<TextButton> stopDebuggingButton;
    ScopedPointer<Label> minstrelLabel;
    ScopedPointer<ComboBox> minstrelComboBox;
    ScopedPointer<TextButton> openExtDebuggerButton;
    ScopedPointer<TextButton> continueDebuggingButton;
    ScopedPointer<Label> skoarpionLabel;
    ScopedPointer<ComboBox> skoarpionComboBox;
    ScopedPointer<TextButton> stepToBeatButton;
    ScopedPointer<TextButton> playWithoutDebuggingButton;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DebuggoarToolbar)
};

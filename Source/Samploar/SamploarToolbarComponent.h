#pragma once
#include "../../JuceLibraryCode/JuceHeader.h"
class SamploarComponent;

class SamploarToolbarComponent  : public Component,
    public Button::Listener,
    public Label::Listener
{
public:
    //==============================================================================
    SamploarToolbarComponent ();
    ~SamploarToolbarComponent();

    //==============================================================================
    void setPlayButtonEnabled(bool);
    void setStopButtonEnabled(bool);

    void setPlayButtonAsPause();
    void setPlayButtonAsPlay();

    void setStopButtonAsReset();
    void setStopButtonAsStop();

    void setFileName(String fileName);
    void setFileLength(double seconds);
    void setInstrumentId(String id);

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void labelTextChanged (Label* labelThatHasChanged) override;

private:
    String makeValidId(String s);

    class AwesomeButtonsLNF : public LookAndFeel_V3
    {
        Font getTextButtonFont(TextButton&, int buttonHeight) override
        {
            auto fontawesome = Typeface::createSystemTypefaceFor(BinaryData::fontawesomewebfont_ttf, BinaryData::fontawesomewebfont_ttfSize);
            auto size = jmin(15.0f, buttonHeight * 0.6f);
            auto font = Font(fontawesome);
            font.setHeight(size);
            return font;
        }
    };

    AwesomeButtonsLNF awesome;
    SamploarComponent* samploar;

    //==============================================================================
    ScopedPointer<TextButton> playButton;
    ScopedPointer<TextButton> stopButton;
    ScopedPointer<Label> fileNameLabel;
    ScopedPointer<Label> fileNameValueLabel;
    ScopedPointer<Label> instrumentIdLabel;
    ScopedPointer<Label> instrumentIdValueLabel;
    ScopedPointer<Label> lengthLabel;
    ScopedPointer<Label> lengthValueLabel;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamploarToolbarComponent)
};

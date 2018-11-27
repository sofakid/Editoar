#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TestoarResultsToolBar  : public Component,
                               public Button::Listener
{
public:
    //==============================================================================
    TestoarResultsToolBar ();
    ~TestoarResultsToolBar();

    //==============================================================================
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

    void testRunning();
    void testsPassed();
    void testsFailed();

    void setTitle(String&);
    void setCounts(String &counts);

    void redrawTitle();

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;

private:
    AwesomeButtonsLNF awesome;
    Colour backgroundColour;
    String titleText;
    String countsText;

    std::unique_ptr<Label> textLabel;
    std::unique_ptr<TextButton> debugButton;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestoarResultsToolBar)
};

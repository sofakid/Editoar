#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class SamploarComponent : public AudioAppComponent,
                          public ChangeListener,
                          public Button::Listener
{
public:
    SamploarComponent(File file);
    ~SamploarComponent();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void resized() override;
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void buttonClicked(Button* button) override;

private:


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

    AwesomeButtonsLNF lnf;

    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping
    };

    void changeState(TransportState newState);

    void playButtonClicked();
    void stopButtonClicked();

    //==========================================================================
    TextButton playButton;
    TextButton stopButton;

    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TransportState state;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamploarComponent)
};

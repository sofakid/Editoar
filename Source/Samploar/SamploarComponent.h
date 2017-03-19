#pragma once

#include "../jucer_Headers.h"
#include "SoundFileDocument.h"
#include "SamploarToolbarComponent.h"

class SamploarComponent : public AudioAppComponent,
                          public ChangeListener,
                          private Timer
{
public:
    SamploarComponent(SoundFileDocument* doc);
    ~SamploarComponent();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void resized() override;
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void paint(Graphics& g) override;

    void playButtonClicked();
    void stopButtonClicked();

    void timerCallback() override;

    SoundFileDocument* getDocument();

private:
    void paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);
    void paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds);

    void transportSourceChanged();
    void thumbnailChanged();

    enum TransportState
    {
        Stopped,
        Starting,
        Playing,
        Stopping
    };

    void changeState(TransportState newState);



    //==========================================================================
    SoundFileDocument *document;

    SamploarToolbarComponent toolbar;

    AudioFormatManager formatManager;
    ScopedPointer<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TransportState state;
    AudioThumbnailCache thumbnailCache;
    AudioThumbnail thumbnail;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SamploarComponent)
};

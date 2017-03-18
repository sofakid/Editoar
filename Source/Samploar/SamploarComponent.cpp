#include "../../JuceLibraryCode/JuceHeader.h"
#include "SamploarComponent.h"

SamploarComponent::SamploarComponent(File file)
    :   state (Stopped)
{

    //addAndMakeVisible (&openButton);
    //openButton.setButtonText ("Open...");
    //openButton.addListener (this);
        

    addAndMakeVisible (&playButton);
    playButton.setLookAndFeel(&lnf);
    playButton.setButtonText (CharPointer_UTF16(L"\xf04b"));
    playButton.addListener (this);
    playButton.setColour (TextButton::buttonColourId, Colours::green);
    playButton.setEnabled (false);

    addAndMakeVisible (&stopButton);
    stopButton.setLookAndFeel(&lnf);
    stopButton.setButtonText (CharPointer_UTF16(L"\xf04d"));
    stopButton.addListener (this);
    stopButton.setColour (TextButton::buttonColourId, Colours::red);
    stopButton.setEnabled (false);
        
    setSize (300, 200);
        
    formatManager.registerBasicFormats();       // [1]
    transportSource.addChangeListener (this);   // [2]

    setAudioChannels (0, 2);

    AudioFormatReader* reader = formatManager.createReaderFor(file); // [10]

    if (reader != nullptr)
    {
        ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource(reader, true); // [11]
        transportSource.setSource(newSource, 0, nullptr, reader->sampleRate);                         // [12]
        playButton.setEnabled(true);                                                                  // [13]
        readerSource = newSource.release();                                                           // [14]
    }
}
    
SamploarComponent::~SamploarComponent()
{
    shutdownAudio();
}

void SamploarComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void SamploarComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    if (readerSource == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }
        
    transportSource.getNextAudioBlock (bufferToFill);
}

void SamploarComponent::releaseResources()
{
    transportSource.releaseResources();
}

void SamploarComponent::resized()
{
    playButton.setBounds (10, 10, getWidth() - 20, 40);
    stopButton.setBounds (10, 60, getWidth() - 20, 40);
}
    
void SamploarComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState (Playing);
        else
            changeState (Stopped);
    }
}

void SamploarComponent::buttonClicked (Button* button)
{
    if (button == &playButton)  playButtonClicked();
    if (button == &stopButton)  stopButtonClicked();
}

    
void SamploarComponent::changeState (TransportState newState)
{
    if (state != newState)
    {
        state = newState;
            
        switch (state)
        {
            case Stopped:                           // [3]
                stopButton.setEnabled (false);
                playButton.setEnabled (true);
                transportSource.setPosition (0.0);
                break;
                    
            case Starting:                          // [4]
                playButton.setEnabled (false);
                transportSource.start();
                break;
                    
            case Playing:                           // [5]
                stopButton.setEnabled (true);
                break;
                    
            case Stopping:                          // [6]
                transportSource.stop();
                break;
        }
    }
}
    
void SamploarComponent::playButtonClicked()
{
    changeState (Starting);
}
    
void SamploarComponent::stopButtonClicked()
{
    changeState (Stopping);
}
    
//Component* createSamploarContentComponent()     { return new SamploarComponent(); }



#include "../../JuceLibraryCode/JuceHeader.h"
#include "SamploarComponent.h"

SamploarComponent::SamploarComponent(SoundFileDocument* doc) :
    document(doc),
    state (Stopped),
    thumbnailCache(5),                            // [4]
    thumbnail(512, formatManager, thumbnailCache) // [5]
{
    auto file = document->getFile();
    addAndMakeVisible (&toolbar);
   
    setSize (300, 200);
        
    formatManager.registerBasicFormats();
    transportSource.addChangeListener (this);
    thumbnail.addChangeListener(this);

    setAudioChannels (0, 2);

    AudioFormatReader* reader = formatManager.createReaderFor(file);

    if (reader != nullptr)
    {
        ScopedPointer<AudioFormatReaderSource> newSource = new AudioFormatReaderSource(reader, true);
        transportSource.setSource(newSource, 0, nullptr, reader->sampleRate);
        thumbnail.setSource(new FileInputSource(file));
        toolbar.setPlayButtonEnabled(true);
        
        toolbar.setFileName(file.getFullPathName());

        auto seconds = ((double) reader->lengthInSamples) / reader->sampleRate;
        toolbar.setFileLength(seconds);

        toolbar.setInstrumentId(document->getInstrument()->getId());

        readerSource = newSource.release();
    }

    startTimer(5);
}

    
SamploarComponent::~SamploarComponent()
{
    document = nullptr;
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

// -- changeListener stuff -----------------------------------------------------
void SamploarComponent::changeListenerCallback (ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState (Playing);
        else
            changeState (Stopped);
    }

    if (source == &transportSource)  transportSourceChanged();
    if (source == &thumbnail)        thumbnailChanged();
}

void SamploarComponent::transportSourceChanged()
{
    if (transportSource.isPlaying())
        changeState(Playing);
    else
        changeState(Stopped);
}

void SamploarComponent::thumbnailChanged()
{
    repaint();
}

// --- buttons --------------------------------------------------------
//
// these aren't button click listeners, these are explicitly called 
// by the listeners in the toolbar.

void SamploarComponent::playButtonClicked() {
    changeState(Starting);
}
void SamploarComponent::stopButtonClicked() {
    changeState(Stopping);
}


// --- state ----------------------------------------------------------
    
void SamploarComponent::changeState (TransportState newState)
{
    if (state != newState)
    {
        state = newState;
            
        switch (state)
        {
            case Stopped:
                toolbar.setPlayButtonEnabled (true);
                toolbar.setStopButtonEnabled (false);
                transportSource.setPosition (0.0);
                break;
                    
            case Starting:
                toolbar.setPlayButtonEnabled (false);
                transportSource.start();
                break;
                    
            case Playing:
                toolbar.setStopButtonEnabled (true);
                break;
                    
            case Stopping:
                transportSource.stop();
                break;
        }
    }
}
    
// -- painting ---------------------------------------------------------------------
void SamploarComponent::timerCallback()
{
    repaint();
}


void SamploarComponent::resized()
{
    toolbar.setBounds(0, 0, getWidth(), 128);
}


void SamploarComponent::paint(Graphics& g)
{
    const Rectangle<int> thumbnailBounds(10, 128, getWidth() - 20, getHeight() - 140);

    if (thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g, thumbnailBounds);
    else
        paintIfFileLoaded(g, thumbnailBounds);
}

void SamploarComponent::paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
    g.setColour(Colours::darkgrey);
    g.fillRect(thumbnailBounds);
    g.setColour(Colours::black);
    g.drawFittedText("No File Loaded", thumbnailBounds, Justification::centred, 1.0f);
}

void SamploarComponent::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds)
{
    g.setColour(Colours::black);
    g.fillRect(thumbnailBounds);

    g.setColour(Colours::mediumpurple);                                     // [8]

    const double audioLength(thumbnail.getTotalLength());

    thumbnail.drawChannels(g,                                      // [9]
        thumbnailBounds,
        0.0,                                    // start time
        thumbnail.getTotalLength(),             // end time
        1.0f);                                  // vertical zoom

    g.setColour(Colours::blue);

    const double audioPosition(transportSource.getCurrentPosition());
    const float drawPosition((audioPosition / audioLength) 
        * thumbnailBounds.getWidth()
        + thumbnailBounds.getX());                                        // [13]
    
    g.drawLine(drawPosition, 
        thumbnailBounds.getY(), 
        drawPosition,
        thumbnailBounds.getBottom(), 
        2.0f);                                             // [14]
}

SoundFileDocument* SamploarComponent::getDocument() {
    return document;
}
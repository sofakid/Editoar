
#include "DebuggoarSession.h"
#include "../Playoar/PlayoarSession.h"

#include "DebuggoarToolbar.h"
#include "DebuggoarComponent.h"

static DebuggoarToolbar* instance (nullptr);

DebuggoarToolbar* DebuggoarToolbar::getInstance() {
    return instance;
}

void DebuggoarToolbar::selectSkoarpion (SkoarpionPtr skoarpion, String voice)
{
    int i (0);
    bool found (false);
    for (auto& v : voices)
    {
        ++i;
        if (v == voice)
        {
            found = true;
            break;
        }
    }

    if (!found)
        i = 0;

    auto selected (minstrelComboBox->getSelectedId ());
    if (selected <= 0)
    {
        minstrelComboBox->setSelectedId (i, sendNotification);
        selected = i;
    }

    if (selected == i)
    {
        i = 0;
        found = false;
        for (auto& s : skoarpions)
        {
            ++i;
            if (s == skoarpion)
            {
                found = true;
                break;
            }
        }

        if (!found)
            i = 0;

        selected = skoarpionComboBox->getSelectedId ();
        if (selected <= 0)
            selected = i;

        if (selected != i)
            skoarpionComboBox->setSelectedId (i, sendNotification);

    }
}

//==============================================================================
DebuggoarToolbar::DebuggoarToolbar ()
{
    instance = this;

    addAndMakeVisible (stepInButton = new TextButton ("stepInButton"));
    stepInButton->setTooltip (TRANS("Step In"));
    stepInButton->setButtonText (TRANS("_"));
    stepInButton->addListener (this);

    addAndMakeVisible (stepOverButton = new TextButton ("stepOverButton"));
    stepOverButton->setTooltip (TRANS("Step Over"));
    stepOverButton->setButtonText (TRANS("->"));
    stepOverButton->addListener (this);

    addAndMakeVisible (stepOutButton = new TextButton ("stepOutButton"));
    stepOutButton->setTooltip (TRANS("Step Out"));
    stepOutButton->setButtonText (TRANS("^"));
    stepOutButton->addListener (this);

    addAndMakeVisible (stopDebuggingButton = new TextButton ("stopDebuggingButton"));
    stopDebuggingButton->setTooltip (TRANS("Stop Debugging"));
    stopDebuggingButton->setButtonText (TRANS("[]"));
    stopDebuggingButton->addListener (this);
    stopDebuggingButton->setColour (TextButton::buttonColourId, Colours::grey);
    stopDebuggingButton->setColour (TextButton::buttonOnColourId, Colours::grey);
    stopDebuggingButton->setColour (TextButton::textColourOffId, Colours::black);
    stopDebuggingButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (minstrelLabel = new Label ("minstrelLabel",
                                                  TRANS("Voice:")));
    minstrelLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    minstrelLabel->setJustificationType (Justification::centredRight);
    minstrelLabel->setEditable (false, false, false);
    minstrelLabel->setColour (Label::textColourId, Colours::white);
    minstrelLabel->setColour (TextEditor::textColourId, Colours::black);
    minstrelLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (minstrelComboBox = new ComboBox ("minstrelComboBox"));
    minstrelComboBox->setEditableText (false);
    minstrelComboBox->setJustificationType (Justification::centredLeft);
    minstrelComboBox->setTextWhenNothingSelected (String());
    minstrelComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    minstrelComboBox->addListener (this);

    addAndMakeVisible (openExtDebuggerButton = new TextButton ("openExtDebuggerButton"));
    openExtDebuggerButton->setTooltip (TRANS("Open C++ Debugger"));
    openExtDebuggerButton->setButtonText (TRANS("%"));
    openExtDebuggerButton->addListener (this);

    addAndMakeVisible (continueDebuggingButton = new TextButton ("continueDebuggingButton"));
    continueDebuggingButton->setTooltip (TRANS("Continue"));
    continueDebuggingButton->setButtonText (TRANS(")>"));
    continueDebuggingButton->addListener (this);
    continueDebuggingButton->setColour (TextButton::buttonColourId, Colours::grey);
    continueDebuggingButton->setColour (TextButton::buttonOnColourId, Colours::grey);
    continueDebuggingButton->setColour (TextButton::textColourOffId, Colours::black);
    continueDebuggingButton->setColour (TextButton::textColourOnId, Colours::white);

    addAndMakeVisible (skoarpionLabel = new Label ("skoarpionLabel",
                                                   TRANS("Skoarpion:")));
    skoarpionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    skoarpionLabel->setJustificationType (Justification::centredRight);
    skoarpionLabel->setEditable (false, false, false);
    skoarpionLabel->setColour (Label::textColourId, Colours::white);
    skoarpionLabel->setColour (TextEditor::textColourId, Colours::black);
    skoarpionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (skoarpionComboBox = new ComboBox ("skoarpionComboBox"));
    skoarpionComboBox->setEditableText (false);
    skoarpionComboBox->setJustificationType (Justification::centredLeft);
    skoarpionComboBox->setTextWhenNothingSelected (String());
    skoarpionComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    skoarpionComboBox->addListener (this);

    addAndMakeVisible (stepToBeatButton = new TextButton ("stepToBeatButton"));
    stepToBeatButton->setTooltip (TRANS("Step To Beat"));
    stepToBeatButton->setButtonText (TRANS(")"));
    stepToBeatButton->addListener (this);

    addAndMakeVisible (playWithoutDebuggingButton = new TextButton ("playWithoutDebuggingButton"));
    playWithoutDebuggingButton->setTooltip (TRANS("Play Without Debugging"));
    playWithoutDebuggingButton->setButtonText (TRANS(")>"));
    playWithoutDebuggingButton->addListener (this);
    playWithoutDebuggingButton->setColour (TextButton::buttonColourId, Colours::grey);
    playWithoutDebuggingButton->setColour (TextButton::buttonOnColourId, Colours::grey);
    playWithoutDebuggingButton->setColour (TextButton::textColourOffId, Colours::black);
    playWithoutDebuggingButton->setColour (TextButton::textColourOnId, Colours::white);

    openExtDebuggerButton->setLookAndFeel (&awesome);
    openExtDebuggerButton->setButtonText(L"\xf188");

    continueDebuggingButton->setLookAndFeel (&awesome);
    continueDebuggingButton->setButtonText(L"\xf144");

    stopDebuggingButton->setLookAndFeel (&awesome);
    stopDebuggingButton->setButtonText(L"\xf28d");

    stepInButton->setLookAndFeel (&awesome);
    stepInButton->setButtonText(L"\xf13a");

    stepOutButton->setLookAndFeel (&awesome);
    stepOutButton->setButtonText(L"\xf139");

    stepOverButton->setLookAndFeel (&awesome);
    stepOverButton->setButtonText(L"\xf138");

    playWithoutDebuggingButton->setLookAndFeel (&awesome);
    playWithoutDebuggingButton->setButtonText (L"\xf04b");

    setSize (600, 32);
}

DebuggoarToolbar::~DebuggoarToolbar()
{
    instance = nullptr;

    stepInButton = nullptr;
    stepOverButton = nullptr;
    stepOutButton = nullptr;
    stopDebuggingButton = nullptr;
    minstrelLabel = nullptr;
    minstrelComboBox = nullptr;
    openExtDebuggerButton = nullptr;
    continueDebuggingButton = nullptr;
    skoarpionLabel = nullptr;
    skoarpionComboBox = nullptr;
    stepToBeatButton = nullptr;
    playWithoutDebuggingButton = nullptr;
}

//==============================================================================
void DebuggoarToolbar::paint (Graphics& g)
{
    g.fillAll (Colour (0xff222222));
}

void DebuggoarToolbar::resized()
{
    stepInButton->setBounds (getWidth() - 185, 6, 32, 20);
    stepOverButton->setBounds (getWidth() - 145, 6, 32, 20);
    stepOutButton->setBounds (getWidth() - 105, 6, 32, 20);
    stopDebuggingButton->setBounds (512, 6, 40, 20);
    minstrelLabel->setBounds (240, 6, 55, 20);
    minstrelComboBox->setBounds (296, 6, 150, 20);
    openExtDebuggerButton->setBounds (getWidth() - 49, 6, 40, 20);
    continueDebuggingButton->setBounds (464, 6, 40, 20);
    skoarpionLabel->setBounds (7, 6, 79, 20);
    skoarpionComboBox->setBounds (87, 6, 150, 20);
    stepToBeatButton->setBounds (getWidth() - 225, 6, 32, 20);
    playWithoutDebuggingButton->setBounds (600, 6, 40, 20);
}

void DebuggoarToolbar::buttonClicked (Button* buttonThatWasClicked)
{
    if (buttonThatWasClicked == stepInButton)
    {
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stepIn();
    }
    else if (buttonThatWasClicked == stepOverButton)
    {
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stepOver();
    }
    else if (buttonThatWasClicked == stepOutButton)
    {
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stepOut();
    }
    else if (buttonThatWasClicked == stopDebuggingButton)
    {
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stop ();
    }
    else if (buttonThatWasClicked == openExtDebuggerButton)
    {
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->cpp_breakpoint ();
    }
    else if (buttonThatWasClicked == continueDebuggingButton)
    {
        auto debuggoar = DebuggoarComponent::getDebuggoar ();
        debuggoar->startSession();
    }
    else if (buttonThatWasClicked == stepToBeatButton)
    {
        auto x = DebuggoarSession::getInstance ();
        if (x != nullptr)
            x->stepToBeat();
    }
    else if (buttonThatWasClicked == playWithoutDebuggingButton)
    {
        auto debuggoar = DebuggoarComponent::getDebuggoar ();
        debuggoar->playWithoutDebugging ();
    }
}

void DebuggoarToolbar::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    if (comboBoxThatHasChanged == minstrelComboBox)
        updateTabs ();
    else if (comboBoxThatHasChanged == skoarpionComboBox)
        updateTabs ();
}

void DebuggoarToolbar::updateTabs () {

    const auto selected_voice (minstrelComboBox->getSelectedId ());
    if (selected_voice <= 0)
        return;

    const auto voice (voices.getUnchecked (selected_voice - 1));
    if (voice == "")
        return;

    const auto selected_skoarpion (skoarpionComboBox->getSelectedId ());
    if (selected_skoarpion <= 0)
        return;

    const auto skoarpion (skoarpions.getUnchecked (selected_skoarpion - 1));
    if (skoarpion == nullptr)
        return;

    auto ast (SkoarASTComponent::getInstance ());
    if (ast != nullptr)
        ast->loadSkoarpion (skoarpion);

    auto projection (SkoarProjectionComponent::getInstance ());
    if (projection != nullptr)
    {
        SkoarString v (voice.toWideCharPointer ());
        projection->loadProjection (Skoarpion::projection (skoarpion, v));
    }
}

String DebuggoarToolbar::getVoice() {
    return minstrelComboBox->getText();
}

SkoarpionPtr DebuggoarToolbar::getSkoarpion () {
    auto id (skoarpionComboBox->getSelectedId ());
    if (id > 0)
        return skoarpions.getUnchecked (id - 1);

    if (skoarpions.size() > 0)
        return skoarpions.getUnchecked (0);

    return nullptr;
}

void DebuggoarToolbar::loadSkoar(Skoar* skoar) {

    const int already_selected_minstrel_id (minstrelComboBox->getSelectedId ());
    const int already_selected_skoarpion_id (skoarpionComboBox->getSelectedId ());

    const String all (L"all");
    const auto already_selected_minstrel (already_selected_minstrel_id > 0 ?
        voices.getUnchecked (already_selected_minstrel_id - 1) : all
    );

    const SkoarString skoar_name (L"skoar");
    const String already_selected_skoarpion (already_selected_skoarpion_id > 0 ?
        skoarpions.getUnchecked (already_selected_skoarpion_id - 1)->name.c_str() : skoar_name.c_str()
    );

    // load minstrels
    minstrelComboBox->clear();
    int i = 0;
    int selected_minstrel = 1;
    voices.clearQuick ();

    for (auto x : skoar->voices) {

        String voice (x.first.c_str ());
        if (voice == "")
            continue;

        minstrelComboBox->addItem(voice, ++i);

        if (already_selected_minstrel == voice)
            selected_minstrel = i;

        voices.add (voice);
    }

    // load skoarpions
    skoarpionComboBox->clear ();
    i = 0;
    auto selected_skoarpion = 1;
    skoarpions.clearQuick ();

    for (auto x : skoar->skoarpions)
    {
        String skoarpion_name (x->name.c_str ());
        if (skoarpion_name == "")
            continue;

        skoarpionComboBox->addItem (skoarpion_name, ++i);

        if (already_selected_skoarpion == skoarpion_name)
            selected_skoarpion = i;

        skoarpions.add (x);
    }

    minstrelComboBox->setSelectedId (selected_minstrel, dontSendNotification);
    skoarpionComboBox->setSelectedId (selected_skoarpion, sendNotification);
}

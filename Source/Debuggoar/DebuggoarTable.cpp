/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 4.3.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "DebuggoarTable.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DebuggoarTable::DebuggoarTable ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent = new GroupComponent ("groupy",
                                                            TRANS("data")));
    groupComponent->setTextLabelPosition (Justification::centredLeft);
    groupComponent->setColour (GroupComponent::outlineColourId, Colour (0x66ffffff));
    groupComponent->setColour (GroupComponent::textColourId, Colours::white);

    addAndMakeVisible (table = new TableListBox());
    table->setName ("table");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

DebuggoarTable::~DebuggoarTable()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    table = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DebuggoarTable::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DebuggoarTable::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent->setBounds (0, 0, proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    table->setBounds (16, 24, proportionOfWidth (1.0000f) - 34, proportionOfHeight (1.0000f) - 39);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DebuggoarTable" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="200">
  <BACKGROUND backgroundColour="ff000000"/>
  <GROUPCOMPONENT name="groupy" id="ca43c5bc9a154d01" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0 0 100% 100%" outlinecol="66ffffff"
                  textcol="ffffffff" title="data" textpos="33"/>
  <GENERICCOMPONENT name="table" id="b1b82fad102a4904" memberName="table" virtualName=""
                    explicitFocusOrder="0" pos="16 24 34M 39M" posRelativeW="ca43c5bc9a154d01"
                    posRelativeH="ca43c5bc9a154d01" class="TableListBox" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

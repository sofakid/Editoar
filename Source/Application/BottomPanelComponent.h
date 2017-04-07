#pragma once

#include "../jucer_Headers.h"
#include "../Utility/jucer_EditoarLookAndFeel.h"

class BottomPanelComponent : public Component {
public:
    BottomPanelComponent();
    ~BottomPanelComponent();

    void paint(Graphics& g) override;
    void resized() override;

private:

    class : public LookAndFeel_V3 {
    public:
        void drawTabButton(TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown) override
        {
            const Rectangle<int> activeArea(button.getActiveArea());

            const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();

            const Colour bkg(button.isFrontTab() ? Colours::darkblue.withAlpha(0.5f) : button.getTabBackgroundColour());

            g.setColour(bkg);
            g.fillRect(activeArea);

            g.setColour(button.findColour(TabbedButtonBar::tabOutlineColourId));

            Rectangle<int> r(activeArea);

            if (o != TabbedButtonBar::TabsAtBottom)   g.fillRect(r.removeFromTop(1));
            if (o != TabbedButtonBar::TabsAtTop)      g.fillRect(r.removeFromBottom(1));
            if (o != TabbedButtonBar::TabsAtRight)    g.fillRect(r.removeFromLeft(1));
            if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect(r.removeFromRight(1));

            const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;

            Colour col(bkg.contrasting().withMultipliedAlpha(alpha));

            if (TabbedButtonBar* bar = button.findParentComponentOfClass<TabbedButtonBar>())
            {
                TabbedButtonBar::ColourIds colID = button.isFrontTab() ? TabbedButtonBar::frontTextColourId
                    : TabbedButtonBar::tabTextColourId;

                if (bar->isColourSpecified(colID))
                    col = bar->findColour(colID);
                else if (isColourSpecified(colID))
                    col = findColour(colID);
            }

            const Rectangle<float> area(button.getTextArea().toFloat());

            float length = area.getWidth();
            float depth = area.getHeight();

            if (button.getTabbedButtonBar().isVertical())
                std::swap(length, depth);

            TextLayout textLayout;
            createTabTextLayout(button, length, depth, col, textLayout);

            AffineTransform t;

            switch (o)
            {
            case TabbedButtonBar::TabsAtRight:  t = t.rotated(float_Pi * 0.5f).translated(area.getRight(), area.getY()); break;
            case TabbedButtonBar::TabsAtLeft:   t = t.rotated(float_Pi * -0.5f).translated(area.getX(), area.getBottom()); break;
            case TabbedButtonBar::TabsAtTop:
            case TabbedButtonBar::TabsAtBottom: t = t.translated(area.getX(), area.getY()); break;
            default:                            jassertfalse; break;
            }

            g.addTransform(t);
            textLayout.draw(g, Rectangle<float>(length, depth));
        }
    } LNF;

    ScopedPointer<TabbedComponent> tabs;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BottomPanelComponent)
};

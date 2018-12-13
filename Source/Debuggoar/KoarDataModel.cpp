#include "KoarDataModel.h"
#include "all_skoarpuscles.hpp"

KoarDataModel::KoarDataModel(SkoarKoarPtr p) :
    koar(p),
    name(p->name.c_str()),
    skoarboard_entries(p->skoarboard->size()),
    stack_height(p->stack.size()),
    state_stack_height(p->state_stack.size()),
    skoarboard_pref("skoarboard :: "),
    stack_pref("stack :: "),
    state_stack_pref("state_stack :: ")
{
    String suffix(": ");

    for (auto x : p->skoarboard->table) {
        if (x.second == nullptr)
            continue;

        skoarboard.add(
            std::make_pair(
                skoarboard_pref + String(x.first.c_str()) + suffix,
                String(x.second->asString().c_str())
            )
        );
    }

    for (auto x : p->state_stack) {
        for (auto y : x->table) {
            if (y.second == nullptr)
                continue;
            state_stack.add(
                std::make_pair(
                    state_stack_pref + String(y.first.c_str()) + suffix,
                    String(y.second->asString().c_str())
                )
            );
        }
    }

    for (auto x : p->stack) {
        for (auto y : x->table) {
            if (y.second == nullptr)
                continue;
            stack.add(
                std::make_pair(
                    stack_pref + String(y.first.c_str()) + suffix,
                    String(y.second->asString().c_str())
                )
            );
        }
    }
}

KoarDataModel::~KoarDataModel() {
    koar = nullptr;
}

//==============================================================================
/** This must return the number of rows currently in the table.

If the number of rows changes, you must call TableListBox::updateContent() to
cause it to refresh the list.
*/
int KoarDataModel::getNumRows() {
    return names_n + stack.size() + state_stack.size() + skoarboard.size();
}

/** This must draw the background behind one of the rows in the table.

The graphics context has its origin at the row's top-left, and your method
should fill the area specified by the width and height parameters.

Note that the rowNumber value may be greater than the number of rows in your
list, so be careful that you don't assume it's less than getNumRows().
*/
void KoarDataModel::paintRowBackground(
    Graphics& g,
    int /*rowNumber*/,
    int width, int height,
    bool rowIsSelected) {

    Colour background = rowIsSelected ?
        Colours::darkmagenta : Colours::black;

    g.fillRect(0, 0, width, height);

}

/** This must draw one of the cells.

The graphics context's origin will already be set to the top-left of the cell,
whose size is specified by (width, height).

Note that the rowNumber value may be greater than the number of rows in your
list, so be careful that you don't assume it's less than getNumRows().
*/
void KoarDataModel::paintCell(
    Graphics& g,
    int rowNumber,
    int columnId,
    int width, int height,
    bool /*rowIsSelected*/) {

    if (rowNumber >= getNumRows()) {
        return;
    }

    if (columnId == EColumn::field) {
        g.setColour(Colours::grey);
    }
    else {
        g.setColour(Colours::blanchedalmond);
    }
    Rectangle<int> r(0, 0, width, height);

    auto skoarboard_offs = names_n;
    // values
    if (rowNumber < skoarboard_offs) {

        if (columnId == EColumn::field) {
            auto str = names[rowNumber];
            g.drawText(str, r, Justification::right);
        }
        else {
            auto str = vals[rowNumber];
            g.drawText(*str, r, Justification::left);
        }
    }
    // arrays
    else {
        const String suffix(" ]: ");
        
        auto state_stack_offs = skoarboard_offs + skoarboard.size();
        auto stack_offs = state_stack_offs + state_stack.size();

        // skoarboard
        if (rowNumber < state_stack_offs)
        {

            int child_i = rowNumber - static_cast<int>(skoarboard_offs);
            if (columnId == EColumn::field) {
                g.setColour(Colours::darkgrey);
                g.drawText(skoarboard[child_i].first, r, Justification::right);
            }
            else {
                g.drawText(skoarboard[child_i].second, r, Justification::left);
            }

        }

        // state_stack
        else if (rowNumber < stack_offs) {
            int child_i = rowNumber - static_cast<int>(state_stack_offs);
            if (columnId == EColumn::field) {
                g.drawText(state_stack[child_i].first, r, Justification::right);
            }
            else {
                g.drawText(state_stack[child_i].second, r, Justification::left);
            }

        } 

        // stack
        else {

            int child_i = rowNumber - static_cast<int>(stack_offs);
            if (columnId == EColumn::field) {
                g.setColour(Colours::darkgrey);
                g.drawText(stack[child_i].first, r, Justification::right);
            }
            else {
                g.drawText(stack[child_i].second, r, Justification::left);
            }
        }
    }
}

//==============================================================================
/** Returns the best width for one of the columns.

If you implement this method, you should measure the width of all the items
in this column, and return the best size.

Returning 0 means that the column shouldn't be changed.

This is used by TableListBox::autoSizeColumn() and TableListBox::autoSizeAllColumns().
*/
int KoarDataModel::getColumnAutoSizeWidth(int columnId) {
    const int char_width = 8;
    int biggest = 0;

    if (columnId == EColumn::field) {
        // names
        for (auto x : names) {
            auto w = x.length();
            if (w > biggest)
                biggest = w;
        }

        // skoarboard
        for (auto x : skoarboard) {
            auto w = x.first.length();
            if (w > biggest)
                biggest = w;
        }

        // state_stack
        for (auto x : state_stack) {
            auto w = x.first.length();
            if (w > biggest)
                biggest = w;
        }

        // stack
        for (auto x : stack) {
            auto w = x.first.length();
            if (w > biggest)
                biggest = w;
        }

        return biggest * char_width;
    }
    
    // values
    for (auto x : vals) {
        auto w = x->length();
        if (w > biggest)
            biggest = w;
    }

    // skoarboard
    for (auto x : skoarboard) {
        auto w = x.second.length();
        if (w > biggest)
            biggest = w;
    }

    // state_stack
    for (auto x : state_stack) {
        auto w = x.second.length();
        if (w > biggest)
            biggest = w;
    }

    // stack
    for (auto x : stack) {
        auto w = x.second.length();
        if (w > biggest)
            biggest = w;
    }

    return biggest * char_width;
}

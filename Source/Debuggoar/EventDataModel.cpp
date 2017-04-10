#include "EventDataModel.h"
#include "all_skoarpuscles.hpp"

EventDataModel::EventDataModel(SkoarEventPtr p)
{
    String suffix(": ");

    for (auto x : p->table) {
        if (x.second == nullptr)
            continue;
        entries.add(
            make_pair(
                String(x.first.c_str()) + suffix,
                String(x.second->asString().c_str())
            )
        );
    }
}

EventDataModel::~EventDataModel() {
    entries.clear();
}

//==============================================================================
/** This must return the number of rows currently in the table.

If the number of rows changes, you must call TableListBox::updateContent() to
cause it to refresh the list.
*/
int EventDataModel::getNumRows() {
    return entries.size();
}

/** This must draw the background behind one of the rows in the table.

The graphics context has its origin at the row's top-left, and your method
should fill the area specified by the width and height parameters.

Note that the rowNumber value may be greater than the number of rows in your
list, so be careful that you don't assume it's less than getNumRows().
*/
void EventDataModel::paintRowBackground(
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
void EventDataModel::paintCell(
    Graphics& g,
    int rowNumber,
    int columnId,
    int width, int height,
    bool /*rowIsSelected*/) {

    if (rowNumber >= getNumRows()) {
        return;
    }

    Rectangle<int> r(0, 0, width, height);

    if (columnId == EColumn::field) {
        g.setColour(Colours::grey);
        g.drawText(entries[rowNumber].first, r, Justification::right);
    }
    else {
        g.setColour(Colours::blanchedalmond);
        g.drawText(entries[rowNumber].second, r, Justification::left);
    }

}

//==============================================================================
/** Returns the best width for one of the columns.

If you implement this method, you should measure the width of all the items
in this column, and return the best size.

Returning 0 means that the column shouldn't be changed.

This is used by TableListBox::autoSizeColumn() and TableListBox::autoSizeAllColumns().
*/
int EventDataModel::getColumnAutoSizeWidth(int columnId) {
    const int char_width = 8;
    int biggest = 0;

    if (columnId == EColumn::field) {
        
        for (auto x : entries) {
            auto w = x.first.length();
            if (w > biggest)
                biggest = w;
        }

        return biggest * char_width;
    }

    for (auto x : entries) {
        auto w = x.second.length();
        if (w > biggest)
            biggest = w;
    }

    return biggest * char_width;
}


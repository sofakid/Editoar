#include "FairyDataModel.h"
#include "all_skoarpuscles.hpp"

FairyDataModel::FairyDataModel(SkoarFairyPtr p) :
    name(p->name.c_str()),
    impression(p->impression == nullptr ?
        L"" : p->impression->asString().c_str()),
    noat(p->noat == nullptr ?
        L"" : p->noat->asString().c_str())
{
}

FairyDataModel::~FairyDataModel() {
}

//==============================================================================
/** This must return the number of rows currently in the table.

If the number of rows changes, you must call TableListBox::updateContent() to
cause it to refresh the list.
*/
int FairyDataModel::getNumRows() {
    return names_n;
}

/** This must draw the background behind one of the rows in the table.

The graphics context has its origin at the row's top-left, and your method
should fill the area specified by the width and height parameters.

Note that the rowNumber value may be greater than the number of rows in your
list, so be careful that you don't assume it's less than getNumRows().
*/
void FairyDataModel::paintRowBackground(
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
void FairyDataModel::paintCell(
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

    if (columnId == EColumn::field) {
        auto str = names[rowNumber];
        g.drawText(str, r, Justification::right);
    }
    else {
        auto str = vals[rowNumber];
        g.drawText(*str, r, Justification::left);
    }
}

//==============================================================================
/** Returns the best width for one of the columns.

If you implement this method, you should measure the width of all the items
in this column, and return the best size.

Returning 0 means that the column shouldn't be changed.

This is used by TableListBox::autoSizeColumn() and TableListBox::autoSizeAllColumns().
*/
int FairyDataModel::getColumnAutoSizeWidth(int columnId) {
    const int char_width = 8;
    int biggest = 0;

    if (columnId == EColumn::field) {
        // names
        for (auto x : names) {
            auto w = x.length();
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

    return biggest * char_width;
}

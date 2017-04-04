#include "SkoarpuscleDataModel.h"

SkoarpuscleDataModel::SkoarpuscleDataModel(SkoarpusclePtr p) :
    skoarpuscle(p),
    type(p->typeAsString().c_str()),
    val(p->valAsString().c_str()),
    impressionable(p->isImpressionable() ? "true" : "false"),
    noatworthy(p->isNoatworthy() ? "true" : "false"),
    county(p->isCounty() ? "true" : "false"),
    kind(p->kind)
{
}

SkoarpuscleDataModel::~SkoarpuscleDataModel() {
    skoarpuscle = nullptr;
}

//==============================================================================
/** This must return the number of rows currently in the table.

If the number of rows changes, you must call TableListBox::updateContent() to
cause it to refresh the list.
*/
int SkoarpuscleDataModel::getNumRows() {
    return names_n;
}

/** This must draw the background behind one of the rows in the table.

The graphics context has its origin at the row's top-left, and your method
should fill the area specified by the width and height parameters.

Note that the rowNumber value may be greater than the number of rows in your
list, so be careful that you don't assume it's less than getNumRows().
*/
void SkoarpuscleDataModel::paintRowBackground(
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
void SkoarpuscleDataModel::paintCell(
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
/** This is used to create or update a custom component to go in a cell.

Any cell may contain a custom component, or can just be drawn with the paintCell() method
and handle mouse clicks with cellClicked().

This method will be called whenever a custom component might need to be updated - e.g.
when the table is changed, or TableListBox::updateContent() is called.

If you don't need a custom component for the specified cell, then return nullptr.
(Bear in mind that even if you're not creating a new component, you may still need to
delete existingComponentToUpdate if it's non-null).

If you do want a custom component, and the existingComponentToUpdate is null, then
this method must create a new component suitable for the cell, and return it.

If the existingComponentToUpdate is non-null, it will be a pointer to a component previously created
by this method. In this case, the method must either update it to make sure it's correctly representing
the given cell (which may be different from the one that the component was created for), or it can
delete this component and return a new one.
*/
Component* SkoarpuscleDataModel::refreshComponentForCell(int /*rowNumber*/, int /*columnId*/, bool /*isRowSelected*/,
    Component* /*existingComponentToUpdate*/) {
    return nullptr;
}

//==============================================================================
/** This callback is made when the user clicks on one of the cells in the table.

The mouse event's coordinates will be relative to the entire table row.
@see cellDoubleClicked, backgroundClicked
*/
void SkoarpuscleDataModel::cellClicked(int /*rowNumber*/, int /*columnId*/, const MouseEvent&) {

}

/** This callback is made when the user clicks on one of the cells in the table.

The mouse event's coordinates will be relative to the entire table row.
@see cellClicked, backgroundClicked
*/
void SkoarpuscleDataModel::cellDoubleClicked(int /*rowNumber*/, int /*columnId*/, const MouseEvent&) {

}

/** This can be overridden to react to the user double-clicking on a part of the list where
there are no rows.

@see cellClicked
*/
void SkoarpuscleDataModel::backgroundClicked(const MouseEvent&) {

}

//==============================================================================
/** This callback is made when the table's sort order is changed.

This could be because the user has clicked a column header, or because the
TableHeaderComponent::setSortColumnId() method was called.

If you implement this, your method should re-sort the table using the given
column as the key.
*/
void SkoarpuscleDataModel::sortOrderChanged(int /*newSortColumnId*/, bool /*isForwards*/) {

}

//==============================================================================
/** Returns the best width for one of the columns.

If you implement this method, you should measure the width of all the items
in this column, and return the best size.

Returning 0 means that the column shouldn't be changed.

This is used by TableListBox::autoSizeColumn() and TableListBox::autoSizeAllColumns().
*/
int SkoarpuscleDataModel::getColumnAutoSizeWidth(int columnId) {
    const int char_width = 7;
    if (columnId == EColumn::field) {
        return String("impressionable: ").length() * char_width;
    }
    int biggest = 0;
    for (auto x : vals) {
        auto w = x->length();
        if (w > biggest)
            biggest = w;
    }
    return biggest * char_width;
}

/** Returns a tooltip for a particular cell in the table. */
String SkoarpuscleDataModel::getCellTooltip(int /*rowNumber*/, int /*columnId*/) {
    return String();
}

//==============================================================================
/** Override this to be informed when rows are selected or deselected.
@see ListBox::selectedRowsChanged()
*/
void SkoarpuscleDataModel::selectedRowsChanged(int /*lastRowSelected*/) {

}

/** Override this to be informed when the delete key is pressed.
@see ListBox::deleteKeyPressed()
*/
void SkoarpuscleDataModel::deleteKeyPressed(int /*lastRowSelected*/) {

}

/** Override this to be informed when the return key is pressed.
@see ListBox::returnKeyPressed()
*/
void SkoarpuscleDataModel::returnKeyPressed(int /*lastRowSelected*/) {

}

/** Override this to be informed when the list is scrolled.

This might be caused by the user moving the scrollbar, or by programmatic changes
to the list position.
*/
void SkoarpuscleDataModel::listWasScrolled() {

}

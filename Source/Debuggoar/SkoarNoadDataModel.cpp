#include "SkoarNoadDataModel.h"


SkoarNoadDataModel::SkoarNoadDataModel(SkoarNoadPtr p) :
    noad(p),
    name(p->name.c_str()),
    address(p->address.code().c_str()),
    parent(p->parent == nullptr ? L"" : p->parent->name.c_str()),
    skoarpuscle(p->skoarpuscle == nullptr ? L"" : p->skoarpuscle->asString().c_str()),
    toke(p->toke == nullptr ? L"" : p->toke->lexeme.c_str()),
    voice(p->voice == nullptr ? L"" : p->voice->name.c_str()),
    skoap(p->voice == nullptr ? L"" : p->skoap->name.c_str()),
    offs(p->offs),
    size(p->size)
{
    for (auto x : p->children) {
        children.add(new String(x->name.c_str()));
    }
}

SkoarNoadDataModel::~SkoarNoadDataModel() {
    noad = nullptr;
}

//==============================================================================
/** This must return the number of rows currently in the table.

If the number of rows changes, you must call TableListBox::updateContent() to
cause it to refresh the list.
*/
int SkoarNoadDataModel::getNumRows() {
    int children_n = children.size();
    return names_n + children_n;
}

/** This must draw the background behind one of the rows in the table.

The graphics context has its origin at the row's top-left, and your method
should fill the area specified by the width and height parameters.

Note that the rowNumber value may be greater than the number of rows in your
list, so be careful that you don't assume it's less than getNumRows().
*/
void SkoarNoadDataModel::paintRowBackground(Graphics& g,
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
void SkoarNoadDataModel::paintCell(Graphics& g,
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

    if (rowNumber < names_n) {
        if (columnId == EColumn::field) {
            auto str = names[rowNumber];
            g.drawText(str, r, Justification::right);
        }
        else {
            auto str = vals[rowNumber];
            g.drawText(*str, r, Justification::left);
        }
    }
    else {
        int child_i = rowNumber - names_n;
        if (columnId == EColumn::field) {
            String prefix("children[");
            String index(child_i);
            String suffix("]: ");
            
            g.drawText(prefix + index + suffix, r, Justification::right);
        }
        else {
            g.drawText(*children[child_i], r, Justification::left);
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
int SkoarNoadDataModel::getColumnAutoSizeWidth(int columnId) {
    const int char_width = 8;
    if (columnId == EColumn::field) {
        return String("skoarpuscle: ").length() * char_width;
    }
    int biggest = 0;
    for (auto x : vals) {
        auto w = x->length();
        if (w > biggest)
            biggest = w;
    }
    for (auto x : children) {
        auto w = x->length();
        if (w > biggest)
            biggest = w;
    }
    return biggest * char_width;
}

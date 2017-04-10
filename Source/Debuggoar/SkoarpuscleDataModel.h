#pragma once
#include "../jucer_Headers.h"
#include "all_skoarpuscles.hpp"

class SkoarpuscleDataModel : public TableListBoxModel {

public:

    enum EColumn {
        field = 1,
        value
    };

    SkoarpuscleDataModel();
    SkoarpuscleDataModel(SkoarpusclePtr);

    ~SkoarpuscleDataModel() override;

    int getNumRows() override;

    void paintRowBackground(Graphics&,
        int rowNumber,
        int width, int height,
        bool rowIsSelected) override;

    void paintCell(Graphics&,
        int rowNumber,
        int columnId,
        int width, int height,
        bool rowIsSelected) override;

    int getColumnAutoSizeWidth(int columnId) override;

private:
    SkoarpusclePtr skoarpuscle;

    String type;
    String val;
    String impressionable;

    String noatworthy;
    String county;
    String kind;

    static const size_t names_n = 6;
    const String names[names_n] = {
        "type: ",
        "val: ",
        "impressionable: ",

        "noatworthy: ",
        "county: ",
        "kind: "
     
    };

    const String* vals[names_n] = {
        &type,
        &val,
        &impressionable,
        &noatworthy,
        &county,
        &kind
    };

};

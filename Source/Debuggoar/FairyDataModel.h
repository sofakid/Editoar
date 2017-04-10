#pragma once
#include "../jucer_Headers.h"
#include "fairy.hpp"

class FairyDataModel : public TableListBoxModel {

public:

    enum EColumn {
        field = 1,
        value
    };

    FairyDataModel(SkoarFairyPtr);

    ~FairyDataModel() override;

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

    String name;
    String impression;
    String noat;
    String boolean_impression;
    String l_value;

    static const size_t names_n = 5;
    const String names[names_n] = {
        "name: ",
        "impression: ",
        "noat: ",
        "boolean_impression: ",
        "l_value: "
    };

    const String* vals[names_n] = {
        &name,
        &impression,
        &noat,
        &boolean_impression,
        &l_value
    };

};

#pragma once
#include "../jucer_Headers.h"
#include "koar.hpp"
#include "event.hpp"

class KoarDataModel : public TableListBoxModel {

public:

    enum EColumn {
        field = 1,
        value
    };

    KoarDataModel(SkoarKoarPtr);

    ~KoarDataModel() override;

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
    SkoarKoarPtr koar;

    String name;
    String skoarboard_entries;
    String stack_height;
    String state_stack_height;

    String skoarboard_pref;
    String stack_pref;
    String state_stack_pref;

    static const size_t names_n = 4;
    const String names[names_n] = {
        "name: ",
        "skoarboard_height: ",
        "stack_height: ",
        "state_stack_height: "
    };

    const String* vals[names_n] = {
        &name,
        &skoarboard_entries,
        &stack_height,
        &state_stack_height
    };

    Array<std::pair<String, String>> stack;
    Array<std::pair<String, String>> state_stack;
    Array<std::pair<String, String>> skoarboard;

};

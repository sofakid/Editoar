#pragma once
#include "../jucer_Headers.h"
#include "event.hpp"

class EventDataModel : public TableListBoxModel {

public:

    enum EColumn {
        field = 1,
        value
    };

    EventDataModel(SkoarEventPtr);

    ~EventDataModel() override;

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
    Array<std::pair<String, String>> entries;

};

#pragma once
#include "../jucer_Headers.h"
#include "noad.hpp"
#include "koar.hpp"
#include "skoarpuscle.hpp"

class SkoarNoadDataModel : public TableListBoxModel {
public:

    enum EColumn {
        field = 1,
        value
    };

    SkoarNoadDataModel(SkoarNoadPtr);
    ~SkoarNoadDataModel() override;

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

    SkoarNoadPtr noad;

    String name;
    String address;
    String parent;

    String skoarpuscle;
    String toke;
    String voice;
    
    String skoap;
    String size;
    String offs;

    static const size_t names_n = 9;
    const String names[names_n] = {
        "name: ",
        "address: ",
        "parent: ",
        
        "skoarpuscle: ",
        "toke: ",
        "voice: ",
        
        "skoap: ",
        "offs: ",
        "size: "
    };
    
    const String* vals[names_n] = {
        &name,
        &address,
        &parent,

        &skoarpuscle,
        &toke,
        &voice,
        
        &skoap,
        &offs,
        &size
    };

    OwnedArray<String> children;

};



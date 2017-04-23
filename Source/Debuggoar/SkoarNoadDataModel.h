#pragma once
#include "../jucer_Headers.h"
#include "noad.hpp"
#include "koar.hpp"
#include "skoarpuscle.hpp"

class SkoarNoadDataModel : public TableListBoxModel
{
public:

    enum EColumn
    {
        field = 1,
        value
    };

    SkoarNoadDataModel (SkoarNoadPtr);
    ~SkoarNoadDataModel () override;

    int getNumRows () override;

    void paintRowBackground (Graphics&,
        int rowNumber,
        int width, int height,
        bool rowIsSelected) override;

    void paintCell (Graphics&,
        int rowNumber,
        int columnId,
        int width, int height,
        bool rowIsSelected) override;

    int getColumnAutoSizeWidth (int columnId) override;


private:
    SkoarNoadPtr noad;

    String name;
    String address;
    String parent;

    String skoarpuscle;
    String toke;
    String voice;

    String size;
    String offs;

    static const size_t names_n = 8;
    const String names[names_n] = {
        "name: ",
        "address: ",
        "parent: ",

        "skoarpuscle: ",
        "toke: ",
        "voice: ",

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

        &offs,
        &size
    };

    OwnedArray<String> children;

};


class SkoarNoaditeDataModel : public TableListBoxModel
{
public:

    enum EColumn
    {
        field = 1,
        value
    };

    SkoarNoaditeDataModel (const SkoarNoadite&);

    int getNumRows () override;

    void paintRowBackground (Graphics&,
        int rowNumber,
        int width, int height,
        bool rowIsSelected) override;

    void paintCell (Graphics&,
        int rowNumber,
        int columnId,
        int width, int height,
        bool rowIsSelected) override;

    int getColumnAutoSizeWidth (int columnId) override;


private:
    String name;
    String skoarpuscle;
    String voice;
    String size;
    String offs;

    static const size_t names_n = 5;
    const String names[names_n] = {
        "name: ",
        "skoarpuscle: ",
        "voice: ",
        "offs: ",
        "size: "
    };

    const String* vals[names_n] = {
        &name,
        &skoarpuscle,
        &voice,
        &offs,
        &size
    };
};



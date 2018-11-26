#include "SkoarLogger.hpp"


// ---------------------------------------------------
SkoarUiLogger::SkoarUiLogger(
        Colour d_colour,
        Colour i_colour,
        Colour w_colour,
        Colour e_colour
    ) : ui(nullptr),
        d_col(d_colour),
        i_col(i_colour),
        w_col(w_colour),
        e_col(e_colour) {}

SkoarUiLogger::~SkoarUiLogger() {
    ui = nullptr;
}

void SkoarUiLogger::setUi(ISkoarUiLogger *component) {
    ui = component;
}

ISkoarUiLogger* SkoarUiLogger::getUi() {
    return ui;
}

void SkoarUiLogger::log_d(const std::wstring &s) {
    ISkoarUiLogger *copy = ui;
    if (copy != nullptr) {
        String str(s.c_str());
        copy->logMsg(str, d_col);
    }
}
void SkoarUiLogger::log_i(const std::wstring &s) {
    ISkoarUiLogger *copy = ui;
    if (copy != nullptr) {
        String str(s.c_str());
        copy->logMsg(str, i_col);
    }

}

void SkoarUiLogger::log_w(const std::wstring &s) {
    ISkoarUiLogger *copy = ui;
    if (copy != nullptr) {
        String str(s.c_str());
        copy->logMsg(str, w_col);
    }
}

void SkoarUiLogger::log_e(const std::wstring &s) {
    ISkoarUiLogger *copy = ui;
    if (copy != nullptr) {
        String str(s.c_str());
        copy->logMsg(str, e_col);
    }
}

// SkoarLog is global.
//
// log stuff like: SkoarLog.d("derp", 7, 2.8)
//
const Colour blue(30, 100, 255);
const Colour white(200, 200, 200);
const Colour yellow(230, 230, 100);
const Colour red(255, 95, 70);
SkoarUiLogger SkoarLog (blue, white, yellow, red);
//
// the following doesn't work, other static stuff isn't necessarily initialized yet: 
//SkoarUiLogger SkoarLog(Colours::lightgreen, Colours::white, Colours::lightyellow, Colours::red);

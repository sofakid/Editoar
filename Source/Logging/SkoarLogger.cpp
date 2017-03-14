#include "SkoarLogger.hpp"

// ---------------------------------------------------
void SkoarNullLogger::log_d(const std::wstring &) {}
void SkoarNullLogger::log_i(const std::wstring &) {}
void SkoarNullLogger::log_w(const std::wstring &) {}
void SkoarNullLogger::log_e(const std::wstring &) {}

// ---------------------------------------------------
void SkoarConsoleLogger::log_d(const std::wstring &s) {
	std::wcout << L"D .. " << s << std::endl;
}
void SkoarConsoleLogger::log_i(const std::wstring &s) {
	std::wcout << L"I -- " << s << std::endl;
}
void SkoarConsoleLogger::log_w(const std::wstring &s) {
	std::wcout << L"W == " << s << std::endl;
}
void SkoarConsoleLogger::log_e(const std::wstring &s) {
	std::wcout << L"E !! " << s << std::endl;
}

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
const Colour green(0, 255, 0);
const Colour white(255, 255, 255);
const Colour yellow(255, 255, 100);
const Colour red(255, 70, 70);
SkoarUiLogger SkoarLog (green, white, yellow, red);
//
// the following doesn't work, other static stuff isn't necessarily initialized yet: 
//SkoarUiLogger SkoarLog(Colours::lightgreen, Colours::white, Colours::lightyellow, Colours::red);

#pragma once

#include "skoar_public.hpp"
#include "../../JuceLibraryCode/JuceHeader.h"

struct SkoarNullLogger : public ISkoarLog {
	void log_d(const std::wstring &s) override;
	void log_i(const std::wstring &s) override;
	void log_w(const std::wstring &s) override;
	void log_e(const std::wstring &s) override;
};

struct SkoarConsoleLogger : public ISkoarLog {
	void log_d(const std::wstring &s) override;
	void log_i(const std::wstring &s) override;
	void log_w(const std::wstring &s) override;
	void log_e(const std::wstring &s) override;
};

class ISkoarUiLogger {
public:
    virtual void logMsg(String &s, Colour colour) = 0;
};

class SkoarUiLogger : public ISkoarLog {
public:
    SkoarUiLogger(
        Colour d_colour,
        Colour i_colour,
        Colour w_colour,
        Colour e_colour);
    ~SkoarUiLogger();

    void setUi(ISkoarUiLogger *component);
    ISkoarUiLogger* getUi();

    void log_d(const std::wstring &s) override;
    void log_i(const std::wstring &s) override;
    void log_w(const std::wstring &s) override;
    void log_e(const std::wstring &s) override;

private:
    ISkoarUiLogger *ui;
    Colour d_col;
    Colour i_col;
    Colour w_col;
    Colour e_col;
};

extern SkoarUiLogger SkoarLog;

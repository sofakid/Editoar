
#ifndef SKOARLOGGER_H_INCLUDED
#define SKOARLOGGER_H_INCLUDED


#include "../jucer_Headers.h"
#include "../Application/jucer_Application.h"

struct SkoarNullLogger : public ISkoarLog {
	void d(const std::wstring &s) override;
	void i(const std::wstring &s) override;
	void w(const std::wstring &s) override;
	void e(const std::wstring &s) override;
};

struct SkoarConsoleLogger : public ISkoarLog {
	void d(const std::wstring &s) override;
	void i(const std::wstring &s) override;
	void w(const std::wstring &s) override;
	void e(const std::wstring &s) override;
};

#endif  // SKOARLOGGER_H_INCLUDED

#include "SkoarLogger.hpp"

// ---------------------------------------------------
void SkoarNullLogger::d(const std::wstring &s) {}
void SkoarNullLogger::i(const std::wstring &s) {}
void SkoarNullLogger::w(const std::wstring &s) {}
void SkoarNullLogger::e(const std::wstring &s) {}

// ---------------------------------------------------
void SkoarConsoleLogger::d(const std::wstring &s) {
	std::wcout << L"D .. " << s << std::endl;
}
void SkoarConsoleLogger::i(const std::wstring &s) {
	std::wcout << L"I -- " << s << std::endl;
}
void SkoarConsoleLogger::w(const std::wstring &s) {
	std::wcout << L"W == " << s << std::endl;
}
void SkoarConsoleLogger::e(const std::wstring &s) {
	std::wcout << L"E !! " << s << std::endl;
}


#ifndef UTIL_H
#define UTIL_H

#include <vector>

using namespace std;

vector<string> splitString(const string src,const char sem);

int str2Int(string str);
string suInt2Str(int i);

string currentDateTime();

string ansi2Utf8(const char *srcstr);
string suUtf82Ansi(const char *srcstr);
void trimStr(string &s);
string ws2s(const std::wstring& ws);


#ifdef WIN32
#include <Windows.h>

BOOL getAppVersion(string path, int &major, int &minor, int &build, int &revision);
void removeFileReadOnlyAttr(string filename);
BOOL winSystemShutdown(LPWSTR lpMsg, int timeout, BOOL restart);
string hostIP();
wstring s2ws(const std::string& s);
#else

#endif

#endif // UTIL_H

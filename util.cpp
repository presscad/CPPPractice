#include "util.h"
#include <sstream>
#include <time.h>
#include <algorithm>

vector<string> splitString(const string src, const char sem){
    string::size_type pos1 = 0, pos2 = 0;
    vector<string> v;
    string s;
    if(src.length() > 0) {
        while((pos2 = src.find(sem, pos1)) != string::npos) {
            s = src.substr(pos1, pos2 - pos1);
            v.push_back(s);
            pos1 = pos2 + 1;
        }
        // line is not end with sem
        if(pos1 != src.length()) {
            s = src.substr(pos1);
            v.push_back(s);
        }
    }
    return v;
}

int str2Int(string str){
    int i;
    stringstream ss(str);
    ss >> i;
    return i;
}

string suInt2Str(int i)
{
    stringstream ss;
    locale loc("C");
    ss.imbue(loc);
    ss<<i;
    string s = ss.str();
    return s;
}

string currentDateTime(){
    time_t now = time(0);
    tm  tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}

string ansi2Utf8(const char *srcstr)
{
    int rev;
    wchar_t *wstr = NULL;
    char *utf8 = NULL;
    string rstring;

    if(srcstr == NULL || strlen(srcstr) == 0) return "";
#ifdef  WIN32
    // ANSI to UNICODE
    rev = MultiByteToWideChar(CP_ACP, 0, srcstr, -1, wstr, 0);
    wstr = (wchar_t*)malloc(rev * sizeof(wchar_t));
    if(wstr == NULL) return "";
    rev = MultiByteToWideChar(CP_ACP, 0, srcstr, -1, wstr, rev);

    // UNICODE to UTF-8
    rev = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, 0, 0, 0);
    utf8 = (char*)malloc(rev);
    if(utf8 == NULL) return "";
    rev = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, rev, 0, 0);

    rstring = utf8;
    free(wstr);
    free(utf8);
    return rstring;
#else
    /*
    const char* currLcctype = setlocale(LC_CTYPE, NULL);
    setlocale(LC_CTYPE, LOCALE_CONVERT);
    wchar_t* ws = new wchar_t[strlen(srcstr) * 2];
    memset(ws, 0, strlen(srcstr) * 2);
    mbstate_t mbs;
    memset(&mbs, 0, sizeof(mbs));
    size_t st = mbsrtowcs(ws, &srcstr, strlen(srcstr) * 2, &mbs);
    ws[st] = L'\0';

    char* ansi = new char[wcslen(ws) * 4 + 1];
    memset(ansi, 0, wcslen(ws) * 4 + 1);
    mbstate_t mbs2;
    memset(&mbs2, 0, sizeof(mbs2));
    const wchar_t* wsc = ws;
    size_t st2 = wcsrtombs(ansi , &wsc, wcslen(ws) * 4, &mbs2);

    setlocale(LC_CTYPE, currLcctype);
    rstring = ansi;
    delete[] ws;
    delete[] ansi;*/
    rstring = srcstr;
    return rstring;
#endif
}

string suUtf82Ansi(const char *srcstr)
{
    int rev;
    wchar_t *wstr = NULL;
    string rstring;

    char *ansi = NULL;
    if(srcstr == NULL || strlen(srcstr) == 0) return "";
#ifdef WIN32
    // UTF8 to UNICODE
    rev = MultiByteToWideChar(CP_UTF8, 0, srcstr, -1, wstr, 0);
    wstr = (wchar_t*)malloc(rev * sizeof(wchar_t));
    if(wstr == NULL) return "";
    rev = MultiByteToWideChar(CP_UTF8, 0, srcstr, -1, wstr, rev);

    // UNICODE to ANSI
    rev = WideCharToMultiByte(CP_ACP, 0, wstr, -1, ansi, 0, 0, 0);
    ansi = (char*)malloc(rev);
    if(ansi == NULL) return "";
    rev = WideCharToMultiByte(CP_ACP, 0, wstr, -1, ansi, rev, 0, 0);

    rstring = ansi;
    free(wstr);
    free(ansi);
    return rstring;
#else
    /*
    const char* currLcctype = setlocale(LC_CTYPE, NULL);
    setlocale(LC_CTYPE, LOCALE_CONVERT);
    wchar_t* ws = new wchar_t[strlen(srcstr) * 2];
    memset(ws, 0, strlen(srcstr) * 2);
    mbstate_t mbs;
    memset(&mbs, 0, sizeof(mbs));
    size_t st = mbsrtowcs(ws, &srcstr, strlen(srcstr) * 2, &mbs);
    ws[st] = L'\0';

    ansi = new char[wcslen(ws) * 4 + 1];
    memset(ansi, 0, wcslen(ws) * 4 + 1);
    mbstate_t mbs2;
    memset(&mbs2, 0, sizeof(mbs2));
    const wchar_t* wsc = ws;
    size_t st2 = wcsrtombs(ansi , &wsc, wcslen(ws) * 4, &mbs2);

    setlocale(LC_CTYPE, currLcctype);
    rstring = ansi;
    delete[] ansi;*/
    rstring = srcstr;
    return rstring;
#endif
}

void trimStr(string &str){
    int n;
    while (1) {
        if (str.length() == 0) break;
        if (!isascii(str[0])) break;
        if (!isspace(str[0])) break;
        str.erase(0, 1);
    }
    while (1) {
        n = (int)str.length();
        if (n == 0) break;
        if (!isascii(str[n-1])) break;
        if (!isspace(str[n-1])) break;
        str.erase(n-1, 1);
    }
}

string ws2s(const std::wstring& ws){
    std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
    setlocale(LC_ALL, "chs");
    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest,0,_Dsize);
    wcstombs(_Dest,_Source,_Dsize);
    std::string result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, curLocale.c_str());
    return result;
}

#ifdef WIN32
#include <Windows.h>

BOOL getAppVersion(string path, int &major, int &minor, int &build, int &revision){
    DWORD dwHandle, dwLen;
    UINT BufLen;
    LPTSTR lpData;
    VS_FIXEDFILEINFO *pFileInfo;
    dwLen = GetFileVersionInfoSize(s2ws(path).c_str(), &dwHandle);
    if (!dwLen)
    return FALSE;

    lpData = (LPTSTR) malloc (dwLen);
    if (!lpData)
    return FALSE;

    if(!GetFileVersionInfo(s2ws(path).c_str(), dwHandle, dwLen, lpData)){
        free (lpData);
        return FALSE;
    }
    if(VerQueryValue(lpData, TEXT("\\"), (LPVOID *) &pFileInfo, (PUINT)&BufLen)){
        major =     (pFileInfo->dwProductVersionMS >> 16) & 0xffff;
        minor =     (pFileInfo->dwProductVersionMS >>  0) & 0xffff;
        revision =  (pFileInfo->dwProductVersionLS >> 16) & 0xffff;
        build =     (pFileInfo->dwProductVersionLS >>  0) & 0xffff;
        free (lpData);
        return TRUE;
    }
    free (lpData);
    return FALSE;
}

void removeFileReadOnlyAttr(string filename)
{
    DWORD dwAttribute = GetFileAttributes(s2ws(filename).c_str());
    if(dwAttribute & FILE_ATTRIBUTE_READONLY)
    {
        dwAttribute &= ~FILE_ATTRIBUTE_READONLY;
        SetFileAttributes(s2ws(filename).c_str(),dwAttribute);
    }
}

BOOL winSystemShutdown(LPWSTR lpMsg, int timeout, BOOL restart)
{
   HANDLE hToken;              // handle to process token
   TOKEN_PRIVILEGES tkp;       // pointer to token structure

   BOOL fResult;               // system shutdown flag

   // Get the current process token handle so we can get shutdown privilege.
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
      return FALSE;
   }

   // Get the LUID for shutdown privilege.
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);

   tkp.PrivilegeCount = 1;  // one privilege to set
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

   // Get shutdown privilege for this process.
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);

   // Cannot test the return value of AdjustTokenPrivileges.
   if(GetLastError() != ERROR_SUCCESS) {
       char errorcode[256];
       sprintf(errorcode, "%d", GetLastError());
       return FALSE;
   }

   // Display the shutdown dialog box and start the countdown.
   fResult = InitiateSystemShutdown(NULL, lpMsg, timeout, TRUE, restart);
   if(!fResult) {
       char errorcode[256];
       sprintf(errorcode, "%d", GetLastError());
       return FALSE;
   }

   // Disable shutdown privilege.
   tkp.Privileges[0].Attributes = 0;
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
   return TRUE;
}

string hostIP()
{
    char szBuffer[1024];
    string ip;

    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if(::WSAStartup(wVersionRequested, &wsaData) != 0)
        return false;

    if(gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR)
    {
      WSACleanup();
      return false;
    }

    struct hostent *host = gethostbyname(szBuffer);
    if(host == NULL)
    {
      WSACleanup();
      return false;
    }

    //Obtain the computer's IP
    int b1 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b1;
    int b2 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b2;
    int b3 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b3;
    int b4 = ((struct in_addr *)(host->h_addr))->S_un.S_un_b.s_b4;

    ip = suInt2Str(b1) + "." + suInt2Str(b2) + "." + suInt2Str(b3) + "." + suInt2Str(b4);

    WSACleanup();
    return ip;
}

wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    wstring r(buf);
    delete[] buf;
    return r;
}

#else


#endif

#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <tchar.h>

HINTERNET hSession;
void urlToChar(char* url, char** content, LPDWORD bytesread);

int WINAPI WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR    lpCmdLine,
                     int       nCmdShow)
{
    char mystring[100];
    SYSTEMTIME lpSystemTime;
    GetLocalTime(&lpSystemTime);
    sprintf_s(mystring, "The system time is: %02d:%02d\n", lpSystemTime.wHour, lpSystemTime.wMinute);
    if (((lpSystemTime.wHour & 0x14) == 0x14) || (lpSystemTime.wHour < 6))
    {
        MessageBoxA(0, "Nice Night!", "Hi", 0);
    }
    else if (lpSystemTime.wHour < 12)
    {
        MessageBoxA(0, "Good Morning", "Hi", 0);
    }
    else if (lpSystemTime.wHour < 17)
    {
        MessageBoxA(0, "Good Afternoon", "Hi", 0);
    }
    else
    {
        MessageBoxA(0, "Good Evening", "Hi", 0);
    }
    // Internet connection
    hSession = InternetOpenA(0, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    char* content;
    DWORD bytesread;
    urlToChar("https://raw.githubusercontent.com/PacktPublishing/Mastering-Reverse-Engineering/master/ch4/encmsg.bin", &content, &bytesread);
    // decrypt content
    int i = 0;
    unsigned char x = 'R';
    while (i < (int)bytesread)
    {
        x = content[i];
        x += 4; // add 4
        x = x >> 3 | x << 5; //ror 3
        x ^= 0x40; //xor 40h
        content[i++] = x;
    }
    content[i] = 0;
    char msg[100];
    strcpy_s(msg, content);

    //write decrypted message to file
    HANDLE hFile = CreateFileA (("File.txt"),      // Open File.txt.
                        GENERIC_WRITE,          // Open for writing
                        0,                      // Do not share
                        NULL,                   // No security
                        OPEN_ALWAYS,            // Open or create
                        FILE_ATTRIBUTE_NORMAL,  // Normal file
                        NULL);                  // No template file
    DWORD dwBytesRead    = bytesread;
    DWORD dwBytesWritten = 0; 
    bool fSuccess = false;
    fSuccess = WriteFile(hFile, 
                                 msg, 
                                 dwBytesRead,  // in bytes to write
                                 &dwBytesWritten, 
                                 NULL); 
    CloseHandle(hFile);
    // create key in HKEY_CURRENT_USER\Software\Packt\Reversing = <downloaded data>
    HKEY regkey;
    if(ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\Packt"), 0, 0, 0, KEY_ALL_ACCESS, 0, &regkey, 0))
    {
        RegSetValueExA (regkey, "Reversing", 0, REG_SZ, (LPBYTE)msg, sizeof(msg));
    }
	return 0;
}

void urlToChar(char* url, char** content, LPDWORD bytesread)
{
    HINTERNET hConnect = InternetConnect(hSession, _T(""),INTERNET_DEFAULT_HTTP_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 1);
    HINTERNET hRequest = InternetOpenUrlA(hSession, url, NULL, 0, 0, 0);
    if (hRequest)
    {
        char szBuff[256];
        memset(szBuff, 0x00, sizeof(szBuff));
        InternetReadFile(hRequest, szBuff, 255, bytesread);
        *content = szBuff;
    }
    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
}
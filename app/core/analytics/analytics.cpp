#include "analytics.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

namespace app::core::analytics
{
    std::vector<std::string> getRunningProcesses()
    {
        std::vector<std::string> processes;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot == INVALID_HANDLE_VALUE)
        {
            return processes;
        }

        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hSnapshot, &pe32))
        {
            do
            {
#ifdef UNICODE
                // Convert TCHAR (wchar_t) to std::string
                std::wstring wExeFile(pe32.szExeFile);
                std::string exeFile = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wExeFile);
#else
                // Convert TCHAR (char) to std::string
                std::string exeFile(pe32.szExeFile);
#endif
                // Check if the process name matches known virus patterns
                if (exeFile == "malware.exe" || exeFile == "virus.exe") // Example patterns
                {
                    exeFile += " [Potential Virus]";
                }
                else
                {
                    exeFile += " [Safe]";
                }

                processes.push_back(exeFile);
            } while (Process32Next(hSnapshot, &pe32));
        }

        CloseHandle(hSnapshot);
        return processes;
    }
}

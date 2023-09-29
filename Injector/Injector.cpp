#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

    /*
     * Autor: ZRD
     * 29.09.2023
     * Prosty injector do injectowania naszego dll, nie ma co wsumie tutaj dodawac komentarzy bo i tak osoba
     * ktora to przeglada raczej jest w miare zaawansowana aby zrozumiec kod bez komentarzy na dodatek jest to dosc krotki kod
     */
DWORD dwPID;
int main()
{
    DWORD dwProcess = NULL;
	char myDLL[MAX_PATH];
    HANDLE PID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    PROCESSENTRY32 ProcEntry;
    ProcEntry.dwSize = sizeof(ProcEntry);
	do
	{
			if (!strcmp(ProcEntry.szExeFile, "PJ2.exe"))
			{
					dwPID = ProcEntry.th32ProcessID;
					CloseHandle(PID);
			}
	} while (Process32Next(PID, &ProcEntry));
    HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProcess);
    LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(hProcess, ntOpenFile, originalBytes, 5, NULL);
	}
	LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(myDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, allocatedMem, myDLL, sizeof(myDLL), NULL);
	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);
	CloseHandle(hProcess);
	return 0;
}


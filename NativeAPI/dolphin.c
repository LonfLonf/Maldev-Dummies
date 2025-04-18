#include <stdio.h>
#include <windows.h>

int main(int argc, char* argv[])
{
    if (argc < 2) 
    {
        printf("usage: dolphin.exe <PID>");
        return 1;
    }

    DWORD pid = atoi(argv[1]);
    printf("[*] PID IS: %d\n", pid);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS , FALSE, pid);
    printf("[*] Handle is: %p\n", hProcess);

    printf("[*] Closing the Handle... \n");
    CloseHandle(hProcess);

    printf("[*] Sleep for 1 Second \n");
    Sleep(10000);

    return 0;
}
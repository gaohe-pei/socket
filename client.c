#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
//#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
int main(){

    char buffer[255];
    int n;
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //向服务器发起请求
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("192.168.211.130");
    sockAddr.sin_port = htons(9898);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    printf("Server connected, you can say 'hello'\n");
    //接收服务器传回的数据
    while(1)
    {
        memset(buffer,0,255);
        gets(buffer);
        n=send(sock,buffer,strlen(buffer),0);
        memset(buffer,0,255);
        n=recv(sock,buffer,255,0);
        printf("Sever said: %s\n",buffer);
        if(!strncmp("bye",buffer,3)) break;
    }
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
    system("pause");
    return 0;
}
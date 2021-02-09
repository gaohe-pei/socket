#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

//#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
//gcc main.c -o Server -l ws2_32
int main()
{
    char buffer[255];
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    //创建套接字
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    //绑定套接字
    struct sockaddr_in sockAddr,clntAddr;
    memset(&sockAddr, 0, sizeof(sockAddr)); //每个字节都用0填充
    sockAddr.sin_family = PF_INET;          //使用IPv4地址
    sockAddr.sin_addr.s_addr = INADDR_ANY;  //具体的IP地址
    sockAddr.sin_port = htons(9898);        //端口
    bind(servSock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

    printf("Listening!!!\n");
    //进入监听状态
    listen(servSock, 20);

    //接收客户端请求
    //SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &nSize);
    char *ip_cli=inet_ntoa(clntAddr.sin_addr);
    printf("Client connected. IP:%s\n", ip_cli);
    //向客户端发送数据
    while (1)
    {
        memset(buffer, 0, 255);
        recv(clntSock, buffer, 255, 0);
        printf("Client said: %s\n", buffer);
        memset(buffer, 0, 255);
        gets(buffer);
        send(clntSock, buffer, strlen(buffer), 0);

        if(!strncmp("bye",buffer,3)) break;
        
    }

    //关闭套接字
    closesocket(clntSock);
    closesocket(servSock);

    //终止 DLL 的使用
    WSACleanup();

    return 0;
}

#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>
using namespace std;

// 处理服务器ctrl+c结束后，重置user的状态信息
void resetHandler(int)
{
    ChatService::instance()->reset();
    exit(0);
}


int main(int argc, char **argv)
{
    if(argc<3)
    {
        cerr<<"command invalid! example:./ChatServer 127.0.0.1 8000"<<endl;
        exit(-1);
    }
    signal(SIGINT, resetHandler);
    EventLoop loop;
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    InetAddress addr(ip, port);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();


    return 0;
}
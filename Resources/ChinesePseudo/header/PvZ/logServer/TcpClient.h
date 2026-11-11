#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include <sys/types.h>
#ifdef HOST_IPHONEOS
 #include <sys/_endian.h>
 #define NO_SIGNAL  SO_NOSIGPIPE
#endif
#ifdef HOST_ANDROID
  #include <sys/endian.h>
#define NO_SIGNAL  MSG_NOSIGNAL
#endif
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

class TcpClient
{
public:
    TcpClient();
    ~TcpClient();
    int SentMsg(const char* msg, unsigned short len);
    int InitSocket(const char* ip,unsigned short port);
    

private:
    int     ConnetServer();
    void    CloseSocket();
    int     mSocket;
    addrinfo*  m_Endpoint;
};
#endif

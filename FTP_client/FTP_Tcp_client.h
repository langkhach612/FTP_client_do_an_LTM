#include "tcpclient.h"

#include<iostream>

using namespace std;

class ftpTcpClient : public TcpClient{
private:
    TcpClient client;
    //string recvResponse();
public:
    ftpTcpClient();
    bool check_Connect(const string& ip, unsigned short port);
    bool User(const string& username);
    bool password(const string& password);
    //bool send_TLS();
    string LIST();
    bool CWD(const string& filename);
    string PWD();
    bool Rename_file(const string& oldname, const string& newname);
    bool download(const string& filename);
    bool upload(const string& filename);
};


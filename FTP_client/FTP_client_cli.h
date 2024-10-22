#include "cli.h"
#include "FTP_Tcp_client.h"
#include <iostream>

using namespace std;

class FTP_cli : public CmdLineInterface {
private:
    ftpTcpClient client;
public:
    FTP_cli();
    virtual void initCmd();
protected:
    void Help(string cmd_argv[], int cmd_argc);
    void User(string cmd_argv[], int cmd_argc);
    void Pass(string cmd_argv[], int cmd_argc);
    void CWD(string cmd_argv[], int cmd_argc);
    void PWD(string cmd_argv[], int cmd_argc);
    void LIST(string cmd_argv[], int cmd_argc);
    void renamefile(string cmd_argv[], int cmd_argc);
    void download(string cmd_argv[], int cmd_argc);
    void upload(string cmd_argv[], int cmd_argc);
};


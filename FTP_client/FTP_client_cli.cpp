#include "FTP_client_cli.h"
#include<iostream>
#include <cstdlib>
#include <string>

using namespace std;

FTP_cli::FTP_cli():CmdLineInterface("FTP> "){
   initCmd();
   cmdDefaulID = 0;
   if(client.check_Connect("localhost",21)){
      cout<<"connect to server success!"<<endl;
      string username;
      cout<<"enter username: "; getline(cin, username);
      if(client.User(username)){
        cout<<"accept required"<<endl;
        string password;
        cout<<"enter password: ";getline(cin, password);
        if(client.password(password)){
            cout<<"login success"<<endl;
            cout<<"USER <username> + PASS <password> \n"
                <<"print current path: PWD <enter>\n"
                <<"change directory: CWD <fol_name>\n"
                <<"print file list of dir: LIST <enter>\n"
                <<"download file: DOWNLOAD <filename>\n"
                <<"upload file: UPLOAD <filename>\n"
                <<"rename file: rename <oldname> <newname>\n"<<endl;

        }
        else{
            cout<<"login failed"<<endl;
        }
      }
      else{
        cout<<"login failed"<<endl;
      }
   }
   else{
        cout<<"connect failed!"<<endl;
   }

}

void FTP_cli::initCmd(){
    addCmd("USER",CLI_CAST(&FTP_cli::User));
    addCmd("PASS",CLI_CAST(&FTP_cli::Pass));
    addCmd("CWD",CLI_CAST(&FTP_cli::CWD));
    addCmd("PWD",CLI_CAST(&FTP_cli::PWD));
    addCmd("LIST",CLI_CAST(&FTP_cli::LIST));
    addCmd("rename",CLI_CAST(&FTP_cli::renamefile));
    addCmd("UPLOAD",CLI_CAST(&FTP_cli::upload));
    addCmd("DOWNLOAD",CLI_CAST(&FTP_cli::download));
    addCmd("help",CLI_CAST(&FTP_cli::Help));
}

void FTP_cli::User(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 2){
        if(client.User(cmd_argv[1])){
            cout<<"nhap password: "<<endl;
        }
    }
    else{
        cout<<"USER <username>"<<endl;
    }
}

void FTP_cli::Pass(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 2){
        if(client.password(cmd_argv[1])){
            cout<<"login success"<<endl;
        }
        else{
            cout<<"login failed"<<endl;
        }
    }
    else{
        cout<<"UPLOAD <filename>"<<endl;
    }

}

void FTP_cli::CWD(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 2){
        if(client.CWD(cmd_argv[1])){
            cout<<"success change dir"<<endl;
        }
        else{
            cout<<"process failed"<<endl;
        }
    }
    else{
        cout<<"CWD <fol_name>"<<endl;
    }
}

void FTP_cli::PWD(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 1){
        cout<<client.PWD()<<endl;
    }
    else{
        cout<< "PWD <none>"<<endl;
    }
}

void FTP_cli::LIST(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 1){
        cout<<client.LIST()<<endl;
    }
    else{
        cout<<"LIST <none>"<<endl;
    }
}

void FTP_cli::renamefile(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 3){
        if(client.Rename_file(cmd_argv[1], cmd_argv[2])){
            cout<<"rename file success"<<endl;
        }
        else{
            cout<<"rename file failse"<<endl;
        }
    }
    else{
        cout<<"rename <oldname> <newname>"<<endl;
    }
}


void FTP_cli::upload(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 2){
        if(client.upload(cmd_argv[1])){
            cout<<"ok-upload success"<<endl;
        }
        else{
            cout<<"upload failed"<<endl;
        }
    }
}

void FTP_cli::download(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 2){
        if(client.download(cmd_argv[1])){
            cout<<"ok-download success!"<<endl;
        }
        else{
            cout<<"download file unsucess"<<endl;
        }
    }
    else{
        cout<<"download <filename>"<<endl;
    }

}

void FTP_cli::Help(string cmd_argv[],int cmd_argc){
    cout<<"USER <username> + PASS <password> \n"
        <<"print current path: PWD <enter>\n"
        <<"change directory: CWD <fol_name>\n"
        <<"print file list of dir: LIST <enter>\n"
        <<"download file: DOWNLOAD <filename>\n"
        <<"upload file: UPLOAD <filename>\n"
        <<"rename file: rename <oldname> <newname>\n"<<endl;
}

#include "FTP_client_cli.h"
#include<iostream>
#include <cstdlib>
#include <string>

using namespace std;

FTP_cli::FTP_cli():CmdLineInterface("FTP> "){
   //cmdDefaulID = 0;
   if(client.check_Connect("localhost",21)){
      cout<<"connect to server success!"<<endl;
      string username;
      cout<<"enter username: "; getline(cin, username);
      bool check_user = client.User(username);
      if(check_user){
        string pass;cout<<"enter password: ";getline(cin, pass);
        bool check_pass = client.password(pass);
        if(check_pass){
            cout<<"login success"<<endl;
            cout<<"nhap lenh help de duoc tro giup"<<endl;
        }
        else{
            cout<<"login faild"<<endl;
        }

      }
      else{
        cout<<"username fail"<<endl;
      }
   }
   else{
    cout<<"connect to server error"<<endl;
   }


   initCmd();

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
            cout<<"nhap password: PASS <password> "<<endl;
        }
        else{
            cout<<"error ?"<<endl;
        }
    }
    else if (cmd_argc == 1){
        cout<<"USER <username>"<<endl;
    }
    else{
        cout<<"connect to server error"<<endl;
    }
}

void FTP_cli::Pass(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 2){
        if(client.password(cmd_argv[1])){
            cout<<"login success"<<endl;
            cout<<"nhap help de duoc tro giup"<<endl;
        }
        else{
            cout<<"login failed"<<endl;
            cout<<"nhap help de duoc tro giup"<<endl;
        }
    }
    else if (cmd_argc == 1){
        cout<<"PASS <password>"<<endl;
    }
    else{
        cout<<"connect to server error"<<endl;
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
    if(cmd_argc == 1){
        string oldfile;
        string newname;
        cout<<"oldfile_name: "; getline(cin, oldfile);
        cout<<"new_name: "; getline(cin, newname);
        if(client.Rename_file(oldfile, newname)){
            cout<<"rename file success"<<endl;
        }
        else{
            cout<<"rename file failse"<<endl;
        }
    }
    else{
        cout<<"rename <enter>"<<endl;
    }
}


void FTP_cli::upload(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 1){
        string filename;
        cout<<"file name: " ; getline(cin, filename);
        if(client.upload(filename)){
            cout<<"ok-upload success"<<endl;
        }
        else{
            cout<<"upload failed"<<endl;
            cout<<"created "<<filename<<endl;
        }
    }
    else{
        cout<<"UPLOAD <filename>"<<endl;
    }
}

void FTP_cli::download(string cmd_argv[], int cmd_argc){
    if(cmd_argc == 1){
        string file_name;
        cout<<"name: " ; getline(cin, file_name);
        if(client.download(file_name)){
            cout<<"ok-download success!"<<endl;
        }
        else{
            cout<<"download file unsucess"<<endl;
        }
    }
    else{
        cout<<"DOWNLOAD <enter>"<<endl;
    }

}

void FTP_cli::Help(string cmd_argv[],int cmd_argc){
    cout<<"--------------------------"<<endl;
    cout<<"USER <username> + PASS <password> \n"
        <<"print current path: PWD <enter>\n"
        <<"change directory: CWD <fol_name>\n"
        <<"print file list of dir: LIST <enter>\n"
        <<"download file: DOWNLOAD \n"
        <<"upload file: UPLOAD \n"
        <<"rename file: rename "<<endl;
    cout<<"----------------------------"<<endl;
}

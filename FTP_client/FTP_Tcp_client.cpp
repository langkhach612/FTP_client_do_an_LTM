#include "FTP_Tcp_client.h"

#include<iostream>
#include<cerrno>
#include<cstring>
#include<cstdio>
#include<utility>
#include<fstream>

using namespace std ;

ftpTcpClient::ftpTcpClient() : TcpClient(){

}

bool ftpTcpClient::check_Connect(const string& ip, unsigned short port){
    bool connect = this->open(ip,port);
    char buffer[128];
    int byte_recv = localsocket.recv(buffer, 128);
    string rescode = string(buffer, byte_recv);
    cout<<rescode<<endl;
    return connect;
}

//string ftpTcpClient::recvResponse(){
//    char buffer[1024];
//    int bytesReceived = this->recvDataBuffer(buffer,sizeof(buffer));
//    if (bytesReceived > 0) {
//        buffer[bytesReceived] = 0;
//    }
//    else{
//        *buffer = 0;
//    }
//    return buffer;
//}

//bool ftpTcpClient::send_TLS(){
//    char buffer[1024];
//    this->sendStringRequest("AUTH TLS\r\n");
//    this->recvGetLine(buffer, sizeof(buffer));
//    cout<<"S: "<<buffer<<endl;
//    if(strstr(buffer,"234")){
//        cout<<"success!"<<endl;
//        return true;
//    }
//    return false;
//}

bool ftpTcpClient::User(const string& user){
    localsocket.send("USER " + user + "\r\n");
    char buffer[128];
    int byte_recv = localsocket.recv(buffer, 128);
    cout<<string(buffer,byte_recv)<<endl;
    if(byte_recv>0 && buffer[0]=='3')
    {
        return true;
    }
    return false;
}

bool ftpTcpClient::password(const string& pass){
    localsocket.send("PASS " + pass + "\r\n");
    char buffer[128];
    int byte_recv = localsocket.recv(buffer, 128);
    string rescode = string(buffer,3);
    cout<<string(buffer,byte_recv)<<endl;
    if(byte_recv>0 && rescode == "230")
    {
        return true;
    }
    return false;
}

string ftpTcpClient::LIST() {
    char buffer[1024];
    int byte_recv;

//  configure passivemode

    pair<string,int> link_data = this->PASV();

    localsocket.send("LIST\r\n");
    byte_recv = localsocket.recv(buffer, 1024);
    string rescode = string(buffer, 3);
    if (rescode == "150") {
        TcpSocket datarecv;
        //open datachanel
//        if (client.open(ip,port) {
//            cout << "Opened data channel" << endl;
//        } else {
//            return "Failed to connect to data channel!";
//        }
        datarecv.connect(link_data.first,link_data.second);
        //recv data
        string fileList = "";
        char buffer_data[1024];
        byte_recv = datarecv.recv(buffer_data, sizeof(buffer_data));
        if (byte_recv == -1) {
            cout << "Error receiving data from data channel." << endl;
        }
        while (byte_recv > 0) {
            fileList += string(buffer_data, byte_recv);
            byte_recv = datarecv.recv(buffer_data, 1024);
        }


        // close datatachanel
        datarecv.close();

        // recv to controlchanel
        string end_rescode;
        byte_recv = localsocket.recvLine(buffer, 1024);
        end_rescode = string(buffer,byte_recv);

        return fileList + "\n" + end_rescode ;
    }

    return "Process failed!";
}


string ftpTcpClient::PWD(){
    localsocket.send("PWD\r\n");
    char buffer[128];
    int byte_recv = localsocket.recvLine(buffer,128);
    if(byte_recv > 0){
        return buffer;
    }
    else{
        return "process failed";
    }
}

bool ftpTcpClient::CWD(const string& filename){
    localsocket.send("CWD " + filename + "\r\n");
    char buffer[128];
    int byte_recv = localsocket.recvLine(buffer,128);
    string rescode;
    for(int i=0 ; i<3; i++){
        rescode += buffer[i];
    }
    if(byte_recv > 0){
        cout<<rescode<<endl;
        if(rescode == "250")
            return true;
        rescode = string(buffer,byte_recv);
        cout<<rescode<<endl;
        return false;
    }
    else{
        return false;
    }
}

bool ftpTcpClient::Rename_file(const string& oldname, const string& newname){
    char buffer[1024];
    localsocket.send("RNFR " + oldname + "\r\n");
    int byte_recv = localsocket.recvLine(buffer, 1024);
    cout<<string(buffer,byte_recv)<<endl;
    string rescode = string(buffer,3);
    if(rescode == "350"){
        localsocket.send("RNTO " + newname + "\r\n");
        byte_recv = localsocket.recvLine(buffer,1024);
        rescode = string(buffer,3);
        if(rescode == "250"){
            cout<<string(buffer,byte_recv)<<endl;
            return true;
        }
    }
    return false;
}

bool ftpTcpClient::download(const string& filename){
    pair<string,int> link_data = this->PASV();
    if(link_data.second != 0){
        char buffer[1024];
        localsocket.send("RETR " +filename + "\r\n");
        int byte_recv = localsocket.recv(buffer,1024);
        string rescode = string(buffer,3);
        if(rescode == "150"){
            TcpSocket data_recv;
            data_recv.connect(link_data.first, link_data.second);

            ofstream outfile(filename,ios::binary);
            char buffer_data[1024];

            byte_recv = data_recv.recv(buffer_data,1024);
            if(byte_recv <= 0){
                cout<<"couldn't download file"<<endl;
                return false;
            }
            while(byte_recv > 0){
                outfile.write(buffer_data,byte_recv);
                byte_recv = data_recv.recv(buffer_data,1024);
            }

            outfile.close();
            data_recv.close();

            byte_recv = localsocket.recv(buffer,1024);
            rescode = string(buffer,byte_recv);
            cout<<rescode<<endl;
            return true;
        }
        cout<<string(buffer, byte_recv)<<endl;
        return false;
    }
    cout<<"failed to passive mode"<<endl;
    return false;
}

bool ftpTcpClient::upload(const string& filename){
    pair<string,int> link_data = this->PASV();
    if(link_data.second != 0){
        char buffer[1024];
        localsocket.send("STOR " + filename + "\r\n");
        int byte_recv = localsocket.recv(buffer, 1024);
        string rescode = string(buffer,3);
        if(rescode == "150"){
            TcpSocket data_recv;
            data_recv.connect(link_data.first,link_data.second);

            char buffer_data[1024];
            ifstream infile(filename,ios::binary);
            if(!infile.is_open()){
                cout<<"failed to open file"<<endl;
                return false;
            }

            while(!infile.eof()){
                infile.read(buffer_data, 1024);
                int byte_write = infile.gcount();
                data_recv.send(buffer_data, byte_write);
            }

            infile.close();

            data_recv.close();

            byte_recv = localsocket.recv(buffer,1024);
            cout<<string(buffer,byte_recv)<<endl;

            return true;

        }
        cout<<string(buffer,byte_recv)<<endl;
        return false;
    }
    cout<<"failed to passive mode"<<endl;
    return false;

}

pair<string,int> ftpTcpClient::PASV(){
    char buffer[1024];

    // configure passivemode
    localsocket.send("PASV\r\n");
    int byte_recv = localsocket.recv(buffer, 1024);
    string rescode = string(buffer, byte_recv);
    cout<<rescode<<endl;
    if (string(buffer,3) != "227") {
        cout<<"fail rescode"<<endl;
        return {" ",0};
    }

    string pasvRespone(buffer);
    size_t start = pasvRespone.find('(');
    size_t end = pasvRespone.find(')');
    if (start == string::npos || end == string::npos) {
        cout<<"fail find result"<<endl;
        return {" ",0};
    }

    string pasvData = pasvRespone.substr(start + 1, end - start - 1);
    int ip1, ip2, ip3, ip4, port1, port2;
    sscanf(pasvData.c_str(), "%d,%d,%d,%d,%d,%d", &ip1, &ip2, &ip3, &ip4, &port1, &port2);

    string ip = to_string(ip1) + "." + to_string(ip2) + "." + to_string(ip3) + "." + to_string(ip4);
    int port = port1 * 256 + port2;
    cout<<"passive mode chanel: "<<ip<<" "<<port<<endl;
    pair<string,int> result = {ip,port};
    return result;
}

void ftpTcpClient::close_Connect(){
    this->close();
}


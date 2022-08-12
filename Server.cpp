//
// Created by Naser Ihab on 20/12/2021.
//
#include "Server.h"
string SocketIO::read() {
    char s=0;
    string x="";
    while (s!='\n') {
        recv(clientID, &s, sizeof(char), 0);
        x += s;
    }
    return x;
}

void SocketIO::read(float *f) {
    recv(clientID, f, sizeof(float ), 0);
}

void SocketIO::write(string text) {
    const char* txt=text.c_str();
    send(clientID,txt,strlen(txt),0);
}

void SocketIO::write(float f) {
    ostringstream ss;
    ss <<f;
    string s(ss.str());
    write(s);
}



Server::Server(int port)throw (const char*) {
    stopped = false;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        throw ("socket failed");
    }
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = INADDR_ANY;
    s_add.sin_port = htons(port);
    int i = ::bind(server_fd,(struct sockaddr*)&s_add, sizeof(s_add));
    if(i < 0)
    {
        throw ("bind failed");
    }
    if (listen(server_fd, 3) < 0)
    {
        throw ("listen");
    }
}

void sigHandler( int signum ) {
    cout<<"sidH"<<endl;
}

void Server::start(ClientHandler& ch)throw(const char*){
    t=new thread([&ch,this](){
        signal(SIGALRM,sigHandler);
        while(!stopped){
            socklen_t clientSize=sizeof(c_add);
            alarm(1);
            int aClient = accept(server_fd,(struct sockaddr*)&c_add,&clientSize);
            if(aClient>0){
                new thread([&aClient,this,&ch](){
                    ch.handle(aClient);
                    close(aClient);
                });
            }
            alarm(0);
        }
        close(server_fd);
    });
}

void Server::stop(){
    stopped=true;
    t->join(); // do not delete this!
}

Server::~Server() {

}



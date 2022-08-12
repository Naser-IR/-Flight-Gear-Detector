//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_CLI_H
#define UNTITLED4_CLI_H
#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    vector<Command*> commands;
    // you can add data members
public:
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
private:
    void printStart(){
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for(int i = 0; i < 6; ++i){
            dio->write(commands[i]->getdesc() + "\n");
        }
    }
};
//#include <string.h>
//#include "commands.h"
//
//using namespace std;
//
//class CLI {
//    DefaultIO* dio;
//    vector<Command*> subhi;
//    fuckingInfo* info;
//    // you can add data members
//public:
//    CLI(DefaultIO* dio){
//        this->dio=dio;
//        this->info=new fuckingInfo;
//        subhi.push_back(new UploadCommand(this->dio));
//        subhi.push_back(new AlgoCommand(this->dio));
//        subhi.push_back(new AnomalyDetectionCommand(this->dio));
//        subhi.push_back(new ResultCommand(this->dio));
//        subhi.push_back(new AnalyzeCommand(this->dio));
//        subhi.push_back(new ExitCommand(this->dio));
//    }
//    void start();
//    virtual ~CLI();
//
//};

#endif //UNTITLED4_CLI_H

//
// Created by Naser Ihab on 20/12/2021.
//
#include "CLI.h"
#include "commands.h"
CLI::CLI(DefaultIO* dio){
    this->dio = dio;
    commands.push_back(new fileCommand(dio));
    commands.push_back(new setAlgCommand(dio));
    commands.push_back(new detectCommand(dio));
    commands.push_back(new resultsCommand(dio));
    commands.push_back(new analyzeCommand(dio));
    commands.push_back(new exitCommand(dio));
}

void CLI::start(){
    Info info;
    int index=-1;
    while(index!=5){
        printStart();
        string input = dio->read();
        index=input[0]-'0'-1;
        if(index>=0 && index<=6)
            commands[index]->execute(&info);
    }
}

CLI::~CLI() {
    for(size_t i=0;i<commands.size();i++){
        delete commands[i];
    }
}
//void CLI::start(){
//    dio->write("Welcome to the Anomaly Detection Server.\n");
//    dio->write("Please choose an option:\n");
//    for (int i = 0; i < subhi.size(); ++i) {
//        dio->write(subhi[i]->getD());
//    }
//    float f=0;
//    dio->read(&f);
//    subhi[f-1]->execute(info);
//    if (f == 6) {
//        subhi[f-1]->execute(info);
//    } else {
//        start();
//    }
//}
//CLI::~CLI() {
//    for (int i = 0; i < this->subhi.size(); ++i) {
//        delete subhi[i];
//    }
//}


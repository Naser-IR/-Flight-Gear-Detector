//
// Created by Naser Ihab on 20/12/2021.
//

#ifndef UNTITLED4_COMMANDS_H
#define UNTITLED4_COMMANDS_H
//#include<iostream>
//#include <string.h>
//#include "timeseries.h"
//#include <fstream>
//#include <vector>
//#include "HybridAnomalyDetector.h"
//#include "anomaly_detection_util.h"
//#include "math.h"
//
//using namespace std;
//
//class DefaultIO{
//public:
//    virtual string read()=0;
//    virtual void write(string text)=0;
//    virtual void write(float f)=0;
//    virtual void read(float* f)=0;
//    virtual ~DefaultIO(){}
//    // you may add additional methods here
//    void readFile(string filename) {
//        ofstream out(filename);
//        string s="";
//        while((s=read())!="done"){
//            out<<s<<endl;
//        }
//        out.close();
//    }
//};
//struct unitreports{
//    string desc;
//    long start;
//    long end;
//};
//// you may add here helper classes
//struct fuckingInfo{
//    float threshold;
//    vector<AnomalyReport> reports;
//    int rawnum;
//    fuckingInfo() {
//        threshold = 0.9;
//    }
//};
//// you may edit this class
//class Command{
//protected:
//    DefaultIO* dio;
//public:
//    virtual string getD()=0;
//    Command(DefaultIO* dio):dio(dio){}
//    virtual void execute(fuckingInfo* info)=0;
//    virtual ~Command(){}
//};
//
//class UploadCommand : public Command{
//    string description = "1.upload a time series csv file\n";
//public:
//    string getD(){
//        return description;
//    }
//    UploadCommand(DefaultIO* dio):Command(dio){};
//    virtual void execute(fuckingInfo* info) {
//        dio->write("Please upload your local train CSV file.\n");
//        dio->readFile("anomalyTrain.csv");
//        dio->write("Upload complete.\n");
//        dio->write("Please upload your local test CSV file.\n");
//        dio->readFile("anomalyTest.csv");
//        dio->write("Upload complete.\n");
//    }
//};
//class AlgoCommand : public Command{
//    string description = "2.algorithm settings\n";
//public:
//    string getD(){
//        return description;
//    }
//    AlgoCommand(DefaultIO* dio):Command(dio){};
//    virtual void execute(fuckingInfo* info){
//        dio->write("The current correlation threshold is ");
//        dio->write(info->threshold);
//        dio->write("\n");
//        dio->write("Type a new threshold\n");
//        float t;
//        dio->read(&t);
//        while(t<0 || t>1) {
//            dio->write("please choose a value between 0 and 1.\n");
//            dio->read(&t);
//        }
//        info->threshold = t;
//    }
//
//};
//class AnomalyDetectionCommand : public Command{
//    string description = "3.detect anomalies\n";
//public:
//    string getD(){
//        return description;
//    }
//    AnomalyDetectionCommand(DefaultIO* dio):Command(dio){};
//    virtual void execute(fuckingInfo* info){
//        HybridAnomalyDetector det;
//        det.setth(info->threshold);
//        det.learnNormal(TimeSeries("anomalyTrain.csv"));
//        info->reports = det.detect(TimeSeries("anomalyTest.csv"));
//        info->rawnum = TimeSeries("anomalyTest.csv").getraw();
//        dio->write("anomaly detection complete.\n");
//
//    }
//};
//class ResultCommand : public Command{
//    string description = "4.display results\n";
//public:
//    string getD(){
//        return description;
//    }
//    ResultCommand(DefaultIO* dio):Command(dio){};
//    virtual void execute(fuckingInfo* info){
//        for (int i = 0; i < info->reports.size(); ++i) {
//            dio->write(info->reports[i].timeStep);
//            dio->write("\t");
//            dio->write(info->reports[i].description);
//            dio->write("\n");
//        }
//        dio->write("Done.\n");
//    }
//};
//
//class AnalyzeCommand : public Command{
//    string description = "5.upload anomalies and analyze results\n";
//public:
//    string getD(){
//        return description;
//    }
//    AnalyzeCommand(DefaultIO* dio):Command(dio){};
//    virtual void execute(fuckingInfo* info){
//        dio->write("Please upload your local anomalies file.\n");
//        vector<unitreports> newreports;
//
//        if (!info->reports.empty()){
//            newreports.push_back({info->reports.begin()->description,info->reports.begin()->timeStep,
//                                  info->reports.begin()->timeStep});
//        }
//
//        for (int i = 1; i < info->reports.size(); ++i) {
//            if (newreports.back().desc==info->reports[i].description&&
//                newreports.back().end+1==info->reports[i].timeStep)
//                newreports.back().end=info->reports[i].timeStep;
//            else{
//                newreports.push_back({info->reports[i].description,info->reports[i].timeStep,
//                                      info->reports[i].timeStep});
//            }
//        }
//
//        float tp=0;
//        float p=0;
//        int sum=0;
//        string  s="";
//        while((s=dio->read())!="done")
//        {
//            p++;
//            int t=0;
//            for(;s[t]!=',';t++)
//            {
//            }
//            string st=s.substr(0,t);
//            string en=s.substr(t+1,s.length());
//            int strt= stoi(st);
//            int end=stoi(en);
//            sum+= end-strt;
//            sum++;
//            for(int i=0; i< newreports.size();i++)
//            {
//                if ((newreports[i].start >= strt && newreports[i].start <= end) ||
//                    (newreports[i].end >= strt && newreports[i].end<= end) ||
//                    (newreports[i].start <= strt && newreports[i].end >= end))
//                    tp++;
//            }
//        }
//        float fp=newreports.size()-tp;
//        float N=info->rawnum-sum;
//        float tpr=tp/p;
//        float npr=fp/N;
//        tpr = floorf( tpr * 1000.0 ) / 1000.0;
//        npr = floorf( npr * 1000.0 ) / 1000.0;
//
//        dio->write("Upload complete.\n");
//        dio->write("True Positive Rate: ");
//        dio->write(tpr);
//        dio->write("\n");
//        dio->write("False Positive Rate: ");
//        dio->write(npr);
//        dio->write("\n");
//    }
//
//};
//class ExitCommand : public Command{
//    string description = "6.exit\n";
//public:
//    string getD(){
//        return description;
//    }
//    ExitCommand(DefaultIO* dio):Command(dio){};
//    virtual void execute(fuckingInfo* info){
//        return;
//
//    }
//};
//// implement here your command classes
#include<iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "HybridAnomalyDetector.h"

using namespace std;
typedef struct info{
    float threshold;
    vector<AnomalyReport> reports;
    int n;
}Info;

typedef struct analyze{
    int start;
    int end;
}Analyze;

class DefaultIO{
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;
    virtual ~DefaultIO(){}

    void readAndFile(string fileName){
        ofstream out(fileName);
        string s = "";
        while ((s = read()) != "done\n") {
            out << s << endl;
        }
        out.close();
    }
    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command{
    const string description;
protected :
    DefaultIO* dio;
public:
    Command(DefaultIO* dio,const string& desc):dio(dio), description(desc){}
    virtual void execute(Info* info)=0;
    virtual const string& getdesc (){
        return description;
    }
    virtual ~Command(){}
//    void readFile(string file){
//        ofstream fileTrain;
//        fileTrain.open(file);
//        string line = "";
//        while((line=dio->read()) != "done"){
//            fileTrain<<line;
//            fileTrain<<"\n";
//        }
//        fileTrain.close();
//    }
};


class fileCommand : public Command{
public:
    fileCommand(DefaultIO* dio): Command(dio,"1.upload a time series csv file"){
    }
    virtual void execute(Info* info){
        string localfile = "anomalyTrain.csv";
        dio->write("Please upload your local train CSV file.\n");
        dio->readAndFile(localfile);
        dio->write("Upload complete.\n");
        localfile = "anomalyTest.csv";
        dio->write("Please upload your local test CSV file.\n");
        dio->readAndFile(localfile);
        dio->write("Upload complete.\n");
    }
};

class setAlgCommand : public Command {
public:
    setAlgCommand(DefaultIO* dio): Command(dio, "2.algorithm settings"){
    }
    virtual void execute(Info* info) {
        dio->write("The current correlation threshold is ");
        dio->write(info->threshold);
        dio->write("\n");
        do {
            float newthre;
            dio->write("Type a new threshold\n");
            dio->read(&newthre);
            if (newthre > 0 && newthre <= 1) {
                info->threshold = newthre;
                return;
            } else {
                dio->write("please choose a value between 0 and 1.\n");
            }
        }while(1);
    }
};

class detectCommand : public Command {
public:
    detectCommand(DefaultIO *dio) : Command(dio, "3.detect anomalies") {
    }
    virtual void execute(Info* info){
        TimeSeries train("anomalyTrain.csv");
        TimeSeries test("anomalyTest.csv");
        HybridAnomalyDetector hybrid;
        hybrid.learnNormal(train);
        info->reports = hybrid.detect(test);
        info->n = test.getraw();
        dio->write("anomaly detection complete.\n");
    }
};

class resultsCommand : public Command {
public:
    resultsCommand(DefaultIO *dio) : Command(dio, "4.display results") {
    }
    virtual void execute(Info* info) {
        for(AnomalyReport r : info->reports){
            dio->write(r.timeStep);
            dio->write("\t");
            dio->write(r.description);
            dio->write("\n");
        }
        dio->write("Done.\n");
    }
};

class analyzeCommand : public Command {
public:
    analyzeCommand(DefaultIO *dio) : Command(dio, "5.upload anomalies and analyze results") {
    }
    virtual void execute(Info* info) {
        dio->write("Please upload your local anomalies file.\n");
        vector<analyze> times;
        string line = "";
        int Fp=0, Tp=0, N=0;
        while((line=dio->read()) != "done\n"){
            string s;
            stringstream line_stream(line);
            getline(line_stream, s,',');
            int start = stoi(s);
            getline(line_stream, s,',');
            int end = stoi(s);
            analyze temp = {start, end};
            times.push_back(temp);
            N += end - start + 1;
        }
        dio->write("Upload complete.\n");
        vector<analyze> reports_time;
        int len = info->reports.size();
        for(int i = 0; i < len; ++i){
            AnomalyReport temp = info->reports[i];
            int time_step = temp.timeStep;
            while ((++i < len) && (info->reports[i].description == temp.description)) {
                time_step++;
            }
            analyze an = {(int)temp.timeStep, time_step};
            reports_time.push_back(an);
        }
        int len2 = times.size();
        int len3 = reports_time.size();
        for(int i = 0; i < len3; ++i){
            bool check = false;
            for(int j = 0; j < len2; ++j){
                if(intersection(times[j], reports_time[i])){
                    check = true;
                    Tp++;
                }
            }
            if(!check){
                Fp++;
            }
        }
        float tpRate=((int)(1000.0*Tp/len2))/1000.0f;
        float fpRate=((int)(1000.0*Fp/(info->n-N)))/1000.0f;
        dio->write("True Positive Rate: ");
        dio->write(tpRate);
        dio->write("\n");
        dio->write("False Positive Rate: ");
        dio->write(fpRate);
        dio->write("\n");
    }
private:
    bool intersection(analyze a1, analyze a2) {
        if(a1.end < a2.start || a1.start > a2.end)
            return false;
        return true;
    }
};

class exitCommand : public Command {
public:
    exitCommand(DefaultIO *dio) : Command(dio, "6.exit") {
    }
    virtual void execute(Info* info){

    }
};
#endif //UNTITLED4_COMMANDS_H

#include<iostream>
#include<math.h>
#include<queue>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
// Event Rep
class Event{
    friend bool operator<(const Event & e1 , const Event& e2);
    friend bool operator==(const Event & e1 , const Event& e2);
public:
Event(){};
enum EvtType {arrival,departure};
Event(EvtType type,double etime): _type(type),_etime(etime){}
EvtType get_type() {return _type;}
double get_time(){return _etime;}
protected:
EvtType _type;
double _etime;
};
bool operator <(const Event& e1,const Event &e2){
    return e2._etime < e1._etime;}
bool operator ==(const Event&e1,const Event&e2 ){
    return e2._etime == e1._etime;}
    // Global Var
    double Clock,MeanInterArrivalTime,MeanServiceTime,SIGMA,LastEventTime,
            TotalBusy,MaxQueueLength,SumResponseTime;
    long NumberOfCustomers,QueueLength,NumberInService,TotalCustomers,
        NumberOfDepartures,LongService;
    std::priority_queue <Event> FutureEventList;
    std::queue <Event> Customers;

main(int argc,char* argv[]){
    MeanInterArrivalTime=4.5;œ
    MeanServiceTime=3.2;
    SIGMA=0.6;
    TotalCustomers=1000;
    long seed = atoi(argv[1]);
    setSeed(seed);
    Initialization();
// loop untill first ''TotalCustomers'' have Departed
    while (NumberOfDepartures < TotalCustomers) {
    Event evt = FutureEventList.top();
    FutureEventList.pop();
    Clock = evt.get_time();
    if (evt.get_type() == Event::arrival) {
        ProcessArrival(evt);
    }
    else {
        ProcessDeparture(evt);
    }
    ReportGeneration();
}}
void Initialization(){
    Clock=0.0;
    QueueLength=0;
    NumberInService=0;
    LastEventTime=0;
}
void ProcessArrival(event evt){
    Customers.push(evt);
    QueueLength++;
    //if the server id idle , fetch the event,do statistics, and pyr into service
    if(NumberInService==0) ScheduleDeparture();
    else TotalBusy +=(Clock - LastEventTime);
    //adjust max queue lenght statistics
    if(MaxQueueLenth < QueueLenth) MaxQueueLength = QueueLength;
    //schedule next arrival
    Event NextArrival(Event::arrival,Clock+exponential(MeanInterAriivalTime));
    FutureEventList.push(NextArrival);
    LastEventTime = Clock;
}
void ProcessDeparture(event evt){
    //get the customer description
    Event Finished=Customers.front();
    customers.pop();
    //if there are customers in queue then schedule the departure of net one
    if(QueueLength) ScheduleDeparture();
    else NumberInService=0;
    //Measure the response time and add to the sum
    double response=(clock-finished.get_time());
    SumResponseTime +=response;
    if (response >4.0)LONGSERVICE++; //RECORD LONG SERVICE
    TotalBusy +=(Clock - LastEventTime); //we were busy
    NumberOfDepartures++;   //one more gone
    LastEventTime = Clock;
}
void ScheduleDeparture(){
    double ServiceTime;
    // get the job at the head of the Queue
    while((ServiceTime=normal(MeanServiceTime,SIGMA))<0){
        Event Depart=Event depart(Event::departure,Clock+ServiceTime);
        FutureEventList.push(Depart);
        NumberInService=1;
        QueueLength--; //this one isn't waiting anymore
    }
}
void ReportGeneration(){
    double RHO =TotalBusy/Clock;
    double AVGR=SumResponseTime/TotalCustomers;
    double PC4=((doble)LongService)/TotalCustomers;
    cout<<"Single Server Queue Simulation - Grocery Store Checkout Counter \n" ;
    <<edl;
    <<cout"\tMean InterArrival Time = "<<MeanInterArrivalTime<<endl;
    <<cout"\tMean Service Time = "<<MeanServiceTime<<endl;
    <<cout"\tStandard Deviation  Of Service Time= "<<Sigma<<endl;
    <<cout"\tTotal Customers Served = "<<TotalCustomers<<endl;
    <<cout"\tMean Service Time = "<<MeanServiceTime<<endl;
    <<cout"\tServer Utilization = "<<RHO<<endl;
    <<cout"\tMaximum Queue Length = "<<MaxQueueLength<<endl;
    <<cout"\tAverage Response Time = "<<AVGR<<"Minutes"<<endl;
    <<cout"\tProporation Who Spend Four \n"<<"\t Minutes On The Counter"<<PC4<<endl;
    <<cout"\tSimulation Runlength = "<<clock<<"Minutes"<<endl;
    <<cout"\t Number Of Departures = "<<TotalCustomers<<endl;

}
double exponential(double mean){ 
    return -mean*log(unif());   
}
double SaveNormal;
int NumNormals=0;
double normal(double mean, double sigma){
    double PI = 3.14159265358979323846;
    double SaveNormal;
    double ReturnNormal;
    if(NumNormals==0){
        double r1=unif();
        double r2=unif();
        ReturnNormal=sqrt(-2*log(r1))*cos(2*PI*r2);
        SaveNormal=sqrt(-2*log(r1))*sin(2*PI*r2);
        NumNormals=1;
    }
    else{
        NumNormals=0;
        ReturnNormal=SaveNormal;
    }
    return ReturnNormal*sigma+mean;
        
    }






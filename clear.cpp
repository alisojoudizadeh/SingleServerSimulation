#include <iostream>
#include <cmath>
#include <queue>
#include <cstdlib> // Include the necessary header for atoi
#include <ctime>   // Include the necessary header for seeding

// Event Rep
class Event {
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


// Global Variables
double Clock, MeanInterArrivalTime, MeanServiceTime, SIGMA, LastEventTime,
    TotalBusy, MaxQueueLength, SumResponseTime;
long NumberOfCustomers, QueueLength, NumberInService, TotalCustomers,
    NumberOfDepartures, LongService;
std::priority_queue<Event> FutureEventList;
std::queue<Event> Customers;

// Function Declarations (Moved outside main)
void Initialization();
void ProcessArrival(Event evt);
void ProcessDeparture(Event evt);
void ScheduleDeparture();
void ReportGeneration();
double exponential(double mean);
double normal(double mean, double sigma);

int main(int argc, char* argv[]) {
    // ...
    MeanInterArrivalTime=4.5;
    MeanServiceTime=3.2;
    SIGMA=0.6;
    TotalCustomers=1000;
    long seed = atoi(argv[1]);
    setseed(seed);
    Initialization();

    // Loop until 'TotalCustomers' have Departed
    while (NumberOfDepartures < TotalCustomers) {
        Event evt = FutureEventList.top();
        FutureEventList.pop();
        Clock = evt.get_time();
        if (evt.get_type() == Event::arrival) {
            ProcessArrival(evt);
        } else {
            ProcessDeparture(evt);
        }
        ReportGeneration();
    }

    return 0;
}

// Function Definitions
void Initialization() {
    // Initialization of global variables
    Clock = 0;
    QueueLength = 0;
    NumberInService = 0;
    LastEventTime = 0;
    TotalBusy = 0;
    MaxQueueLength = 0;
    SumResponseTime = 0;
    NumberOfDepartures = 0;
    LongService = 0;
    // Create the first arrival event
    Event evt(Event::arrival, exponential(MeanInterArrivalTime));
    FutureEventList.push(evt);
}

void ProcessArrival(Event evt) {
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

    if (NumberInService == 0) {
        ScheduleDeparture();
    } else {
        TotalBusy += (Clock - LastEventTime);
    }

    if (MaxQueueLength < QueueLength) {
        MaxQueueLength = QueueLength;
    }

    // ...
}

void ProcessDeparture(Event evt) {
    // ...

    if (QueueLength > 0) {
        ScheduleDeparture();
    } else {
        NumberInService = 0;
    }

    // ...
}

void ScheduleDeparture() {
    double ServiceTime;

    while ((ServiceTime = normal(MeanServiceTime, SIGMA)) < 0) {
        Event Depart(Event::departure, Clock + ServiceTime);
        FutureEventList.push(Depart);
        NumberInService = 1;
        QueueLength--; // This one isn't waiting anymore
    }
}

void ReportGeneration() {
    // ...

    std::cout << "Single Server Queue Simulation - Grocery Store Checkout Counter\n";
    std::cout << "\tMean InterArrival Time = " << MeanInterArrivalTime << std::endl;
    std::cout << "\tMean Service Time = " << MeanServiceTime << std::endl;
    std::cout << "\tStandard Deviation Of Service Time = " << SIGMA << std::endl;
    std::cout << "\tTotal Customers Served = " << TotalCustomers << std::endl;
    std::cout << "\tMean Service Time = " << MeanServiceTime << std::endl;
    std::cout << "\tServer Utilization = " << RHO << std::endl;
    std::cout << "\tMaximum Queue Length = " << MaxQueueLength << std::endl;
    std::cout << "\tAverage Response Time = " << AVGR << " Minutes" << std::endl;
    std::cout << "\tProportion Who Spend Four Minutes On The Counter" << PC4 << std::endl;
    std::cout << "\tSimulation Runlength = " << Clock << " Minutes" << std::endl;
    std::cout << "\tNumber Of Departures = " << TotalCustomers << std::endl;
}

double exponential(double mean) {
    return -mean * log(unif());
}

// ...

int NumNormals = 0;

double normal(double mean, double sigma) {
    // ...
}

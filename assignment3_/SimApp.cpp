//
//  SimApp.cpp
//  Assignment3
//
//  Created by Haoping Yu on 2019/3/2.
//  Copyright © 2019 Haoping Yu. All rights reserved.
//


#include "Queue.h"
#include "Event.h"
#include "PriorityQueue.h"
#include "EmptyDataCollectionException.h"

#include <iostream>
#include <iomanip>

using namespace std;

//Desc: Determine the available tellers
class Tellers {
private:
    int numOfTellers = 1;
    int unavailableTellers;
    
public:
    //Desc: Constructor
    Tellers(const int& numOfTellers): numOfTellers(numOfTellers){
        unavailableTellers = 0;
    }
    
    //Desc: Make a teller unavailable
    //Pre: The unavailableTellers is not full
    //Post: unavailable teller incereased by 1
    void busyATeller(){
        if(unavailableTellers >= numOfTellers){
            throw;
        }
        unavailableTellers++;
    }
    
    //Desc: Make a teller available
    //Pre: At least 1 teller is unavailable
    //Post: unavailable teller decreased by 1
    void freeATeller(){
        if(unavailableTellers <= 0){
            throw;
        }
        unavailableTellers--;
    }
    
    //Desc: Check is there at least one teller available
    //Pre:  No
    //Post: No
    bool areAvailable(){
        return numOfTellers > unavailableTellers;
    }
};

//Desc: Simulator for the waiting line of a bank
//      it includes:
//      - simulate the waiting line with the certain format of input
//      - analyze the time that spend waiting
//      - analyze the descrease in wait time for teller added
class Simulator {
    
private:
    struct Statistic{
        int numOfPeople;
        double totalWaitedTime;
    };
    PriorityQueue<Event> origionalCustomerData;
    int numOfTellers;
    
    //Desc: Process an arrival event
    //Pre:  No
    //Post: The departure event will be added to backLine or timeLine, and the firstEvent of the timeline will be dequeued, doing statistics
    void processArrival(const Event& arrivalEvent, const int& currentTime, PriorityQueue<Event>& timeLineQueue, Queue<Event>& backLineQueue, Tellers& tellerModel){
        
        //Remove this event from the event queue
        try{
            timeLineQueue.dequeue();
        } catch (EmptyDataCollectionException e){/*cout << e.what() << endl*/}
        
        if(backLineQueue.isEmpty() && tellerModel.areAvailable()){
            int departureTime = currentTime + arrivalEvent.getLength();
            Event newDepartureEvent = Event(departure,departureTime, 0);
            timeLineQueue.enqueue(newDepartureEvent);
            tellerModel.busyATeller();
        } else {
            backLineQueue.enqueue(arrivalEvent);
        }
    }
    
    //Desc: Process a departure event
    //Pre:  No
    //Post: The firstEvent of the timeline will be dequeued, doing statistics
    void processDeparture(const Event& arrivalEvent, const int& currentTime, PriorityQueue<Event>& timeLineQueue, Queue<Event>& backLineQueue, Statistic& statistic, Tellers& tellerModel){
        
        // Remove this event from the event queue
        try{
            timeLineQueue.dequeue();
        } catch (EmptyDataCollectionException e){/*cout << e.what() << endl*/}
        
        if(!backLineQueue.isEmpty()){
            // Customer at front of line begins transaction
            Event customer;
            try {
                customer = backLineQueue.peek();
                backLineQueue.dequeue();
            } catch (EmptyDataCollectionException e) {}
            statistic.totalWaitedTime += (currentTime - customer.getTime());
            Event newDepatureEvent = Event(departure, currentTime + customer.getLength(), 0);
            timeLineQueue.enqueue(newDepatureEvent);
        } else {
            tellerModel.freeATeller();
        }
    }
    
public:
    //Desc: Constructor
    //Pre:  input should be certain designed format
    //Post: input changes and numOfTellers changes
    Simulator(istream& input, int numOfTellers){
        origionalCustomerData = PriorityQueue<Event>();
        int arriveTime, processTime;
        while (input >> arriveTime >> processTime) {
            origionalCustomerData.enqueue(Event(arrival, arriveTime, processTime));
        }
        this->numOfTellers = numOfTellers;
    }
    
    //Desc: start a simulation, and returns its statistics
    //Pre:  input should be certain designed format
    //Post: if the print is true, then print the simulation process and generated statistics
    Statistic simulation(bool print){
        //initialization
        Queue<Event> backLine;
        PriorityQueue<Event> timeLine = origionalCustomerData;
        Tellers tellers = Tellers(numOfTellers);
        Statistic statistic;
        statistic.numOfPeople = 0;
        statistic.totalWaitedTime = 0;
        
        //Start Simulation
        if(print){
            cout << "Simulation Begins" << endl;
        }
        
        //Create and add arrive events to timeline
        //EventLoop
        while (!timeLine.isEmpty()) {
            Event currentEvent = timeLine.peek();
            int currentTime = currentEvent.getTime();
            if(currentEvent.getType() == arrival){
                statistic.numOfPeople++;
                if(print){
                    cout << "Processing an arrival event at time:" << right << setw(5) << currentTime << endl;
                }
                processArrival(currentEvent, currentTime, timeLine, backLine, tellers);
            } else {
                if(print){
                    cout << "Processing a departure event at time:" << right << setw(4) << currentTime << endl;
                }
                processDeparture(currentEvent, currentTime, timeLine, backLine, statistic, tellers);
            }
        }
        
        if(print){
            cout << "Simulation Ends" << endl << endl;
        }
        //End Simulation
        
        if(print){
            cout << "Final Statistics:  " << endl
            << "    Total number of people processed:  " << statistic.numOfPeople << endl
            << "    Average amount of time spent waiting: " << setprecision(3) << statistic.totalWaitedTime / statistic.numOfPeople << endl;
        }
        return statistic;
    }
    
    //Desc: Print the time decreased if the teller added to target number
    //Pre:  Target Num of teller non-zero or negative
    //Post: No
    void printDecreasedTime(int targetNumOfTeller){
        int origionalNumOfTeller = numOfTellers;
        Statistic origionalStat = simulation(false);
        numOfTellers = targetNumOfTeller;
        Statistic newStat = simulation(false);
        numOfTellers = origionalNumOfTeller;
        cout << "For " << origionalNumOfTeller << " tellers: " << origionalStat.totalWaitedTime / origionalStat.numOfPeople << endl;
        cout << "For " << targetNumOfTeller << " tellers: " << newStat.totalWaitedTime / newStat.numOfPeople << endl;
        cout << "Decreased time: " << origionalStat.totalWaitedTime / origionalStat.numOfPeople - newStat.totalWaitedTime / newStat.numOfPeople << endl;
        
    }
};


int main () {
    Simulator a = Simulator(cin, 1);
    a.simulation(true);
	return 0;
} // main



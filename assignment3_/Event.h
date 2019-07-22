//
//  Event.h
//  Assignment3
//
//  Created by Haoping Yu on 2019/3/2.
//  Copyright © 2019 Haoping Yu. All rights reserved.
//
//  Desc: Determine the event of departure and arrive


#pragma once 

typedef enum etype { arrival, departure } EventType;


// Desc:  Represents a simulation event
class Event {
private:
    
    etype eventType;
    int time;
    int length;

public:
    //Constructor
    Event(etype eventType, int time, int length):eventType(eventType), time(time), length(length){}
    Event():eventType(arrival),time(0),length(0){};

    // Desc:  Comparators
    bool operator<(const Event &r) const { return time < r.time; };
    bool operator>(const Event &r) const { return time > r.time; };
    bool operator<=(const Event &r) const { return time <= r.time; };
    bool operator>=(const Event &r) const { return time >= r.time; };

    //Desc:  Getter
    void setTime(const int& time);
    void setLength(const int& length);
    void changeType(const etype& eType);
    
    //Desc: Setter
    int getTime() const;
    int getLength() const;
    etype getType() const;
    
    
}; // Event


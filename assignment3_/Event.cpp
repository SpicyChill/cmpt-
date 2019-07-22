//
//  Event.h
//  Assignment3
//
//  Created by Haoping Yu on 2019/3/2.
//  Copyright © 2019 Haoping Yu. All rights reserved.
//
//  Desc: Determine the event of departure and arrive



#include "Event.h"

//Desc:  Getter
void Event::setTime(const int& time){
    this->time = time;
}

void Event::setLength(const int& length){
    this->length = length;
}

void Event::changeType(const etype& eType){
    eventType = eType;
}

//Desc: Setter
int Event::getTime() const{
    return time;
}
int Event::getLength() const{
    return length;
}
etype Event::getType() const{
    return eventType;
}

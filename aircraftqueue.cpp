#include <iostream>
#include "aircraftqueue.h"

using namespace std;

AircraftQueue::AircraftQueue(){
    totalTime = 0;
    totalCrafts = 0;
    maxWaitTime = 0;
}

void AircraftQueue::addTime(){
    if(!this->empty()){
        QueueElement<Aircraft>* current;
        current = getFront();
        while(current){
            current->data.increaseTime();
            current = current->next;
        }
    }
}

bool AircraftQueue::push(Aircraft const& aircraft){
    canceled++;
    return LQueue<Aircraft> :: push(aircraft);
}

Aircraft AircraftQueue::pop(){
    totalTime += head().getTimeInQ();
    totalCrafts++;
    if(maxWaitTime < head().getTimeInQ())
        maxWaitTime = head().getTimeInQ();
    return LQueue<Aircraft> :: pop();
}

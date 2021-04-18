#include <iostream>
#include "aircraft.h"

using namespace std;

Aircraft::Aircraft(){
    runAway = -1;
    priority = 0;
    time_in_q = 0;
}

Aircraft::Aircraft(int _priority, int _runAway):
                    runAway(_runAway), priority(_priority){
    time_in_q = 0;
}

Aircraft::Aircraft(Aircraft const& aircraft){
    copy(aircraft);
}

Aircraft& Aircraft::operator=(Aircraft const& aircraft){
    if(this != &aircraft)
        copy(aircraft);
    return *this;
}

void Aircraft::copy(Aircraft const& aircraft){
    runAway = aircraft.runAway;
    priority = aircraft.priority;
    time_in_q = aircraft.time_in_q;
}

void Aircraft::increaseTime(){
    time_in_q++;
}

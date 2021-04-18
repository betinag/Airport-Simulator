#include <iostream>
#include "airport.h"

using namespace std;

Airport::Airport(){
    runAways = NULL;
    landed = tookOff = 0;
    n = allFree = 0;
    avgWaitL = avgWaitT = maxWaitL = maxWaitT = 0;
}

Airport::Airport(int _n){
    n = _n;
    runAways = new bool[n];
    for(int i = 0; i < n; i++)
        runAways[i] = true;

    landed = tookOff = allFree = 0;
    avgWaitL = avgWaitT = maxWaitL = maxWaitT = 0;
}

double Airport::getAverageWaitingTimeToLand(){
    if(landing.getTotalCrafts() == 0)
        return 0;
    return landing.getTotalTime()/landing.getTotalCrafts();
}

double Airport::getAveragewaitingTimeToTakeOff(){
    if(takeoff.getTotalCrafts() == 0)
        return 0;
    return takeoff.getTotalTime()/takeoff.getTotalCrafts();
}

void Airport::addInLanding(Aircraft craft){
    landing.push(craft);
}

void Airport::addInTakeOff(Aircraft craft){
    takeoff.push(craft);
}

void Airport::freeRunAway(int runAway){
    if(checkFree(runAway))
        runAways[runAway] = true;
    else
        freeMinRunAway();
}

bool Airport::checkFree(int runAway) const{
    int index = 0;
    while(index < runAway && runAways[index])
        index++;

    if(index != runAway)
        return false;
    return true;
}

bool Airport::checkTakeOff(Aircraft& plane) const{
    if(takeoff.empty()
        ||(!takeoff.empty()
                && takeoff.head().getRunAway() <= plane.getRunAway()))
        return true;

    if(takeoff.head().getPriority() < plane.getPriority())
        return false;
}

void Airport::freeMinRunAway(){
    int index = 0;
    while (runAways[index])
        index++;

    runAways[index] = true;
}

void Airport::updateInformation(){
    increaseWaitTime();
    checkAllRunAwaysFree();
    avgWaitL += landing.getLength();
    avgWaitT += takeoff.getLength();

    if(landing.getLength() > maxWaitL)
        maxWaitL = landing.getLength();
    if(takeoff.getLength() > maxWaitT)
        maxWaitT = takeoff.getLength();
}

void Airport::checkAllRunAwaysFree(){
    for(int i = 0; i < n; i++)
        if(!runAways[i])
            return;
    allFree++;
}

void Airport::increaseWaitTime(){
    landing.addTime();
    takeoff.addTime();
}

void Airport::movePlane(Aircraft plane){
    plane.decreasePriority();
    QueueElement<Aircraft>* current = takeoff.getFront();
    while(current->next && current->next->data.getPriority() < plane.getPriority())
        current = current->next;

    while(current->next && current->next->data.getRunAway() > plane.getRunAway())
        current = current->next;

    QueueElement<Aircraft>* toInsert = new QueueElement<Aircraft>;
    toInsert->data = plane;
    toInsert->next = current->next;
    current->next = toInsert;
    takeoff.pop();
}

void Airport::takeOffNew(Aircraft plane){
    int _runAway = plane.getRunAway();
    if(!(checkFree(_runAway) && runAways[_runAway])){
        takeoff.push(plane);
        if(!checkFree(_runAway))
            freeMinRunAway();
        else
            runAways[_runAway] = true;
    }
}

int Airport::getLeftPlanes() const{
    return landing.getLength() + takeoff.getLength();
}

void Airport::service(){
    if(!landing.empty())
        landQuery(landing.head());
    else
        if(!takeoff.empty())
            takeOffQuery(takeoff.head());
}

bool Airport::land(Aircraft& plane){
    int _runAway = plane.getRunAway();
    if(runAways[_runAway] && checkTakeOff(plane)){
        if(!checkFree(_runAway)){
            runAways[_runAway] = false;
            freeMinRunAway();
        }
        landed++;
        return true;
    }
    return false;
}

bool Airport::takeOff(Aircraft& plane){
    int _runAway = plane.getRunAway();
    if(runAways[_runAway] && checkFree(_runAway)){
        takeoff.pop();
        tookOff++;
        return true;
    }
    return false;
}

void Airport::landQuery(Aircraft newPlane){
    bool flag = false;
    if(!takeoff.empty()
            && ((landing.empty() && takeoff.head().getPriority() < newPlane.getPriority()) || (!landing.empty()
                    && takeoff.head().getPriority() < landing.head().getPriority()))){
        Aircraft toTakeOff = takeoff.head();
        flag = takeOff(toTakeOff);
        if(!flag){
            movePlane(toTakeOff);
            landQuery(newPlane);
        }
        landing.push(newPlane);
    }
    else{
        if(landing.empty()){
            flag = land(newPlane);
            if(!flag){
                if(!checkTakeOff(newPlane)){
                    Aircraft toTakeOff = takeoff.head();
                    flag = takeOff(toTakeOff);
                    if(!flag){
                        movePlane(toTakeOff);
                        landQuery(newPlane);
                    }
                }
                else
                    freeRunAway(newPlane.getRunAway());
                landing.push(newPlane);
            }
        }
        else{
            Aircraft toLand = landing.head();
            flag = land(toLand);
            if(flag)
                landing.pop();
            else{
                if(!checkTakeOff(toLand)){
                    movePlane(takeoff.head());
                    landQuery(newPlane);
                }
                else
                    freeRunAway(toLand.getRunAway());
                landing.push(newPlane);
            }
        }
    }
}

void Airport::takeOffQuery(Aircraft newPlane){
    bool flag = false;

    if(landing.empty()){
        if(takeoff.empty()){
            takeOffNew(newPlane);
        }
        else{
            if(newPlane.getPriority() > takeoff.head().getPriority()
               || (newPlane.getPriority() == takeoff.head().getPriority()
                   && newPlane.getRunAway() < takeoff.head().getRunAway())){
                Aircraft toTakeOff = takeoff.head();
                flag = takeOff(toTakeOff);
                if(!flag){
                    movePlane(toTakeOff);
                    takeOffQuery(newPlane);
                }
                takeoff.push(newPlane);
            }
            else
               takeOffNew(newPlane);
        }
    }else{
        Aircraft toLand = landing.head();
        flag = land(toLand);
        if(flag)
            landing.pop();
        else{
             if(!checkTakeOff(toLand)){
                movePlane(takeoff.head());
                takeOffQuery(newPlane);
             }
             else
                freeRunAway(toLand.getRunAway());
        }
        takeoff.push(newPlane);
    }
}

Airport::~Airport(){
    delete[] runAways;
}

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "aircraftqueue.h"

class Airport{
private:
    int n;
    int simulation_time;
    bool* runAways;
    AircraftQueue landing, takeoff;
public:
    Airport();
    Airport(int);
    int getLeftPlanes() const;
    int getLanded() const { return landed; }
    int getTookOff() const { return tookOff; }
    int getSimulationTime() const { return simulation_time; }
    int getCanceledPlanes() { return landing.getCanceled() + takeoff.getCanceled(); }
    int getMaxWaitingToLand() const { return maxWaitL; }
    int getMaxWaitingToTakeOff() const { return maxWaitT; }
    double getPercentageFree(){ return allFree/simulation_time*100; }
    double getAverageWaitingToLand() { return avgWaitL/simulation_time; }
    double getAverageWaitingtoTakeOff() { return avgWaitT/simulation_time; }
    double getMaxWaitingTimeToLand() { return landing.getMaxWaitTime(); }
    double getMaxWaitingTimeToTakeOff() { return takeoff.getMaxWaitTime(); }
    double getAverageWaitingTimeToLand();
    double getAveragewaitingTimeToTakeOff();
    void addInLanding(Aircraft);
    void addInTakeOff(Aircraft);
    void landQuery(Aircraft);
    void takeOffQuery(Aircraft);
    void updateInformation();
    void increaseWaitTime();
    void checkAllRunAwaysFree();
    void service();
    bool land(Aircraft&);
    bool takeOff(Aircraft&);
    ~Airport();
private:
    int landed, tookOff,
        avgWaitL, avgWaitT,
        maxWaitL, maxWaitT;
    int allFree;
    void freeMinRunAway();
    void freeRunAway(int);
    void takeOffNew(Aircraft);
    void movePlane(Aircraft);
    bool checkFree(int) const;
    bool checkTakeOff(Aircraft&) const;
};

#endif /* AIRPORT_H_ */

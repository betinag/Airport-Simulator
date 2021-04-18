#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include<iostream>

using namespace std;

class Aircraft{
public:
    Aircraft();
    Aircraft(int, int);
    Aircraft(Aircraft const&);
    Aircraft& operator=(Aircraft const&);
    int getRunAway() const { return runAway; }
    int getPriority() const { return priority; }
    int getTimeInQ() const { return time_in_q; }
    void increaseTime();
    void decreasePriority() { priority++; }
private:
    int runAway;
    int priority;
    int time_in_q;
    void copy(Aircraft const&);
};

#endif /* AIRCRAFT_H_ */

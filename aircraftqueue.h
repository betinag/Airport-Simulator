#ifndef AIRCRAFTQUEUE_H_
#define AIRCRAFTQUEUE_H_

#include "queue.cpp"
#include "aircraft.h"

class AircraftQueue : public LQueue<Aircraft> {
private:
    int totalTime, totalCrafts;
    int maxWaitTime, canceled;
public:
    AircraftQueue();
    void addTime();
    int getTotalTime() const { return totalTime ;}
    int getTotalCrafts() const { return totalCrafts; }
    int getCanceled() const { return canceled; }
    int getMaxWaitTime() const { return maxWaitTime; }
    Aircraft pop();
    bool push(Aircraft const&);
};

#endif /* AIRCRAFTQUEUE_H_ */

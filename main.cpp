#include <iostream>
#include <cstdlib>
#include <ctime>
#include "airport.h"

using namespace std;

void sort(int* array, int size){
    for(int i = 0; i < size; i++){
        int max = i;
        for(int j = i+1; j < size; j++)
            if(array[j] > array[max])
                max = j;
        int swap = array[max];
        array[max] = array[i];
        array[i] = swap;
    }
}

int main()
{
    cout << "Airport Simulation\n";
    int numberOfRunAways;
    cout << "Number of runaways: ";
    cin >> numberOfRunAways;
    Airport airport(numberOfRunAways);
    int landing, takeoff;
    int simulation_time = airport.getSimulationTime();
    srand(time(NULL));
    for(int i = 1; i <= simulation_time; i++){
        if(i + airport.getLeftPlanes() < simulation_time){
            landing = rand() % 3;
            takeoff = rand() % 3;
            int* runAways = NULL;
            if(landing) {
                runAways = new int[landing];
                for(int k = 0; k < landing; k++)
                    runAways[k] = rand() % simulation_time + 1;
                sort(runAways, landing);
                airport.landQuery(Aircraft(i, *runAways));
                for(int k = 1; k < landing; k++)
                    airport.addInLanding(Aircraft(i, runAways[k]));
                delete runAways;
            }
            if(takeoff){
                runAways = new int[takeoff];
                for(int k = 0; k < takeoff; k++)
                    runAways[k] = rand() % simulation_time + 1;
                sort(runAways, takeoff);
                if(landing)
                    for(int k = 0; k < takeoff; k++)
                        airport.addInTakeOff(Aircraft(i, runAways[k]));
                else{
                    airport.takeOffQuery(Aircraft(i, *runAways));
                    for(int k = 1; k < takeoff; k++)
                        airport.addInTakeOff(Aircraft(i, runAways[k]));
                }
                delete runAways;
            }
            if(!landing && !takeoff)
                airport.service();
        }
        else
            airport.service();

        airport.increaseWaitTime();
        airport.updateInformation();
    }
    return 0;
}

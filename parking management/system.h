#ifndef system_H
#define system_H
#include "Class_vehicle.h"
const int max_queue_size = 100;
class parkingsystem
{
private:
    struct parkingSlot {
        vehicle* ptr;
        bool occupied;
    };

    parkingSlot* parking;
    int totalslots;
    int parkedCount;

    vehicle** waitQueue;
    int queueFront, queueRear,queuesize;

    vehicle* undoStack[100];
    int stackTop;

public:
    parkingsystem(int cap);
    ~parkingsystem();
    void initialize(int slots);
    bool parkVehicle(vehicle* v);
    bool removeVehicle(int slotID);
    void viewAll();
    void reset();
   void viewslots();
    void addslots(int extraslots);
    void savesystem();
    void loadsystem();
   void pushUndo(vehicle* v);
   vehicle* popUndo();
    void enqueue(vehicle* v);
    vehicle* dequeue();
    bool isQueueEmpty();
    bool isStackEmpty();
    void undolastaction();
    void viewqueue();
    void Viewqueue();
};

#endif



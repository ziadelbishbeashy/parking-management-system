#ifndef system_H
#define system_H
#include "Class_vehicle.h"
class system
{
private:
    struct parkingSlot {
        vehicle* ptr;
        bool occupied;
    };

    parkingSlot* parking;
    int totalslots;
    int parkedCount;

    vehicle* waitQueue[100];
    int queueFront, queueRear;

    vehicle* undoStack[100];
    int stackTop;

public:
    system();
    ~system();
    void initialize(int slots);
    bool parkVehicle(vehicle* v);
    bool removeVehicle(int slotID);
    void viewAll();
    void reset();

    void pushUndo(vehicle* v);
    vehicle* popUndo();
    void enqueue(vehicle* v);
    vehicle* dequeue();
    bool isQueueEmpty();
    bool isStackEmpty();
};

#endif



#ifndef system_H
#define system_H
#include "Class_vehicle.h"
const int max_queue_size = 100;
class parkingsystem
{
private:
    struct parkingSlot {
        vehicle* ptr = nullptr;
        bool occupied = false;
    };
    struct action {
        char type;      // 'p' = park , 'r' = remove , etc
        vehicle* v;      //pointer to the vehicle
        int postion;        //slot number

    };
    action undostack[100];   // Stack of actions
    int undotop = -1;        // Top index of undo stack

    parkingSlot* parking = nullptr;
    int totalslots = 0;
    int parkedCount = 0;

    vehicle** waitQueue = nullptr;
    int queueFront = 0;
    int queueRear = -1;
    const int queuesize = max_queue_size;

    vehicle* undoStack[100];
    int stackTop = -1;

public:

    parkingsystem();
    parkingsystem(int cap);
    ~parkingsystem();
    void initialize(int slots);
    void parkVehicle(vehicle* v);
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
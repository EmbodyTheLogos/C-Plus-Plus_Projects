//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: PriorityQueue.h
//
// Description: a modified version of Queue class discussed in class
//
// Acknowledgement: (1) Doctor Chang's Notes
//					(2) Class demo programs
//
//---------------------------------------------------------------------
#include "DLList.h"

template <typename T>
class PriorityQueue {

private:
    DLList<T> list;

public:
    PriorityQueue();
    ~PriorityQueue();
    bool isEmpty();
    void clear();
    void enqueue(T, int);
    int largest();
    T dequeue();
    T top();
    T first();
};

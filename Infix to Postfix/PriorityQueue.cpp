//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: PriorityQueue.cpp
//
// Description: a modified version of Queue class discussed in class
//
// Acknowledgement: (1) Doctor Chang's Notes
//		    (2) Class demo programs
//
//---------------------------------------------------------------------

#include "PriorityQueue.h"
using namespace std;

template<typename T>
PriorityQueue<T>::PriorityQueue() {
    // nothing!
}


template<typename T>
PriorityQueue<T>::~PriorityQueue() {
    // nada
}

template<typename T>
bool PriorityQueue<T>::isEmpty() {
    return list.isEmpty();
}

template<typename T>
void PriorityQueue<T>::clear() {
    while (!list.isEmpty()) {
        list.removeTail();
    }
}

template<typename T>
void PriorityQueue<T>::enqueue(T data, int priority) {
	
    list.addToTail(data, priority);
}

template<typename T>
T PriorityQueue<T>::dequeue() {

	int large = largest();
	int index = 0;
	DLNode<T> *temp = list.getHead();
	
	while(!list.isEmpty() && temp!=NULL)
	{
		if(large == temp->getPriority())
		{
			break;
		}
		temp = temp->getNext();
		index++;
	}
	return list.removeAt(index);

}

template <typename T>
T PriorityQueue<T>::first()
{
	int large = largest();
	int index = 0;
	DLNode<T> *temp = list.getHead();
	
	while(!list.isEmpty() && temp!=NULL)
	{
		if(large == temp->getPriority())
		{
			break;
		}
		temp = temp->getNext();
		index++;
	}
	return list.at(index);
}

template<typename T>
T PriorityQueue<T>::top() {
    // give us the first element in the PriorityQueue
    // but not remove it!
    return list.getHead()->getData();
}

template<typename T>
int PriorityQueue<T>::largest()
{
	int large;
	
	DLNode<T> *temp = list.getHead();
	large = temp->getPriority();
	while(temp!=NULL)
	{
		if(large <= temp->getPriority())
		{
			large = temp->getPriority();
		}
		temp = temp->getNext();		
	}	
	return large;
}


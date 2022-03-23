//---------------------------------------------------------------------
// Name: Long Nguyen
// Email:lhn5032 @psu.edu
// Class: CMPSC 122, Section 1
// Program: DLList.h
//
// Description: Contains List implementations from class notes.
//
//---------------------------------------------------------------------
#include <cstddef>

template <typename T>
class DLNode {
public:

    DLNode(T, DLNode<T> *, DLNode<T> *,int);
    DLNode();
    T getData() const;
    void setData(T data);
    DLNode<T> *getNext() const;
    void setNext(DLNode<T> *next);
    DLNode<T> *getPrev() const;
    void setPrev(DLNode<T> *prev);
    int getPriority(){ return priority;	}
    void setPriority(int);
    T getData(){ return data;}


private:
    T data;
    int priority;
    DLNode<T> *next;
    DLNode<T> *prev;
};

template<typename T>
T DLNode<T>::getData() const {
    return data;
}

template<typename T>
void DLNode<T>::setData(T data) {
    DLNode::data = data;
}
template<typename T>
void DLNode<T>::setPriority(int prior) {
    DLNode::priority = prior;
}

template<typename T>
DLNode<T> *DLNode<T>::getNext() const {
    return next;
}

template<typename T>
void DLNode<T>::setNext(DLNode<T> *next) {
    DLNode::next = next;
}

template<typename T>
DLNode<T> *DLNode<T>::getPrev() const {
    return prev;
}

template<typename T>
void DLNode<T>::setPrev(DLNode<T> *prev) {
    DLNode::prev = prev;
}

template<typename T>
DLNode<T>::DLNode() {
    next = prev = NULL;
}

template<typename T>
DLNode<T>::DLNode(T d, DLNode<T> *p, DLNode<T> *n, int prior) {
    data = d;
    prev = p;
    next = n;
    priority = prior;
}

template <typename T>
class DLList {

public:

    DLList();
    ~DLList();
    bool isEmpty();
    bool isInList(T);
    void addToHead(T, int);
    void addToTail(T, int);
    T removeHead();
    T removeTail();
    void print();
    void printReverse();
    DLNode<T> *getHead() const;
    void setHead(DLNode<T> *head);
    DLNode<T> *getTail() const;
    void setTail(DLNode<T> *tail);
    T removeAt(int index);
	bool remove(T value);

	T at(int index);

private:
    DLNode<T> *head;
    DLNode<T> *tail;
    
};

template<typename T>
DLList<T>::DLList() {
    head = tail = NULL;
}

template<typename T>
DLList<T>::~DLList() {
    while (! isEmpty()) {
        removeTail();
    }
}

template<typename T>
bool DLList<T>::isEmpty() {
    return head == NULL;
}

template<typename T>
bool DLList<T>::isInList(T d) { // O(N)
    DLNode<T> *temp = head;
    while (temp != NULL&& temp->getData() != d) {
        temp = temp->getNext();
    }
    return temp != NULL;
}

template<typename T>
void DLList<T>::addToHead(T d, int prior) { // O(1)
    if (head == NULL) {
        head = tail = new DLNode<T>(d, NULL, NULL, prior);
    } else {
        head = new DLNode<T>(d, NULL, head, prior);
        head->getNext()->setPrev(head);
    }
}

template<typename T>
void DLList<T>::addToTail(T d, int prior) {    // O(1)
    if (isEmpty()) {
        head = tail = new DLNode<T>(d, NULL, NULL, prior);
    } else {
        tail = new DLNode<T>(d, tail, NULL, prior);
        tail->getPrev()->setNext(tail);
    }
}

template<typename T>
T DLList<T>::removeHead() { // O(1)
    T d = head-> getData();
    if (head == tail) {
        delete tail;
        head = tail = NULL;
    } else {
        head = head->getNext();
        delete head->getPrev();
        head->setPrev(NULL);
    }
    return d;
}

template<typename T>
T DLList<T>::removeTail() { // O(1)
    T d = head->getData();
    if (head == tail) {
        delete tail;
        head = tail = NULL;
    } else {
        tail = tail->getPrev();
        delete tail->getNext();
        tail->setNext(NULL);
    }
    return d;
}



template<typename T>
DLNode<T> *DLList<T>::getHead() const {
    return head;
}

template<typename T>
void DLList<T>::setHead(DLNode<T> *head) {
    DLList::head = head;
}

template<typename T>
DLNode<T> *DLList<T>::getTail() const {
    return tail;
}

template<typename T>
void DLList<T>::setTail(DLNode<T> *tail) {
    DLList::tail = tail;
}

template<typename T>
T DLList<T>::removeAt(int index)
{
	T data = at(index);
	remove(at(index));
	return data;
}

template<typename T>
bool DLList<T>::remove(T value)
{	
 //Check if the value is in the list
	DLNode<T> *temp = getHead();
	while (temp != NULL && temp->getData() != value)
		temp = temp->getNext();


	if(temp != NULL)
	{
		while(temp->getNext()!=NULL)
	 	{
	 		temp->setData(temp->getNext()->getData());
	 		temp->setPriority(temp->getNext()->getPriority());
	 		temp=temp->getNext();
	 	}
	 	removeTail();
		return true;
	} else return false;
}

template<typename T>
T DLList<T>::at(int index)
{
	DLNode<T> *temp = getHead();
	for (int i = 0; i<index;i++)
	{
		temp=temp->getNext();
	}
	return temp->getData();
}

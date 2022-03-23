//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: stack_int.h
//					
//
// Description: I ran into a problem while trying to genericize the stack file
//				I even go to the learning center and they still could not figure it out,
//				even though the syntax was right. 
//				So, I decided to make another stack file for integer type.
// 
// Acknowledgement: The provided stack file
//
//---------------------------------------------------------------------

#include <cstddef>
class IntListNode
{
private: 
	int data;
	IntListNode* prev;
	IntListNode* next;

public:
	IntListNode() { prev = next = NULL; }
	IntListNode(int d, IntListNode* p, IntListNode* n) { data = d; prev = p; next = n; }

	friend class IntList;
};

class IntList
{
private:
	IntListNode* list_head;
	IntListNode* list_tail;

public:
	IntList() { list_head = list_tail = NULL; }
	~IntList() { clear(); }

	bool isEmpty() { return list_head == NULL; }
	bool contains(int value);

	void addToHead(int value);
	void addToTail(int value);

	int head() { return list_head->data; }
	int tail() { return list_tail->data; }

	int removeHead();
	int removeTail();
	void clear();
};

bool IntList::contains(int value)
{
	IntListNode *temp = list_head;
	while (temp != NULL && temp->data != value)
		temp = temp->next;

	return temp != NULL;
}

void IntList::addToHead(int value)
{
	if (isEmpty())
	{
		list_head = list_tail = new IntListNode(value, NULL, NULL);
	}
	else
	{
		list_head = new IntListNode(value, NULL, list_head);
		list_head->next->prev = list_head;	
	}
}

void IntList::addToTail(int value)
{
	if (isEmpty())
	{
		list_head = list_tail = new IntListNode(value, NULL, NULL);
	}
	else
	{
		list_tail = new IntListNode(value, list_tail, NULL);
		list_tail->prev->next = list_tail;
	}
}

int IntList::removeHead()
{
	int value = list_head->data;
	if (list_head == list_tail)
	{
		delete list_tail;
		list_head = list_tail = NULL;
	}
	else
	{
		list_head = list_head->next;
		delete list_head->prev;
		list_head->prev = NULL;
	}

	return value;
}

int IntList::removeTail()
{
	int value = list_head->data;
	if (list_head == list_tail)
	{
		delete list_tail;
		list_head = list_tail = NULL;
	}
	else
	{
		list_tail = list_tail->prev;
		delete list_tail->next;
		list_tail->next = NULL;
	}

	return value;
}

void IntList::clear()
{
	while (!isEmpty())
		removeTail();
}

class IntStack
{
private:
	IntList* list;
	int size;
public:
	IntStack() { list = new IntList(); size = 0;};
	~IntStack() { delete list;	}

	bool isEmpty() { return list->isEmpty(); }
	void clear() { list->clear(); }
	void push(int data) { list->addToHead(data); size++;}
	int pop() { return list->removeHead(); size--;}
	int top() { return list->head(); }
	int getSize() { return size;}
};

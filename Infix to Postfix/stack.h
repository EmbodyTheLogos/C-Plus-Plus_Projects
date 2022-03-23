//---------------------------------------------------------------------
// Name: Long Nguyen
// Email: lhn5032@psu.edu
// Class: CMPSC 122, Section 1
// Program: stack.h
//
// Description: Contains List and Stack implementations from
// class notes.
//
//---------------------------------------------------------------------

#include <cstddef>
class ListNode
{
private: 
	char data;
	ListNode* prev;
	ListNode* next;

public:
	ListNode() { prev = next = NULL; }
	ListNode(char d, ListNode* p, ListNode* n) { data = d; prev = p; next = n; }

	friend class List;
};

class List
{
private:
	ListNode* list_head;
	ListNode* list_tail;

public:
	List() { list_head = list_tail = NULL; }
	~List() { clear(); }

	bool isEmpty() { return list_head == NULL; }
	bool contains(char value);

	void addToHead(char value);
	void addToTail(char value);

	char head() { return list_head->data; }
	char tail() { return list_tail->data; }

	char removeHead();
	char removeTail();
	void clear();
};

bool List::contains(char value)
{
	ListNode *temp = list_head;
	while (temp != NULL && temp->data != value)
		temp = temp->next;

	return temp != NULL;
}

void List::addToHead(char value)
{
	if (isEmpty())
	{
		list_head = list_tail = new ListNode(value, NULL, NULL);
	}
	else
	{
		list_head = new ListNode(value, NULL, list_head);
		list_head->next->prev = list_head;	
	}
}

void List::addToTail(char value)
{
	if (isEmpty())
	{
		list_head = list_tail = new ListNode(value, NULL, NULL);
	}
	else
	{
		list_tail = new ListNode(value, list_tail, NULL);
		list_tail->prev->next = list_tail;
	}
}

char List::removeHead()
{
	char value = list_head->data;
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

char List::removeTail()
{
	char value = list_head->data;
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

void List::clear()
{
	while (!isEmpty())
		removeTail();
}

class Stack
{
private:
	List* list;
public:
	Stack() { list = new List(); }
	~Stack() { delete list;	}

	bool isEmpty() { return list->isEmpty(); }
	void clear() { list->clear(); }
	void push(char data) { list->addToHead(data); }
	char pop() { return list->removeHead(); }
	char top() { return list->head(); }
};

#include "Stack.h"

Stack::Stack()
{
	pHead = NULL;
}

Stack::~Stack()
{
	while (!isEmpty())
	{
		Node* p = pHead;
		pHead = p->pNext;
		delete p;
	}
}

bool Stack::isEmpty()
{
	return (pHead == NULL ? 1 : 0);
}

Node* Stack::createNode(Data x)
{
	Node* p = new Node();
	p->Info = x;
	p->pNext = NULL;
	return p;
}

void Stack::Push(Data x)
{
	Node* p = createNode(x);
	if (isEmpty())
	{
		pHead = p;
	}
	else
	{
		p->pNext = pHead;
		pHead = p;
	}
}

int Stack::Pop(Data& x)
{
	if (isEmpty())
	{
		return 0;
	}
	else
	{
		Node* p = pHead;
		x = p->Info;
		pHead = p->pNext;
		delete p;
	}
	return 1;
}

Node* Stack::getHead()
{
	return pHead;
}

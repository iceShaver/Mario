#pragma once
#include "Object.h"

//--------------------------ListElement Class----------------------------
template <class Type> class ListElement
{
	template <class Object> friend class List;

public:
	ListElement();
	~ListElement();
private:
	int index;
	ListElement<Type> * nextPtr;
	ListElement<Type> * prevPtr;
	Type * object;
};


template <class Type>
ListElement<Type>::ListElement()
{
	index = 0;
	nextPtr = nullptr;
	prevPtr = nullptr;
	object = nullptr;
}

template <class Type>
ListElement<Type>::~ListElement()
{
	if (object)
		delete object;
}

//class Object;

//--------------------------List class--------------------------------
template <class Type> class List
{
public:
	List();
	~List();
	bool Add(Type * object);
	Type * Get(int index);
	Type * GetLast() const;
	Type * GetFirst() const;
	bool ForEach(bool (Type::*function)());
	bool Delete(int index);
private:
	ListElement<Type> * getElement(int index);
	int elementsNumber;
	ListElement<Type> * firstPtr;
	ListElement<Type> * lastPtr;
	//ListElement<Type> element;
};



template <class Type> List<Type>::List()
{
	elementsNumber = 0;
	firstPtr = nullptr;
	lastPtr = nullptr;
}

template <class Type> List<Type>::~List()
{
	ListElement<Type> * el = firstPtr;
	ListElement<Type> * tmp;
	while (el)
	{
		tmp = el;
		el = el->nextPtr;
		delete tmp;
	}
}




template <class Type> bool List<Type>::Add(Type * object)
{
	ListElement<Type> * element = new ListElement<Type>;
	if (object == nullptr)
	{
		printf("Given pointer is nullptr");
		return false;
	}
	element->index = elementsNumber;
	elementsNumber++;
	//If there is no elements in the list
	if (firstPtr == nullptr)
	{
		firstPtr = element;
		lastPtr = element;
		element->prevPtr = nullptr;
		element->nextPtr = nullptr;
	}
	else
	{
		lastPtr->nextPtr = element;
		element->nextPtr = nullptr;
		element->prevPtr = lastPtr;
		lastPtr = element;
	}
	element->object = object;
	return true;


}




template<class Type> Type * List<Type>::Get(int index)
{
	ListElement<Type> * element = firstPtr;
	while (element != nullptr)
	{
		if (element->index == index) return element->object;
		element = element->nextPtr;
	}
	return nullptr;
}




template<class Type> Type * List<Type>::GetLast() const
{
	if (!lastPtr) return nullptr;
	return lastPtr->object;
}






template<class Type> Type * List<Type>::GetFirst() const
{
	return firstPtr->object;
}




template <class Type>
bool List<Type>::ForEach(bool (Type::*function)())
{
	ListElement<Type> * element = firstPtr;
	if (element)
		do
		{
			if ((element->object->*function)()) return true;
		} while (element = element->nextPtr);
		return false;
}

template <class Type> bool List<Type>::Delete(int index)
{
	ListElement<Type> * element = getElement(index);
	if (element == nullptr) return false;


	if (element->prevPtr != nullptr && element->nextPtr != nullptr)
	{
		element->prevPtr->nextPtr = element->nextPtr;
		element->nextPtr->prevPtr = element->prevPtr;
	}
	else {
		if (element->prevPtr == nullptr && element->nextPtr == nullptr)
		{
			firstPtr = nullptr;
			lastPtr = nullptr;
		}
		else {
			if (element->prevPtr == nullptr)
			{
				firstPtr = element->nextPtr;
				element->nextPtr->prevPtr = nullptr;
			}
			if (element->nextPtr == nullptr) {
				lastPtr = element->prevPtr;
				element->prevPtr->nextPtr = nullptr;
			}
		}
	}
	elementsNumber--;
	delete element;
	return true;
}

template <class Type>
ListElement<Type>* List<Type>::getElement(int index)
{
	ListElement<Type> * element = firstPtr;
	while (element != nullptr)
	{
		if (element->index == index) return element;
		element = element->nextPtr;
	}
	return nullptr;
}







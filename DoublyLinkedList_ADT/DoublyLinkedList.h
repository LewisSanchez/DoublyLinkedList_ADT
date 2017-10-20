#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>
using std::cout;

#include "Node.h"

template <typename T>
class DoublyLinkedList
{
	public:
		DoublyLinkedList();
		DoublyLinkedList(const DoublyLinkedList & copy);
		~DoublyLinkedList();
		DoublyLinkedList & operator= (const DoublyLinkedList & rhs);
		bool isEmpty() const;
		const T & First() const;
		const T & Last() const;
		void Prepend(T data);
		void Append(T data);
		void Purge();
		void Extract(T data);
		void InsertAfter(T target, T data);
		void InsertBefore(T target, T data);

		// Test methods
		Node<T> * getHead();
		Node<T> * getTail();
		void PrintForwards();
		void PrintBackwards();

	private:
		Node<T> * m_head;
		Node<T> * m_tail;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
	: m_head(nullptr), m_tail(nullptr)
{

}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> & copy)
	: m_head(nullptr), m_tail(nullptr)
{
	if (copy.m_head != nullptr)
	{
		Node<T> * travel = copy.m_head;

		while (travel != nullptr)
		{
			Append(travel->m_data);
			travel = travel->m_next;
		}
	}
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	if (m_head != nullptr)
		Purge();
}

template <typename T>
DoublyLinkedList<T> & DoublyLinkedList<T>::operator= (const DoublyLinkedList<T> & rhs)
{
	if (this != &rhs)
	{
		if (m_head != nullptr)
			Purge();

		if (rhs.m_head != nullptr)
		{
			Node<T> * travel = rhs.m_head;

			while (travel != nullptr)
			{
				Append(travel->m_data);
				travel = travel->m_next;
			}
		}
	}

	return *this;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
	return (m_head == nullptr ? true : false);
}


template <typename T>
const T & DoublyLinkedList<T>::First() const
{
	if (m_head == nullptr)
		throw "List is empty - Cannot access First!";

	return m_head->m_data;
}

template <typename T>
const T & DoublyLinkedList<T>::Last() const
{
	if (m_head == nullptr)
		throw "List is empty - Cannot access Last!";

	return m_tail->m_data;
}

template <typename T>
void DoublyLinkedList<T>::Prepend(T data)
{
	Node<T> * new_node = new Node<T>(data);

	if (m_head != nullptr)
	{
		m_head->m_previous = new_node;
		new_node->m_next = m_head;
		m_head = new_node;
	}
	else
	{
		m_head = new_node;
		m_tail = new_node;
	}
}

template <typename T>
void DoublyLinkedList<T>::Append(T data)
{
	Node<T> * new_node = new Node<T>(data);

	if (m_head != nullptr)
	{
		m_tail->m_next = new_node;
		new_node->m_previous = m_tail;
		m_tail = new_node;
	}
	else
	{
		m_head = new_node;
		m_tail = new_node;
	}
}

template <typename T>
void DoublyLinkedList<T>::Purge()
{
	Node<T> * temp = nullptr;

	while (m_head != nullptr)
	{
		temp = m_head;
		m_head = m_head->m_next;
		delete temp;
	}

	m_head = nullptr;
	m_tail = nullptr;
}

template <typename T>
void DoublyLinkedList<T>::Extract(T data)
{
	Node<T> * travel = m_head;
	Node<T> * travels_previous = nullptr;
	Node<T> * travels_next = nullptr;

	while (travel != nullptr && travel->m_data != data)
		travel = travel->m_next;

	if (travel != nullptr && travel->m_data == data)
	{
		if (travel->m_previous == nullptr && travel->m_next == nullptr)
		{
			m_head = nullptr;
			m_tail = nullptr;
		}
		else if (travel == m_head)
		{
			travels_next = travel->m_next;
			travels_next->m_previous = nullptr;
			m_head = travels_next;
		}
		else if (travel == m_tail)
		{
			travels_previous = travel->m_previous;
			travels_previous->m_next = nullptr;
			m_tail = travels_previous;
		}
		else if (travel != nullptr)
		{
			travels_previous = travel->m_previous;
			travels_next = travel->m_next;
			travels_previous->m_next = travels_next;
			travels_next->m_previous = travels_previous;
		}
		delete travel;
	}
	else
		throw "Target to extract was not found!";
}

template <typename T>
void DoublyLinkedList<T>::InsertAfter(T target, T data)
{
	Node<T> * travel = m_head;

	while (travel != nullptr && travel->m_data != target)
		travel = travel->m_next;

	if (travel != nullptr && travel->m_data == target)
	{
		if (travel == m_tail)
			Append(data);
		else if (travel != nullptr)
		{
			Node<T> * new_node = new Node<T>(data);
			Node<T> * next = travel->m_next;

			travel->m_next = new_node;
			next->m_previous = new_node;
			new_node->m_previous = travel;
			new_node->m_next = next;
		}
	}
	else
		throw "Target to insert after was not found!";
}

template <typename T>
void DoublyLinkedList<T>::InsertBefore(T target, T data)
{
	Node<T> * travel = m_tail;

	while (travel != nullptr && travel->m_data != target)
		travel = travel->m_previous;

	if (travel != nullptr && travel->m_data == target)
	{
		if (travel == m_head)
			Prepend(data);
		else if (travel != nullptr)
		{
			Node<T> * new_node = new Node<T>(data);
			Node<T> * previous = travel->m_previous;

			travel->m_previous = new_node;
			previous->m_next = new_node;
			new_node->m_previous = previous;
			new_node->m_next = travel;
		}
	}
	else
		throw "Target to insert before was not found!";
}

template <typename T>
Node<T> * DoublyLinkedList<T>::getHead()
{
	return m_head;
}

template <typename T>
Node<T> * DoublyLinkedList<T>::getTail()
{
	return m_tail;
}

template <typename T>
void DoublyLinkedList<T>::PrintForwards()
{
	Node<T> * travel = m_head;

	while (travel != nullptr)
	{
		cout << travel->m_data << ' ';
		travel = travel->m_next;
	}

	cout << '\n';
}

template <typename T>
void DoublyLinkedList<T>::PrintBackwards()
{
	Node<T> * travel = m_tail;

	while (travel != nullptr)
	{
		cout << travel->m_data << ' ';
		travel = travel->m_previous;
	}

	cout << '\n';
}

#endif
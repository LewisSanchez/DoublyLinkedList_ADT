#ifndef NODE_H
#define NODE_H

template <typename T>
class DoubleLinkedList;

template <typename T>
class Node
{
	friend class DoubleLinkedList<T>;

	public:
		Node();
		Node(T data);
		Node(const Node & copy);
		~Node();
		Node & operator= (const Node & rhs);

		void setData(T data);
		T getData();
		void setNext(Node * next);
		Node * getNext();
		void setPrevious(Node * previous);
		Node * getPrevious();

	private:
		T m_data;
		Node * m_next;
		Node * m_previous;
};

template <typename T>
Node<T>::Node()
	: m_data(), m_next(nullptr), m_previous(nullptr)
{

}

template <typename T>
Node<T>::Node(T data)
	: m_data(data), m_next(nullptr), m_previous(nullptr)
{

}

template <typename T>
Node<T>::Node(const Node<T> & copy)
	: m_data(copy.m_data), m_next(copy.m_next), m_previous(copy.m_previous)
{

}

template <typename T>
Node<T>::~Node()
{
	m_data = 0;
	m_next = nullptr;
	m_previous = nullptr;
}

template <typename T>
Node<T> & Node<T>::operator= (const Node<T> & rhs)
{
	if (this != &rhs)
	{
		m_data = rhs.m_data;
		m_next = rhs.m_next;
		m_previous = rhs.m_previous;
	}

	return *this;
}

template <typename T>
void Node<T>::setData(T data)
{
	m_data = data;
}

template <typename T>
T Node<T>::getData()
{
	return m_data;
}

template <typename T>
void Node<T>::setNext(Node<T> * next)
{
	m_next = next;
}

template <typename T>
Node<T> * Node<T>::getNext()
{
	return m_next;
}

template <typename T>
void Node<T>::setPrevious(Node<T> * previous)
{
	m_previous = previous;
}

template <typename T>
Node<T> * Node<T>::getPrevious()
{
	return m_previous;
}

#endif
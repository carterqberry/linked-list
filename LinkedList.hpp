#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <string>
#include <sstream>

#include "LinkedListInterface.hpp"

using namespace std;

template<typename T>
struct Node {
	T value;
	Node<T>* prev;
	Node<T>* next;

	Node(const T& value, Node<T>* prev = nullptr, Node<T>* next = nullptr):
		value(value), prev(prev), next(next) {}
};

template<typename T>
class LinkedList : LinkedListInterface<T>
{
	private:
		Node<T>* head;
		Node<T>* tail;
		size_t length;
	public:
		LinkedList() :
		head(nullptr),
		tail(nullptr),
		length(0) {}

		LinkedList(const LinkedList& other);

		~LinkedList() {
			clear();
		}

		LinkedList<T>& operator=(const LinkedList<T>& other) {
			clear();

			LinkedList<T>* temp = new LinkedList<T>(other);
			swap(temp);
			return *this;
		}

		/** Insert Node(value) at beginning of linked list */
		virtual void push_front(const T& value) {
			Node<T>* new_head = new Node(value);
			new_head->next = head;
			if(head != nullptr) head->prev = new_head;
			head = new_head;
			if(tail == nullptr) tail = new_head;
			length++;
		}

		/** Remove Node at beginning of linked list */
		virtual void pop_front();

		/** Return reference to value of Node at beginning of linked list */
		virtual T& front()
		{
			return head->value;
		}

		/** Return true if linked list size == 0 */
		virtual bool empty() const {
			return length == 0;
		}

		/** Remove all Nodes with value from linked list */
		virtual void remove(const T& value);

		/** Remove all Nodes from linked list */
		virtual void clear();

		/** Reverse Nodes in linked list */
		virtual void reverse();

		/** Return the number of nodes in the linked list */
		virtual size_t size() const { return length; }

		/** Return contents of Linked List as a string */
		virtual std::string toString() const;

		/** BONUS ** Insert Node(value) at end of linked list */
		virtual void push_back(const T& value)
		{
			Node<T>* new_tail = new Node(value);
			new_tail->prev = tail;
			if(tail != nullptr) tail->next = new_tail;
			tail = new_tail;
			if(head == nullptr) head = new_tail;
			length++;
		}

		/** BONUS ** Remove Node at end of linked list */
		virtual void pop_back();

		/** BONUS ** Return reference to value of Node at end of linked list */
		virtual T& back()
		{
			return tail->value;
		}

		friend std::ostream& operator<<(ostream& os, const LinkedList<T>& list)
		{
			os << list.toString();
			return os;
		}
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	LinkedList<T> new_list;

	Node<T>* next = other.head;
	while(next != nullptr)
	{
		new_list->push_back(next->value);
		next = next->next;
	}

	swap(new_list);
}

template<typename T>
void LinkedList<T>::pop_front()
{
	if(head != nullptr && head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		length--;
	}
	else if(head != nullptr)
	{
		Node<T>* next = head->next;
		delete head;
		head = next;
		head->prev = nullptr;
		length--;
	}
}

template<typename T>
void LinkedList<T>::remove(const T& value)
{
	Node<T>* prev = nullptr;
	Node<T>* curr = head;

	while(curr != nullptr)
	{
		if(curr->value == value)
		{
			Node<T>* temp = curr->next;
			delete curr;
			curr = temp;

			if(curr != nullptr)
				curr->prev = prev;
			else
				tail = prev;
			
			if(prev != nullptr)
				prev->next = curr;
			else
				head = curr;
			length--;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

template<typename T>
void LinkedList<T>::clear()
{
	while(head != nullptr)
	{
		Node<T>* next = head->next;
		delete head;
		head = next;
	}

	head = nullptr;
	tail = nullptr;
	length = 0;
}

template<typename T>
void LinkedList<T>::reverse()
{
	Node<T>* next = head;
	while(next != nullptr)
	{
		Node<T>* temp = next->next;
		next->next = next->prev;
		next->prev = temp;

		next = next->prev;
	}
	
	Node<T>* temp = head;
	head = tail;
	tail = temp;
}

template<typename T>
std::string LinkedList<T>::toString() const
{
	ostringstream out("");
	
	Node<T>* next = head;
	while(next != nullptr)
	{
		out << next->value << " ";
		next = next->next;
	}

	return out.str();
}

template<typename T>
void LinkedList<T>::pop_back()
{
	if(tail != nullptr && head == tail)
	{
		delete tail;
		head = nullptr;
		tail = nullptr;
		length--;
	}
	else if(tail != nullptr)
	{
		Node<T>* prev = tail->prev;
		delete tail;
		tail = prev;
		tail->next = nullptr;
		length--;
	}
}

#endif // LINKED_LIST_HPP
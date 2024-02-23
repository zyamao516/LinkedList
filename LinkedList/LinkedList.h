#pragma once
#pragma once
#include "Node.h"
#include <vector>
#include <memory>

namespace linkedList {

	// Template Linked List class	
	template <typename T>
	class LinkedList {

		// Private variables head and tail pointers
		std::shared_ptr<node::Node<T>> Head = nullptr;
		std::shared_ptr<node::Node<T>> Tail = nullptr;
		// number of elements in the list
		int count = 0;

		// Private new element function 
		// Input:		reference type T Element
		// Output:		shared pointer to new Node with Element
		// Function:	Creates new node and returns a shared pointer to it
		inline std::shared_ptr<node::Node<T>> newElement(T& Element) {
			auto newNode = std::make_shared<node::Node<T>>(Element);
			return newNode;
		}
		inline std::shared_ptr<const node::Node<T>> getHead() const noexcept { return Head; }
		inline std::shared_ptr<const node::Node<T>> getTail() const noexcept { return Tail; }
	public:

		// Default constructor, defaults to initialised values of private variables
		LinkedList() = default;

		// 'copy' constructor, takes in vector of type T and copies it as linked list
		explicit LinkedList(const std::vector<T>& referenceVector) : count(referenceVector.size()) {
			for (const T& x : referenceVector) {
				addTail(x);
			}
		}

		// copy constructor, takes in a linked list of same type and copies nodes in linked list
		// Pointer copy creates shallow copy of list, Use with caution
		explicit LinkedList(const LinkedList<T>& referenceList, bool pointerCopy = false) {
			std::shared_ptr<node::Node<T>> iterator = referenceList.getHead();
			if (pointerCopy) {
				this->Head = referenceList.getHead();
				this->Tail = referenceList.getTail();
				this->count = referenceList.getcount();
				return;
			}
			while (iterator != nullptr) {
				this->addTail(iterator->getElement());
				this->count++;
				iterator = iterator->Next;
			}
		}

		~LinkedList() {
			if (!Head) { return; }
			std::shared_ptr<node::Node<T>> iterator = Head;
			for (int i = 0; i < count; i++) {
				iterator = iterator->Next;
				iterator->Prev.reset();
			}
			iterator.reset();
		}

		// Utility functions

		// Add new element at head of list
		// Input:		pointer to object of type T
		// Output:		void
		// Function:	adds new element of type T to head of the linked list
		void addHead(T& Element) {
			// new element created
			auto newNode = newElement(Element);
			// checks if list is empty
			if (!Head) {
				Head = Tail = newNode;
				return;
			}
			// sets pointers
			newNode->Next = Head;
			Head->Prev = newNode;
			Head = newNode;
			count++;
		}

		// Add new element at tail of list
		// Input:		pointer to object of type T
		// Output:		void
		// Function:	adds new element of type T to tail of the linked list
		void addTail(T& Element) {
			// new element created
			auto newNode = newElement(Element);
			// checks if list is empty
			if (!Head) {
				Head = Tail = newNode;
				return;
			}
			// sets pointers
			newNode->Next = nullptr;
			Tail->Prev = newNode;
			Tail = newNode;
			count++;
		}

		// Add new element at specified index of list
		// Input:		pointer to object of type T, index
		// Output:		void
		// Function:	adds new element of type T to index of the linked list
		void add(T& Element, int index) {
			if (index >= count || index < 0) { return; }
			count++;
			if (index == 0) { addHead(Element); return; }
			if (index == count - 1) { addTail(Element); return; }
			std::shared_ptr<node::Node<T>> iterator = getHead();
			auto newNode = newElement(Element);
			for (int i = 0; i < index; i++) {
				iterator = iterator->Next;
			}
			newNode->Next = iterator;
			newNode->Prev = iterator->Prev;
			newNode->Next->Prev = newNode;
			newNode->Prev->Next = newNode;

		}

		// Removes element at head of list
		// Input:		None
		// Output:		void
		// Function:	Removes element from head of list
		void removeHead() {
			if (!Head) { return; } // Returns if list is empty
			if (count == 1) { Tail = nullptr; } // sets tail to NULL if only 1 element in list
			std::shared_ptr<node::Node<T>> temp = Head;
			Head = Head->Next;
			temp.reset();
			count--;
		}

		// Removes element at tail of list
		// Input:		None
		// Output:		void
		// Function:	Removes element from tail of list
		void removeTail() {
			if (count == 0) { return; } // Returns if list is empty
			if (count == 1) { Head = nullptr; } // Sets tail to NULL if only 1 element in list
			std::shared_ptr<node::Node<T>> temp = Tail;
			Tail = Tail->Prev;
			temp.reset();
			count--;
		}

		// Removes element at index of list
		// Input:		int index
		// Output:		void
		// Function:	Removes element from index of list
		void remove(int index) {
			if (index >= count || index < 0) { return; }
			count--;
			if (index == 0) { removeHead(); return; }
			if (index == count - 1) { addTail(); return; }
			std::shared_ptr<node::Node<T>> iterator = getHead();
			for (int i = 0; i < index; i++) {
				iterator = iterator->Next;
			}
			iterator->Next->Prev = iterator->Prev;
			iterator->Prev->Next = iterator->Next;
			iterator.reset();

		}

		// check if element is in list
		// Input:		Reference to search element
		// Output:		Bool indicating 
		// Function:	Search list to see if element is in the array, if found returns true
		bool find(const T& searchElement) {
			if (isEmpty()) { return false; }
			std::shared_ptr<node::Node<T>> iterator = getHead();
			while (iterator != nullptr) {
				if (iterator->getElement() == searchElement) { return true; }
				iterator = iterator->Next;
			}
			return false;

		}

		// gets element from index
		// Input:		index to retrive from
		// Output:		Copy of element at index
		// Function:	Traverses list untill it reaches index, then returns value at index
		T getElement(int index) const {
			if (isEmpty() || index >= count || index < 0) { return nullptr; }
			std::shared_ptr<node::Node<T>> iterator = getHead();
			for (int i = 0; i < index; i++) {
				iterator = iterator->Next;
			}
			return iterator->getElement();
		}

		// sets value at node at index to new element
		// Input:		Reference to new element, index to set
		// Output:		void
		// Function:	Traverses list untill it reaches index, then replaces value at index
		void setElement(T& newElement, int index) {
			if (isEmpty() || index >= count || index < 0) { return; }
			std::shared_ptr<node::Node<T>> iterator = getHead();
			for (int i = 0; i < index; i++) {
				iterator->getElement();
			}
			iterator->setElement(newElement);
		}

		// Getter method to see how many elements are in list
		inline int getcount() const noexcept { return count; }
		inline bool isEmpty() const noexcept { return count == 0; }

	};


}
#pragma once
#include "Node.h"
#include <vector>
#include <memory>

namespace linkedList {

	// Template Linked List class	
	template <typename T>
	class LinkedList {

		// Private variables head and tail pointers
		std::unique_ptr<node::Node<T>> Head = nullptr;
		node::Node<T>* Tail = nullptr;
		// number of elements in the list
		int count = 0;

		// Private new element function 
		// Input:		reference type T Element
		// Output:		shared pointer to new Node with Element
		// Function:	Creates new node and returns a shared pointer to it
		inline std::unique_ptr<node::Node<T>> newElement(T& Element) {
			auto newNode = std::make_unique<node::Node<T>>(Element);
			return std::move(newNode);
		}

		inline void addEmpty(std::unique_ptr<node::Node<T>>&& newNode) { Head = std::move(newNode); Tail = Head.get(); }

		inline node::Node<T>* getHead() const noexcept { return Head.get(); }
		inline node::Node<T>* getTail() const noexcept { return Tail; }
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
		explicit LinkedList(const LinkedList<T>& referenceList) {
			node::Node<T>* iterator = referenceList.getHead();
			while (iterator != nullptr) {
				addTail(iterator->getElement());
				count++;
				iterator = iterator->Next;
			}
		}

		~LinkedList() { Head.reset(); }

		// Utility functions

		// Add new element at head of list
		// Input:		pointer to object of type T
		// Output:		void
		// Function:	adds new element of type T to head of the linked list
		void addHead(T& Element) {
			// new element created
			std::unique_ptr<node::Node<T>> newNode = newElement(Element);
			// checks if list is empty
			if (!Head) {
				addEmpty(std::move(newNode));
				return;
			}
			// sets pointers
			Head->Prev = newNode.get();
			newNode->Next = std::move(Head);
			Head = std::move(newNode);
			count++;
		}

		// Add new element at tail of list
		// Input:		pointer to object of type T
		// Output:		void
		// Function:	adds new element of type T to tail of the linked list
		void addTail(T& Element) {
			// new element created
			std::unique_ptr<node::Node<T>> newNode = newElement(Element);
			// checks if list is empty
			if (!Head) {
				addEmpty(std::move(newNode));
				return;
			}
			// sets pointers
			newNode->Prev = Tail;
			Tail->Next = std::move(newNode);
			Tail = Tail->Next.get();
			count++;
		}

		// Add new element at specified index of list
		// Input:		pointer to object of type T, index
		// Output:		void
		// Function:	adds new element of type T to index of the linked list
		void add(T& Element, int index) {
			if (index > count || index < 0) { return; } // Check for valid index
			if (index == 0) {
				addHead(Element); // Add at the head if index is 0
				return;
			}
			else if (index == count) {
				addTail(Element); // Add at the tail if index is equal to count
				return;
			}

			std::unique_ptr<node::Node<T>> newNode = newElement(Element); // Create the new node
			node::Node<T>* iterator = getHead();
			for (int i = 0; i < index - 1; ++i) { // Move to the node just before the index
				iterator = iterator->Next.get();
			}

			// Inserting newNode in between nodes
			newNode->Next = std::move(iterator->Next); // Set newNode's next to iterator's next
			if (newNode->Next) {
				newNode->Next->Prev = newNode.get(); // Set newNode as the previous of its next node
			}
			newNode->Prev = iterator; // Set newNode's prev to iterator
			iterator->Next = std::move(newNode); // Set iterator's next to newNode

			count++; // Increment count after insertion
		}


		// Removes element at head of list
		// Input:		None
		// Output:		void
		// Function:	Removes element from head of list
		void removeHead() {
			if (!Head) { return; } // Returns if list is empty
			if (count == 1) { Tail = nullptr; } // sets tail to NULL if only 1 element in list
			else { Head->Next->Prev = nullptr; }
			Head = std::move(Head->Next);
			count--;
		}

		// Removes element at tail of list
		// Input:		None
		// Output:		void
		// Function:	Removes element from tail of list
		void removeTail() {
			if (!Head) { return; } // Returns if list is empty
			if (count == 1) {
				Head.reset();
				Tail = nullptr;
				count--;
				return;
			}
			Tail = Tail->Prev;
			Tail->Next.reset();
			count--;
		}

		// Removes element at index of list
		// Input:		int index
		// Output:		void
		// Function:	Removes element from index of list
		void remove(int index) {
			if (index >= count || index < 0) { return; }
			if (index == 0) { removeHead(); return; }
			if (index == count - 1) { removeTail(); return; }
			node::Node<T>* iterator = getHead();
			for (int i = 0; i < index - 1; i++) {
				iterator = iterator->Next.get();
			}
			iterator->Next = std::move(iterator->Next->Next);
			iterator->Next->Prev = iterator;
			count--;
		}

		// check if element is in list
		// Input:		Reference to search element
		// Output:		Bool indicating 
		// Function:	Search list to see if element is in the array, if found returns true
		bool find(const T& searchElement) {
			if (isEmpty()) { return false; }
			node::Node<T>* iterator = getHead();
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
		T& getElement(int index) const {
			if (isEmpty() || index >= count || index < 0) { throw std::out_of_range("Index is out of range"); }
			node::Node<T>* iterator = getHead();
			for (int i = 0; i < index; i++) {
				iterator = iterator->Next.get();
			}
			return iterator->getElement();
		}

		// sets value at node at index to new element
		// Input:		Reference to new element, index to set
		// Output:		void
		// Function:	Traverses list untill it reaches index, then replaces value at index
		void setElement(T& newElement, int index) {
			if (isEmpty() || index >= count || index < 0) { return; }
			node::Node<T>* iterator = getHead();
			for (int i = 0; i < index; i++) { iterator = iterator->Next.get(); }
			iterator->setElement(newElement);
		}

		// Getter method to see how many elements are in list
		inline int getcount() const noexcept { return count; }
		inline bool isEmpty() const noexcept { return count == 0; }

	};


}

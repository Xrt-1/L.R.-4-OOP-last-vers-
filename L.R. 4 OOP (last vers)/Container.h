#pragma once
#include "CCircle.h"
class circles {
private:
	class Node {
	public:
		CCircle* value;
		Node* nextNode;
		Node(CCircle& circle, Node* nxt = nullptr) {
			value = &circle;
			nextNode = nxt;
		}
		~Node() {
			delete value;
			nextNode = nullptr;
		}
	};
	Node* first;
	Node* current;
	Node* last;//доделать определение last
	int size;
public:
	circles() {
		last = current = first = nullptr;
		size = 0;
	}
	CCircle* getCurrent() {
		if (current->value!= nullptr) return (current->value);
	}
	CCircle* getLast() {
		if (last != nullptr) return (last->value);
		else return nullptr;
	}
	int getSize() {
		return size;
	}
	void next() {
		if (current != nullptr) {
			current = current->nextNode;
		}
	}
	void resetCurrent() {
		current = first;
	}
	void push_back(CCircle* cr) {
		Node* newNode = new Node(*cr);
		if (first == nullptr) { 
			first = newNode;
			last = newNode;
		}
		else {
			last->nextNode = newNode; 
			last = newNode;  
		}
		size++;
	}
	Node* prev(Node* cr) {
		current = first;
		for (int i = 0; i < size; i++) {
			Node* prevNode = nullptr;
			Node* r = first;
			while (r != nullptr) {
				if (r->nextNode == cr) {
					prevNode = r;
					break;
				}
				r = r->nextNode;
			}
			return prevNode;
		}
	}
	void del(CCircle* c) {
		if (c == nullptr || first == nullptr) return;
		Node* r = first;
		while (r != nullptr) {
			if (r->value == c) {
				Node* p = prev(r);
				if (p == nullptr) {
					if (current == first) current = first->nextNode;
					if (last == first) last = nullptr;
					Node* nxt = first->nextNode;
					delete first;
					first = nxt;
					return;
				}
				else {
					if (current == r) current = current->nextNode;
					if (last == r) last = p;
					p->nextNode = r->nextNode;
					delete r;
					return;
				}
			}
			r = r->nextNode;
		}
	}
	void deleteCurrent() {
		if (current == nullptr) return;

		Node* r = first;
		if (current == first) {
			first = first->nextNode;
			delete current;
			current = first;
			if (size == 1) last = current;

		}
		else if(current == last) {
			r = prev(last);
			delete last;
			last = r;
			last->nextNode = current = nullptr;
		}
		else {
			while (r->nextNode != current) {
				r = r->nextNode;
			}
			if (r != nullptr) {
				r->nextNode = current->nextNode;
				delete current;
				current = r->nextNode;
			}
		}
		size--;
	}
		
		
	void unselect(System::Drawing::Graphics^ g) {
		current = first;
		while (current != nullptr) {
			if ((current->value)->getIsSlctd()) {
				current->value->setIsSlctd(false);
				current->value->Bleach(g);
				current->value->Draw(g);
			}
			next();
		}
	}
	void unClick(System::Drawing::Graphics^ g) {
		current = first;
		while (current != nullptr) {
			if ((current->value)->isClicked) {
				current->value->setIsSlctd(false);
				current->value->isClicked = false;
				current->value->Bleach(g);
				current->value->Draw(g);
			}
			next();
		}
	}
	void DrawAll(System::Drawing::Graphics^ g) {
		current = first;
		while (current != nullptr) {
			(current->value)->Draw(g);
			next();
		}
	}
	void deleteSlctd(System::Drawing::Graphics^ g) {
		current = first;
		while (current != nullptr) {
			if (current->value->getIsSlctd()) {
				current->value->Bleach(g);
				deleteCurrent();
			}
			else next();
		}
	}

};
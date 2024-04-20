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
	int size;
public:
	CCircle* last = nullptr;
	circles() {
		current = first = nullptr;
		size = 0;
		//System::Drawing::SolidBrush^ brushUnSlctd = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Gray);
		///System::Drawing::Graphics^ g = pBox->CreateGraphics();
		//System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::BlueViolet);
	}
	CCircle* getCurrent() {
		return (current->value);
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
		resetCurrent();
		if (first == nullptr) {
			first = new Node(*cr);
			current = first;
		}
		else {
			while (current->nextNode != nullptr) {
				next();

			}
			current->nextNode = new Node(*cr);
		}
		size++;
		resetCurrent();
		last = cr;
	}
	void deleteCurrent() {
		if (last == current->value) last = nullptr;
		if (current == first) {
			first = first->nextNode;
			delete current;
			current = first;
			size--;
		}
		else if (current != nullptr) {
			Node* nxt = current->nextNode;
			Node* oldCur = current;
			resetCurrent();
			while (current != nullptr) {
				if (current->nextNode == oldCur) {
					current->nextNode = nxt;
					delete oldCur;
					break;
				}
				next();
			}
			current = nxt;
			size--;
		}
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
		last = nullptr;
	}

};
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
	circles(System::Windows::Forms::PictureBox^ pBox) {
		current = first = nullptr;
		size = 0;
		System::Drawing::SolidBrush^ brushUnSlctd = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Gray);
		System::Drawing::Graphics^ g = pBox->CreateGraphics();
		System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::BlueViolet);
	}
	CCircle* getCurrent() {
		return (current->value);
	}
	void next() {
		if (current != nullptr) {
			current = current->nextNode;
		}
	}
	void resetCurrent() {
		current = first;
	}
	void push_back(CCircle& cr) {
		if (first == nullptr) {
			first = new Node(cr);
			current = first;
		}
		else {
			while (current->nextNode != nullptr) {
				next();

			}
			current->nextNode = new Node(cr);
		}
		size++;
		resetCurrent();
	}
	void deleteCurrent() {
		if (current->nextNode == nullptr) {
			delete current;
			current = nullptr;
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
			}
			current = current->nextNode;
			size--;
		}
	}

};
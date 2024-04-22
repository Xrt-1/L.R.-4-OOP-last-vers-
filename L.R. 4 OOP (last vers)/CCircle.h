#pragma once
#include <iostream>
#include "MyForm.h"

class CCircle {
private:
	int x, y, r;
	bool isSelected;
	void DrawUnSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Gray)) {
		g->FillEllipse(brush, x, y, r * 2, r * 2);
	}
	void DrawSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::BlueViolet)) {
		g->FillEllipse(brush, x, y, r * 2, r * 2);
	}
public:
	bool isClicked;
	CCircle(int _x, int _y) {
		r = 20;
		x = _x - r;
		y = _y - r;
		isClicked = false;
	}
	CCircle(int x, int y, bool slctd) : CCircle(x, y) {
		isSelected = slctd;
	}
	void setIsSlctd(bool slctd) {
		isSelected = slctd;
	}
	bool getIsSlctd() {
		return isSelected;
	}
	bool isPointInC(int x1, int y1) {
		int distanceSquared = (x1 - (x + r)) * (x1 - (x + r)) + (y1 - (y + r)) * (y1 - (y + r));
		return distanceSquared <= r * r;
	}
	void Draw(System::Drawing::Graphics^ g) {
		if (this->isSelected) DrawSlctd(g);
		else DrawUnSlctd(g);
	}
	void Bleach(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::White)) {
		g->FillEllipse(brush, x, y, r * 2, r * 2);
	}
	
};
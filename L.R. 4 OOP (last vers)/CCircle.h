#pragma once
#include <iostream>
#include "MyForm.h"

class CCircle {
private:
	int x, y, r;
	bool isSelected, isDrawed;
public:
	CCircle(int _x, int _y) {
		r = 20;
		x = _x - r;
		y = _y - r;
	}
	CCircle(int x, int y, bool slctd) : CCircle(x, y) {
		isSelected = slctd;
	}
	void DrawUnSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Gray)) {
		g->FillEllipse(brush, x, y, r * 2, r * 2);
		this->isDrawed = true;
	}
	void DrawSlctd(System::Drawing::Graphics^ g, System::Drawing::SolidBrush^ brush = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Violet)) {
		g->FillEllipse(brush, x, y, r * 2, r * 2);
		this->isDrawed = true;
	}
};
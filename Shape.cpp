#include "pch.h"
#include "Shape.h"

namespace ASMPT
{
	/* Shape */
	Shape::Shape(float value, uint32_t width, uint32_t height, ShapeColor color) {
		value_ = value;
		width_ = width;
		height_ = height;
		color_ = color;
	}

	ShapeValue Shape::GetValue() {
		return value_;
	}

	uint32_t Shape::GetWidth() {
		return width_;
	}

	uint32_t Shape::GetHeight() {
		return height_;
	}

	ShapeColor Shape::GetColor() {
		return color_;
	}


	/* Rectangle */
	Rectangle::Rectangle(float value, uint32_t width, uint32_t height, ShapeColor color) :Shape(value, width, height, color) {}

	ShapeType Rectangle::GetType() {
		return ShapeType::ShapeRectangle;
	}

	void Rectangle::Draw(int x, int y, CDC* cdc) {
		// set color
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetColor() == Red ? 255 : 0, GetColor() == Green ? 255 : 0, GetColor() == Blue ? 255 : 0));
		cdc->SelectObject(brush);

		// draw shape
		uint32_t w = GetWidth(), h = GetHeight();
		cdc->Rectangle(x - w / 2, y - h / 2, x + w / 2, y + h / 2);

		// set content
		CString content;
		content.Format(_T("%.3f"), GetValue());
		cdc->TextOutW(x, y, content);
	}

	/* Square */
	Square::Square(float value, uint32_t size, ShapeColor color) :Shape(value, size, size, color) {}

	ShapeType Square::GetType() {
		return ShapeType::ShapeSquare;
	}

	void Square::Draw(int x, int y, CDC* cdc) {
		
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetColor() == Red ? 255 : 0, GetColor() == Green ? 255 : 0, GetColor() == Blue ? 255 : 0));
		cdc->SelectObject(brush);

		uint32_t w = GetWidth(), h = GetHeight();
		cdc->Rectangle(x - w / 2, y - h / 2, x + w / 2, y + h / 2);

		CString content;
		content.Format(_T("%.3f"), GetValue());
		cdc->TextOutW(x, y, content);
	}

	/* Circle */
	Circle::Circle(float value, uint32_t r, ShapeColor color) :Shape(value, 2 * r, 2 * r, color) {}

	ShapeType Circle::GetType() {
		return ShapeType::ShapeCircle;
	}

	void Circle::Draw(int x, int y, CDC* cdc) {
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetColor() == Red ? 255 : 0, GetColor() == Green ? 255 : 0, GetColor() == Blue ? 255 : 0));
		cdc->SelectObject(brush);

		uint32_t r = GetWidth() / 2;
		cdc->Ellipse(x - r, y - r, x + r, y + r);

		CString content;
		content.Format(_T("%.3f"), GetValue());
		cdc->TextOutW(x, y, content);
	}
}
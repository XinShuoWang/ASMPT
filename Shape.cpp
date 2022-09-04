#include "pch.h"
#include "Shape.h"

namespace ASMPT
{
	/* Shape */
	Shape::Shape(ShapeValue value, uint32_t width, uint32_t height, ShapeColor color) {
		value_ = value;
		width_ = width;
		height_ = height;
		color_ = color;
	}

	ShapeValue Shape::GetValue() const {
		return value_;
	}

	uint32_t Shape::GetWidth() const {
		return width_;
	}

	uint32_t Shape::GetHeight() const {
		return height_;
	}

	ShapeColor Shape::GetColor() const {
		return color_;
	}

	Center Shape::GetCenter() const {
		return center_;
	}

	void Shape::SetCenter(Center& center) {
		center_ = center;
	}

	/* Rectangle */
	Rectangle::Rectangle(ShapeValue value, uint32_t width, uint32_t height, ShapeColor color) : Shape(value, width, height, color) {}

	ShapeType Rectangle::GetType() {
		return ShapeType::ShapeRectangle;
	}

	void Rectangle::Draw(CDC* cdc) {
		// set color
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetColor() == Red ? 255 : 0,
			GetColor() == Green ? 255 : 0,
			GetColor() == Blue ? 255 : 0));
		cdc->SelectObject(brush);

		// draw shape
		uint32_t w = GetWidth(), h = GetHeight();
		if (!GetCenter().IsSet()) return;
		uint32_t x = GetCenter().GetX(), y = GetCenter().GetY();
		cdc->Rectangle(x - w / 2, y - h / 2, x + w / 2, y + h / 2);

		// set content
		CString content;
		content.Format(_T("%.3f"), GetValue());
		cdc->TextOutW(x, y, content);
	}

	bool Rectangle::ContainPoint(int x, int y) {
		uint32_t w = GetWidth(), h = GetHeight();
		if (!GetCenter().IsSet()) return false;
		uint32_t center_x = GetCenter().GetX(), center_y = GetCenter().GetY();
		return x < center_x + w / 2 && x > center_x - w / 2 && y < center_y + h / 2 && y > center_y - h / 2;
	}

	/* Square */
	Square::Square(ShapeValue value, uint32_t size, ShapeColor color) : Shape(value, size, size, color) {}

	ShapeType Square::GetType() {
		return ShapeType::ShapeSquare;
	}

	void Square::Draw(CDC* cdc) {
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetColor() == Red ? 255 : 0,
			GetColor() == Green ? 255 : 0,
			GetColor() == Blue ? 255 : 0));
		cdc->SelectObject(brush);

		uint32_t w = GetWidth(), h = GetHeight();
		if (!GetCenter().IsSet()) return;
		uint32_t x = GetCenter().GetX(), y = GetCenter().GetY();
		cdc->Rectangle(x - w / 2, y - h / 2, x + w / 2, y + h / 2);

		CString content;
		content.Format(_T("%.3f"), GetValue());
		cdc->TextOutW(x, y, content);
	}

	bool Square::ContainPoint(int x, int y) {
		uint32_t w = GetWidth(), h = GetHeight();
		if (!GetCenter().IsSet()) return false;
		uint32_t center_x = GetCenter().GetX(), center_y = GetCenter().GetY();
		return x < center_x + w / 2 && x > center_x - w / 2 && y < center_y + h / 2 && y > center_y - h / 2;
	}

	/* Circle */
	Circle::Circle(ShapeValue value, uint32_t r, ShapeColor color) :
		Shape(value, 2 * r, 2 * r, color) {}

	ShapeType Circle::GetType() {
		return ShapeType::ShapeCircle;
	}

	void Circle::Draw(CDC* cdc) {
		CBrush brush;
		brush.CreateSolidBrush(RGB(GetColor() == Red ? 255 : 0,
			GetColor() == Green ? 255 : 0,
			GetColor() == Blue ? 255 : 0));
		cdc->SelectObject(brush);

		uint32_t r = GetWidth() / 2;
		if (!GetCenter().IsSet()) return;
		uint32_t x = GetCenter().GetX(), y = GetCenter().GetY();
		cdc->Ellipse(x - r, y - r, x + r, y + r);

		CString content;
		content.Format(_T("%.3f"), GetValue());
		cdc->TextOutW(x, y, content);
	}

	bool Circle::ContainPoint(int x, int y) {
		uint32_t r = GetWidth();
		if (!GetCenter().IsSet()) return false;
		uint32_t center_x = GetCenter().GetX(), center_y = GetCenter().GetY();
		return (center_x - x) * (center_x - x) + (center_y - y) * (center_y - y) < r * r;
	}
}
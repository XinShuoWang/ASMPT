#pragma once

#include "Shape.h"
#include "Direction.h"

#include <cstdint>
#include <bitset>


namespace ASMPT
{
	typedef int32_t Reference;

	static const int INIT_WIDTH = 100;
	static const int INIT_HEIGHT = 100;
	static const ShapeType INIT_SHAPE_TYPE = ShapeType::ShapeRectangle;
	static const InsertDirection INIT_DIRECTION = InsertDirection::Before;
	static const Reference INIT_REFERENCE = -1;
	static const ShapeColor INIT_COLOR = ShapeColor::Green;

	static const int DEFAULT_WIDTH = INIT_WIDTH;
	static const int DEFAULT_HEIGHT = INIT_HEIGHT;
	static const ShapeType DEFAULT_SHAPE_TYPE = INIT_SHAPE_TYPE;
	static const InsertDirection DEFAULT_DIRECTION = INIT_DIRECTION;
	static const Reference DEFAULT_REFERENCE = INIT_REFERENCE;
	static const ShapeColor DEFAULT_COLOR = INIT_COLOR;

	static const int SIZE_START = 50;
	static const int SIZE_END = 150;
	static const int SIZE_STEP = 10;
}


namespace ASMPT
{
	struct InsertEventOption {
		ShapeType shape_type_;
		InsertDirection dir_;
		ShapeColor color_;
		Reference reference_;
		uint32_t width_;
		uint32_t height_;

		// Default construct function
		InsertEventOption() {
			shape_type_ = INIT_SHAPE_TYPE;
			dir_ = INIT_DIRECTION;
			reference_ = INIT_REFERENCE;
			width_ = INIT_WIDTH;
			height_ = INIT_HEIGHT;
			color_ = INIT_COLOR;
		}
	};

	struct DeleteEventOption {
		// Record the selection in the IDC_DEL_REFERENCE ListBox
		Reference reference_;

		// Default construct function
		DeleteEventOption() {
			reference_ = INIT_REFERENCE;
		}
	};
}
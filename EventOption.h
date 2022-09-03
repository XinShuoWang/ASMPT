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

	static const int SIZE_START = 50;
	static const int SIZE_END = 150;
	static const int SIZE_STEP = 10;
}


namespace ASMPT
{
	struct AddEventOption {
		ShapeType shape_type_;
		InsertDirection dir_;
		ShapeColor color_;
		Reference reference_;
		uint32_t width_;
		uint32_t height_;

		// Default construct function
		AddEventOption() {
			shape_type_ = INIT_SHAPE_TYPE;
			dir_ = INIT_DIRECTION;
			reference_ = INIT_REFERENCE;
			width_ = INIT_WIDTH;
			height_ = INIT_HEIGHT;
			color_ = INIT_COLOR;
		}
	};

	struct DelEventOption {
		// Record the selection in the IDC_DEL_REFERENCE ListBox
		Reference reference_;

		// Default construct function
		DelEventOption() {
			reference_ = INIT_REFERENCE;
		}
	};
}
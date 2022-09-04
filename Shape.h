#pragma once

namespace ASMPT
{
	// Graphical shape constructed at initialization time
	class Rectangle;
	typedef Rectangle DefaultShape;

	struct Point;
	typedef Point Center;

	// Rename the value inside the graph to ShapeValue
	typedef float ShapeValue;

	static const ShapeValue DEFAULT_SHAPE_VALUE = 0.0;
}

namespace ASMPT
{
	// Support three colors of red, green and blue
	enum ShapeColor {
		Red = 0,
		Green,
		Blue
	};

	// Support rectangle, square, prototype three shapes
	enum ShapeType {
		ShapeRectangle = 0,
		ShapeSquare,
		ShapeCircle,
	};

	/*
	 * Abstraction of "dots" in graphical interface
	 *
	 * There is also a boolean variable `is_set_` to indicate whether 
	 * the result within this data structure is valid
	 */
	struct Point {
	private:
		uint32_t x_, y_;
		bool is_set_;

	public:
		Point() {
			x_ = 0, y_ = 0;
			is_set_ = false;
		}

		Point(uint32_t x, uint32_t y) {
			x_ = x, y_ = y;
			is_set_ = true;
		}

		// Before calling the Get function, you must first call IsSet to judge
		uint32_t GetX() const {
			return x_;
		}

		// Before calling the Get function, you must first call IsSet to judge
		uint32_t GetY() const {
			return y_;
		}

		void Set(uint32_t x, uint32_t y) {
			x_ = x, y_ = y;
			is_set_ = true;
		}

		bool IsSet() const {
			return is_set_;
		}
	};

	/*
	 * In order to facilitate the subsequent spacing adjustment action, each figure is abstracted as a rectangle
	 */
	class Shape {
	protected:
		ShapeValue value_;
		uint32_t width_, height_;
		Center center_;
		ShapeColor color_;
	public:
		Shape(ShapeValue value, uint32_t width, uint32_t height, ShapeColor color);
		virtual ~Shape() {};
		virtual ShapeValue GetValue() const;
		virtual uint32_t GetWidth() const;
		virtual uint32_t GetHeight() const;
		virtual ShapeColor GetColor() const;

		// Shape's center of gravity
		virtual Center GetCenter() const;
		virtual void SetCenter(Center& center);

		// Every subclass of Shape needs to implement this function
		virtual ShapeType GetType() = 0;

		/*
		 * Every subclass of Shape needs to implement this function
		 *
		 * x, y represent the barycentric coordinates of the graph when drawing
		 * cdc is the pointer used for drawing in the MFC framework
		 *
		 */
		virtual void Draw(CDC* cdc) = 0;

		// This function is used to determine whether a point is inside the graph
		virtual bool ContainPoint(int x, int y) = 0;
	};

	class Rectangle : public Shape {
	public:
		Rectangle(ShapeValue value, uint32_t width, uint32_t height, ShapeColor color);
		~Rectangle() override {};
		ShapeType GetType() override;
		void Draw(CDC* cdc) override;
		bool ContainPoint(int x, int y) override;
	};


	class Square : public Shape {
	public:
		Square(ShapeValue value, uint32_t size, ShapeColor color);
		~Square() override {};
		ShapeType GetType() override;
		void Draw(CDC* cdc) override;
		bool ContainPoint(int x, int y) override;
	};

	class Circle : public Shape {
	public:
		Circle(ShapeValue value, uint32_t r, ShapeColor color);
		~Circle() override {};
		ShapeType GetType() override;
		void Draw(CDC* cdc) override;
		bool ContainPoint(int x, int y) override;
	};
}
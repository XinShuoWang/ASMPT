#pragma once

namespace ASMPT
{
	// Graphical shape constructed at initialization time
	class Rectangle;
	typedef Rectangle DefaultShape;

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
	 * In order to facilitate the subsequent spacing adjustment action, each figure is abstracted as a rectangle
	 */
	class Shape {
	protected:
		ShapeValue value_;
		uint32_t width_;
		uint32_t height_;
		ShapeColor color_;
	public:
		Shape(ShapeValue value, uint32_t width, uint32_t height, ShapeColor color);
		virtual ~Shape() {};
		virtual ShapeValue GetValue();
		virtual uint32_t GetWidth();
		virtual uint32_t GetHeight();
		virtual ShapeColor GetColor();

		// Every subclass of Shape needs to implement this function
		virtual ShapeType GetType() = 0;

		/*
		 * Every subclass of Shape needs to implement this function
		 *
		 * x, y represent the barycentric coordinates of the graph when drawing
		 * cdc is the pointer used for drawing in the MFC framework
		 * 
		 */ 
		virtual void Draw(int x, int y, CDC* cdc) = 0;
	};

	class Rectangle : public Shape {
	public:
		Rectangle(ShapeValue value, uint32_t width, uint32_t height, ShapeColor color);
		~Rectangle() override {};
		ShapeType GetType() override;
		void Draw(int x, int y, CDC* cdc) override;
	};


	class Square : public Shape {
	public:
		Square(ShapeValue value, uint32_t size, ShapeColor color);
		~Square() override {};
		ShapeType GetType() override;
		void Draw(int x, int y, CDC* cdc) override;
	};

	class Circle : public Shape {
	public:
		Circle(ShapeValue value, uint32_t r, ShapeColor color);
		~Circle() override {};
		ShapeType GetType() override;
		void Draw(int x, int y, CDC* cdc) override;
	};
}
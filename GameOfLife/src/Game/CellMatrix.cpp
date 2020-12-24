#include "Game/CellMatrix.h"

gol::CellMatrix::CellMatrix(size_t width, size_t height) :
	Matrix(width, height,
	       [](size_t, size_t)
	       {
		       return Cell();
	       })
{
	this->reset();
}

void gol::CellMatrix::reset()
{
	this->forEach([](size_t, size_t, Cell& cell)
	{
		cell = Cell();
	});
}

void gol::CellMatrix::setCell(Vector2s position, const bool value)
{
	this->at(position).isAlive = value;
}

Cell gol::CellMatrix::getCell(Vector2s position)
{
	return this->at(position);
}

size_t gol::CellMatrix::width() const
{
	return _width;
}

size_t gol::CellMatrix::height() const
{
	return _height;
}

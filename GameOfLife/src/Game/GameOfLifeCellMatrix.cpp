#include "Game/GameOfLifeCellMatrix.h"

static std::vector<gol::Vector2s> CreateAliveCellsPositionsArray(size_t reserveSize)
{
	std::vector<gol::Vector2s> vector;
	if (reserveSize)
		vector.reserve(reserveSize);
	return vector;
}

gol::GameOfLifeCellMatrix::GameOfLifeCellMatrix(size_t width, size_t height) : CellMatrix(width, height)
{
	this->_aliveCellsPositions = CreateAliveCellsPositionsArray(width * height);
}

void gol::GameOfLifeCellMatrix::setCell(gol::Vector2s position, bool value)
{
	CellMatrix::setCell(position, value);
	
	const auto value_pos = 
		std::find(this->_aliveCellsPositions.begin(), this->_aliveCellsPositions.end(), position);
	const auto exists = 
		value_pos != this->_aliveCellsPositions.end();
	
	if (value && !exists)
		this->_aliveCellsPositions.emplace_back(position);
	else if (!value && exists)
		this->_aliveCellsPositions.erase(value_pos);
}

void gol::GameOfLifeCellMatrix::countNeighboursCount()
{
	this->resetCellsNeighboursCount();

	for (auto const& value : this->_aliveCellsPositions)
	{
		for (int xOffset = -1; xOffset <= 1; xOffset++)
			for (int yOffset = -1; yOffset <= 1; yOffset++)
			{
				if (
					(xOffset == 0 && yOffset == 0) ||
					(static_cast<size_t>(value.x) + xOffset >= this->_width) ||
					(value.x + xOffset < 0) ||
					(static_cast<size_t>(value.y) + yOffset >= this->_height) ||
					(value.y + yOffset < 0))
					continue;

				this->at(value.x + xOffset, value.y + yOffset).neighboursCount++;
			}
	}
}

void gol::GameOfLifeCellMatrix::applyRule()
{
	this->_aliveCellsPositions = CreateAliveCellsPositionsArray(this->_width * this->_height);

	for (size_t x = 0; x < this->_width; x++)
	{
		for (size_t y = 0; y < this->_height; y++)
		{
			bool newState = false;

			auto& cell = this->at(x, y);

			if (cell.isAlive && (cell.neighboursCount == 3 || cell.neighboursCount == 2)) newState = true;
			if (!cell.isAlive && cell.neighboursCount == 3) newState = true;

			cell.isAlive = newState;

			if (newState)
				_aliveCellsPositions.emplace_back(x, y);
		}
	}
}

void gol::GameOfLifeCellMatrix::resetCellsNeighboursCount()
{
	this->forEach([](size_t, size_t, Cell& cell)
		{
			cell.neighboursCount = 0;
		});
}

void gol::GameOfLifeCellMatrix::step()
{
	this->countNeighboursCount();
	this->applyRule();
}

std::vector<gol::Vector2s> gol::GameOfLifeCellMatrix::getCellsToRenderPositions() const
{
	return this->_aliveCellsPositions;
}

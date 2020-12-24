#pragma once
#include <mutex>
#include "CellMatrix.h"

namespace gol
{
	class GameOfLifeCellMatrix : public CellMatrix
	{
	protected:
		std::vector<Vector2s> _aliveCellsPositions;

		void countNeighboursCount();
		void applyRule();
		void resetCellsNeighboursCount();
	public:
		GameOfLifeCellMatrix(size_t width, size_t height);

		void setCell(Vector2s position, bool value) override;
		void step() override;
		std::vector<Vector2s> getCellsToRenderPositions() const override;
	};
}

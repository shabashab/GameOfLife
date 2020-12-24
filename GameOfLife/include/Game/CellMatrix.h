#pragma once
#include <vector>

#include "Utils/Vector2.h"
#include "Utils/Matrix.h"
#include "Game/Cell.h"

namespace gol
{
	class CellMatrix : protected Matrix<Cell>
	{
	public:
		CellMatrix(size_t width, size_t height);
		virtual ~CellMatrix() = default;

		void reset();
		virtual void setCell(Vector2s position, bool value);
		virtual Cell getCell(Vector2s position);
		
		virtual std::vector<Vector2s> getCellsToRenderPositions() const = 0;
		virtual void step() = 0;

		size_t width() const override;
		size_t height() const override;
	};
}

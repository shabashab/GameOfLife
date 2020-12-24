#include "Graphics/CellMatrixRenderer.h"


gol::CellMatrixRenderer::CellMatrixRenderer(std::shared_ptr<CellMatrix> matrix, Vector2s cellSize,
                                            olc::Pixel aliveCellColor)
{
	this->_cellMatrix = matrix;
	this->_cellSize = cellSize;
	this->_aliveCellColor = aliveCellColor;
}

void gol::CellMatrixRenderer::render(olc::PixelGameEngine& engine)
{
	for (auto& value : _cellMatrix->getCellsToRenderPositions())
	{
		engine.FillRect(
			value.x * this->_cellSize.x,
			value.y * this->_cellSize.y,
			this->_cellSize.x,
			this->_cellSize.y,
			this->_aliveCellColor);
	}
}

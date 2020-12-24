#include "Graphics/GridRenderer.h"

void gol::GridRenderer::drawVerticalLines(
	olc::PixelGameEngine& engine) const
{
	for (auto x = 0; x < this->_gridSize.x; x += this->_cellSize.x)
	{
		engine.DrawLine(x, 0, x, this->_gridSize.y, this->_color);
	}
}

void gol::GridRenderer::drawHorizontalLines(
	olc::PixelGameEngine& engine) const
{
	for (auto y = 0; y < this->_gridSize.y; y += this->_cellSize.y)
	{
		engine.DrawLine(0, y, this->_gridSize.x, y, this->_color);
	}
}

gol::GridRenderer::GridRenderer(Vector2s cellSize, Vector2s gridSize, olc::Pixel color)
{
	this->_cellSize = cellSize;
	this->_gridSize = gridSize;
	this->_color = color;
}

void gol::GridRenderer::render(olc::PixelGameEngine& engine)
{
	this->drawHorizontalLines(engine);
	this->drawVerticalLines(engine);
}

#include "Game/GameOfLife.h"
#include "Game/GameOfLifeCellMatrix.h"

void GameOfLife::fillCellByCursorPos(const gol::Vector2s cursorPosition, bool newValue)
{
	const gol::Vector2s cell_position(
		cursorPosition.x / this->_cellSize.x,
		cursorPosition.y / this->_cellSize.y
	);
	this->_cellMatrix->setCell(cell_position, newValue);
}

gol::Vector2s GameOfLife::getMousePositionVector() const
{
	return {static_cast<size_t>(this->GetMouseX()), static_cast<size_t>(this->GetMouseY())};
}

GameOfLife::GameOfLife()
{
	this->_cellSize = gol::Vector2s(20, 20);
}

bool GameOfLife::OnUserCreate()
{
	this->_cellMatrix =
		std::make_shared<gol::GameOfLifeCellMatrix>(500, 500);

	this->_cellMatrixRenderer =
		std::make_unique<gol::CellMatrixRenderer>(this->_cellMatrix, this->_cellSize, olc::BLACK);

	this->_gridRenderer =
		std::make_unique<gol::GridRenderer>(
			this->_cellSize,
			gol::Vector2s(this->ScreenWidth(), this->ScreenHeight()),
			olc::GREY);

	return true;
}

bool GameOfLife::OnUserUpdate(float fDeltaTime)
{
	Clear(olc::WHITE);

	if (this->_renderGrid)
		this->_gridRenderer->render(*this);

	if (GetMouse(0).bPressed)
	{
		this->fillCellByCursorPos(this->getMousePositionVector(), true);
	}

	if (GetMouse(1).bPressed)
	{
		this->fillCellByCursorPos(this->getMousePositionVector(), false);
	}

	if (GetKey(olc::RIGHT).bHeld)
	{
		_cellMatrix->step();
	}

	if (GetKey(olc::A).bPressed)
	{
		this->_renderGrid = !this->_renderGrid;
	}

	if (GetKey(olc::C).bPressed)
	{
		_cellMatrix->reset();
	}

	this->_cellMatrixRenderer->render(*this);

	return true;
}

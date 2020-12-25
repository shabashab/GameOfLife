#include "Game/GameOfLife.h"
#include "Game/GameOfLifeCellMatrix.h"

void gol::GameOfLife::fillCellByCursorPos(const Vector2s cursorPosition, bool newValue) const
{
	const Vector2s cell_position(
		cursorPosition.x / this->_cellSize.x,
		cursorPosition.y / this->_cellSize.y
	);
	this->_cellMatrix->setCell(cell_position, newValue);
}

gol::Vector2s gol::GameOfLife::getMousePositionVector() const
{
	return {static_cast<size_t>(this->GetMouseX()), static_cast<size_t>(this->GetMouseY())};
}

gol::GameOfLife::GameOfLife() : _cellSize(20, 20)
{
}

bool gol::GameOfLife::OnUserCreate()
{
	this->_cellMatrix =
		std::make_shared<GameOfLifeCellMatrix>(500, 500);

	this->_cellMatrixRenderer =
		std::make_unique<CellMatrixRenderer>(this->_cellMatrix, this->_cellSize, olc::BLACK);

	this->_gridRenderer =
		std::make_unique<GridRenderer>(
			this->_cellSize,
			Vector2s(this->ScreenWidth(), this->ScreenHeight()),
			olc::GREY);

	return true;
}

bool gol::GameOfLife::OnUserUpdate(float fDeltaTime)
{
	Clear(olc::WHITE);

	if (this->_renderGrid)
		this->_gridRenderer->render(*this);

	if (this->_isPlaying)
	{
		_playingTime += fDeltaTime;

		if (_playingTime > 0.5f)
		{
			this->_cellMatrix->step();
			_playingTime = 0;
		}
	}
	else
	{
		if (GetMouse(0).bPressed)
			this->fillCellByCursorPos(this->getMousePositionVector(), true);

		if (GetMouse(1).bPressed)
			this->fillCellByCursorPos(this->getMousePositionVector(), false);

		if (GetKey(olc::RIGHT).bHeld)
			_cellMatrix->step();

		if (GetKey(olc::C).bPressed)
			_cellMatrix->reset();
	}

	if (GetKey(olc::A).bPressed)
		this->_renderGrid = !this->_renderGrid;

	if (GetKey(olc::SPACE).bPressed)
		this->_isPlaying = !this->_isPlaying;

	this->_cellMatrixRenderer->render(*this);

	return true;
}

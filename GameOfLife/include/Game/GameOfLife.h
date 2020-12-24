#pragma once
#include "Graphics/GridRenderer.h"
#include "Game/CellMatrix.h"
#include "Graphics/CellMatrixRenderer.h"
#include "Utils/Vector2.h"


class GameOfLife : public olc::PixelGameEngine
{
private:
	gol::Vector2s _cellSize;

	bool _renderGrid = true;

	std::shared_ptr<gol::CellMatrix>					_cellMatrix;
	
	std::unique_ptr<gol::CellMatrixRenderer>	_cellMatrixRenderer;
	std::unique_ptr<gol::GridRenderer>				_gridRenderer;

private:
	void fillCellByCursorPos(gol::Vector2s cursor_position, bool newValue);
	gol::Vector2s getMousePositionVector() const;

public:
	GameOfLife();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fDeltaTime) override;
};


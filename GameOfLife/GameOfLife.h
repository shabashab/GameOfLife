#pragma once
#include "GridRenderer.h"
#include <vector>

struct Vector2 {
	int x;
	int y;
};

struct Cell {
	bool isAlive;
	int neighboursCount;
};

class GameOfLife : public olc::PixelGameEngine
{
private:
	std::vector<std::vector<Cell>> cells;
	std::vector<Vector2> blackCellsPos;

	int cell_w;
	int cell_h;

	double last_count_time = 0;

	bool render_grid = true;
	
	gol::GridRenderer grid_renderer_;

private:
	void DrawCells(olc::Pixel color);
	void CalculateNeighboursCount();
	void ApplyNeighboursCount();
	void ResetNeighboursCount(bool fullReset = true);
	void ResetBlackCellsPos();
	void FillCellByCursorPos(int cursor_x, int cursor_y, bool value);
	void FillCell(int x, int y, bool value);

public:
	GameOfLife();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fDeltaTime) override;
};


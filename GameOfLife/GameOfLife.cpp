#include "GameOfLife.h"
#include <iostream>
#include <chrono>


void GameOfLife::DrawCells(olc::Pixel color)
{
	for (auto pos : blackCellsPos) {
		FillRect(pos.x * cell_w, pos.y * cell_h, cell_w, cell_h, color);
	}
}

void GameOfLife::CalculateNeighboursCount()
{
	//Reset neighbours count array
	ResetNeighboursCount(false);

	//Go through black cells positions
	for (auto pos : blackCellsPos) {
		//On each black cell add 1 to neighbours' neighbours count
		for (int x_offset = -1; x_offset <= 1; x_offset++) {
			for (int y_offset = -1; y_offset <= 1; y_offset++) {
				if (x_offset == 0 && y_offset == 0) continue;
				if (pos.x + x_offset < 0 || pos.y + y_offset < 0) continue;
				if (!(!(cells.size() < pos.x + x_offset) || !(cells[0].size() < pos.y + y_offset))) continue;

				cells[pos.x + x_offset][pos.y + y_offset].neighboursCount++;
			}
		}
	}
}

void GameOfLife::ApplyNeighboursCount()
{
	ResetBlackCellsPos();
	for (int x = 0; x < cells.size(); x++) {
		for (int y = 0; y < cells[x].size(); y++) {
			Cell* cell = &cells[x][y];

			//RULES

			//By default cell dies
			bool lives = false;

			//Cell doesn't die if two or three neighbours
			if (cell->isAlive && (cell->neighboursCount == 2 || cell->neighboursCount == 3)) lives = true;

			//Cell becomes alive if three neighbours
			if (!cell->isAlive && cell->neighboursCount == 3) lives = true;

			//If lives add to black cells array
			FillCell(x, y, lives);
		}
	} 
}

void GameOfLife::ResetNeighboursCount(bool fullReset)
{
	if(fullReset)
		cells = std::vector<std::vector<Cell>>((int)(ScreenWidth() / cell_w), std::vector<Cell>((int)(ScreenHeight() / cell_h)));
	else
	{
		for (auto& cellArr : cells) {
			for (auto& cell : cellArr) {
				cell.neighboursCount = 0;
			}
		}
	}
}

void GameOfLife::ResetBlackCellsPos()
{
	blackCellsPos.clear();
}

void GameOfLife::FillCellByCursorPos(int cursor_x, int cursor_y, bool value)
{
	int x = (int)((float)cursor_x / cell_w);
	int y = (int)((float)cursor_y / cell_h);
	
	FillCell(x, y, value);
}

void GameOfLife::FillCell(int x, int y, bool value)
{
	int index = -1;
	for (int i = 0; i < blackCellsPos.size(); i++) {
		if (blackCellsPos[i].x == x && blackCellsPos[i].y == y) {
			index = i;
			break;
		}
	}

	if (value && (index < 0)) {
		blackCellsPos.push_back(Vector2{ x = x, y = y });
	}
	else if (!value && (index >= 0)) {
		blackCellsPos.erase(blackCellsPos.begin() + index);
	}

	cells[x][y].isAlive = value;
}

GameOfLife::GameOfLife()
{
	this->cell_w = 20;
	this->cell_h = 20;
	this->grid_renderer_ = 
		gol::GridRenderer(
			cell_w,
			gol::Vector2{ this->ScreenWidth(), this->ScreenHeight() }, 
			olc::GREY);
}

bool GameOfLife::OnUserCreate()
{
	ResetBlackCellsPos();
	ResetNeighboursCount();
	return true;
}

bool GameOfLife::OnUserUpdate(float fDeltaTime)
{
	Clear(olc::WHITE);
	
	if(this->render_grid)
		this->grid_renderer_.Render(*this);

	if (GetMouse(0).bHeld) {
		FillCellByCursorPos(GetMouseX(), GetMouseY(), true);
	}
	
	if (GetMouse(1).bHeld) {
		FillCellByCursorPos(GetMouseX(), GetMouseY(), false);
	}

	if (GetKey(olc::RIGHT).bHeld) {
		auto start = std::chrono::steady_clock::now();
		CalculateNeighboursCount();
		ApplyNeighboursCount();
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_time = end - start;
		this->last_count_time = elapsed_time.count();
	}

	if (GetKey(olc::A).bPressed)
	{
		this->render_grid = !this->render_grid;
	}

	if (GetKey(olc::C).bPressed) {
		ResetBlackCellsPos();
	}
	
	DrawCells(olc::BLACK);
	DrawString(0, 0, "Time: " + std::to_string(this->last_count_time), olc::BLACK);
	DrawString(0, 10, "Black cells count: " + std::to_string(blackCellsPos.size()), olc::BLACK);

	return true;
}

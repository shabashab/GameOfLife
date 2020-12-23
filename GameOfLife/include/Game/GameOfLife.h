#pragma once
#include "Graphics/GridRenderer.h"
#include "Game/CellMatrix.h"
#include "Graphics/CellMatrixRenderer.h"
#include "Utils/Vector2.h"


class GameOfLife : public olc::PixelGameEngine
{
private:
	gol::Vector2 cell_size_ ;

	bool render_grid = true;

	std::shared_ptr<gol::CellMatrix>					cell_matrix_;
	
	std::unique_ptr<gol::CellMatrixRenderer>	cell_matrix_renderer_;
	std::unique_ptr<gol::GridRenderer>				grid_renderer_;

private:
	void fill_cell_by_cursor_pos(gol::Vector2 cursor_position, bool new_value);
	gol::Vector2 get_mouse_position_vector() const;

public:
	GameOfLife();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fDeltaTime) override;
};


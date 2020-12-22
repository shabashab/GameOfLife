#include "Game/GameOfLife.h"
#include "Game/GameOfLifeCellRule.h"

void GameOfLife::fill_cell_by_cursor_pos(gol::Vector2 cursor_position, bool new_value)
{
	const gol::Vector2 cell_position(
		cursor_position.x / this->cell_size_.x,
		cursor_position.y / this->cell_size_.y
	);
	this->cell_matrix_->setCell(cell_position, new_value);
}

gol::Vector2 GameOfLife::get_mouse_position_vector() const
{
	return {this->GetMouseX(), this->GetMouseY()};
}

GameOfLife::GameOfLife()
{
	this->cell_size_ = gol::Vector2(20, 20);
	this->grid_renderer_ = 
		gol::GridRenderer(this->cell_size_, gol::Vector2(this->ScreenWidth(), this->ScreenHeight()), olc::GREY);
}

bool GameOfLife::OnUserCreate()
{
	this->cell_matrix_ = 
		std::make_shared<gol::CellMatrix>(500, 500, GameOfLifeCellRule::getInstance());
	
	this->cell_matrix_renderer_ = 
		std::make_unique<gol::CellMatrixRenderer>(this->cell_matrix_, this->cell_size_, olc::BLACK);
	
	return true;
}

bool GameOfLife::OnUserUpdate(float fDeltaTime)
{
	Clear(olc::WHITE);
	
	if(this->render_grid)
		this->grid_renderer_.Render(*this);

	if (GetMouse(0).bPressed) {
		this->fill_cell_by_cursor_pos(this->get_mouse_position_vector(), true);
	}
	
	if (GetMouse(1).bPressed) {
		this->fill_cell_by_cursor_pos(this->get_mouse_position_vector(), false);
	}

	if (GetKey(olc::RIGHT).bHeld) {
		cell_matrix_->step();
	}

	if (GetKey(olc::A).bPressed)
	{
		this->render_grid = !this->render_grid;
	}

	if (GetKey(olc::C).bPressed) {
		cell_matrix_->reset();
	}

	this->cell_matrix_renderer_->Render(*this);

	return true;
}

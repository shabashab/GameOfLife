#include "CellMatrixRenderer.h"


gol::CellMatrixRenderer::CellMatrixRenderer(std::shared_ptr<gol::CellMatrix> matrix, gol::Vector2 cell_size,
	olc::Pixel alive_cell_color)
{
	this->cell_matrix_ = matrix;
	this->cell_size_ = cell_size;
	this->alive_cell_color_ = alive_cell_color;
}

void gol::CellMatrixRenderer::Render(olc::PixelGameEngine& engine)
{
	for(auto& value: cell_matrix_->getAliveCells())
	{
		engine.FillRect(
			value.x * this->cell_size_.x, 
			value.y * this->cell_size_.y, 
			this->cell_size_.x, 
			this->cell_size_.y,
			this->alive_cell_color_);
	}
}

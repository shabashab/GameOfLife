#include "Graphics/GridRenderer.h"

void gol::GridRenderer::draw_vertical_lines(
	olc::PixelGameEngine& engine) const
{
	for(auto x = 0; x < this->grid_size_.x; x += this->cell_size_.x)
	{
		engine.DrawLine(x, 0, x, this->grid_size_.y, this->color_);
	}
}

void gol::GridRenderer::draw_horizontal_lines(
	olc::PixelGameEngine& engine) const
{
	for(auto y = 0; y < this->grid_size_.y; y += this->cell_size_.y) {
		engine.DrawLine(0, y, this->grid_size_.x, y, this->color_);
	}
}

gol::GridRenderer::GridRenderer(gol::Vector2s cell_size, gol::Vector2s grid_size, olc::Pixel color)
{
	this->cell_size_ = cell_size;
	this->grid_size_ = grid_size;
	this->color_ = color;
}

void gol::GridRenderer::Render(olc::PixelGameEngine& engine)
{
	this->draw_horizontal_lines(engine);
	this->draw_vertical_lines(engine);
}

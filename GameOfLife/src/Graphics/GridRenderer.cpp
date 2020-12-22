#include "Graphics/GridRenderer.h"
#include <chrono>


void gol::GridRenderer::draw_vertical_lines(
	olc::PixelGameEngine& engine) 
{
	for(auto x = 0; x < engine.ScreenWidth(); x += this->cell_size_.x)
	{
		v_line_renderer_.setXPos(x, engine.ScreenHeight());
		v_line_renderer_.Render(engine);
	}
}

void gol::GridRenderer::draw_horizontal_lines(
	olc::PixelGameEngine& engine)	
{
	for(auto y = 0; y < engine.ScreenHeight(); y += this->cell_size_.y)
	{
		h_line_renderer_.setYPos(y, engine.ScreenWidth());
		h_line_renderer_.Render(engine);
	}
}

gol::GridRenderer::GridRenderer(gol::Vector2 cell_size, Vector2 screen_size, olc::Pixel color = olc::GREY) :
	v_line_renderer_(color, screen_size.y),
	h_line_renderer_(color, screen_size.x)
{
	this->cell_size_ = cell_size;
}

void gol::GridRenderer::Render(olc::PixelGameEngine& engine)
{
	this->draw_horizontal_lines(engine);
	this->draw_vertical_lines(engine);
}

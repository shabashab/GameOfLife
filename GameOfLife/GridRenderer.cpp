#include "GridRenderer.h"
#include <chrono>


void gol::GridRenderer::draw_vertical_lines(
	olc::PixelGameEngine& engine) 
{
	for(auto x = 0; x < engine.ScreenWidth(); x += this->cell_size_)
	{
		VerticalLineRenderer::setXPos(x, engine.ScreenHeight());
		VerticalLineRenderer::Render(engine);
	}
}

void gol::GridRenderer::draw_horizontal_lines(
	olc::PixelGameEngine& engine)	
{
	for(auto y = 0; y < engine.ScreenHeight(); y += this->cell_size_)
	{
		HorizontalLineRenderer::setYPos(y, engine.ScreenWidth());
		HorizontalLineRenderer::Render(engine);
	}
}

gol::GridRenderer::GridRenderer(int cell_size, Vector2 screen_size, olc::Pixel color = olc::GREY) :
	HorizontalLineRenderer(color, screen_size.x),
	VerticalLineRenderer(color, screen_size.y)
{
	this->cell_size_ = cell_size;
}

void gol::GridRenderer::Render(olc::PixelGameEngine& engine)
{
	this->draw_horizontal_lines(engine);
	this->draw_vertical_lines(engine);
}

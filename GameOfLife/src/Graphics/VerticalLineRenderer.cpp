#include "Graphics/VerticalLineRenderer.h"

gol::VerticalLineRenderer::VerticalLineRenderer(olc::Pixel color, int screen_h,  int x_pos)
{
	this->setXPos(x_pos, screen_h);
	this->setColor(color);
}

void gol::VerticalLineRenderer::setXPos(int x_pos, int screen_h)
{
	this->setPosition(
		LinePosition{
			Vector2 {x_pos, 0},
			Vector2 {x_pos, screen_h}
		});
}

int gol::VerticalLineRenderer::getXPos() const
{
	return this->getPosition().position_1.x;
}

void gol::VerticalLineRenderer::Render(olc::PixelGameEngine& engine)
{
	LineRenderer::Render(engine);
}
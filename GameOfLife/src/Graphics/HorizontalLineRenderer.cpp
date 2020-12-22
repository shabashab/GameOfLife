#include "Graphics/HorizontalLineRenderer.h"

gol::HorizontalLineRenderer::HorizontalLineRenderer(olc::Pixel color, int screen_w, int y_pos)
{
	this->setColor(color);
	this->setYPos(y_pos, screen_w);
}

void gol::HorizontalLineRenderer::Render(olc::PixelGameEngine& engine)
{
	LineRenderer::Render(engine);
}

int gol::HorizontalLineRenderer::getYPos() const
{
	return this->getPosition().position_1.y;
}

void gol::HorizontalLineRenderer::setYPos(int y_pos, int screen_w)
{
	this->setPosition(
		LinePosition{
			Vector2 {0, y_pos},
			Vector2 {screen_w, y_pos}
		}
	);
}

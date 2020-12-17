#include "LineRenderer.h"

void gol::LineRenderer::setPosition(gol::LinePosition position)
{
	this->position_ = position;
}

gol::LinePosition gol::LineRenderer::getPosition() const
{
	return this->position_;
}

void gol::LineRenderer::Render(olc::PixelGameEngine& engine)
{
	engine.DrawLine(
		this->position_.position_1.x,
		this->position_.position_1.y,
		this->position_.position_2.x,
		this->position_.position_2.y,
		this->getColor());
}

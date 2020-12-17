#pragma once
#include "IRenderer.h"

namespace gol
{
	class IColoredRenderer : public gol::IRenderer
	{
	private:
		olc::Pixel color_;
	public:
		olc::Pixel getColor() const { return this->color_; }
		void setColor(olc::Pixel new_color) { this->color_ = new_color; }
	};	
}

#pragma once
#include "Graphics/IRenderer.h"

namespace gol
{
	class IColoredRenderer : public gol::IRenderer
	{
	protected:
		olc::Pixel color_;
	public:
		olc::Pixel getColor() const { return this->color_; }
	};	
}

#pragma once
#include "Graphics/IRenderer.h"

namespace gol
{
	class IColoredRenderer : public IRenderer
	{
	protected:
		olc::Pixel _color;
	public:
		olc::Pixel getColor() const { return this->_color; }
	};
}

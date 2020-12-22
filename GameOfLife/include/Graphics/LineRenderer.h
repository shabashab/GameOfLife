#pragma once

#include "Graphics/IColoredRenderer.h"
#include "Utils/LinePosition.h"

namespace gol
{
	class LineRenderer : public gol::IColoredRenderer
	{
	private:
		gol::LinePosition position_ = {};
	public:
		void setPosition(gol::LinePosition position);
		gol::LinePosition getPosition() const;
		virtual void Render(olc::PixelGameEngine& engine) override;
	};
}

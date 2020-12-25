#pragma once
#include "Graphics/IRenderer.h"
#include "GameBase/CellMatrix.h"
#include "Utils/Vector2.h"

namespace gol
{
	class CellMatrixRenderer : IRenderer
	{
	private:
		std::shared_ptr<CellMatrix> _cellMatrix;
		Vector2s _cellSize{};
		olc::Pixel _aliveCellColor;
	public:
		explicit CellMatrixRenderer(std::shared_ptr<CellMatrix> matrix, Vector2s cellSize,
		                            olc::Pixel aliveCellColor = olc::BLACK);
		void render(olc::PixelGameEngine& engine) override;
	};
}

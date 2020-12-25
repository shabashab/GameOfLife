#pragma once
#include "Graphics/GridRenderer.h"
#include "GameBase/CellMatrix.h"
#include "Graphics/CellMatrixRenderer.h"
#include "Utils/Vector2.h"


namespace gol
{
	class GameOfLife : public olc::PixelGameEngine
	{
	private:
		Vector2s _cellSize;

		bool _renderGrid = true;
		bool _isPlaying = false;

		float _playingTime = 0.f;
		
		std::shared_ptr<CellMatrix> _cellMatrix;

		std::unique_ptr<CellMatrixRenderer> _cellMatrixRenderer;
		std::unique_ptr<GridRenderer> _gridRenderer;

	private:
		void fillCellByCursorPos(Vector2s cursorPosition, bool newValue) const;
		Vector2s getMousePositionVector() const;

	public:
		GameOfLife();

	public:
		bool OnUserCreate() override;
		bool OnUserUpdate(float fDeltaTime) override;
	};
}

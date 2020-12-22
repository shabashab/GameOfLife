#define OLC_PGE_APPLICATION
#include "GameOfLife.h"
#include "VerticalLineRenderer.h"

int main() {
	GameOfLife gol;
	if (gol.Construct(1280, 720, 1, 1)) {
		gol.Start();
	}
	return 0;
}
#include "Game/GameOfLife.h"

int main() {
	GameOfLife gol;
	if (gol.Construct(1280, 720, 1, 1)) {
		gol.Start();
	}
	return 0;
}
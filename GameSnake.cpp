#include "GameSnake.h"

GameSnake::GameSnake() {
	StartGame();
}

GameSnake::~GameSnake()
{
}

int GameSnake::GetFreePosition() {
	int pos;
	while (true) {
		pos = random(MATRIX_SIZE);
		if (GetPixel(pos) == 0) break;
	}

	return pos;
}

void GameSnake::SetPaika() {
	SetPixel(GetFreePosition(), paikaColor);
}

void GameSnake::KeyDown(int keyCode) {
	direction = keyCode;
}

void GameSnake::Update(float deltaTime) {

	time -= deltaTime;
	if (time > 0) return;
	time = maxTime;

	switch ( direction) {
		case KEY_RIGHT:
			currentX++;
			if (currentX >= MATRIX_SIDE) currentX = 0;
			break;
		case KEY_DOWN:
			currentY--;
			if (currentY < 0) currentY = MATRIX_SIDE - 1;
			break;
		case KEY_LEFT:
			currentX--;
			if (currentX < 0 ) currentX = MATRIX_SIDE - 1;
			break;
		case KEY_UP:
			currentY++;
			if (currentY >= MATRIX_SIDE) currentY = 0;
			break;
	}

	uint32_t newPos = GetPixel(currentX, currentY);

	if (newPos == snakeColor) {
		Lose(deltaTime);
		return;
	}

	if (newPos == paikaColor) {
		current++;

		Snake[current] = Position(currentX, currentY);
		SetPixel(Snake[current], snakeColor);
		SetPaika();
		return;
	}

	SetPixel(Snake[0], 0);

	for (int i = 0; i < current; i++) {
		Snake[i] = Snake[i + 1];
	}

	Snake[current] = Position(currentX, currentY);
	SetPixel(Snake[current], snakeColor);

}

void GameSnake::StartGame() {
	for (int i = 0; i < MATRIX_SIZE; i++) Snake[i] = 0;

	direction = KEY_RIGHT;

	Snake[0] = 0;

	current = 0;
	currentX = 0;
	currentY = 0;

	SetPaika();

	for (int i = 0; i <= current; i++) SetPixel(Snake[i], snakeColor);

}

void GameSnake::NextLevel(){
  StartGame();
}
void GameSnake::RestartLevel() {
  maxTime = 0.5;
  StartGame();
}





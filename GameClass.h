// GameClass.h

#ifndef _GAMECLASS_h
#define _GAMECLASS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define MATRIX_SIZE 64
#define MATRIX_SIDE 8

#define KEY_UP 1
#define KEY_RIGHT 2
#define KEY_DOWN 3
#define KEY_LEFT 4

class GameClass
{
public:
	int Level = 1;

	int GameStatus = 0; //0 normal game, 1 victory 2 lose

	bool updated = false;
	uint32_t Matrix[MATRIX_SIZE];

	bool KeyUP = false;
	bool KeyDOWN = false;
	bool KeyLEFT = false;
	bool KeyRIGHT = false;

	GameClass();
	~GameClass();
	void Loop(float deltaTime);

	virtual void Update(float deltaTime) {};

	uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
	int Position(int x, int y);

	void Clear();

	void SetPixel(int position, uint32_t color);
	void SetPixel(int x, int y, uint32_t color);
	uint32_t GetPixel(int position);
	uint32_t GetPixel(int x, int y);

	virtual void StartGame() {};
	virtual void NextLevel() {};
	virtual void RestartLevel() {};

	void Victory(float deltaTime);
	void Lose(float deltaTime);

	void CheckKey(bool up, bool right, bool down, bool left);

	virtual void KeyDown(int keyCode) {};
	virtual void KeyUp(int keyCode) {};

private:
	float waitLevel = 5;
};

#endif


#include "GameSnake.h"
#include "GameClass.h"
#include <Adafruit_NeoPixel.h>

#define MATRIXPIN      10

#define up 7
#define down 5
#define right 4
#define left 6

Adafruit_NeoPixel Matrix = Adafruit_NeoPixel(MATRIX_SIZE, MATRIXPIN, NEO_GRB + NEO_KHZ800);

unsigned long MainTime;

GameClass* GAME;

void setup() {
  randomSeed(analogRead(0));

  Matrix.begin();
  Matrix.clear();
  Matrix.show();

  Serial.begin(115200);
  pinMode(up,INPUT_PULLUP);
pinMode(down,INPUT_PULLUP);
pinMode(right,INPUT_PULLUP);
pinMode(left,INPUT_PULLUP);
  delay(200);
  Serial.println("Start");

  GAME = new GameSnake();
  DrawGame();

  MainTime = millis();
}

void loop() {

  if (GAME) GAME->CheckKey(digitalRead(up) == 0, digitalRead(right) == 0, digitalRead(down) == 0, digitalRead(left) == 0);

  unsigned long delta = millis() - MainTime;
  if (delta > 8) {
    MainTime = millis();
    if (GAME) {
      GAME->Loop((float)delta / 1000.0);
      DrawGame();
    }
  }
}

void DrawGame() {
  if (GAME) {
    if (GAME->updated) {
      for (int i = 0; i < MATRIX_SIZE; i++) Matrix.setPixelColor(i, GAME->Matrix[i]);
      Matrix.show();
      GAME->updated = false;
    }
  }

}

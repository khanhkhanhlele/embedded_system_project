#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define GAME_SPEED 50
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int game_state = 1; // 0 = game over screen, 1 = in game
int score = 0; // current game score
int high_score = 0; // highest score since the nano was reset
int bird_x = (int)display.width() / 4; // birds x position (along) - initialised to 1/4 the way along the screen
int bird_y; // birds y position (down)
int momentum = 0; // how much force is pulling the bird down
int wall_x[2]; // an array to hold the walls x positions
int wall_y[2]; // an array to hold the walls y positions
int wall_gap = 30; // size of the wall wall_gap in pixels
int wall_width = 10; // width of the wall in pixels

// Initialise 'sprites'
#define SPRITE_HEIGHT   16
#define SPRITE_WIDTH    16



static const unsigned char PROGMEM wing_down_bmp[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000011, B11000000,
  B00011111, B11110000,
  B00111111, B00111000,
  B01111111, B11111110,
  B11111111, B11000001,
  B11011111, B01111110,
  B11011111, B01111000,
  B11011111, B01111000,
  B11001110, B01111000,
  B11110001, B11110000,
  B01111111, B11100000,
  B00111111, B11000000,
  B00000111, B00000000,
  B00000000, B00000000,
};

static const unsigned char PROGMEM wing_up_bmp[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000011, B11000000,
  B00011111, B11110000,
  B00111111, B00111000,
  B01110001, B11111110,
  B11101110, B11000001,
  B11011111, B01111110,
  B11011111, B01111000,
  B11111111, B11111000,
  B11111111, B11111000,
  B11111111, B11110000,
  B01111111, B11100000,
  B00111111, B11000000,
  B00000111, B00000000,
  B00000000, B00000000,
};
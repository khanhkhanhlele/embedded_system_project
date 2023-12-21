#include "snake.h"
#include "fruit.h"
#include "renderer.h"
#include "icon.h"
#include "nano_bird.h"
#include "U8g2lib.h"
#include "setup.h"
#include "animation.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0); // [full framebuffer, size = 1024 bytes]


Snake snake;
Fruit fruit(&snake);

void startSnake() {
  snake = Snake();
  fruit = Fruit(&snake);
}


void snakeGame(){
  int horz = analogRead(HORZ_PIN);
  int vert = analogRead(VERT_PIN);
  
  if (up()) snake.turn(UP);
  if (down()) snake.turn(DOWN);
  if (left()) snake.turn(LEFT);
  if (right()) snake.turn(RIGHT);


  bool resetFruit = false;
  if(snake.nextHeadPosition() == fruit.getPosition()) {
    snake.grow();
    resetFruit = true;
  }

  snake.advance();
  if(resetFruit) fruit.randomize(&snake);
  
  Renderer::startFrame();
  Renderer::renderBorder();
  Renderer::renderSnake(&snake);
  Renderer::renderFruit(&fruit);
  if(!snake.isAlive()) {
    Renderer::renderGameOver(&snake);
    if(vert==4095 && horz==4095) startSnake();

  }
  Renderer::endFrame();
  
  delay(500);
}

void nano_bird(){
  display.clearDisplay();

    // If the flap button is currently pressed, reduce the downward force on the bird a bit.
    // Once this foce goes negative the bird goes up, otherwise it falls towards the ground
    // gaining speed
    if (up()) {
      momentum = -4;
    }

    // increase the downward force on the bird
    momentum += 1;

    // add the downward force to the bird position to determine it's new position
    bird_y += momentum;

    // make sure the bird doesn't fly off the top of the screen
    if (bird_y < 0 ) {
      bird_y = 0;
    }

    // make sure the bird doesn't fall off the bottom of the screen
    // give it a slight positive lift so it 'waddles' along the ground.
    if (bird_y > display.height() - SPRITE_HEIGHT) {
      bird_y = display.height() - SPRITE_HEIGHT;
      momentum = -2;
    }

    // display the bird
    // if the momentum on the bird is negative the bird is going up!
    if (momentum < 0) {

      // display the bird using a randomly picked flap animation frame
      if (random(2) == 0) {
        display.drawBitmap(bird_x, bird_y, wing_down_bmp, 16, 16, WHITE);
      }
      else {
        display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);
      }

    }
    else {

      // bird is currently falling, use wing up frame
      display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);

    }

    // now we draw the walls and see if the player has hit anything
    for (int i = 0 ; i < 2; i++) {

      // draw the top half of the wall
      display.fillRect(wall_x[i], 0, wall_width, wall_y[i], WHITE);

      // draw the bottom half of the wall
      display.fillRect(wall_x[i], wall_y[i] + wall_gap, wall_width, display.height() - wall_y[i] + wall_gap, WHITE);

      // if the wall has hit the edge of the screen
      // reset it back to the other side with a new gap position
      if (wall_x[i] < 0) {
        wall_y[i] = random(0, display.height() - wall_gap);
        wall_x[i] = display.width();
      }

      // if the bird has passed the wall, update the score
      if (wall_x[i] == bird_x) {
        score++;

        // highscore is whichever is bigger, the current high score or the current score
        high_score = max(score, high_score);
      }

      // if the bird is level with the wall and not level with the gap - game over!
      if (
        (bird_x + SPRITE_WIDTH > wall_x[i] && bird_x < wall_x[i] + wall_width) // level with wall
        &&
        (bird_y < wall_y[i] || bird_y + SPRITE_HEIGHT > wall_y[i] + wall_gap) // not level with the gap
      ) {
        current_screen = 0;
        bird_y = display.height() / 2;
        momentum = -4;
        wall_x[0] = display.width() ;
        wall_y[0] = display.height() / 2 - wall_gap / 2;
        wall_x[1] = display.width() + display.width() / 2;
        wall_y[1] = display.height() / 2 - wall_gap / 1;
        score = 0;

        // // display the crash and pause 1/2 a second
        // display.display();
        delay(100);

      }

      // move the wall left 4 pixels
      wall_x[i] -= 4;
    }

    // display the current score
    boldTextAtCenter(0, (String)score);

    // now display everything to the user and wait a bit to keep things playable
    display.display();
    delay(GAME_SPEED);
}
void boldTextAtCenter(int y, String txt) {
  int x = display.width() / 2 - txt.length() * 3;

  textAt(x, y, txt);
  textAt(x + 1, y, txt);

}

void textAt(int x, int y, String txt) {
  display.setCursor(x, y);
  display.print(txt);
}

void setup() {
  u8g2.setColorIndex(1);  // set the color to white
  u8g2.begin();
  u8g2.setBitmapMode(1);
  auxScreen.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.setTextColor(WHITE);
  display.clearDisplay();
  // Initialise the random number generator
  randomSeed(analogRead(0));
}

bool down(){
  return analogRead(VERT_PIN) > 4000 && analogRead(HORZ_PIN) < 4000;
}
bool up(){
  return analogRead(VERT_PIN) < 2000;
}
bool left(){
  return analogRead(HORZ_PIN) < 2000;
}
bool right(){
  return analogRead(HORZ_PIN) > 4000 && analogRead(VERT_PIN) < 4000;
}
bool click(){
  return analogRead(HORZ_PIN) == 4095 && analogRead(VERT_PIN) == 4095;
}
bool unclick(){
  return analogRead(HORZ_PIN)<4000 && analogRead(HORZ_PIN)>2000 && analogRead(VERT_PIN)<4000 && analogRead(VERT_PIN)>2000;
}
void loop() {

  // int horz = analogRead(HORZ_PIN);
  // int vert = analogRead(VERT_PIN);

  if (current_screen == 0) { // MENU SCREEN

      // up and down buttons only work for the menu screen
      if (up()) { // up button clicked - jump to previous menu item
        item_selected = item_selected - 1; // select previous item
        button_up_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected < 0) { // if first item was selected, jump to last item
          item_selected = NUM_ITEMS-1;
        }
        delay(200);
      }
      else if (down()) { // down button clicked - jump to next menu item
        item_selected = item_selected + 1; // select next item
        button_down_clicked = 1; // set button to clicked to only perform the action once
        if (item_selected >= NUM_ITEMS) { // last item was selected, jump to first menu item
          item_selected = 0;
          }
        delay(200);

      } 

      if (unclick() && (button_up_clicked == 1)) { // unclick 
        button_up_clicked = 0;
        // delay(100);

      }
      if (unclick() && (button_down_clicked == 1)) { // unclick
        button_down_clicked = 0;
        // delay(100);

      }
      if (click()) { // select button clicked, jump between screens
        current_screen = 1;// menu items screen --> screenshots screen
        delay(100);

      } 
      
        // set correct values for the previous and next items
      item_sel_previous = item_selected - 1;
      if (item_sel_previous < 0) {item_sel_previous = NUM_ITEMS - 1;} // previous item would be below first = make it the last
      item_sel_next = item_selected + 1;  
      if (item_sel_next >= NUM_ITEMS) {item_sel_next = 0;} // next item would be after last = make it the first

      u8g2.clearBuffer();  // clear buffer for storing display content in RAM

      // selected item background
      u8g2.drawXBMP(0, 22, 128, 21, bitmap_item_sel_outline);

      // draw previous item as icon + label
      u8g2.setFont(u8g_font_7x14);
      u8g2.drawStr(25, 15, menu_items[item_sel_previous]); 
      u8g2.drawXBMP( 4, 2, 16, 16, bitmap_icons[item_sel_previous]);          

      // draw selected item as icon + label in bold font
      u8g2.setFont(u8g_font_7x14B);    
      u8g2.drawStr(25, 15+20+2, menu_items[item_selected]);   
      u8g2.drawXBMP( 4, 24, 16, 16, bitmap_icons[item_selected]);     

      // draw next item as icon + label
      u8g2.setFont(u8g_font_7x14);     
      u8g2.drawStr(25, 15+20+20+2+2, menu_items[item_sel_next]);   
      u8g2.drawXBMP( 4, 46, 16, 16, bitmap_icons[item_sel_next]);  

      // draw scrollbar background
      u8g2.drawXBMP(128-8, 0, 8, 64, bitmap_scrollbar_background);

      // draw scrollbar handle
      u8g2.drawBox(125, 64/NUM_ITEMS * item_selected, 3, 64/NUM_ITEMS); 
        

    } 
  else if (current_screen == 1 && item_selected == 0 && game_on == 0) {// snake
    startSnake();
    game_on = 1;
  }
  else if (current_screen == 1 && item_selected == 0 && game_on == 1) {
    snakeGame();
  }
  else if (current_screen == 1 && item_selected == 1 ) {//teacher
    u8g2.clearBuffer();  // clear buffer for storing display content in RAM
    u8g2.drawXBMP( 0, 0, 128, 64, epd_bitmap_TienND); // draw screenshot
    if(click()) {
      current_screen = 0;
      delay(200);
    }
  }
  else if (current_screen == 1 && item_selected == 2 ) {//flappy bird
    u8g2.clearBuffer();  // clear buffer for storing display content in RAM
    nano_bird();
    if(click()) {
      current_screen = 0;
      delay(200);
    }
  }
  else if (current_screen == 1 && item_selected == 3) { // SCREENSHOTS SCREEN
    u8g2.clearBuffer();  // clear buffer for storing display content in RAM

    u8g2.drawXBMP( 0, 0, 128, 64, bitmap_screenshots[album_item]); // draw screenshot
    if(click()) {
      current_screen = 0; delay(300);
    }
    if(right()) {
      album_item += 1; if (album_item >= num_album_item) album_item = 0;
      delay(300);
    }
    if(left()){
      album_item -= 1; if(album_item < 0) album_item = num_album_item -1;
      delay(300);
    }
  }
  else if (current_screen == 1 && item_selected == 4 ) {//animation
    u8g2.clearBuffer();  // clear buffer for storing display content in RAM
    if(click()) {
      current_screen = 0;
      delay(200);
    }
    playAnimation (64,47,50,6,3,-64,128,-40,64,frames,sizeBytes, icon_animation);
    
  }
    


  u8g2.sendBuffer(); // send buffer from RAM to display controller

  // delay(100);

}


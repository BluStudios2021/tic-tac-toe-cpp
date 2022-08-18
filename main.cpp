#include "raylib.h"
#include "iostream"

using namespace std;

void drawCircle(int x, int y, int radius, Color color, int width, Color bgColor) {
  DrawCircle(x, y, radius, color);
  DrawCircle(x, y, radius - width, bgColor);
}

void drawCross(int x, int y, int radius, Color color, int width, Color bgColor) {
  int diameter = radius * 2;
  int triRadius = radius - width;

  // draw base rectangle
  DrawRectangleRounded((Rectangle){(float) x - radius, (float) y - radius, (float) radius * 2, (float) radius * 2}, 0.38, 0, color);

  // draw middle triangles to cut out the basic cross shape
  DrawTriangle((Vector2){(float) x - triRadius, (float) y - radius},
               (Vector2){(float) x, (float) y - width},
               (Vector2){(float) x + triRadius, (float) y - radius},
               bgColor);
  DrawTriangle((Vector2){(float) x + radius, (float) y - triRadius},
               (Vector2){(float) x + width, (float) y},
               (Vector2){(float) x + radius, (float) y + triRadius},
               bgColor);
  DrawTriangle((Vector2){(float) x - triRadius, (float) y + radius},
               (Vector2){(float) x + triRadius, (float) y + radius},
               (Vector2){(float) x, (float) y + width},
               bgColor);
  DrawTriangle((Vector2){(float) x - radius, (float) y - triRadius},
               (Vector2){(float) x - radius, (float) y + triRadius},
               (Vector2){(float) x - width, (float) y},
               bgColor);

  // draw edge triangles to cut of the excess edges of the cross
  DrawTriangle((Vector2){(float) x - radius, (float) y - radius},
               (Vector2){(float) x - radius, (float) y - triRadius},
               (Vector2){(float) x - triRadius, (float) y -radius},
               bgColor);
  DrawTriangle((Vector2){(float) x + radius, (float) y - radius},
               (Vector2){(float) x + triRadius, (float) y - radius},
               (Vector2){(float) x + radius, (float) y - triRadius},
               bgColor);
  DrawTriangle((Vector2){(float) x + radius, (float) y + radius},
               (Vector2){(float) x + radius, (float) y + triRadius},
               (Vector2){(float) x + triRadius, (float) y + radius},
               bgColor);
  DrawTriangle((Vector2){(float) x - radius, (float) y + radius},
               (Vector2){(float) x - triRadius, (float) y + radius},
               (Vector2){(float) x - radius, (float) y + triRadius},
               bgColor);
}


// Main Function

int main(void)
{
  const int screenWidth = 600;
  const int screenHeight = 808;

  InitWindow(screenWidth, screenHeight, "raylib example");


  Color colors[7][2] = {{GOLD, DARKBLUE}, {ORANGE, SKYBLUE}, {PINK, GREEN}, {MAROON, DARKGREEN}, {VIOLET, LIME}, {PURPLE, BEIGE}};

  int colorNum = 0;

  int field[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

  int counter = 0;

  int selectPos[2] = {-1, -1};

  bool isTurnCircle = true;

  int won = -1;
  
  int circleScore = 0;
  int crossScore = 0;
  
  int linePos[2] = {-1, -1};

  SetTargetFPS(60);


  while (!WindowShouldClose())
  {
    // Update
    // -------------------------------------------------------------------------
    Vector2 mousePos = GetMousePosition();
    selectPos[0] = mousePos.x / 200;
    selectPos[1] = (mousePos.y - 200) / 200;
    
    if (mousePos.x < 0 || mousePos.x > 600) {
      selectPos[0] = -1;
    }
    if (mousePos.y < 200 || mousePos.y > 800) {
      selectPos[1] = -1;
    }
    if (!IsCursorOnScreen()) {
      selectPos[0] = -1;
      selectPos[1] = -1;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (won < 0) {
        int num = selectPos[0] + 3 * selectPos[1];
        if (field[num] == -1) {
          field[num] = (int) !isTurnCircle;
          isTurnCircle = !isTurnCircle;
          counter++;
        }

        // Check for win condition
        for (int i = 0; i < 3; i++) {
          if (field[0 + 3 * i] >= 0 && field[0 + 3 * i] == field[1 + 3 * i] && field[0 + 3 * i] == field[2 + 3 * i]) {
            won = field[0 + 3 * i];
            linePos[0] = 0 + 3 * i;
            linePos[1] = 2 + 3 * i;
            break;
          } 
          if (field[0 + i] >= 0 && field[0 + i] == field[3 + i] && field[0 + i] == field[6 + i]) {
            won = field[0 + i];
            linePos[0] = 0 + i;
            linePos[1] = 6 + i;
            break;
          }
        }

        if (field[0] == field[4] && field[0] == field[8]) {
          won = field[0];
          linePos[0] = 0;
          linePos[1] = 8;
        } else if (field[2] == field[4] && field[2] == field[6]) {
          won = field[2];
          linePos[0] = 2;
          linePos[1] = 6;
        }

        if (won < 0 && counter >= 9) {
            won = 2;
        }
        
        switch(won) {
          case 0:
            circleScore++;
            break;
          case 1:
            crossScore++;
            break;
          case 2:
            circleScore++;
            crossScore++;
            break;
        }

      } else {
        for (int i = 0; i < 9; i++) {
          field[i] = -1;
        }
        won = -1;
        counter = 0;
      }

      if (mousePos.x > 200 && mousePos.x < 400 && mousePos.y > 0 && mousePos.y < 200) {
        colorNum++;
        if (colorNum > 5) {
          colorNum = 0;
        }
      }
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
      if (mousePos.x > 200 && mousePos.x < 400 && mousePos.y > 0 && mousePos.y < 200) {
        colorNum--;
        if (colorNum < 0) {
          colorNum = 5;
        }
      }
    }
    

    // Draw
    // -------------------------------------------------------------------------
    BeginDrawing();

      ClearBackground(RAYWHITE);

      // Background
      DrawRectangle(0, 0, 600, 208, BLACK);
      DrawRectangle(0, 208, 600, 600, GRAY);

      if (won < 0 && selectPos[0] >= 0 && selectPos[1] >= 0) {
        DrawRectangle(0 + 196 * selectPos[0], 208 + 196 * selectPos[1], 208, 208, LIGHTGRAY);
      }

      for (int i = 0; i < 3; i++) {
        DrawRectangle(12 + 196 * i, 12, 184, 184, DARKGRAY);
      }

      for (int i = 0; i < 9; i++) {
        DrawRectangle(12 + 196 * (i - 3 * ((int) i / 3)), 220 + 196 * ((int) i / 3), 184, 184, DARKGRAY);
      }
      
      // Score
      std::string s = std::to_string(circleScore);
      DrawText(s.c_str(), 12 + (184 - MeasureText(s.c_str(), 160)) / 2, 34, 160, colors[colorNum][0]);

      s = std::to_string(crossScore);
      DrawText(s.c_str(), 404 + (184 - MeasureText(s.c_str(), 160)) / 2, 34, 160, colors[colorNum][1]);

      // Turn Indicator
      if (isTurnCircle) {
        drawCircle(300, 104, 60, colors[colorNum][0], 18, DARKGRAY);
      } else {
        drawCross(300, 104, 60, colors[colorNum][1], 14, DARKGRAY);
      }

      // Cross and Circle
      for (int i = 0; i < 9; i++) {
        if (field[i] == 0) {
          drawCircle(104 + 196 * (i - 3 * ((int) i / 3)), 312 + 196 * ((int) i / 3), 80, colors[colorNum][0], 26, DARKGRAY);
        }
        else if (field[i] == 1) {
          drawCross(104 + 196 * (i - 3 * ((int) i / 3)), 312 + 196 * ((int) i / 3), 80, colors[colorNum][1], 20, DARKGRAY);
        }
      }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

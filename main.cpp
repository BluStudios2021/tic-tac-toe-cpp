#include "raylib.h"

void drawCircle(int x, int y, int radius, Color color, int width, Color bgColor) {
  DrawCircle(x, y, radius, color);
  DrawCircle(x, y, radius - width, bgColor);
}

void drawCross(int x, int y, int radius, Color color, int width, Color bgColor) {
  int diameter = radius * 2;
  int triRadius = radius - width;

  // draw base rectangle
  DrawRectangleRounded((Rectangle){x - radius, y - radius, radius * 2, radius * 2}, 0.35, 0, color);

  // draw middle triangles to cut out the basic cross shape
  DrawTriangle((Vector2){x - triRadius, y - radius},
               (Vector2){x, y - width},
               (Vector2){x + triRadius, y - radius},
               bgColor);
  DrawTriangle((Vector2){x + radius, y - triRadius},
               (Vector2){x + width, y},
               (Vector2){x + radius, y + triRadius},
               bgColor);
  DrawTriangle((Vector2){x - triRadius, y + radius},
               (Vector2){x + triRadius, y + radius},
               (Vector2){x, y + width},
               bgColor);
  DrawTriangle((Vector2){x - radius, y - triRadius},
               (Vector2){x - radius, y + triRadius},
               (Vector2){x - width, y},
               bgColor);

  // draw edge triangles to cut of the excess edges of the cross
  DrawTriangle((Vector2){x - radius, y - radius},
               (Vector2){x - radius, y - triRadius},
               (Vector2){x - triRadius, y -radius},
               bgColor);
  DrawTriangle((Vector2){x + radius, y - radius},
               (Vector2){x + triRadius, y - radius},
               (Vector2){x + radius, y - triRadius},
               bgColor);
  DrawTriangle((Vector2){x + radius, y + radius},
               (Vector2){x + radius, y + triRadius},
               (Vector2){x + triRadius, y + radius},
               bgColor);
  DrawTriangle((Vector2){x - radius, y + radius},
               (Vector2){x - triRadius, y + radius},
               (Vector2){x - radius, y + triRadius},
               bgColor);
}

int main(void)
{
  const int screenWidth = 600;
  const int screenHeight = 808;

  InitWindow(screenWidth, screenHeight, "raylib example");

  int colorCounter = 0;

  Color ballColors[7] = {MAROON, LIME, DARKBLUE, PURPLE, YELLOW, ORANGE, BEIGE};

  SetTargetFPS(60);

  while (!WindowShouldClose())
  {
    // Update
    // -------------------------------------------------------------------------
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) colorCounter++;
    else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) colorCounter--;

    if (colorCounter < 0) colorCounter = sizeof(ballColors) / sizeof(int);
    else if (colorCounter >= sizeof(ballColors) / sizeof(int)) colorCounter = 0;

    // Draw
    // -------------------------------------------------------------------------
    BeginDrawing();

      ClearBackground(DARKGRAY);

      // Grid
      DrawRectangle(0, 0, 600, 12, BLACK);
      DrawRectangle(0, 196, 600, 12, BLACK);
      
      DrawRectangle(0, 12, 12, 184, BLACK);
      DrawRectangle(196, 12, 12, 184, BLACK);
      DrawRectangle(392, 12, 12, 184, BLACK);
      DrawRectangle(588, 12, 12, 184, BLACK);

      DrawRectangle(0, 208, 600, 12, GRAY);
      DrawRectangle(0, 404, 600, 12, GRAY);
      DrawRectangle(0, 600, 600, 12, GRAY);
      DrawRectangle(0, 796, 600, 12, GRAY);
      
      DrawRectangle(0, 220, 12, 576, GRAY);
      DrawRectangle(196, 220, 12, 576, GRAY);
      DrawRectangle(392, 220, 12, 576, GRAY);
      DrawRectangle(588, 220, 12, 576, GRAY);

      // Cross and Circle
      drawCircle(104, 312, 80, MAROON, 26, DARKGRAY);

      drawCross(300, 312, 80, DARKGREEN, 20, DARKGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

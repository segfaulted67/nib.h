#include <stdio.h>
#include <raylib.h>

int main()
{
  InitWindow(800, 600, "A window");
  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLUE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

#include <raylib.h>

int main(void){
  InitWindow(800, 600, "A window");

  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }

  CloseWindow();
}

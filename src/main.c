#include "raylib.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
  int imagePathIndex;
  Color bgColor = BLACK;
  Texture2D image;

  // Different arguments for the program
  if (argc < 2) // Make sure at least something is inputted
  {
    printf("No arguments provided\n");
    return 1;
  }
  if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) // Help output
  {
    printf("Usage: rimg [--bg] <path to image>\n\n--bg: Set the background color, possible values: black, white\n");
    return 0;
  }
  else if (!strcmp(argv[1], "--bg") && argc == 4) // BG color setting arguments, making sure there are enough arguments
  {
    // Different color options
    if (!strcmp(argv[2], "black"))
    {
      bgColor = BLACK;
    }
    else if (!strcmp(argv[2], "white"))
    {
      bgColor = WHITE;
    }
    imagePathIndex = 3; // Setting the index for what string to read from argv to load image from
  }
  else if (!strcmp(argv[1], "--bg") && argc == 3)
  {
    printf("Missing arguments");
    return 1;
  }
  else // In case no other arguments exist, just get the image from argv[1]
  {
    imagePathIndex = 1; 
  }

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(1280, 720, "rImg");
  
  Image imageImage = LoadImage(argv[imagePathIndex]);
  image = LoadTextureFromImage(imageImage);
  UnloadImage(imageImage);

  while (!WindowShouldClose())
  {
    BeginDrawing();
      ClearBackground(bgColor);
      
      DrawTexture(image, (GetScreenWidth() - image.width) / 2, (GetScreenHeight() - image.height) / 2, WHITE);
    EndDrawing();
  }
}


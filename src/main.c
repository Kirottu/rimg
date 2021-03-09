#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <string.h>

void PrintHelp()
{
  printf("Usage: rimg [--bg] <path to image>\n\n");
  printf("--bg        : Set the background color, possible values: black, white, lightgray, gray, darkgray\n");
  printf("--help | -h : Show this help message\n\n");
  printf("Keybinds:\n\n");
  printf("Escape             : Exit the program");
  printf("Ctrl + Up Arrow    : Zoom in 10%%\n");
  printf("Ctrl + Down Arrow  : Zoom out 10%%\n");
  printf("Ctrl + 0           : Reset zoom\n");
  printf("Up Arrow           : Pan up\n");
  printf("Down Arrow         : Pan down\n");
  printf("Left Arrow         : Pan left\n");
  printf("Right Arrow        : Pan right\n");
  printf("Ctrl + P           : Reset pan\n");
}

int main(int argc, char* argv[])
{
  int imagePathIndex; // Varibale to store the index of the path in argv[] that will be used for the image
  Color bgColor = BLACK; // Default bg to BLACK if no argument for that is provided
  Texture2D image;
  Camera2D camera;
  RenderTexture2D target;

  // Initial values for the camera
  camera.zoom = 1;
  camera.rotation = 0;
  camera.target = (Vector2) {0, 0};
  camera.offset = (Vector2) {0, 0};

  // Zooming related values
  float zoomFactor = 1;
  float minZoomFactor = 0.1;
  float maxZoomFactor = 10;
  float zoomFactorStep = 0.1;
  
  float panSpeed = 1000;
  
  bool flipH = false;
  bool flipV = false;

  // Different arguments for the program
  if (argc < 2) // Make sure at least something is inputted
  {
    PrintHelp();
    return 1;
  }
  if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) // Help output
  {
    PrintHelp();
    return 0;
  }
  else if (!strcmp(argv[1], "--bg")) // BG color setting arguments, making sure there are enough arguments
  {
    if (argc == 2)
    {
      printf("No color input\n\n");
      PrintHelp();
      return 1;
    }
    // Different color options
    // God I wish one could switch on strings in C
    if (!strcmp(argv[2], "black"))
    {
      bgColor = BLACK;
    }
    else if (!strcmp(argv[2], "white"))
    {
      bgColor = WHITE;
    }
    else if (!strcmp(argv[2], "lightgray"))
    {
      bgColor = LIGHTGRAY;
    }
    else if (!strcmp(argv[2], "gray"))
    {
      bgColor = GRAY;
    }
    else if (!strcmp(argv[2], "darkgray"))
    {
      bgColor = DARKGRAY;
    }
    else
    {
      printf("Invalid color input\n\n");
      PrintHelp();
      return 1;
    }
    imagePathIndex = 3; // Setting the index for what string to read from argv to load image from
  }
  else // In case no other arguments exist, just get the image from argv[1]
  {
    imagePathIndex = 1; 
  }

  // Creating the main window
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(1280, 720, "rImg");
  
  target = LoadRenderTexture(1280, 720);

  // Loading the image specified with the path
  Image imageImage = LoadImage(argv[imagePathIndex]);
  image = LoadTextureFromImage(imageImage);
  UnloadImage(imageImage);

  while (!WindowShouldClose())
  {
    if (IsWindowResized())
    {
      target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    }

    float deltaTime = GetFrameTime();

    // Zooming controls
    if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)))
    {
      if (IsKeyPressed(KEY_UP) && zoomFactor < maxZoomFactor) zoomFactor += zoomFactorStep;
      if (IsKeyPressed(KEY_DOWN) && zoomFactor > minZoomFactor) zoomFactor -= zoomFactorStep;
      if (IsKeyPressed(KEY_ZERO)) zoomFactor = 1;
      
      if (IsKeyPressed(KEY_P)) camera.target = (Vector2) {0, 0};

      if (IsKeyPressed(KEY_H)) flipH = !flipH;
      if (IsKeyPressed(KEY_V)) flipV = !flipV;
    }
    else // Enable panning controls if neither zoom modifier was used
    {
      Vector2 input = {0, 0};

      input.y -= IsKeyDown(KEY_UP);
      input.y += IsKeyDown(KEY_DOWN);
      input.x -= IsKeyDown(KEY_LEFT);
      input.x += IsKeyDown(KEY_RIGHT);

      input = Vector2Scale(input, panSpeed * deltaTime);
      
      camera.target.x += input.x;
      camera.target.y += input.y;
    }
      
    BeginDrawing();
      ClearBackground(bgColor); // Set the background as the specified color
      BeginMode2D(camera); // Use the 2D camera for panning and zooming

        DrawTexturePro( // Draw the image with the correct zoom factor
            image, 
            (Rectangle) {0, 0, image.width, image.height}, 
            (Rectangle) {
                (GetScreenWidth() - image.width * zoomFactor) / 2, 
                (GetScreenHeight() - image.height * zoomFactor) / 2, 
                image.width * zoomFactor, 
                image.height * zoomFactor
            }, 
            (Vector2) {0, 0},
            0, 
            WHITE
        );
      EndMode2D();
    EndDrawing();
  }
}

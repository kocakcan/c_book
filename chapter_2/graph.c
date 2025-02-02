#include <SDL2/SDL.h>
#include <stdio.h>

// Function to initialize SDL and create a window
SDL_Window *initWindow(const char *title, int width, int height) {
  SDL_Window *window =
      SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       width, height, SDL_WINDOW_SHOWN);
  if (!window) {
    fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return window;
}

// Main function
int main(int argc, char *argv[]) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  // Create a window
  SDL_Window *window = initWindow("Basic SDL Window", 640, 480);

  // Get the renderer
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    fprintf(stderr, "Could not create renderer: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Main loop
  int running = 1;
  SDL_Event event;
  while (running) {
    // Event handling
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      }
    }

    // Clear the renderer with a color (Black)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Set draw color (Red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // Draw a rectangle
    SDL_Rect rect = {100, 100, 200, 150}; // (x, y, width, height)
    SDL_RenderFillRect(renderer, &rect);

    // Present the drawn renderer
    SDL_RenderPresent(renderer);

    SDL_Delay(30); // Delay for a bit for easier viewing
  }

  // Cleanup
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

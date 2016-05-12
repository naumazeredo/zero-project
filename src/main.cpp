#include <cstdio>

#include "includes.h"

#include "types.h"
#include "globals.h"
#include "timer.h"
#include "sprite.h"
#include "texture.h"
#include "rigidbody.h"

// TODO(naum): Refactor
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool isRunning;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;

char title[32];

Timer g_timer;
u32 frameCount;
u32 frameTimeLast;
double frameTime;

// Test
Rigidbody rigidbody {{0, 0}, {0, 0}};

Mix_Music* music = nullptr;
Mix_Chunk* powerup = nullptr;
// ----

bool startGame();
void quitGame();

void startGraphics();
void destroyGraphics();
void limitFramesPerSecond(u32);

void startMixer();
void destroyMixer();

void handleInput();
void physicsUpdate();

int main() {
  startGame();

  /* XXX Test startup */
  Sprite sprite = createSprite("assets/gfx/blank.png", {0, 0, 32, 32}, {0, 0});
  music = Mix_LoadMUS("assets/sfx/tetris.mp3");
  powerup = Mix_LoadWAV("assets/sfx/powerup.wav");

  //Mix_PlayMusic(music, -1);
  /* ---- */

  startTimer(&g_timer);
  u32 previousTime = g_timer.currentTime;

  frameTimeLast = g_timer.currentTime;
  frameTime = 0.0f;

  isRunning = true;
  while (isRunning) {
    handleInput();

    /* XXX Physics test */
    physicsUpdate();
    /* ---------------- */

    SDL_RenderClear(g_renderer);

    /* XXX Render test */
    renderSprite(sprite, vec2toPoint(rigidbody.position));
    /* ----------- */

    SDL_RenderPresent(g_renderer);

    // Frames per second
    updateTimer(&g_timer);
    limitFramesPerSecond(60);

    frameCount++;
    double frameTimeAlpha = 0.2;
    frameTime = frameTimeAlpha * getDeltaTime() + (1 - frameTimeAlpha) * frameTime;
    if (g_timer.currentTime - previousTime >= 200) {
      sprintf(title, "Zero Project - %4.2f FPS", 1 / frameTime);
      SDL_SetWindowTitle(g_window, title);
      previousTime = g_timer.currentTime;
    }
  }

  /* XXX Test cleanup */
  Mix_FreeChunk(powerup);
  Mix_FreeMusic(music);
  destroySprite(&sprite);
  /* ------------ */

  quitGame();

  return 0;
}

// -------------------------------
// TODO(naum): Refactor into another file

bool startGame() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    SDL_LogError(
      SDL_LOG_CATEGORY_SYSTEM,
      "SDL_Init - SDL could not be initialized: %s\n",
      SDL_GetError()
    );

    return false;
  }

  startGraphics();
  startMixer();

  return true;
}

void quitGame() {
  destroyMixer();
  destroyGraphics();
  IMG_Quit();
  SDL_Quit();
}

void startGraphics() {
  int img_flags = IMG_INIT_PNG;
  if ((IMG_Init(img_flags) & img_flags) != img_flags) {
    SDL_LogError(
      SDL_LOG_CATEGORY_SYSTEM,
      "IMG_Init - Could not initialize PNG support: %s\n",
      IMG_GetError()
    );

    // TODO(naum): Return on error
  }

  g_window = SDL_CreateWindow(
    "Zero Project",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREEN_WIDTH, SCREEN_HEIGHT, 0
  );

  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
  //g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void destroyGraphics() {
  SDL_DestroyRenderer(g_renderer);
  SDL_DestroyWindow(g_window);

  g_renderer = nullptr;
  g_window = nullptr;
}

void limitFramesPerSecond(u32 desiredFramesPerSecond) {
  // TODO(naum): Improve limit fps algorithm
  u32 frameTicks = getDeltaTicks();
  const u32 ticksPerFrame = 1000 / desiredFramesPerSecond;
  if (frameTicks <= ticksPerFrame)
    SDL_Delay(ticksPerFrame - frameTicks);
  inframeUpdateTimer(&g_timer);
}

void startMixer() {
  if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
    SDL_LogError(
      SDL_LOG_CATEGORY_SYSTEM,
      "Mix_OpenAudio - Could not initialize mixer: %s\n",
      Mix_GetError()
    );

    // TODO(naum): Return on error
  }
}

void destroyMixer() {
  Mix_CloseAudio();
}

// ------------------------------------

void handleInput() {
  // Keystate
  const u8* keyState = SDL_GetKeyboardState(0);

  /* XXX Test */
  if (keyState[SDL_SCANCODE_D]) rigidbody.velocity.x++;
  if (keyState[SDL_SCANCODE_A]) rigidbody.velocity.x--;
  if (keyState[SDL_SCANCODE_S]) rigidbody.velocity.y++;
  if (keyState[SDL_SCANCODE_W]) rigidbody.velocity.y--;
  /* ---- */

  // Events
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    } else if (event.type == SDL_KEYDOWN) {
      SDL_Keycode sym = event.key.keysym.sym;

      if (sym == SDLK_ESCAPE)
        isRunning = false;

      /* XXX Test */
      if (sym == SDLK_j) pauseTimer(&g_timer);
      if (sym == SDLK_k) unpauseTimer(&g_timer);
      if (sym == SDLK_1) Mix_PlayChannel(-1, powerup, 0);
      /* -------- */
    }
  }
}

void physicsUpdate() {
  /* XXX Test */
  updateRigidbody(&rigidbody);
  /* ---- */
}

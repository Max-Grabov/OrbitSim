#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mutex.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <string>

#define LOWER_CASE_STARTY 6
#define LOWER_CASE_HEIGHT 16

#define UPPER_CASE_STARTY 28
#define UPPER_CASE_HEIGHT 14

#define NUM_WIDTH 11
#define NUM_STARTX 8
#define NUM_STARTY 49
#define NUM_HEIGHT 15

// TODO Typing has been bugged before and upon switching to running on unix systems, the bug
// is at this point happening 100% of the time.
// Look into fixing duplicate letters
namespace OrbitSim
{

// Lower and upper case x values, There is an extra integer to account for Z in the rendering
// function without having if checks
const int lower_case_x_positions[] = {8,   19,  30,  41,  52,  63,  71,  82,  93,
                                      97,  108, 117, 122, 133, 144, 155, 165, 176,
                                      187, 198, 205, 216, 227, 238, 248, 259, 269};
const int upper_case_x_positions[] = {8,   19,  30,  41,  52,  63,  74,  84,  95,
                                      102, 113, 124, 135, 145, 156, 167, 178, 189,
                                      200, 210, 220, 232, 242, 253, 264, 275, 286};
const int number_x_positions[] = {9, 20, 30, 41, 52, 63, 73, 84, 95, 106, 116};

class TextRenderer
{
public:
  // texture_ has to be a raw pointer, since it doesn't have a destructor to take care of destroying
  // the texture after it falls out of scope This means it can't be written utilizing a simple
  // shared_ptr, since it won't call the required destroy texture method
  // TODO Possibly add a wrapper for things such as SDL_Texture and SDL_Renderer?
  SDL_Texture *texture_ = nullptr;
  SDL_Surface *surface_ = nullptr;

  mutable SDL_Rect source_, dest_;

  TextRenderer(SDL_Renderer *renderer);

  ~TextRenderer();

  TextRenderer(TextRenderer &&other);

  TextRenderer &operator=(TextRenderer &&other);

  TextRenderer(const TextRenderer &other);

  TextRenderer &operator=(const TextRenderer &other);

  void render(SDL_Renderer *renderer, const std::string &input, const int &x, const int &y) const;

  void clearRender(SDL_Renderer *renderer, const int &x, const int &y) const; 
};
} // namespace OrbitSim

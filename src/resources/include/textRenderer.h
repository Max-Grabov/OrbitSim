#ifndef TREND_H_
#define TREND_H_

#include <../SDL2/SDL.h>
#include <string>

#define LOWER_CASE_STARTY 6
#define LOWER_CASE_HEIGHT 16

#define UPPER_CASE_STARTY 28
#define UPPER_CASE_HEIGHT 14

#define NUM_WIDTH 11
#define NUM_STARTX 8
#define NUM_STARTY 49
#define NUM_HEIGHT 15

//Lower and upper case x values, There is an extra integer to account for Z in the rendering function without having if checks
const int lowerLetterX[] = {8, 19, 30, 41, 52, 63, 71, 82, 93, 97, 108, 117, 122, 133, 144, 155, 165, 176, 187, 198, 205, 216, 227, 238, 248, 259, 269};
const int upperLetterX[] = {8, 19, 30, 41, 52, 63, 74, 84, 95, 102, 113, 124, 135, 145, 156, 167, 178, 189, 200, 210, 220, 232, 242, 253, 264, 275, 286};
const int         numX[] = {9, 20, 30, 41, 52, 63, 73, 84, 95, 106, 116};

class TextRenderer {
public:
    SDL_Texture *texture;
    SDL_Rect source;
    SDL_Rect dest;

    TextRenderer(SDL_Renderer *renderer);

    void render(SDL_Renderer *renderer, std::string input, int x, int y);

    void clearRender(SDL_Renderer *renderer, int x, int y);

    ~TextRenderer();
};
#endif
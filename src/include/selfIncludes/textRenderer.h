//TODO
#include <SDL2/SDL.h>
#include <string>

#ifndef TREND_H_
#define TREND_H_

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
const int upperLetterX[] = {8, 19, 30, 41, 52, 63, 74, 84, 95, 102, 113, 124, 135, 145, 156, 167, 178, 189, 200, 210, 221, 232, 242, 253, 264, 275, 286};
//8 , 49 start, 11 interval, y end 64
class TextRenderer {
public:

    SDL_Texture *texture;
    SDL_Rect source;
    SDL_Rect dest;

    TextRenderer(SDL_Renderer *renderer){
        SDL_Surface *surface = SDL_LoadBMP("./src/include/SelfIncludes/font.bmp");
        this->texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);
    }

    void render(SDL_Renderer *renderer, std::string input, int x, int y){
        int currX = 0;
        for(auto c : input){
            if(c >= '0' && c <= '9'){
                //Get character source from map
                this->source.x = NUM_STARTX + NUM_WIDTH*(c - '0');
                this->source.y = NUM_STARTY;
                this->source.w = NUM_WIDTH;
                this->source.h = NUM_HEIGHT;

                //Get destination source, using specified x and y coordinates (starting from top left corner)
                this->dest.x = x + currX;
                this->dest.y = y;
                this->dest.w = NUM_WIDTH + 1;
                this->dest.h = NUM_HEIGHT + 1;
            }

            else if(c >= 'a' && c <= 'z'){
                this->source.x = lowerLetterX[c - 'a'];
                this->source.y = LOWER_CASE_STARTY;
                this->source.w = lowerLetterX[c - 'a' + 1] - lowerLetterX[c - 'a'];
                this->source.h = LOWER_CASE_HEIGHT;

                this->dest.x = x + currX;
                this->dest.y = y;
                this->dest.w = this->source.w + 1;
                this->dest.h = this->source.h + 1;
            }

            else if(c >= 'A' && c <= 'Z'){
                this->source.x = upperLetterX[c - 'A'];
                this->source.y = UPPER_CASE_STARTY;
                this->source.w = upperLetterX[c - 'A' + 1] - upperLetterX[c - 'A'];
                this->source.h = UPPER_CASE_HEIGHT;

                this->dest.x = x + currX;
                this->dest.y = y;
                this->dest.w = this->source.w + 1;
                this->dest.h = this->source.h + 1;
            }

            currX += this->source.w;
            SDL_RenderCopy(renderer, this->texture, &this->source, &dest);
        }
    }

    void clearRender(SDL_Renderer *renderer, int x, int y){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_Rect del = {x, y, 12, 16};
        SDL_RenderDrawRect(renderer, &del);
        SDL_RenderFillRect(renderer, &del);
    }

    ~TextRenderer(){
        SDL_DestroyTexture(texture);
    }
};
#endif
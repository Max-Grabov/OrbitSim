//TODO
#include <SDL2/SDL.h>
#include <string>

#ifndef TREND_H_
#define TREND_H_
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
        int i = 0;
        for(auto c : input){
            if(c >= '0' && c <= '9'){
                //Get character source from map
                this->source.x = 8 + 11*(c - '0');
                this->source.y = 49;
                this->source.w = 11;
                this->source.h = 15;

                //Get destination source, using specified x and y coordinates (starting from top left corner)
                this->dest.x = x + 11*(i++);
                this->dest.y = y;
                this->dest.w = 12;
                this->dest.h = 16;

                SDL_RenderCopy(renderer, this->texture, &this->source, &dest);
            }
            else if(c >= 'z' && c <= 'a'){
                //TODO
            }
            else if(c >= 'Z' && c <= 'A'){
                //TODO
            }
        }
    }

    void clearRender(){
        //TODO
    }

    ~TextRenderer(){
        SDL_DestroyTexture(texture);
    }
};
#endif
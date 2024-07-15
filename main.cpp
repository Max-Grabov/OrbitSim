#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <objects.h>
#include <sphere.h>

const int w = 1200, h = 640;
std::vector<Sphere> spheres;

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Touhou", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if(!window){
        std::cout << "Error creating window" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    bool on = true;
    SDL_Event event;

    while(on){
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                on = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){
                case SDL_SCANCODE_C:
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    break;
                }
                case SDL_SCANCODE_I:
                {
                    Sphere *s1 = new Sphere(200, 200);
                    Sphere *s2 = new Sphere(20, 20);

                    s1->position.x = w/2;
                    s1->position.y = h/2;

                    s2->position.x = w/2 - 400;
                    s2->position.y = h/2 - 200;

                    s1->Draw(renderer);
                    s2->Draw(renderer);

                    break;
                }

                case SDL_SCANCODE_S:
                {
                    Sphere *s = new Sphere(200, 0);

                    s->position.x = w/3;
                    s->position.y = h/3;

                    s->Draw(renderer);
                    break;
                }
                case SDL_SCANCODE_ESCAPE:
                {
                    on = false;
                    break;
                }

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
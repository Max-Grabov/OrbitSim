#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <objects.h>
#include <sphere.h>


const int w = 1300, h = 800;

//Used to achieve coordinate system on the window centered on the center of the screen (0,0) = Center instead of (w/2, h/2)
const int offsetX = w/2;
const int offsetY = h/2;

const double frame = 0.01;

bool c = false;

Sphere *s1 = new Sphere(100, 2000000000000000000);
Sphere *s2 = new Sphere(25, 2000000000000);

void update(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, int cameraOffx, int cameraOffy);

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int cameraOffx = 0;
    int cameraOffy = 0;

    if(!window){
        std::cout << "Error creating window" << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
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
                    s1->position.x = 0;
                    s1->position.y = 0;

                    s2->position.x = 206;
                    s2->position.y = 206;

                    s2->setVelocity({900, -900, 0});

                    s1->Draw(renderer, offsetX, offsetY);
                    s2->Draw(renderer, offsetX, offsetY);

                    c = true;

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
        if(c){
            update(s1, s2, renderer, cameraOffx, cameraOffy);
        }

        if(keyState[SDL_SCANCODE_UP]){
            cameraOffy -= 5;
        }
        if(keyState[SDL_SCANCODE_DOWN]){
            cameraOffy += 5;
        }
        if(keyState[SDL_SCANCODE_RIGHT]){
            cameraOffx += 5;
        }
        if(keyState[SDL_SCANCODE_LEFT]){
            cameraOffx -= 5;
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

//So far one body problem (big sphere is immobile)
void update(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, int cameraOffx, int cameraOffy){
    double rad = s1->distance(*s1, *s2) - s1->radius - s2->radius;

    double forceG = (G * s2->mass * s1->mass)/(pow(rad, 2));
    double forceC = (s2->mass * sqrt(pow(s2->velocity.x, 2) + pow(s2->velocity.y, 2)))/(rad);

    double theta = (s2->position.x == s1->position.x) ?
                    (M_PI/2) :
                    atan((s2->position.y - s1->position.y)/(1.0*(s2->position.x - s1->position.x)));

    if(theta < 0){
        theta = -theta;
    }

    if(s2->position.x > s1->position.x && s2->position.y > s1->position.y){
        theta = theta;
    }
    else if(s2->position.x > s1->position.x && s2->position.y < s1->position.y){
        theta = -theta;
    }
    else if(s2->position.x < s1->position.x && s2->position.y < s1->position.y){
        theta = -(M_PI - theta);
    }
    else if(s2->position.x < s1->position.x && s2->position.y > s1->position.y){
        theta = (M_PI - theta);
    }
    else {
        theta = M_PI/2;
    }


    double FxG = -cos(theta) * forceG;
    double FyG = -sin(theta) * forceG;

    double FxC = sin(theta) * forceC;
    double FyC = -cos(theta) * forceC;

    double FnX = (FxG + FxC);
    double FnY = (FyG + FyC);

    s2->acceleration.x = FnX/s2->mass;
    s2->acceleration.y = FnY/s2->mass;

    s2->position.x = 0.5 * s2->acceleration.x * frame * frame + s2->velocity.x * frame + s2->position.x;
    s2->position.y = 0.5 * s2->acceleration.y * frame * frame + s2->velocity.y * frame + s2->position.y;

    s2->velocity.x = s2->velocity.x + s2->acceleration.x * frame;
    s2->velocity.y = s2->velocity.y + s2->acceleration.y * frame;

    std::cout << (s2->position.x) << " " << (s2->position.y) << std::endl;
    std::cout << theta << " angle" << std::endl;

    SDL_Delay(100);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    s1->Draw(renderer, offsetX + cameraOffx, offsetY + cameraOffy);
    s2->Draw(renderer, offsetX + cameraOffx, offsetY + cameraOffy);
}
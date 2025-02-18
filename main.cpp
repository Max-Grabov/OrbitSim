// On Windows compile with:
// g++ -I src/resources/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
#include "src/resources/include/objects.h"
#include "src/resources/include/sphere.h"
#include "src/resources/include/oneBody.h"
#include "src/resources/include/TwoBody.h"
#include "src/resources/include/menu.h"
#include "src/resources/include/textRenderer.h"
#include "src/resources/include/textInput.h"
#include "src/resources/include/init.h"
#include "src/resources/SDL2/SDL.h"

int main(int argc, char *argv[]){
    int cameraOffx = 0;
    int cameraOffy = 0;

    int *tabCycle = (int*)malloc(sizeof(int));
    *tabCycle = 0;
    int currScreen = 0;
    int selectedScreen = 1;

    bool onMenu = true;
    bool c = false;
    bool on = true;
    bool pause = false;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TextRenderer *textRenderer = new TextRenderer(renderer);

    Sphere *s1 = new Sphere(1, BIG_MASS);
    Sphere *s2 = new Sphere(1, SMALL_MASS);

    std::vector<TextInput*> inputs1;
    std::vector<TextInput*> inputs2;

    char *ch = (char*)malloc(sizeof(char));

    if(!window){
        std::cout << "Error creating window" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    Menu::loadMenu(renderer, textRenderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, Options[0].x, Options[0].y + 210,
                                 Options[0].x + 200, Options[0].y + 210);


    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;

    while(on){
        while(SDL_PollEvent(&event)){

            //Used to keep track of what screen we are on
            if(currScreen == 0){
                switch(event.type){
                    case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode){
                        case SDL_SCANCODE_ESCAPE:
                        {
                            on = false;
                            break;
                            //Add visual indicator
                        }

                        case SDL_SCANCODE_TAB:
                        {
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x, Options[(selectedScreen + 1) % 2].y + 210,
                                                         Options[(selectedScreen + 1) % 2].x + 200, Options[(selectedScreen + 1) % 2].y + 210);

                            selectedScreen = ((selectedScreen + 1) % (SCREENS));

                            if(!selectedScreen){
                                selectedScreen++;
                            }

                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x, Options[(selectedScreen + 1) % 2].y + 210,
                                                         Options[(selectedScreen + 1) % 2].x + 200, Options[(selectedScreen + 1) % 2].y + 210);

                            break;
                            //Add visual indicator
                        }

                        //Actually go to what the selected screen is, and init the sim
                        case SDL_SCANCODE_S:
                        {
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                            SDL_RenderClear(renderer);

                            currScreen = selectedScreen;
                            switch(currScreen){
                            case 1:
                                inputs1 = OneBody::initTextBox();
                                OneBody::initHotbar(renderer, textRenderer, inputs1);
                                OneBody::init(inputs1, renderer, s1, s2);
                                break;
                            case 2:
                                inputs2 = TwoBody::initTextBox();
                                TwoBody::initHotbar(renderer, textRenderer, inputs2);
                                TwoBody::init(inputs2, renderer, s1, s2);
                                break;
                            }
                        }
                    }
                }
            }

            //If not on the menu, do the sim's method continuously
            else if(currScreen == 1){
                currScreen = OneBody::update(ch, tabCycle, keyState, event, &cameraOffx, &cameraOffy, renderer, textRenderer, inputs1, s1, s2, &pause);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                if(!currScreen){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x, Options[(selectedScreen + 1) % 2].y + 210,
                                                 Options[(selectedScreen + 1) % 2].x + 200, Options[(selectedScreen + 1) % 2].y + 210);
                }
            }
            else if(currScreen == 2){
                currScreen = TwoBody::update(ch, tabCycle, keyState, event, &cameraOffx, &cameraOffy, renderer, textRenderer, inputs2, s1, s2);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                if(!currScreen){
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x, Options[(selectedScreen + 1) % 2].y + 210,
                                                 Options[(selectedScreen + 1) % 2].x + 200, Options[(selectedScreen + 1) % 2].y + 210);
                }
            }
        }

        // Now update our calcs
        switch(currScreen){
        case 1:
        {
            if(pause){
                continue;
            }

            OneBody::calc(s1, s2, renderer, cameraOffx, cameraOffy);
            break;
        }
        case 2:
        {
            TwoBody::calc(s1, s2, renderer, cameraOffx, cameraOffy);
            break;
        }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    free(ch);
    free(tabCycle);
    delete textRenderer;
    delete s1;
    delete s2;
    SDL_Quit();

    return EXIT_SUCCESS;
}
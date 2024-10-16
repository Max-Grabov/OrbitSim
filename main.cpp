// On Windows compile with:
// g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
#include <SelfIncludes/objects.h>
#include <SelfIncludes/sphere.h>
#include <SelfIncludes/oneBody.h>
#include <SelfIncludes/TwoBody.h>
#include <SelfIncludes/menu.h>
#include <SelfIncludes/textRenderer.h>
#include <SelfIncludes/textInput.h>
#include <SelfIncludes/init.h>
#include <SDL2/SDL.h>

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

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TextRenderer *textRenderer = new TextRenderer(renderer);

    Sphere *s1 = new Sphere(1, BIG_MASS);
    Sphere *s2 = new Sphere(1,  SMALL_MASS);

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

                            selectedScreen = (selectedScreen + 1) % (SCREENS);

                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                            SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x, Options[(selectedScreen + 1) % 2].y + 210,
                                                         Options[(selectedScreen + 1) % 2].x + 200, Options[(selectedScreen + 1) % 2].y + 210);

                            break;
                            //Add visual indicator
                        }

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
                                inputs1 = TwoBody::initTextBox();
                                TwoBody::initHotbar(renderer, textRenderer, inputs1);
                                TwoBody::init(inputs1, renderer, s1, s2);
                                break;
                            }
                        }
                    }
                }
            }
            else if(currScreen == 1){
                currScreen = OneBody::update(ch, tabCycle, keyState, event, &cameraOffx, &cameraOffy, renderer, textRenderer, inputs1, s1, s2);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            }
            else if(currScreen == 2){
                //currScreen =
            }
        }
        switch(currScreen){
        case 1:
        {
            OneBody::calc(s1, s2, renderer, cameraOffx, cameraOffy);
            break;
        }
        case 2:
        {
            //TwoBody::calc()
        }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    free(ch);
    free(tabCycle);
    SDL_Quit();

    return EXIT_SUCCESS;
}
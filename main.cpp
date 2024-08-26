// On Windows compile with:
// g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
#include <SelfIncludes/objects.h>
#include <SelfIncludes/sphere.h>
#include <SelfIncludes/oneBody.h>
#include <SelfIncludes/menu.h>
#include <SelfIncludes/textRenderer.h>
#include <SelfIncludes/textInput.h>
#include <SelfIncludes/init.h>
#include <SDL2/SDL.h>

Sphere *s1 = new Sphere(100, BIG_MASS);
Sphere *s2 = new Sphere(25,  SMALL_MASS);

int main(int argc, char *argv[]){
    int cameraOffx = 0;
    int cameraOffy = 0;

    int tabCycle = 0;
    int currScreen = 0;
    int selectedScreen = 1;

    bool onMenu = true;
    bool c = false;
    bool on = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TextRenderer *textRenderer = new TextRenderer(renderer);

    std::vector<TextInput*> inputs;

    char *ch = (char*)malloc(sizeof(char));

    if(!window){
        std::cout << "Error creating window" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    Menu::loadMenu(renderer, textRenderer);

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
                            selectedScreen = (selectedScreen + 1) % SCREENS;
                            if(selectedScreen == 0) selectedScreen++;

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
                                inputs = OneBody::initTextBox();
                                OneBody::initHotbar(renderer, textRenderer, inputs);
                                OneBody::init(inputs, renderer, s1, s2);
                            }
                        }
                    }
                }
            }
            else if(currScreen == 1){
                currScreen = OneBody::update(ch, keyState, event, &cameraOffx, &cameraOffy, renderer, textRenderer, inputs, s1, s2);
            }

        }
        switch(currScreen){
        case 1:
        {
            OneBody::calc(s1, s2, renderer, textRenderer, inputs, cameraOffx, cameraOffy);
        }
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    free(ch);
    SDL_Quit();

    return EXIT_SUCCESS;
}
// On Windows compile with:
// g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
#include <SelfIncludes/objects.h>
#include <SelfIncludes/sphere.h>
#include <SelfIncludes/OneBody.h>
#include <SelfIncludes/textRenderer.h>
#include <SelfIncludes/textInput.h>
#include <SelfIncludes/init.h>

Sphere *s1 = new Sphere(100, 2000000000000000000);
Sphere *s2 = new Sphere(25,  2000000000000);

int main(int argc, char *argv[]){
    int cameraOffx = 0;
    int cameraOffy = 0;

    int tabCycle = 0;

    bool c = false;
    bool on = true;

    vectord v;
    std::string oneChange;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TextRenderer *textRenderer = new TextRenderer(renderer);

    std::vector<TextInput*> inputs;

    inputs = OneBody::initTextBox();

    //Text input character
    char *ch = (char*)malloc(sizeof(char));

    if(!window){
        std::cout << "Error creating window" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    SDL_Event event;

    //Setup hotbar for inputting data
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    OneBody::initHotbar(renderer, textRenderer, inputs);

    while(on){
        while(SDL_PollEvent(&event)){

            switch(event.type){
            case SDL_QUIT:
                on = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){

                //Initialize the setup
                case SDL_SCANCODE_I:
                {
                    s1->position.x = 0;
                    s1->position.y = 0 + HOTBAR_H;

                    s2->position.x = 206;
                    s2->position.y = 206 + HOTBAR_H;

                    s2->setVelocity({inputs.at(2)->getText() == "" ?
                                    900 : std::stod(inputs.at(2)->getText(), nullptr),
                                    inputs.at(3)->getText() == "" ?
                                    -900 : std::stod(inputs.at(3)->getText(), nullptr),
                                    0});

                    s1->Draw(renderer, OFFSET_X, OFFSET_Y);
                    s2->Draw(renderer, OFFSET_X, OFFSET_Y);

                    c = true;
                    break;
                }

                //Kill the program
                case SDL_SCANCODE_ESCAPE:
                {
                    on = false;
                    break;
                }

                //Clear the field and offsets
                case SDL_SCANCODE_C:
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderFillRect(renderer, &Screen);

                    c = false;

                    cameraOffx = 0;
                    cameraOffy = 0;

                    break;
                }

                case SDL_SCANCODE_TAB:
                {
                    //Clear last line
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, inputs.at(tabCycle)->getBorder().x,
                       inputs.at(tabCycle)->getBorder().y + + inputs.at(tabCycle)->getBorder().h + 3,
                       inputs.at(tabCycle)->getBorder().x + inputs.at(tabCycle)->getBorder().w,
                       inputs.at(tabCycle)->getBorder().y + + inputs.at(tabCycle)->getBorder().h + 3);

                    tabCycle = (tabCycle + 1) % 4;

                    //Add new line
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                    SDL_RenderDrawLine(renderer, inputs.at(tabCycle)->getBorder().x,
                                       inputs.at(tabCycle)->getBorder().y + + inputs.at(tabCycle)->getBorder().h + 3,
                                       inputs.at(tabCycle)->getBorder().x + inputs.at(tabCycle)->getBorder().w,
                                       inputs.at(tabCycle)->getBorder().y + + inputs.at(tabCycle)->getBorder().h + 3);
                    break;
                }
                //Take in the text input PLACEHOLDER
                case SDL_SCANCODE_A:
                {
                    oneChange = inputs.at(tabCycle)->getText();

                    if(oneChange == ""){
                        break;
                    }

                    switch(tabCycle){
                    case 0:
                        s1->mass = 1000000000000*std::stod(oneChange, nullptr);
                        break;
                    case 1:
                        s2->mass = 1000000000*std::stod(oneChange, nullptr);
                        break;

                    case 2:
                        v = {std::stod(oneChange, nullptr), s2->velocity.y, 0};
                        s2->setVelocity(v);
                        break;

                    case 3:
                        v = {s2->velocity.x, std::stod(oneChange, nullptr), 0};
                        s2->setVelocity(v);
                    }
                    break;
                }

                //Checking typing information
                case SDL_SCANCODE_0:
                {
                    *ch = '0';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_1:
                {
                    *ch = '1';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_2:
                {
                    *ch = '2';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_3:
                {
                    *ch = '3';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_4:
                {
                    *ch = '4';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_5:
                {
                    *ch = '5';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_6:
                {
                    *ch = '6';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_7:
                {
                    *ch = '7';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_8:
                {
                    *ch = '8';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_9:
                {
                    *ch = '9';
                    inputs.at(tabCycle)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_BACKSPACE:
                {
                    inputs.at(tabCycle)->deleteChar(textRenderer, renderer);
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
            OneBody::update(s1, s2, renderer, textRenderer, inputs, cameraOffx, cameraOffy);
        }

        //Add camera movement to simulate "infinite space"
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
    free(ch);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
// On Windows compile with:
// g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2

#include <SelfIncludes/init.h>
#include <SelfIncludes/textInput.h>

Sphere *s1 = new Sphere(100, 2000000000000000000);
Sphere *s2 = new Sphere(25, 2000000000000);

int main(int argc, char *argv[]){
    int cameraOffx = 0;
    int cameraOffy = 0;

    bool c = false;
    bool on = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TextRenderer *textRenderer = new TextRenderer(renderer);

    std::vector<TextInput*> inputs;

    TextInput *massObject1 = new TextInput();
    TextInput *massObject2 = new TextInput();

    inputs.push_back(massObject1);
    inputs.push_back(massObject2);

    massObject1->setBorder(oneInputMass);
    massObject2->setBorder(twoInputMass);

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

    initHotbar(renderer, textRenderer, inputs);

    while(on){
        while(SDL_PollEvent(&event)){

            switch(event.type){
            case SDL_QUIT:
                on = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.scancode){

                //Clear the field and offsets
                case SDL_SCANCODE_C:
                {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);

                    c = false;

                    cameraOffx = 0;
                    cameraOffy = 0;

                    break;
                }

                //Initialize the setup
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

                //Kill the program
                case SDL_SCANCODE_ESCAPE:
                {
                    on = false;
                    break;
                }

                //Checking typing information
                case SDL_SCANCODE_0:
                {
                    *ch = '0';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_1:
                {
                    *ch = '1';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_2:
                {
                    *ch = '2';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_3:
                {
                    *ch = '3';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_4:
                {
                    *ch = '4';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_5:
                {
                    *ch = '5';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_6:
                {
                    *ch = '6';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_7:
                {
                    *ch = '7';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_8:
                {
                    *ch = '8';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_9:
                {
                    *ch = '9';
                    inputs.at(0)->type(textRenderer, renderer, ch);
                    break;
                }

                case SDL_SCANCODE_BACKSPACE:
                {
                    inputs.at(0)->deleteChar(textRenderer, renderer);
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
            update(s1, s2, renderer, textRenderer, inputs, cameraOffx, cameraOffy);
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

void update(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, TextRenderer *tRenderer, std::vector<TextInput*> inputs,
            int cameraOffx, int cameraOffy){

    //Fill the rectangle every fram with white, effectively clearing this portion of the screen
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &Screen);

    //Setup math
    double rad = s1->distance(*s1, *s2) - s1->radius - s2->radius;

    double forceG = (G * s2->mass * s1->mass)/(pow(rad, 2));
    double forceC = (s2->mass * sqrt(pow(s2->velocity.x, 2) + pow(s2->velocity.y, 2)))/(rad);

    //Use theta from -pi to pi
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

    //Kinematics
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

    SDL_Delay(100);

    //Draw the new positions
    s1->Draw(renderer, offsetX + cameraOffx, offsetY + cameraOffy);
    s2->Draw(renderer, offsetX + cameraOffx, offsetY + cameraOffy);
}

void initHotbar(SDL_Renderer *renderer, TextRenderer *tRenderer, std::vector<TextInput*> inputs){
    tRenderer->render(renderer, "1", 10, 20);
    tRenderer->render(renderer, "2", 10, 50);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(renderer, 0, hotbarH, 2*w, hotbarH);

    for(auto const &i : inputs){
        i->init(renderer);
    }
}
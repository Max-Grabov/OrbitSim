#include <SDL2/SDL.h>
#include <SelfIncludes/menu.h>
#include <SelfIncludes/init.h>
#include <SelfIncludes/objects.h>
#include <SelfIncludes/sphere.h>
#include <SelfIncludes/textRenderer.h>
#include <SelfIncludes/textInput.h>

#ifndef _TWO_BODY_
#define _TWO_BODY_

class TwoBody {
public:
    static void init(std::vector<TextInput*> inputs, SDL_Renderer *renderer, Sphere *s1, Sphere *s2){
        s1->radius = 30;
        s2->radius = 30;

        s1->position.x = 300;
        s1->position.y = 0 + HOTBAR_H;

        s2->position.x = -300;
        s2->position.y =  + HOTBAR_H;

        s2->velocity = {inputs.at(2)->getText() == "" ?
                        900 : std::stod(inputs.at(2)->getText(), nullptr),
                        inputs.at(3)->getText() == "" ?
                        -900 : std::stod(inputs.at(3)->getText(), nullptr),
                        0};

        s1->Draw(renderer, OFFSET_X, OFFSET_Y);
        s2->Draw(renderer, OFFSET_X, OFFSET_Y);

        SDL_RenderPresent(renderer);
    }

    static void initHotbar(SDL_Renderer *renderer, TextRenderer *tRenderer, std::vector<TextInput*> inputs){
        tRenderer->render(renderer, "Mass One(Tg)", 10, 20);
        tRenderer->render(renderer, "Mass Two(Gg)", 10, 60);

        tRenderer->render(renderer, "Velocity Two X(m/s)", 245, 20);
        tRenderer->render(renderer, "Velocity Two Y(m/s)", 245, 60);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

        SDL_RenderDrawLine(renderer, 0, HOTBAR_H, 2*SCREEN_WIDTH, HOTBAR_H);

        SDL_RenderDrawLine(renderer, inputs.at(0)->getBorder().x,
                           inputs.at(0)->getBorder().y + + inputs.at(0)->getBorder().h + 3,
                           inputs.at(0)->getBorder().x + inputs.at(0)->getBorder().w,
                           inputs.at(0)->getBorder().y + + inputs.at(0)->getBorder().h + 3);

        for(auto const &i : inputs){
            i->init(renderer);
        }
    }

    static std::vector<TextInput*> initTextBox(){
        std::vector<TextInput*> inputs;
        TextInput *massObject1 = new TextInput();
        TextInput *massObject2 = new TextInput();
        TextInput *velObject1 = new TextInput();
        TextInput *velObject2 = new TextInput();

        inputs.push_back(massObject1);
        inputs.push_back(massObject2);
        inputs.push_back(velObject1);
        inputs.push_back(velObject2);

        massObject1->setBorder(oneInputMass);
        massObject2->setBorder(twoInputMass);
        velObject1->setBorder(oneInputVel);
        velObject2->setBorder(twoInputVel);

        return inputs;
    }

    static void calc(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, int cameraOffx, int cameraOffy){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &Screen);

        double dist = Object::distance(*s1, *s2) - s1->radius - s2->radius;

        double forceG1, forceG2;
        forceG1 = forceG2 = (G * s1->mass * s2->mass)/dist;

        double theta = (s2->position.x == s1->position.x) ?
        (M_PI/2) :
        atan((s1->position.y - s2->position.y)/(1.0*(s1->position.x - s2->position.x)));

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

        double phi = M_PI/2 - theta;


    }
};
#endif
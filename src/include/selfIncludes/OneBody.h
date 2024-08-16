#include <SDL2/SDL.h>
#include <SelfIncludes/init.h>
#include <SelfIncludes/objects.h>
#include <SelfIncludes/sphere.h>
#include <SelfIncludes/textRenderer.h>
#include <SelfIncludes/textInput.h>

#ifndef _ONE_BODY_
#define _ONE_BODY_

class OneBody {
public:
    static void update(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, TextRenderer *tRenderer, std::vector<TextInput*> inputs,
                int cameraOffx, int cameraOffy){

        //Fill the rectangle every fram with white, effectively clearing this portion of the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &Screen);

        //Setup math
        double rad = Object::distance(*s1, *s2) - s1->radius - s2->radius;

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

        s2->position.x = 0.5 * s2->acceleration.x * FRAME * FRAME + s2->velocity.x * FRAME + s2->position.x;
        s2->position.y = 0.5 * s2->acceleration.y * FRAME * FRAME + s2->velocity.y * FRAME + s2->position.y;

        s2->velocity.x = s2->velocity.x + s2->acceleration.x * FRAME;
        s2->velocity.y = s2->velocity.y + s2->acceleration.y * FRAME;

        SDL_Delay(100);

        //Draw the new positions
        s1->Draw(renderer, OFFSET_X + cameraOffx, OFFSET_Y + cameraOffy);
        s2->Draw(renderer, OFFSET_X + cameraOffx, OFFSET_Y + cameraOffy);
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
};

#endif
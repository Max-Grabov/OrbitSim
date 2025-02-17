#ifndef _TWO_BODY_
#define _TWO_BODY_

#include "../SDL2/SDL.h"
#include "menu.h"
#include "init.h"
#include "objects.h"
#include "sphere.h"
#include "textRenderer.h"
#include "textInput.h"

class TwoBody {
public:
    static void init(std::vector<TextInput*> inputs, SDL_Renderer *renderer, Sphere *s1, Sphere *s2);

    static void initHotbar(SDL_Renderer *renderer, TextRenderer *tRenderer, std::vector<TextInput*> inputs);

    static std::vector<TextInput*> initTextBox();

    static void calc(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, int cameraOffx, int cameraOffy);

    static void reset(Sphere *s1, Sphere *s2, int *tabCycle, int *cameraOffx, int *cameraOffy);

    static int update(char *ch, int *tabCycle, const Uint8 *keyState, SDL_Event e, int *cameraOffx, int *cameraOffy, SDL_Renderer *renderer, TextRenderer *tRenderer, std::vector <TextInput*> inputs, Sphere *s1, Sphere *s2);
};
#endif
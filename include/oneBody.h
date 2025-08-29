#ifndef _ONE_BODY_
#define _ONE_BODY_

#include "../SDL2/SDL.h"
#include "menu.h"
#include "init.h"
#include "objects.h"
#include "sphere.h"
#include "textRenderer.h"
#include "textInput.h"

namespace OneBody {
    static void calc(const &Sphere sphere_one, const &Sphere sphere_two, SDL_Renderer *renderer, const &int cameraOffx, const &int cameraOffy);

    static void initHotbar(SDL_Renderer *renderer, const &TextRenderer tRenderer, std::vector<TextInput*> inputs);

    static std::vector<TextInput*> initTextBox();

    static void init(std::vector<TextInput*> inputs, SDL_Renderer *renderer, Sphere *s1, Sphere *s2);

    static void reset(Sphere *s1, Sphere *s2, int *tabCycle, int *cameraOffx, int *cameraOffy, std::vector<TextInput*> inputs);

    static int update(char *ch, int *tabCycle,
                    const Uint8 *keyState, SDL_Event e,
                    int *cameraOffx, int *cameraOffy,
                    SDL_Renderer *renderer, TextRenderer
                    *tRenderer, std::vector <TextInput*> inputs,
                    Sphere *s1, Sphere *s2, bool *pause);
};

#endif
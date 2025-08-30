#pragma once

#include "Init.hpp"
#include "Menu.hpp"
#include "Sphere.hpp"
#include "TextInput.hpp"
#include "TextRenderer.hpp"

class TwoBody {
public:
  static void init(std::vector<TextInput *> inputs, SDL_Renderer *renderer, Sphere *s1, Sphere *s2);

  static void initHotbar(SDL_Renderer *renderer, TextRenderer *tRenderer,
                         std::vector<TextInput *> inputs);

  static std::vector<TextInput *> initTextBox();

  static void calc(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, int cameraOffx, int cameraOffy);

  static void reset(Sphere *s1, Sphere *s2, int *tabCycle, int *cameraOffx, int *cameraOffy,
                    std::vector<TextInput *> inputs);

  static int update(char *ch, int *tabCycle, const uint8 *keystate, SDL_Event e, int *cameraOffx,
                    int *cameraOffy, SDL_Renderer *renderer, TextRenderer *tRenderer,
                    std::vector<TextInput *> inputs, Sphere *s1, Sphere *s2);
};

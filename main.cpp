#include "SDL2/SDL.h"
// #include "TwoBody.hpp"
#include "include/Init.hpp"
#include "include/Menu.hpp"
#include "include/Object.hpp"
#include "include/OneBody.hpp"
#include "include/Sphere.hpp"
#include "include/TextInput.hpp"
#include "include/TextRenderer.hpp"

// TODO get off of this but im too lazy rn
using namespace OrbitSim;

int main(int argc, char *argv[])
{
  int currScreen = 0;
  int selectedScreen = 1;

  bool onMenu = true;
  bool c = false;
  bool on = true;

  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window =
      SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                       SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

  // TODO 10th to do on this make this a wrapper please
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // TODO This should be window specific instead of passing this poor object's reference around
  // everywhere
  TextRenderer text_renderer{renderer};

  // TODO eventually needs to be moved to new class holding all the windows
  OneBody one_body;

  // std::vector<TextInput *> inputs2;

  if (!window) {
    std::cout << "Error creating window" << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  Menu::loadMenu(renderer, text_renderer);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, Options[0].x, Options[0].y + 210, Options[0].x + 200,
                     Options[0].y + 210);

  const Uint8 *keyState = SDL_GetKeyboardState(NULL);
  SDL_Event event;

  while (on) {
    while (SDL_PollEvent(&event)) {

      // Used to keep track of what screen we are on
      if (currScreen == 0) {
        switch (event.type) {
        case SDL_KEYDOWN:
          switch (event.key.keysym.scancode) {
          case SDL_SCANCODE_ESCAPE: {
            on = false;
            break;
            // Add visual indicator
          }

          case SDL_SCANCODE_TAB: {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x,
                               Options[(selectedScreen + 1) % 2].y + 210,
                               Options[(selectedScreen + 1) % 2].x + 200,
                               Options[(selectedScreen + 1) % 2].y + 210);

            selectedScreen = ((selectedScreen + 1) % (SCREENS));

            if (!selectedScreen) {
              selectedScreen++;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x,
                               Options[(selectedScreen + 1) % 2].y + 210,
                               Options[(selectedScreen + 1) % 2].x + 200,
                               Options[(selectedScreen + 1) % 2].y + 210);

            break;
            // Add visual indicator
          }

          // Actually go to what the selected screen is, and init the sim
          case SDL_SCANCODE_S: {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(renderer);

            currScreen = selectedScreen;
            switch (currScreen) {
            case 1:
              one_body.init(renderer, text_renderer);
              break;
              // case 2:
              // inputs2 = TwoBody::initTextBox();
              // TwoBody::initHotbar(renderer, text_renderer, inputs2);
              // TwoBody::init(inputs2, renderer, s1, s2);
              // break;
            }
          }
          }
        }
      }

      // If not on the menu, do the sim's method continuously
      else if (currScreen == 1) {
        currScreen = one_body.update(keyState, event, renderer, text_renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        if (!currScreen) {
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
          SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x,
                             Options[(selectedScreen + 1) % 2].y + 210,
                             Options[(selectedScreen + 1) % 2].x + 200,
                             Options[(selectedScreen + 1) % 2].y + 210);
        }
      }
      // else if (currScreen == 2) {
      //   currScreen = TwoBody::update(ch, tabCycle, keyState, event, &cameraOffx, &cameraOffy,
      //                                renderer, text_renderer, inputs2, s1, s2);
      //   SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

      //   if (!currScreen) {
      //     SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      //     SDL_RenderDrawLine(renderer, Options[(selectedScreen + 1) % 2].x,
      //                        Options[(selectedScreen + 1) % 2].y + 210,
      //                        Options[(selectedScreen + 1) % 2].x + 200,
      //                        Options[(selectedScreen + 1) % 2].y + 210);
      //   }
      // }
    }

    // TODO This NEEDS to be moved in the fucking one body window
    // Same as all the run shit
    switch (currScreen) {
    case 1: {
      if (one_body.pause_) {
        continue;
      }

      one_body.calc(renderer);
      break;
    }
      // case 2: {
      // TwoBody::calc(s1, s2, renderer, cameraOffx, cameraOffy);
      // break;
      // }
    }
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
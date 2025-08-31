#include "Application.hpp"
#include "TextRenderer.hpp"


namespace OrbitSim
{
Application::Application() : window_(SDL_CreateWindow("OrbitSim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL)), renderer_(SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)), text_renderer_(renderer_), keystate_(SDL_GetKeyboardState(NULL))
{
  SDL_Init(SDL_INIT_EVERYTHING);
}

void Application::init()
{
  running_ = true;

  // TODO Make this an enum in the future
  selected_screen_ = 0;

  SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  renderMenu();
}

void Application::run()
{
  while(running_)
  {
    while(SDL_PollEvent(&event_))
    {
      handleEvents();
    }

    if(!running_)
      break;
  }
}

void Application::exit()
{
  running_ = false;
 
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Application::handleEvents()
{
  switch(event_.type)
  {
  case SDL_KEYDOWN:
    handleKeyboardInput();
    break;

  default:
    break;
  }
}

void Application::handleKeyboardInput()
{
  switch(event_.key.keysym.scancode)
  {
  case SDL_SCANCODE_ESCAPE:
    exit();
    return;

  case SDL_SCANCODE_TAB:
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer_, Options[selected_screen_].x, Options[selected_screen_].y + 210,
                       Options[selected_screen_].x + 200, Options[selected_screen_].y + 210);

    // TODO Reminder Enum this
    selected_screen_ = ((selected_screen_ + 1) % (SCREENS));

    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer_, Options[selected_screen_].x, Options[selected_screen_].y + 210,
                       Options[selected_screen_].x + 200, Options[selected_screen_].y + 210);

    SDL_RenderPresent(renderer_);

    break;

  case SDL_SCANCODE_S:
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer_);
    handleWindowChange();
    renderMenu();
    break;

  default:
    break;
  }
}

void Application::handleWindowChange()
{
  switch(selected_screen_)
  {
  case 0:
    one_body_.init(renderer_, text_renderer_);
    one_body_.run(renderer_, text_renderer_, keystate_);
    break;
  case 1:
    two_body_.init(renderer_, text_renderer_);
    two_body_.run(renderer_, text_renderer_, keystate_);
    break;
  }
}

void Application::renderMenu()
{
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);

  SDL_RenderDrawRect(renderer_, &Options[0]);
  text_renderer_.render(renderer_, "One Body", SCREEN_WIDTH / 2 - 45 - 150, SCREEN_HEIGHT / 2 - 50);
  text_renderer_.render(renderer_, "Simulation", SCREEN_WIDTH / 2 - 43 - 150,
                        SCREEN_HEIGHT / 2 - 25);

  SDL_RenderDrawRect(renderer_, &Options[1]);
  text_renderer_.render(renderer_, "Two Body", SCREEN_WIDTH / 2 - 45 + 150, SCREEN_HEIGHT / 2 - 50);
  text_renderer_.render(renderer_, "Simulation", SCREEN_WIDTH / 2 - 43 + 150,
                        SCREEN_HEIGHT / 2 - 25);

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer_, Options[selected_screen_].x, Options[selected_screen_].y + 210,
                     Options[selected_screen_].x + 200, Options[selected_screen_].y + 210);
  SDL_RenderPresent(renderer_);
}
} // namespace OrbitSim

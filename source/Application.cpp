#include "Application.hpp"

namespace OrbitSim
{
void Application::init()
{
  running_ = true;

  SDL_Init(SDL_INIT_EVERYTHING);

  window_ = SDL_CreateWindow("Sim", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                             SCREEN_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL);

  if(!window_)
  {
    std::cerr << "Error creating window: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  // TODO 10th to do on this make this a wrapper please
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

  if(!renderer_)
  {
    std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
    throw std::exception();
  }

  text_renderer_.init(renderer_);

  // TODO Make this an enum in the future
  selected_screen_ = 0;

  SDL_SetWindowFullscreen(window_, SDL_WINDOW_FULLSCREEN_DESKTOP);
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);

  keystate_ = SDL_GetKeyboardState(NULL);
  if(!keystate_)
  {
    std::cerr << "Error getting keyboard state: " << SDL_GetError() << "\n";
    throw std::exception();
  }

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

  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
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

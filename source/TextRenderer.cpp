#include "TextRenderer.hpp"

namespace OrbitSim
{

void TextRenderer::init(SDL_Renderer *renderer)
{
  SDL_Surface *surface = SDL_LoadBMP("include/font.bmp");
  texture_ = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);
}

void TextRenderer::render(SDL_Renderer *renderer, const std::string &input, const int &x,
                          const int &y) const
{
  int current_x_position = 0;

  // Probably a better way to do this but i dont give a fuck
  for(const auto &c : input)
  {
    if(c >= '0' && c <= '9')
    {
      source_.x = number_x_positions[c - '0'];
      source_.y = NUM_STARTY;
      source_.w = number_x_positions[c - '0' + 1] - number_x_positions[c - '0'];
      source_.h = NUM_HEIGHT;
    }

    else if(c >= 'a' && c <= 'z')
    {
      source_.x = lower_case_x_positions[c - 'a'];
      source_.y = LOWER_CASE_STARTY;
      source_.w = lower_case_x_positions[c - 'a' + 1] - lower_case_x_positions[c - 'a'];
      source_.h = LOWER_CASE_HEIGHT;
    }

    else if(c >= 'A' && c <= 'Z')
    {
      source_.x = upper_case_x_positions[c - 'A'];
      source_.y = UPPER_CASE_STARTY;
      source_.w = upper_case_x_positions[c - 'A' + 1] - upper_case_x_positions[c - 'A'];
      source_.h = UPPER_CASE_HEIGHT;
    }

    else if(c == ' ')
    {
      // This is a blank spot on the map
      source_.x = lower_case_x_positions[26] + 3;
      source_.y = LOWER_CASE_STARTY;
      source_.w = NUM_WIDTH;
      source_.h = LOWER_CASE_HEIGHT;
    }

    // TODO Get rid of Magic Numbers
    else if(c == '(')
    {
      source_.x = 131;
      source_.y = NUM_STARTY;
      source_.w = 9;
      source_.h = NUM_HEIGHT;
    }

    else if(c == ')')
    {
      source_.x = 183;
      source_.y = NUM_STARTY;
      source_.w = 9;
      source_.h = NUM_HEIGHT;
    }

    else if(c == '/')
    {
      source_.x = 287;
      source_.y = LOWER_CASE_STARTY;
      source_.w = 9;
      source_.h = LOWER_CASE_HEIGHT;
    }

    // Forced to do this since SDL_RenderCopy needs to define the dimensions for both the source
    // rectangle on the texture, and the destination on the window
    dest_.x = x + current_x_position;
    dest_.y = y;
    dest_.w = source_.w;
    dest_.h = source_.h;

    current_x_position += source_.w;
    SDL_RenderCopy(renderer, texture_, &source_, &dest_);
  }
}

void TextRenderer::clearRender(SDL_Renderer *renderer, const int &x, const int &y) const
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_Rect to_delete = {x + 1, y, NUM_WIDTH + 1, NUM_HEIGHT + 1};

  SDL_RenderDrawRect(renderer, &to_delete);
  SDL_RenderFillRect(renderer, &to_delete);
}

TextRenderer::~TextRenderer() { SDL_DestroyTexture(texture_); }
} // namespace OrbitSim

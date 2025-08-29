#include "TextInput.hpp"

namespace OrbitSim {
TextInput::TextInput()
{
  current_text_{""};
  border_{0, 0, 0, 0};
}

const std::string &TextInput::getText() const { return current_text_; }

const SDL_Rect &TextInput::getBorder() const { return border_; }

void TextInput::setText(std::string text) { current_text_ = std::move(text) }

void TextInput::setBorder(SDL_Rect border) { border_ = std::move(border); }

void TextInput::init(SDL_Renderer *renderer) const
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &border_);
}

void TextInput::type(const TextRenderer &text_renderer, SDL_Renderer *renderer, const char &input)
{
  int x_pixel_to_type = BORDER_OFFSET + border_.x + 11 * (current_text_.length());

  if (current_text_.length() >= LIMIT) {
    return;
  }

  current_text_.push_back(c);
  text_renderer.render(renderer, (std::string)c, x_pixel_to_type, border_.y + BORDER_OFFSET);
}

void TextInput::deleteChar(const TextRenderer &text_renderer, SDL_Renderer *renderer)
{
  if (current_text_.length() == 0) {
    return;
  }

  current_text_.pop_back();
  int x_pixel_to_type = border_.x + NUM_WIDTH * (current_text_.length());

  text_renderer->clearRender(renderer, x_pixel_to_type, border_.y + BORDER_OFFSET);
}

void TextInput::reset()
{
  current_text_ = "";
  border_ = {0, 0, 0, 0};
}
} // namespace OrbitSim

#pragma once

#include "Init.hpp"
#include "TextRenderer.hpp"

#include <string>

#define BORDER_OFFSET 1
#define LIMIT 8

namespace OrbitSim {
class TextInput {
private:
  std::string current_text_;
  SDL_Rect border_;

public:
  TextInput();

  const std::string &getText() const;

  const SDL_Rect &getBorder() const;

  void setText(std::string text);

  void setBorder(SDL_Rect border);

  void init(SDL_Renderer *renderer) const;

  void type(const TextRenderer &text_renderer, SDL_Renderer *renderer, const char &input);

  void deleteChar(const TextRenderer &text_rendere, SDL_Renderer *renderer);
};
} // namespace OrbitSim

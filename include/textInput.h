#ifndef TIN_H_
#define TIN_H_

#include <string>
#include <../SDL2/SDL.h>
#include "textRenderer.h"

#define BORDER_OFFSET 1
#define LIMIT 8

class TextInput {
private:
    std::string currentText;
    SDL_Rect border;

public:
    TextInput();

    std::string getText();

    SDL_Rect getBorder();

    void setText(std::string s);

    void setBorder(SDL_Rect r);

    void init(SDL_Renderer *renderer);

    void type(TextRenderer *tRenderer, SDL_Renderer *renderer, char *c);

    void deleteChar(TextRenderer *tRenderer, SDL_Renderer *renderer);
};
#endif
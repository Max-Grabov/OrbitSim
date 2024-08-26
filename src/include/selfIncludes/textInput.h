#include <string>
#include <SDL2/SDL.h>
#include <SelfIncludes/textRenderer.h>

#ifndef TIN_H_
#define TIN_H_

#define BORDER_OFFSET 1
#define LIMIT 8

class TextInput {
private:
    std::string currentText;
    SDL_Rect border;

public:
    TextInput(){
        this->currentText = "";
        this->border = {0, 0, 0, 0};
    }

    std::string getText(){
        return this->currentText;
    }

    SDL_Rect getBorder(){
        return this->border;
    }

    void setText(std::string s){
        this->currentText = s;
    }

    void setBorder(SDL_Rect r){
        this->border = r;
    }

    void init(SDL_Renderer *renderer){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &this->border);
    }

    void type(TextRenderer *tRenderer, SDL_Renderer *renderer, char *c){
        int currXPixel = BORDER_OFFSET + this->border.x + 11*(this->currentText.length());

        if(this->currentText.length() >= LIMIT){
            return;
        }

        this->currentText.push_back(*c);
        tRenderer->render(renderer, (std::string)c, currXPixel, this->border.y + BORDER_OFFSET);
    }

    void deleteChar(TextRenderer *tRenderer, SDL_Renderer *renderer){
        if(this->currentText.length() == 0){
            return;
        }

        this->currentText.pop_back();
        int newXPixel = this->border.x + NUM_WIDTH*(this->currentText.length());
        tRenderer->clearRender(renderer, newXPixel, this->border.y + BORDER_OFFSET);
    }
};
#endif
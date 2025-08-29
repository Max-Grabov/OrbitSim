#include "../include/textInput.h"

TextInput::TextInput(){
    this->currentText = "";
    this->border = {0, 0, 0, 0};
}

std::string TextInput::getText(){
    return this->currentText;
}

SDL_Rect TextInput::getBorder(){
    return this->border;
}

void TextInput::setText(std::string s){
    this->currentText = s;
}

void TextInput::setBorder(SDL_Rect r){
    this->border = r;
}

void TextInput::init(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &this->border);
}

void TextInput::type(TextRenderer *tRenderer, SDL_Renderer *renderer, char *c){
    int currXPixel = BORDER_OFFSET + this->border.x + 11*(this->currentText.length());

    if(this->currentText.length() >= LIMIT){
        return;
    }

    this->currentText.push_back(*c);
    tRenderer->render(renderer, (std::string)c, currXPixel, this->border.y + BORDER_OFFSET);
}

void TextInput::deleteChar(TextRenderer *tRenderer, SDL_Renderer *renderer){
    if(this->currentText.length() == 0){
        return;
    }

    this->currentText.pop_back();
    int newXPixel = this->border.x + NUM_WIDTH*(this->currentText.length());
    tRenderer->clearRender(renderer, newXPixel, this->border.y + BORDER_OFFSET);
}
#pragma once

#include "Menu.hpp"
#include "Window.hpp"
#include "Init.hpp"
#include "Sphere.hpp"
#include "TextRenderer.hpp"
#include "TextInput.hpp"

#include <array>

namespace OrbitSim
{
class OneBody : public Window 
{
public:
    void init (SDL_Renderer *renderer) override;
	
    void reset() override;

    void run() override;

    static void calc(SDL_Renderer *renderer);

    static void initHotbar(SDL_Renderer *renderer);

    static std::vector<TextInput*> initTextBox();

    static int update(char *ch, int *tabCycle,
                    const Uint8 *keyState, SDL_Event e,
                    int *cameraOffx, int *cameraOffy,
                    SDL_Renderer *renderer, TextRenderer
                    *tRenderer, std::vector <TextInput*> inputs,
                    Sphere *s1, Sphere *s2, bool *pause);
private:
    Sphere sphere_one_, sphere_two_;
    int camera_offset_x_, camera_offset_y_;
    bool pause_;
    std::array<TextInput, 4> textboxes_;
    int selected_box_;

    void InitHotbar(SDL_Renderer *renderer);
    
};
}

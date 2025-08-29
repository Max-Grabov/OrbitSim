#pragma once

#include <SDL2/SDL.h>

namespace OrbitSim
{
class Window
{
	virtual void init(SDL_Renderer *renderer) = 0;

	virtual void reset() = 0;
	
	virtual void run() = 0;
};
}

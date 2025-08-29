#include "OneBody.hpp"

namespace OrbitSim {
void OneBody::init(SDL_Renderer *renderer const TexRenderer &text_renderer)
{
  OneBody::initHotbar(renderer, text_renderer);
}
void OneBody::initHotbar(SDL_Renderer *renderer, const TextRenderer &text_renderer)
{
  text_renderer.render(renderer, "Mass One(Tg)", 10, 20);
  text_renderer.render(renderer, "Mass Two(Gg)", 10, 60);

  text_renderer.render(renderer, "Velocity Two X(m/s)", 245, 20);
  text_renderer.render(renderer, "Velocity Two Y(m/s)", 245, 60);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

  SDL_RenderDrawLine(renderer, 0, HOTBAR_H, 2 * SCREEN_WIDTH, HOTBAR_H);

  const auto initial_border = textboxes_[0].getBorder();

  SDL_RenderDrawLine(renderer, initial_border.x, initial_border.y + initial_border.h + 3,
                     initial_border.x + initial_border.w, initial_border.y + initial_border.h + 3);

  for (size_t i = 0; i < 4; ++i) {
    text_input[i].setBorder(textbox_borders_[i]);
    text_input[i].init(renderer);
  }
}

void OneBody::init(SDL_Renderer *renderer)
{
  sphere_one_.radius = 100;
  sphere_two_.radius = 25;

  sphere_one_.position.x = 0;
  sphere_one_.position.y = 0 + HOTBAR_H;

  sphere_two_.position.x = 212;
  sphere_two_.position.y = 212 + HOTBAR_H;

  sphere_two_.setVelocity(
      {textboxes_[2].getText() == "" ? 900 : std::stod(textboxes_[2].getText(), nullptr),
       textboxes_[3].getText() == "" ? -900 : std::stod(textboxes_[3].getText(), nullptr), 0});

  sphere_one_.Draw(renderer, OFFSET_X, OFFSET_Y);
  sphere_two_.Draw(renderer, OFFSET_X, OFFSET_Y);

  SDL_RenderPresent(renderer);
}

void OneBody::reset()
{
  sphere_one_.mass = BIG_MASS;
  sphere_two_.mass = SMALL_MASS;
  selected_box_ = 0;
  camera_offset_x_ = camera_offset_y_ = 0;

  for (size_t i = 0; i < 4; ++i) {
    textboxes[i].reset();
  }
}

void OneBody::calc(SDL_Renderer *renderer)
{

  // Fill the rectangle every frame with white, effectively clearing this
  // portion of the screen
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &Screen);

  // Setup math
  double rad =
      (Object::distance(*s1, *s2) - sphere_one_.radius - sphere_two_.radius) / PIXELCONVERT;

  if (rad < 1e-6)
    rad = 1e-6;

  double forceG = (G * sphere_two_.mass * sphere_one_.mass) / (pow(rad, 2));

  // Use theta from -pi to pi
  double theta;

  if (sphere_two_.position.x == sphere_one_.position.x) {
    theta = (sphere_two_.position.y > sphere_one_.position.y) ? M_PI / 2 : -M_PI / 2;
  }
  else {
    // So OP
    theta = atan2(1.0 * (sphere_two_.position.y - sphere_one_.position.y),
                  1.0 * (sphere_two_.position.x - sphere_one_.position.x));
  }

  vector oldDistance = sphere_two_.position;

  // Kinematics
  double FxG = -cos(theta) * forceG;
  double FyG = -sin(theta) * forceG;

  sphere_two_.position.x += 0.5 * PIXELCONVERT * sphere_two_.acceleration.x * FRAME * FRAME +
                            sphere_two_.velocity.x * FRAME;
  sphere_two_.position.y += 0.5 * PIXELCONVERT * sphere_two_.acceleration.y * FRAME * FRAME +
                            sphere_two_.velocity.y * FRAME;

  // For error correction
  double newTheta = atan2(sphere_two_.position.y - sphere_one_.position.y,
                          sphere_two_.position.x - sphere_one_.position.x);

  double newRad = Object::distance(*s1, *s2) - sphere_one_.radius - sphere_two_.radius;
  double newFG = (G * sphere_two_.mass * sphere_one_.mass) / (newRad * newRad);

  double newFXG = -cos(newTheta) * newFG;
  double newFYG = -sin(newTheta) * newFG;

  double newAccelx = newFXG / sphere_two_.mass;
  double newAccely = newFYG / sphere_two_.mass;

  // Try to counteract error cummulation via looking at next accel
  sphere_two_.velocity.x += 0.5 * (sphere_two_.acceleration.x + newAccelx) * FRAME;
  sphere_two_.velocity.y += 0.5 * (sphere_two_.acceleration.y + newAccely) * FRAME;

  sphere_two_.acceleration.x = newAccelx;
  sphere_two_.acceleration.y = newAccely;

  SDL_Delay(100);

  // Draw the new positions
  sphere_one_.Draw(renderer, OFFSET_X + cameraOffx, OFFSET_Y + cameraOffy);
  sphere_two_.Draw(renderer, OFFSET_X + cameraOffx, OFFSET_Y + cameraOffy);
}

int OneBody::update(char *ch, int *tabCycle, const Uint8 *keyState, SDL_Event e,
                    int camera_offset_x_, int camera_offset_y_, SDL_Renderer *renderer,
                    TextRenderer *tRenderer, std::vector<TextInput *> inputs, Sphere *s1,
                    Sphere *s2, bool *pause)
{
  vectord v;
  std::string oneChange;

  switch (e.type) {
  case SDL_KEYDOWN:
    switch (e.key.keysym.scancode) {
    case SDL_SCANCODE_ESCAPE: {
      reset(s1, s2, tabCycle, cameraOffx, cameraOffy, inputs);
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);

      Menu::loadMenu(renderer, tRenderer);
      return 0;
    }

    case SDL_SCANCODE_TAB: {
      // Clear last line
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(
          renderer, inputs.at(*tabCycle)->getBorder().x,
          inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3,
          inputs.at(*tabCycle)->getBorder().x + inputs.at(*tabCycle)->getBorder().w,
          inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3);

      *tabCycle = (*tabCycle + 1) % 4;

      // Add new line
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(
          renderer, inputs.at(*tabCycle)->getBorder().x,
          inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3,
          inputs.at(*tabCycle)->getBorder().x + inputs.at(*tabCycle)->getBorder().w,
          inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3);
      break;
    }

    case SDL_SCANCODE_A: {
      oneChange = inputs.at(*tabCycle)->getText();

      if (oneChange == "") {
        break;
      }

      // Get values
      switch (*tabCycle) {
      case 0:
        sphere_one_.mass = 1000000000000 * std::stod(oneChange, nullptr);
        break;
      case 1:
        sphere_two_.mass = 1000000000 * std::stod(oneChange, nullptr);
        break;
      case 2:
        v = {std::stod(oneChange, nullptr), sphere_two_.velocity.y, 0};
        sphere_two_.setVelocity(v);
        break;
      case 3:
        v = {sphere_two_.velocity.x, std::stod(oneChange, nullptr), 0};
        sphere_two_.setVelocity(v);
      }
      break;
    }

    case SDL_SCANCODE_P: {
      *pause = !*pause;
      break;
    }

    case SDL_SCANCODE_0: {
      *ch = '0';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_1: {
      *ch = '1';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_2: {
      *ch = '2';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_3: {
      *ch = '3';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_4: {
      *ch = '4';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_5: {
      *ch = '5';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_6: {
      *ch = '6';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_7: {
      *ch = '7';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_8: {
      *ch = '8';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_9: {
      *ch = '9';
      inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
      break;
    }

    case SDL_SCANCODE_BACKSPACE: {
      inputs.at(*tabCycle)->deleteChar(tRenderer, renderer);
      break;
    }

    default:
      break;
    }

    if (keyState[SDL_SCANCODE_UP]) {
      camera_offset_y_ -= 5;
    }
    if (keyState[SDL_SCANCODE_DOWN]) {
      camera_offset_y_ += 5;
    }
    if (keyState[SDL_SCANCODE_RIGHT]) {
      camera_offset_x_ += 5;
    }
    if (keyState[SDL_SCANCODE_LEFT]) {
      camera_offset_x_ -= 5;
    }
    return 1;

  default:
    return 1;
  }
}
} // namespace OrbitSim

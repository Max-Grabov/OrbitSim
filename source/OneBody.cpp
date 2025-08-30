#include "OneBody.hpp"

namespace OrbitSim {
void OneBody::init(SDL_Renderer *renderer, const TextRenderer &text_renderer)
{
  initHotbar(renderer, text_renderer);
  initData(renderer);
}

// TODO thanks sdl for not using uint8_t
void OneBody::run(SDL_Renderer *renderer, const TextRenderer &text_renderer, const Uint8 *keystate)
{
  while(running_)
  {
    SDL_PollEvent(&current_event_);
    handleEvents(current_event_, renderer, text_renderer, keystate);

    if(!pause_)
    {
      calc(renderer);
    }

    SDL_RenderPresent(renderer);
  }
  std::cout << "leaving\n";
}

void OneBody::exit(SDL_Renderer *renderer)
{
  sphere_one_.mass_ = BIG_MASS;
  sphere_two_.mass_ = SMALL_MASS;
  selected_box_ = 0;
  camera_offset_x_ = camera_offset_y_ = 0;

  for (size_t i = 0; i < 4; ++i) {
    textboxes_[i].reset();
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  running_ = false;
}

void OneBody::handleEvents(const SDL_Event &event, SDL_Renderer *renderer, const TextRenderer &text_renderer, const Uint8 *keystate)
{
  switch (event.type) {
    case SDL_KEYDOWN:
      handleKeyboardInput(event, renderer, text_renderer, keystate);
      break;
  }
}

void OneBody::handleKeyboardInput(const SDL_Event &event, SDL_Renderer *renderer, const TextRenderer &text_renderer, const Uint8 *keystate)
{
  const auto border = textboxes_.at(selected_box_).getBorder();

  // TODO remove this bullshit
  std::string new_velocity_value;

  switch (event.key.keysym.scancode) {
    case SDL_SCANCODE_ESCAPE: {
      exit(renderer);
      return;
    }

    // TODO Holy shit a renderer wrapper is a must wtf is this block
    case SDL_SCANCODE_TAB: {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(renderer, border.x, border.y + border.h + 3, border.x + border.w,
                         border.y + border.h + 3);

      selected_box_ = (selected_box_ + 1) % 4;

      const auto new_border = textboxes_.at(selected_box_).getBorder();

      // Add new line
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderDrawLine(renderer, new_border.x, new_border.y + new_border.h + 3,
                         new_border.x + new_border.w, new_border.y + new_border.h + 3);
      break;
    }

    case SDL_SCANCODE_A: {
      new_velocity_value = textboxes_.at(selected_box_).getText();

      if (new_velocity_value == "") {
        break;
      }

      // TODO This is utter dogshit change this later
      switch (selected_box_) {
      case 0:
        sphere_one_.mass_ = 1000000000000 * std::stod(new_velocity_value, nullptr);
        break;
      case 1:
        sphere_two_.mass_ = 1000000000 * std::stod(new_velocity_value, nullptr);
        break;
      case 2:
        sphere_two_.setVelocity(
            {std::stod(new_velocity_value, nullptr), sphere_two_.velocity_.y_, 0});
        break;
      case 3:
        sphere_two_.setVelocity(
            {sphere_two_.velocity_.x_, std::stod(new_velocity_value, nullptr), 0});
      }
      break;
    }

    case SDL_SCANCODE_P: {
      pause_ = !pause_;
      break;
    }

    // TODO Look into making this if else and not spam this
    case SDL_SCANCODE_0: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '0');
      break;
    }

    case SDL_SCANCODE_1: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '1');
      break;
    }

    case SDL_SCANCODE_2: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '2');
      break;
    }

    case SDL_SCANCODE_3: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '3');
      break;
    }

    case SDL_SCANCODE_4: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '4');
      break;
    }

    case SDL_SCANCODE_5: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '5');
      break;
    }

    case SDL_SCANCODE_6: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '6');
      break;
    }

    case SDL_SCANCODE_7: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '7');
      break;
    }

    case SDL_SCANCODE_8: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '8');
      break;
    }

    case SDL_SCANCODE_9: {
      textboxes_.at(selected_box_).type(text_renderer, renderer, '9');
      break;
    }

    case SDL_SCANCODE_BACKSPACE: {
      textboxes_.at(selected_box_).deleteChar(text_renderer, renderer);
      break;
    }

    default:
      break;

    // TODO probably change this
    if (keystate[SDL_SCANCODE_UP]) {
      camera_offset_y_ -= 5;
    }
    if (keystate[SDL_SCANCODE_DOWN]) {
      camera_offset_y_ += 5;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
      camera_offset_x_ += 5;
    }
    if (keystate[SDL_SCANCODE_LEFT]) {
      camera_offset_x_ -= 5;
    }
  }
}

void OneBody::initHotbar(SDL_Renderer *renderer, const TextRenderer &text_renderer)
{
  std::cout << "initing onebody hotbar\n";
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
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
    textboxes_[i].setBorder(textbox_borders_[i]);
    textboxes_[i].init(renderer);
  }
}

void OneBody::initData(SDL_Renderer *renderer)
{
  std::cout << "initData OneBody\n";
  sphere_one_.mass_ = BIG_MASS;
  sphere_two_.mass_ = SMALL_MASS;

  sphere_one_.radius_ = 100;
  sphere_two_.radius_ = 25;

  sphere_one_.position_.x_ = 0;
  sphere_one_.position_.y_ = 0 + HOTBAR_H;

  sphere_two_.position_.x_ = 212;
  sphere_two_.position_.y_ = 212 + HOTBAR_H;

  sphere_two_.setVelocity(
      {textboxes_[2].getText() == "" ? 900 : std::stod(textboxes_[2].getText(), nullptr),
       textboxes_[3].getText() == "" ? -900 : std::stod(textboxes_[3].getText(), nullptr), 0});

  sphere_one_.Draw(renderer, OFFSET_X, OFFSET_Y);
  sphere_two_.Draw(renderer, OFFSET_X, OFFSET_Y);

  running_ = true;

  SDL_RenderPresent(renderer);
}

void OneBody::calc(SDL_Renderer *renderer)
{

  // Fill the rectangle every frame with white, effectively clearing this
  // portion of the screen
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(renderer, &Screen);

  // Setup math
  double distance_from_surface =
      (Object::distance(sphere_one_, sphere_two_) - sphere_one_.radius_ - sphere_two_.radius_) /
      PIXELCONVERT;

  if (distance_from_surface < 1e-6)
    distance_from_surface = 1e-6;

  double force_gravity =
      (G * sphere_two_.mass_ * sphere_one_.mass_) / (pow(distance_from_surface, 2));

  // Use theta from -pi to pi
  double theta;

  if (sphere_two_.position_.x_ == sphere_one_.position_.x_) {
    theta = (sphere_two_.position_.y_ > sphere_one_.position_.y_) ? M_PI / 2 : -M_PI / 2;
  }
  else {
    // So OP
    theta = atan2(1.0 * (sphere_two_.position_.y_ - sphere_one_.position_.y_),
                  1.0 * (sphere_two_.position_.x_ - sphere_one_.position_.x_));
  }

  Vector old_position = sphere_two_.position_;

  // Kinematics
  double force_gravity_x = -cos(theta) * force_gravity;
  double force_gravity_y = -sin(theta) * force_gravity;

  sphere_two_.position_.x_ += 0.5 * PIXELCONVERT * sphere_two_.acceleration_.x_ * FRAME * FRAME +
                              sphere_two_.velocity_.x_ * FRAME;
  sphere_two_.position_.y_ += 0.5 * PIXELCONVERT * sphere_two_.acceleration_.y_ * FRAME * FRAME +
                              sphere_two_.velocity_.y_ * FRAME;

  // TODO I am guaranteeing I did something very wrong here when i first wrote this.
  // TODO Fix these calculations and ensure calculations make actual sense

  // For error correction
  double new_theta = atan2(sphere_two_.position_.y_ - sphere_one_.position_.y_,
                           sphere_two_.position_.x_ - sphere_one_.position_.x_);

  double new_distance_from_surface =
      Object::distance(sphere_one_, sphere_two_) - sphere_one_.radius_ - sphere_two_.radius_;
  double new_force_gravity = (G * sphere_two_.mass_ * sphere_one_.mass_) /
                             (new_distance_from_surface * new_distance_from_surface);

  double new_force_gravity_x = -cos(new_theta) * new_force_gravity;
  double new_force_gravity_y = -sin(new_theta) * new_force_gravity;

  double new_acceleration_x = new_force_gravity_x / sphere_two_.mass_;
  double new_acceleration_y = new_force_gravity_y / sphere_two_.mass_;

  // Try to counteract error cummulation via looking at next accel
  sphere_two_.velocity_.x_ += 0.5 * (sphere_two_.acceleration_.x_ + new_acceleration_x) * FRAME;
  sphere_two_.velocity_.y_ += 0.5 * (sphere_two_.acceleration_.y_ + new_acceleration_y) * FRAME;

  sphere_two_.acceleration_.x_ = new_acceleration_x;
  sphere_two_.acceleration_.y_ = new_acceleration_y;

  // TODO Why was this done before? also this should not be in this method
  SDL_Delay(100);

  sphere_one_.Draw(renderer, OFFSET_X + camera_offset_x_, OFFSET_Y + camera_offset_y_);
  sphere_two_.Draw(renderer, OFFSET_X + camera_offset_x_, OFFSET_Y + camera_offset_y_);
}
} // namespace OrbitSim

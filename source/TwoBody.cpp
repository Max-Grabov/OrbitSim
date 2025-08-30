// #include "TwoBody.hpp"

// void TwoBody::init(std::vector<TextInput *> inputs, SDL_Renderer *renderer, Sphere *s1, Sphere
// *s2)
// {

//   // Init stats
//   s1->radius = 60;
//   s2->radius = 40;

//   s1->position.x = 200;
//   s1->position.y = -30 + HOTBAR_H;

//   s2->position.x = -200;
//   s2->position.y = 100 + HOTBAR_H;

//   s2->velocity = {inputs.at(2)->getText() == "" ? 120 : std::stod(inputs.at(2)->getText(),
//   nullptr),
//                   inputs.at(3)->getText() == "" ? 430 : std::stod(inputs.at(3)->getText(),
//                   nullptr), 100};

//   s1->velocity = {
//       inputs.at(2)->getText() == "" ? -600 : std::stod(inputs.at(2)->getText(), nullptr),
//       inputs.at(3)->getText() == "" ? -193 : std::stod(inputs.at(3)->getText(), nullptr), 0};

//   s1->Draw(renderer, OFFSET_X, OFFSET_Y);
//   s2->Draw(renderer, OFFSET_X, OFFSET_Y);

//   SDL_RenderPresent(renderer);
// }

// void TwoBody::initHotbar(SDL_Renderer *renderer, TextRenderer *tRenderer,
//                          std::vector<TextInput *> inputs)
// {
//   tRenderer->render(renderer, "Mass One(Tg)", 10, 20);
//   tRenderer->render(renderer, "Mass Two(Gg)", 10, 60);

//   tRenderer->render(renderer, "Velocity One X(m/s)", 245, 20);
//   tRenderer->render(renderer, "Velocity One Y(m/s)", 245, 60);

//   tRenderer->render(renderer, "Velocity Two X(m/s)", 538, 20);
//   tRenderer->render(renderer, "Velocity Two Y(m/s)", 538, 60);

//   SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

//   SDL_RenderDrawLine(renderer, 0, HOTBAR_H, 2 * SCREEN_WIDTH, HOTBAR_H);

//   SDL_RenderDrawLine(renderer, inputs.at(0)->getBorder().x,
//                      inputs.at(0)->getBorder().y + +inputs.at(0)->getBorder().h + 3,
//                      inputs.at(0)->getBorder().x + inputs.at(0)->getBorder().w,
//                      inputs.at(0)->getBorder().y + +inputs.at(0)->getBorder().h + 3);

//   for (auto const &i : inputs) {
//     i->init(renderer);
//   }
// }

// std::vector<TextInput *> TwoBody::initTextBox()
// {
//   std::vector<TextInput *> inputs;
//   TextInput *massObject1 = new TextInput();
//   TextInput *massObject2 = new TextInput();
//   TextInput *velObject1 = new TextInput();
//   TextInput *velObject2 = new TextInput();
//   TextInput *velObject3 = new TextInput();
//   TextInput *velObject4 = new TextInput();

//   inputs.push_back(massObject1);
//   inputs.push_back(massObject2);
//   inputs.push_back(velObject1);
//   inputs.push_back(velObject2);
//   inputs.push_back(velObject3);
//   inputs.push_back(velObject4);

//   massObject1->setBorder(oneInputMass);
//   massObject2->setBorder(twoInputMass);
//   velObject1->setBorder(oneInputVel);
//   velObject2->setBorder(twoInputVel);
//   velObject3->setBorder(threeInputVel);
//   velObject4->setBorder(fourInputVel);

//   return inputs;
// }

// void TwoBody::calc(Sphere *s1, Sphere *s2, SDL_Renderer *renderer, int cameraOffx, int
// cameraOffy)
// {
//   SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//   SDL_RenderFillRect(renderer, &Screen);

//   // Setup math
//   double rad = (Object::distance(*s1, *s2) - s1->radius - s2->radius) / PIXELCONVERT;

//   if (rad < 1e-6)
//     rad = 1e-6;

//   double forceG = (G * s2->mass * s1->mass) / (pow(rad, 2));

//   // Use theta from -pi to pi
//   double theta;

//   if (s2->position.x == s1->position.x) {
//     theta = (s2->position.y > s1->position.y) ? M_PI / 2 : -M_PI / 2;
//   }
//   else {
//     theta = atan2(1.0 * (s2->position.y - s1->position.y), 1.0 * (s2->position.x -
//     s1->position.x));
//   }

//   vector oldDistance = s2->position;

//   // Kinematics
//   double FxG = -cos(theta) * forceG;
//   double FyG = -sin(theta) * forceG;

//   s2->position.x +=
//       0.5 * PIXELCONVERT * s2->acceleration.x * FRAME * FRAME + s2->velocity.x * FRAME;
//   s2->position.y +=
//       0.5 * PIXELCONVERT * s2->acceleration.y * FRAME * FRAME + s2->velocity.y * FRAME;

//   s1->position.x +=
//       0.5 * PIXELCONVERT * s1->acceleration.x * FRAME * FRAME + s1->velocity.x * FRAME;
//   s1->position.y +=
//       0.5 * PIXELCONVERT * s1->acceleration.y * FRAME * FRAME + s1->velocity.y * FRAME;

//   // Look at next fram for more accurate data
//   double newTheta = atan2(s2->position.y - s1->position.y, s2->position.x - s1->position.x);

//   double newRad = Object::distance(*s1, *s2) - s1->radius - s2->radius;
//   double newFG = (G * s2->mass * s1->mass) / (newRad * newRad);

//   double newFXG = -cos(newTheta) * newFG;
//   double newFYG = -sin(newTheta) * newFG;

//   double newAccelx = newFXG / s2->mass;
//   double newAccely = newFYG / s2->mass;

//   double newAccelx2 = -newFXG / s2->mass;
//   double newAccely2 = -newFYG / s2->mass;

//   s2->velocity.x += 0.5 * (s2->acceleration.x + newAccelx) * FRAME;
//   s2->velocity.y += 0.5 * (s2->acceleration.y + newAccely) * FRAME;

//   s1->velocity.x += 0.5 * (s2->acceleration.x + newAccelx2) * FRAME;
//   s1->velocity.y += 0.5 * (s2->acceleration.y + newAccely2) * FRAME;

//   s2->acceleration.x = newAccelx;
//   s2->acceleration.y = newAccely;

//   s1->acceleration.x = -newAccelx;
//   s1->acceleration.y = -newAccely;

//   SDL_Delay(100);

//   // std::cout << "pos 1 " << s1->position.x << " " << s1->position.y <<
//   // std::endl; std::cout << "pos 2 " << s2->position.x << " " << s2->position.y
//   // << std::endl;

//   // Draw the new positions
//   s1->Draw(renderer, OFFSET_X + cameraOffx, OFFSET_Y + cameraOffy);
//   s2->Draw(renderer, OFFSET_X + cameraOffx, OFFSET_Y + cameraOffy);
// }

// void TwoBody::reset(Sphere *s1, Sphere *s2, int *tabCycle, int *cameraOffx, int *cameraOffy,
//                     std::vector<TextInput *> inputs)
// {
//   s1->mass = BIG_MASS;
//   s2->mass = SMALL_MASS;
//   *tabCycle = 0;
//   *cameraOffx = *cameraOffy = 0;
//   delete inputs[0];
//   delete inputs[1];
//   delete inputs[2];
//   delete inputs[3];
//   delete inputs[4];
//   delete inputs[5];
// }

// int TwoBody::update(char *ch, int *tabCycle, const Uint8 *keyState, SDL_Event e, int *cameraOffx,
//                     int *cameraOffy, SDL_Renderer *renderer, TextRenderer *tRenderer,
//                     std::vector<TextInput *> inputs, Sphere *s1, Sphere *s2)
// {

//   vectord v;
//   std::string oneChange;

//   switch (e.type) {
//   case SDL_KEYDOWN:
//     switch (e.key.keysym.scancode) {
//     case SDL_SCANCODE_ESCAPE: {
//       reset(s1, s2, tabCycle, cameraOffx, cameraOffy, inputs);
//       SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//       SDL_RenderClear(renderer);

//       Menu::loadMenu(renderer, tRenderer);
//       return 0;
//     }

//     case SDL_SCANCODE_TAB: {
//       // Clear last line
//       SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//       SDL_RenderDrawLine(
//           renderer, inputs.at(*tabCycle)->getBorder().x,
//           inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3,
//           inputs.at(*tabCycle)->getBorder().x + inputs.at(*tabCycle)->getBorder().w,
//           inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3);

//       *tabCycle = (*tabCycle + 1) % 6;

//       // Add new line
//       SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//       SDL_RenderDrawLine(
//           renderer, inputs.at(*tabCycle)->getBorder().x,
//           inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3,
//           inputs.at(*tabCycle)->getBorder().x + inputs.at(*tabCycle)->getBorder().w,
//           inputs.at(*tabCycle)->getBorder().y + +inputs.at(*tabCycle)->getBorder().h + 3);
//       break;
//     }

//     case SDL_SCANCODE_A: {
//       oneChange = inputs.at(*tabCycle)->getText();

//       if (oneChange == "") {
//         break;
//       }

//       // Get values
//       switch (*tabCycle) {
//       case 0:
//         s1->mass = 1000000000000 * std::stod(oneChange, nullptr);
//         break;
//       case 1:
//         s2->mass = 1000000000 * std::stod(oneChange, nullptr);
//         break;
//       case 2:
//         v = {std::stod(oneChange, nullptr), s1->velocity.y, 0};
//         s1->setVelocity(v);
//         break;
//       case 3:
//         v = {s1->velocity.x, std::stod(oneChange, nullptr), 0};
//         s1->setVelocity(v);
//         break;
//       case 4:
//         v = {std::stod(oneChange, nullptr), s2->velocity.y, 0};
//         s2->setVelocity(v);
//         break;
//       case 5:
//         v = {s2->velocity.x, std::stod(oneChange, nullptr), 0};
//         s2->setVelocity(v);
//         break;
//       }
//       break;
//     }

//       // case SDL_SCANCODE_P:
//       // {
//       //     *pause = !*pause;
//       //     break;
//       // }

//     case SDL_SCANCODE_0: {
//       *ch = '0';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_1: {
//       *ch = '1';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_2: {
//       *ch = '2';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_3: {
//       *ch = '3';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_4: {
//       *ch = '4';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_5: {
//       *ch = '5';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_6: {
//       *ch = '6';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_7: {
//       *ch = '7';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_8: {
//       *ch = '8';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_9: {
//       *ch = '9';
//       inputs.at(*tabCycle)->type(tRenderer, renderer, ch);
//       break;
//     }

//     case SDL_SCANCODE_BACKSPACE: {
//       inputs.at(*tabCycle)->deleteChar(tRenderer, renderer);
//       break;
//     }

//     default:
//       break;
//     }

//     if (keyState[SDL_SCANCODE_UP]) {
//       *cameraOffy -= 5;
//     }
//     if (keyState[SDL_SCANCODE_DOWN]) {
//       *cameraOffy += 5;
//     }
//     if (keyState[SDL_SCANCODE_RIGHT]) {
//       *cameraOffx += 5;
//     }
//     if (keyState[SDL_SCANCODE_LEFT]) {
//       *cameraOffx -= 5;
//     }
//     return 2;

//   default:
//     return 2;
//   }
// }

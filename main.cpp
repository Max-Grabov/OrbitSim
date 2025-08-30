#include "include/Application.hpp"

int main(int argc, char *argv[])
{
  OrbitSim::Application application;

  try {
    application.init();
  }
  catch (const std::exception &) {
    return EXIT_FAILURE;
  }

  application.run();
  std::cout << "exiting safely\n";
  return EXIT_SUCCESS;
}
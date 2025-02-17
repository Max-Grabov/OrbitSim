# OrbitSim
A 2D Large body simulator built entirely with SDL2 and CMake and C++, Currently supports 1 Body Simulations.

Options in the simulator include:
- Moving the frame of reference
- Editing the Mass and Velocity of each large body
- Choosing simulators from a menu

## Compiling and Running
```bash
git clone https://github.com/Max-Grabov/OrbitSim.git
# In the destination of the clone, either do
make

# OR

mingw32-make

# Depending on your version. Alternatively:

g++ -I src/resources/include -L src/lib -o main main.cpp src/resources/source/menu.cpp src/resources/source/objects.cpp src/resources/source/oneBody.cpp src/resources/source/sphere.cpp src/resources/source/textInput.cpp src/resources/source/textRenderer.cpp src/resources/source/init.cpp -lmingw32 -lSDL2main -lSDL2

# Then run it
./main
```
## Contributions
To report a bug, contribute to the codebase, or request a feature, submit an issue or pull request
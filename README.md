# 4/19/2025 Update
Now that I know more knowledge about c++ and better practices from work and other experiences i've done, I plan to remake this project completely. Not sure if I'll keep the SDL2 or switch to a different framework.

In addition, since I have a new interest in Rust, I'll take the time once the c++ remake is done to release a different version of the project in Rust as well for my own learning.

For now, I have to finish my semester and my own work strongly ^_^

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
# OrbitSim
A 2D Large body simulator built entirely with SDL2 and CMake and C++, Currently supports 1 Body Simulations.

Options in the simulator include:
- Moving the frame of reference
- Editing the Mass and Velocity of each large body
- Choosing simulators from a menu

## Compiling and Running
```bash
git clone https://github.com/Max-Grabov/OrbitSim.git
# In the destination of the clone, use this line to compile
g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
./main
```
## Contributions
To report a bug, contribute to the codebase, or request a feature, submit an issue or pull request
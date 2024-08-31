# OrbitSim
2D object simulator, currently contains 1 Body motion.

Built entirely with SDL2 and cmake

To compile:
g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2

ToDo
- [x] Add menu system to choose different simulations
- [ ] Actually make different simulations
- [x] Set up typing restriction Changeable with a key
- [x] Use user input to alter current object values
- [ ] Make it look pretty (yeah...)
- [ ] Complete standard header

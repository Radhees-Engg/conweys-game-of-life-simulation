# conweys-game-of-life-simulation  

## Conway's Game of Life

Conway's Game of Life is a classic zero-player cellular automaton — you set an initial pattern and watch it evolve. Each cell is either alive or dead, and each generation the grid updates based on four rules: live cells with fewer than 2 or more than 3 neighbours die, live cells with 2–3 neighbours survive, and dead cells with exactly 3 neighbours come to life. Simple rules, surprisingly complex behaviour.

## How it's built

The simulation runs on a **100×100 toroidal (wrapping) grid** — edges connect to the opposite side, so no cell ever hits a wall. Written in C++ with two classes: `World` handles the simulation logic (neighbour counting, rule application, double-buffered grid updates) and `Render` handles drawing and camera input via Raylib. The default starting pattern is the **Acorn** methuselah, which takes 5000+ generations to fully stabilise. An oscillator and a spaceship are also in the code, just commented out.

## controls 

To Zoom in and Out → Mouse Wheel  
To move the gird → Arrow Keys (Up, Down, Right, left)  

## Dependencies 

Raylib and C++ 

## Instructions 

Make sure raylib is installed, and just open the given file that's it. 

Video: [RadheesBala](https://www.linkedin.com/in/radhees-bala/)

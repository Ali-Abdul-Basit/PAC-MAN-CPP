# PAC-MAN Game in C++

A text-based console implementation of the classic arcade game Pac-Man, developed as part of the Programming Fundamentals course.

## 🕹️ Game Overview
The game initializes a grid-based maze inside the Windows console terminal. The user controls Pac-Man (`P`) to navigate through a field of dots while evading an automated ghost (`G`) that moves randomly through available paths.

### Rules & Gameplay
- **Controls:** Use `W` (Up), `A` (Left), `S` (Down), and `D` (Right) keys to navigate.
- **Victory:** Collect all the dots scattered across the grid.
- **Defeat:** Collide with the ghost.

## 🛠️ Core Concepts Implemented
- **Grid-Based Maze Generation:** Uses multi-dimensional arrays to render boundary walls (`#`), dots (`.`), and characters.
- **Non-Blocking User Input:** Implements `_kbhit()` and `_getch()` to handle inputs seamlessly without freezing the game loop execution.
- **Randomized Ghost AI:** Implements a pseudo-random direction validation algorithm via a do-while check to stop ghosts from breaking out of walls.

## 💻 Environment
- **Language:** C++
- **Compiler:** MSVC (Visual Studio Compiler)
- **Execution:** Windows Console

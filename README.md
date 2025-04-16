# 🎯 Circle Board Game (in C)

This is a turn-based circular board game implemented in C. The player and the computer race along a 10x10 square path while avoiding hidden traps. The first to complete the full circle wins!

## 📌 Features

- 10x10 dynamic board grid
- Player vs. Computer mode
- Trap system with random penalties
- Real-time dice roll animations
- Win detection & replay option

## 🧠 Game Logic

- Players move clockwise around the board.
- Each player sets a trap for the opponent.
- Trap values (1-5) reduce movement when stepped on.
- The first to reach their starting point again wins!

## 🔧 Compile & Run

```bash
gcc -o circle circle.c
./circle

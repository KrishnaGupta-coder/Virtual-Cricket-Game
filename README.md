# 🏏 Virtual Cricket Game

A C++ terminal-based cricket simulation game where two teams compete in a short-format match. The game includes realistic match features like player selection, toss, overs, runs, wickets, and a match summary.

---

## 🎮 Features

- Select 4 players each for **Team A** and **Team B** from a pool of 11 players.
- Simulate a **toss** to decide batting or bowling.
- Each team gets **1 over** to score.
- **Automatic run generation**, with `0` run counting as **OUT**.
- Live **score updates**, **wickets**, and **match results**.
- Real-time feel with timed pauses (`usleep()` for effects).

---

## 🧠 Gameplay Flow

1. Welcome message & instructions.
2. Players select teams.
3. Toss to decide the first batting team.
4. First innings: Batting & bowling simulation.
5. Second innings: Reverse roles.
6. Scoreboard and match result.

---

## 🧱 Technologies Used

- C++ (Standard Libraries)
- Terminal-based user interface
- `usleep()` for timing (Note: May need changes for Windows)

---

## 💻 How to Run

### ✅ Requirements

- A C++ compiler (like `g++`)
- Unix-like system (Linux/macOS) or compatible terminal
  - For **Windows**, replace `#include <unistd.h>` with:
    ```cpp
    #include <windows.h>
    #define usleep(x) Sleep(x/1000)
    ```

### ▶️ Compile & Run

```bash
g++ -o cricket_game cricket.cpp
./cricket_game

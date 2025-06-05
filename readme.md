
# 🕹️ Cub3D

Cub3D is a **42 programming school project** designed as an introduction to **basic 3D rendering** using the **raycasting** technique. The project is heavily inspired by early first-person shooter games such as *Wolfenstein 3D* and aims to implement a minimalist 3D graphics engine from scratch, using only low-level tools and libraries.

This project was developed in collaboration with [Denuen](https://github.com/Denuen).

---

## 📌 Objective

- Parse a custom `.cub` map file describing walls, textures, and player starting position.  
- Render a 3D scene from a first-person perspective using **raycasting**.  
- Handle **real-time input**, **collision detection**, and **texture mapping**.  
- Implement a **basic minimap** and display **sprites** (bonus).  
- Comply with the constraints of the **MiniLibX** graphics library (no OpenGL or 3D APIs).

---

## 🧠 Technical Overview

- **Language:** C (compiled with `-Wall -Wextra -Werror`)  
- **Graphics:** MiniLibX (macOS only)  
- **Algorithm:** Digital Differential Analysis (DDA) for raycasting  
- **Textures:** XPM files for walls and sprites  
- **Controls:** Arrow keys or WASD for movement and rotation

---

## 📁 Project Structure

```

cub3d/
├── include/            # Header files
├── src/                # Source code
│   ├── init/           # Initialization routines
│   ├── parser/         # Map and configuration file parsing
│   ├── raycasting/     # Core raycasting logic
│   ├── rendering/      # Texture mapping and drawing
│   └── input/          # Key event handling
├── assets/             # Textures (XPM format)
├── maps/               # Example .cub map files
├── Makefile
└── README.md

````

---

## 🕹️ Controls

| Key        | Action                  |
|------------|-------------------------|
| `W` / `S`  | Move forward / backward |
| `A` / `D`  | Strafe left / right     |
| `←` / `→`  | Rotate view left / right|
| `ESC`      | Exit the game           |

---

## 🧾 Map File (.cub)

A valid `.cub` map file includes:

- Texture paths (`NO`, `SO`, `WE`, `EA`)  
- Floor and ceiling colors (`F`, `C`)  
- A valid map grid with walls (`1`), empty space (`0`), and a player starting point (`N`, `S`, `E`, `W`)  

The parser performs strict validation and will refuse to run if the input map is malformed (e.g., open walls, invalid characters, missing textures).

---

## ⚙️ Build & Run

> ❗️ **macOS only**, due to MiniLibX

### 🔧 Dependencies

- MiniLibX (provided or built from source)  
- macOS (Metal or X11 depending on version)  

### 🧪 Compile

```bash
make
````

### ▶️ Run

```bash
./cub3d maps/sample.cub
```

---

## 🧪 Bonus Features (optional)

* Minimap with real-time player position
* Sprite rendering with depth-sorting
* Door opening / interactive elements
* Mouse support (if implemented)

---

## 👥 Authors

* [YourGitHubUsername](https://github.com/YourGitHubUsername)
* [Denuen](https://github.com/Denuen)

---

## 📜 License

This project is released for educational purposes under the 42 school guidelines. No formal license is applied.

---

## 💡 Credits

Cub3D is part of the core curriculum of [École 42](https://42.fr/en/homepage/), designed to explore low-level graphics programming and foundational concepts in real-time rendering.


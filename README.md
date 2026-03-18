_This project has been created as part of the 42 curriculum by asadik._

# Description
Reads a map of coordinates and renders them as a 3D wireframe model.

First, the coordinates from the map are translated into world coordinates (`t_world_coord`). At each frame, these world coordinates are translated into screen coordinates (`t_screen_coord`), taking into account the camera's current translation, rotation, and zoom. The MLX library is used for input handling, window management, and rendering.

# Instruction
Compile with `make`. To compile with debug flags, use `make debug`. All other standard make rules apply.

Run the program with `./fdf 'path/to/mapfile'`. The program will close gracefully if an incorrect number of arguments is provided.

## Maps
A valid map file must comply with the following rules:
1.  **File Name**: The map file must have a `.fdf` extension.
2.  **Grid Structure**: Each row must contain the same number of points. Rows are separated by newline characters, and empty lines are not allowed.
3.  **Point Separation**: Points on the same row must be separated by one or more spaces.
4.  **Point Format**: Each point must be a valid integer representing the height. Optionally, a color can be specified after the height, separated by a comma (e.g., `10,0xFF0000`). There should be no spaces around the comma.
5.  **Color Format**: Colors must be hexadecimal numbers prefixed with `0x` in ARGB (Alpha, Red, Green, Blue) format. For example, `0xFF` is a valid short form for blue.
6.  **Minimum Points**: A map must contain at least two points.

If the map file is invalid, empty, or does not follow these rules, the program will exit gracefully.

## Controls
- **Pan Camera**: `W`, `A`, `S`, `D` keys.
- **Rotate Camera (Z-axis)**: `Q` and `E` keys.
- **Arbitrary Rotation**: Hold down the left mouse button and drag.
- **Zoom**: Mouse wheel.
- **Change Height Scale**: `+` and `-` keys on the numpad.
- **Toggle Projection**: `P` key (switches between parallel and perspective).
- **Center Camera**: `C` key.
- **Reset Rotation**: `Y` and `Z` keys.
- **Reset Zoom**: `X` key.
- **Reset Camera**: `R` key (resets position, rotation, and zoom).

# Resources
The program structure was inspired by my previous game development experience. The math, especially for quaternions, was developed through discussions with colleagues and AI. I learned Bresenham's line-drawing algorithm from this video: [Bresenham's Line Algorithm - Demystified Step by Step](https://www.youtube.com/watch?v=CceepU1vIKo).
_This project has been created as part of the 42 curriculum by asadik._

# Description
Reads a map of coordinates and renders them as a 3D wireframe model.

First, the coordinates from the map are translated into world coordinates (`t_world_coord`). At each frame, these world coordinates are translated into screen coordinates (`t_screen_coord`), taking into account the camera's current translation, rotation, and zoom. The MLX library is used for input handling, window management, and rendering.

# Instruction
Compile with `make`. To compile with debug flags, use `make debug`. All other standard make rules apply.

Run the program with `./fdf 'path/to/mapfile'`. The program will close gracefully if an incorrect number of arguments is provided.

## Maps
A valid map file must comply with the following rules:
1.  **Grid Structure**: Each row must have the same number of points. Rows are separated by newline characters.
2.  **Point Separation**: Points on the same row must be separated by spaces.
3.  **Point Format**: Each point consists of a numeric height value. Optionally, a color can be specified after the height, separated by a comma (e.g., `10,0xFF0000`).
4.  **Color Format**: Colors must be hexadecimal numbers prefixed with `0x` in ARGB (Alpha, Red, Green, Blue) format. Shorter values are padded with leading zeros; for example, `0xFF` is treated as `0x000000FF` (opaque blue).
5.  **Value Limits**: The program does not protect against integer overflow. Map dimensions and height values should stay within the `INT_MIN` and `INT_MAX` range.
6.  **Minimum Points**: A wireframe requires at least two points to draw a line. A map with fewer than two points will render nothing.

If any of these rules are not followed, the program should not crash, but the model may not render as expected. If the map file is empty, the program will close gracefully.

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
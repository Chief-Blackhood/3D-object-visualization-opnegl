## Drawing 3D objects

This assignment is to help understand 3D rendering of multiple dodecahedron.

The 3D objects rendered are:
 - elongated square dipyramid
 - hexagonal dipyramid
 - undecagonal pyramid

## How to Run

```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./Hello-World
```

> Input an one of the 3 options (1, 2, 3) to view different dodecahedron.

## Key Bindings

The keys to move the object are:
 - <kbd>A</kbd>: To move in negative x-axis
 - <kbd>D</kbd>: To move in positive x-axis
 - <kbd>W</kbd>: To move in positive y-axis
 - <kbd>S</kbd>: To move in negative y-axis
 - <kbd>F</kbd>: To move in positive z-axis
 - <kbd>G</kbd>: To move in negative z-axis 

> All axis are fixed global co-oridinates for the object

The keys to move the camera are:
 - <kbd>← </kbd>: To move in negative x-axis
 - <kbd>→</kbd>: To move in positive x-axis
 - <kbd>↑</kbd>: To move in positive y-axis
 - <kbd>↓</kbd>: To move in negative y-axis
 - <kbd>Z</kbd>: To move in positive z-axis
 - <kbd>X</kbd>: To move in negative z-axis 

> All axis are relative laptop screen co-oridinates for the camera

The keys for rotation are:
 - <kbd>R</kbd>: To rotate camera about the object
 - <kbd>O</kbd>: To move object about its x-axis

The keys for teleporation are:
 - <kbd>T</kbd>: To see the top view of the object
 - <kbd>B</kbd>: To see the bottom view of the object
 - <kbd>P</kbd>: To see the side/parallel view of the object

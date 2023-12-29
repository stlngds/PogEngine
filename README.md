A simple-ish game engine for Digipen's Fall 2023 CS529 course (Fundamentals of Game Development) taught by Mariojulio Alvarez.
Written in C++ and OpenGL using Visual Studio plus the ImGui, RapidJSON, and STB libraries, with special thanks to The Cherno for his fantastic OpenGL tutorial video series.
Main file (BestSellerEngine.cpp) implements a very simple, legally-distinct tennis game - Ping.

Major features:
- Abstracted away tons of OpenGL functionality for your OOPing convenience!
- Initialize a scene and all its objects by reading a JSON file!
- AABB/OBB collisions!

Issues to fix at a later time: 
- Collision callbacks are prohibitively basic, only taking the GameObject for whom the collision event was triggered as a parameter.
- Move Renderer functionality from the Window class to the Renderer class without triggering the ancient arcane curse apparently plaguing my bloodline.
- Clean up unused/unwanted code (i.e., old_* files, barely-used/deprecated/stub classes like Input, Color, FramerateController...)

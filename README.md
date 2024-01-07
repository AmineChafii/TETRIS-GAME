# TETRIS-GAME
![Design sans titre (2)](https://github.com/AmineChafii/TETRIS-GAME/assets/126218968/577c50a8-e1c0-4f7c-8fdd-dc777e621c87)

A tetris game in c using NCURSES and MVC methodology.

# Building :

 My dependencie is : 
   - **ncruses** for terminal manipulation.

 To install it on Arch Linux :

        sudo pacman -S sdl_mixer ncurses

To install it on Ubuntu : 

         sudo apt-get install libncurses5-dev

To compile : 

        make

To run :

        bin/release/main

# Instructions

The controls are typical of Tetris:

        - ← and →: Move the tetromino,

        - ↑: Rotate (clockwise?) the tetromino,

        - ↓: Immediately drop the tetromino (not a fast drop, an immediate drop),

        - Q: Exit the game prematurely,

        - P: Pause the game (any key to resume),

        - S: Save game and exit (just assumes filename tetris.save). To resume the game, run bin/release/main tetris.save (or whatever you may have renamed the game save to).

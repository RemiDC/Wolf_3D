# Wolf3D
A way of learning raycasting

## Install
For now, it works on **macOs Sierra**, I didn't tested with other OS yet.

Type the command in shell :
```
$> make
```
It will take some time, it needs to compile the SDL2 Library.

## Usage
### How to run the Wolf3D 

Once the program is compiled, you can show the usage with this command :
```
$> ./wolf3d
```
You can run the game with this command :
```
$> ./wolf3d map.w3d
```

### The map

To run the program, you will need a map **map.w3d**.
A map is designed like this :
```
1 1 1 1 1 1 1
1 0 0 1 0 0 1
1 0 9 0 0 0 1
1 0 0 1 1 0 1
1 0 0 1 0 5 1
1 1 1 1 1 1 1
```
#### You must need :
* '*1*' in every border of the map
* At least one '*0*', a empty case
* The map *MUST* be a rectangle
* You can add a spawnpoint with '*9*', the player will appear inside
* You can add a finish point with '*5*', something will appen if the player go inside

### Controls

Keyboard :
* **W / A / S / D** Move the player in any directions *(Up / Left / Down / Right)*
* **< / > / Pge Up / Pge Down** Move the camera in any directions *(Left / Right / Up / Down)*
* **lShift** Toggle a sprint
* **Tab** Toggle the minimap
* **P** Pause the game, and take control of the mouse
* **F** Toggle fullscreen mode
* **T** Change textures between *Real textures* / *Colors textures*

Mouse :
* You can control the camera with the mouse
* When pause is active, you can resize the game window

## Error management

Each of the following errors is handled by the program :
* Wrong running directory (*ERR_EXE*)
* Map isn't surrounded by walls (*ERR_MAP*)
* Can't create SDL window (*ERR_WIN*)
* Can't update SDL renderer (*ERR_COPY*)
* Can't open file (*ERR_OPEN*)
* Can't connect with SDL's API (*ERR_INIT*)
* No spawnable cell in the map (*ERR_FULL*)
* Can't close file (*ERR_CLOSE*)
* Map width uneven on each row (*ERR_WIDTH*)
* Can't retrieve all points (*ERR_SPLIT*)
* Incorrect map format (*ERR_FORMAT*)
* Can't hide cursor position (*ERR_CURSOR*)
* Can't update SDL texture (*ERR_UPDATE*)
* Can't allocate memory (*ERR_MALLOC*)
* Can't create SDL texture (*ERR_TEXTURE*)
* Can't create SDL renderer (*ERR_RENDERER*)
* Incorrect filename (*.w3d) (*ERR_FILENAME*)
* Empty row within the map (*ERR_EMPTY_ROW*)
* Empty file (*EMPTY_FILE*)

When one of these error occurs, the correct message is displayed on the **standard output**.

## Screenshots
![screen1](/screens/screen1.png)
![screen2](/screens/screen2.png)
![screen3](/screens/screen3.png)

## Credits
This project was made in collaboration with [@reda-con](https://github.com/RemiDC) and [@kibotrel](https://github.com/kibotrel).

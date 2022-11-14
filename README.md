# minesweeper
A simple minesweeper made in c++

# Details

This is a simple minesweeper engine make to custom use. The user can easy set the difficulty of the game and handle inputs from the user. 


# Minesweeper game example

This project shows the use of the engine with the classic minesweeper game implemetation. You can view the game code on `examples/minesweeper_game.cpp`. Here are some pictures of the current game state:

![easy setup](asserts/easy_setup.png)
![medium setup](asserts/medium_setup.png)
![hard setup](asserts/hard_setup.png)

The user can choose the game difficulty, place marks on bombs spots and click to acctually play the game:

![victory example](asserts/victory.png)

# Build and Run

This project depends on [CMake](https://cmake.org/) to build and run. The basic set to build is the following:

```console
foo@bar:~$ mkdir build && cd build
foo@bar:~$ cmake ..
foo@bar:~$ cmake --build .
```

If you want to run the tests on each module of the engine, just run the following line:

```console
foo@bar:~$ cmake --build . --target <test_name>
```

Where `test_name`, is one of type `test_<module>`. Example: You want to test the 'cell' module, so you run:

```console
foo@bar:~$ cmake --build . --target test_cell
```

## Test Status
| Test Status |        Okay        | Fail | Not Done |
|:-----------:|:------------------:|:----:|:--------:|
|     cell    | :heavy_check_mark: |      |          |
|     grid    | :heavy_check_mark: |      |          |
|     mine    | :heavy_check_mark: |      |          |

## Building with GUI

This project supports a minesweeper game using [SFML](https://github.com/SFML/SFML). To use the GUI provided first run the build and than run the following command:

```console
// on build folder
foo@bar:~$ cmake .. -DUSE_GUI=ON
```

This command tells cmake to include the SFML library and the targets to run with the GUI.

# Know Issues

When you run the example project using the GUI option, the game will not open because it's missing some dlls. To handle this problem, make sure to add the dlls from `SFML/build/bin` folder into the executable folder of the game.

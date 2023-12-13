# Rubik's cube solver
This is an implementation of a two-phase algorithm developed by Herbert Kociemba for solving a Rubik's cube, providing near-optimal solutions in real time.
The algorithm is a combination several ideas mainly based on the concepts presented in [Kociemba's page].
Detailed explanation can be found [here] (in Serbian).

## Run
The program is written in C++ using GCC for compilation.
Compilation process can be invoked using ```make```.

During the first run, the user is ecountered with a promt to generate required files (heuristic tables).
They are necessary for program to work and will be created in *resources* directory.
The process of creation can take some time and will require about 6GB both of working memory and storage.
When formed, the tables are loaded and demand about 2GB of working memory while active.

## Results
On 100 randomly generated cubes, the results are the following.

| Time                  | Shortest solution | Longest solution  | Average solution  |
| ----------            | ----              | ------            | -------           |
| 0.5s                  | 17                | 22                | 20.17             |
| 1s                    | 17                | 21                | 20.09             |
| 2s                    | 17                | 21                | 19.96             |
| 5s                    | 17                | 21                | 19.73             |

Time parameter represent the amount of time given to the program to find solution.
With more than 2s, the average solution length is less than 20 moves (which is theoretical maximum).

[Kociemba's page]: http://kociemba.org/cube.htm
[here]: https://www.mg.edu.rs/uploads/files/dokumenta/najbolji-maturski/stefan-milenkovic.pdf

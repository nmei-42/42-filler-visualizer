# 42-filler-visualizer
A visualizer for the 42 Filler project. Made using the 42 MLX graphics library!

No more staring at X's and O's on terminal!!

### Installation
To generate an executable for this project run `make` in the root of the project directory after you've downloaded or cloned it.
The make process will generate a binary called `filler_viz`.

This project will only work on MacOS El Capitan/Sierra/HighSierra and even then, no promises!

### Usage
After generating a binary you can run the program with `./filler_viz [filler_vm_output.txt]` or you can directly pipe the [`filler_vm`](https://github.com/nmei-42/42-filler-visualizer/tree/master/Filler_resources) output to the program with `filler_vm [vm_options] | ./filler_viz`.

If you want to generate more games to watch, you can use the `filler_vm` to generate more games. Its usage is as follows:

```
./Filler_resources/filler_vm, made by Hcao and Abanlin, version 1.1

Usage: ./Filler_resources/filler_vm -f path [-i | -p1 path | -p2 path] [-s | -q | -t time]

   -t  --time		set timeout in second
   -q  --quiet		quiet mode
   -i  --interactive	interactive mode(default)
   -p1 --player1	use filler binary as a first player
   -p2 --player2	use filler binary as a second player
   -f  --file		use a map file (required)
   -s  --seed		use the seed number (initialization random) (man srand)
```

### Filler viz usage examples

Reading from file:

`./Filler_resources/filler_vm -f ./Filler_resources/maps/map01 -p1 ./Filler_resources/players/carli.filler -p2 ./Filler_resources/players/superjeannot.filler > ./Filler_resources/sample_game2.txt`

To visualize you can just run `./filler_viz ./Filler_resources/sample_game2.txt`

Reading from pipe:

`./Filler_resources/filler_vm -f ./Filler_resources/maps/map01 -p1 ./Filler_resources/players/carli.filler -p2 ./Filler_resources/players/superjeannot.filler | ./filler_viz`

### Output

Player 1 (i.e. 'O' and 'o') will always be red with lighter red colors indicating earlier moves.

Player 2 (i.e. 'X' and 'x') will always be blue with lighter blue colors also indicating earlier moves.

![Example Picture](https://github.com/nmei-42/42-filler-visualizer/blob/master/screenshots/example.png)

The user can view game states with the following commands:

```
left arrow (←): move back one turn
right arrow (→): move forward one turn
down arrow (↓): move forward 9x
up arrow (↑): move backward 9x
p: Print the current player, board, and piece to console
f: Move the game state to the first turn
l: Move the game state to the last turn
esc: Quit :(
```
The command "p" can be especially useful for troubleshooting as you can copy paste the console output into a .txt and then `cat console.txt |` to your filler binary.

![Example "p" usage](https://github.com/nmei-42/42-filler-visualizer/blob/master/screenshots/print_to_console_option.png)

### Acknowledgements

Many thanks to "ashih" @ 42 USA for coming up with his own original implementation of a Filler visualizer using the MLX library first. This inspired me to make my own!

Many thanks also to [qst0](https://github.com/qst0) for maintaining multiple versions of the mlx library and for including really awesome documentation!

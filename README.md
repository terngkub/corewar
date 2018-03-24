# corewar
École 42 assignment in C - assembler and virtual machine of Corewar game (in 42's style)

### About this project
* This is a group project of [École 42](https://42.fr)
* My group consists of 4 people. My teammate are [fxbabin](https://github.com/fxbabin), [arobion](https://github.com/arobion), [nendek](https://github.com/nendek).
* The objective of this project is to create an assembler, a virtual machine and a simple champion for Corewar game.

### What is Corewar game
* It's a battle royale of champions. The objective of the game is to be the last champion that is alive in the arena.
* A champion has a set of instructions that will run when the game start. The champion file is .s type.
  ![champion](/screenshot/champion.png?raw=true)
* An assembler will comply a champion into a byte code or .cor type.
  ![bytecode](/screenshot/bytecode.png?raw=true)
* A virtual machine will run the game
  * receiving .cor files
  * placing each heroes in the memory
  * read byte codes, interpret them and run them if it's valid
  * run the game until there is a winner
![virtual machine](/screenshot/flag_v.png?raw=true)


### How to run the program
* Run Makefile to create executable files: "asm" and "corewar"
  ```
  make
  ```
* Assembler
  ```
  ./asm [champion.s]
  ```
* Virtual machine
  ```
  ./corewar [-dump N || -v] [-n N] <champion1.cor> <...>
  ```
  * without flag
    * ![output](/screenshot/output.png?raw=true)
  * flag dump - will show the memory of stated cycle
    * ![flag_dump](/screenshot/flag_dump.png?raw=true)
  * flag n - will change the player number
    * ![flag_n](/screenshot/flag_n.png?raw=true)
  * flag v - will visualize the virtual machine
    * ![flag_v](/screenshot/flag_v.png?raw=true)

### Contributions
* Me
  * assembler - instructions/labels parsing and writing
  * vitual machine - instuction executions
* [fxbabin](https://github.com/fxbabin)
  * assembler - name/comment parsing and writing
  * virtual machine - visualization
* [arobion](https://github.com/arobion)
  * virtual machine - processing
  * virtual machine - instruction executions
  * create simple champion
* [nendek](https://github.com/nendek)
  * virtual machine - processing
  * virtual machine - visualization

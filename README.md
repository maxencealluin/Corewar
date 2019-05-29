# Corewar

A reproduction of the Corewar game: Virtual Machine with GUI using Ncurses library, Assembly compiler and champion written in redcode.

## Description : 

Core War was inspired by a malicious virus written in the 80’s. To deal with the self-replicating virus, a white hat hacker invented Reaper. It was a virus designed to spread and eliminate the malware. He fought fire with fire.

This inspired A. K. Dewdney to coin the idea for Core War.

The idea was simple. You compete by designing viruses to overtake a computer. You win by protecting your own program and overwriting your opponent's programs. This is all happening on a virtual machine.

Our implementation (made with Ncurses library) looks like this: 

![Alt text](http://g.recordit.co/4Lg6eHYb88.gif "Implementation")

### Virtual Machine

The virtual machine is the program that will hosts the fight between up to 4 champions. The champions files are passed as arguments to the virtual machine which will read their code and place them on the arena. 
There are 3 main gameplay elements:
* The arena in which the place takes place : it consists of a circulary memory range of 4096 bytes.
* The champions which are passed as arguments.
* The processes (colored cubes on the graphical interface) which roam the arena and try to execute the operations they are standing on.

When the program starts the virtual machine initializes the arena by writing at specific places the code of the different champions. Each player starts with one process that is located at the beginning of their code. The processes will then play sequentially, executing operations if possible or going forward in the arena. 

There are 16 different operations which are recognizable by their opcodes (01 to 0F in hexadecimal), they have various uses such as:
* Loading values into the personnal memory (registers) of the processes
* Replicating the process
* Writing from their memory onto the arena
* Perform arithmetic operations
* Executing a live signal on a champion, which will make the process survive the next 'purge'.

After a certain number of cycles, a purge of processes that have not been able to execute a 'live' operation will be made.

The game will remain active until every process is dead. Once that happens the last champion that has been declared alive by a process will be declared the winner. 

Therefore the goal of the game is to create a champion in such a way that the processes will declare it alive repeatdly until the end of the game. The different operations provided and the technical specificities of the game allow for a broad range of strategies. 

## Installation : 

Clone the repository and run `make`
Alternatively you can run `make corewar` and `make asm` to compile binaries independently.  

### Usage:

#### Virtual Machine: 
`./corewar [-dump N -v N | -g] [[-n N] <champion1.cor>] <...>`

Ncurses (gui) interface:
* -g   : Ncurses output mode`

Text output mode:
* -dump N: Dumps memory after N cycles then exits
* -v    N: Verbosity levels, can be added together to enable several:
*	- 0 : Show only essentials
*	- 1 : Show lives
*	- 2 : Show cycles
*	- 4 : Show operations (Params are NOT litteral ...)
*	- 8 : Show deaths
*	- 16 : Show PC movements (Except for jumps)
*	- 32 : Show Cycles_to_die changes

#### Assembler: 
`./asm <sourcefile.s>`


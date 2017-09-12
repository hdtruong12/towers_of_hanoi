# towers_of_hanoi
Algorithm solving a complex example of the towers of Hanoi game.

The project solves the towers of Hanoi game with 6 pegs and any number of discs (theoretically) with the following pattern:

Start → Peg1 → Peg2 → Peg3 → Peg4 → Destination
           ↓→→→→→→→→→→→→→→→→→→→↑
           
To solve this game, the algorithm breaks the problem into 2 subproblems:
  1. Pushing every discs into the inner loop (Peg1, Peg4), and solve it with Peg4 as the temporary Destination
  2. Push every discs from the inner loop the the Destination

The program would print out the moves and analytical information into a text file

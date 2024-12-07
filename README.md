# PageRank Algorithm

This repository provides an implementation of the PageRank algorithm, a fundamental algorithm used to determine the relative importance of nodes in a graph, often applied to web pages in a hyperlink graph.

## Overview

The code includes:

- **Data Structures**: 
  - A `Graph` class that stores a collection of `Node` objects.
  - Each `Node` maintains its `pagerank`, a list of `parents`, and a list of `children`.
  
- **Core Functions**:
  - `Update_PageRank`: Updates the PageRank of a single node based on its parents.
  - `PageRank_One_Iteration`: Executes one iteration of the PageRank algorithm across all nodes, then normalizes results.
  - `Compute_PageRank`: Repeats the iterative process until values converge within a small tolerance (`epsilon`).

## Compilation and Execution

1. **Compile the Program**  
   Run the `make` command in the terminal:
   ```bash
   make
   ```
   This will generate an executable named `a.out`.
   
2. **Run the Program**  
   Once compiled, you can run the program by typing:
   ```bash
   ./a.out
   ```
   This will execute the PageRank algorithm based off input given from the user.

3. **Run Example Tests**  
   To run 10 example tests located in the `Test_Files` directory, execute:
   ```bash
   ./runTests a.out ./Test_Files/
   ```
   
   This script will run a batch of test inputs and compare the program’s outputs against expected results. It’s a quick way to verify correctness and stability of the implementation.
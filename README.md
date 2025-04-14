# Skyscraper Puzzle Solver

This is a C program that solves the **4x4 Skyscraper puzzle** using backtracking and constraint checking.

## 🧩 What is the Skyscraper Puzzle?

The Skyscraper puzzle is a logic game played on a square grid (4x4 in this case). Each cell must contain a number representing the height of a building (1–4), with the following constraints:

- No duplicate heights in any row or column (similar to Sudoku).
- From each edge of the grid, you can "see" a certain number of buildings.
- Taller buildings hide shorter ones behind them.
- The number of visible buildings from each edge is provided as a constraint.

## 🔧 How It Works

The program:
1. Parses the input constraint string.
2. Initializes an empty 4x4 grid.
3. Uses backtracking to fill the grid with valid building heights.
4. Validates the solution against the visibility constraints.
5. Prints the solution grid if valid, otherwise prints `Error`.

## 📥 Input Format

The program takes a **single argument**: a string of 16 digits (1–4) separated by spaces.

These 16 numbers represent the visibility constraints in this order:

Top (left to right): 4 values
Bottom (left to right): 4 values
Left (top to bottom): 4 values
Right (top to bottom): 4 values

### Example:

./skyscraper "4 3 2 1 1 2 2 2 3 2 2 1 1 2 2 2"
📄 Output
If a valid solution is found, the program prints the 4x4 grid to stdout.

If no valid solution exists or input is malformed, it prints Error.

Sample Output:
1 2 3 4 
2 3 4 1 
3 4 1 2 
4 1 2 3

🧠 How the Code is Structured
solve() – Recursively attempts to place valid numbers on the grid.

is_valid() – Validates the full grid against visibility constraints.

checkrow() and checkcol() – Ensure uniqueness in rows and columns.

check_view() – Counts visible skyscrapers from a side.

initialize_grid() – Fills the grid with zeros.

set_constraints() – Parses the input constraint string.

🚨 Error Handling
Input must be exactly 16 digits, each between '1' and '4', separated by a single space.

Invalid inputs or unsolvable puzzles will trigger an Error message.

🛠️ Compilation
To compile the program:

gcc -Wall -Wextra -Werror -o skyscraper skyscraper.c

To run:

./skyscraper "4 3 2 1 1 2 2 2 3 2 2 1 1 2 2 2"
📜 License
This project is open source and free to use under the MIT License.

# Mini Chess

A C++ implementation of a chess-like game engine with multiple AI player strategies competing against each other.

## Overview

Mini Chess is a game engine designed to simulate and test various artificial intelligence algorithms for game-playing. The project implements a complete chess game state system with multiple AI strategies that can compete against each other in automated matches.

## Features

- **Complete Game Engine**: Full chess-like game state management with board representation, move validation, and game state tracking
- **Multiple AI Strategies**:
  - **Random Player**: Makes random legal moves
  - **Minimax**: Classic minimax algorithm for game tree search
  - **Negamax**: Negamax algorithm variant of minimax
  - **Alpha-Beta Pruning**: Optimized minimax with alpha-beta pruning
  - **Submission Strategy**: Custom submission implementation with alpha-beta pruning and negamax

- **Game Simulation**: Framework to run matches between different AI players with logging and move validation
- **Flexible Architecture**: Extensible design allowing new AI strategies to be easily added

## Project Structure

```
Mini_Chess/
├── src/
│   ├── main.cpp                 # Game engine and match orchestration
│   ├── config.hpp              # Configuration constants
│   ├── state/                  # Game state management
│   │   └── state.hpp/cpp       # Board representation and legal move generation
│   ├── policy/                 # AI strategy implementations
│   │   ├── minimax.hpp
│   │   ├── negamax.hpp
│   │   ├── alphabeta.hpp
│   │   ├── MCTS.hpp
│   │   ├── random.hpp
│   │   └── submission.hpp
│   └── player/                 # Player executable implementations
│       ├── minimax.cpp
│       ├── negamax.cpp
│       ├── alphabeta.cpp
│       ├── MCTS.cpp
│       ├── random.cpp
│       └── submission.cpp
├── unittest/
│   └── state_test.cpp          # Unit tests for game state
└── Makefile                     # Build configuration
```

## Building the Project

The project uses a Makefile for compilation:

```bash
make
```

This will compile the game engine and all AI player implementations.

## Usage

### Running a Match

To run a match between two AI players:

```bash
./game <player1_executable> <player2_executable>
```

**Arguments:**
- `player1_executable`: Path to the executable for the white player
- `player2_executable`: Path to the executable for the black player

The game will output:
- Step-by-step game progression to the console and `gamelog.txt`
- Board state at each turn
- Moves made by each player
- Final game result

### Example

```bash
./game ./player_random ./player_alphabeta
```

This would run a match between a random player and an alpha-beta pruning player.

## How Players Interact

1. **Game Engine** writes current board state to a file
2. **Player Process** reads the board state and computes the best move
3. **Player Process** writes the chosen move to output file
4. **Game Engine** reads the move, validates it, and updates game state
5. **Process repeats** until game ends

Each player executable receives board state encoded in a specific format and must output moves as coordinates: `from_x from_y to_x to_y`

## AI Strategies

### Random
- Selects uniformly at random from all legal moves
- Baseline strategy for testing

### Minimax
- Searches game tree to specified depth
- Evaluates positions using a static evaluation function
- Explores all branches

### Negamax
- Variant of minimax using a single evaluation function
- Symmetric evaluation from both player perspectives

### Alpha-Beta Pruning
- Optimized minimax with branch pruning
- Eliminates unnecessary subtrees during search
- Significantly faster than standard minimax

### Monte Carlo Tree Search (MCTS)
- Statistical tree search algorithm
- Uses random simulations to evaluate positions
- Scales with computation time (configurable simulation counts)

### Submission Strategy
- Hybrid approach combining alpha-beta pruning with negamax
- Custom implementation for competitive performance

## Building and Testing

### Compile the project:
```bash
make
```

### Run unit tests:
```bash
make test
```

### Run a sample game:
```bash
./game ./player_random ./player_alphabeta
```

## Configuration

Game parameters can be configured in `src/config.hpp`:
- Board dimensions
- Random seed for reproducibility
- Evaluation function weights

## Requirements

- C++17 or later
- GCC/Clang compiler
- Standard Unix/Linux environment

## Output Files

- `gamelog.txt`: Detailed log of the entire game including all moves and board states
- Command-line output showing game progression

## Author

Created by JieHongChen

---

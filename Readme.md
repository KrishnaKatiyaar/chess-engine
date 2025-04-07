# Chess Engine ♟️

A sophisticated C++ chess engine featuring an intelligent AI opponent and comprehensive chess rules implementation.

## Features

- 🎮 Interactive Unicode chess board display
- 🧠 Advanced AI using Minimax algorithm with alpha-beta pruning
- ⚡ Efficient move generation for all pieces
- 📊 Sophisticated position evaluation system including:
  - Material balance
  - Pawn structure analysis
  - Piece positioning
  - Center control evaluation
- ♟️ Complete chess rules implementation:
  - Legal move validation
  - Check and checkmate detection
  - Stalemate detection
- 📜 Move history tracking with algebraic notation
- ↩️ Move undo functionality

## Requirements

- Windows operating system
- C++ compiler supporting C++11 or later
- Visual Studio 2019 or later (for building from source)

## Quick Start

### Using Pre-compiled Binary

1. Download the latest release
2. Run `ChessEngine.exe`

### Building from Source

```bash
git clone https://github.com/KrishnaKatiyaar/chess-engine
cd chess-engine
mkdir build && cd build
cmake ..
cmake --build . --config Release

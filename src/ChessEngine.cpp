#include "ChessEngine.h"
#include <cmath>

ChessEngine::ChessEngine() {
    Piece initialBoard[64] = {
        Piece::Rook, Piece::Knight, Piece::Bishop, Piece::Queen,
        Piece::King, Piece::Bishop, Piece::Knight, Piece::Rook,
        Piece::Pawn, Piece::Pawn,   Piece::Pawn,   Piece::Pawn,
        Piece::Pawn, Piece::Pawn,   Piece::Pawn,   Piece::Pawn,
        Piece::Empty, // ... (fill rest of board)
    };
    std::copy(initialBoard, initialBoard+64, board);
    turn = Color::White;
}

void ChessEngine::PrintBoard() {
    SetConsoleOutputCP(CP_UTF8);
    const wchar_t pieces[] = L"♜♞♝♛♚♝♞♜♟♙♖♘♗♕♔";
    wprintf(L"\n  a b c d e f g h\n");
    for(int y = 0; y < 8; y++) {
        wprintf(L"%d ", 8-y);
        for(int x = 0; x < 8; x++) {
            int pos = y*8+x;
            wprintf(L"%lc ", pieces[static_cast<int>(board[pos])]);
        }
        wprintf(L"%d\n", 8-y);
    }
    wprintf(L"  a b c d e f g h\n");
}

Move ChessEngine::GetBestMove(int depth) {
    auto moves = GenerateMoves();
    Move bestMove(-1, -1);
    int bestValue = (turn == Color::White) ? INT_MIN : INT_MAX;
    
    for(auto& move : moves) {
        // Make/undo move and evaluate
        Piece captured = board[move.to];
        board[move.to] = board[move.from];
        board[move.from] = Piece::Empty;
        
        int currentEval = Minimax(depth-1, INT_MIN, INT_MAX, turn == Color::Black);
        
        board[move.from] = board[move.to];
        board[move.to] = captured;
        
        if((turn == Color::White && currentEval > bestValue) ||
           (turn == Color::Black && currentEval < bestValue)) {
            bestValue = currentEval;
            bestMove = move;
        }
    }
    return bestMove;
}

// ... (Implement remaining methods)
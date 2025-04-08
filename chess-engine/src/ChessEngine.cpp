#include "ChessEngine.h"
#include <cmath>

ChessEngine::ChessEngine() {
    Piece initialBoard[64] = {
        Piece::Rook, Piece::Knight, Piece::Bishop, Piece::Queen,
        Piece::King, Piece::Bishop, Piece::Knight, Piece::Rook,
        Piece::Pawn, Piece::Pawn,   Piece::Pawn,   Piece::Pawn,
        Piece::Pawn, Piece::Pawn,   Piece::Pawn,   Piece::Pawn,
        Piece::Empty, 
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

void ChessEngine::GenerateBishopMoves(int pos, std::vector<Move>& moves) {
    const int directions[] = {7, 9, -7, -9}; // Diagonal directions
    for(int dir : directions) {
        for(int n = 1; n < 8; n++) {
            int target = pos + n*dir;
            if(target < 0 || target >= 64) break;
            if(abs((target%8)-(pos%8)) > 2) break;
            
            if(board[target] == Piece::Empty) {
                moves.emplace_back(pos, target);
            } else {
                if(GetPieceColor(target) != turn) {
                    moves.emplace_back(pos, target);
                }
                break;
            }
        }
    }
}

void ChessEngine::GenerateRookMoves(int pos, std::vector<Move>& moves) {
    const int directions[] = {1, -1, 8, -8}; 
    for(int dir : directions) {
        for(int n = 1; n < 8; n++) {
            int target = pos + n*dir;
            if(target < 0 || target >= 64) break;
            if(dir == 1 || dir == -1) {
                if(target/8 != pos/8) break;
            }
            
            if(board[target] == Piece::Empty) {
                moves.emplace_back(pos, target);
            } else {
                if(GetPieceColor(target) != turn) {
                    moves.emplace_back(pos, target);
                }
                break;
            }
        }
    }
}

void ChessEngine::GenerateQueenMoves(int pos, std::vector<Move>& moves) {

    GenerateRookMoves(pos, moves);
    GenerateBishopMoves(pos, moves);
}

void ChessEngine::GenerateKingMoves(int pos, std::vector<Move>& moves) {
    const int directions[] = {1, -1, 8, -8, 7, 9, -7, -9};
    for(int dir : directions) {
        int target = pos + dir;
        if(target >= 0 && target < 64 && abs((target%8)-(pos%8)) <= 1) {
            if(board[target] == Piece::Empty || GetPieceColor(target) != turn) {
                moves.emplace_back(pos, target);
            }
        }
    }
}

void ChessEngine::GeneratePawnMoves(int pos, std::vector<Move>& moves) {
   
    if(!moveHistory.empty()) {
        Move lastMove = moveHistory.back();
        if(board[lastMove.to] == Piece::Pawn && abs(lastMove.from - lastMove.to) == 16) {
            int x = pos % 8;
            int y = pos / 8;
            if(abs(lastMove.to%8 - x) == 1 && lastMove.to/8 == y) {
                int capturePos = lastMove.to + ((turn == Color::White) ? -8 : 8);
                moves.emplace_back(pos, capturePos);
            }
        }
    }
}


void ChessEngine::GenerateKingMoves(int pos, std::vector<Move>& moves) {
  
    if(!HasKingMoved(turn)) {
       
        if(CanCastleKingside(turn)) {
            moves.emplace_back(pos, pos+2);
        }
      
        if(CanCastleQueenside(turn)) {
            moves.emplace_back(pos, pos-2);
        }
    }
}

bool ChessEngine::IsMoveLegal(const Move& move) {
   
    if(move.from < 0 || move.from >= 64 || move.to < 0 || move.to >= 64) 
        return false;
    
   
    Piece captured = board[move.to];
    board[move.to] = board[move.from];
    board[move.from] = Piece::Empty;
    
    bool inCheck = IsInCheck(turn);
    
    
    board[move.from] = board[move.to];
    board[move.to] = captured;
    
    return !inCheck;
}

bool ChessEngine::IsInCheck(Color color) {
    int kingPos = -1;
    for(int i = 0; i < 64; i++) {
        if(board[i] == Piece::King && GetPieceColor(i) == color) {
            kingPos = i;
            break;
        }
    }
    
    Color opponent = (color == Color::White) ? Color::Black : Color::White;
    Color originalTurn = turn;
    turn = opponent; 
    
    auto opponentMoves = GenerateMoves();
    turn = originalTurn;
    
    for(const auto& move : opponentMoves) {
        if(move.to == kingPos) return true;
    }
    return false;
}

bool ChessEngine::HasKingMoved(Color color) {
    
    int kingPos = (color == Color::White) ? 4 : 60;
    return board[kingPos] != Piece::King;
}

bool ChessEngine::CanCastleKingside(Color color) {
    int rookPos = (color == Color::White) ? 7 : 63;
    return board[rookPos] == Piece::Rook &&
           board[rookPos-1] == Piece::Empty &&
           board[rookPos-2] == Piece::Empty;
}

bool ChessEngine::CanCastleQueenside(Color color) {
    int rookPos = (color == Color::White) ? 0 : 56;
    return board[rookPos] == Piece::Rook &&
           board[rookPos+1] == Piece::Empty &&
           board[rookPos+2] == Piece::Empty &&
           board[rookPos+3] == Piece::Empty;
}

int ChessEngine::Evaluate() {
    int score = 0;
    const int pieceValues[] = {0, 100, 320, 330, 500, 900, 20000};
    
   
    for(int i = 0; i < 64; i++) {
        if(board[i] != Piece::Empty) {
            int value = pieceValues[static_cast<int>(board[i])];
            
            value += GetPositionalScore(i, board[i]);
            score += (GetPieceColor(i) == Color::White) ? value : -value;
        }
    }
    

    int mobility = GenerateMoves().size();
    score += (turn == Color::White) ? mobility : -mobility;
    
    return score;
}

int ChessEngine::GetPositionalScore(int pos, Piece piece) {
   
    static const int pawnTable[64] = {
        0,  0,  0,  0,  0,  0,  0,  0,
        50, 50, 50, 50, 50, 50, 50, 50,
        10, 10, 20, 30, 30, 20, 10, 10,
        5,  5, 10, 25, 25, 10,  5,  5,
        0,  0,  0, 20, 20,  0,  0,  0,
        5, -5,-10,  0,  0,-10, -5,  5,
        5, 10, 10,-20,-20, 10, 10,  5,
        0,  0,  0,  0,  0,  0,  0,  0
    };
    
 
    if(GetPieceColor(pos) == Color::Black) {
        pos = 63 - pos;
    }
    
    switch(piece) {
        case Piece::Pawn: return pawnTable[pos];
       
        default: return 0;
    }
}

void ChessEngine::MakeMove(const Move& move) {
    
    if(board[move.from] == Piece::King && abs(move.from - move.to) == 2) {
        
        int rookFrom = (move.to > move.from) ? move.from+3 : move.from-4;
        int rookTo = (move.to > move.from) ? move.from+1 : move.from-1;
        board[rookTo] = board[rookFrom];
        board[rookFrom] = Piece::Empty;
    }
    
    moveHistory.push_back(move);
    board[move.to] = board[move.from];
    board[move.from] = Piece::Empty;
    turn = (turn == Color::White) ? Color::Black : Color::White;
}

void ChessEngine::UndoMove(const Move& move) {
    board[move.from] = board[move.to];
    board[move.to] = Piece::Empty;
    turn = (turn == Color::White) ? Color::Black : Color::White;
    moveHistory.pop_back();
    
   
}


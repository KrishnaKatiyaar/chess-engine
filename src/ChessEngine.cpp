#include "ChessEngine.h"
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <climits>

using namespace std;

// Constructor
ChessEngine::ChessEngine() {
    // Initialize empty board first
    for(int i = 0; i < 64; i++) {
        board[i] = Piece::Empty;
    }

    // Set up white pieces
    board[0] = board[7] = Piece::Rook;
    board[1] = board[6] = Piece::Knight;
    board[2] = board[5] = Piece::Bishop;
    board[3] = Piece::Queen;
    board[4] = Piece::King;
    for(int i = 8; i < 16; i++) {
        board[i] = Piece::Pawn;
    }

    // Set up black pieces
    board[56] = board[63] = Piece::Rook;
    board[57] = board[62] = Piece::Knight;
    board[58] = board[61] = Piece::Bishop;
    board[59] = Piece::Queen;
    board[60] = Piece::King;
    for(int i = 48; i < 56; i++) {
        board[i] = Piece::Pawn;
    }

    turn = Color::White;
    capturedPieces.clear();  // Fixed syntax
}

void ChessEngine::PrintBoard() {
    SetConsoleOutputCP(CP_UTF8);
    const wchar_t pieces[] = L"♜♞♝♛♚♝♞♜♟♙♖♘♗♕♔·";
    wprintf(L"\n  a b c d e f g h\n");
    for(int y = 0; y < 8; y++) {
        wprintf(L"%d ", 8 - y);
        for(int x = 0; x < 8; x++) {
            int pos = y * 8 + x;
            int piece = static_cast<int>(board[pos]);
            int offset = (GetPieceColor(pos) == Color::White) ? 7 : 0;
            wprintf(L"%lc ", pieces[piece + offset]);
        }
        wprintf(L"%d\n", 8 - y);
    }
    wprintf(L"  a b c d e f g h\n");
}

Move ChessEngine::GetBestMove(int depth) {
    vector<Move> moves = GenerateMoves();
    Move bestMove(-1, -1);
    int bestValue = (turn == Color::White) ? INT_MIN : INT_MAX;

    for(Move& move : moves) {
        MakeMove(move);
        int currentEval = Minimax(depth - 1, INT_MIN, INT_MAX, turn == Color::Black);
        UndoMove(move);

        if((turn == Color::White && currentEval > bestValue) ||
           (turn == Color::Black && currentEval < bestValue)) {
            bestValue = currentEval;
            bestMove = move;
        }
    }
    return bestMove;
}

<<<<<<< HEAD
void ChessEngine::GenerateBishopMoves(int pos, std::vector<Move>& moves) {
    const int directions[] = {7, 9, -7, -9}; // Diagonal directions
    for(int dir : directions) {
        for(int n = 1; n < 8; n++) {
            int target = pos + n*dir;
            if(target < 0 || target >= 64) break;
            if(abs((target%8)-(pos%8)) > 2) break; // Prevent wrapping
            
            if(board[target] == Piece::Empty) {
                moves.emplace_back(pos, target);
            } else {
                if(GetPieceColor(target) != turn) {
                    moves.emplace_back(pos, target);
                }
                break;
=======
vector<Move> ChessEngine::GenerateMoves() {
    vector<Move> moves;
    for(int i = 0; i < 64; i++) {
        if(board[i] != Piece::Empty && GetPieceColor(i) == turn) {
            GeneratePieceMoves(i, moves);
        }
    }
    return moves;
}

void ChessEngine::GeneratePieceMoves(int pos, vector<Move>& moves) {
    switch(board[pos]) {
        case Piece::Pawn: GeneratePawnMoves(pos, moves); break;
        case Piece::Knight: GenerateKnightMoves(pos, moves); break;
        case Piece::Bishop: GenerateBishopMoves(pos, moves); break;
        case Piece::Rook: GenerateRookMoves(pos, moves); break;
        case Piece::Queen: GenerateQueenMoves(pos, moves); break;
        case Piece::King: GenerateKingMoves(pos, moves); break;
        default: break;
    }
}

// Piece-specific move generators
void ChessEngine::GeneratePawnMoves(int pos, vector<Move>& moves) {
    int x = pos % 8;
    int y = pos / 8;
    int direction = (turn == Color::White) ? 1 : -1;
    int startRow = (turn == Color::White) ? 1 : 6;

    // Forward moves
    if(IsValidSquare(pos + 8 * direction) && board[pos + 8 * direction] == Piece::Empty) {
        AddMoveIfValid(pos, pos + 8 * direction, moves);
        if(y == startRow && board[pos + 16 * direction] == Piece::Empty) {
            AddMoveIfValid(pos, pos + 16 * direction, moves);
        }
    }

    // Captures
    for(int dx : {-1, 1}) {
        int target = pos + 8 * direction + dx;
        if(target >= 0 && target < 64 && abs((target % 8) - x) == 1) {
            if(board[target] != Piece::Empty && GetPieceColor(target) != turn) {
                AddMoveIfValid(pos, target, moves);
>>>>>>> 38862bc (Fixed accidental embedded repo)
            }
        }
    }
}

<<<<<<< HEAD
void ChessEngine::GenerateRookMoves(int pos, std::vector<Move>& moves) {
    const int directions[] = {1, -1, 8, -8}; // Straight directions
    for(int dir : directions) {
        for(int n = 1; n < 8; n++) {
            int target = pos + n*dir;
            if(target < 0 || target >= 64) break;
            if(dir == 1 || dir == -1) {
                if(target/8 != pos/8) break; // Same row check
            }
            
            if(board[target] == Piece::Empty) {
                moves.emplace_back(pos, target);
            } else {
                if(GetPieceColor(target) != turn) {
                    moves.emplace_back(pos, target);
                }
                break;
            }
=======
void ChessEngine::GenerateKnightMoves(int pos, vector<Move>& moves) {
    const int offsets[] = {15, 17, -17, -15, 10, -6, 6, -10};
    int x = pos % 8;
    int y = pos / 8;

    for(int offset : offsets) {
        int target = pos + offset;
        if(target < 0 || target >= 64) continue;
        
        int tx = target % 8;
        int ty = target / 8;
        if(abs(tx - x) + abs(ty - y) == 3) {
            AddMoveIfValid(pos, target, moves);
>>>>>>> 38862bc (Fixed accidental embedded repo)
        }
    }
}

<<<<<<< HEAD
void ChessEngine::GenerateQueenMoves(int pos, std::vector<Move>& moves) {
    // Queen = Rook + Bishop
=======
void ChessEngine::GenerateBishopMoves(int pos, vector<Move>& moves) {
    const int directions[] = {7, 9, -7, -9};
    SlideMoves(pos, directions, 4, moves);
}

void ChessEngine::GenerateRookMoves(int pos, vector<Move>& moves) {
    const int directions[] = {1, -1, 8, -8};
    SlideMoves(pos, directions, 4, moves);
}

void ChessEngine::GenerateQueenMoves(int pos, vector<Move>& moves) {
>>>>>>> 38862bc (Fixed accidental embedded repo)
    GenerateRookMoves(pos, moves);
    GenerateBishopMoves(pos, moves);
}

<<<<<<< HEAD
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
// Add to GeneratePawnMoves()
void ChessEngine::GeneratePawnMoves(int pos, std::vector<Move>& moves) {
    // ... existing pawn moves ...
    
    // En passant
    if(!moveHistory.empty()) {
        Move lastMove = moveHistory.back();
        if(board[lastMove.to] == Piece::Pawn && abs(lastMove.from - lastMove.to) == 16) {
            int x = pos % 8;
            int y = pos / 8;
            if(abs(lastMove.to%8 - x) == 1 && lastMove.to/8 == y) {
                int capturePos = lastMove.to + ((turn == Color::White) ? -8 : 8);
                moves.emplace_back(pos, capturePos);
=======
void ChessEngine::GenerateKingMoves(int pos, vector<Move>& moves) {
    const int directions[] = {1, -1, 8, -8, 7, 9, -7, -9};
    for(int dir : directions) {
        int target = pos + dir;
        if(target >= 0 && target < 64 && abs((target % 8) - (pos % 8)) <= 1) {
            AddMoveIfValid(pos, target, moves);
        }
    }
}

// Helper methods
void ChessEngine::SlideMoves(int pos, const int directions[], int count, vector<Move>& moves) {
    int x = pos % 8;
    int y = pos / 8;

    for(int i = 0; i < count; i++) {
        int dx = directions[i] % 8;
        int currentX = x;
        
        for(int n = 1; n < 8; n++) {
            int target = pos + n * directions[i];
            if(target < 0 || target >= 64) break;
            
            currentX += dx;
            if(currentX < 0 || currentX >= 8) break;  // Prevent wrapping

            if(board[target] == Piece::Empty) {
                AddMoveIfValid(pos, target, moves);
            } else {
                if(GetPieceColor(target) != turn) {
                    AddMoveIfValid(pos, target, moves);
                }
                break;
>>>>>>> 38862bc (Fixed accidental embedded repo)
            }
        }
    }
}

<<<<<<< HEAD
// Add to GenerateKingMoves()
void ChessEngine::GenerateKingMoves(int pos, std::vector<Move>& moves) {
    // ... existing king moves ...
    
    // Castling
    if(!HasKingMoved(turn)) {
        // Kingside castling
        if(CanCastleKingside(turn)) {
            moves.emplace_back(pos, pos+2);
        }
        // Queenside castling
        if(CanCastleQueenside(turn)) {
            moves.emplace_back(pos, pos-2);
        }
    }
}

bool ChessEngine::IsMoveLegal(const Move& move) {
    // Check basic validity
    if(move.from < 0 || move.from >= 64 || move.to < 0 || move.to >= 64) 
        return false;
    
    // Temporarily make the move
    Piece captured = board[move.to];
    board[move.to] = board[move.from];
    board[move.from] = Piece::Empty;
    
    bool inCheck = IsInCheck(turn);
    
    // Undo the move
    board[move.from] = board[move.to];
    board[move.to] = captured;
    
    return !inCheck;
}

bool ChessEngine::IsInCheck(Color color) {
    int kingPos = -1;
    for(int i = 0; i < 64; i++) {
        if(board[i] == Piece::King && GetPieceColor(i) == color) {
=======
int ChessEngine::Minimax(int depth, int alpha, int beta, bool maximizing) {
    if(depth == 0) return Evaluate();

    vector<Move> moves = GenerateMoves();
    if(moves.empty()) return IsInCheck(turn) ? (maximizing ? -10000 : 10000) : 0;

    if(maximizing) {
        int maxEval = INT_MIN;
        for(Move& move : moves) {
            MakeMove(move);
            int eval = Minimax(depth - 1, alpha, beta, false);
            UndoMove(move);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if(beta <= alpha) break;
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for(Move& move : moves) {
            MakeMove(move);
            int eval = Minimax(depth - 1, alpha, beta, true);
            UndoMove(move);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if(beta <= alpha) break;
        }
        return minEval;
    }
}

// Add piece position evaluation tables
const int PAWN_TABLE[64] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
};

Color ChessEngine::GetPieceColor(int pos) const {
    if(board[pos] == Piece::Empty) return Color::None;
    
    int rank = pos / 8;
    if(rank < 2) return Color::White;
    if(rank > 5) return Color::Black;
    
    // For pieces in middle ranks, check move history
    for(const Move& move : moveHistory) {
        if(move.to == pos) {
            return (moveHistory.size() % 2 == 0) ? Color::Black : Color::White;
        }
    }
    
    // If no move history found, determine by initial position
    return (rank < 4) ? Color::White : Color::Black;
}

// Add move validation
bool ChessEngine::IsValidMove(const Move& move) const {
    if(move.from < 0 || move.from >= 64 || move.to < 0 || move.to >= 64)
        return false;
    
    if(GetPieceColor(move.from) != turn)
        return false;
    
    if(GetPieceColor(move.to) == turn)
        return false;
    
    // Check if the move is in the list of valid moves
    vector<Move> validMoves;
    ChessEngine* nonConstThis = const_cast<ChessEngine*>(this);
    nonConstThis->GeneratePieceMoves(move.from, validMoves);
    
    return std::find(validMoves.begin(), validMoves.end(), move) != validMoves.end();
}

// Improve evaluation function
int ChessEngine::Evaluate() {
    int score = 0;
    const int pieceValues[] = {0, 100, 320, 330, 500, 900, 20000};

    for(int i = 0; i < 64; i++) {
        if(board[i] != Piece::Empty) {
            int value = pieceValues[static_cast<int>(board[i])];
            
            // Add position-based scoring
            if(board[i] == Piece::Pawn) {
                value += PAWN_TABLE[i];
            }
            
            // Bonus for controlling center squares
            if((i == 27 || i == 28 || i == 35 || i == 36) && 
               (board[i] == Piece::Knight || board[i] == Piece::Bishop)) {
                value += 20;
            }
            
            score += (GetPieceColor(i) == Color::White) ? value : -value;
        }
    }
    
    // Penalize isolated pawns
    for(int file = 0; file < 8; file++) {
        bool whitePawnOnFile = false;
        bool blackPawnOnFile = false;
        
        for(int rank = 0; rank < 8; rank++) {
            int pos = rank * 8 + file;
            if(board[pos] == Piece::Pawn) {
                if(GetPieceColor(pos) == Color::White)
                    whitePawnOnFile = true;
                else
                    blackPawnOnFile = true;
            }
        }
        
        if(whitePawnOnFile) {
            bool isolated = true;
            if(file > 0) {
                for(int rank = 0; rank < 8; rank++) {
                    if(board[rank * 8 + file - 1] == Piece::Pawn && 
                       GetPieceColor(rank * 8 + file - 1) == Color::White) {
                        isolated = false;
                        break;
                    }
                }
            }
            if(file < 7 && isolated) {
                for(int rank = 0; rank < 8; rank++) {
                    if(board[rank * 8 + file + 1] == Piece::Pawn && 
                       GetPieceColor(rank * 8 + file + 1) == Color::White) {
                        isolated = false;
                        break;
                    }
                }
            }
            if(isolated) score -= 20;
        }
    }
    
    return score;
}

bool ChessEngine::TryMakeMove(const Move& move) {
    if (!IsValidMove(move)) return false;
    
    capturedPieces.push_back(board[move.to]);
    moveHistory.push_back(move);
    board[move.to] = board[move.from];
    board[move.from] = Piece::Empty;
    turn = (turn == Color::White) ? Color::Black : Color::White;
    return true;
}

void ChessEngine::UndoMove(const Move& move) {
    board[move.from] = board[move.to];
    board[move.to] = capturedPieces.back();
    capturedPieces.pop_back();
    turn = (turn == Color::White) ? Color::Black : Color::White;
    if (!moveHistory.empty() && moveHistory.back() == move) {
        moveHistory.pop_back();
    }
}

// Add after the constructor
bool ChessEngine::IsValidSquare(int pos) const {
    return pos >= 0 && pos < 64;
}

int ChessEngine::GetMaterialBalance() const {
    int balance = 0;
    const int pieceValues[] = {0, 100, 320, 330, 500, 900, 20000};
    
    for(int i = 0; i < 64; i++) {
        if(board[i] != Piece::Empty) {
            int value = pieceValues[static_cast<int>(board[i])];
            balance += (GetPieceColor(i) == Color::White) ? value : -value;
        }
    }
    return balance;
}

bool ChessEngine::IsCheckmate() const {
    if (!IsInCheck(turn)) return false;
    
    // Try all possible moves to see if any can get out of check
    ChessEngine* nonConstThis = const_cast<ChessEngine*>(this);
    vector<Move> moves = nonConstThis->GenerateMoves();
    
    for (const Move& move : moves) {
        if (nonConstThis->IsValidMove(move)) return false;
    }
    return true;
}

bool ChessEngine::IsStalemate() const {
    if (IsInCheck(turn)) return false;
    
    // Check if there are any legal moves
    ChessEngine* nonConstThis = const_cast<ChessEngine*>(this);
    vector<Move> moves = nonConstThis->GenerateMoves();
    
    for (const Move& move : moves) {
        if (nonConstThis->IsValidMove(move)) return false;
    }
    return true;
}

void ChessEngine::PrintMoveHistory() const {
    for (size_t i = 0; i < moveHistory.size(); ++i) {
        if (i % 2 == 0) {
            cout << (i/2 + 1) << ". ";
        }
        const Move& move = moveHistory[i];
        char fromFile = 'a' + (move.from % 8);
        char fromRank = '8' - (move.from / 8);
        char toFile = 'a' + (move.to % 8);
        char toRank = '8' - (move.to / 8);
        cout << fromFile << fromRank << toFile << toRank << " ";
        if (i % 2 == 1) cout << "\n";
    }
    if (moveHistory.size() % 2 == 1) cout << "\n";
}

bool ChessEngine::UndoLastMove() {
    if (moveHistory.empty()) return false;
    
    Move lastMove = moveHistory.back();
    board[lastMove.from] = board[lastMove.to];
    board[lastMove.to] = capturedPieces.back();
    capturedPieces.pop_back();
    turn = (turn == Color::White) ? Color::Black : Color::White;
    moveHistory.pop_back();
    return true;
}

bool ChessEngine::IsInCheck(Color color) const {
    // Find king position
    int kingPos = -1;
    for (int i = 0; i < 64; i++) {
        if (board[i] == Piece::King && GetPieceColor(i) == color) {
>>>>>>> 38862bc (Fixed accidental embedded repo)
            kingPos = i;
            break;
        }
    }
    
<<<<<<< HEAD
    Color opponent = (color == Color::White) ? Color::Black : Color::White;
    Color originalTurn = turn;
    turn = opponent; // Temporarily switch turns
    
    auto opponentMoves = GenerateMoves();
    turn = originalTurn;
    
    for(const auto& move : opponentMoves) {
        if(move.to == kingPos) return true;
    }
    return false;
}

bool ChessEngine::HasKingMoved(Color color) {
    // Check if king has moved from initial position
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
    
    // Material evaluation
    for(int i = 0; i < 64; i++) {
        if(board[i] != Piece::Empty) {
            int value = pieceValues[static_cast<int>(board[i])];
            // Add positional bonuses
            value += GetPositionalScore(i, board[i]);
            score += (GetPieceColor(i) == Color::White) ? value : -value;
        }
    }
    
    // Mobility bonus
    int mobility = GenerateMoves().size();
    score += (turn == Color::White) ? mobility : -mobility;
    
    return score;
}

int ChessEngine::GetPositionalScore(int pos, Piece piece) {
    // Positional tables for each piece type
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
    
    // Mirror table for black pieces
    if(GetPieceColor(pos) == Color::Black) {
        pos = 63 - pos;
    }
    
    switch(piece) {
        case Piece::Pawn: return pawnTable[pos];
        // Add tables for other pieces
        default: return 0;
    }
}

void ChessEngine::MakeMove(const Move& move) {
    // Handle special moves
    if(board[move.from] == Piece::King && abs(move.from - move.to) == 2) {
        // Castling - move rook too
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
    
    // TODO: Handle undoing special moves
}

=======
    if (kingPos == -1) return false;
    
    // Check if any opponent piece can capture the king
    Color opponent = (color == Color::White) ? Color::Black : Color::White;
    ChessEngine* nonConstThis = const_cast<ChessEngine*>(this);
    Color originalTurn = turn;
    nonConstThis->turn = opponent;
    
    vector<Move> opponentMoves = nonConstThis->GenerateMoves();
    nonConstThis->turn = originalTurn;
    
    for (const Move& move : opponentMoves) {
        if (move.to == kingPos) return true;
    }
    
    return false;
}

void ChessEngine::AddMoveIfValid(int from, int to, vector<Move>& moves) {
    if (to < 0 || to >= 64) return;
    if (GetPieceColor(to) == turn) return;
    
    Move move(from, to);
    // Store current state
    Piece capturedPiece = board[to];
    Color originalTurn = turn;
    
    // Try the move
    board[to] = board[from];
    board[from] = Piece::Empty;
    
    if (!IsInCheck(originalTurn)) {
        moves.push_back(move);
    }
    
    // Restore board state
    board[from] = board[to];
    board[to] = capturedPiece;
}

// Add this private version of MakeMove for internal use
// Add a member variable to store captured pieces
private:
    vector<Piece> capturedPieces;

void ChessEngine::MakeMove(const Move& move) {
    capturedPieces.push_back(board[move.to]);
    board[move.to] = board[move.from];
    board[move.from] = Piece::Empty;
    turn = (turn == Color::White) ? Color::Black : Color::White;
}
>>>>>>> 38862bc (Fixed accidental embedded repo)

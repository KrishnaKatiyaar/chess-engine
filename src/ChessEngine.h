<<<<<<< HEAD
#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>

enum class Piece { Empty, Pawn, Knight, Bishop, Rook, Queen, King };
enum class Color { White, Black, None };

struct Move {
    int from;
    int to;
    int score;
    Move(int f, int t) : from(f), to(t), score(0) {}
};

class ChessEngine {
public:
    ChessEngine();
    void PrintBoard();
    void MakeMove(int from, int to);
    Move GetBestMove(int depth);
    
private:
    Piece board[64];
    Color turn;
    std::vector<Move> moveHistory;
    
    std::vector<Move> GenerateMoves();
    int Evaluate();
    int Minimax(int depth, int alpha, int beta, bool maximizing);
    void GeneratePawnMoves(int pos, std::vector<Move>& moves);
    void GenerateKnightMoves(int pos, std::vector<Move>& moves);
    void GenerateBishopMoves(int pos, std::vector<Move>& moves);
    void GenerateRookMoves(int pos, std::vector<Move>& moves);
    void GenerateQueenMoves(int pos, std::vector<Move>& moves);
    void GenerateKingMoves(int pos, std::vector<Move>& moves);
};
=======
#pragma once
#include <vector>

enum class Color {
    None,
    White,
    Black
};

enum class Piece {
    Empty,
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

struct Move {
    int from;
    int to;
    Move(int f, int t) : from(f), to(t) {}
    
    bool operator==(const Move& other) const {
        return from == other.from && to == other.to;
    }
};

class ChessEngine {
private:
    Piece board[64];
    Color turn;
    vector<Move> moveHistory;
    vector<Piece> capturedPieces;

public:
    ChessEngine();
    void PrintBoard();
    Move GetBestMove(int depth);
    bool IsValidMove(const Move& move) const;
    bool TryMakeMove(const Move& move);
    void UndoMove(const Move& move);
    Color GetCurrentTurn() const { return turn; }
    bool IsInCheck(Color color) const;
    bool IsCheckmate() const;
    bool IsStalemate() const;
    bool IsGameOver() const { return IsCheckmate() || IsStalemate(); }
    int GetMaterialBalance() const;
    void PrintMoveHistory() const;
    bool UndoLastMove();
    int GetMoveCount() const { return moveHistory.size(); }
    bool IsValidSquare(int pos) const { return pos >= 0 && pos < 64; }
    void AddMoveIfValid(int from, int to, vector<Move>& moves);

private:
    vector<Move> GenerateMoves();
    void GeneratePieceMoves(int pos, vector<Move>& moves);
    void GeneratePawnMoves(int pos, vector<Move>& moves);
    void GenerateKnightMoves(int pos, vector<Move>& moves);
    void GenerateBishopMoves(int pos, vector<Move>& moves);
    void GenerateRookMoves(int pos, vector<Move>& moves);
    void GenerateQueenMoves(int pos, vector<Move>& moves);
    void GenerateKingMoves(int pos, vector<Move>& moves);
    void SlideMoves(int pos, const int directions[], int count, vector<Move>& moves);
    int Minimax(int depth, int alpha, int beta, bool maximizing);
    int Evaluate();
    Color GetPieceColor(int pos) const;
};
>>>>>>> 38862bc (Fixed accidental embedded repo)

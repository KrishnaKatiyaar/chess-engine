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

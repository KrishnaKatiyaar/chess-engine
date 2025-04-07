#include "ChessEngine.h"
#include <iostream>

int main() {
    ChessEngine engine;
    engine.PrintBoard();
    
    std::cout << "\nAI is thinking...";
    Move bestMove = engine.GetBestMove(3);
    
    std::cout << "\nBest move: " 
              << char('a' + (bestMove.from%8)) 
              << (8 - bestMove.from/8) << " to "
              << char('a' + (bestMove.to%8)) 
              << (8 - bestMove.to/8) << std::endl;
    
    system("pause");
    return 0;
}

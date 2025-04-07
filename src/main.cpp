<<<<<<< HEAD
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
=======
#include "ChessEngine.h"
#include <iostream>
#include <string>
#include <windows.h>  // Add this line
#include <chrono>
#include <iomanip>

using namespace std;

Move ParseMove(const string& input) {
    if (input.length() < 4) return Move(-1, -1);
    
    int fromX = input[0] - 'a';
    int fromY = '8' - input[1];
    int toX = input[2] - 'a';
    int toY = '8' - input[3];
    
    if (fromX < 0 || fromX > 7 || fromY < 0 || fromY > 7 ||
        toX < 0 || toX > 7 || toY < 0 || toY > 7) {
        return Move(-1, -1);
    }
    
    return Move(fromY * 8 + fromX, toY * 8 + toX);
}

// Add game state tracking
void printGameStatus(const ChessEngine& engine) {
    cout << "\n=== Game Status ===\n";
    cout << "Turn: " << (engine.GetCurrentTurn() == Color::White ? "White" : "Black") << "\n";
    cout << "Material Balance: " << engine.GetMaterialBalance() << "\n";
    if (engine.IsInCheck(engine.GetCurrentTurn())) {
        cout << "CHECK!\n";
    }
    if (engine.IsCheckmate()) {
        cout << "CHECKMATE!\n";
    } else if (engine.IsStalemate()) {
        cout << "STALEMATE!\n";
    }
    cout << "==================\n";
}

int main() {
    ChessEngine engine;
    string input;
    auto gameStart = chrono::steady_clock::now();
    
    while (true) {
        system("cls");  // Clear screen for better display
        engine.PrintBoard();
        printGameStatus(engine);
        
        // Show move history
        cout << "\nMove History:\n";
        engine.PrintMoveHistory();
        
        if (engine.IsGameOver()) {
            cout << "\nGame Over! ";
            if (engine.IsCheckmate()) {
                cout << (engine.GetCurrentTurn() == Color::White ? "Black" : "White") << " wins by checkmate!\n";
            } else if (engine.IsStalemate()) {
                cout << "Draw by stalemate!\n";
            }
            break;
        }

        cout << "\nCommands:\n";
        cout << "- Move (e.g., 'e2e4')\n";
        cout << "- 'ai' for computer move\n";
        cout << "- 'undo' to take back move\n";
        cout << "- 'quit' to exit\n";
        cout << "\nEnter command: ";
        getline(cin, input);
        
        if (input == "quit") break;
        if (input == "undo") {
            if (engine.UndoLastMove()) {
                cout << "Move undone.\n";
            } else {
                cout << "No moves to undo.\n";
            }
            Sleep(500);
            continue;
        }
        
        if (input == "ai") {
            cout << "Thinking...\n";
            auto startTime = chrono::steady_clock::now();
            Move aiMove = engine.GetBestMove(4);
            auto endTime = chrono::steady_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
            
            if (aiMove.from != -1) {
                if (engine.IsValidMove(aiMove)) {
                    if (!engine.TryMakeMove(aiMove)) {
                        cout << "AI move execution failed.\n";
                        continue;
                    }
                    char fromFile = 'a' + (aiMove.from % 8);
                    char fromRank = '8' - (aiMove.from / 8);
                    char toFile = 'a' + (aiMove.to % 8);
                    char toRank = '8' - (aiMove.to / 8);
                    cout << "AI moves: " << fromFile << fromRank << toFile << toRank 
                         << " (took " << duration.count() << "ms)\n";
                }
            }
        } else {
            Move move = ParseMove(input);
            if (move.from == -1) {
                cout << "Invalid move format. Use format like 'e2e4'.\n";
                continue;
            }
            if (!engine.IsValidMove(move)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }
            if (!engine.TryMakeMove(move)) {
                cout << "Move execution failed. Try again.\n";
                continue;
            }
        }

        Sleep(500);
    }
    
    // Show game summary
    auto gameEnd = chrono::steady_clock::now();
    auto gameDuration = chrono::duration_cast<chrono::minutes>(gameEnd - gameStart);
    cout << "\nGame Summary:\n";
    cout << "Duration: " << gameDuration.count() << " minutes\n";
    cout << "Total Moves: " << engine.GetMoveCount() << "\n";
    
    return 0;
}
>>>>>>> 38862bc (Fixed accidental embedded repo)

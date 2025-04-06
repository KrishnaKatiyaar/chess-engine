@echo off
setlocal
set SOURCE_FILES=src\ChessEngine.cpp src\main.cpp
set OUTPUT_FILE=ChessEngine.exe

g++ -std=c++17 -O3 %SOURCE_FILES% -o %OUTPUT_FILE% -municode
echo Build complete! Run %OUTPUT_FILE%
endlocal

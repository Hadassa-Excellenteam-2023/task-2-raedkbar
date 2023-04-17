#pragma once

#include <memory>
#include <map>
#include <vector>
#include <iostream>

#include "PieceFactory.h"

class Piece;

class Board {
public:
    static Board& getInstance();
    int move(const std::string&);
    std::pair<std::pair<int, int>, std::pair<int, int>> parseMoveString(const std::string&) const;
    bool isValidPosition(int, int) const;
    void fillBoard(const std::string&);

private:
    bool m_currentPlayer = 1;
    static constexpr int m_numRows = 8;
    static constexpr int m_numCols = 8;

    std::vector<std::vector<std::unique_ptr<Piece>>> m_chessMatrix;

    // Functions used in move()
    void makeMove(std::pair<std::pair<int, int>, std::pair<int, int>>&);
    bool isCheck(const bool) const;
    bool isValidPath(const std::pair<int, int>&, const std::pair<int, int>&) const;
    
    Board();
};

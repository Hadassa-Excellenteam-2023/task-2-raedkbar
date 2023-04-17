#pragma once

#include <memory>
#include <map>
#include <vector>
#include <iostream>

#include "Factory.h"

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
    static constexpr int numRows = 8;
    static constexpr int numCols = 8;

    std::vector<std::vector<std::unique_ptr<Piece>>> chessMatrix;
    Factory<Piece> factory;

    // Functions used in move()
    void makeMove(std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords);
    bool isCheck(const bool) const;
    bool nextStep(const std::pair<int, int>&, const std::pair<int, int>&) const;
    
    Board();
};

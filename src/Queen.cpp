#pragma once

#include "Queen.h"

const bool Queen::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix)
{
    int startRow = moveCoords.first.first;
    int startCol = moveCoords.first.second;
    int endRow = moveCoords.second.first;
    int endCol = moveCoords.second.second;

    // Queens can move in any direction (diagonal, horizontal, or vertical)
    if (startRow != endRow && startCol != endCol && std::abs(startRow - endRow) != std::abs(startCol - endCol)) {
        return false;
    }
    // Check if path is clear
    if (!isPathClear(moveCoords, chessMatrix)) {
        return false;
    }
    // Check if destination square is occupied by a piece of the same color
    if (chessMatrix[endRow][endCol] != nullptr && chessMatrix[endRow][endCol]->getColor() == this->getColor()) {
        return false;
    }
    return true;
}

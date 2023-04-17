#pragma once

#include "Rook.h"

const bool Rook::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix)
{
    int startRow = moveCoords.first.first;
    int startCol = moveCoords.first.second;
    int endRow = moveCoords.second.first;
    int endCol = moveCoords.second.second;

    // Rooks can move horizontally or vertically, but not diagonally
    if (startRow != endRow && startCol != endCol) {
        return false;
    }

    // Check if the path is clear
    if (!isPathClear(moveCoords, chessMatrix)) {
        return false;
    }

    // Check if the destination square contains a piece of the same color
    if (chessMatrix[endRow][endCol] != nullptr && chessMatrix[endRow][endCol]->getColor() == this->getColor()) {
        return false;
    }

    return true;
}

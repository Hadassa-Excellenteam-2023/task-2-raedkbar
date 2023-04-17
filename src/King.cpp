#pragma once

#include "King.h"

const bool King::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix) {
    int startRow = moveCoords.first.first;
    int startCol = moveCoords.first.second;
    int endRow = moveCoords.second.first;
    int endCol = moveCoords.second.second;

    // King can only move one square in any direction
    if (std::abs(startRow - endRow) > 1 || std::abs(startCol - endCol) > 1) {
        return false;
    }

    // Check if the destination square contains a friendly piece
    if (chessMatrix[endRow][endCol] != nullptr && chessMatrix[endRow][endCol]->getColor() == this->getColor()) {
        return false;
    }

    return true;
}
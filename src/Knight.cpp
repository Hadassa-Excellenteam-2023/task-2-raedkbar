#pragma once

#include "Knight.h"

/**
 * Check if the move is valid for the Knight piece.
 *
 * @param moveCoords The start and end coordinates of the move.
 * @param chessMatrix The matrix representing the chessboard.
 * @return True if the move is valid for the Knight, false otherwise.
 */
const bool Knight::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix) {
    int startRow = moveCoords.first.first;
    int startCol = moveCoords.first.second;
    int endRow = moveCoords.second.first;
    int endCol = moveCoords.second.second;

    // Knight can move 2 squares in one direction and 1 square in the other, or vice versa
    if (std::abs(startRow - endRow) * std::abs(startCol - endCol) != 2) {
        return false;
    }

    // Check if the destination square contains a friendly piece
    if (chessMatrix[endRow][endCol] != nullptr && chessMatrix[endRow][endCol]->getColor() == this->getColor()) {
        return false;
    }

    return true;
}

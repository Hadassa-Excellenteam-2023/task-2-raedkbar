#pragma once

#include "Bishop.h"

/**
 * Checks if the move is valid for a Bishop piece.
 *  
 * @param moveCoords A pair of pairs of integers representing the start and end coordinates of the move.
 * @param chessMatrix A 2D vector of unique_ptr to Piece representing the current state of the chess board.
 * @return true if the move is valid for the Bishop piece, false otherwise.
 */
const bool Bishop::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix)
{
    int startRow = moveCoords.first.first;
    int startCol = moveCoords.first.second;
    int endRow = moveCoords.second.first;
    int endCol = moveCoords.second.second;

    // Bishops can only move diagonally
    if (std::abs(startRow - endRow) != std::abs(startCol - endCol)) {
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

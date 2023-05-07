#pragma once

#include "pieces_headers/Knight.h"

/**
 * Check if the move is valid for the Knight piece.
 *
 * @param moveCoords The start and end coordinates of the move.
 * @param chessBoard The matrix representing the chessboard.
 * @return True if the move is valid for the Knight, false otherwise.
 */
const bool Knight::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) {
    int sourceRow = moveCoords.first.first;
    int sourceCol = moveCoords.first.second;
    int destinationRow = moveCoords.second.first;
    int destinationCol = moveCoords.second.second;

    // Knight can move 2 squares in one direction and 1 square in the other, or vice versa
    if (std::abs(sourceRow - destinationRow) * std::abs(sourceCol - destinationCol) != 2) {
        return false;
    }

    // Check if the destination square contains a friendly piece
    if (isDestinationOccupiedBySameColorPiece(destinationRow, destinationCol, chessBoard)) {
        return false;
    }

    return true;
}

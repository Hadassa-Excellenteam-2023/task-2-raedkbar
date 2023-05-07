#pragma once

#include "pieces_headers/King.h"

/**
 * Check if the move is valid for the King piece.
 *
 * @param moveCoords The start and end coordinates of the move.
 * @param chessBoard The matrix representing the chessboard.
 * @return True if the move is valid for the King, false otherwise.
 */
const bool King::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) {
    int sourceRow = moveCoords.first.first;
    int sourceCol = moveCoords.first.second;
    int destinationRow = moveCoords.second.first;
    int destinationCol = moveCoords.second.second;

    // King can only move one square in any direction
    if (std::abs(sourceRow - destinationRow) > 1 || std::abs(sourceCol - destinationCol) > 1) {
        return false;
    }

    // Check if the destination square contains a friendly piece
    if (isDestinationOccupiedBySameColorPiece(destinationRow, destinationCol, chessBoard)) {
        return false;
    }

    return true;
}
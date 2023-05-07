#pragma once

#include "pieces_headers/Queen.h"

/**
 * Check if the move is valid for the Queen piece.
 *
 * @param moveCoords The start and end coordinates of the move.
 * @param chessBoard The matrix representing the chessboard.
 * @return True if the move is valid for the Queen, false otherwise.
 */
const bool Queen::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard)
{
    int sourceRow = moveCoords.first.first;
    int sourceCol = moveCoords.first.second;
    int destinationRow = moveCoords.second.first;
    int destinationCol = moveCoords.second.second;

    // Queens can move in any direction (diagonal, horizontal, or vertical)
    if (sourceRow != destinationRow && sourceCol != destinationCol && std::abs(sourceRow - destinationRow) != std::abs(sourceCol - destinationCol)) {
        return false;
    }

    // Check if path is clear
    if (!isPathClear(moveCoords, chessBoard)) {
        return false;
    }

    // Check if the destination square contains a friendly piece
    if (isDestinationOccupiedBySameColorPiece(destinationRow, destinationCol, chessBoard)) {
        return false;
    }

    return true;
}



#include "pieces_headers/Bishop.h"

/**
 * Checks if the move is valid for a Bishop piece.
 *  
 * @param moveCoords A pair of pairs of integers representing the source and destination coordinates of the move.
 * @param chessBoard A 2D vector of unique_ptr to Piece representing the current state of the chess board.
 * @return true if the move is valid for the Bishop piece, false otherwise.
 */
const bool Bishop::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) {
    int sourceRow = moveCoords.first.first;
    int sourceCol = moveCoords.first.second;
    int destinationRow = moveCoords.second.first;
    int destinationCol = moveCoords.second.second;

    // Bishops can only move diagonally
    if (std::abs(sourceRow - destinationRow) != std::abs(sourceCol - destinationCol)) {
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
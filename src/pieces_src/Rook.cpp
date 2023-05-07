

#include "pieces_headers/Rook.h"

/**
 * Check if the move is valid for the Rook piece.
 *
 * @param moveCoords The start and end coordinates of the move.
 * @param chessBoard The matrix representing the chessboard.
 * @return True if the move is valid for the Rook, false otherwise.
 */
const bool Rook::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard)
{
    int sourceRow = moveCoords.first.first;
    int sourceCol = moveCoords.first.second;
    int destinationRow = moveCoords.second.first;
    int destinationCol = moveCoords.second.second;

    // Rooks can move horizontally or vertically, but not diagonally
    if (sourceRow != destinationRow && sourceCol != destinationCol) {
        return false;
    }

    // Check if the path is clear
    if (!isPathClear(moveCoords, chessBoard)) {
        return false;
    }

    // Check if the destination square contains a friendly piece
    if (isDestinationOccupiedBySameColorPiece(destinationRow, destinationCol, chessBoard)) {
        return false;
    }

    return true;
}

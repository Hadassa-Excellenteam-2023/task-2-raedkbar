#include "pieces_headers/Pawn.h"

/**
 * Check if the move is valid for the Pawn piece.
 *
 * @param moveCoords The start and end coordinates of the move.
 * @param chessBoard The matrix representing the chessboard.
 * @return True if the move is valid for the Pawn, false otherwise.
 */
const bool Pawn::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard)
{
    int sourceRow = moveCoords.first.first;
    int sourceCol = moveCoords.first.second;
    int destinationRow = moveCoords.second.first;
    int destinationCol = moveCoords.second.second;

    const int direction = (this->getColor() == Color::WHITE) ? 1 : -1;
    const int rowDiff = destinationRow - sourceRow;
    const int colDiff = std::abs(destinationCol - sourceCol);

    // Pawns can only move forward
    if (sourceCol != destinationCol) {
        // If a pawn is moving diagonally, it can only take an enemy piece
        if (chessBoard[destinationRow][destinationCol] == nullptr || chessBoard[destinationRow][destinationCol]->getColor() == this->getColor()) {
            return false;
        }
        // Pawns can only move diagonally one square forward
        if (colDiff != 1 || rowDiff != direction) {
            return false;
        }
        // Pawns can only move diagonally one square forward except for en passant
        // If the pawn moved two squares forward in the previous move and lands next to the current pawn, then it can take it en passant
        if (chessBoard[sourceRow][destinationCol] == nullptr) {
            const auto& lastMove = getPrevMove();
            if (lastMove.second.first == sourceRow && std::abs(lastMove.second.second - destinationCol) == 1) {
                this->setPrevMove(moveCoords);
                return true;
            }
            return false;
        }
        this->setPrevMove(moveCoords);
        return true;
    } else {
        // Pawns can move one or two squares forward on their first move
        if (rowDiff == 2 * direction && sourceRow == (this->getColor() == Color::WHITE ? 1 : 6) && chessBoard[sourceRow + direction][sourceCol] == nullptr && chessBoard[destinationRow][destinationCol] == nullptr) {
            this->setPrevMove(moveCoords);
            return true;
        }
        // Pawns can only move one square forward otherwise
        if (rowDiff != direction) {
            return false;
        }
        // Pawns can only move one square forward except when taking a piece diagonally
        if (colDiff > 1 || (colDiff == 1 && chessBoard[destinationRow][destinationCol] == nullptr)) {
            return false;
        }
        this->setPrevMove(moveCoords);
        return true;
    }

}
#include "Piece.h"

/**
 * Sets the color of the piece.
 * 
 * @param color The color to set the piece to.
 */
void Piece::setIsWhite(bool color) { 
	m_isWhite = color; 
}

/**
 * @brief Gets the color of the piece.
 *
 * @return true if the piece is white, false otherwise.
 */
const bool Piece::getColor() const {
    return m_isWhite;
}

void Piece::setPrevMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& move) {
    prevMove = move;
}

/**
 * @brief Gets the previous move made by the piece.
 *
 * @return The previous move made by the piece.
 */
const std::pair<std::pair<int, int>, std::pair<int, int>>& Piece::getPrevMove() const {
    return prevMove;
}

/**
 * @brief Checks if the path of the move is clear of any pieces.
 *
 * @param moveCoords The start and end coordinates of the move.
 * @param chessMatrix The current state of the chess board.
 * @return true if the path is clear, false otherwise.
 */
const bool Piece::isPathClear(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix) const {
    int startRow = moveCoords.first.first;
    int startCol = moveCoords.first.second;
    int endRow = moveCoords.second.first;
    int endCol = moveCoords.second.second;

    // Check if move is horizontal
    if (startRow == endRow) {
        int direction = endCol > startCol ? 1 : -1;
        for (int col = startCol + direction; col != endCol; col += direction) {
            if (chessMatrix[startRow][col] != nullptr) {
                return false;
            }
        }
    }
    // Check if move is vertical
    else if (startCol == endCol) {
        int direction = endRow > startRow ? 1 : -1;
        for (int row = startRow + direction; row != endRow; row += direction) {
            if (chessMatrix[row][startCol] != nullptr) {
                return false;
            }
        }
    }
    // Check if move is diagonal
    else if (std::abs(startRow - endRow) == std::abs(startCol - endCol)) {
        int rowDirection = endRow > startRow ? 1 : -1;
        int colDirection = endCol > startCol ? 1 : -1;
        int row = startRow + rowDirection;
        int col = startCol + colDirection;
        while (row != endRow && col != endCol) {
            if (chessMatrix[row][col] != nullptr) {
                return false;
            }
            row += rowDirection;
            col += colDirection;
        }
    }

    return true;
}
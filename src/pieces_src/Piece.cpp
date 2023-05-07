#include "pieces_headers/Piece.h"

/**
 * Sets the color of the piece.
 * 
 * @param color The color to set the piece to.
 */
void Piece::setColor(bool color) { 
    m_color = (color == true) ? Color::WHITE : Color::BLACK;
}

/**
 * Gets the color of the piece.
 *
 * @return true if the piece is white, false otherwise.
 */
const Color Piece::getColor() const {
    return m_color;
}

/**
 * Sets the previous move.
 */
void Piece::setPrevMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& move) {
    prevMove = move;
}

/**
 * Gets the previous move made by the piece.
 *
 * @return The previous move made by the piece.
 */
const std::pair<std::pair<int, int>, std::pair<int, int>>& Piece::getPrevMove() const {
    return prevMove;
}

/**
 * Checks if the path of the move is clear of any pieces.
 *
 * @param moveCoords The source and destination coordinates of the move.
 * @param chessBoard The current state of the chess board.
 * @return true if the path is clear, false otherwise.
 */
const bool Piece::isPathClear(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) const {
    int sourceRow = moveCoords.first.first;
    int sourceCol = moveCoords.first.second;
    int destinationRow = moveCoords.second.first;
    int destinationCol = moveCoords.second.second;

    if (isHorizontalMove(sourceRow, destinationRow)) {
        return isHorizontalPathClear(sourceRow, sourceCol, destinationCol, chessBoard);
    } else if (isVerticalMove(sourceCol, destinationCol)) {
        return isVerticalPathClear(sourceRow, destinationRow, sourceCol, chessBoard);
    } else if (isDiagonalMove(sourceRow, destinationRow, sourceCol, destinationCol)) {
        return isDiagonalPathClear(sourceRow, destinationRow, sourceCol, destinationCol, chessBoard);
    }

    return true;
}

const bool Piece::isHorizontalMove(int& sourceRow, int& destinationRow) const {
    return sourceRow == destinationRow;
}

const bool Piece::isVerticalMove(int& sourceCol, int& destinationCol) const {
    return sourceCol == destinationCol;
}

const bool Piece::isDiagonalMove(int& sourceRow, int& destinationRow, int& sourceCol, int& destinationCol) const {
    return std::abs(sourceRow - destinationRow) == std::abs(sourceCol - destinationCol);
}

const bool Piece::isHorizontalPathClear(int& row, int& sourceCol, int& destinationCol, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) const {
    int direction = destinationCol > sourceCol ? 1 : -1;
    for (int col = sourceCol + direction; col != destinationCol; col += direction) {
        if (chessBoard[row][col] != nullptr) {
            return false;
        }
    }
    return true;
}

const bool Piece::isVerticalPathClear(int& sourceRow, int& destinationRow, int& col, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) const {
    int direction = destinationRow > sourceRow ? 1 : -1;
    for (int row = sourceRow + direction; row != destinationRow; row += direction) {
        if (chessBoard[row][col] != nullptr) {
            return false;
        }
    }
    return true;
}

const bool Piece::isDiagonalPathClear(int& sourceRow, int& destinationRow, int& sourceCol, int& destinationCol, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) const {
    int rowDirection = destinationRow > sourceRow ? 1 : -1;
    int colDirection = destinationCol > sourceCol ? 1 : -1;
    int row = sourceRow + rowDirection;
    int col = sourceCol + colDirection;
    while (row != destinationRow && col != destinationCol) {
        if (chessBoard[row][col] != nullptr) {
            return false;
        }
        row += rowDirection;
        col += colDirection;
    }
    return true;
}

/**
 * Check if a given move is valid for any pieces.
 *
 * @param moveCoords The source and destination coordinates of the move
 * @param chessBoard The current state of the chess board
 * @return True if the move is valid, false otherwise
 */
const bool Piece::isDestinationOccupiedBySameColorPiece(int destinationRow, int destinationCol, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) const {
    if (chessBoard[destinationRow][destinationCol] != nullptr && chessBoard[destinationRow][destinationCol]->getColor() == this->getColor()) {
        return true;
    }
    return false;
}
#include "MoveHandler.h"

/**
 * Get the singleton instance of the Board class.
 *
 * @return The Board instance.
 */
MoveHandler& MoveHandler::getInstance() {
    static MoveHandler instance;
    return instance;
}

/**
 * Check if the given position is a valid position on the chess board.
 *
 * @param row The row of the position.
 * @param col The column of the position.
 * @return True if the position is valid, false otherwise.
 */
bool MoveHandler::isValidPosition(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

/**
 * Makes a move on the chess board given the move coordinates.
 * @param moveCoords - The coordinates of the move in the format of a pair of pairs.
 */
void MoveHandler::carryMove(std::pair<std::pair<int, int>,
    std::pair<int, int>>& moveCoords,
    std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) {
    auto& sourcePos = moveCoords.first;
    auto& destinationPos = moveCoords.second;
    auto& targetPiece = chessBoard[destinationPos.first][destinationPos.second];

    // If there is a piece at the target position, remove it.
    if (targetPiece) {
        targetPiece.reset(nullptr);
    }

    // Move the piece from the source position to the end position.
    std::swap(chessBoard[sourcePos.first][sourcePos.second],
        chessBoard[destinationPos.first][destinationPos.second]);
}

/**
 * Checks if the given color is in check.
 * @param color - The color to check if in check.
 * @return - True if the given color is in check, false otherwise.
 */
bool MoveHandler::isCheck(const Color currentPlayer,
    std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) const {

    // Find the position of the king of the given color.
    std::pair<int, int> kingPosition;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (chessBoard[row][col] &&
                typeid(*chessBoard[row][col]) == typeid(King) &&
                chessBoard[row][col]->getColor() != currentPlayer) {
                kingPosition = std::make_pair(row, col);
                break;
            }
        }
    }

    // Check if any piece of the opposite color can capture the king.
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (chessBoard[row][col] != nullptr && chessBoard[row][col]->getColor() == currentPlayer) {
                std::pair piecePos = { row, col };
                if (chessBoard[row][col]->isValidMove({ piecePos, kingPosition }, chessBoard) && isValidPath(piecePos, kingPosition, chessBoard)) {
                    return true;
                }
            }
        }
    }

    return false;
}

/**
 * Checks if the path between two given positions is valid.
 * @param currPos - The current position.
 * @param newPos - The new position.
 * @return - True if the path is valid, false otherwise.
 */
bool MoveHandler::isValidPath(const std::pair<int, int>& currPos,
    const std::pair<int, int>& newPos,
    std::vector<std::vector<std::unique_ptr<Piece>>>& chessBoard) const {
    int deltaRow = newPos.first - currPos.first;
    int deltaCol = newPos.second - currPos.second;

    // Calculate the direction of the move.
    int rowDir = (deltaRow == 0) ? 0 : deltaRow / abs(deltaRow);
    int colDir = (deltaCol == 0) ? 0 : deltaCol / abs(deltaCol);

    // Check if the path is clear.
    int checkRow = currPos.first + rowDir;
    int checkCol = currPos.second + colDir;

    while (checkRow != newPos.first || checkCol != newPos.second) {
        if (chessBoard[checkRow][checkCol] != nullptr) {
            return false;
        }
        checkRow += rowDir;
        checkCol += colDir;
    }

    return true;
}
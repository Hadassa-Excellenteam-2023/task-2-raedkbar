#pragma once

#include "Board.h"

/**
 * Get the singleton instance of the Board class.
 *
 * @return The Board instance.
 */
Board& Board::getInstance() {
    static Board instance;
    return instance;
}

/**
 * Move a piece on the chess board.
 *
 * @param moveString The move to be made in string format.
 * @return An integer representing the result of the move.
 *         11: The starting position is not occupied by any piece.
 *         12: The player is trying to move a piece that is not theirs.
 *         13: The player is trying to capture their own piece.
 *         21: The move is not valid for the piece.
 *         41: The move results in the current player being in check.
 *         42: The move is successful and the turn is switched.
 */
int Board::move(const std::string& moveString) {
    auto moveCoords = parseMoveString(moveString);
    auto& startPos = moveCoords.first;
    auto& endPos = moveCoords.second;
    auto& currentPiece = m_chessMatrix[startPos.first][startPos.second];

    if (!currentPiece) {
        return 11;
    }

    if (currentPiece->getColor() != m_currentPlayer) {
        return 12;
    }

    if (m_chessMatrix[endPos.first][endPos.second] &&
        m_chessMatrix[endPos.first][endPos.second]->getColor() == m_currentPlayer) {
        return 13;
    }

    if (!currentPiece->isValidMove(moveCoords, m_chessMatrix)) {
        return 21;
    }

    makeMove(moveCoords);

    auto check = isCheck(m_currentPlayer);

    if (check) {
        return 41;
    }

    return 42;
}

/**
 * Parse the move string into coordinates.
 *
 * @param moveString The move to be parsed.
 * @return A pair of pairs, where the first pair is the starting position
 *         and the second pair is the ending position.
 */
std::pair<std::pair<int, int>, std::pair<int, int>> Board::parseMoveString(const std::string& moveString) const {
    std::pair<int, int> startPos = { -1, -1 };
    std::pair<int, int> endPos = { -1, -1 };
    int row = moveString[0] - 'a';
    int col = moveString[1] - '1';
    if (row >= 0 && row < m_numRows && col >= 0 && col < m_numCols) {
        startPos = { row, col };
    }
    row = moveString[2] - 'a';
    col = moveString[3] - '1';
    if (row >= 0 && row < m_numRows && col >= 0 && col < m_numCols) {
        endPos = { row, col };
    }
    return { startPos, endPos };
}

/**
 * Check if the given position is a valid position on the chess board.
 *
 * @param row The row of the position.
 * @param col The column of the position.
 * @return True if the position is valid, false otherwise.
 */
bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < m_numRows&& col >= 0 && col < m_numCols;
}

/**
 * Fill the chess board with pieces based on the input string.
 *
 * @param boardString The string representing the board and pieces.
 */
void Board::fillBoard(const std::string& boardString) {
    int index = 0;
    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            PieceFactory::getInstance().registerPiece(boardString[index], m_chessMatrix, row, col);
            ++index;
        }
    }
}

/**
 * Makes a move on the chess board given the move coordinates.
 * @param moveCoords - The coordinates of the move in the format of a pair of pairs.
 */
void Board::makeMove(std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords) {
    auto& startPos = moveCoords.first;
    auto& endPos = moveCoords.second;
    auto& targetPiece = m_chessMatrix[endPos.first][endPos.second];

    // If there is a piece at the target position, remove it.
    if (targetPiece) {
        targetPiece.reset(nullptr);
    }

    // Move the piece from the start position to the end position.
    std::swap(m_chessMatrix[startPos.first][startPos.second], m_chessMatrix[endPos.first][endPos.second]);
    m_currentPlayer = !m_currentPlayer;
}

/**
 * Checks if the given color is in check.
 * @param color - The color to check if in check.
 * @return - True if the given color is in check, false otherwise.
 */
bool Board::isCheck(const bool color) const {

    // Find the position of the king of the given color.
    std::pair<int, int> kingPosition;

    for (int row = 0; row < m_numRows; ++row) {
        for (int col = 0; col < m_numCols; ++col) {
            if (m_chessMatrix[row][col] &&
                typeid(*m_chessMatrix[row][col]) == typeid(King) &&
                m_chessMatrix[row][col]->getColor() == color) {
                kingPosition = std::make_pair(row, col);
                break;
            }
        }
    }

    // Check if any piece of the opposite color can capture the king.
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (m_chessMatrix[row][col] != nullptr && m_chessMatrix[row][col]->getColor() != color) {
                std::pair piecePos = { row, col };
                if (m_chessMatrix[row][col]->isValidMove({ piecePos, kingPosition }, m_chessMatrix) && isValidPath(piecePos, kingPosition)) {
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
bool Board::isValidPath(const std::pair<int, int>& currPos, const std::pair<int, int>& newPos) const {
    int deltaRow = newPos.first - currPos.first;
    int deltaCol = newPos.second - currPos.second;

    // Calculate the direction of the move.
    int rowDir = (deltaRow == 0) ? 0 : deltaRow / abs(deltaRow);
    int colDir = (deltaCol == 0) ? 0 : deltaCol / abs(deltaCol);

    // Check if the path is clear.
    int checkRow = currPos.first + rowDir;
    int checkCol = currPos.second + colDir;

    while (checkRow != newPos.first || checkCol != newPos.second) {
        if (m_chessMatrix[checkRow][checkCol] != nullptr) {
            return false;
        }
        checkRow += rowDir;
        checkCol += colDir;
    }

    return true;
}

/**
 *  @brief Constructor for the Board class.
 *  Initializes the chess matrix to contain null pointers for each square on the board.
 *  @return void
 */
Board::Board() {
    for (int row = 0; row < m_numRows; ++row) {
        std::vector<std::unique_ptr<Piece>> rowVec;
        for (int col = 0; col < m_numCols; ++col) {
            rowVec.emplace_back(nullptr);
        }
        m_chessMatrix.emplace_back(std::move(rowVec));
    }
}
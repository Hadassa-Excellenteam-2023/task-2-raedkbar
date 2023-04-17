#pragma once

#include "Board.h"

Board& Board::getInstance() {
    static Board instance;
    return instance;
}

int Board::move(const std::string& moveString) {
    auto moveCoords = parseMoveString(moveString);
    auto& startPos = moveCoords.first;
    auto& endPos = moveCoords.second;
    auto& currentPiece = chessMatrix[startPos.first][startPos.second];

    if (!currentPiece) {
        // There is no piece at the source
        return 11;
    }

    if (currentPiece->getColor() != m_currentPlayer) {
        // The piece in the source belongs to the opponent
        return 12;
    }

    if (chessMatrix[endPos.first][endPos.second] &&
        chessMatrix[endPos.first][endPos.second]->getColor() == m_currentPlayer) {
        // There is one of your pieces at the destination
        return 13;
    }

    if (!currentPiece->isValidMove(moveCoords, chessMatrix)) {
        // Illegal movement of that piece
        return 21;
    }

    // Make the move and check for checkmate
    makeMove(moveCoords);

    // Check if the move caused check
    auto check = isCheck(m_currentPlayer);

    if (check) {
        // The last movement was legal and caused check
        return 41;
    }

    // The last movement was legal and did not cause check
    return 42;
}

std::pair<std::pair<int, int>, std::pair<int, int>> Board::parseMoveString(const std::string& moveString) const {
    std::pair<int, int> startPos = { -1, -1 };
    std::pair<int, int> endPos = { -1, -1 };
    int row = moveString[0] - 'a';
    int col = moveString[1] - '1';
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        startPos = { row, col };
    }
    row = moveString[2] - 'a';
    col = moveString[3] - '1';
    if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
        endPos = { row, col };
    }
    return { startPos, endPos };
}

bool Board::isValidPosition(int row, int col) const {
    return row >= 0 && row < numRows && col >= 0 && col < numCols;
}

void Board::fillBoard(const std::string& boardString) {
    int index = 0;
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            factory.registerPiece(boardString[index], chessMatrix, row, col);
            ++index;
        }
    }
}

void Board::makeMove(std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords) {
    auto& startPos = moveCoords.first;
    auto& endPos = moveCoords.second;
    auto& currentPiece = chessMatrix[startPos.first][startPos.second];
    auto& targetPiece = chessMatrix[endPos.first][endPos.second];

    if (targetPiece) {
        targetPiece.reset(nullptr);
    }

    std::swap(chessMatrix[startPos.first][startPos.second], chessMatrix[endPos.first][endPos.second]);
    m_currentPlayer = !m_currentPlayer;
}

bool Board::isCheck(const bool color) const{
    
    std::pair<int, int> kingPosition;

    // Find king position
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            if (chessMatrix[row][col] &&
                typeid(*chessMatrix[row][col]) == typeid(King) &&
                chessMatrix[row][col]->getColor() == color) {
                kingPosition = std::make_pair(row, col);
                break;
            }
        }
    }

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (chessMatrix[row][col] != nullptr && chessMatrix[row][col]->getColor() != color) {
                std::pair piecePos = { row, col };
                if (chessMatrix[row][col]->isValidMove({ piecePos, kingPosition }, chessMatrix) && nextStep(piecePos, kingPosition)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Board::nextStep(const std::pair<int, int>& currPos, const std::pair<int, int>& newPos) const {
    int deltaRow = newPos.first - currPos.first;
    int deltaCol = newPos.second - currPos.second;

    //compute the direction the piece is going 
    int rowDir = (deltaRow == 0) ? 0 : deltaRow / abs(deltaRow);
    int colDir = (deltaCol == 0) ? 0 : deltaCol / abs(deltaCol);


    int checkRow = currPos.first + rowDir;
    int checkCol = currPos.second + colDir;
    //move gradually towards the new position
    while (checkRow != newPos.first || checkCol != newPos.second) {
        if (chessMatrix[checkRow][checkCol] != nullptr) {//if the path is blocked on the way
            return false;//return false, path is blocked
        }
        checkRow += rowDir;
        checkCol += colDir;
    }

    return true;//otherwise return true
}




Board::Board() {
    for (int row = 0; row < numRows; ++row) {
        std::vector<std::unique_ptr<Piece>> rowVec;
        for (int col = 0; col < numCols; ++col) {
            rowVec.emplace_back(nullptr);
        }
        chessMatrix.emplace_back(std::move(rowVec));
    }
}
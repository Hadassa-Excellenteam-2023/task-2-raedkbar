#pragma once

#include "Pawn.h"

const bool Pawn::isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix)
{
    int startRow = moveCoords.first.first;
    int startCol = moveCoords.first.second;
    int endRow = moveCoords.second.first;
    int endCol = moveCoords.second.second;

    // Pawns can only move forward
    if (startCol != endCol) {
        // If a pawn is moving diagonally, it can only take an enemy piece
        if (chessMatrix[endRow][endCol] == nullptr || chessMatrix[endRow][endCol]->getColor() == this->getColor()) {
            return false;
        }
        // Pawns can only move diagonally one square forward
        if (std::abs(startCol - endCol) != 1 || std::abs(startRow - endRow) != 1) {
            return false;
        }
        // Pawns can only move diagonally one square forward except for en passant
        // If the pawn moved two squares forward in the previous move and lands next to the current pawn, then it can take it en passant
        if (chessMatrix[startRow][endCol] == nullptr) {
            auto& lastMove = getPrevMove();
            if (lastMove != std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1)) &&
                lastMove.second.first == startRow && std::abs(lastMove.second.second - endCol) == 1) {
                this->setPrevMove(moveCoords);
                return true;
            }
            return false;
        }
        this->setPrevMove(moveCoords);
        return true;
    } else {
        // Pawns can move one or two squares forward on their first move
        if (startRow == 1 && endRow == 3 && startCol == endCol && chessMatrix[2][endCol] == nullptr && chessMatrix[3][endCol] == nullptr && this->getColor()) {
            this->setPrevMove(moveCoords);
            return true;
        } else if (startRow == 6 && endRow == 4 && startCol == endCol && chessMatrix[5][endCol] == nullptr && chessMatrix[4][endCol] == nullptr && !this->getColor()) {
            this->setPrevMove(moveCoords);
            return true;
        }
        // Pawns can only move one square forward otherwise
        if (std::abs(startRow - endRow) != 1) {
            return false;
        }
        // Pawns can only move one square forward, except for the first move where they can move two squares
        int direction = this->getColor() ? -1 : 1;
        if (startRow - endRow != direction) {
            return false;
        }
        // Pawns can only move one square forward except when taking a piece diagonally
        if (chessMatrix[endRow][endCol] != nullptr && std::abs(startCol - endCol) != 1) {
            return false;
        }
        this->setPrevMove(moveCoords);
        return true;
    }
}
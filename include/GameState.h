#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>
#include <map>
#include <vector>
#include <iostream>

#include "PieceFactory.h"
#include "MoveHandler.h"
#include "pieces_headers/Piece.h"

class GameState {
public:
    static GameState& getInstance();
    int handleTurn(const std::string&);
    std::pair<std::pair<int, int>, std::pair<int, int>> parseMoveString(const std::string&) const;
    std::pair<int, int> getPositionFromCharacters(char, char) const;
    void initializeBoard(const std::string&);
    void switchTurns();

private:
    Color m_currentPlayer;

    std::vector<std::vector<std::unique_ptr<Piece>>> m_chessBoard;

    GameState();
};

#endif // GAMESTATE_H
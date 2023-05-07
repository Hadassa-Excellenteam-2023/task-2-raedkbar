#include "GameState.h"

/**
 * Get the singleton instance of the Board class.
 *
 * @return The Board instance.
 */
GameState& GameState::getInstance() {
    static GameState instance;
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
int GameState::handleTurn(const std::string& moveString) {
    auto moveCoords = parseMoveString(moveString);
    auto& sourcePos = moveCoords.first;
    auto& destinationPos = moveCoords.second;
    auto& currentPiece = m_chessBoard[sourcePos.first][sourcePos.second];

    if (!currentPiece) {
        return SOURCE_EMPTY;
    }

    if (currentPiece->getColor() != m_currentPlayer) {
        return OPPONENT_PIECE;
    }

    if (m_chessBoard[destinationPos.first][destinationPos.second] &&
        m_chessBoard[destinationPos.first][destinationPos.second]->getColor() == m_currentPlayer) {
        return CAPTURE_OWN_PIECE;
    }

    if (!currentPiece->isValidMove(moveCoords, m_chessBoard)) {
        return INVALID_MOVE;
    }

    MoveHandler::getInstance().carryMove(moveCoords, m_chessBoard);

    if (MoveHandler::getInstance().isCheck(m_currentPlayer, m_chessBoard)) { 
        return CHECK; 
    }

    switchTurns();
    return SUCCESSFUL_MOVE;
}

/**
 * Parse the move string into coordinates.
 *
 * @param moveString The move to be parsed.
 * @return A pair of pairs, where the first pair is the source position
 *         and the second pair is the destination position.
 */
std::pair<std::pair<int, int>, std::pair<int, int>> GameState::parseMoveString(const std::string& moveString) const
{
    std::pair<int, int> sourcePos, destinationPos = { -1, -1 };
    if (moveString.size() == 4) {
        sourcePos = getPositionFromCharacters(moveString[0], moveString[1]);
        destinationPos = getPositionFromCharacters(moveString[2], moveString[3]);
    }
    return { sourcePos, destinationPos };
}

/**
 * Helper function to extract coordinates.
 *
 * @param c The character.
 * @return A pair that indicates a coordinate
 */
std::pair<int, int> GameState::getPositionFromCharacters(char c1, char c2) const {
    int row = c1 - 'a';
    int col = c2 - '1';
    return { row, col };
}

/**
 * Fill the chess board with pieces based on the input string.
 *
 * @param boardString The string representing the board and pieces.
 */
void GameState::initializeBoard(const std::string& boardString) {
    int index = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            m_chessBoard[row][col] = std::move(PieceFactory::getInstance().registerPiece(boardString[index]).value_or(nullptr));
            auto& a = m_chessBoard[row][col];
            ++index;
        }
    }
}

/**
 *  switches turns
 */
void GameState::switchTurns() {
    m_currentPlayer = (m_currentPlayer == Color::WHITE) ? Color::BLACK : Color::WHITE;
}


/**
 *  Constructor for the Board class.
 *
 *  Initializes the chess matrix to contain null pointers for each square on the board.
 *  @return void
 */
GameState::GameState() {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        std::vector<std::unique_ptr<Piece>> rowVec;
        for (int col = 0; col < BOARD_SIZE; ++col) {
            rowVec.emplace_back(nullptr);
        }
        m_chessBoard.emplace_back(std::move(rowVec));
    }
    m_currentPlayer = Color::WHITE;
}

#include "PieceFactory.h"

/**
 * Constructor for PieceFactory. Adds creators for each chess piece to the map.
 */
PieceFactory::PieceFactory() {
    // register creators for each chess piece
    registerCreator('R', []() { return std::make_unique<Rook>(); });
    registerCreator('N', []() { return std::make_unique<Knight>(); });
    registerCreator('B', []() { return std::make_unique<Bishop>(); });
    registerCreator('Q', []() { return std::make_unique<Queen>(); });
    registerCreator('K', []() { return std::make_unique<King>(); });
    registerCreator('P', []() { return std::make_unique<Pawn>(); });
}

/**
 * Returns a new unique_ptr to a Piece object of the given character, or nullptr if not found.
 *
 * @param c The character code of the piece to create.
 * @return A unique_ptr to the new Piece object, or nullptr if not found.
 */
std::unique_ptr<Piece> PieceFactory::createPiece(char pieceType) {
    auto creator = creators.find(pieceType);
    if (creator == creators.end()) {
        // creator not found, return nullptr
        return nullptr;
    }
    return creator->second();
}

/**
 * Creates a new Piece object from the given character code and adds it to the matrix at the given row and column.
 *
 * @param c The character code of the piece to create.
 * @param matrix The matrix to add the new piece to.
 * @param row The row index of the matrix to add the new piece to.
 * @param col The column index of the matrix to add the new piece to.
 * @return A unique_ptr to the new Piece object, or nullopt if not found.
 */
std::optional<std::unique_ptr<Piece>> PieceFactory::registerPiece(char c) {
    // Create a new Piece object from the given character code.
    auto piece = createPiece(std::toupper(c));
    if (piece) {
        // Set the Piece's color based on the character case.
        bool isWhite = (c >= 'A' && c <= 'Z');
        piece->setColor(isWhite);
        
        return piece;
    }
    // Return an empty optional to indicate an error.
    return std::nullopt;
}

/**
 * Adds a creator function for a new piece to the creators map.
 *
 * @param c The character code of the piece to create.
 * @param creator The creator function for the new piece.
 */
void PieceFactory::registerCreator(char pieceType, std::function<std::unique_ptr<Piece>()> creator) {
    creators[pieceType] = creator;
}
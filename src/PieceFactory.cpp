#include "PieceFactory.h"

/**
 * Constructor for PieceFactory. Adds creators for each chess piece to the map.
 */
PieceFactory::PieceFactory() {
    // Add creator for each chess piece to the map.
    addCreator('R', []() { return std::make_unique<Rook>(); });
    addCreator('N', []() { return std::make_unique<Knight>(); });
    addCreator('B', []() { return std::make_unique<Bishop>(); });
    addCreator('Q', []() { return std::make_unique<Queen>(); });
    addCreator('K', []() { return std::make_unique<King>(); });
    addCreator('P', []() { return std::make_unique<Pawn>(); });
}

/**
 * Returns a new unique_ptr to a Piece object of the given character, or nullptr if not found.
 *
 * @param c The character code of the piece to create.
 * @return A unique_ptr to the new Piece object, or nullptr if not found.
 */
std::unique_ptr<Piece> PieceFactory::createPiece(char c) {
    // Find the creator function associated with the given character.
    auto creator = creators.find(c);
    if (creator == creators.end()) {
        // Creator not found, return nullptr.
        return nullptr;
    }
    // Call the creator function and return the new Piece object.
    return creator->second();
}

/**
 * Creates a new Piece object from the given character code and adds it to the matrix at the given row and column.
 *
 * @param c The character code of the piece to create.
 * @param matrix The matrix to add the new piece to.
 * @param row The row index of the matrix to add the new piece to.
 * @param col The column index of the matrix to add the new piece to.
 * @return A unique_ptr to the new Piece object, or nullptr if not found.
 */
std::unique_ptr<Piece> PieceFactory::registerPiece(char c, std::vector<std::vector<std::unique_ptr<Piece>>>& matrix, int row, int col) {
    // Create a new Piece object from the given character code.
    auto piece = createPiece(std::toupper(c));
    if (piece) {
        // Set the Piece's color based on the character case.
        bool isWhite = (c >= 'A' && c <= 'Z');
        piece->setIsWhite(isWhite);
        // Add the Piece to the matrix.
        matrix[row][col] = std::move(piece);
    }
    return nullptr;
}

/**
 * Adds a creator function for a new piece to the creators map.
 *
 * @param c The character code of the piece to create.
 * @param creator The creator function for the new piece.
 */
void PieceFactory::addCreator(char c, std::function<std::unique_ptr<Piece>()> creator) {
    // Add the creator function to the map.
    creators[c] = creator;
}

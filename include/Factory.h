#include <memory>
#include <unordered_map>
#include <functional>

#include "Piece.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

template<typename T>
class Factory {
public:
    Factory() {
        addCreator('R', []() { return std::make_unique<Rook>(); });
        addCreator('N', []() { return std::make_unique<Knight>(); });
        addCreator('B', []() { return std::make_unique<Bishop>(); });
        addCreator('Q', []() { return std::make_unique<Queen>(); });
        addCreator('K', []() { return std::make_unique<King>(); });
        addCreator('P', []() { return std::make_unique<Pawn>(); });
    };

    std::unique_ptr<T> createPiece(char c);
    std::unique_ptr<T> registerPiece(char c, std::vector<std::vector<std::unique_ptr<T>>>& matrix, int row, int col);
    void addCreator(char c, std::function<std::unique_ptr<T>()> creator);
private:
    std::unordered_map<char, std::function<std::unique_ptr<T>()>> creators;
};

template<typename T>
std::unique_ptr<T> Factory<T>::createPiece(char c) {
    auto creator = creators.find(c);
    if (creator == creators.end()) {
        return nullptr;
    }
    return creator->second();
}

template<typename T>
std::unique_ptr<T> Factory<T>::registerPiece(char c, std::vector<std::vector<std::unique_ptr<T>>>& matrix, int row, int col) {
    auto piece = createPiece(std::toupper(c));
    if (piece) {
        bool isWhite = (c >= 'A' && c <= 'Z');
        piece->setIsWhite(isWhite);
        matrix[row][col] = std::move(piece);
    }
    return nullptr;
}

template<typename T>
void Factory<T>::addCreator(char c, std::function<std::unique_ptr<T>()> creator) {
    creators[c] = creator;
}
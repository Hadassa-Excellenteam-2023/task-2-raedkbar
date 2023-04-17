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

class PieceFactory {
public:
    static PieceFactory& getInstance() {
        static PieceFactory instance;
        return instance;
    }

    std::unique_ptr<Piece> createPiece(char);
    std::unique_ptr<Piece> registerPiece(char, std::vector<std::vector<std::unique_ptr<Piece>>>&, int, int);
private:
    PieceFactory();

    std::unordered_map<char, std::function<std::unique_ptr<Piece>()>> creators;

    void addCreator(char, std::function<std::unique_ptr<Piece>()>);
};
// PieceFactory.h
#ifndef PIECEFACTORY_H
#define PIECEFACTORY_H

#include <memory>
#include <map>
#include <vector>
#include <functional>
#include <optional>

#include "pieces_headers/Piece.h"
#include "pieces_headers/Rook.h"
#include "pieces_headers/Knight.h"
#include "pieces_headers/Bishop.h"
#include "pieces_headers/Queen.h"
#include "pieces_headers/King.h"
#include "pieces_headers/Pawn.h"



class PieceFactory {
public:
    static PieceFactory& getInstance() {
        static PieceFactory instance;
        return instance;
    }

    std::unique_ptr<Piece> createPiece(char pieceType);

    void registerCreator(char pieceType, std::function<std::unique_ptr<Piece>()> creator);
    std::optional<std::unique_ptr<Piece>> registerPiece(char);

private:
    PieceFactory();

    std::map<char, std::function<std::unique_ptr<Piece>()>> creators;
};

#endif // PIECEFACTORY_H
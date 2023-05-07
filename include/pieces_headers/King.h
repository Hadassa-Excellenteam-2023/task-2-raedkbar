#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    using Piece::Piece;

    const bool isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) override;
};

#endif // KING_H
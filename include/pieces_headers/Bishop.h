#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    using Piece::Piece;

    const bool isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) override;
};

#endif // BISHOP_H
#ifndef MOVEHANDLER_H
#define MOVEHANDLER_H

#include <string>
#include <vector>
#include <pieces_headers/King.h>

#include "Piece.h"

class MoveHandler {
public:
	static MoveHandler& getInstance();
	bool isValidPosition(int, int) const;

	void carryMove(std::pair<std::pair<int, int>, std::pair<int, int>>&,
		std::vector<std::vector<std::unique_ptr<Piece>>>&);

	bool isCheck(const Color,
		std::vector<std::vector<std::unique_ptr<Piece>>>&) const;

	bool isValidPath(const std::pair<int, int>&,
		const std::pair<int, int>&,
		std::vector<std::vector<std::unique_ptr<Piece>>>&) const;

private:
	MoveHandler() {};
};

#endif // MOVEHANDLER_H
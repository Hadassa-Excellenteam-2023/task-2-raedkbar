#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <memory>
#include <macros.h>

class Piece {
public:
	Piece() {};
	virtual ~Piece() {};
	virtual const bool isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) = 0;

	void setColor(bool);
	void setPrevMove(const std::pair<std::pair<int, int>, std::pair<int, int>>&);

	const Color getColor() const;
	const std::pair<std::pair<int, int>, std::pair<int, int>>& getPrevMove() const;

protected:
	const bool isPathClear(const std::pair<std::pair<int, int>, std::pair<int, int>>&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) const;
	const bool isDestinationOccupiedBySameColorPiece(int, int, const std::vector<std::vector<std::unique_ptr<Piece>>>&) const;

private:
	const bool isHorizontalMove(int&, int&) const;
	const bool isVerticalMove(int&, int&) const;
	const bool isDiagonalMove(int&, int&, int&, int&) const;
	const bool isHorizontalPathClear(int&, int&, int&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) const;
	const bool isVerticalPathClear(int&, int&, int&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) const;
	const bool isDiagonalPathClear(int&, int&, int&, int&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) const;

	std::pair<std::pair<int, int>, std::pair<int, int>> prevMove = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
	Color m_color = Color::NO_COLOR;
};

#endif // PIECE_H
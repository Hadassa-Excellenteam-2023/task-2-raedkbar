#pragma once

#include <string>
#include <vector>
#include <memory>

class Piece {
public:
	Piece() {};
	virtual ~Piece() {};
	virtual const bool isValidMove(const std::pair<std::pair<int, int>, std::pair<int, int>>&, const std::vector<std::vector<std::unique_ptr<Piece>>>&) = 0;

	void setIsWhite(bool);
	const bool getColor() const;
	void setPrevMove(const std::pair<std::pair<int, int>, std::pair<int, int>>&);
	const std::pair<std::pair<int, int>, std::pair<int, int>>& getPrevMove() const;

protected:
	const bool isPathClear(const std::pair<std::pair<int, int>, std::pair<int, int>>& moveCoords, const std::vector<std::vector<std::unique_ptr<Piece>>>& chessMatrix) const;

private:
	std::pair<std::pair<int, int>, std::pair<int, int>> prevMove = std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
	bool m_isWhite = NULL;
};
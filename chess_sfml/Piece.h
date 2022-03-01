#pragma once

struct Piece {

	int type;
	// unsigned int position;
	int color;

	// Rank, File, Knight, Diag1, Diag2, White pawn, Black pawn, King
	std::vector<bool> moveTypes;

	~Piece() = default;
	Piece(int _type, unsigned int _position) {

		if (std::abs(_type) >= 7)
			std::cout << "Invalid piece type" << std::endl;

		if (_position < 0 || 63 < _position)
			std::cout << "Invalid piece position" << std::endl;

		type = _type;
		// position = _position;
		
		if (type == 0)
			color = 0;
		else color = type > 0 ? 1 : -1;

		std::vector<bool> mt(8);

		if (type == 0)
			moveTypes = mt;
		else if (type == 1) // White pawn
			mt[0] = 1;
		else if (type == -1) // Black pawn
			mt[1] = 1;
		else if (std::abs(type) == 2) // Knight
			mt[2] = 1;
		else if (std::abs(type) == 3) // Bishop
			mt[3] = mt[4] = 1;
		else if (std::abs(type) == 4) // Rook
			mt[5] = mt[6] = 1;
		else if (std::abs(type) == 5) // Queen
			mt[3] = mt[4] = mt[5] = mt[6] = 1;
		else mt[7] = 1; // King

		moveTypes = mt;

	}
	std::string getPieceString() {

		std::string prefix = (type < 0) ? "B" : "W";

		if (type == 0)
			return "";
		else if (std::abs(type) == 1)
			return prefix + "Pawn";
		else if (std::abs(type) == 2)
			return prefix + "Knight";
		else if (std::abs(type) == 3)
			return prefix + "Bishop";
		else if (std::abs(type) == 4)
			return prefix + "Rook";
		else if (std::abs(type) == 5)
			return prefix + "Queen";
		else if (std::abs(type) == 6)
			return prefix + "King";

	}
};
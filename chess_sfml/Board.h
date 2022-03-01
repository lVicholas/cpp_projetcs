# pragma once
# include <iostream>
# include <vector>
# include <algorithm>
# include <map>

# include <SFML/Graphics.hpp>
# include <SFML/Window.hpp>

# include "Piece.h"

/*
	To include SFML files, in Visual Studio 2019...
	  1. Select ALL CONFIGURATIONS in Project properties
	  2. Add ...SFML\include to include path via
	     Project properties -> C/C++ -> General -> Additional Include Directories
      3. Add ...SFML\lib to
	     Project Properties -> Linker -> General-> Additional Library Directories
	  4. In Linker -> Input -> Additional Dependencies, add each SFML library file you need
	     (e.g., sfml-window.lib)
	  5. For DEBUG configuration, add debug library files to Additional Dependencies
	     (e.g., sfml-window-d.lib)
*/

struct Tile {

	unsigned int position, rank, file;
	bool color; // White == 0
	Piece* piece;
	std::vector<std::vector<Tile*>> neighborhoods;

	// Neighborhoods are
	// White pawn, Black pawn, Knight, Diag1, Diag2, Rank, File, King
	// Indices within neighborhoods listed in increasing order

	~Tile() = default;
	Tile(unsigned int _rank, unsigned int _file, int _piece) {

		if (_rank >= 8 || _file >= 8)
			std::cout << "Invalid rank/file" << std::endl;

		rank  = _rank;
		file  = _file;
		color = (rank + file) % 2;
		position = 8 * rank + file;
		piece = new Piece(_piece, position);

	}
	std::vector<unsigned int> whitePawnNeighborhood() {

		std::vector<unsigned int> w;

		if (rank == 0)
			return w;

		if (file != 0)
			w.push_back(position - 9);

		w.push_back(position - 8);
		
		if (file != 7)
			w.push_back(position - 7);

		return w;

	}
	std::vector<unsigned int> blackPawnNeighborhood() {

		std::vector<unsigned int> b;

		if (rank == 7)
			return b;

		if (file != 0)
			b.push_back(position + 7);

		b.push_back(position + 8);

		if (file != 7)
			b.push_back(position + 9);

		return b;

	}
	std::vector<unsigned int> getKnightIndices() {

		std::vector<unsigned int> vec;
		if (rank >= 2 && file >= 1)
			vec.push_back(position - 17);
		if (rank >= 2 && file <= 6)
			vec.push_back(position - 15);
		if (rank >= 1 && file >= 2)
			vec.push_back(position - 10);
		if (rank >= 1 && file <= 5)
			vec.push_back(position - 6);
		if (rank <= 6 && file >= 2)
			vec.push_back(position + 6);
		if (rank <= 6 && file <= 5)
			vec.push_back(position + 10);
		if (rank <= 5 && file >= 1)
			vec.push_back(position + 15);
		if (rank <= 5 && file <= 6)
			vec.push_back(position + 17);


		return vec;

	}
	std::vector<unsigned int> getDiag1Indices() {

		std::vector<unsigned int> vec;
		unsigned int M = std::max(rank, file);
		unsigned int m = std::min(rank, file);

		unsigned int it = position - (9 * m);
		while (it <= position + 9 * (7 - M)) {

			if (it < 0 || it >= 64)
				std::cout << "Tile " + position << " Diag1 out of bounds" << std::endl;

			if (it != position)
				vec.push_back(it);

			it += 9;

		}

		return vec;

	}
	std::vector<unsigned int> getDiag2Indices() {

		std::vector<unsigned int> vec;
		unsigned int m = std::min(rank, 7 - file);
		unsigned int M = std::min(7 - rank, file);

		unsigned int it = position - (7 * m);
		while (it <= position + (7 * M)) {

			if (it < 0 || it >= 64)
				std::cout << "Tile " + position << " diag2 out of bounds" << std::endl;

			if (it != position)
				vec.push_back(it);

			it += 7;

		}

		return vec;

	}
	std::vector<unsigned int> getrankIndices() {

		std::vector<unsigned int> vec;
		unsigned int it = 8 * rank;
		while ((it / 8) == rank) {

			if (it < 0 || it >= 64)
				std::cout << "Tile " + position << "out of bounds rank" << std::endl;

			if (it != position)
				vec.push_back(it);

			it++;

		}

		return vec;

	}
	std::vector<unsigned int> getFileIndices() {

		std::vector<unsigned int> vec;
		unsigned int it = file;
		while (it <= 63) {

			if (it < 0 || it >= 64)
				std::cout << "Tile " + position << " file out of bounds" << std::endl;

			if (it != position)
				vec.push_back(it);

			it += 8;

		}

		return vec;

	}
	std::vector<unsigned int> kingNeighborhood() {

		std::vector<unsigned int> k;

		if (rank != 0) {

			if (file != 0)
				k.push_back(position - 9);

			k.push_back(position - 8);

			if(file != 7)
				k.push_back(position - 7);

		}
		if (file != 0)
			k.push_back(position - 1);
		if (file != 7)
			k.push_back(position + 1);
		
		if (rank != 7) {

			if (file != 0)
				k.push_back(position + 7);

			k.push_back(position + 8);

			if(file != 7)
				k.push_back(position + 9);

		}

		return k;

	}
	void printIndices(std::vector<unsigned int>& v) {

		for (unsigned int i = 0; i < v.size(); i++)
			std::cout << v[i] << " ";
		std::cout << std::endl;

	}
	void printTile() {

		std::vector<unsigned int> R = getrankIndices(),
								  F = getFileIndices(),
								  N = getKnightIndices(),
								  U = getDiag1Indices(),
								  L = getDiag2Indices(),
								  W = whitePawnNeighborhood(),
								  B = blackPawnNeighborhood(),
								  K = kingNeighborhood();

		std::cout << "Rank, File, Position, Piece: \n";
		std::cout << rank << " " << file << " " << position << " " << piece << std::endl;
		std::cout << "Rank indices: "; printIndices(R);
		std::cout << "File indices: "; printIndices(F);
		std::cout << "Knight indices: "; printIndices(N);
		std::cout << "Upper diagonal indices: "; printIndices(U);
		std::cout << "Lower diagonal indices: "; printIndices(L);
		std::cout << "White pawn indices: "; printIndices(W);
		std::cout << "Black pawn indices: "; printIndices(B);
		std::cout << "King indices: "; printIndices(K);

	}
	bool inNeighborhood(Tile* to, unsigned int n) {

		// Takes advantage of neighborhoods listed in increasing order

		if (position == to->position) {

			std::cout << "Tile cannot be in neighborhood of itself" << std::endl;
			return false;

		}

		for (unsigned int i = 0; i < neighborhoods[n].size(); i++) {

			if (neighborhoods[n][i]->position == position)
				return true;

			if (neighborhoods[n][i]->position > to->position)
				return false;

		}

		std::cout << "Somehow reached end of inNeighborhood(); returning 0" << std::endl;
		return false;

	}
	unsigned int getNeighborhood(Tile* to) {

		for (unsigned int i = 0; i < neighborhoods.size(); i++) {
			if (inNeighborhood(to, i))
				return i;
		}

		return 8;

	}

};
struct Board {

	std::vector<Tile*> tiles;
	std::vector<int> pieceMatrix;
	bool move;
	std::pair<bool, bool> checks;
	std::vector<unsigned int> pieceTileIndices;
	std::vector<Piece*> pieces;
	std::vector<std::vector<unsigned int>> checkThreateners;

	std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	~Board() = default;
	Board() {

		move = 0;
		checks = { 0, 0 };
		pieceMatrix = readFEN(startingFEN);

		for (unsigned int i = 0; i < 8; i++) {
			for (unsigned int j = 0; j < 8; j++) {
				Tile* t = new Tile(i, j, pieceMatrix[j + (8 * i)]);
				tiles.push_back(t);

				if (pieceMatrix[j + (8 * i)] != 0) {

					pieceTileIndices.push_back(j + (8 * i));
					pieces.push_back(t->piece);

				}

				// By construction, pieceTileIndices and pieces in order of starting
				// position tile indices



			}
		}

		for (unsigned int i = 0; i < tiles.size(); i++)
			connectTileNeighbors(tiles[i]);

	}
	void connectTileNeighbors(Tile* tile) {

		std::vector<unsigned int> W = tile->whitePawnNeighborhood(),
			B = tile->blackPawnNeighborhood(),
			N = tile->getKnightIndices(),
			D = tile->getDiag1Indices(),
			E = tile->getDiag2Indices(),
			R = tile->getrankIndices(),
			F = tile->getFileIndices(),
			K = tile->kingNeighborhood();

		tile->neighborhoods.push_back(convertIndices(W));
		tile->neighborhoods.push_back(convertIndices(B));
		tile->neighborhoods.push_back(convertIndices(N));
		tile->neighborhoods.push_back(convertIndices(D));
		tile->neighborhoods.push_back(convertIndices(E));
		tile->neighborhoods.push_back(convertIndices(R));
		tile->neighborhoods.push_back(convertIndices(F));
		tile->neighborhoods.push_back(convertIndices(K));

	}
	std::vector<Tile*> convertIndices(std::vector<unsigned int>& indices) {

		std::vector<Tile*> vec;

		for (unsigned int i = 0; i < indices.size(); i++)
			vec.push_back(tiles[indices[i]]);

		return vec;

	}
	std::vector<int> readFEN(std::string& fen) {

		std::vector<int> matrix(64);
		unsigned int f = 0, r = 0, it = 0;
		for (unsigned int i = 0; i < fen.size(); i++) {

			if (it >= 64 || isspace(fen[i]))
				break;

			if (isalpha(fen[i])) {
				matrix[it] = convertLetterToNum(fen[i]);
				pieceTileIndices.push_back(it);
				it++;
			}

			if (isdigit(fen[i]))
				it += fen[i] - '0';

			if (fen[i] == '/')
				it += it % 8;

		}

		return matrix;

	}
	int convertLetterToNum(char p) {

		if (p == 'p')
			return -1;
		else if (p == 'P')
			return 1;
		else if (p == 'n')
			return -2;
		else if (p == 'N')
			return 2;
		else if (p == 'b')
			return -3;
		else if (p == 'B')
			return 3;
		else if (p == 'r')
			return -4;
		else if (p == 'R')
			return 4;
		else if (p == 'q')
			return -5;
		else if (p == 'Q')
			return 5;
		else if (p == 'k')
			return -6;
		else if (p == 'K')
			return 6;
		else {

			std::cout << "Invalid char in convertLetterToNumber" << std::endl;
			return -100;

		}

	}
	void printPieceMatrix() {

		if (pieceMatrix.empty())
			std::cout << "Empty piece matrix" << std::endl;

		for (unsigned int i = 0; i < pieceMatrix.size(); i++) {

			if (i % 8 == 0)
				std::cout << "\n" << pieceMatrix[i] << " ";
			else std::cout << pieceMatrix[i] << " ";

		}

	}
	std::string getPieceString(unsigned int position) {

		int p = pieceMatrix[position];

		if (p == 0)
			return " ";

		std::string prefix = (p < 0) ? "B" : "W";

		if (std::abs(p) == 1)
			return prefix + "Pawn";
		else if (std::abs(p) == 2)
			return prefix + "Knight";
		else if (std::abs(p) == 3)
			return prefix + "Bishop";
		else if (std::abs(p) == 4)
			return prefix + "Rook";
		else if (std::abs(p) == 5)
			return prefix + "Queen";
		else if (std::abs(p) == 6)
			return prefix + "King";
		else {

			std::cout << "Invalid piece in getPieceString" << std::endl;
			return " ";

		}

	}
	std::vector<unsigned int> getPossibleMoveIndices(Tile* from) {

		std::vector<unsigned int> moves;
		Piece* p = from->piece;

		if (p->type == 0)
			return moves;

		for (unsigned int i = 0; i < from->neighborhoods.size(); i++) {

			if (p->moveTypes[i]) {

				for (unsigned int j = 0; j < from->neighborhoods[i].size(); j++) {

					if (canAccessPositionally(from, from->neighborhoods[i][j], i))
						moves.push_back(from->neighborhoods[i][j]->position);

				}

			}

		}

		return moves;

	}
	bool canAccessPositionally(Tile* from, Tile* to, unsigned int n) {

		// Assuming "to" is in neighbohood "n" of "from"
		// Also assuming "from" has a piece

		// If piece on "to" is same color
		if (from->piece->color == to->piece->color)
			return false;

		// If Pawn, Knight, or King neighborhood, return if "to" is unoccupied
		// Or if occupied by enemy piece
		if (n < 3 || n == 7)
			return from->piece->color != to->piece->color;

		bool between = 0,
			 lesser = from->position < to->position;

		for (unsigned int i = 0; i < from->neighborhoods[n].size(); i++) {

			if (lesser) {

				if (from->neighborhoods[n][i]->position > from->position)
					between = 1;

				if (between == 1) {

					if (from->neighborhoods[n][i] == to)
						return true;
					else if (from->neighborhoods[n][i]->piece->color != 0)
						return false;

				}

			}

			if (!lesser) {

				if (from->neighborhoods[n][i] == to) {

					between = 1;
					continue;

				}

				if (from->neighborhoods[n][i] == from)
					return true;
				else if (from->neighborhoods[n][i]->piece->color != 0)
					return false;


			}

		}

		return true;

	}
	bool illegalMove(Tile* from, Tile* to) {


		

	}
	void movePiece(Tile* from, Tile* to) {

		pieceMatrix[to->position] = from->piece->type;
		pieceMatrix[from->position] = 0;

		from->piece = new Piece()

	}

};

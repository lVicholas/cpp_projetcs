# Chess
[IN PROGRESS]
Chess game using SFML

Summary:
Piece obects simply store the color (white or black) of the piece and the piece type (e.g. pawn, queen) as ints.

Board object is a 64-array of tile objects. Each Tile object stores its position (rank and file), a pointer to the pice object on the tile (nullptr if no piece), and a collection of arrays of tile pointers. Each array of tile pointers is associated with a piece type (e.g. knight), and any piece of that type can access any tile in that array (assuming there are no checks or pins onboard). These arrays are calculated and stored at the beginning of the cpp to decrease the time needed to calculate legal moves at any given turn.

main() is responsible for displaying sprites (by using SFML library) and registering events (e.g. piece clicked by user)

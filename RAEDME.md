Chess Game

This is a console-based Chess Game written in C++ using CMake as the build system. The game allows two players to play against each other and implements all standard chess rules.

rules:

    The game starts with the board displayed on the console.
    Players will take turns moving their pieces by entering the coordinates of the piece they want to move, and the coordinates of the destination square. For example, to move a pawn from square A2 to square A4, the player would enter "A2A4".
    If a player's move puts the opponent's king in check, the game will notify the player.
    If a player's move puts the opponent's king in checkmate, the game will end and the player who put the king in checkmate will be declared the winner.
    If a player's move results in a stalemate, the game will end in a draw.

Features

    The game implements standard chess rules, including castling, en passant.
    The game tracks the state of the board and enforces legal moves.
    The game notifies players of illegal moves and checks and checkmates, by returning response codes.
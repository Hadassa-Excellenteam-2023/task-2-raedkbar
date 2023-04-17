// Chess 
#include "Chess.h"
#include "Board.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	auto& b = Board::getInstance();
	b.fillBoard("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	int codeResponse = 0;
	string res = a.getInput();
    while (res != "exit")
    {
        codeResponse = b.move(res);
        a.setCodeResponse(codeResponse);
        res = a.getInput();
    }

	cout << endl << "Exiting " << endl; 
	return 0;
}
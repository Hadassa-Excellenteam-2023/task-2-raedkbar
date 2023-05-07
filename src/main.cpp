// Chess 
#include "Chess.h"
#include "GameState.h"

int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr"; 
//	string board = "##########K###############################R#############r#r#####";
	Chess a(board);
	auto& g = GameState::getInstance();
	g.initializeBoard("RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	int code = 0;
	string res = a.getInput();
    while (res != "exit")
    {
        code = g.handleTurn(res);
        a.setCodeResponse(code);
        res = a.getInput();
    }

	cout << endl << "Exiting " << endl; 
	return 0;
}
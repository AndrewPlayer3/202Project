#ifndef BOARD_HPP
#define BOARD_HPP
#include <vector>

class Board {

public:

	//Vector that holds the board pieces
	std::vector<std::vector<int>> board{ { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 0, 0, 0, 0, 0 },
										 { 0, 0, 0, 0, 0, 0, 0 },
									   	 { 0, 0, 0, 0, 0, 0, 0 }
	};


	//Draw function

	//Checks Winner  function

	//Check 4 in a row function (Vertically, horizontally, diagonally)

	//Check if column is maxxed out (7)

}

#endif
#pragma once

class Board
{
public:
	std::vector<std::string> board;
	Board()
	{
		board.resize(9, " ");
	}

	void Place(int pos, const std::string& symbol)
	{
		if (pos > 0 && pos <= 9 && Space_check(pos)) 
		{
			board[pos - 1] = symbol;
		}
		else
		{
			std::cout << "ERROR: UNABLE TO PLACE '" << symbol << "' AT POS. " << pos << std::endl;
			exit(-1);
		}
	}

	 bool Space_check(int pos) const
	{
		if (pos > 0 && pos <= 9)
		{
			return board[pos - 1] == " ";

		}
		else
		{
			return false;
		}
	}

	int Win_cond(const std::string& mark) const
	{
		return(((board[6] == mark and board[7] == mark and board[8] == mark) || // across the top
		(board[3] == mark && board[4] == mark && board[5] == mark) || // across the middle
		(board[0] == mark && board[1] == mark && board[2] == mark) || // across the bottom
		(board[6] == mark && board[3] == mark && board[0] == mark) || // down the middle
		(board[7] == mark && board[4] == mark && board[1] == mark) || // down the middle
		(board[8] == mark && board[5] == mark && board[2] == mark) || // down the right side
		(board[6] == mark && board[4] == mark && board[2] == mark) || // diagonal
		(board[8] == mark && board[4] == mark && board[0] == mark)));
	}

	bool Full_board_check() const
	{
		const int size = 9;
		for (int i = 0; i < size; i++)
		{
			if (Space_check(i))
			{
				return false;
			}
		}
		return true;
	}

	void Display()
	{
		std::cout << "     |     |     "  << std::endl;
		std::cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << std::endl;
		std::cout << "     |     |     "  << std::endl;
		std::cout << "-----|-----|-----"  << std::endl;
		std::cout << "     |     |      " << std::endl;
		std::cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << std::endl;
		std::cout << "     |     |      "  << std::endl;
		std::cout << "-----|-----|-----"  << std::endl;
		std::cout << "     |     |      " << std::endl;
		std::cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << std::endl;
		std::cout << "     |     |      " << std::endl;
		std::cout << std::endl;
	}
};

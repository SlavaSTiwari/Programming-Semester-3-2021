#pragma once

class Logic
{
private:

public:
	std::string P1_symb = " ";
	std::string P2_symb = " ";
	Logic(){};

	void Symbol_choice()
	{
		std::string P1_symbol = "";
		while (P1_symbol != "X" && P1_symbol != "O" && P1_symbol != "x" && P1_symbol != "o")
		{
			std::cout << "Player 1, Choose 'X' or 'O': ";
			std::cin >> P1_symbol;
			if (P1_symbol == "X" || P1_symbol == "x")
			{
				P1_symb = "X";
				P2_symb = "O";
			}
			else if(P1_symbol == "O" || P1_symbol == "o")
			{
				P1_symb = "O";
				P2_symb = "X";
			}
			else
			{
				std::cout << "INVALID CHOICE! PLEASE CHOOSE 'X' OR 'O'!\n" << std::endl;
			}
		}
	}

	int Player_choice(Board board)
	{
		int input = -1;
		std::cout << "Choose a position: ";
		while( !(input > 0 && input <= 9 && board.Space_check(input)) )
		{
			std::cin >> input;
			 
			if ( !(input > 0 && input <= 9 && board.Space_check(input)) )
			{
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "INVALID POSITTION, CHOOSE AGAIN: ";
			}
		}
		return input;
	}


	std::string Check_winner(Board board)
	{
		if (board.Win_cond(P1_symb))
		{
			return "P1";
		}
		if (board.Win_cond(P2_symb))
		{
			return "P2";
		}
		if (board.Full_board_check())
		{
			return "TIE";
		}
		return "NULL";
	}

	int Minimax(Board& board, int depth, int alpha, int beta, bool isMaximizing)
	{
		std::string result = Check_winner(board);
		if (result != "NULL")
		{
			if (result == "P1")
			{
				return  -10;
			}
			if (result == "P2")
			{
				return +10;
			}
			if (result == "TIE")
			{
				return 0;
			}
		}
		if (isMaximizing)
		{
			int best_score = -10000;
			for (int i = 1; i <= 9; i++)
			{
				if (board.Space_check(i))
				{
					board.Place(i, P2_symb); // p2 is the AI...
					int score = Minimax(board, depth+1, alpha, beta ,false);
					board.board[i-1] = " ";
					best_score = std::max(best_score, score);
					alpha = std::max(alpha, score);
					if (beta <= alpha)
					{
						break;
					}
				}
			}
			return best_score;
		}
		else
		{
			int best_score = 10000;
			for (int i = 1; i <= 9; i++)
			{
				if (board.Space_check(i))
				{
					board.Place(i, P1_symb); // p1 is the human...
					int score = Minimax(board, depth + 1,alpha, beta, true);
					board.board[i-1] = " ";
					best_score = std::min(best_score, score);
					beta = std::min(beta, score);
					if (beta <= alpha)
					{
						break;
					}
				}
			}
			return best_score;
		}
	}

	int Best_move(Board& board)
	{
		int score;
		int best_score = -10000;
		int best_move;
		for (int i = 1; i <= 9; i++)
		{
			// Is the spot available?
			if (board.Space_check(i))
			{
				board.Place(i, P2_symb); // p2 is the AI...
				score = Minimax(board, 0, -10000, 10000 ,false);
				board.board[i-1] = " ";
				if (score > best_score)
				{
					//std::cout << "The score is : " << score << " > " << best_score << std::endl;
					best_score = score;
					best_move = i;
				}
			}
		}
		std::cout << "TICTACBOT: 'Hahaha! The best move is: " << best_move << "!'" << std::endl;
		return best_move;
	}


	bool replay()
	{
		char Choice;
		std::cout << "\nDo you want to play again? [Y/N]: ";
		while (true)
		{
			std::cin >> Choice;
			if (Choice == 'Y' || Choice == 'y')
			{
				return true;
			}
			else if (Choice == 'N' || Choice == 'n')
			{
				return false;
			}
			else
			{
				std::cout << "Please enter a valid choice! [Y/N]: ";
			}
		}
	}



	std::string Choose_turn()
	{
		srand(time(0));
		std::string turn;
		int choice = rand() % 2 + 1;
		if (choice == 1)
		{
			return "Player_1";
		}
		else
		{
			return "Player_2";
		}
	}

};

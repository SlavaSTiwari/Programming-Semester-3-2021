#pragma once

void Game_start()
{
	while (true)
	{
		bool Game_on = true;

		Logic logic;
		Board board;
		std::cout << "Welcome to TicTacToe!" << std::endl;
		logic.Symbol_choice();
		board.Display();
		std::string turn = logic.Choose_turn();

		while (Game_on)
		{
			if (turn == "Player_1")
			{
				// Player 1 turn:
				std::cout << "\nPlayer 1's turn:" << std::endl << std::flush;
				board.Place(logic.Player_choice(board), logic.P1_symb);
				board.Display();
				if (board.Win_cond(logic.P1_symb))
				{
					std::cout << "Player 1 wins!" << std::endl;
					Game_on = false;
				}
				else
				{
					if (board.Full_board_check())
					{
						std::cout << "The game is a draw!" << std::endl;
						Game_on = false;
					}
					else
					{
						turn = "Player_2";
					}
				}
			}

			if (turn == "Player_2")
			{
				// Player 2 turn:
				std::cout << "\nTICTACBOT's turn: " << std::endl << std::flush;
				board.Place(logic.Best_move(board), logic.P2_symb);
				board.Display();
				if (board.Win_cond(logic.P2_symb))
				{
					std::cout << "TICTACBOT: 'Bwahaha! You can't beat me!'" << std::endl;
					std::cout << "TICTACBOT wins!" << std::endl;
					Game_on = false;
				}
				else
				{
					if (board.Full_board_check())
					{
						std::cout << "The game is a draw!" << std::endl;
						Game_on = false;
					}
					else
					{
						turn = "Player_1";
					}
				}
			}

		}
		if (!logic.replay())
		{
			std::cout << "Thanks for playing!" << std::endl;
			break;
		}

	}

}


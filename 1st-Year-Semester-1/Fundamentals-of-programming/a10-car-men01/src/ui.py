from board import Board
from game import Game, ComputerRandomMoves


class UI:
    def __init__(self):
        pass

    @staticmethod
    def check_row_column_input(parameters: str):
        elements = parameters.split(' ')
        is_digit = elements[0].isdigit() and elements[1].isdigit()

        if (len(elements) != 2) or not is_digit:
            raise ValueError("Incorrect parameters!")

        return int(elements[0]), int(elements[1])

    @staticmethod
    def get_computer_player():
        return ComputerRandomMoves()

    def start(self):
        print("Welcome to Obstruction!\n")
        board_size = input("Enter the size of a square board on which you want to play: ")
        try:
            board_size = int(board_size)
        except ValueError:
            print("Board size must be an integer.")

        board_game = Board(board_size)
        computer_player = self.get_computer_player()
        game = Game(board_game, computer_player)

        user_turn = True

        while True:
            print('\nThe current board is:')
            print("")
            print(board_game)

            if user_turn:
                try:
                    user_input = input("\nEnter your move (row column): ").strip()
                    try:
                        x, y = self.check_row_column_input(user_input)
                        game.make_user_move(x, y, 'X')
                        print("\nThe user moved X on row", x, "column", y)
                    except ValueError as v:
                        print("\n" + str(v))
                        continue
                except ValueError:
                    print("\nInvalid command. Please input a command in the format: row column.\n")
                    continue
            else:
                row, column = game.make_computer_move()
                print("\nThe computer moved O on row", row, "column", column)

            board_status = board_game.get_board_status()

            if board_status == "human":
                print(board_game)
                print('\nGame was won by the human player.')
                return
            elif board_status == "computer":
                print(board_game)
                print('\nGame was won by the computer player.')
                return

            user_turn = not user_turn

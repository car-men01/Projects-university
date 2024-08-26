from random import randint

class ComputerRandomMoves:
    def __init__(self):
        pass

    def move(self, board):
        """
        Generates a random move for the computer
        :param board: The updated board on which the computer plays
        """
        row = randint(1, board.size)
        column = randint(1, board.size)
        valid_move = False
        while not valid_move:
            try:
                board.update_position(row, column, 'O')
                valid_move = True
                return row, column
            except ValueError:
                row = randint(1, board.size)
                column = randint(1, board.size)

class Game:
    def __init__(self, board, computer_player):
        self.__board = board
        self.__computer = computer_player

    def make_user_move(self, row, column, symbol):
        """
        Make the user move on the board
        :param row: chosen row
        :param column: chosen column
        :param symbol: user's symbol 'X'
        """
        self.__board.update_position(row, column, symbol)

    def make_computer_move(self):
        return self.__computer.move(self.__board)

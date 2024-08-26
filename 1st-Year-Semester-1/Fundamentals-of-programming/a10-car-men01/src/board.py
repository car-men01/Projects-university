from texttable import Texttable

class Board:
    def __init__(self, size):
        self.__size = size
        self.__board = [[' ' for _ in range(self.__size)] for _ in range(self.__size)]
        self.__moves = []

    @property
    def size(self):
        return self.__size

    def get_board(self):
        return self.__board

    def update_position(self, row, column, symbol):
        """
        Updates the position (row,column) on the board with the given symbol, if possible
        :param row: row of current move
        :param column: column of current move
        :param symbol: the symbol we want to place on position (row,column)
        """

        if not 0 < row <= self.__size or not 0 < column <= self.__size:
            raise ValueError("Invalid position on board.")

        if self.__board[row - 1][column - 1] != ' ':
            raise ValueError(f"The space {row}, {column} has already been played.")

        self.__board[row - 1][column - 1] = symbol          # update the board with the symbol 'X' or 'O'
        self.__moves.append(symbol)                         # add the move to the list of moves

        # add the obstructed squares using the symbol '/'
        i = row - 2
        j = column - 2

        while i < row + 1:
            while j < column + 1:
                if 0 <= i < self.__size and 0 <= j < self.__size:
                    if self.__board[i][j] == ' ':
                        self.__board[i][j] = '/'
                j += 1
            j = column - 2
            i += 1

    def is_full(self):
        """
        Checks if the board is full by looking for empty spaces
        """
        for row in self.__board:
            if ' ' in row:
                return False
        return True

    def get_board_status(self) -> str:
        """
        Checks if someone won the game
        """
        if self.is_full():
            if self.__moves[-1] == 'X':
                return "human"
            else:
                return "computer"
        return "playing"

    def __str__(self):
        """
        Prints the board
        """
        table = Texttable()
        header = ['/']
        for i in range(self.__size):
            header.append(i + 1)
        table.add_row(header)

        i = 1
        for row in self.__board:
            row = [elem for elem in row]
            table.add_row([i] + row)
            i += 1
        return table.draw()

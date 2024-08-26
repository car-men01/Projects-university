import unittest

from board import Board

class Test(unittest.TestCase):

    def setUp(self):
        self.board = Board(6)

    def test_board_size(self):
        self.assertEqual(self.board.size, 6)

    def test_update_position_valid_move(self):
        self.board.update_position(1, 1, 'X')
        self.assertEqual(self.board.get_board()[0][0], 'X')
        self.assertEqual(self.board.get_board_status(), 'playing')

    def test_get_board_status_playing(self):
        self.assertEqual(self.board.get_board_status(), 'playing')

    def test_get_board_status_human_winner(self):
        self.board.update_position(1, 1, 'X')
        self.board.update_position(3, 3, 'O')
        self.board.update_position(5, 6, 'X')
        self.assertEqual(self.board.get_board_status(), 'human')

    def test_get_board_status_computer_winner(self):
        self.board.update_position(1, 1, 'X')
        self.board.update_position(3, 3, 'O')
        self.assertEqual(self.board.get_board_status(), 'computer')

    def test_is_full_empty_board(self):
        self.assertFalse(self.board.is_full())

    def test_is_full_board(self):
        for i in range(1, self.board.size + 1):
            for j in range(1, self.board.size + 1):
                self.board.update_position(i, j, 'X')
        self.assertTrue(self.board.is_full())

import unittest
from src.domain.book import Book
from src.domain.client import Client
from src.domain.rental import Rental
from src.repository.bookRepository import BookRepositoryMemory
from src.repository.clientRepository import ClientRepositoryMemory
from src.repository.rentalRepository import RentalRepositoryMemory
from src.services.rentalService import RentalService
from src.services.bookService import BookService
from src.services.clientService import ClientService
from src.services.undoService import UndoService


class TestServices(unittest.TestCase):
    client_repository = ClientRepositoryMemory()
    book_repository = BookRepositoryMemory()
    rental_repository = RentalRepositoryMemory()
    undo_service = UndoService()
    client_service = ClientService(client_repository, undo_service, rental_repository)
    book_service = BookService(book_repository, undo_service, rental_repository)
    rental_service = RentalService(rental_repository, book_repository, client_repository, undo_service)

    def test_add(self):
        client_id = 1
        name = "Mara Pacurar"
        self.client_service.add_client(client_id, name)
        self.assertEqual(len(self.client_service.get_all_clients()), 1)

        book_id = 1
        title = "The Lord of the Rings"
        author = "J.R.R. Tolkien"
        self.book_service.add_book(book_id, title, author)
        self.assertEqual(len(self.book_service.get_all_books()), 1)

        rental_id = 1
        rented_date = "10-10-2022"
        returned_date = "11-12-2022"
        self.rental_service.add_rental(rental_id, book_id, client_id, rented_date, returned_date)
        self.assertEqual(len(self.rental_service.get_all_rentals()), 1)

    def test_delete(self):
        self.client_service.delete_client(1)
        self.assertEqual(len(self.client_service.get_all_clients()), 0)
        self.book_service.delete_book(1)
        self.assertEqual(len(self.book_service.get_all_books()), 0)
        self.rental_service.delete_rental(1)
        self.assertEqual(len(self.rental_service.get_all_rentals()), 0)

    def test_update(self):
        self.client_service.add_client(1, "Mara Pacurar")
        new_name = "Marius Pop"
        updated_client = self.client_service.update_client(1, new_name)
        self.assertEqual(updated_client.name, new_name)

        self.book_service.add_book(1, "The Lord of the Rings", "J.R.R. Tolkien")
        new_title = "The Hobbit"
        new_author = "J.R.R. Tolkien"
        updated_book = self.book_service.update_book(1, new_title, new_author)
        self.assertEqual(updated_book.title, new_title)

class TestRepository(unittest.TestCase):
    test_repository = ClientRepositoryMemory()
    assert (test_repository.__len__() == 0)

    client1 = Client(10, "Andi Popescu")
    client2 = Client(5, "Maria Scurtu")

    test_repository.add(client1)
    test_repository.add(client2)
    assert (test_repository.__len__() == 2)


class TestObjects(unittest.TestCase):
    client = Client(1, "Mihai Chirita")
    assert (client.name() == "Mihai Chirita")

    client1 = Client(10, "Andi Popescu")
    client2 = Client(10, "Andi Popescu")
    assert (client1 == client2)

    client1 = Client(100, "Andi Popescu")
    client2 = Client(10, "Andi Popescu")
    assert (client1 != client2)

    book = Book(2, "The Lord of the Rings", "J.R.R. Tolkien")
    assert (book.title() == "The Lord of the Rings")
    assert (book.author() == "J.R.R. Tolkien")

    book1 = Book(10, "The Lord of the Rings", "J.R.R. Tolkien")
    book2 = Book(10, "The Lord of the Rings", "J.R.R. Tolkien")
    assert (book1 == book2)

    book1 = Book(100, "The Lord of the Rings", "J.R.R. Tolkien")
    book2 = Book(10, "The Lord of the Rings", "J.R.R. Tolkien")
    assert (book1 != book2)

    rental = Rental(1, book, client, "10-10-2022", "11-12-2022")
    assert (rental.id() == 1)
    assert (rental.book() == book)
    assert (rental.client() == client)
    assert (rental.rented_date() == "10-10-2022")
    assert (rental.returned_date() == "11-12-2022")
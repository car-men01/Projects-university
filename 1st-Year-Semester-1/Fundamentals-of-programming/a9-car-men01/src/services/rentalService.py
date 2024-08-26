import random
from random import choice, randint
from collections import Counter
from datetime import datetime, timedelta
from src.domain.rental import Rental
from src.repository.errorRepository import BookRentalException, RepositoryError
from src.services.undoService import Command, Operation

class RentalService:
    def __init__(self, rental_repository, book_repository, client_repository, undo_service):
        self.__rental_repository = rental_repository
        self.__book_repository = book_repository
        self.__client_repository = client_repository
        self.__undo_service = undo_service

    def save_rental_file(self):
        try:
            self.__rental_repository.save_file()
        except:
            pass

    def add_rental(self, id: int, client_id, book_id, rented_date, returned_date):
        client = self.__client_repository.get(client_id)
        book = self.__book_repository.get(book_id)

        rental = Rental(id, book, client, rented_date, returned_date)

        if self.is_book_available(rental.book, rental.rented_date, rental.returned_date) is False:
            raise BookRentalException()

        self.__rental_repository.add(rental)
        self.save_rental_file()
        return rental

    def rent_book(self, rental_id, client_id, book_id, rented_date):
        book = self.__book_repository.get(book_id)
        client = self.__client_repository.get(client_id)
        if self.is_book_available(book, rented_date, rented_date):
            rental = Rental(rental_id, book, client, rented_date, "-")
            undo_command = Command(self.delete_rental, rental_id)
            redo_command = Command(self.add_rental, rental_id, client_id, book_id, rented_date, "-")
            operation = Operation(undo_command, redo_command)
            self.__undo_service.record_for_undo(operation)
            self.__rental_repository.add(rental)
        else:
            raise BookRentalException()
        self.save_rental_file()

    def is_book_available(self, book, rented_date, returned_date):
        """
        Check the availability of the given book to be rented in the provided time period
        book - The availability of this book is verified
        rented, returned date - The time span. The book is available if it is not rented in this time span
        Return True if the book is available, False otherwise
        """
        rentals = self.filter_rentals(None, book)
        for rental in rentals:
            if rented_date > rental.returned_date or returned_date < rental.rented_date:
                continue
            return False
        return True

    def filter_rentals(self, client, book):
        """
        Return a list of rentals performed by the provided client for the provided book
        client - The client performing the rental. None means all clients
        book - The rented book. None means all books
        """
        list_of_clients = []
        for rental in self.__rental_repository.get_all():
            if client is not None and rental.client != client:
                continue
            if book is not None and rental.book != book:
                continue
            list_of_clients.append(rental)
        self.save_rental_file()
        return list_of_clients

    def return_book(self, id, book_id, returned_date):
        """
        Returns a book back to the library
        """
        for rental in self.__rental_repository.get_all():
            if rental.id == id and rental.book.id == book_id:
                if rental.rented_date <= returned_date:
                    old_rental = Rental(id, rental.book, rental.client, rental.rented_date, rental.returned_date)
                    new_rental = Rental(id, rental.book, rental.client, rental.rented_date, returned_date)
                    undo_command = Command(self.__rental_repository.update, old_rental)
                    redo_command = Command(self.__rental_repository.update, new_rental)
                    operation = Operation(undo_command, redo_command)
                    self.__undo_service.record_for_undo(operation)
                    self.__rental_repository.update(new_rental)
                else:
                    raise RepositoryError("The returned date has to be after the rented date.")
        self.save_rental_file()

    def delete_rental(self, id: int):
        """
        Delete a rental with given id
        """
        deleted_rental = self.__rental_repository.remove(id)
        self.save_rental_file()
        return deleted_rental

    def most_rented_books(self):
        """
        Return a list of books sorted descending by the number of times they were rented
        """
        book_appearances = Counter(rental.book.id for rental in self.__rental_repository.get_all())
        sorted_books = sorted(self.__book_repository.get_all(), key=lambda book: book_appearances[book.id],
                              reverse=True)

        return sorted_books, book_appearances

    def most_active_clients(self):
        """
        Return a list of clients sorted descending by the number of days they rented books
        """
        client_appearances = Counter(rental.client.id for rental in self.__rental_repository.get_all())
        sorted_clients = sorted(self.__client_repository.get_all(), key=lambda client: client_appearances[client.id],
                                reverse=True)

        return sorted_clients, client_appearances

    def most_rented_authors(self):
        """
        Return a list of authors sorted descending by the number of times their books were rented
        """
        author_appearances = Counter(rental.book.author for rental in self.__rental_repository.get_all())
        sorted_authors = sorted(self.__book_repository.get_all(), key=lambda book: author_appearances[book.author],
                                reverse=True)

        return sorted_authors, author_appearances

    def get_all_rentals(self) -> list:
        return self.__rental_repository.get_all()

    @staticmethod
    def generate_random_date(start_date, end_date):
        start_datetime = datetime.strptime(start_date, "%d-%m-%Y")
        end_datetime = datetime.strptime(end_date, "%d-%m-%Y")
        random_days = randint(0, (end_datetime - start_datetime).days)
        random_date = start_datetime + timedelta(days=random_days)
        return random_date.strftime("%d-%m-%Y")

    def add_generated_rentals(self):
        start_date = "01-01-2022"
        end_date = "31-12-2023"
        id = list(range(1, 100))
        random.shuffle(id)
        for i in range(15):
            client_id = choice(self.__client_repository.get_all_id())
            book_id = choice(self.__book_repository.get_all_id())
            client = self.__client_repository.get(client_id)
            book = self.__book_repository.get(book_id)
            rented_date = self.generate_random_date(start_date, end_date)
            returned_date = self.generate_random_date(rented_date, end_date)
            rental = Rental(id[i], book, client, rented_date, returned_date)
            self.__rental_repository.add(rental)
        self.save_rental_file()
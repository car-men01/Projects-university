from src.domain.client import Client
from src.domain.book import Book

class Rental:
    def __init__(self, id: int, book: Book, client: Client, rented_date, returned_date):
        self.__id = id
        self.__book = book
        self.__client = client
        self.__rented_date = rented_date
        self.__returned_date = returned_date

    @property
    def id(self):
        return self.__id

    @property
    def book(self):
        return self.__book

    @property
    def client(self):
        return self.__client

    @property
    def rented_date(self):
        return self.__rented_date

    @property
    def returned_date(self):
        return self.__returned_date

    @id.setter
    def id(self, new_id):
        self.__id = new_id

    @book.setter
    def book(self, book):
        self.__book = book

    @client.setter
    def client(self, client):
        self.__client = client

    @rented_date.setter
    def rented_date(self, rented_date):
        self.__rented_date = rented_date

    @returned_date.setter
    def returned_date(self, returned_date):
        self.__returned_date = returned_date

    def __str__(self):
        return ("Rental id " + str(self.id) + "\n- " + str(self.__book) + "\n- Rented by " + str(self.__client) +
                "\n- Period: " + str(self.__rented_date) + " to " +
                str(self.__returned_date))

    def __eq__(self, other):
        if not isinstance(other, Rental):
            return False
        return self.__id == other.id

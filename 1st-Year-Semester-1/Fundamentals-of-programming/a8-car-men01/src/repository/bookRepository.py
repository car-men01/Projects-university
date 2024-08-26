from src.domain.book import Book
from src.repository.errorRepository import RepositoryError

class BookRepositoryMemory:
    def __init__(self):
        self.__books = {}

    def add(self, book: Book):
        """
        Add a book to repository
        """
        if book.id in self.__books:
            raise RepositoryError("There is already a book with this id")
        self.__books[book.id] = book

    def remove(self, id: int):
        """
        Remove book with given id
        """
        if id not in self.__books:
            raise RepositoryError("Book with given id does not exist")
        deleted_book = self.__books[id]
        del self.__books[id]
        return deleted_book

    def get(self, book_id: int):
        """
        Find book with the given id
        """

        for book in self.__books.values():
            if book_id == book.id:
                return book

    def update(self, updated_book: Book):
        """
        Update the book given as parameter. The provided book replaces the one having the same id
        """
        book = self.get(updated_book.id)
        if book is None:
            raise RepositoryError("Book with given id does not exist.")

        self.__books[book.id] = updated_book

    def get_all(self):
        """
        Return all books in repository
        """
        return list(self.__books.values())

    def get_all_id(self):
        return [book.id for book in self.__books.values()]

    def __len__(self):
        """
        Return number of books in repository
        """
        return len(self.__books.values())

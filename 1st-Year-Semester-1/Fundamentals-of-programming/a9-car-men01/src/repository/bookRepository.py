from src.domain.book import Book
from src.repository.errorRepository import RepositoryError
import pickle

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


class BookRepositoryText(BookRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            file = open(self.__filename, mode='r')
            book_list = {}
            lines = file.readlines()
            for line in lines:
                elements = line.split(',')
                elements = [element.strip() for element in elements]
                id = int(elements[0])
                title = elements[1]
                author = elements[2]
                book = Book(id, title, author)
                book_list[book.id] = book
            file.close()
            return book_list
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, mode='w') as file:
            for book in self.get_all():
                book_elements = [book.id, book.title, book.author]
                book_elements = [str(element) for element in book_elements]
                line = ', '.join(book_elements) + '\n'
                file.write(line)

class BookRepositoryBinary(BookRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            with open(self.__filename, 'rb') as file:
                while True:
                    books = pickle.load(file)
                    self.add(books)
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, 'wb') as file:
            for book in self.get_all():
                pickle.dump(book, file)

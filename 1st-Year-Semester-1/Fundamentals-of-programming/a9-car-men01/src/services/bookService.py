import random
from src.domain.book import Book
from src.services.undoService import Command, Operation

class BookService:
    def __init__(self, repository, undo_service, rental_service):
        self.__repository = repository
        self.__undo_service = undo_service
        self.__rental_service = rental_service

    def save_book_file(self):
        try:
            self.__repository.save_file()
        except:
            pass

    def add_book(self, id: int, title: str, author: str):
        """
        Add a book
        """
        book = Book(id, title, author)
        self.__repository.add(book)
        undo_command = Command(self.delete_book, id)
        redo_command = Command(self.add_book, id, book.title, book.author)
        operation = Operation(undo_command, redo_command)
        self.__undo_service.record_for_undo(operation)
        self.save_book_file()

    def delete_book(self, id: int):
        """
        Delete a book with given id
        """
        deleted_book = self.__repository.remove(id)
        undo_command = Command(self.add_book, deleted_book.id, deleted_book.title, deleted_book.author)
        redo_command = Command(self.delete_book, id)
        book_operation = Operation(undo_command, redo_command)
        self.__undo_service.record_for_undo(book_operation)

        rentals = self.__rental_service.filter_rentals(None, deleted_book)
        for rental in rentals:
            self.__rental_service.delete_rental(rental.id)
        self.save_book_file()
        return deleted_book

    def update_book(self, id: int, title: str, author: str):
        """
        Updates a book`s data
        """
        book = self.__repository.get(id)
        undo_action = Command(self.update_book, id, book.title, book.author)
        redo_action = Command(self.update_book, id, title, author)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.__repository.update(Book(id, title, author))
        self.save_book_file()

    def search_book(self, text):
        """
        Searches for books that contain the given text in their id, title or author
        """
        matching_books = {}
        for book in self.__repository.get_all():
            if text.lower() in str(book.id) or text.lower() in book.title.lower() or text.lower() in book.author.lower():
                matching_books[book.id] = book

        if matching_books:
            return list(matching_books.values())
        else:
            return None

    def get_all_books(self) -> list:
        return self.__repository.get_all()

    def add_generated_books(self):
        id = list(range(1, 100))
        random.shuffle(id)
        for i in range(20):
            title_list = ["The Great Gatsby", "Moby Dick", "Hamlet", "The Odyssey", "The Divine Comedy",
                          "Pride and Prejudice", "The Adventures of Huckleberry Finn", "Nineteen Eighty Four",
                          "Invisible Man", "To Kill a Mockingbird", "The Trial", "The Lord of the Rings",
                          "Les Misérables", "The Metamorphosis", "Frankenstein", "Lord of the Flies",
                          "The Good Soldier", "Poems of Emily Dickinson", "King Lear", "The Little Prince"]
            author_list = ["F. Scott Fitzgerald", "Herman Melville", "William Shakespeare", "Homer", "Dante Alighieri",
                           "Jane Austen", "Mark Twain", "George Orwell", "Ralph Ellison", "Harper Lee", "Franz Kafka",
                           "J. R. R. Tolkien", "Victor Hugo", "Franz Kafka", "Mary Shelley", "William Golding",
                           "Ford Madox Ford", "Emily Dickinson", "William Shakespeare", "Antoine de Saint-Exupéry"]
            self.add_book(id[i], title_list[i], author_list[i])
        self.save_book_file()

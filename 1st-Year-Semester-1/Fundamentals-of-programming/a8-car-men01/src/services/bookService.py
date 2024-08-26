import random
from src.domain.book import Book

class BookService:
    def __init__(self, repository):
        self.__repository = repository

    def add_book(self, id: int, title: str, author: str):
        """
        Add a book
        """
        book = Book(id, title, author)
        self.__repository.add(book)

    def delete_book(self, id: int):
        """
        Delete a book with given id
        """
        return self.__repository.remove(id)

    def update_book(self, id: int, title: str, author: str):
        """
        Updates a book`s data
        """
        self.__repository.update(Book(id, title, author))

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

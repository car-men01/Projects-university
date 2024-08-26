from src.domain.rental import Rental
from src.domain.book import Book
from src.domain.client import Client
from src.repository.errorRepository import RentalAlreadyExistsError, RentalDoesNotExistError
import pickle


class RentalRepositoryMemory:
    def __init__(self):
        self.__rentals = {}

    def add(self, rental: Rental):
        """
        Add rental to repository
        """
        if rental.id in self.__rentals.keys():
            raise RentalAlreadyExistsError()
        self.__rentals[rental.id] = rental

    def remove(self, id):
        """
        Remove rental
        """
        if id not in self.__rentals:
            raise RentalDoesNotExistError()
        deleted_rental = self.__rentals[id]
        del self.__rentals[id]
        return deleted_rental

    def get(self, rental_id: int):
        """
        Find rental with the given id
        """
        for rental in self.__rentals.values():
            if rental_id == rental.id:
                return rental
        return None

    def update(self, updated_rental: Rental):
        """
        Update the rental given as parameter. The provided rental replaces the one having the same id
        """
        rental = self.get(updated_rental.id)
        if rental is None:
            raise RentalDoesNotExistError()

        self.__rentals[rental.id] = updated_rental

    def get_all(self):
        """
        Return all rentals in repository
        """
        return list(self.__rentals.values())

    def __len__(self):
        """
        Return number of rentals in repository
        """
        return len(self.__rentals)

class RentalRepositoryText(RentalRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            file = open(self.__filename, mode='r')
            rental_list = {}
            lines = file.readlines()
            for line in lines:
                elements = line.split(',')
                elements = [element.strip() for element in elements]
                id = int(elements[0])
                book = Book(int(elements[1]), elements[2], elements[3])
                client = Client(int(elements[4]), elements[5])
                rented_date = elements[6]
                returned_date = elements[7]
                rental = Rental(id, book, client, rented_date, returned_date)
                rental_list[rental.id] = rental
            file.close()
            return rental_list
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, mode='w') as file:
            for rental in self.get_all():
                rental_elements = [rental.id, rental.book, rental.client, rental.rented_date, rental.returned_date]
                rental_elements = [str(element) for element in rental_elements]
                line = ', '.join(rental_elements) + '\n'
                file.write(line)

class RentalRepositoryBinary(RentalRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            with open(self.__filename, 'rb') as file:
                while True:
                    rentals = pickle.load(file)
                    self.add(rentals)
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, 'wb') as file:
            for rental in self.get_all():
                pickle.dump(rental, file)

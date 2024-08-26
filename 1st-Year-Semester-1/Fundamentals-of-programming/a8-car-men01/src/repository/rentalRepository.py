from src.domain.rental import Rental
from src.repository.errorRepository import RentalAlreadyExistsError, RentalDoesNotExistError


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
        # return None

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

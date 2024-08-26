class RepositoryError(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message

    def __str__(self):
        return "Repository error: " + str(self.message)


class DuplicateIdError(RepositoryError):
    def __init__(self):
        RepositoryError.__init__(self, "There already is a client with this id.")


class ClientDoesNotExistError(RepositoryError):
    def __init__(self):
        RepositoryError.__init__(self, "Client with the given id does not exist.")

class RentalAlreadyExistsError(RepositoryError):
    def __init__(self):
        RepositoryError.__init__(self, "There already is a rental with that Id.")

class RentalDoesNotExistError(RepositoryError):
    def __init__(self):
        RepositoryError.__init__(self, "There is no rental with that Id.")

class BookRentalException(RepositoryError):
    def __init__(self):
        RepositoryError.__init__(self, "Book is not available for rental during that time period.")

class UndoException(RepositoryError):
    def __init__(self):
        RepositoryError.__init__(self, "There is nothing left to undo.")

class RedoException(RepositoryError):
    def __init__(self):
        RepositoryError.__init__(self, "There is nothing left to redo.")

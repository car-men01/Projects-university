import configparser
import pathlib
from src.repository.clientRepository import ClientRepositoryMemory, ClientRepositoryText, ClientRepositoryBinary
from src.repository.bookRepository import BookRepositoryMemory, BookRepositoryText, BookRepositoryBinary
from src.repository.rentalRepository import RentalRepositoryMemory, RentalRepositoryText, RentalRepositoryBinary
from src.services.clientService import ClientService
from src.services.bookService import BookService
from src.services.rentalService import RentalService
from src.services.undoService import UndoService
from src.ui.UI import UI


config = configparser.ConfigParser()
config.read('src/ui/settings.properties')
config.sections()

repository_type = config["repository"]["repositoryType"]

client_repository_files = config['repository.files']['clients']
book_repository_files = config['repository.files']['books']
rental_repository_files = config['repository.files']['rentals']

if repository_type == 'inmemory':
    client_repository = ClientRepositoryMemory()
    book_repository = BookRepositoryMemory()
    rental_repository = RentalRepositoryMemory()

elif repository_type == 'textfiles':
    path = pathlib.Path(__file__).parent.parent.absolute().joinpath(client_repository_files)
    client_repository = ClientRepositoryText(path)
    path = pathlib.Path(__file__).parent.parent.absolute().joinpath(book_repository_files)
    book_repository = BookRepositoryText(path)
    path = pathlib.Path(__file__).parent.parent.absolute().joinpath(rental_repository_files)
    rental_repository = RentalRepositoryText(path)

    client_repository.load_file()
    book_repository.load_file()
    rental_repository.load_file()

elif repository_type == 'binaryfiles':
    path = pathlib.Path(__file__).parent.parent.absolute().joinpath(client_repository_files)
    client_repository = ClientRepositoryBinary(path)
    path = pathlib.Path(__file__).parent.parent.absolute().joinpath(book_repository_files)
    book_repository = BookRepositoryBinary(path)
    path = pathlib.Path(__file__).parent.parent.absolute().joinpath(rental_repository_files)
    rental_repository = RentalRepositoryBinary(path)

    client_repository.load_file()
    book_repository.load_file()
    rental_repository.load_file()


undo_service = UndoService()
rental_service = RentalService(rental_repository, book_repository, client_repository, undo_service)
client_service = ClientService(client_repository, undo_service, rental_service)
book_service = BookService(book_repository, undo_service, rental_service)

console = UI(book_service, client_service, rental_service, undo_service)

console.run_program()

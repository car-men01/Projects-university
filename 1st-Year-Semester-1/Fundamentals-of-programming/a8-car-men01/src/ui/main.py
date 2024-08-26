from src.repository.clientRepository import ClientRepositoryMemory
from src.repository.bookRepository import BookRepositoryMemory
from src.repository.rentalRepository import RentalRepositoryMemory
from src.services.clientService import ClientService
from src.services.bookService import BookService
from src.services.rentalService import RentalService
from src.ui.UI import UI

client_repository = ClientRepositoryMemory()
book_repository = BookRepositoryMemory()
rental_repository = RentalRepositoryMemory()

client_service = ClientService(client_repository)
book_service = BookService(book_repository)
rental_service = RentalService(rental_repository, book_repository, client_repository)

console = UI(book_service, client_service, rental_service)

console.run_program()

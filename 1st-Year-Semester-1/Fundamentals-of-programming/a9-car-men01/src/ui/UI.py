from src.repository.errorRepository import RepositoryError

class UI:
    def __init__(self, book_service, client_service, rental_service, undo_service):
        self.__book_service = book_service
        self.__client_service = client_service
        self.__rental_service = rental_service
        self.__undo_service = undo_service

    @staticmethod
    def __print_main_menu():
        print("1 ~ Manage clients and books")
        print("2 ~ Rent or return a book")
        print("3 ~ Search for clients or books")
        print("4 ~ Create statistics")
        print("5 ~ Undo/Redo")
        print("6 ~ Exit the program")

    @staticmethod
    def __print_submenu_1():
        print("1 ~ Add client")
        print("2 ~ Add book")
        print("3 ~ Remove client")
        print("4 ~ Remove book")
        print("5 ~ Update client")
        print("6 ~ Update book")
        print("7 ~ List clients")
        print("8 ~ List books")

    @staticmethod
    def __print_submenu_2():
        print("1 ~ Rent a book")
        print("2 ~ Return a book")
        print("3 ~ List rentals")

    @staticmethod
    def __print_submenu_3():
        print("1 ~ Search for clients")
        print("2 ~ Search for books")

    @staticmethod
    def __print_submenu_4():
        print("1 ~ Most rented books")
        print("2 ~ Most active clients")
        print("3 ~ Most rented author")

    @staticmethod
    def print_entity_list(entity_list):
        print("")
        for entity in entity_list:
            print(entity)
        print("")

    def add_book_ui(self):
        print('Please provide book information')
        id = input("Book id: ")
        title = input("Book title: ")
        author = input("Book author: ")
        try:
            id = int(id)
            self.__book_service.add_book(id, title, author)
            print('\nThe book was successfully added.')
        except ValueError:
            print('\nId should be a number')

        except RepositoryError as e:
            print('\nERROR:' + str(e))
        print("")

    def delete_book_ui(self):
        id = input("Please provide the id of the book you want to delete: ")
        try:
            id = int(id)
            deleted_book = self.__book_service.delete_book(id)
            print('\nThe book ' + str(deleted_book) + ' was deleted successfully.')
        except ValueError:
            print("\nId should be a number.")
        except RepositoryError as e:
            print("\nERROR: " + str(e))
        print("")

    def update_book_ui(self):
        id = input("Please provide the id of the book you want to update: ")
        title = input("Enter the book title: ")
        author = input("Enter the book author: ")
        try:
            id = int(id)
            self.__book_service.update_book(id, title, author)
            print("\nThe book was updated successfully.")
        except Exception as e:
            print("\nERROR: " + str(e))
        print("")

    def add_client_ui(self):
        print('Please provide client information')
        id = input('Client id: ')
        name = input('Client name: ')
        try:
            id = int(id)
            self.__client_service.add_client(id, name)
            print('\nThe client was added successfully.')
        except Exception as e:
            print("\nERROR: " + str(e))
        print("")

    def delete_client_ui(self):
        id = input('Please provide the id of the client you want to delete: ')
        try:
            id = int(id)
            deleted_client = self.__client_service.delete_client(id)
            print('\nThe client ' + str(deleted_client) + ' was deleted successfully.')
        except Exception as e:
            print("\nERROR: " + str(e))
        print("")

    def update_client_ui(self):
        id = input("Please provide the id of the client you want to update: ")
        name = input("Enter a name for the client: ")
        try:
            id = int(id)
            self.__client_service.update_client(id, name)
            print("\nThe client was updated successfully.")
        except Exception as e:
            print("\nERROR: " + str(e))
        print("")

    def rental_ui(self):
        print("Please provide the rental information")
        id_rental = input("Rental id: ")
        id_client = input("Client id: ")
        id_book = input("Book id: ")
        rented_date = input("Please provide the rented date: ")
        try:
            id_rental = int(id_rental)
            id_book = int(id_book)
            id_client = int(id_client)
            self.__rental_service.rent_book(id_rental, id_client, id_book, rented_date)
            print("\nThe rental was added successfully.")
        except Exception as e:
            print("\nERROR: " + str(e))
        print("")

    def return_rental_ui(self):
        print("Return a book back to the library")
        id_rental = input("Rental id: ")
        id_book = input("Book id: ")
        returned_date = input("Please provide the returned date: ")
        try:
            id_rental = int(id_rental)
            id_book = int(id_book)
            self.__rental_service.return_book(id_rental, id_book, returned_date)
            print("\nThe book was returned successfully.")
        except Exception as e:
            print("\nERROR: " + str(e))
        print("")

    def search_client_ui(self):
        print("Search for clients")
        text = input("Enter the text you want to search for: ")
        if self.__client_service.search_client(text) is not None:
            self.print_entity_list(self.__client_service.search_client(text))
        else:
            print(f"No clients were found that contain the text {text}.\n")

    def search_book_ui(self):
        print("Search for books")
        text = input("Enter the text you want to search for: ")
        if self.__book_service.search_book(text) is not None:
            self.print_entity_list(self.__book_service.search_book(text))
        else:
            print(f"No books were found that contain the text {text}.\n")

    def most_rented_books_ui(self):
        print("Most rented books")
        most_rented_books, books_appearances = self.__rental_service.most_rented_books()
        print("")
        for book in most_rented_books:
            print(book)
            print(f"- number of rentals: {books_appearances[book.id]}")
        print("")

    def most_active_clients_ui(self):
        print("Most active clients")
        most_active_clients, clients_appearances = self.__rental_service.most_active_clients()
        print("")
        for client in most_active_clients:
            print(client)
            print(f"- number of rentals: {clients_appearances[client.id]}")
        print("")

    def most_rented_author_ui(self):
        print("Most rented author")
        most_rented_authors, authors_appearances = self.__rental_service.most_rented_authors()
        print("")
        for book in most_rented_authors:
            print(book.author)
            print(f"- number of rentals: {authors_appearances[book.author]}")
        print("")

    def undo_ui(self):
        print("")
        try:
            self.__undo_service.undo()
            print("Undo was successful.")
        except Exception as e:
            print(str(e))
        print("")

    def redo_ui(self):
        print("")
        try:
            self.__undo_service.redo()
            print("Redo was successful.")
        except Exception as e:
            print(str(e))
        print("")

    def add_generated_clients_ui(self):
        self.__client_service.add_generated_clients()

    def add_generated_books_ui(self):
        self.__book_service.add_generated_books()

    def add_generated_rentals_ui(self):
        self.__rental_service.add_generated_rentals()

    def run_program(self):
        manage_clients_and_books = 1
        rent_or_return_book = 2
        search_clients_and_books = 3
        create_statistics = 4
        exit_the_program = 6
        add_client = 1
        add_book = 2
        remove_client = 3
        remove_book = 4
        update_client = 5
        update_book = 6
        list_client = 7
        list_book = 8
        rent_a_book = 1
        return_a_book = 2
        list_rentals = 3
        search_clients = 1
        search_books = 2
        most_rented_books = 1
        most_active_clients = 2
        most_rented_author = 3
        undo_redo = 5
        undo = 1
        redo = 2

        self.add_generated_books_ui()
        self.add_generated_clients_ui()
        self.add_generated_rentals_ui()

        print("Library main menu\n")

        while True:
            self.__print_main_menu()
            option = int(input("\nEnter an option from the menu: "))

            if option == manage_clients_and_books:
                print("\nManage clients and books\n")
                self.__print_submenu_1()
                sub_option = int(input("\nEnter an option from the submenu: "))

                if sub_option == add_client:
                    self.add_client_ui()
                elif sub_option == add_book:
                    self.add_book_ui()
                elif sub_option == remove_client:
                    self.delete_client_ui()
                elif sub_option == remove_book:
                    self.delete_book_ui()
                elif sub_option == update_client:
                    self.update_client_ui()
                elif sub_option == update_book:
                    self.update_book_ui()
                elif sub_option == list_client:
                    print("\nThe library currently has the following clients:")
                    self.print_entity_list(self.__client_service.get_all_clients())
                elif sub_option == list_book:
                    print("\nThe library currently holds the following books:")
                    self.print_entity_list(self.__book_service.get_all_books())
                else:
                    print("Invalid option. Please enter a number between 1 and 8.")

            elif option == rent_or_return_book:
                print("\nRent or return a book\n")
                self.__print_submenu_2()
                sub_option = int(input("\nEnter an option from the submenu: "))

                if sub_option == rent_a_book:
                    self.rental_ui()
                elif sub_option == return_a_book:
                    self.return_rental_ui()
                elif sub_option == list_rentals:
                    print("\nThe library currently has the following rentals:")
                    self.print_entity_list(self.__rental_service.get_all_rentals())
                else:
                    print("Invalid option. Please enter a number between 1 and 3.")

            elif option == search_clients_and_books:
                print("\nSearch for clients or books\n")
                self.__print_submenu_3()
                sub_option = int(input("\nEnter an option from the submenu: "))

                if sub_option == search_clients:
                    self.search_client_ui()
                elif sub_option == search_books:
                    self.search_book_ui()
                else:
                    print("Invalid option. Please enter a number between 1 and 2.")

            elif option == create_statistics:
                print("\nCreate statistics\n")
                self.__print_submenu_4()
                sub_option = int(input("\nEnter an option from the submenu: "))

                if sub_option == most_rented_books:
                    self.most_rented_books_ui()
                elif sub_option == most_active_clients:
                    self.most_active_clients_ui()
                elif sub_option == most_rented_author:
                    self.most_rented_author_ui()
                else:
                    print("Invalid option. Please enter a number between 1 and 3.")

            elif option == undo_redo:
                print("\nUndo and Redo\n")
                print("1 ~ Undo")
                print("2 ~ Redo")
                sub_option = int(input("\nEnter an option from the submenu: "))

                if sub_option == undo:
                    self.undo_ui()
                elif sub_option == redo:
                    self.redo_ui()
                else:
                    print("Invalid option. Please enter a number between 1 and 2.")

            elif option == exit_the_program:
                print('You exited the program, thank you!')
                exit()

            else:
                print("Invalid option. Please enter a number between 1 and 6.")

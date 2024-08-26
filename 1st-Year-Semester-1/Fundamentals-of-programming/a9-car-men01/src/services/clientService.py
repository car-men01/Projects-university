import random
from src.domain.client import Client
from src.services.undoService import Command, Operation

class ClientService:
    def __init__(self, repository, undo_service, rental_service):
        self.__repository = repository
        self.__undo_service = undo_service
        self.__rental_service = rental_service

    def save_client_file(self):
        try:
            self.__repository.save_file()
        except:
            pass

    def add_client(self, id: int, name: str):
        """
        Add a client
        """
        client = Client(id, name)
        self.__repository.add(client)
        undo_command = Command(self.delete_client, id)
        redo_command = Command(self.add_client, id, client.name)
        operation = Operation(undo_command, redo_command)
        self.__undo_service.record_for_undo(operation)
        self.save_client_file()

    def delete_client(self, id: int):
        """
        Delete a client with given id
        """
        deleted_client = self.__repository.remove(id)
        undo_command = Command(self.add_client, deleted_client.id, deleted_client.name)
        redo_command = Command(self.delete_client, id)
        client_operation = Operation(undo_command, redo_command)
        self.__undo_service.record_for_undo(client_operation)

        rentals = self.__rental_service.filter_rentals(deleted_client, None)
        for rental in rentals:
            self.__rental_service.delete_rental(rental.id)
        self.save_client_file()
        return deleted_client

    def update_client(self, id: int, name: str):
        """
        Updates a client`s data
        """
        client = self.__repository.get(id)
        undo_action = Command(self.update_client, id, client.name)
        redo_action = Command(self.update_client, id, name)
        operation = Operation(undo_action, redo_action)
        self.__undo_service.record_for_undo(operation)
        self.__repository.update(Client(id, name))
        self.save_client_file()

    def search_client(self, text):
        """
        Searches for clients that contain the given text in their id or name
        """
        matching_clients = {}
        for client in self.__repository.get_all():
            if text.lower() in str(client.id) or text.lower() in client.name.lower():
                matching_clients[client.id] = client

        if matching_clients:
            return list(matching_clients.values())
        else:
            return None

    def get_all_clients(self) -> list:
        return self.__repository.get_all()

    def add_generated_clients(self):
        id = list(range(1, 100))
        random.shuffle(id)
        for i in range(20):
            name_list = ["Razvan Miclea", "Bogdan Chirita", "Ana Dumitrescu", "Mike Pop", "Marius Matache",
                         "Alexandra Moisescu", "Ionut Petrescu", "Maria Sava", "Cristiana Dragomir",
                         "Paul Moldovan", "Serban Stoica", "Vlad Vladimir", "David Marcel", "Ana Floarea",
                         "Luca Istrate", "Isabela Mira", "Andrei Popescu", "Eliza Tudorescu", "Daniela Lucia",
                         "Ioana Petrache"]
            self.add_client(id[i], name_list[i])
        self.save_client_file()

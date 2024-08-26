import random
from src.domain.client import Client

class ClientService:
    def __init__(self, repository):
        self.__repository = repository

    def add_client(self, id: int, name: str):
        """
        Add a client
        """
        client = Client(id, name)
        self.__repository.add(client)

    def delete_client(self, id: int):
        """
        Delete a client with given id
        """
        return self.__repository.remove(id)

    def update_client(self, id: int, name: str):
        """
        Updates a client`s data
        """
        self.__repository.update(Client(id, name))

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

from src.domain.client import Client
from src.repository.errorRepository import DuplicateIdError, ClientDoesNotExistError

class ClientRepositoryMemory:
    def __init__(self):
        self.__clients = {}

    def add(self, client: Client):
        """
        Add a client to repository
        """
        if client.id in self.__clients:
            raise DuplicateIdError()
        self.__clients[client.id] = client

    def remove(self, id: int):
        """
        Remove client with given id
        """
        if id not in self.__clients:
            raise ClientDoesNotExistError()
        deleted_client = self.__clients[id]
        del self.__clients[id]
        return deleted_client

    def update(self, updated_client: Client):
        """
        Update the client given as parameter. The provided client replaces the one having the same id
        """
        client = self.get(updated_client.id)
        if client is None:
            raise ClientDoesNotExistError()

        self.__clients[client.id] = updated_client

    def get(self, client_id: int):
        """
        Find client with the given id
        """
        # if id in self.__clients:
        #     return self.__clients[id]
        for client in self.__clients.values():
            if client_id == client.id:
                return client
        # raise ClientDoesNotExistError()
        return None

    def get_all(self):
        """
        Return all clients in repository
        """
        return list(self.__clients.values())

    def get_all_id(self):
        return [client.id for client in self.__clients.values()]

    def __len__(self):
        """
        Return number of clients in repository
        """
        return len(self.__clients)

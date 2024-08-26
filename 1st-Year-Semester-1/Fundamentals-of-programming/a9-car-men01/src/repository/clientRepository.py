from src.domain.client import Client
from src.repository.errorRepository import DuplicateIdError, ClientDoesNotExistError
import pickle

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
        for client in self.__clients.values():
            if client_id == client.id:
                return client
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

class ClientRepositoryText(ClientRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            file = open(self.__filename, mode='r')
            client_list = {}
            lines = file.readlines()
            for line in lines:
                elements = line.split(',')
                elements = [element.strip() for element in elements]
                id = int(elements[0])
                name = elements[1]
                client = Client(id, name)
                client_list[client.id] = client
            file.close()
            return client_list
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, mode='w') as file:
            for client in self.get_all():
                client_elements = [client.id, client.name]
                client_elements = [str(element) for element in client_elements]
                line = ', '.join(client_elements) + '\n'
                file.write(line)

class ClientRepositoryBinary(ClientRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            with open(self.__filename, 'rb') as file:
                while True:
                    clients = pickle.load(file)
                    self.add(clients)
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, 'wb') as file:
            for client in self.get_all():
                pickle.dump(client, file)

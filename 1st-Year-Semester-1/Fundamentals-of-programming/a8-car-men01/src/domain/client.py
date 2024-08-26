class Client:
    def __init__(self, id: int, name: str):
        self.__id = id
        self.__name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @id.setter
    def id(self, new_id):
        self.__id = new_id

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    def __str__(self):
        return "Client id " + str(self.id) + ", client name " + self.name

    def __eq__(self, other):
        if not isinstance(other, Client):
            return False
        return self.id == other.id

class Student:
    def __init__(self, id: int, name: str, group: int):
        self._id = id
        self._name = name
        self._group = group

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def group(self):
        return self._group

    @id.setter
    def id(self, new_id: int):
        self._id = new_id

    @name.setter
    def name(self, new_name: str):
        self._name = new_name

    @group.setter
    def group(self, new_group: int):
        self._group = new_group

    def __str__(self):
        return "Id " + str(self.id) + ", student name " + self._name + ", group " + str(self._group)

    def __eq__(self, other):
        if not isinstance(other, Student):
            return False
        return self._id == other.id

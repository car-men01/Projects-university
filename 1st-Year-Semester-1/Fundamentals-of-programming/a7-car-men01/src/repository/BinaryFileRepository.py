import pickle
from src.repository.MemoryRepository import StudentRepositoryMemory


class StudentRepositoryBinary(StudentRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            with open(self.__filename, 'rb') as file:
                while True:
                    students = pickle.load(file)
                    self.add(students)
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, 'wb') as file:
            for student in self.get_all():
                pickle.dump(student, file)

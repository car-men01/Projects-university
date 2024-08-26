"""
1. Add a student. Student data is read from the console.
2. Display the list of students.
3. Filter the list so that students in a given group (read from the console) are deleted from the list.
4. Undo the last operation that modified program data. This step can be repeated. The user can undo only 
those operations made during the current run of the program.
"""

import random
import copy
from src.domain.student import Student


class StudentService:
    def __init__(self, repository):
        self.__repository = repository
        self.__history = []

    def add_student(self, id: int, name: str, group: int):
        self.__history.append(copy.deepcopy(self.__repository.get_all_dictionary()))
        student = Student(id, name, group)
        self.__repository.add(student)
        try:
            self.__repository.save_file()
        except:
            pass

    def delete_student(self, id: int):
        deleted_student = self.__repository.remove(id)
        try:
            self.__repository.save_file()
        except:
            pass
        return deleted_student

    def filter_by_group(self, group: int):
        """
        Deletes students from a given group
        """
        self.__history.append(copy.deepcopy(self.__repository.get_all_dictionary()))
        for student in self.__repository.get_all():
            if group == student.group:
                self.__repository.remove(student.id)
        try:
            self.__repository.save_file()
        except:
            pass

    def get_all_students(self) -> list:
        return self.__repository.get_all()

    def add_generated_students(self):
        id = list(range(1, 100))
        random.shuffle(id)  # for unique id

        for i in range(10):
            group = random.randint(100, 110)
            name_list = ["Razvan Miclea", "Bogdan Chirita", "Ana Dumitrescu", "Mike Pop", "Marius Matache",
                         "Alexandra Moisescu", "Ionut Petrescu", "Maria Sava", "Cristiana Dragomir",
                         "Paul Moldovan"]
            student = Student(id[i], name_list[i], group)
            self.__repository.add(student)

        self.__history.append(copy.deepcopy(self.__repository.get_all_dictionary()))
        try:
            self.__repository.save_file()
        except:
            pass

    def undo(self):
        if len(self.__history) > 1:
            self.__repository.undo(self.__history[-1])
            self.__history.pop()
            try:
                self.__repository.save_file()
            except:
                pass
        elif len(self.__history) == 1:
            self.__history.pop()
            self.__history.pop()

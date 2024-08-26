from src.domain.student import Student

class RepositoryError(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message

    def __str__(self):
        return "Repository error: " + str(self.message)


class StudentRepositoryMemory:
    def __init__(self):
        # students are stored in this dictionary, keys are ids
        self.__student_list = {}

    def add(self, student):
        """
        Add a new student to the repo
        Raise RepositoryError if student with id already in repository
        """
        if student.id in self.__student_list:
            raise RepositoryError(f"A student with id {student.id} already exists")
        self.__student_list[student.id] = student

    def remove(self, id: int) -> Student:
        """
        Remove the student from repository
        Raise RepositoryError if student not in repository
        """
        if id in self.__student_list:
            deleted_student = self.__student_list[id]
            del self.__student_list[id]
            return deleted_student
        else:
            raise RepositoryError("The student does not exist.")

    def undo(self, last_history_dictionary: dict):
        """
        Undo the last operation
        """
        self.__student_list = last_history_dictionary

    def get_all(self) -> list:
        """
        Returns all students in repository
        """
        return list(self.__student_list.values())

    def get_all_dictionary(self) -> dict:
        """
        Returns all students in repository as a dictionary
        """
        return self.__student_list

    def __len__(self):
        """
        Return number of students in repository
        """
        return len(self.__student_list)

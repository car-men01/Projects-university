from src.domain.student import Student
from src.repository.MemoryRepository import StudentRepositoryMemory


class StudentRepositoryText(StudentRepositoryMemory):
    def __init__(self, filename):
        super().__init__()
        self.__filename = filename

    def load_file(self):
        try:
            file = open(self.__filename, mode='r')
            student_list = {}
            lines = file.readlines()
            for line in lines:
                elements = line.split(',')
                elements = [element.strip() for element in elements]
                id = int(elements[0])
                name = elements[1]
                group = int(elements[2])
                student = Student(id, name, group)
                student_list[student.id] = student
            file.close()
            return student_list
        except EOFError:
            pass
        except FileNotFoundError:
            pass

    def save_file(self):
        with open(self.__filename, mode='w') as file:
            for student in self.get_all():
                student_elements = [student.id, student.name, student.group]
                student_elements = [str(element) for element in student_elements]
                line = ', '.join(student_elements) + '\n'
                file.write(line)

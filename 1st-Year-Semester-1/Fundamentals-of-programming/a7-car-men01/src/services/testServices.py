from src.domain.student import Student
from src.services.studentServices import StudentService
from src.repository.MemoryRepository import StudentRepositoryMemory

def testRepository():
    test_repository = StudentRepositoryMemory()
    assert (test_repository.__len__() == 0)

    student1 = Student(10, "Andi Popescu", 100)
    student2 = Student(5, "Maria Scurtu", 110)
    student3 = Student(1, "Mihai Chirita", 105)

    test_repository.add(student1)
    test_repository.add(student2)
    test_repository.add(student3)

    assert (test_repository.__len__() == 3)


def testStudent():
    student = Student(1, "Mihai Chirita", 105)
    assert (student.name() == "Mihai Chirita")
    assert (student.group() == 105)
    student.group(900)
    assert (student.group() == 900)

    student1 = Student(10, "Andi Popescu", 100)
    student2 = Student(10, "Andi Popescu", 100)
    assert (student1 == student2)

    student1 = Student(10, "Andi Popescu", 100)
    student2 = Student(100, "Andi Popescu", 100)
    assert (student1 != student2)

def testService():
    test_repository = StudentRepositoryMemory()
    student_service = StudentService(test_repository)
    student_service.add_student(30, "Luca Moldo", 101)
    test_student_list = student_service.get_all_students()

    assert (len(test_student_list) == 1)

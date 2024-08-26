from src.repository.MemoryRepository import StudentRepositoryMemory
from src.repository.BinaryFileRepository import StudentRepositoryBinary
from src.repository.TextFileRepository import StudentRepositoryText
from src.services.studentServices import StudentService
from src.ui.UI import UI
import pathlib


"""
Memory Repository
"""

# repository = StudentRepositoryMemory()

"""
Text File Repository
"""

path = pathlib.Path(__file__).parent.parent.absolute().joinpath("students.txt")
repository = StudentRepositoryText(path)
repository.load_file()

"""
Binary File Repository
"""

# path = pathlib.Path(__file__).parent.parent.absolute().joinpath("students.bin")
# repository = StudentRepositoryBinary(path)
# repository.load_file()

controller = StudentService(repository)
console = UI(controller)
console.run_program()

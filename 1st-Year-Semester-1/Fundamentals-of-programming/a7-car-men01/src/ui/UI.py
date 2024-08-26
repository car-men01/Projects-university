class UI:
    def __init__(self, student_service):
        self.__student_service = student_service

    @staticmethod
    def __print_menu():
        menu_options = {
            1: 'Add a student to the list',
            2: 'Display the entire list of students',
            3: 'Delete the students from a given group',
            4: 'Undo the last operation',
            5: 'Exit the program'
        }
        for key in menu_options.keys():
            print(key, '~', menu_options[key])

    @staticmethod
    def print_student_list(student_list):
        print("")
        for student in student_list:
            print(student)
        print("")

    def delete_from_group_ui(self):
        group = input("Please type in the group from which you want the students to be deleted: ")
        print("")
        try:
            group = int(group)
            self.__student_service.filter_by_group(group)
            print(f"The students from group {group} were deleted successfully.")
        except ValueError as e:
            print("Error: " + str(e))
        print("")

    def add_student_ui(self):
        student_id = input("Student id: ")
        student_name = input("Student name: ")
        student_group = input("Student group: ")
        print("")
        try:
            student_id = int(student_id)
            student_group = int(student_group)
            self.__student_service.add_student(student_id, student_name, student_group)
            print("The student was added successfully.")
        except Exception as e:
            print("Error: " + str(e))
        print("")

    def undo_ui(self):
        print("")
        try:
            self.__student_service.undo()
            print("Undo last operation successful.")
        except Exception:
            print("There is nothing left to can undo.")
        print("")

    def add_generated_students_ui(self):
        self.__student_service.add_generated_students()

    def run_program(self):
        add_student = 1
        display_all_students = 2
        delete_students_from_given_group = 3
        undo_last_operation = 4
        exit_the_program = 5
        self.add_generated_students_ui()

        while True:
            self.__print_menu()
            option = int(input("\nEnter an option from the menu: "))

            if option == add_student:
                self.add_student_ui()

            elif option == display_all_students:
                self.print_student_list(self.__student_service.get_all_students())

            elif option == delete_students_from_given_group:
                self.delete_from_group_ui()

            elif option == undo_last_operation:
                self.undo_ui()

            elif option == exit_the_program:
                print('You exited the program, thank you!')
                exit()

            else:
                print('Invalid option, please enter a number between 1 and 5.')

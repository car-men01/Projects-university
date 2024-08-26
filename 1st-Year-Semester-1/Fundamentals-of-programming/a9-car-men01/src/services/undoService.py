from src.repository.errorRepository import RedoException, UndoException

class Command:
    def __init__(self, fn, *args):
        self._fn = fn
        self._fn_params = args

    def execute(self):
        """
        Executes the stored function together with its parameters
        """
        self._fn(*self._fn_params)

    def __str__(self):
        return "Function:" + str(self._fn) + " with parameters: " + str(self._fn_params)


class Operation:
    def __init__(self, undo_action: Command, redo_action: Command):
        self.__undo_action = undo_action
        self.__redo_action = redo_action

    def undo(self):
        """
        Executes the undo action of the Operation.
        """
        self.__undo_action.execute()

    def redo(self):
        """
        Executes the redo action of the Operation.
        """
        self.__redo_action.execute()

    def __str__(self):
        return "Operation:" + str(self.__undo_action) + " & " + str(self.__redo_action)


class UndoService:
    """
    Initializes an UndoService object.
    """
    def __init__(self):
        self.__undo_stack = []
        self.__redo_stack = []
        self.__is_undoredo_op = False

    def record_for_undo(self, operation: Operation):
        """
        Records an operation for undo/redo.
        """
        if self.__is_undoredo_op:
            return
        self.__undo_stack.append(operation)

    def undo(self):
        if len(self.__undo_stack) == 0:
            raise UndoException()
        self.__is_undoredo_op = True
        operation = self.__undo_stack.pop()
        operation.undo()
        self.__redo_stack.append(operation)
        self.__is_undoredo_op = False

    def redo(self):
        if len(self.__redo_stack) == 0:
            raise RedoException()
        self.__is_undoredo_op = True
        operation = self.__redo_stack.pop()
        operation.redo()
        self.__undo_stack.append(operation)
        self.__is_undoredo_op = False

    def __str__(self):
        op_str = 'UNDO stack\n'
        for nr_op, op in enumerate(self.__undo_stack):
            op_str += str(nr_op) + " "
            op_str += str(op)
            op_str += '\n'

        op_str += 'REDO stack\n'
        for nr_op, op in enumerate(self.__redo_stack):
            op_str += str(nr_op) + " "
            op_str += str(op)
            op_str += '\n'

        return op_str

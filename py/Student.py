class Student:
    def __init__(self):
        pass

    def __init__(self, number, name, grade):
        self.number = number
        self.name = name
        self.grade = grade

    def set_info(self, number, name, grade):
            self.number = number
            self.name = name
            self.grade = grade

    def print_info(self):
        print("-----------------")
        print("Number: ", self.number)
        print("Name: ", self.email)
        print("Grade: ", self.grade)
        print("-----------------")


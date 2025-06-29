class Note:
    def __init__(self, title, content):
        self.title = title
        self.content = content

    def __str__(self):
        return f"{self.title}: {self.content}"

class Notebook:
    def __init__(self):
        self.notes = []

    def get_num_notes(self):
        return len(self.notes)

    def add_note(self, title, content):
        self.notes.append(Note(title, content))

    # def __iter__(self):
    #     return self.notes.__iter__()


# 사용 예시
notebook = Notebook()
notebook.add_note("Shopping List", "Eggs, Milk, Bread")
notebook.add_note("Ideas", "Build a game with time travel.")
notebook.add_note("Todo", "Finish project by Friday.")

# notebook에는 list 객체가 하나 있고,
# list 객체 안에는 Note 객체(ShoppingList, Ideas, Todo)가 3개 있음.
print(notebook.notes[0])

for elem in notebook:
    print(elem)

# 1) for a in notebook 하면, 자동으로!!! notebook.__iter__()가 호출이 된다.
# 2)
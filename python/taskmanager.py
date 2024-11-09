import tkinter as tk
from tkinter import simpledialog
import json
import os

class ToDoApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("To-Do List Application")
        self.geometry("800x400")

        self.lists = {}
        self.completed_tasks = []
        self.filename = "todo_data.txt"

        self.frame = tk.Frame(self)
        self.frame.pack(pady=10, padx=10)

        self.add_task_button = tk.Button(self.frame, text="Add Task", command=self.add_task)
        self.add_task_button.pack(pady=5, padx=5, side="left")

        self.add_list_button = tk.Button(self.frame, text="Add New List", command=self.add_new_list)
        self.add_list_button.pack(pady=5, padx=5, side="left")

        self.delete_list_button = tk.Button(self.frame, text="Delete List", command=self.delete_list)
        self.delete_list_button.pack(pady=5, padx=5, side="left")

        self.show_completed_button = tk.Button(self.frame, text="Show Completed Tasks", command=self.show_completed_tasks)
        self.show_completed_button.pack(pady=5, padx=5, side="left")

        # Main frame as PanedWindow to allow resizing between lists
        self.paned_window = tk.PanedWindow(self, orient=tk.HORIZONTAL)
        self.paned_window.pack(fill='both', expand=True, padx=10, pady=10)

        self.list_frames = {}
        self.task_widgets = {}

        self.load_data()
        self.create_lists_display()

        self.protocol("WM_DELETE_WINDOW", self.on_closing)

    def create_lists_display(self):
        for list_name in self.lists:
            self.create_list_frame(list_name)

    def create_list_frame(self, list_name):
        num_lists = len(self.lists)
        
        # Each list gets its own Frame embedded inside the PanedWindow
        list_frame = tk.Frame(self.paned_window, bd=1, relief="solid", bg="white", width=int(780/num_lists), height=300)
        self.paned_window.add(list_frame, stretch="always")  # Add to the PanedWindow, making it resizable
        
        list_label = tk.Label(list_frame, text=list_name, bg="white")
        list_label.pack(pady=5)

        self.list_frames[list_name] = list_frame

        for task, status in self.lists[list_name]:
            self.add_task_widget(list_name, task, status)

    def add_task(self):
        task = simpledialog.askstring("Input", "Enter a task:")
        if task:
            if "Main List" not in self.lists:
                self.lists["Main List"] = []
            self.lists["Main List"].append((task, False))
            self.add_task_widget("Main List", task, False)
            self.save_data()

    def add_new_list(self):
        list_name = simpledialog.askstring("Input", "Enter new list name:")
        if list_name and list_name not in self.lists:
            self.lists[list_name] = []
            self.create_list_frame(list_name)
            self.save_data()

    def delete_list(self):
        list_name = simpledialog.askstring("Input", "Enter the list name to delete:")
        if list_name in self.lists and list_name != "Main List":
            del self.lists[list_name]
            self.list_frames[list_name].destroy()
            del self.list_frames[list_name]
            self.save_data()

    def add_task_widget(self, list_name, task, status):
        task_frame = tk.Frame(self.list_frames[list_name], bd=1, relief="raised", bg="white")
        task_frame.pack(fill="x", pady=5, padx=5)

        var = tk.BooleanVar(value=status)
        check_button = tk.Checkbutton(task_frame, text=task, variable=var, command=lambda t=task, ln=list_name: self.complete_task(t, ln, var.get()))
        check_button.pack(side="left", padx=10)

        move_button = tk.Button(task_frame, text="Move", command=lambda t=task, ln=list_name: self.move_task(t, ln))
        move_button.pack(side="right", padx=5)

        down_button = tk.Button(task_frame, text="Down", command=lambda t=task, ln=list_name: self.change_task_priority(t, ln, 1))
        down_button.pack(side="right", padx=5)

        up_button = tk.Button(task_frame, text="Up", command=lambda t=task, ln=list_name: self.change_task_priority(t, ln, -1))
        up_button.pack(side="right", padx=5)

        del_button = tk.Button(task_frame, text="Delete", command=lambda t=task, ln=list_name: self.delete_task(t, ln))
        del_button.pack(side="right", padx=5)

        self.task_widgets[(list_name, task)] = task_frame

    def change_task_priority(self, task, list_name, direction):
        tasks = self.lists[list_name]
        index = next(i for i, (t, _) in enumerate(tasks) if t == task)
        if direction == -1 and index > 0:
            tasks[index], tasks[index-1] = tasks[index-1], tasks[index]
            self.move_task_widget(list_name, index, index-1)
        elif direction == 1 and index < len(tasks) - 1:
            tasks[index], tasks[index+1] = tasks[index+1], tasks[index]
            self.move_task_widget(list_name, index, index+1)
        self.save_data()

    def move_task_widget(self, list_name, old_index, new_index):
        task_frames = self.list_frames[list_name].winfo_children()[1:]  # Skip the list label
        task_frame = task_frames.pop(old_index)
        task_frames.insert(new_index, task_frame)
        for i, frame in enumerate(task_frames, start=1):
            frame.pack_forget()
            frame.pack(fill="x", pady=5, padx=5)

    def move_task(self, task, current_list):
        new_list = simpledialog.askstring("Input", "Enter list name to move task:")
        if new_list in self.lists:
            if new_list != current_list:
                status = next(s for t, s in self.lists[current_list] if t == task)
                self.lists[current_list] = [(t, s) for t, s in self.lists[current_list] if t != task]
                self.lists[new_list].append((task, status))
                
                # Remove the task widget from the current list
                task_frame = self.task_widgets.pop((current_list, task))
                task_frame.destroy()
                
                # Add the task widget to the new list
                self.add_task_widget(new_list, task, status)
                self.save_data()
            else:
                tk.messagebox.showinfo("Info", "Task is already in this list.")
        else:
            tk.messagebox.showerror("Error", f"List '{new_list}' does not exist.")

    def delete_task(self, task, list_name):
        self.lists[list_name] = [(t, s) for t, s in self.lists[list_name] if t != task]
        self.task_widgets.pop((list_name, task)).destroy()
        self.save_data()

    def complete_task(self, task, list_name, is_completed):
        if is_completed:
            # Auto-delete the task from the current list
            self.lists[list_name] = [(t, s) for t, s in self.lists[list_name] if t != task]
            self.completed_tasks.append(task)
            self.task_widgets.pop((list_name, task)).destroy()
        else:
            self.completed_tasks.remove(task)
        self.save_data()

    def show_completed_tasks(self):
        # Create a Toplevel window to display completed tasks without alert sound
        completed_window = tk.Toplevel(self)
        completed_window.title("Completed Tasks")
        completed_window.geometry("300x300")
        
        completed_label = tk.Label(completed_window, text="Completed Tasks", font=("Arial", 14))
        completed_label.pack(pady=10)

        completed_tasks_str = "\n".join(self.completed_tasks) if self.completed_tasks else "No tasks completed yet."
        completed_tasks_label = tk.Label(completed_window, text=completed_tasks_str, justify="left")
        completed_tasks_label.pack(pady=10, padx=10)

    def save_data(self):
        with open(self.filename, 'w') as f:
            json.dump({"lists": self.lists, "completed_tasks": self.completed_tasks}, f)

    def load_data(self):
        if os.path.exists(self.filename):
            with open(self.filename, 'r') as f:
                data = json.load(f)
                self.lists = data.get("lists", {"Main List": []})
                self.completed_tasks = data.get("completed_tasks", [])
        else:
            self.lists = {"Main List": []}
            self.completed_tasks = []

    def on_closing(self):
        self.save_data()
        self.destroy()

if __name__ == "__main__":
    app = ToDoApp()
    app.mainloop()

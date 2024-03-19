#include <iostream>
#include <vector>
#include <fstream>
#include <string> // Include string header for C++98 mode compatibility

using namespace std;

struct Task
{
    string description;
    bool completed;
};

void displayTasks(const vector<Task> &tasks)
{
    cout << "Task List:\n";
    for (size_t i = 0; i < tasks.size(); ++i)
    {
        cout << "[" << i + 1 << "] ";
        cout << (tasks[i].completed ? "[Completed] " : "[Pending] ");
        cout << tasks[i].description << "\n";
    }
}

void addTask(vector<Task> &tasks, const string &description)
{
    Task newTask = {description, false};
    tasks.push_back(newTask);
}

void editTask(vector<Task> &tasks, size_t taskIndex, const string &newDescription)
{
    if (taskIndex < tasks.size())
    {
        tasks[taskIndex].description = newDescription;
    }
    else
    {
        cout << "Invalid task index.\n";
    }
}

void completeTask(vector<Task> &tasks, size_t taskIndex)
{
    if (taskIndex < tasks.size())
    {
        tasks[taskIndex].completed = true;
    }
    else
    {
        cout << "Invalid task index.\n";
    }
}

void saveTasks(const vector<Task> &tasks, const string &filename)
{
    ofstream file(filename.c_str());
    if (file.is_open())
    {
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            file << tasks[i].completed << " " << tasks[i].description << "\n";
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to save tasks to file.\n";
    }
}

void loadTasks(vector<Task> &tasks, const string &filename)
{
    ifstream file(filename.c_str());
    if (file.is_open())
    {
        tasks.clear();
        while (!file.eof())
        {
            Task task;
            file >> std::boolalpha >> task.completed;
            file.ignore(); // Ignore the space after bool
            getline(file, task.description);
            tasks.push_back(task);
        }
        file.close();
    }
    else
    {
        cout << "Error: Unable to load tasks from file.\n";
    }
}

int main()
{
    vector<Task> tasks;
    string filename = "task_history.txt";
    loadTasks(tasks, filename);
    while (true)
    {
        cout << "\nOptions:\n";
        cout << "1. Display Tasks\n";
        cout << "2. Add Task\n";
        cout << "3. Edit Task\n";
        cout << "4. Complete Task\n";
        cout << "5. Save and Quit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            displayTasks(tasks);
            break;
        case 2:
        {
            string description;
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, description);
            addTask(tasks, description);
            break;
        }
        case 3:
        {
            size_t taskIndex;
            string newDescription;
            cout << "Enter task index to edit: ";
            cin >> taskIndex;
            cout << "Enter new task description: ";
            cin.ignore();
            getline(cin, newDescription);
            editTask(tasks, taskIndex - 1, newDescription);
            break;
        }
        case 4:
        {
            size_t taskIndex;
            cout << "Enter task index to mark as completed: ";
            cin >> taskIndex;
            completeTask(tasks, taskIndex - 1);
            break;
        }
        case 5:
            saveTasks(tasks, filename);
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

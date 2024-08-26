#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <map>
#include <functional>

std::vector<std::string> Load(const std::string& f) {
    std::ifstream file(f);
    std::vector<std::string> tasks;
    tasks.reserve(100);
    std::string t;
    while (std::getline(file, t)) {
        tasks.push_back(std::move(t));
    }
    return tasks;
}

void Save(const std::string& f, const std::vector<std::string>& t) {
    std::ofstream file(f, std::ios::trunc);
    for (const auto& task : t) {
        file << task << '\n';
    }
}

void Add(std::vector<std::string>& t) {
    std::cout << "Enter task description: ";
    std::string task;
    std::getline(std::cin, task);
    t.push_back(std::move(task));
    std::cout << "\nTask added.\n";
}

void Del(std::vector<std::string>& t) {
    std::cout << "Enter task number to delete: ";
    size_t idx;
    if (std::cin >> idx && idx > 0 && idx <= t.size()) {
        t.erase(t.begin() + idx - 1);
        std::cout << "\nTask deleted.\n";
    } else {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInvalid number. Try again.\n";
    }
}

void List(const std::vector<std::string>& t) {
    if (t.empty()) {
        std::cout << "\nNo tasks to list.\n";
    } else {
        std::cout << "\nCurrent tasks:\n";
        for (size_t i = 0; i < t.size(); ++i) {
            std::cout << "  " << i + 1 << ". " << t[i] << '\n';
        }
    }
    std::cout << '\n';
}

void Show() {
    std::cout << "\nChoose an option:\n";
    std::cout << "1. Add a task\n";
    std::cout << "2. Delete a task\n";
    std::cout << "3. List all tasks\n";
    std::cout << "4. Exit\n";
    std::cout << '\n';
}

int main() {
    const std::string file = "tasks.txt";
    auto tasks = Load(file);
    std::map<int, std::function<void()>> opts = {
        {1, [&]() { Add(tasks); Save(file, tasks); }},
        {2, [&]() { Del(tasks); Save(file, tasks); }},
        {3, [&]() { List(tasks); }},
        {4, [&]() { Save(file, tasks); std::cout << "\nExiting...\n"; exit(0); }}
    };
    int opt;
    while (true) {
        Show();
        if (!(std::cin >> opt) || opts.find(opt) == opts.end()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid option. Try again.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        opts[opt]();
    }
}

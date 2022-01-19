#include <iostream>
#include <vector>
#include <cstdlib>

enum Task
{
    NONE,
    A,
    B,
    C
};

class Worker
{
private:
    Task task;
    bool isBusy;

public:
    Worker(Task inTask = NONE, bool inIsBusy = false) :
            task(inTask), isBusy(inIsBusy){}

    std::string getNameTask() {
        if (task == A) return "A";
        else if (task == B) return "B";
        else if (task == C) return "C";
        else return "NONE";
    }

    void setNameTask(const Task &inName) {
        task = inName;
    }

    bool getIsBusy() const {
        return isBusy;
    }

    void setIsBusy(bool inIsBusy) {
        isBusy = inIsBusy;
    }
};

class Manager : public Worker
{
private:
    std::vector<Worker*> workers;

public:
    Manager(){}
    Manager (const int &employees) : Worker()
    {
        for (int i = 0; i < employees; ++i)
        {
            Worker *worker = new Worker;
            workers.push_back(worker);
        }
    }

    std::vector<Worker*> getWorker()
    {
        return workers;
    }

    int workersSize()
    {
        return workers.size();
    }
};

class Chief : public Manager
{
private:
    std::vector<Manager*> managers;
    static int counterTeam;

public:
    Chief(int numberTeams) : Manager()
    {
        for (int i = 0; i < numberTeams; ++i)
        {
            std::cout << "Enter the number of employees in each team.";
            int employees;
            std::cout << "Enter the number of employees in # " << counterTeam << " team: ";
            ++counterTeam;
            std::cin >> employees;
            Manager* manager = new Manager(employees);
            managers.push_back(manager);
        }
    }

    bool performTask(int mainTask);// постановка задач свободным работникам
    void printWorkers();// для проверки выводит всех работников на экран
};

int Chief::counterTeam = 1;

bool Chief::performTask(int mainTask)
{
    bool allWorkersIsBusy{true};
    for (int i = 0; i < managers.size(); ++i){
        srand(mainTask + i);
        int numberTasks = rand() % (managers[i]->workersSize()) + 1;
        for (int j = 0; j < managers[i]->workersSize() && numberTasks > 0; ++j){
            Task typeTask = static_cast<Task>(rand() % 3 + 1);
            if (!(managers[i]->getWorker()[j]->getIsBusy())) {
                managers[i]->getWorker()[j]->setNameTask(typeTask);
                managers[i]->getWorker()[j]->setIsBusy(true);
                --numberTasks;
                allWorkersIsBusy = false;
            }
        }
    }
    return allWorkersIsBusy;
}
void Chief::printWorkers() {
    for (int i = 0; i < managers.size(); ++i) {
        for (int j = 0; j < managers[i]->workersSize(); ++j) {
            std::cout << "Team #" << i + 1 << " Worker #" << j + 1 << " " <<
                      managers[i]->getWorker()[j]->getNameTask() << " * " <<
                      managers[i]->getWorker()[j]->getIsBusy() << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
}

int main() {
    std::cout << "Enter the number of teams: ";
    int numberTeams;
    std::cin >> numberTeams;
    Chief chief(numberTeams);

    while (true) {
        chief.printWorkers();
        std::cout << "Please enter an integer identifier of the task: ";
        int identifier;
        std::cin >> identifier;
        if (chief.performTask(identifier)){
            std::cout << "All workers are busy!!!" << std::endl;
            return 0;
        }
    }
}

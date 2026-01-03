#include <iostream>
#include <functional>
#include <string>
#include <vector>

//测试bind 各种用法

using namespace std;
using namespace std::placeholders; // 对于 _1, _2, ...

class Worker {
private:
    string workerName;

public:
    Worker(const string& name) : workerName(name) {}

    void doTask(const string& task) {
        cout << workerName << " is doing task: " << task << endl;
    }

    int calculate(int x, int y) {
        int result = x + y;
        cout << workerName << " calculated: " << x << " + " << y
             << " = " << result << endl;
        return result;
    }

    void showInfo(int id) {
        cout << "Worker " << workerName << " has ID: " << id << endl;
    }
};

class TaskManager {
private:
    //function<void()> 可以接受bind之后带任意参数或者返回值的函数，不需要声明匹配为不带参数和返回值
    vector<function<void()>> tasks;

public:
    // 添加任务（使用std::function包装成员函数）
    void addTask(function<void()> task) {
        tasks.push_back(task);
    }

    // 执行所有任务
    void runAll() {
        cout << "Running " << tasks.size() << " tasks:" << endl;
        for (auto& task : tasks) {
            task();
        }
    }

    // 接收带参数的成员函数
    void schedule(function<int()> task) {
        cout << "Scheduled task result: " << task() << endl;
    }
};

int main() {
    Worker alice("Alice");
    Worker bob("Bob");
    TaskManager manager;

    // 方法1：使用std::bind绑定对象和成员函数
    // 语法：std::bind(&类名::成员函数, &对象, 参数占位符...)

    manager.addTask(bind(&Worker::doTask, &alice, "Clean the room"));
    manager.addTask(bind(&Worker::doTask, &bob, "Write report"));
    manager.addTask(bind(&Worker::showInfo, &alice, 101));
    manager.addTask([=](){
        cout<< "lamdba express"<<endl;
    });

    // 使用占位符（延迟参数绑定）
    function<int(int, int)> calcFunc1 = bind(&Worker::calculate, &alice, _1, _2);
    cout << "Bound function result: " << calcFunc1(5, 3) << endl;

    // 预绑定部分参数
    function<int()> calcFunc2 = bind(&Worker::calculate, &bob, 10, 20);
    manager.schedule(calcFunc2);

    // 执行所有任务
    manager.runAll();

    return 0;
}

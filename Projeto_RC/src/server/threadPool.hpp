#ifndef SERVER_THREADPOOL_HPP
#define SERVER_THREADPOOL_HPP

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

#include "./commands/command.hpp"

using namespace std;

class ThreadPool {
public:
    ThreadPool();
    ~ThreadPool();

    void enqueue(Command* command);

private:
    int n_threads;
    mutex mutex_q;
    condition_variable condition;
    vector<thread> workers;
    queue<Command*> commands;
};

#endif
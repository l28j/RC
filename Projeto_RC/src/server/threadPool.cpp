#include "threadPool.hpp"

ThreadPool::ThreadPool(){
    this->threadsNumber = thread::hardware_concurrency();

    for(int i = 0; i < this->threadsNumber; i++){
        // emplace_back() constructs the thread in-place
        this->workers.emplace_back(
            [this](){
                while(true){
                    Command* command;
                    {
                        unique_lock<mutex> lock(this->queue_mutex);

                        // wait until lock is acquired and queue is not empty
                        this->condition.wait(lock, [this](){
                            // only moves if this condition is true
                            return !this->commands.empty();
                        });

                        // returns first element of queue
                        command = this->commands.front();
                        // removes first element of queue
                        this->commands.pop();

                        // nullptr is used to stop threads
                        if(command == nullptr){
                            break;
                        }
                    } // lock is released here

                    command->execute();
                }
            }
        );
    }
}

ThreadPool::~ThreadPool(){
    for(int i = 0; i < this->threadsNumber; i++){
        // enqueue nullptr to stop threads
        this->enqueue(nullptr);
    }

    for(int i = 0; i < this->threadsNumber; i++){
        // wait for all threads to finish
        if(this->workers[i].joinable()) this->workers[i].join();
    }
}

void ThreadPool::enqueue(Command* command){
    {
        unique_lock<mutex> lock(queue_mutex);
        commands.push(command);
    } // lock is released here

    // notify one thread that there is a new command
    // notify_all() would wake up all threads, but only one is needed
    condition.notify_one();
}
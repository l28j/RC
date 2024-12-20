#include "threadPool.hpp"


void ThreadPool::enqueue(Command* command){
    {
        unique_lock<mutex> lock(mutex_q);
        commands.push(command);
    } // lock is released here

    // notify one thread that there is a new command
    // notify_all() would wake up all threads, but only one is needed
    condition.notify_one();
}

ThreadPool::~ThreadPool(){
    int j=0;
    for(j = 0; j < this->n_threads; j++){
        // enqueue nullptr to stop threads
        this->enqueue(nullptr);
    }

    for(j = 0; j < this->n_threads; j++){
        // wait for all threads to finish
        if(this->workers[j].joinable()) this->workers[j].join();
    }
}
ThreadPool::ThreadPool(){
    this->n_threads = thread::hardware_concurrency();

    int j=0;
    for(j = 0; j < this->n_threads; j++){
        // emplace_back() constructs the thread in-place
        this->workers.emplace_back(
            [this](){
                while(true){
                    Command* command;
                    {
                        unique_lock<mutex> lock(this->mutex_q);

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

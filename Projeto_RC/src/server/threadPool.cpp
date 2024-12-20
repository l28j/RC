#include "threadPool.hpp"
ThreadPool::ThreadPool() {
    this->threadsNumber = thread::hardware_concurrency();

    for (int i = 0; i < this->threadsNumber; i++) {
        this->workers.emplace_back(
            [this]() {
                while (true) {
                    std::unique_ptr<Command> command;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);

                        this->condition.wait(lock, [this]() {
                            return !this->commands.empty();
                        });

                        command = std::move(this->commands.front());
                        this->commands.pop();

                        if (!command) {
                            break;
                        }
                    }

                    command->execute(); // Executa o comando
                }
            }
        );
    }
}


ThreadPool::~ThreadPool() {
    for (int i = 0; i < this->threadsNumber; i++) {
        // Enfileira nullptr (smart pointer vazio) para sinalizar o término
        this->enqueue(nullptr);
    }

    for (auto& worker : this->workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}


void ThreadPool::enqueue(std::unique_ptr<Command> command) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        commands.push(std::move(command)); // Mover para a fila
    }

    condition.notify_one(); // Notificar uma thread
}

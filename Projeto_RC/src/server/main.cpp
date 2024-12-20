#include "main.hpp"

// Function to run the UDP monitor, handling incoming UDP requests.
void runUdpMonitor(ThreadPool* threadPool, int port, bool verbose) {
    printf("Starting udp monitor on port %d %s verbose mode\n", port, verbose ? "with" : "without");
    UdpSocket udpMonitor = UdpSocket(port, verbose); // Initialize the UDP monitor socket.

    while (true) {
        // Receive data from the UDP socket.
        string receivedData = udpMonitor.receiveData();

        // Create a Command object from the received data.
        Command* command = CommandFactory::createCommand(receivedData);
        if (command == nullptr) {
            udpMonitor.sendData(ERR); // Send error response if the command is invalid.
            continue;
        }

        // Set up the socket connection for the command.
        command->setupSocketConnection(
            port,
            verbose,
            udpMonitor.getCommandSocketfd(),
            udpMonitor.getServerInfo(),
            udpMonitor.getClientInfo()
        );

        // Enqueue the command into the thread pool for execution.
        threadPool->enqueue(command);
    }
}

// Function to run the TCP monitor, handling incoming TCP requests.
void runTcpMonitor(ThreadPool* threadPool, int port, bool verbose) {
    printf("Starting tcp monitor on port %d %s verbose mode\n", port, verbose ? "with" : "without");
    TcpSocket tcpMonitor = TcpSocket(port, verbose); // Initialize the TCP monitor socket.

    while (true) {
        // Receive data from the TCP socket.
        string receivedData = tcpMonitor.receiveData();

        // Create a Command object from the received data.
        Command* command = CommandFactory::createCommand(receivedData);
        if (command == nullptr) {
            tcpMonitor.sendData(ERR); // Send error response if the command is invalid.
            continue;
        }

        // Set up the socket connection for the command.
        command->setupSocketConnection(
            port,
            verbose,
            tcpMonitor.getCommandSocketfd(),
            tcpMonitor.getServerInfo(),
            tcpMonitor.getClientInfo()
        );

        // Enqueue the command into the thread pool for execution.
        threadPool->enqueue(command);
    }
}

// Main function to initialize and run the UDP and TCP monitors.
int main(int argc, char** argv) {
    int port = DEFAULT_PORT; // Default port for the server.
    bool verbose = DEFAULT_VERBOSE; // Default verbosity setting.

    // Parse command-line arguments.
    for (int i = 0; i < argc; i++) {
        string arg = argv[i];

        if (arg == PORT_FLAG) {
            port = atoi(argv[i + 1]); // Set the port based on the argument.
        } else if (arg == VERBOSE_FLAG) {
            verbose = true; // Enable verbose mode.
        }
    }

    ThreadPool threadPool = ThreadPool(); // Initialize the thread pool.

    // Run the UDP and TCP monitors in separate threads.
    thread udpMonitorThread(runUdpMonitor, &threadPool, port, verbose);
    thread tcpMonitorThread(runTcpMonitor, &threadPool, port, verbose);

    printf("Waiting for monitors to finish\n");

    // Wait for the monitor threads to complete.
    udpMonitorThread.join();
    tcpMonitorThread.join();

    return 0;
}

#include "main.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    string serverIP = DEFAULT_IP; // Default server IP
    int serverPort = DEFAULT_PORT; // Default server port

    // Parse command-line arguments to set server IP and port
    for (int i = 0; i < argc; i++) {
        string arg = argv[i];

        if (arg == IP_FLAG) {
            serverIP = argv[i + 1];
        } else if (arg == PORT_FLAG) {
            serverPort = atoi(argv[i + 1]);
        }
    }

    printf("Connecting to %s:%d\n", serverIP.c_str(), serverPort); // Display connection details

    Client client = Client(); // Initialize the client
    int exit = 0; // Exit flag for the main loop

    // Main loop for handling user input and executing commands
    while (!exit) {
        printf("\n> "); // Prompt for user input

        string input;
        getline(cin, input); // Read input from the user

        Command* command = nullptr; // Pointer to the current command

        try {
            command = CommandParser::parseCommand(input); // Parse the input into a command

            // If the command is invalid or not recognized, skip to the next iteration
            if (command == nullptr) {
                continue;
            }

            // Set up the command with the server and client information
            command->setNetworkClient(serverIP, serverPort);
            command->setClient(&client);

            // Execute the command
            exit = command->execute();
        } catch (const CostumError& e) {
            printf("%s\n", e.what());
        } catch (const exception& e) {
            printf("%s\n", string(UNKNOW_ERROR_MSG).c_str());
        }

        // Clean up the command object after execution
        if (command != nullptr) {
            delete command;
        }

        // Reset the client state if the game has ended
        if (client.isWin() || client.isLose()) {
            client.reset();
        }
    }

    return 0; // Exit the program
}

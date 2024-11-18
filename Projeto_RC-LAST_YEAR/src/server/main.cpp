#include "main.hpp"

void runUdpMonitor(ThreadPool* threadPool, int port, bool verbose){
  printf("Starting udp monitor on port %d %s verbose mode\n", port, verbose ? "with" : "without");
  UdpSocket udpMonitor = UdpSocket(port, verbose);

  while (true){
    string receivedData = udpMonitor.receiveData();

    Command *command = CommandFactory::createCommand(receivedData);
    if (command == nullptr) {
      udpMonitor.sendData(STATUS_ERR);
      continue;
    }

    //set up the socket connection for the command
    command->setupSocketConnection(
      port, 
      verbose, 
      udpMonitor.getCommandSocketfd(),
      udpMonitor.getServerInfo(),
      udpMonitor.getClientInfo()
    );

    threadPool->enqueue(command);
  }
}

void runTcpMonitor(ThreadPool* threadPool, int port, bool verbose){
  printf("Starting tcp monitor on port %d %s verbose mode\n", port, verbose ? "with" : "without");
  TcpSocket tcpMonitor = TcpSocket(port, verbose);

  while (true){
    string receivedData = tcpMonitor.receiveData();

    Command *command = CommandFactory::createCommand(receivedData);
    if (command == nullptr) {
      tcpMonitor.sendData(STATUS_ERR);
      continue;
    }

    //set up the socket connection for the command
    command->setupSocketConnection(
      port, 
      verbose, 
      tcpMonitor.getCommandSocketfd(),
      tcpMonitor.getServerInfo(),
      tcpMonitor.getClientInfo()
    );

    threadPool->enqueue(command);
  }
}

int main(int argc, char **argv){
  int port = DEFAULT_PORT;
  bool verbose = DEFAULT_VERBOSE;

  for (int i = 0; i < argc; i++){
    string arg = argv[i];

    if (arg == PORT_FLAG)
    {
      port = atoi(argv[i + 1]);
    }
    else if (arg == VERBOSE_FLAG){
      verbose = true;
    }
  }

  ThreadPool threadPool = ThreadPool();

  // run each monitor in a separate thread
  thread udpMonitorThread(runUdpMonitor, &threadPool, port, verbose);
  thread tcpMonitorThread(runTcpMonitor, &threadPool, port, verbose);

  printf("Waiting for monitors to finish\n");
  udpMonitorThread.join();
  tcpMonitorThread.join();

  return 0;
}
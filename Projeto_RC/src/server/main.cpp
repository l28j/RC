#include "main.hpp"

void runUdpMonitor(ThreadPool* threadPool, int port, bool verbose){
  UdpSocket udpMonitor = UdpSocket(port, verbose);
  printf("Starting udp monitor on port %d %s verbose mode\n", port, verbose ? "with" : "without");

  while (true){
    string received_data = udpMonitor.receiveData();

    Command *command = CommandFactory::createCommand(received_data);
    if (command == nullptr) {
      udpMonitor.sendData(ERR);
      continue;
    }

    //set up the socket connection for the command
    command->setupSocketConnection(
      verbose, 
      port, 
      udpMonitor.getCommandSocketfd(),
      udpMonitor.getServerInfo(),
      udpMonitor.getClientInfo()
    );

    threadPool->enqueue(command);
  }
}

void runTcpMonitor(ThreadPool* threadPool, int port, bool verbose){
  printf("Starting tcp monitor on port %d %s verbose mode\n", port, verbose ? "with" : "without");
  TcpSocket tcp_monitor = TcpSocket(port, verbose);

  while (true){
    string received_data = tcp_monitor.receiveData();

    Command *command = CommandFactory::createCommand(received_data);
    if (command == nullptr) {
      tcp_monitor.sendData(ERR);
      continue;
    }

    //set up the socket connection for the command
    command->setupSocketConnection(
      port, 
      verbose, 
      tcp_monitor.getCommandSocketfd(),
      tcp_monitor.getServerInfo(),
      tcp_monitor.getClientInfo()
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
  thread udp_monitor_thread(runUdpMonitor, &threadPool, port, verbose);
  thread tcp_monitor_thread(runTcpMonitor, &threadPool, port, verbose);

  printf("Waiting for monitors to finish\n");
  udp_monitor_thread.join();
  tcp_monitor_thread.join();

  return 0;
}
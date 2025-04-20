//
//

#include "std_io_handler.h"

#include <csignal>
#include <iostream>

namespace mcp {

void HandleSignal(int signal) {
  if (signal == SIGINT) {
    std::cout << "\nReceived Ctrl+C. Exiting program." << std::endl;
    std::exit(0);
  }
}

void StdIoHandler::Handle(Server* server) {
  std::signal(SIGINT, HandleSignal);

  std::string id = "id";
  server->RegisterSession(id, Session());
  while (true) {
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    if (input == "exit") {
      break;
    }
    ServerContextPtr context = std::make_shared<ServerContext>(input);
    auto response = server->HandleMessage(context);
    std::cout << response.ToJson() << std::endl;
  }
  server->UnregisterSession(id);
}

}  // namespace mcp
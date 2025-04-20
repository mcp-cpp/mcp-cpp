//
//

#include "std_io_handler.h"

#include <csignal>
#include <iostream>

namespace mcp {

void handleSignal(int signal) {
  if (signal == SIGINT) {
    std::cout << "\nReceived Ctrl+C. Exiting program." << std::endl;
    std::exit(0);
  }
}

void StdIoHandler::Handle(Server* server) {
  std::signal(SIGINT, handleSignal);

  while (true) {
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    ServerContextPtr context = std::make_shared<ServerContext>(input);
    auto response = server->HandleMessage(context);
    std::cout << response.ToJson() << std::endl;
  }
}

}  // namespace mcp
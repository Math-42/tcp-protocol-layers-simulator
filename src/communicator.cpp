#include "communicator.hpp"

void EchoCommunicator::start() {
    std::string message;
    while (true) {

        std::cout << "\033[36m[INPUT]\033[0m Mensagem:";
        std::getline(std::cin, message);
        if (!message.compare("exit")) break;

        std::cout << "\033[34m[INFO]\033[0m Enviando: " << std::endl;
        std::cout << "\033[34m[INFO]\033[0m Mensagem: " << message << std::endl;

    	Application::send(message);

    }
}

void EchoCommunicator::receive(std::string message) {
    std::cout << "\033[36m[OUTPUT]\033[0m Mensagem Recebida:";
    std::cout << message << std::endl;
}
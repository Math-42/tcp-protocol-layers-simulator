#include "./application.hpp"
/**
 * O std::vector<bool> é uma especialização do std vector que permite trabalhar diretamente com bits
 * ref: https://en.cppreference.com/w/cpp/container/vector_bool 
 */

void Application::send(std::string message) {
    std::cout << "\033[35m[LAYER]\033[0m Camada de aplicação:" << std::endl;
    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Convertendo para bits:" << std::endl;

    std::vector<bool> bitFrame;

    for (auto character : message) {
        std::bitset<8> tempBits(character);//le um caracter de 8bits
        for (int i = 7; i >= 0; i--) {
            bitFrame.push_back(tempBits[i]);//salva na ordem correta
        }
    }

    printBytes(bitFrame);

    DataLink::send(bitFrame);
}

void Application::receive(std::vector<bool> message) {
    std::cout << "\033[35m[LAYER]\033[0m Camada de aplicação:" << std::endl;
    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Convertendo mensagem:" << std::endl;

    std::string parsedMessage = "";
    int i = 7;
    std::bitset<8> tempBits;
    for (auto bit : message) {
        tempBits[i] = bit;
        i--;
        if (i < 0) {
            i = 7;
            unsigned long X = tempBits.to_ulong();
            parsedMessage += static_cast<char>(X);
        }
    }

    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Mensagem convertida:" << std::endl;
    std::cout << parsedMessage << std::endl;
    EchoCommunicator::receive(parsedMessage);
}

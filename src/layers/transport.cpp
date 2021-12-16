#include "transport.hpp"

void Transport::send(std::vector<bool> messageFrame) {
    std::cout << "\033[35m[LAYER]\033[0m Camada do meio de comunicação:" << std::endl;
    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Binário enviado:" << std::endl;
    printStream(messageFrame);
    std::srand(std::time(nullptr));

    std::vector<bool> messageDestinationBuffer;

    bool temp;
    for (auto bit : messageFrame) {
        temp = (std::rand() % 100) <= ERROR_PROBABILITY ? !bit : bit;
        messageDestinationBuffer.push_back(temp);
    }

    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Recebimento:" << std::endl;
    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Binário recebido:" << std::endl;
    printStream(messageDestinationBuffer);

    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Diff:" << std::endl;

    printDiff(messageFrame, messageDestinationBuffer);

    DataLink::receive(messageDestinationBuffer);
}
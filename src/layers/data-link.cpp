#include "data-link.hpp"

void DataLink::send(std::vector<bool> frame) {
    std::cout << "\033[35m[LAYER]\033[0m Camada de enlace:" << std::endl;
    frame = errorHandling(frame);
    Transport::send(frame);
}

void DataLink::receive(std::vector<bool> frame) {
    std::cout << "\033[35m[LAYER]\033[0m Camada de enlace:" << std::endl;
    if (errorTest(frame)) std::cout << "\033[1m\033[31m[ERROR]\033[0m Erro no quadro recebido" << std::endl;

    std::cout << "\033[35m[INFO]\033[0m Binário da mensagem:" << std::endl;
    printBytes(frame);

    Application::receive(frame);
}

std::vector<bool> DataLink::errorHandling(std::vector<bool> frame) {
    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Iniciando tratamento de erros" << std::endl;
    switch (ERROR_HANDLING_TYPE) {
        case 0:
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando paridade par" << std::endl;
            return evenParityControl(frame);

        case 1:
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando paridade impar" << std::endl;
            return oddParityControl(frame);

        default:
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando polinomio" << std::endl;
            return evenParityControl(frame);
    }
}

bool DataLink::errorTest(std::vector<bool>& frame) {
    std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Iniciando teste de erros" << std::endl;
    switch (ERROR_HANDLING_TYPE) {
        case 0:
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando paridade par" << std::endl;
            return evenParityCheck(frame);

        case 1:
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando paridade impar" << std::endl;
            return oddParityCheck(frame);

        default:
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando polinomio" << std::endl;
            return evenParityCheck(frame);
    }
}

bool DataLink::isEven(std::vector<bool> frame) {
    bool isEven = false;

    for (auto bit : frame) {
        isEven = isEven ^ bit;
    }

    return !isEven;
}

std::vector<bool> DataLink::evenParityControl(std::vector<bool> frame) {
    frame.insert(frame.begin(), isEven(frame));
    return frame;
}

std::vector<bool> DataLink::oddParityControl(std::vector<bool> frame) {
    frame.insert(frame.begin(), !isEven(frame));
    return frame;
}

bool DataLink::evenParityCheck(std::vector<bool>& frame) {
    bool parity = frame[0];
    frame.erase(frame.begin());
    std::cout << "\033[35m[INFO]\033[0m Bit de paridade e paridade" << std::endl;
    return parity != isEven(frame);
}

bool DataLink::oddParityCheck(std::vector<bool>& frame) {
    bool parity = frame[0];
    frame.erase(frame.begin());
    return parity != !isEven(frame);
}
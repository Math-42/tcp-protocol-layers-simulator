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
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando polinômio" << std::endl;
            return crc32Control(frame);
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
            std::cout << "\033[34m\033[34m[INFO]\033[0m\033[0m Usando polinômio" << std::endl;
            return crc32Check(frame);
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

std::vector<bool> DataLink::crc32Control(std::vector<bool> frame) {
    std::cout << "\033[34m[INFO]\033[0m Polinômio:" << std::endl;

    std::vector<bool> polinomio{
        1, 0, 0, 0, 0, 0, 1, 0,
        0, 1, 1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 1, 1, 0,
        1, 1, 0, 1, 1, 0, 1, 1,
        1};

    std::cout << std::endl;

    for (int i = 0; i < polinomio.size(); i++) {
        if (polinomio[i]) std::cout << "+x^" << polinomio.size()- 1 - i << " ";
    }

    std::cout << std::endl;

    std::vector<bool> remaining = frame;
    remaining.resize(remaining.size() + 32);

    for (int i = 0; i < remaining.size() - 32; i++) {

        if (remaining[i]) {
            for (int j = 0; j < polinomio.size(); j++) {
                remaining[i + j] = remaining[i + j] ^ polinomio[j];
            }
        }
        remaining[i] = frame[i];
    }

    frame = remaining;

    std::cout << "\033[34m[INFO]\033[0m Frame + resto:" << std::endl;
    printBytes(frame);

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

bool DataLink::crc32Check(std::vector<bool>& frame) {

    std::vector<bool> polinomio{
        1, 0, 0, 0, 0, 0, 1, 0,
        0, 1, 1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 1, 1, 0,
        1, 1, 0, 1, 1, 0, 1, 1,
        1};

    std::vector<bool> remaining = frame;
    remaining.resize(remaining.size());

    for (int i = 0; i < remaining.size() - 32; i++) {

        if (remaining[i]) {
            for (int j = 0; j < polinomio.size(); j++) {
                remaining[i + j] = remaining[i + j] ^ polinomio[j];
            }
        }
        remaining[i] = frame[i];
    }

    std::cout << "\033[34m[INFO]\033[0m Frame + resto:" << std::endl;
    printBytes(remaining);

    bool hasError = false;
    for (int i = 0; i < polinomio.size() - 1; i++) {
        frame.erase(frame.end());
        if (!hasError) hasError = remaining.size();
    }

    return true;
}
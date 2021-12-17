#pragma once

#include <iostream>
#include <string>

#include "layers/application.hpp"
/**
 * Classe que imita as camadas do protocolo, enviando e recebendo mensangens
 */
class EchoCommunicator {
   public:
    /**
	 * Inicializa um loop de leitura do teclado, enviando mensangens toda vez que a tecla
	 * Enter for pressionada
	 */
    static void start();

    /**
	 * Recebe uma mensagem e a imprime
	 * @param message mensagem recebida
	 */
    static void receive(std::string message);
};
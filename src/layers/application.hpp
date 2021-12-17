#pragma once

#include <bitset>
#include <iostream>
#include <vector>

#include "../communicator.hpp"
#include "data-link.hpp"
#include "layer.hpp"
/**
 * O std::vector<bool> é uma especialização do std vector que permite trabalhar diretamente com bits
 * ref: https://en.cppreference.com/w/cpp/container/vector_bool 
 */

class Application : public Layer {
   public:
    /**
	 * Transforma uma mensagem do tipo string em binário e envia para a camada de enlace
	 */
    static void send(std::string message);

    /**
	 * Recebe binários da camada de enlace e converte para uma string, enviando para a aplicação
	 */
    static void receive(std::vector<bool>);
};
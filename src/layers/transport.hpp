#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>

#include "data-link.hpp"
#include "layer.hpp"
#include "../frame.hpp"
#define ERROR_PROBABILITY 5

class Transport : public Layer {
   public:
	/**
	 * Transmite a mensagem para outro "computador" aplicando erros
	 * aleatoriamente em cada bit, de acordo com o ERROR_PROBABILITY
	 * @param messageFrame mensagem que será enviada
	 */
    static void send(std::vector<bool> messageFrame);
};
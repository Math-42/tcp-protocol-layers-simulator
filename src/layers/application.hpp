#pragma once

#include <bitset>
#include <iostream>
#include <vector>
#include "data-link.hpp"
#include "layer.hpp"
#include "../communicator.hpp"
/**
 * O std::vector<bool> é uma especialização do std vector que permite trabalhar diretamente com bits
 * ref: https://en.cppreference.com/w/cpp/container/vector_bool 
 */

class Application : public Layer {
   public:
    static void send(std::string message);
    static void receive(std::vector<bool>);
};
#pragma once

#include <string>
#include <iostream>
#include "layers/application.hpp"

class EchoCommunicator {
   public:

    static void start();
    static void send(std::string);
    static void receive(std::string);
};
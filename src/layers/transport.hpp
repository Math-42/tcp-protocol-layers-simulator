#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>

#include "data-link.hpp"
#include "layer.hpp"
#include "../frame.hpp"
#define ERROR_PROBABILITY 1

class Transport : public Layer {
   public:
    static void send(std::vector<bool> messageFrame);
};
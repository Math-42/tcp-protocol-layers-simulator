#pragma once

#include <vector>
#include <iostream>
#include "layer.hpp"
#include "transport.hpp"
#include "application.hpp"

#define ERROR_HANDLING_TYPE 0

class DataLink : public Layer {
   public:
    static void send(std::vector<bool> frame);
    static void receive(std::vector<bool> frame);

   private:
    static std::vector<bool> errorHandling(std::vector<bool> frame);
	
    static bool errorTest(std::vector<bool>& frame);

    static bool isEven(std::vector<bool> frame);

    static std::vector<bool> evenParityControl(std::vector<bool> frame);

    static std::vector<bool> oddParityControl(std::vector<bool> frame);

    static bool evenParityCheck(std::vector<bool>& frame);

    static bool oddParityCheck(std::vector<bool>& frame);
};
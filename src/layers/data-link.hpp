#pragma once

#include <vector>
#include <iostream>
#include "layer.hpp"
#include "transport.hpp"
#include "application.hpp"

#define ERROR_HANDLING_TYPE 2

class DataLink : public Layer {
   public:
    /**
	 * Recebe um binário e aplica algoritimos de enquadramento, enviando para a camada
	 * de comunicação
	 * @param frame binário a ser enviado
	 */
    static void send(std::vector<bool> frame);

	/**
	 * Recebe um binário da camada de comunicação, testa se houveram erros de comunicação
	 * e extrai a mensagem
	 * @param frame frame a ser testado 
	 */	
    static void receive(std::vector<bool> frame);

   private:
    /**
	 * Seleciona um algoritimo de tratamento de erros e aplica no frame
	 * @param frame frame recebido
	 */
    static std::vector<bool> errorHandling(std::vector<bool> frame);
	
	/**
	 * Seleciona um algoritimo, testa se ocorreram erros e extrai a mensagem
	 * @param frame frame que será testado
	 */
    static bool errorTest(std::vector<bool>& frame);

	/**
	 * Testa se um binário possui um número par de 1's
	 * @return verdadeiro se possui um número par de 1's
	 */
    static bool isEven(std::vector<bool> frame);

    /**
	 * Adiciona um 1 no inicio do binário caso ele possua um número par de 1's e 0 caso contrário
	 * @param frame binário a ser alterado
	 */
    static std::vector<bool> evenParityControl(std::vector<bool> frame);

    /**
	 * Adiciona um 1 no inicio do binário caso ele possua um número impar de 1's e 0 caso contrário
	 * @param frame binário a ser alterado
	 */
    static std::vector<bool> oddParityControl(std::vector<bool> frame);
    
    /**
	 * Aplica o algoritimo crc32 em um binário
	 * @param frame binário a ser alterado
	 */
	static std::vector<bool> crc32Control(std::vector<bool> frame);

    /**
	 * Testa se o bit de paridade continua coerente, e extrai a mensagem
	 * @param frame binário a ser analisado
	 */
    static bool evenParityCheck(std::vector<bool>& frame);

    /**
	 * Testa se o bit de paridade continua coerente, e extrai a mensagem
	 * @param frame binário a ser analisado
	 */
    static bool oddParityCheck(std::vector<bool>& frame);

    /**
	 * Testa se o resto do binário recebido permanece como 0 (reaplica o crc32) e extrai a mensagem 
	 * @param frame binário a ser analisado
	 */
    static bool crc32Check(std::vector<bool>& frame);
};
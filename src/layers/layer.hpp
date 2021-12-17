#pragma once

class Layer {
   public:
    /**
	 * Função chamada quando se recebe algo pela camada inferior
	 */
    template <typename R, typename S>
    static R receive(S value) = delete;

    /**
	 * Função chamada quando se recebe algo pela camada superior
	 */
    template <typename R, typename S>
    static R send(S value) = delete;
};
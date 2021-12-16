#pragma once

class Layer {
   public:
    template <typename R, typename S>
    static R receive(S value) = delete;

    template <typename R, typename S>
    static R send(S value) = delete;
};
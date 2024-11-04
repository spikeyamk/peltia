#pragma once

#include "usart.h"
#include "common/magic/magic.hpp"
#include "tasks/prototype.hpp"

namespace tasks {
    class RS232_UART : public Prototype<RS232_UART, 16 * 1024, "rs232_uart"> {
    private:
        struct Connection {
            struct States {
                struct Disconnected {};
                struct Connected {};
            };

            struct Actions {
                static void connect(RS232_UART& self);
                static void disconnect(RS232_UART& self);
                static void nop(RS232_UART& self);
                static void read_sensors(const RS232_UART& self);
                static void write_temp(RS232_UART& self, const common::magic::commands::WriteTemp& write_temp);
            };

            auto operator()() const;
        };

        float temp_front { 40.0f };
        float temp_rear { 39.0f };
        float desired_temp { 20.0f };
    private:
        RS232_UART() = default;
    public:
        static RS232_UART& get_instance();
        static void worker(void* arg);
    private:
        template<typename T>
        void transmit(const T& obj) const {
            const auto buf { common::magic::results::Serializer::run(obj) };
            static_assert(buf.size() <= common::magic::MTU);
            HAL_UART_Transmit(&huart3, buf.data(), buf.size(), HAL_MAX_DELAY);
        }
    };
}
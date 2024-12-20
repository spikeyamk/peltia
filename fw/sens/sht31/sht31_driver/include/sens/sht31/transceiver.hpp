#pragma once

#include <cstdint>
#include <expected>

#include "stm32f2xx_hal.h"
#include "sens/sht31/addrs.hpp"

namespace sens {
namespace sht31 {
    class Transceiver {
    public:
        I2C_HandleTypeDef* hi2c;
        const uint16_t slave_address_8bit;
    public:
        Transceiver() = delete;
        Transceiver(I2C_HandleTypeDef* hi2c, const SlaveAddress7bit slave_address);

        HAL_StatusTypeDef write_command(const std::bitset<16>& command) const;

        template<size_t N>
        std::expected<std::array<std::bitset<8>, N>, HAL_StatusTypeDef> read() const;

        static std::bitset<8> calculate_crc(const std::array<std::bitset<8>, 2>& data);
    };
}
}
#include "stm32f2xx_hal.h"
#include "fanctl/bulk.hpp"

namespace fanctl {
    void stop_all() {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET); // bottom right
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); // front right

        // Missing fan
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET); // rear left
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET); // front left
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET); // rear right
        HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET); // bottom left

        // Missing fan
        HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}
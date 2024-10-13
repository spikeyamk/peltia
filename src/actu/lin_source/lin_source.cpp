#include "actu/lin_source/lin_source.hpp"

namespace actu {
namespace lin_source {
    void start_dac(DAC_HandleTypeDef* hdac) {
        HAL_DAC_Start(hdac, DAC_CHANNEL_1);  // Start DAC on PA4
        HAL_DAC_Start(hdac, DAC_CHANNEL_2);  // Start DAC on PA5
    }

    void set_output(DAC_HandleTypeDef* hdac, uint32_t val_a, uint32_t val_b) {
        // Write value to DAC channel 2 (PA5)
        HAL_DAC_SetValue(hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, val_a);

        // Write value to DAC channel 1 (PA4)
        HAL_DAC_SetValue(hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, val_b);
    }
}
}
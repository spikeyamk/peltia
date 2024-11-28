#include "comm/rs232_uart/semaphore.hpp"

namespace comm {
namespace rs232_uart {
    Semaphore::Semaphore() {
        const osSemaphoreAttr_t sem_attr {
            .name = "rs232_sem",
            .attr_bits = 0,
            .cb_mem = &sem_control_block,
            .cb_size = sizeof(sem_control_block),
        };
        assert((sem = osSemaphoreNew(1, 0, &sem_attr)) != nullptr);
    }

    void Semaphore::release() {
        osSemaphoreRelease(sem);
    }

    void Semaphore::acquire() {
        while(osSemaphoreAcquire(sem, osWaitForever) != osOK) {}
    }

    bool Semaphore::try_acquire_for(const uint32_t timeout_ms) {
        return osSemaphoreAcquire(sem, timeout_ms) == osOK;
    }
}
}
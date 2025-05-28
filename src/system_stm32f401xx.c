#include "stm32f401xx.h"

void SystemInit(void)
{
    // Vô hiệu hóa tất cả ngắt
    __asm volatile ("cpsid i");

    // Thiết lập lại hệ thống nếu cần, ví dụ bật HSE, PLL (tùy yêu cầu)
    // Ở mức đơn giản, có thể để trống hoặc bật HSI mặc định

    // Có thể bật FPU nếu cần
    *((volatile unsigned int*)0xE000ED88) |= (0xF << 20);

    // Bật lại ngắt nếu muốn
    __asm volatile ("cpsie i");
}

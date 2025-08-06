

#include "stm32f4xx.h"
#include "delay_lib.h"
#include "init_config.h"

// ...existing code...

void usart2_send_string(const char *str)
{
    while (*str) {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        USART_SendData(USART2, *str++);
    }
}

int main(void)
{
    init_config();
    usart2_send_string("hello_world\r\n");

    // Main loop - blink LED on PC13 and PA10
    while (1) {
        GPIO_SetBits(GPIOC, GPIO_Pin_13);    // Turn LED ON (PC13)
        GPIO_SetBits(GPIOA, GPIO_Pin_10);    // Turn LED ON (PA10)
        delay_s(1);  // 1 second delay
        GPIO_ResetBits(GPIOC, GPIO_Pin_13);  // Turn LED OFF (PC13)
        GPIO_ResetBits(GPIOA, GPIO_Pin_10);  // Turn LED OFF (PA10)
        delay_s(1);  // 1 second delay
    }

    // This line should never be reached, but added to avoid warning
    return 0;
}

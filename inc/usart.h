// === FILE: usart.h ===
#ifndef USART_H
#define USART_H

void USART2_Init(void);
void USART2_SendChar(char c);
void USART2_SendString(const char *str);
void USART2_IRQHandler(void);

#endif // USART_H
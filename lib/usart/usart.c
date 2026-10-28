#include"usart.h"

void usart_init(USART_TypeDef * USARTx, uint32_t baudrate){
    //USART 1
    if(USARTx == USART1){
        //enciendo clocks
        RCC -> APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
        //configuro pines
        //TX
        GPIOA-> CRH &=~(0XF << ((9%8) * 4));
        GPIOA-> CRH |= (0xB << ((9%8) * 4));
        //RX
        GPIOA-> CRH &=~(0XF << ((10%8) * 4));
        GPIOA-> CRH |= (0X4 << ((10%8) * 4));
        //formula velocidad
        float velocidad = (16 * baudrate) / 72000000;       //72MHz
        int v_mantissa = velocidad;                         //me quedo con la parte entera del float
        int v_fraccion = (velocidad - v_mantissa) * 100;    //me quedo la parte fraccional
        //velocidad de comunicacion
        USARTx -> BRR |= (v_mantissa << 4) | v_fraccion;    //desplazo 4 bits para que entre la parte fraccional.
                                                            //luego le agrego la parte fraccional con un OR
        USART1->CR1 |= USART_CR1_UE;                        //enciendo el USART
    }
    //USART 2
    if(USARTx == USART2){
        //enciendo clocks
        RCC -> APB2ENR |= RCC_APB1ENR_USART2EN | RCC_APB2ENR_IOPAEN;
        //configuro pines
        //TX
        GPIOA ->CRL&=~(0xF<<(2*4));
        GPIOA ->CRL|=(0x4<<(2*4));
        //RX
        GPIOA ->CRL&=~(0xF<<(3*4));
        GPIOA ->CRL|=(0x4<<(3*4));
        //formula velocidad
        float velocidad = (16 * baudrate) / 36000000;       //36MHz
        int v_mantissa = velocidad;
        int v_fraccion = (velocidad - v_mantissa) * 100;
        //velocidad de comunicacion
        USARTx -> BRR |= (v_mantissa << 4) | v_fraccion;
        USART2->CR1 |= USART_CR1_UE;
    }
    //USART 3
    if(USARTx == USART3){
        //enciendo clocks
        RCC -> APB2ENR |= RCC_APB1ENR_USART3EN | RCC_APB2ENR_IOPBEN;
        //configuro pines
        //TX
        GPIOB-> CRH &=~(0XF << ((10%8) * 4));
        GPIOB-> CRH |= (0xB << ((10%8) * 4));
        //RX
        GPIOB-> CRH &=~(0XF << ((11%8) * 4));
        GPIOB-> CRH |= (0X4 << ((11%8) * 4));
        //formula velocidad
        float velocidad = (16 * baudrate) / 36000000;       //36MHz
        int v_mantissa = velocidad;
        int v_fraccion = (velocidad - v_mantissa) * 100;
        //velocidad de comunicacion
        USARTx -> BRR |= (v_mantissa << 4) | v_fraccion;
        USART3->CR1 |= USART_CR1_UE;
    }

    USARTx-> CR1 |= USART_CR1_TE | USART_CR1_RE;            //habilito transmicion y recepcion
}
void usart_send_char(USART_TypeDef * USARTx, uint8_t data){
    USARTx-> DR = data;
    while(!(USARTx->SR & USART_SR_TXE));
}
void usart_send_string(USART_TypeDef* USARTx, char* textogod){
    while(*textogod){
        usart_send_char(USARTx,*textogod);
        textogod++;
    }
}
uint8_t usart_receive_char(USART_TypeDef * USARTx){
    while(!(USARTx->SR & USART_SR_RXNE));
    return USARTx->DR;
}
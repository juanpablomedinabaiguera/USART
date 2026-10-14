#include "stm32f103xb.h"
#include "clk_maximizer.h"
#include "usart.h"
int main(){
    usart_init(1,115200);
    while(1){
        usart_send_char(1, 'a');
    }
}
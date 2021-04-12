#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

int inp_btn_a()
{
	return (!GPIO->IN & (1 << 17));
}

int inp_btn_b()
{
	return (!GPIO->IN & (1 << 26));
}

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[__BUTTON_A_PIN__] = 0;
	GPIO->PIN_CNF[__BUTTON_B_PIN__] = 0;

	int sleep = 0;
	while(1){
		if(inp_btn_b())
		{
			GPIO->OUTCLR = GPIO->OUTCLR | (111111111 << 4);
			GPIO->OUTSET = GPIO->OUTSET | (111 << 13);
		}
		if(inp_btn_a())
		{
			GPIO->OUTSET = GPIO->OUTCLR | (111111111 << 4);
			GPIO->OUTCLR = GPIO->OUTSET | (111 << 13);
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}

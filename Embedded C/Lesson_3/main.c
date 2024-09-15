typedef volatile unsigned int vuint32_t;

// Register Address
#define RCC_BASE   0x40021000
#define GPOIA_BASE 0x40010800

#define RCC_APB2ENR *(volatile unsigned int *)(RCC_BASE   + 0x18)
#define GPOIA_CRH   *(volatile unsigned int *)(GPOIA_BASE + 0x04)
#define GPOIA_ODR   *(volatile unsigned int *)(GPOIA_BASE + 0x0c)

// Bit Fields
#define RCC_IOPAEN (1<<2)
#define GPIOA13    (1UL<<13)

typedef union
{
	vuint32_t all_fields;
	struct
	{
		vuint32_t reversed:13;
		vuint32_t P_13:1;
	}Pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*) (GPOIA_BASE + 0x0c);

int main(void)
{
	int delay = 100000;
	int i;
	
	// Enable PORT.A
	RCC_APB2ENR |= RCC_IOPAEN;

	// Bit Mode = 2
	GPOIA_CRH &= 0xff0fffff;
	GPOIA_CRH |= 0x00200000;

	/* Loop forever */
	while(1)
	{
		R_ODR->Pin.P_13 = 1;
		for(i=0; i<delay; i++); 
		R_ODR->Pin.P_13 = 0;
		for(i=0; i<delay; i++); 
	}
	
}

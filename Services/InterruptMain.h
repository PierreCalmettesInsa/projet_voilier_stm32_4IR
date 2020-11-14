#include "stm32f103xb.h" 

static uint16_t ticks_scheduler ;

void init_systick(void);

void SysTick_Handler(void);

void verif_girouette(void);

void verif_roulis(void);

void verif_teleco(void);

void send_uart(void);

void schedule_sys_tasks(void);

void interrupt_start(void);

void Verif_sail_50ms(void);

int get_uart(void);

void reset_uart(void);
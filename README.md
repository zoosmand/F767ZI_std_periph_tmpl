# stm32f767zi (Cortex-M7) standard peripheral initialization

## This project aimed at creating an effective style of peripheral configuration, avoiding repetitions in code intrinsic to HAL and even LL.

- 216Mhz PLLP (main clock)
- 48Mhz PLLQ (USB bus clock)
- Cron (SysQuant, Milliseconds, Seconds, Minutes)
- IWDG (independent watchdog)
- printf: to choose the output define SWO_ITM either SWO_USART in main.h
- USART3 echo
- Demo Blinking LED in TIM6 #TODO
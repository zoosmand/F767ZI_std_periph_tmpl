# stm32f767zi (Cortex-M7) standard peripheral initialization

This project aims to create an efficient style of peripheral configuration for the stm32f767zi microcontroller, specifically focusing on avoiding code repetitions intrinsic to HAL and even LL.

## Features

- 216Mhz PLLP (main clock)
- 48Mhz PLLQ (USB bus clock)
- Cron (SysQuant, Milliseconds, Seconds, Minutes)
- IWDG (independent watchdog)
- printf: Choose the output by defining SWO_ITM or SWO_USART in main.h
- USART3 echo
- Demo Blinking LED in TIM6

## TODO

There are some pending tasks in this project that need to be completed:

- [ ] Task 1
- [ ] Task 2
- [ ] Task 3

Feel free to contribute to this project by completing any of the pending tasks or by suggesting improvements.
.syntax unified

.global Delay_Handler
.global _Delay


    .section  .text.Delay_Handler
    .type Delay_Handler, %function
Delay_Handler:
  @ push {r10, fp, lr}
  @ mov r10, r0
  @ add r0, r10, r10
  @ pop {r10, fp, pc}
  bx lr
  .size  Delay_Handler, .-Delay_Handler


@ TODO overfload bug
    .section  .text._Delay
    .type _Delay, %function
_Delay:
  ldr r1, =208000
  muls r0, r0, r1
  _LOOP_:
    sbcs r0, r0, 1
    bpl _LOOP_
  bx lr
  .size  _Delay, .-_Delay



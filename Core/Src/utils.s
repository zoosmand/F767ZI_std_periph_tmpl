.syntax unified

.global Delay_Handler
.global _Delay
.global SVC_Handler
.global prvPortStartFirstTask


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



    .section  .text.SVC_Handler
    .type SVC_Handler, %function
SVC_Handler:
  ldr	r3, pxCurrentTCBConst2
  ldr r1, [r3]
  ldr r0, [r1]
  ldmia r0!, {r4-r11, lr}
  msr psp, r0
  isb
  mov r0, #0
  msr	basepri, r0
  bx lr
  .align 4
  pxCurrentTCBConst2: .word pxCurrentTCB



    .section  .text.prvPortStartFirstTask
    .type prvPortStartFirstTask, %function
prvPortStartFirstTask:
  ldr r0, =0xe000ed08
  ldr r0, [r0]
  ldr r0, [r0]
  msr msp, r0
  mov r0, #0
  msr control, r0
  cpsie i
  cpsie f
  dsb
  isb
  svc 0



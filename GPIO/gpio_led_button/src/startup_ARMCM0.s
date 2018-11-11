# 1 "src/startup_ARMCM0.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "src/startup_ARMCM0.S"
# 26 "src/startup_ARMCM0.S"
 .syntax unified
 .arch armv6-m

 .section .stack
 .align 3
 .equ Stack_Size, 0x00000100
 .globl __StackTop
 .globl __StackLimit
__StackLimit:
 .space Stack_Size
 .size __StackLimit, . - __StackLimit
__StackTop:
 .size __StackTop, . - __StackTop

 .section .heap
 .align 3
 .equ Heap_Size, 0x00000200
 .globl __HeapBase
 .globl __HeapLimit
__HeapBase:
 .if Heap_Size
 .space Heap_Size
 .endif
 .size __HeapBase, . - __HeapBase
__HeapLimit:
 .size __HeapLimit, . - __HeapLimit

 .section .vectors
 .align 2
 .globl __Vectors
__Vectors:
 .long __StackTop
 .long Reset_Handler
 .long NMI_Handler
 .long HardFault_Handler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long SVC_Handler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long PendSV_Handler
 .long SysTick_Handler


 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler
 .long Reserved_IRQHandler

 .size __Vectors, . - __Vectors

 .text
 .thumb
 .thumb_func
 .align 1
 .globl Reset_Handler
 .type Reset_Handler, %function
Reset_Handler:

 bl main

 .end

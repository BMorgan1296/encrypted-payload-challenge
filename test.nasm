bits 64

section .text
global _start

_start:
  xor eax, eax
  xor ebx, ebx
  xor ecx, ecx
  xor edx, edx
  inc eax
  cpuid
  xor ebx, ebx
  mov ebx, eax
  xor eax, eax
  mov al, bl
  and al, 0xf
  ret
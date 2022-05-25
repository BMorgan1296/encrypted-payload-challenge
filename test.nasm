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
  mov eax, ebx
  ret
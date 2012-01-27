#include <stdint.h>
#include "util.h"

uint64_t rdtsc(void)
{
  uint32_t lo, hi;
  __asm__ __volatile__ (
  "xorl %%eax,%%eax \n        cpuid"
  ::: "%rax", "%rbx", "%rcx", "%rdx");
  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return (uint64_t)hi << 32 | lo;
}

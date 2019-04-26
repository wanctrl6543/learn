#ifndef CPUDETECT_H
#define CPUDETECT_H

#ifdef __cplusplus
extern "C" {
#endif 

#define CPUTYPE_I386    3
#define CPUTYPE_I486    4
#define CPUTYPE_I586    5
#define CPUTYPE_I686    6

#ifdef ARCH_X86_64
#  define REGa    rax
#  define REGb    rbx
#  define REGSP   rsp
#  define REG_a  "rax"
#  define REG_b  "rbx"
#  define REG_c  "rcx"
#  define REG_d  "rdx"
#  define REG_S  "rsi"
#  define REG_D  "rdi"
#  define REG_SP "rsp"
#  define REG_BP "rbp"
#else
#  define REGa    eax
#  define REGb    ebx
#  define REGSP   esp
#  define REG_a  "eax"
#  define REG_b  "ebx"
#  define REG_c  "ecx"
#  define REG_d  "edx"
#  define REG_S  "esi"
#  define REG_D  "edi"
#  define REG_SP "esp"
#  define REG_BP "ebp"
#endif

typedef struct cpucaps_s {
    int hasMMX;
    int hasMMX2;
    int has3DNow;
    int has3DNowExt;
    int hasSSE;
    int hasSSE2;
} CpuCaps;

extern CpuCaps gCpuCaps;

#ifdef __cplusplus
}
#endif 

#endif /* !CPUDETECT_H */
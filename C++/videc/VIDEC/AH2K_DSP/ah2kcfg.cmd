/*   Do *not* directly modify this file.  It was    */
/*   generated by the Configuration Tool; any  */
/*   changes risk being overwritten.                */

/* INPUT ah2k.cdb */

/* MODULE PARAMETERS */
GBL_USERINITFXN = _dm642_init;

MEM_SEGZERO = SDRAM;
MEM_MALLOCSEG = SDRAM;

CLK_TIMEFXN = CLK_F_getshtime;
CLK_HOOKFXN = HWI_F_dispatch;

PRD_THOOKFXN = _KNL_tick;

RTDX_DATAMEMSEG = SDRAM;

HST_DSMBUFSEG = SDRAM;

SWI_EHOOKFXN = GBL_NULL;
SWI_IHOOKFXN = GBL_NULL;
SWI_EXECFXN = SWI_F_iexec;
SWI_RUNFXN = SWI_F_run;

TSK_STACKSEG = MEM_NULL;
TSK_VCREATEFXN = _FXN_F_nop;
TSK_VDELETEFXN = _FXN_F_nop;
TSK_VEXITFXN = _FXN_F_nop;

IDL_CALIBRFXN = IDL_F_stub;

SYS_ABORTFXN = _UTL_doAbort;
SYS_ERRORFXN = _UTL_doError;
SYS_EXITFXN = _UTL_halt;
SYS_PUTCFXN = _UTL_doPutc;

GIO_CREATEFXN = _SEM_create;
GIO_DELETEFXN = _SEM_delete;
GIO_PENDFXN = _SEM_pend;
GIO_POSTFXN = _SEM_post;

/* OBJECT ALIASES */
_ISRAM = ISRAM;
_SDRAM = SDRAM;
_HPRAM = HPRAM;
_PRD_clock = PRD_clock;
_RTA_fromHost = RTA_fromHost;
_RTA_toHost = RTA_toHost;
_HWI_RESET = HWI_RESET;
_HWI_NMI = HWI_NMI;
_HWI_RESERVED0 = HWI_RESERVED0;
_HWI_RESERVED1 = HWI_RESERVED1;
_HWI_INT4 = HWI_INT4;
_HWI_INT5 = HWI_INT5;
_HWI_INT6 = HWI_INT6;
_HWI_INT7 = HWI_INT7;
_HWI_INT8 = HWI_INT8;
_HWI_INT9 = HWI_INT9;
_HWI_INT10 = HWI_INT10;
_HWI_INT11 = HWI_INT11;
_HWI_INT12 = HWI_INT12;
_HWI_INT13 = HWI_INT13;
_HWI_INT14 = HWI_INT14;
_HWI_INT15 = HWI_INT15;
_KNL_swi = KNL_swi;
_TSK_idle = TSK_idle;
_LNK_dataPump = LNK_dataPump;
_RTA_dispatcher = RTA_dispatcher;
_IDL_cpuLoad = IDL_cpuLoad;
_LOG_system = LOG_system;
_trace = trace;
_IDL_busyObj = IDL_busyObj;

/* MODULE GBL */

SECTIONS {
   .vers (COPY): {} /* version information */
}

-priority
-llnkrtdx.a64
-ldrivers.a64          /* device drivers support */
-lsioboth.a64          /* supports both SIO models */
-lbiosi.a64            /* DSP/BIOS support */
-lrtdx64xx.lib         /* RTDX support */
-lcslDM642.lib
-lrts6400.lib          /* C and C++ run-time library support */

_GBL_CACHE = GBL_CACHE;

/* MODULE MEM */
-stack 0x1000
MEMORY {
   ISRAM       : origin = 0x0,         len = 0x1f400
   SDRAM       : origin = 0x80000000,  len = 0x100000
   HPRAM       : origin = 0x80100000,  len = 0x1f00000
}
/* MODULE CLK */
SECTIONS {
   .clk: {
        _CLK_start = _CLK_start6x;
        CLK_F_gethtime = CLK_F_getshtime;
        CLK_A_TABBEG = .;
        *(.clk)
        CLK_A_TABEND = .;
        CLK_A_TABLEN = (. - CLK_A_TABBEG) / 1;
   } > SDRAM 
}
_CLK_PRD = CLK_PRD;
_CLK_COUNTSPMS = CLK_COUNTSPMS;
_CLK_REGS = CLK_REGS;
_CLK_USETIMER = CLK_USETIMER;
_CLK_TIMERNUM = CLK_TIMERNUM;
_CLK_TDDR = CLK_TDDR;

/* MODULE PRD */
SECTIONS {
   .prd: {
        PRD_A_TABBEG = .;
        /* no PRD objects */
        PRD_A_TABEND = .;
        PRD_A_TABLEN = (. - PRD_A_TABBEG) / 32;
   } > SDRAM
}

/* MODULE RTDX */
_RTDX_interrupt_mask = 0x0;

/* MODULE HWI */
SECTIONS {
    .hwi_vec: 0x0 {
        HWI_A_VECS = .;
        *(.hwi_vec)
    }
}

/* MODULE SWI */
SECTIONS {
   .swi: {
        SWI_A_TABBEG = .;
        *(.swi)
        SWI_A_TABEND = .;
        SWI_A_TABLEN = (. - SWI_A_TABBEG) / 44;
   } > ISRAM
}

/* MODULE IDL */
SECTIONS {
   .idl: {
        IDL_A_TABBEG = .;
        *(.idl)
        IDL_A_TABEND = .;
        IDL_A_TABLEN = (. - IDL_A_TABBEG) / 8;
        IDL_A_CALBEG = .;
        *(.idlcal)
        IDL_A_CALEND = .;
        IDL_A_CALLEN = (. - IDL_A_CALBEG) / 8;
   } > SDRAM
}



SECTIONS {
        .HPRAM$heap: {
            HPRAM$B = .;
            _HPRAM_base = .;
            HPRAM$L = 0x1f00000;
            _HPRAM_length = 0x1f00000;
            . += 0x1f00000;
        } > HPRAM
        
        .ISRAM$heap: {
            ISRAM$B = .;
            _ISRAM_base = .;
            ISRAM$L = 0x16800;
            _ISRAM_length = 0x16800;
            . += 0x16800;
        } > ISRAM
        
        .bss:     {} > SDRAM
        
        .far:     {} > SDRAM
        
        .sysdata: {} > SDRAM
        
        .sysregs: {} > SDRAM
        
        .sysinit:    {} > SDRAM
        
        .mem: 	  {} > SDRAM
        
        .gblinit:    {} > SDRAM
        
        .cinit:    {} > SDRAM
        
        .trcdata:    {} > SDRAM
        
        .data:    {} > SDRAM
        
        .const:    {} > SDRAM
        
        .switch:    {} > SDRAM
        
        .cio:     {} > SDRAM
        
        .text:    {} > SDRAM
        
        frt:    {} > SDRAM
        
        .bios:    {} > SDRAM
        
        .stack: fill=0xc0ffee {
            GBL_stackbeg = .;
            *(.stack)
            GBL_stackend = GBL_stackbeg + 0x1000 - 1;
            _HWI_STKBOTTOM = GBL_stackbeg + 0x1000 - 4 & ~7;
            _HWI_STKTOP = GBL_stackbeg;
        } > SDRAM
        
        .pinit:   {} > SDRAM
        
        .devtable: {} > SDRAM
        
        .args: fill=0 {
            *(.args)
            . += 0x4;
        } > SDRAM
        
        .rtdx_data: {}  > SDRAM
        
        .rtdx_text: {}  > SDRAM
        
        .hst: {
             HST_A_TABBEG = .;
            _HST_A_TABBEG = .;
            *(.hst)
            HST_A_TABEND = .;
            _HST_A_TABEND = .;
             HST_A_TABLEN = (. - _HST_A_TABBEG) / 20;
            _HST_A_TABLEN = (. - _HST_A_TABBEG) / 20;
        } > SDRAM
        
        .dsm: {} > SDRAM
        
       /* RTA_fromHost buffer */
       .hst1: align = 0x4 {} > SDRAM
        
       /* RTA_toHost buffer */
       .hst0: align = 0x4 {} > SDRAM
        
        .hwi: {}  > SDRAM
        
        .tsk: {
            *(.tsk)
        } > SDRAM
        
        .TSK_idle$stk: {
            *(.TSK_idle$stk)
        } > SDRAM
        
        .log: {
             LOG_A_TABBEG = .;
            _LOG_A_TABBEG = .;
            *(.log)
            LOG_A_TABEND = .;
            _LOG_A_TABEND = .;
             LOG_A_TABLEN = (. - _LOG_A_TABBEG) / 24;
            _LOG_A_TABLEN = (. - _LOG_A_TABBEG) / 24;
        } > SDRAM
        
        .printf (COPY): {} > SDRAM
        
        /* LOG_system buffer */
        .LOG_system$buf: align = 0x1000 fill = 0xffffffff {} > SDRAM
        
        /* trace buffer */
        .trace$buf: align = 0x1000 fill = 0xffffffff {} > SDRAM
        
        .pip: {
             PIP_A_TABBEG = .;
            _PIP_A_TABBEG = .;
            *(.pip)
            PIP_A_TABEND = .;
            _PIP_A_TABEND = .;
             PIP_A_TABLEN = (. - _PIP_A_TABBEG) / 100;
            _PIP_A_TABLEN = (. - _PIP_A_TABBEG) / 100;
        } > SDRAM
        
        .sts: {
             STS_A_TABBEG = .;
            _STS_A_TABBEG = .;
            *(.sts)
            STS_A_TABEND = .;
            _STS_A_TABEND = .;
             STS_A_TABLEN = (. - _STS_A_TABBEG) / 16;
            _STS_A_TABLEN = (. - _STS_A_TABBEG) / 16;
        } > SDRAM
        
        .sys:     {} > SDRAM
        
        .trace: fill = 0x0 {
           _SYS_PUTCBEG = .;
           . += 0x200;
           _SYS_PUTCEND = . - 1;
        } > SDRAM
        
        .gio:     {} > SDRAM
        
        .udev: {} > SDRAM
        
        .SDRAM$heap: {
            SDRAM$B = .;
            _SDRAM_base = .;
            SDRAM$L = 0x10000;
            _SDRAM_length = 0x10000;
            . += 0x10000;
        } > SDRAM
        
}

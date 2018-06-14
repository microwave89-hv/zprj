    
    INCLUDE Token.equ
    INCLUDE Platform.inc
    INCLUDE Ia32.inc

CPU_HEC_BASE    EQU MKF_PCIEX_BASE_ADDRESS  ; Must defined before include Chipset.inc
    INCLUDE Chipset.inc

    INCLUDE SecCore.inc

    .686p
    .xmm
    .model small

    extern  FindMicrocode:NEAR32
    extern  GainestownSecRcEntryEnd:NEAR32

STARTUP_SEG      SEGMENT PARA PUBLIC USE32 'CODE'
                 ASSUME  CS:STARTUP_SEG, DS:STARTUP_SEG

    INCLUDE     SecFlat32.inc

GainestownSecRcEntry        PROC

    jmp     ProtectedModeSECStart       ; Jump to IvyBridge SEC sample code

CallPeiCoreEntryPoint   PROC
    ; Set stack top pointer
    mov     esp, DATA_STACK_BASE_ADDRESS + DATA_STACK_SIZE

    jmp     GainestownSecRcEntryEnd     ; Exit the eLink
CallPeiCoreEntryPoint   ENDP

GainestownSecRcEntry        ENDP

STARTUP_SEG    ENDS
END


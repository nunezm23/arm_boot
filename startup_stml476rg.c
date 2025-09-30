/**
 * @author: Marcos Nunez
 * @date: 29/09/205
 * @version: 1.0.0
 * 
 */

extern unsigned int _stored_data;
extern unsigned int _start_data;
extern unsigned int _end_data;
extern unsigned int _start_bss;
extern unsigned int _end_bss;

extern void *END_STACK;

static int zeroed_variable_in_bss;
static int initialized_variable_in_data = 42;

/**
 * @brief Main program loop
 * 
 */
void main(void) {
    while(1) {
        zeroed_variable_in_bss++;
        initialized_variable_in_data++;
    }
}

void isr_fault(void)
{
    while(1) ;;
}

/**
 * @brief Dummy ISR.
 * 
 */
void isr_empty(void)
{
    /** Nothing here. */
}

/**
 * @brief Bus fault handler.
 * 
 */
void isr_bus_fault(void)
{
    while(1);
}

/**
 * @brief UART0 interrupt handler
 * 
 */
void isr_uart0(void)
{
    while(1);
}

/**
 * @brief Ethernet interrupt handler
 * 
 */
void isr_ethernet(void)
{
    while(1);
}

/**
 * @brief Non-Maskable interrupt
 * 
 */
void isr_nmi(void)
{
    while(1);
}

/**
 * @brief Hard fault handler
 * 
 */
void isr_hard_fault(void)
{
    while(1);
}

/**
 * @brief Memory fault handler
 * 
 */
void isr_mem_fault(void)
{
    while(1);
}

/**
 * @brief Usage interrupt handler
 * 
 */
void isr_usage_fault(void)
{
    while(1);
}

/**
 * @brief Interrupt reset handler
 * @warning Here just copy configure .data and .bss section and then laun main?
 * 
 */
void isr_reset(void) {
    unsigned int *src, *dst;

    /* Copy the .data section from flash to RAM. */
    src = (unsigned int *) &_stored_data;
    dst = (unsigned int *) &_start_data;
    while (dst < (unsigned int *)&_end_data) {
        *dst = *src;
        dst++;
        src++;
    }

    /** Here the BSS section is initialized with zeros. */
    dst = &_start_bss;
    while (dst < (unsigned int *)&_end_bss) {
        *dst = 0U;
        dst++;
    }

    main();
}


/**
 * @brief Interrupt Vector Table
 * 
 */
__attribute__ ((section(".isr_vector")))
void (* const IV[])(void) =
{
    (void (*)(void))(&END_STACK),
    isr_reset,          /** ISR reset handler. */
    isr_nmi,            /** Non-Maskable Interrupt (NMI) */
    isr_hard_fault,     /** Hard fault. */
    isr_mem_fault,      /** Memory exception. */
    isr_bus_fault,      /** Bus fault. */
    isr_usage_fault,    /** Usage fault. */
    0, 0, 0, 0,         /** Reserved x4. */
    isr_empty,          /** Supervisor call. */
    isr_empty,          /** Debug monitor event. */
    0,                  /** Reserved. */
    isr_empty,          /** PendSV call. */
    isr_empty,          /** System tick. */
    /** Interrupts for external peripherals as:  */
    isr_uart0,          /** Uart 0 */
    isr_ethernet,       /** Ethernet ISR */
    /** ... many more external interrupts follow */
};
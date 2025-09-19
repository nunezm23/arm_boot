extern int main(void);

/**
 * @brief Basic implementation for isr_reset function. Here I should to copy or initialize .data and .bss section
 * 
 */
void isr_reset(void)
{
    main();
    while(1);
}

void isr_hard_fault()
{
    while(1);
}

#define IVT_ARRAY_SIZE (48)

typedef void (*isr_t)(void);
static const isr_t ivt[IVT_ARRAY_SIZE] = 
{
    (isr_t)&_stack,
}:
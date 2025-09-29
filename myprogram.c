int main(void)
{
    return 0;
}

extern const uint32_t _stored_data;   // LMA (in FLASH)
extern uint32_t _start_data;          // VMA (in RAM)
extern uint32_t _end_data;

void init_data(void) {
    uint32_t *src = (uint32_t*)&_stored_data;
    uint32_t *dst = (uint32_t*)&_start_data;
    while (dst < (uint32_t*)&_end_data) {
        *dst++ = *src++;
    }
}

extern uint32_t _start_bss;
extern uint32_t _end_bss;

void zero_bss(void) {
    uint32_t *p = (uint32_t*)&_start_bss;
    while (p < (uint32_t*)&_end_bss) {
        *p++ = 0;
    }
}
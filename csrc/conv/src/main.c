#include <pito.h>
#include <stdio.h>
#include "conv2d.h"

#define NUM_HARTS 8
extern int get_pito_hart_id();
extern void wait_for_mvu_irq();
extern void enable_mvu_irq();
static void irq_handler(void) __attribute__ ((interrupt ("machine")));

int layer_out_row_size[] = {4, 4, 4, 4, 2, 2, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0};
int layer_blk_size_kb[] = {9, 9, 9, 9, 18, 36, 36, 36, 72, 144, 144, 144, 288, 576, 576, 576};
// int layer_out_row_size[] = {32, 32, 32, 32, 16, 16, 16, 16, 8, 8, 8, 8, 4, 4, 4, 4};
// int layer_loop_lebgth = [];

void irq_handler(){
    // First things first, disable mvu interrupt ...
    // Clear peending interrup
    __asm__ volatile("addi t1, x0, 1 \n\t\
                     slli t1, t1, 16 \n\t\
                     csrc mip, t1");
    enable_mvu_irq();
}


void main_thread(const int hart_id){
    int iaddr, oaddr, waddr;
    int iofst=0, oofst=0, wofst=0;

    SET_CSR(mtvec, &irq_handler);
    enable_mvu_irq();
    conv3x3_64(hart_id, iofst, oofst, wofst, layer_out_row_size[0], &iaddr, &oaddr, &waddr);
    iofst += *(&iaddr);
    oofst += *(&oaddr);
    wofst += *(&waddr);
    // load_weigths(hart_id);

    conv3x3_64(hart_id, iofst,oofst,wofst, layer_out_row_size[1], &iaddr, &oaddr, &waddr);
    iofst += *(&iaddr);
    oofst += *(&oaddr);
    wofst += *(&waddr);

    if (hart_id==0){
        printf("%d, %d, %d\n", iofst, oofst, wofst);
    }
}

int main(){
    main_thread(get_pito_hart_id());
    return 0;
}

#include "myheader.h"
#include "dma_reg.h"

__bit uart_dma_send_compelete () {
	return BMM_UR1R_AMT == BMM_UR3T_DONE;
}
void uart_dma_init (void* address, u8 size) {
	BMM_UR3T_CFG = B00001010;
	BMM_UR3T_CR  = B10000000;
	BMM_UR3T_AMT = size;    // ���� ch9329 �Ĵ������ݰ�����һ�� sum�����Դ˴��� -1
	ASSIGNMENT16 (BMM_UR3T_TXAH, BMM_UR3T_TXAL, address);
	// BMM_UR3R_CFG = B10001010;
	// BMM_UR3R_CR = B101000001;

}

u8 key_data [70] = {

}


void main () {




}
#ifndef __TBZ_LED88_H_
#define __TBZ_LED88_H_
#define __TBZ_TEST_
// ������� DEBUG �׶Σ���������Щͼ�λᱻд�����
#ifdef __TBZ_TEST_
// �ڵ���LED������ʾһ������
char P1_07_love[] = {
#ifdef __TBZ_BINARY_H_
	B10111101, //    0         0
	B00011000, //  0 0 0     0 0 0
	B00000000, //  0 0 0 0 0 0 0 0
	B00000000, //  0 0 0 0 0 0 0 0
	B00000000, //  0 0 0 0 0 0 0 0
	B10000001, //    0 0 0 0 0 0
	B11000011, //      0 0 0 0
	B11100111  //        0 0
#else
	~0x42, ~0xe7, ~0xff, ~0xff, ~0xff, ~0x7e, ~0x3c, ~0x18
#endif
};
// ���ǵ�����
char P1_07_star[] = {
#ifdef __TBZ_BINARY_H_
	B11101111,
	B11100111,
	B11000011,
	B00000000,
	B11000011,
	B11000011,
	B10010011,
	B10111011
#else
	0xef, 0xe7, 0xc3, 0x00, 0xc3, 0xc3, 0x93, 0xbb
#endif
};
#endif
// �����޸���ʾ������
char P1_07[] = {
	0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff
};
// ��ʾ����
void show_P1_07 (void) {
	for (i = 0; i < 8; i ++) {
		P0 = P1_07_love [i];
		// P0 = P1_07 [i];
		P1 = i;
		delay (1);
		P0 = 0xff;
	}
}
#endif
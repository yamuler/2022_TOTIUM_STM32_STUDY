/*
 * 7segment.h
 *
 *  Created on: 2022. 2. 10.
 *      Author: sikyung
 */

#ifndef INC_7SEGMENT_H_
#define INC_7SEGMENT_H_


#define ON 1
#define OFF 0
#define DIGIT_1ST 0
#define DIGIT_2ND 1
#define DIGIT_3RD 2
#define DIGIT_4TH 3
#define DIGIT_TOTAL DIGIT_1ST|DIGIT_2ND|DIGIT_3RD|DIGIT_4TH

void SevenSeg_GPIO_Init();
void SevenSeg_SetNumber(int digit, int num, int dp);

#endif /* INC_7SEGMENT_H_ */

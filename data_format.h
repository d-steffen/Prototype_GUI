#ifndef __DATA_FORMAT_H__
#define __DATA_FORMAT_H__

struct header_0 {
	unsigned int start		:32;
};

struct header_1 {
	unsigned int no_words		:10;
	unsigned int channelNo		:6;
	unsigned int NU				:3;
	unsigned int RTB			:1;
	unsigned int HS_NU			:12;
};

struct header_2 {
	signed 	 int pedestal		:12;
	unsigned int PSF			:8;
	unsigned int sigma_noise	:12;
};

struct header_3 {
	unsigned int  timestamp		:31; //LSB of timetag in header_1
	unsigned int  err     		:1;
};

struct data_word{
	signed int data0 		:12;
	signed int data1 		:12;
	unsigned int extra 		:8;
};

struct trailer {
	unsigned int trail		:32;
};


#endif

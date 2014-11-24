#ifndef __TREE_FORMAT_H__
#define __TREE_FORMAT_H__

#define NMB_OF_SMPLS 4096 //number of data pieces

struct event_t {
	int eventSize;
	int channelNo;
	int timetag;
	int samples;
	int pedestal;
	int sigma_noise;
	int maximum;
	int smpl[NMB_OF_SMPLS];
};

#endif


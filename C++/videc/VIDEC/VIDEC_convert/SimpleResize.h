#ifndef _SIMPLERESIZE_H_
#define _SIMPLERESIZE_H_

#include "inttypes.h"
#include <windows.h>
typedef int stride_t;
#include "simd.h"

class SimpleResize
{
public:
	struct PVideoFrame
	{
		unsigned char *ptr[4];
		stride_t pitch[4];
		int rowSize[4],height[4];
	};
	struct VideoInfo
	{
		int width,height;
		bool IsYUY2,IsYV12;
	};
private:
	enum
	{
		PLANAR_Y=0,
		PLANAR_U=1,
		PLANAR_V=2
	};
	int newwidth;
	int newheight;
	int oldwidth;
	int oldheight;
	double minslope;
	double hWarp;
	double vWarp;
	unsigned int* hControl;         // weighting masks, alternating dwords for Y & UV
															// 1 qword for mask, 1 dword for src offset, 1 unused dword
	unsigned int* vOffsets;         // Vertical offsets of the source lines we will use
	unsigned int* vWeights;         // weighting masks, alternating dwords for Y & UV
	unsigned int* vOffsetsUV;               // Vertical offsets of the source lines we will use
	unsigned int* vWeightsUV;               // weighting masks, alternating dwords for Y & UV
	unsigned int* vWorkY;           // weighting masks 0Y0Y 0Y0Y...
	unsigned int* vWorkUV;          // weighting masks UVUV UVUV...
	bool SSE2enabled; 
	bool SSEMMXenabled; 
	bool Interlaced; 
	bool DoYV12; 

	int InitTables(void);
	int InitTables_YV12(void);
	void GetFrame_YUY2(const PVideoFrame *src, PVideoFrame *dst, int Planar_Type); 
	void GetFrame_YV12(const PVideoFrame *src, PVideoFrame *dst, int Planar_Type); 

	static double WarpFactor(double z, double wFact);

	static __align16(const int64_t,YMask[2]);
	static __align16(const int64_t,FPround1[2]);
	static __align16(const int64_t,FPround2[2]);
public:
	bool ok;
	SimpleResize(const VideoInfo &vi,unsigned int _width, unsigned int _height, double _hWarp, double _vWarp, bool _Interlaced);
	~SimpleResize();
	void GetFrame(const PVideoFrame *src,PVideoFrame *dst);
};

#endif

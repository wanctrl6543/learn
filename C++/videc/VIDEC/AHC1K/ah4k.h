/*++

Copyright(R) AVCON. All rights reserved.

file:
	ah4k.h

abstract:
	设备接口和IOCTLs

author:
	feichao

time:
	<time>

revision:
	0000 <revision description>

--*/



#include <initguid.h>



// {9E257145-0538-4abb-931E-EC833903C52B}
DEFINE_GUID(GUID_DEVICE_AH4K, 
0x9e257145, 0x538, 0x4abb, 0x93, 0x1e, 0xec, 0x83, 0x39, 0x3, 0xc5, 0x2b);





#define AH4K_TYPE 40001
//
// The IOCTL function codes from 0x800 to 0xFFF are for customer use.
//


#define IOCTL_AH4K_RESET \
    CTL_CODE( AH4K_TYPE, 0x900, METHOD_IN_DIRECT, FILE_ANY_ACCESS  )


#define IOCTL_AH4K_LOAD \
    CTL_CODE( AH4K_TYPE, 0x901, METHOD_BUFFERED, FILE_ANY_ACCESS  )


#define IOCTL_AH4K_SETOPTION \
    CTL_CODE( AH4K_TYPE, 0x902, METHOD_BUFFERED, FILE_ANY_ACCESS  )


#define IOCTL_AH4K_GETOPTION \
    CTL_CODE( AH4K_TYPE, 0x903, METHOD_BUFFERED, FILE_ANY_ACCESS  )



//
//消息机制
//
typedef struct _AH4K_MSG{
	ULONG id;
	ULONG data[15];
}AH4K_MSG,*PAH4K_MSG;


#define IOCTL_AH4K_MSG \
    CTL_CODE( AH4K_TYPE, 0x904, METHOD_BUFFERED, FILE_ANY_ACCESS  )











#ifdef DBG //fre 版本会将移除以下功能


#define IOCTL_ASC8850_INBOUND_WRITE \
	CTL_CODE( AH4K_TYPE, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS  )

#define IOCTL_ASC8850_INBOUND_READ \
	CTL_CODE( AH4K_TYPE, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS  )

#define IOCTL_ASC8850_OUTBOUND0_WRITE \
	CTL_CODE( AH4K_TYPE, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS  )

#define IOCTL_ASC8850_OUTBOUND0_READ \
	CTL_CODE( AH4K_TYPE, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS  )

#define IOCTL_ASC8850_OUTBOUND1_WRITE \
	CTL_CODE( AH4K_TYPE, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS  )

#define IOCTL_ASC8850_OUTBOUND1_READ \
	CTL_CODE( AH4K_TYPE, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS  )

#define IOCTL_ASC8850_INTERRUPT_ASSERT \
	CTL_CODE( AH4K_TYPE, 0x806, METHOD_NEITHER, FILE_ANY_ACCESS  )

#define IOCTL_ASC8850_INTERRUPT_HOOK \
	CTL_CODE( AH4K_TYPE, 0x807, METHOD_NEITHER, FILE_ANY_ACCESS  )

#endif

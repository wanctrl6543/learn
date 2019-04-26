// intrface.h
//
// Generated by C DriverWizard 3.2.0 (Build 2485)
// Requires DDK Only
// File created on 9/29/2007
//
// Define an Interface Guid for DM64 device class.
// This GUID is used to register (IoRegisterDeviceInterface)
// an instance of an interface so that user application
// can control the DM64 device.
//
//  {24131E5D-D439-4BC0-9574-8DF65A983FF9}
DEFINE_GUID(GUID_DEVINTERFACE_DM64,
    0x24131E5D, 0xD439, 0x4BC0, 0x95, 0x74, 0x8D, 0xF6, 0x5A, 0x98, 0x3F, 0xF9);

// Define a Setup Class GUID for DM64 Class. This is same
// as the DM64 CLASS guid in the INF files.
//
//  {FC3320A4-7A1D-4E70-9C5C-5998670F84EC}
DEFINE_GUID(GUID_DEVCLASS_DM64,
    0xFC3320A4, 0x7A1D, 0x4E70, 0x9C, 0x5C, 0x59, 0x98, 0x67, 0x0F, 0x84, 0xEC);

// GUID definition are required to be outside of header inclusion pragma to avoid
// error during precompiled headers.
//

#ifndef __INTRFACE_H__
#define __INTRFACE_H__

#define FILE_DEVICE_DM64  0x8000

// Define Interface reference/dereference routines for
// Interfaces exported by IRP_MN_QUERY_INTERFACE

#define DM64_IOCTL(index) \
    CTL_CODE(FILE_DEVICE_DM64, index, METHOD_BUFFERED, FILE_READ_DATA)

#define IOCTL_WARMRESET \
	CTL_CODE(FILE_DEVICE_DM64, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_RUN \
	CTL_CODE(FILE_DEVICE_DM64, 0x801, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_INITEMIF \
	CTL_CODE(FILE_DEVICE_DM64, 0x802, METHOD_OUT_DIRECT, FILE_WRITE_ACCESS)
#define IOCTL_LOAD \
	CTL_CODE(FILE_DEVICE_DM64, 0x803, METHOD_OUT_DIRECT, FILE_WRITE_ACCESS)
#define IOCTL_HOOK \
	CTL_CODE(FILE_DEVICE_DM64, 0x804, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_UNHOOK \
	CTL_CODE(FILE_DEVICE_DM64, 0x805, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
#define IOCTL_POST_MSG \
	CTL_CODE(FILE_DEVICE_DM64, 0x806, METHOD_OUT_DIRECT, FILE_WRITE_ACCESS)
#define IOCTL_RETRIEVE_MSG \
	CTL_CODE(FILE_DEVICE_DM64, 0x807, METHOD_IN_DIRECT, FILE_READ_ACCESS)
#endif // __INTRFACE_H__
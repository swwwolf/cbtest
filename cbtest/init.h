/* This is free and unencumbered software released into the public domain. */

#ifndef CBTEST_INIT_H_
#define CBTEST_INIT_H_

#include <ntifs.h>

#define POOL_TAG 'stbC'
extern "C" PUSHORT NtBuildNumber;

#ifdef __cplusplus
extern "C" {
#endif

    DRIVER_INITIALIZE DriverEntry;
    void NTAPI        DriverUnload(IN PDRIVER_OBJECT driver);

#ifdef __cplusplus
}
#endif

#endif  // CBTEST_INIT_H_

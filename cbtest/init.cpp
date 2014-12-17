/* This is free and unencumbered software released into the public domain. */

#include <ntifs.h>

#include "init.h"
#include "pscbacks.h"

#ifdef ALLOC_PRAGMA
    #pragma alloc_text(INIT, DriverEntry)
    #pragma alloc_text(PAGECODE, DriverUnload)
#endif

NTSTATUS NTAPI DriverEntry(IN PDRIVER_OBJECT driver, IN PUNICODE_STRING driverKeyName) {
    NTSTATUS status;

    UNREFERENCED_PARAMETER(driverKeyName);

    // DbgBreakPoint();

    status = SetLoadImageNotifyRoutine(LoadImageNotifyRoutine);

    if ( !NT_SUCCESS(status) )
        DbgPrint("Failed to set load image notify routine, status = 0x%08X\n", status);
    else
        DbgPrint("Succeed to set load image notify routine, status = 0x%08X\n", status);

    status = SetRemoveCreateProcessNotifyRoutine(FALSE);

    if ( !NT_SUCCESS(status) )
        DbgPrint("Failed to set create process notify routine, status = 0x%08X\n", status);
    else
        DbgPrint("Succeed to set create process notify routine, status = 0x%08X\n", status);

    status = SetCreateThreadNotifyRoutine(CreateThreadNotifyRoutine);

    if ( !NT_SUCCESS(status) )
        DbgPrint("Failed to set create thread notify routine, status = 0x%08X\n", status);
    else
        DbgPrint("Succeed to set create thread notify routine, status = 0x%08X\n", status);

    driver->DriverUnload = DriverUnload;

    return STATUS_SUCCESS;
}

VOID NTAPI DriverUnload(IN PDRIVER_OBJECT driver) {
    NTSTATUS status;

    PAGED_CODE();

    UNREFERENCED_PARAMETER(driver);

    status = RemoveLoadImageNotifyRoutine(LoadImageNotifyRoutine);

    if ( !NT_SUCCESS(status) )
        DbgPrint("Failed to remove load image notify routine, status = 0x%08X\n", status);
    else
        DbgPrint("Succeed to remove load image notify routine, status = 0x%08X\n", status);

    status = SetRemoveCreateProcessNotifyRoutine(TRUE);

    if ( !NT_SUCCESS(status) )
        DbgPrint("Failed to remove create process notify routine, status = 0x%08X\n", status);
    else
        DbgPrint("Succeed to remove create process notify routine, status = 0x%08X\n", status);

    status = RemoveCreateThreadNotifyRoutine(CreateThreadNotifyRoutine);

    if ( !NT_SUCCESS(status) )
        DbgPrint("Failed to remove thread notify routine, status = 0x%08X\n", status);
    else
        DbgPrint("Succeed to remove thread notify routine, status = 0x%08X\n", status);
}

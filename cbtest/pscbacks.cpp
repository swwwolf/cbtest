/* This is free and unencumbered software released into the public domain. */

#include "init.h"
#include "pscbacks.h"

#ifdef ALLOC_PRAGMA
    #pragma alloc_text(PAGECODE, SetLoadImageNotifyRoutine)
    #pragma alloc_text(PAGECODE, RemoveLoadImageNotifyRoutine)
    #pragma alloc_text(PAGECODE, LoadImageNotifyRoutine)
    #pragma alloc_text(PAGECODE, SetRemoveCreateProcessNotifyRoutine)
    #pragma alloc_text(PAGECODE, CreateProcessNotifyRoutine)
    #pragma alloc_text(PAGECODE, CreateProcessNotifyRoutineEx)
    #pragma alloc_text(PAGECODE, SetCreateThreadNotifyRoutine)
    #pragma alloc_text(PAGECODE, RemoveCreateThreadNotifyRoutine)
    #pragma alloc_text(PAGECODE, CreateThreadNotifyRoutine)
#endif

//////////////////////////////////////////////////////////////////////////
NTSTATUS SetLoadImageNotifyRoutine(IN PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine) {
    PAGED_CODE();

    if ( !NotifyRoutine )
        return STATUS_INVALID_PARAMETER;

    return PsSetLoadImageNotifyRoutine(NotifyRoutine);
}

NTSTATUS RemoveLoadImageNotifyRoutine(IN PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine) {
    PAGED_CODE();

    if ( !NotifyRoutine )
        return STATUS_INVALID_PARAMETER;

    return PsRemoveLoadImageNotifyRoutine(NotifyRoutine);
}

VOID LoadImageNotifyRoutine(IN PUNICODE_STRING FullImageName, IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo) {
    PAGED_CODE();

    UNREFERENCED_PARAMETER(ImageInfo);

    DbgPrint("LoadImageNotifyRoutine called with FullImageName = %wZ, ProcessId = 0x%p\n", FullImageName, ProcessId);
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
NTSTATUS SetRemoveCreateProcessNotifyRoutine(IN BOOLEAN IsRemove) {
    NTSTATUS status;

    PAGED_CODE();

    DECLARE_CONST_UNICODE_STRING(szCreateProcessEx, L"PsSetCreateProcessNotifyRoutineEx");

    PSSETCREATEPROCESSNOTIFYROUTINEEX_PROC pCreateProcessEx = (PSSETCREATEPROCESSNOTIFYROUTINEEX_PROC)
        MmGetSystemRoutineAddress((PUNICODE_STRING)&szCreateProcessEx);

    if ( pCreateProcessEx )
        status = pCreateProcessEx(CreateProcessNotifyRoutineEx, IsRemove);
    else
        status = PsSetCreateProcessNotifyRoutine(CreateProcessNotifyRoutine, IsRemove);

    if ( !NT_SUCCESS(status) )
        DbgPrint("%s:%d failed with status = 0x%08X\n", __FUNCTION__, __LINE__, status);

    DECLARE_CONST_UNICODE_STRING(szCreateProcessEx2, L"PsSetCreateProcessNotifyRoutineEx2");

    PSSETCREATEPROCESSNOTIFYROUTINEEX2_PROC pCreateProcessEx2 = (PSSETCREATEPROCESSNOTIFYROUTINEEX2_PROC)
        MmGetSystemRoutineAddress((PUNICODE_STRING)&szCreateProcessEx2);

    if ( pCreateProcessEx2 )
        status = pCreateProcessEx2(PsCreateProcessNotifyPico, CreateProcessNotifyRoutineEx2, IsRemove);

    if ( !NT_SUCCESS(status) )
        DbgPrint("%s:%d failed with status = 0x%08X\n", __FUNCTION__, __LINE__, status);

    return status;
}

VOID CreateProcessNotifyRoutine(IN HANDLE ParentId, IN HANDLE ProcessId, IN BOOLEAN Create) {
    PAGED_CODE();

    DbgPrint("CreateProcessNotifyRoutine called with ParentId = 0x%p, ProcessId = 0x%p, Create = %d\n",
             ParentId,
             ProcessId,
             Create);
}

VOID CreateProcessNotifyRoutineEx(IN OUT PEPROCESS Process,
                                  IN HANDLE ProcessId,
                                  IN OPTIONAL PPS_CREATE_NOTIFY_INFO CreateInfo) {
    PAGED_CODE();

    if ( CreateInfo ) {
        DbgPrint("%s called with Process = 0x%p, ProcessId = 0x%p, ImageFileName = %wZ, CommandLine = %wZ\n",
                 __FUNCTION__,
                 Process,
                 ProcessId,
                 CreateInfo->ImageFileName,
                 CreateInfo->CommandLine);
    } else {
        DbgPrint("%s called with Process = 0x%p, ProcessId = 0x%p\n", __FUNCTION__, Process, ProcessId);
    }
}

VOID CreateProcessNotifyRoutineEx2(IN OUT PEPROCESS Process,
                                   IN HANDLE ProcessId,
                                   IN OPTIONAL PPS_CREATE_NOTIFY_INFO CreateInfo) {
    PAGED_CODE();

    DbgBreakPoint();

    if ( CreateInfo ) {
        DbgPrint("%s called with Process = 0x%p, ProcessId = 0x%p, ImageFileName = %wZ, CommandLine = %wZ\n",
                 __FUNCTION__,
                 Process,
                 ProcessId,
                 CreateInfo->ImageFileName,
                 CreateInfo->CommandLine);
    } else {
        DbgPrint("%s called with Process = 0x%p, ProcessId = 0x%p\n", __FUNCTION__, Process, ProcessId);
    }
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
NTSTATUS SetCreateThreadNotifyRoutine(IN PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine) {
    PAGED_CODE();

    if ( !NotifyRoutine )
        return STATUS_INVALID_PARAMETER;

    return PsSetCreateThreadNotifyRoutine(NotifyRoutine);
}

VOID CreateThreadNotifyRoutine(IN HANDLE ProcessId, IN HANDLE ThreadId, IN BOOLEAN Create) {
    PAGED_CODE();

    DbgPrint("CreateThreadNotifyRoutine called with ProcessId = 0x%p, ThreadId = 0x%p, Create = %d\n",
             ProcessId,
             ThreadId,
             Create);
}

NTSTATUS RemoveCreateThreadNotifyRoutine(IN PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine) {
    PAGED_CODE();

    if ( !NotifyRoutine )
        return STATUS_INVALID_PARAMETER;

    return PsRemoveCreateThreadNotifyRoutine(NotifyRoutine);
}
//////////////////////////////////////////////////////////////////////////

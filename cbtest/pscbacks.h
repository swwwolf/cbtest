/* This is free and unencumbered software released into the public domain. */

#ifndef CBTEST_PSCBACKS_H_
#define CBTEST_PSCBACKS_H_

typedef NTSTATUS (NTAPI* PSSETCREATEPROCESSNOTIFYROUTINEEX_PROC)(
    IN PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine,
    IN BOOLEAN Remove);

typedef enum _PSCREATEPROCESSNOTIFYTYPE {
    PsCreateProcessNotifyPico = 0
} PSCREATEPROCESSNOTIFYTYPE;

typedef NTSTATUS (NTAPI* PSSETCREATEPROCESSNOTIFYROUTINEEX2_PROC)(
    IN PSCREATEPROCESSNOTIFYTYPE NotifyType,
    IN PVOID NotifyInformation,
    IN BOOLEAN Remove);

#ifdef __cplusplus
extern "C" {
#endif
    //////////////////////////////////////////////////////////////////////////
    NTSTATUS SetLoadImageNotifyRoutine(IN PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine);
    NTSTATUS RemoveLoadImageNotifyRoutine(IN PLOAD_IMAGE_NOTIFY_ROUTINE NotifyRoutine);
    VOID     LoadImageNotifyRoutine(IN PUNICODE_STRING FullImageName, IN HANDLE ProcessId, IN PIMAGE_INFO ImageInfo);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    NTSTATUS SetRemoveCreateProcessNotifyRoutine(IN BOOLEAN IsRemove);
    VOID     CreateProcessNotifyRoutine(IN HANDLE ParentId, IN HANDLE ProcessId, IN BOOLEAN Create);
    VOID     CreateProcessNotifyRoutineEx(IN OUT PEPROCESS Process, IN HANDLE ProcessId,
                                          IN OPTIONAL PPS_CREATE_NOTIFY_INFO CreateInfo);
    VOID     CreateProcessNotifyRoutineEx2(IN OUT PEPROCESS Process, IN HANDLE ProcessId,
                                           IN OPTIONAL PPS_CREATE_NOTIFY_INFO CreateInfo);
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    NTSTATUS SetCreateThreadNotifyRoutine(IN PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine);
    NTSTATUS RemoveCreateThreadNotifyRoutine(IN PCREATE_THREAD_NOTIFY_ROUTINE NotifyRoutine);
    VOID     CreateThreadNotifyRoutine(IN HANDLE ProcessId, IN HANDLE ThreadId, IN BOOLEAN Create);
    //////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#endif  // CBTEST_PSCBACKS_H_

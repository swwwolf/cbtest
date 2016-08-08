/* This is free and unencumbered software released into the public domain. */

#ifndef CBTEST_PSCBACKS_H_
#define CBTEST_PSCBACKS_H_

typedef NTSTATUS (NTAPI* PSSETCREATEPROCESSNOTIFYROUTINEEX_PROC)(
    IN PCREATE_PROCESS_NOTIFY_ROUTINE_EX NotifyRoutine,
    IN BOOLEAN Remove);

typedef enum _PSCREATEPROCESSNOTIFYTYPE {
    PsCreateProcessNotifyPico = 0
} PSCREATEPROCESSNOTIFYTYPE;

typedef struct _PS_CREATE_NOTIFY_INFO_EX {
    _In_ SIZE_T Size;
    union {
        _In_ ULONG Flags;
        struct {
            _In_ ULONG FileOpenNameAvailable : 1;
            _In_ ULONG Reserved : 30;
            _In_ ULONG Pico : 1;
        };
    };
    _In_ HANDLE ParentProcessId;
    _In_ CLIENT_ID CreatingThreadId;
    _Inout_ struct _FILE_OBJECT *FileObject;
    _In_ PCUNICODE_STRING ImageFileName;
    _In_opt_ PCUNICODE_STRING CommandLine;
    _Inout_ NTSTATUS CreationStatus;
} PS_CREATE_NOTIFY_INFO_EX, *PPS_CREATE_NOTIFY_INFO_EX;

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
    VOID     CreateProcessNotifyRoutineEx(IN OUT PEPROCESS Process,
                                          IN HANDLE ProcessId,
                                          IN OPTIONAL PPS_CREATE_NOTIFY_INFO CreateInfo);
    VOID     CreateProcessNotifyRoutineEx2(IN OUT PEPROCESS Process,
                                           IN HANDLE ProcessId,
                                           IN OPTIONAL PPS_CREATE_NOTIFY_INFO_EX CreateInfo);
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

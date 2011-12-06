/* ========================================================================
 *
 * SAMPLE SOURCE CODE - SUBJECT TO THE TERMS OF END-USER LICENSE AGREEMENT
 * FOR INTEL(R) PARALLEL ADVISOR LITE.
 *
 * Copyright 2009 Intel Corporation
 *
 * THIS FILE IS PROVIDED "AS IS" WITH NO WARRANTIES, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO ANY IMPLIED WARRANTY OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT OF INTELLECTUAL
 * PROPERTY RIGHTS.
 *
 * ========================================================================
 */

/* This file defines macros and inline functions used by
 * the Intel(R) Parallel Advisor Lite "Correctness Modeling" analysis,
 * and are in described in the "Annotations" section of the help.
 */

#pragma once

/* This type is used to define Lock ID values - specifically, when
 * the user has dynamically allocated lock IDs and needs a type
 * to hold the values.  (This type is also TCINT.)
 */
typedef int ANNOTATE_LOCKID;

/* Some people may find it useful to have no expansion for annotations,
 * if you have a project that you want to build without any annotation
 * effects at all.  (e.g. if you have a project where you want to have
 * some annotations in a shared source pool, but only particular developers
 * actually building with the annotations enabled.
 * Defining ANNOTATE_EXPAND_NULL avoids declaring comdat routines,
 * and avoids any textual expansion for annotation macros.
 */
#ifdef ANNOTATE_EXPAND_NULL

#define ANNOTATE_SITE_BEGIN   {
#define ANNOTATE_SITE_END     }
#define ANNOTATE_TASK_BEGIN   {
#define ANNOTATE_TASK_END     }
#define ANNOTATE_LOCK_ACQUIRE(_ID)
#define ANNOTATE_LOCK_RELEASE(_ID)
#define ANNOTATE_LOCKID_ALLOCATE(_ID)
#define ANNOTATE_LOCKID_DEALLOCATE(_ID)
#define ANNOTATE_MEMORY_ALLOCATION(_PTR, _SIZE)
#define ANNOTATE_MEMORY_DEALLOCATION(_PTR)
#define ANNOTATE_CRITICAL_BEGIN(_ID)  {
#define ANNOTATE_CRITICAL_END         }
#define ANNOTATE_OBSERVE_USES(_PTR)

#else

#include <stdlib.h>
#include <assert.h>

/* windows.h is required for LoadLibrary and GetProcSymbol.
 * If this triggers problems building your application, you
 * can consider adding:
 *  #define WIN32_LEAN_AND_MEAN
 * prior to including annotate.h in your code.
 * Note that this is only to get 4 definitions:
 * LoadLibrary, GetProcAddress, HINSTANCE and TEXT
 */
#include <windows.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* The standard mode of operation is to use support routines in TcWhatIf.dll.
 * If you need to avoid using this dll for some reason, you can utilize
 * the (unsupported) ANNOTATE_EXPAND_INLINE option.
 * Note that this option will only work if your annotations are all
 * in the main image, not in a dll.
 */
#ifndef ANNOTATE_EXPAND_INLINE

/*** Use the routines in TcWhatIf.dll. ***/

/* Basic approach:
 * For the case of calling the dll, there is an __AnnotateRoutine function
 * declared as a comdat in each compilation unit with annotations present.
 * That routine in turn has an internal static structure that is initialized
 * once to contain the address of functions occuring in TcWhatIf.dll.
 * Each time an annotation macro is invoked, that causes a call to the
 * __AnnotateRoutine function to get addresses of the routines, followed
 * by calling the specific routine, provided the address is non-null.
 */

#define _ANNOTATE_CALL_PREFIX(_BASENAME) _Annotate##_BASENAME

/* This set of macros generates calls that are part of application images,
 * which call the __TcXxx routines in the dynamically loaded TcWhatIf.dll.
 */
#define _ANNOTATE_DECLARE_0(_BASENAME) \
typedef void (*_ANNOTATE_##_BASENAME##_t)(); \
extern void __Tc##_BASENAME();

#define _ANNOTATE_CALL_0(_BASENAME) \
{   _ANNOTATE_##_BASENAME##_t fp = __AnnotateRoutine()->_BASENAME; \
    if (fp) fp(); }

#define _ANNOTATE_DECLARE_1(_BASENAME, _P1TYPE) \
typedef void (*_ANNOTATE_##_BASENAME##_t)(_P1TYPE p1); \
extern void __Tc##_BASENAME(_P1TYPE p1);

#define _ANNOTATE_CALL_1(_BASENAME, _P1) \
{   _ANNOTATE_##_BASENAME##_t fp = __AnnotateRoutine()->_BASENAME; \
    if (fp) fp(_P1); }

#define _ANNOTATE_DECLARE_2(_BASENAME, _P1TYPE, _P2TYPE) \
typedef void (*_ANNOTATE_##_BASENAME##_t)(_P1TYPE p1, _P2TYPE p2); \
extern void __Tc##_BASENAME(_P1TYPE p1, _P2TYPE p2);

#define _ANNOTATE_CALL_2(_BASENAME, _P1, _P2) \
{   _ANNOTATE_##_BASENAME##_t fp = __AnnotateRoutine()->_BASENAME; \
    if (fp) fp(_P1, _P2); }

#else

/*** Use local routines rather than TcWhatIf.dll. ***/

/* For this case, declare the routines directly.
 * (e.g. this declares __TcBeginTask as a comdat routine in the current
 * compilation unit.)
 * Note: While this works for a main image (only), this is not the supported
 * mode of operation.
 */


/* Create a COMDAT routine that will not actually be inlined by either
 * the MS or Intel compilers.  __declspec(noinline) is supposed to suppress
 * inlining, but it still occurs in some cases.  The volatile variable and
 * operation in the routine body appears to be sufficient to get the compilers
 * to honor the __declspec(noinline) in practice.
 */
#define _ANNOTATE_DECLARE_0(_BASENAME) \
    extern __inline __declspec(noinline) void __Tc##_BASENAME() { volatile int i = 0; i++; }

#define _ANNOTATE_CALL_0(_BASENAME) \
    { __Tc##_BASENAME(); }

#define _ANNOTATE_DECLARE_1(_BASENAME, _P1TYPE) \
    extern __inline __declspec(noinline) void __Tc##_BASENAME(_P1TYPE p1) { volatile int i = 0; i++; }

#define _ANNOTATE_CALL_1(_BASENAME, _P1) \
    { __Tc##_BASENAME(_P1); }

#define _ANNOTATE_DECLARE_2(_BASENAME, _P1TYPE, _P2TYPE) \
    extern __inline __declspec(noinline) void __Tc##_BASENAME(_P1TYPE p1, _P2TYPE p2) { volatile int i = 0; i++; }

#define _ANNOTATE_CALL_2(_BASENAME, _P1, _P2) \
    { __Tc##_BASENAME(_P1, _P2); }

#endif

/*** Declare routines appropriately based on usage style ***/

/* Depending on above, this will either expand to comdats that are
 * used directly, or comdats that call routines in TcWhatIf.dll
 */
_ANNOTATE_DECLARE_0(BeginConcurrencySite)
_ANNOTATE_DECLARE_0(EndConcurrencySite)
_ANNOTATE_DECLARE_0(BeginTask)
_ANNOTATE_DECLARE_0(EndTask)
_ANNOTATE_DECLARE_1(SetRecursiveLock,        ANNOTATE_LOCKID)
_ANNOTATE_DECLARE_1(UnsetRecursiveLock,      ANNOTATE_LOCKID)
_ANNOTATE_DECLARE_1(AllocateRecursiveLock,   ANNOTATE_LOCKID*)
_ANNOTATE_DECLARE_1(DeallocateRecursiveLock, ANNOTATE_LOCKID)
_ANNOTATE_DECLARE_2(RecordAllocation,        void*, size_t)
_ANNOTATE_DECLARE_1(RecordDeallocation,      void*)
_ANNOTATE_DECLARE_2(ObserveUses,             void*, size_t)

#ifndef ANNOTATE_EXPAND_INLINE

/* All of the symbols potentially in the library
 */
struct __AnnotateRoutines {
    _ANNOTATE_BeginConcurrencySite_t    BeginConcurrencySite;
    _ANNOTATE_EndConcurrencySite_t      EndConcurrencySite;
    _ANNOTATE_BeginTask_t               BeginTask;
    _ANNOTATE_EndTask_t                 EndTask;
    _ANNOTATE_SetRecursiveLock_t        SetRecursiveLock;
    _ANNOTATE_UnsetRecursiveLock_t      UnsetRecursiveLock;
    _ANNOTATE_AllocateRecursiveLock_t   AllocateRecursiveLock;
    _ANNOTATE_DeallocateRecursiveLock_t DeallocateRecursiveLock;
    _ANNOTATE_RecordAllocation_t        RecordAllocation;
    _ANNOTATE_RecordDeallocation_t      RecordDeallocation;
    _ANNOTATE_ObserveUses_t             ObserveUses;
};

/* This routine is called to get the address of an initialized
 * vector of function pointers for the annotation routines.
 * (This might be done differently if it weren't designed to work
 * with either C or C++...)
 */
__inline struct __AnnotateRoutines* __AnnotateRoutine() {

    /* Initialized by first invocation
     * This assumes that the code here can be executed successfully
     * by multiple threads, should that ever happen.
     */
    static int initialized = 0;
    static struct __AnnotateRoutines tc;

    HINSTANCE tclib;

    if (initialized) return &tc;

    tclib = LoadLibrary(TEXT("TcWhatIf.dll"));
    if (tclib) {
        tc.BeginConcurrencySite     = (_ANNOTATE_BeginConcurrencySite_t)   GetProcAddress(tclib, "__TcBeginConcurrencySite");
        assert(tc.BeginConcurrencySite);
        tc.EndConcurrencySite       = (_ANNOTATE_EndConcurrencySite_t)     GetProcAddress(tclib, "__TcEndConcurrencySite");
        assert(tc.EndConcurrencySite);
        tc.BeginTask                = (_ANNOTATE_BeginTask_t)              GetProcAddress(tclib, "__TcBeginTask");
        assert(tc.BeginTask);
        tc.EndTask                  = (_ANNOTATE_EndTask_t)                GetProcAddress(tclib, "__TcEndTask");
        assert(tc.EndTask);
        tc.SetRecursiveLock         = (_ANNOTATE_SetRecursiveLock_t)       GetProcAddress(tclib, "__TcSetRecursiveLock");
        assert(tc.SetRecursiveLock);
        tc.UnsetRecursiveLock       = (_ANNOTATE_UnsetRecursiveLock_t)     GetProcAddress(tclib, "__TcUnsetRecursiveLock");
        assert(tc.UnsetRecursiveLock);
        tc.AllocateRecursiveLock    = (_ANNOTATE_AllocateRecursiveLock_t)  GetProcAddress(tclib, "__TcAllocateRecursiveLock");
        assert(tc.AllocateRecursiveLock);
        tc.DeallocateRecursiveLock  = (_ANNOTATE_DeallocateRecursiveLock_t)GetProcAddress(tclib, "__TcDeallocateRecursiveLock");
        assert(tc.DeallocateRecursiveLock);
        tc.RecordAllocation         = (_ANNOTATE_RecordAllocation_t)       GetProcAddress(tclib, "__TcRecordAllocation");
        assert(tc.RecordAllocation);
        tc.RecordDeallocation       = (_ANNOTATE_RecordDeallocation_t)     GetProcAddress(tclib, "__TcRecordDeallocation");
        assert(tc.RecordDeallocation);
        tc.ObserveUses              = (_ANNOTATE_ObserveUses_t)            GetProcAddress(tclib, "__TcObserveUses");
        assert(tc.ObserveUses);
    }

    initialized = 1;

    return &tc;
}

#endif

/* Mark the start of a site (region) to be analyzed by the tool */
#define ANNOTATE_SITE_BEGIN { _ANNOTATE_CALL_0(BeginConcurrencySite) {

/* Mark the end of a site (region) to be analyzed by the tool and indicate a WaitForAll task synchronization */
#define ANNOTATE_SITE_END } _ANNOTATE_CALL_0(EndConcurrencySite) }

/* Mark the beginning of a region of code that constitutes a task */
#define ANNOTATE_TASK_BEGIN { _ANNOTATE_CALL_0(BeginTask) {

/* Mark the end of a region of code that constitutes a task */
#define ANNOTATE_TASK_END } _ANNOTATE_CALL_0(EndTask) }

/* Acquire a lock identified by lockId */
#define ANNOTATE_LOCK_ACQUIRE(_ID) _ANNOTATE_CALL_1(SetRecursiveLock, _ID)

/* Release a lock identified by lockId */
#define ANNOTATE_LOCK_RELEASE(_ID) _ANNOTATE_CALL_1(UnsetRecursiveLock, _ID)

/* Allocate a lock */
#if defined(__cplusplus)
#define ANNOTATE_LOCKID_ALLOCATE(_ID) { _AnnotateAllocateRecursiveLock2(_ID); }
#else
#define ANNOTATE_LOCKID_ALLOCATE(_ID) _ANNOTATE_CALL_1(AllocateRecursiveLock, _ID)
#endif

/* Deallocate a lock */
#define ANNOTATE_LOCKID_DEALLOCATE(_ID) _ANNOTATE_CALL_1(DeallocateRecursiveLock, _ID)

/* Record user allocation of memory */
#define ANNOTATE_MEMORY_ALLOCATION(_PTR, _SIZE) _ANNOTATE_CALL_2(RecordAllocation, _PTR, _SIZE)

/* Record user deallocation of memory */
#define ANNOTATE_MEMORY_DEALLOCATION(_PTR) _ANNOTATE_CALL_1(RecordDeallocation, _PTR)

/* Record all observations of uses */
#define ANNOTATE_OBSERVE_USES(_PTR) _ANNOTATE_CALL_2(ObserveUses, &(_PTR), sizeof(_PTR))

#if defined(__cplusplus)
}
#endif

/* Some C++ wrappers for more convenient use */
#if defined(__cplusplus)
inline void _AnnotateAllocateRecursiveLock2(ANNOTATE_LOCKID * lockId) _ANNOTATE_CALL_1(AllocateRecursiveLock, lockId)
inline void _AnnotateAllocateRecursiveLock2(ANNOTATE_LOCKID & lockId) _ANNOTATE_CALL_1(AllocateRecursiveLock, &lockId)

struct ANNOTATE_UNIQUE_LOCKID {
    ANNOTATE_LOCKID _lockId;
     ANNOTATE_UNIQUE_LOCKID() { ANNOTATE_LOCKID_ALLOCATE  (_lockId); }
    ~ANNOTATE_UNIQUE_LOCKID() { ANNOTATE_LOCKID_DEALLOCATE(_lockId); }
    operator ANNOTATE_LOCKID() { return _lockId; }
};

struct _AnnotateCriticalLock {
    ANNOTATE_LOCKID _id;
    _AnnotateCriticalLock(ANNOTATE_LOCKID id)
                           : _id(id)  { _ANNOTATE_CALL_1(SetRecursiveLock, _id) }
    ~_AnnotateCriticalLock()          { _ANNOTATE_CALL_1(UnsetRecursiveLock, _id) }
};

#define ANNOTATE_CRITICAL_BEGIN(_ID)  { _AnnotateCriticalLock _annotateCriticalLock(_ID);
#define ANNOTATE_CRITICAL_END         }
#endif

#endif

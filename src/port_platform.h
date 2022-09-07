#ifndef PORT_PLATFORM_H_
#define PORT_PLATFORM_H_

// IWYU pragma: private, include <grpc/support/port_platform.h>

/*
 * Define C_BACKWARDS_COMPATIBILITY_MODE to try harder to be ABI
 * compatible with older platforms (currently only on Linux)
 * Causes:
 *  - some libc calls to be gotten via dlsym
 *  - some syscalls to be made directly
 */

// [[deprecated]] attribute is only available since C++14
#if __cplusplus >= 201402L
#define GRPC_DEPRECATED(reason) [[deprecated(reason)]]
#else
#define GRPC_DEPRECATED(reason)
#endif  // __cplusplus >= 201402L

/*
 * Defines C_ABSEIL_SYNC to use synchronization features from Abseil
 */
#ifndef C_ABSEIL_SYNC
#if defined(__APPLE__)
// This is disabled on Apple platforms because macos/grpc_basictests_c_cpp
// fails with this. https://github.com/grpc/grpc/issues/23661
#else
#define C_ABSEIL_SYNC 1
#endif
#endif  // C_ABSEIL_SYNC

/* Get windows.h included everywhere (we need it) */
#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED
#define WIN32_LEAN_AND_MEAN
#endif /* WIN32_LEAN_AND_MEAN */

#ifndef NOMINMAX
#define GRPC_NOMINMX_WAS_NOT_DEFINED
#define NOMINMAX
#endif /* NOMINMAX */

#include <windows.h>

#ifndef _WIN32_WINNT
#error \
    "Please compile grpc with _WIN32_WINNT of at least 0x600 (aka Windows Vista)"
#else /* !defined(_WIN32_WINNT) */
#if (_WIN32_WINNT < 0x0600)
#error \
    "Please compile grpc with _WIN32_WINNT of at least 0x600 (aka Windows Vista)"
#endif /* _WIN32_WINNT < 0x0600 */
#endif /* defined(_WIN32_WINNT) */

#ifdef GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED
#undef GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED
#undef WIN32_LEAN_AND_MEAN
#endif /* GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED */

#ifdef GRPC_NOMINMAX_WAS_NOT_DEFINED
#undef GRPC_NOMINMAX_WAS_NOT_DEFINED
#undef NOMINMAX
#endif /* GRPC_WIN32_LEAN_AND_MEAN_WAS_NOT_DEFINED */
#endif /* defined(_WIN64) || defined(WIN64) || defined(_WIN32) || \
          defined(WIN32) */

/* Override this file with one for your platform if you need to redefine
   things.  */

#if !defined(C_NO_AUTODETECT_PLATFORM)
#if defined(_WIN64) || defined(WIN64) || defined(_WIN32) || defined(WIN32)
#if defined(_WIN64) || defined(WIN64)
#define C_ARCH_64 1
#else
#define C_ARCH_32 1
#endif
#define C_PLATFORM_STRING "windows"
#define C_WINDOWS 1
#define C_WINDOWS_SUBPROCESS 1
#define C_WINDOWS_ENV
#ifdef __MSYS__
#define C_GETPID_IN_UNISTD_H 1
#define C_MSYS_TMPFILE
#define C_POSIX_LOG
#define C_POSIX_STRING
#define C_POSIX_TIME
#else
#define C_GETPID_IN_PROCESS_H 1
#define C_WINDOWS_TMPFILE
#define C_WINDOWS_LOG
#define C_WINDOWS_CRASH_HANDLER 1
#define C_WINDOWS_STAT
#define C_WINDOWS_STRING
#define C_WINDOWS_TIME
#endif
#ifdef __GNUC__
#define C_GCC_ATOMIC 1
#else
#define C_WINDOWS_ATOMIC 1
#endif
#elif defined(ANDROID) || defined(__ANDROID__)
#define C_PLATFORM_STRING "android"
#define C_ANDROID 1
#ifndef __ANDROID_API__
#error "__ANDROID_API__ must be defined for Android builds."
#endif
#if __ANDROID_API__ < 21
#error "Requires Android API v21 and above"
#endif
#define C_SUPPORT_BINDER_TRANSPORT 1
// TODO(apolcyn): re-evaluate support for c-ares
// on android after upgrading our c-ares dependency.
// See https://github.com/grpc/grpc/issues/18038.
#define GRPC_ARES 0
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#define C_CPU_POSIX 1
#define C_GCC_SYNC 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_ANDROID_LOG 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#define C_SUPPORT_CHANNELS_FROM_FD 1
#elif defined(__linux__)
#define C_PLATFORM_STRING "linux"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <features.h>
#define C_CPU_LINUX 1
#define C_GCC_ATOMIC 1
#define C_LINUX 1
#define C_LINUX_LOG
#define C_SUPPORT_CHANNELS_FROM_FD 1
#define C_LINUX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#ifdef __GLIBC__
#define C_POSIX_CRASH_HANDLER 1
#ifdef __GLIBC_PREREQ
#if __GLIBC_PREREQ(2, 12)
#define C_LINUX_PTHREAD_NAME 1
#endif
#else
// musl libc & others
#define C_LINUX_PTHREAD_NAME 1
#endif
#include <linux/version.h>
#else /* musl libc */
#define C_MUSL_LIBC_COMPAT 1
#endif
#elif defined(__ASYLO__)
#define C_ARCH_64 1
#define C_CPU_POSIX 1
#define C_PLATFORM_STRING "asylo"
#define C_GCC_SYNC 1
#define C_POSIX_STAT 1
#define C_POSIX_SYNC 1
#define C_POSIX_STRING 1
#define C_POSIX_LOG 1
#define C_POSIX_TIME 1
#define C_POSIX_ENV 1
#define C_ASYLO 1
#define GRPC_POSIX_SOCKET 1
#define GRPC_POSIX_SOCKETADDR
#define GRPC_POSIX_SOCKETUTILS 1
#define GRPC_TIMER_USE_GENERIC 1
#define GRPC_POSIX_NO_SPECIAL_WAKEUP_FD 1
#define GRPC_POSIX_WAKEUP_FD 1
#define GRPC_HAVE_MSG_NOSIGNAL 1
#define GRPC_HAVE_UNIX_SOCKET 1
#define GRPC_ARES 0
#define C_NO_AUTODETECT_PLATFORM 1
#elif defined(__APPLE__)
#include <Availability.h>
#include <TargetConditionals.h>
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#if TARGET_OS_IPHONE
#define C_PLATFORM_STRING "ios"
#define C_CPU_IPHONE 1
#define GRPC_CFSTREAM 1
/* the c-ares resolver isn't safe to enable on iOS */
#define GRPC_ARES 0
#else /* TARGET_OS_IPHONE */
#define C_PLATFORM_STRING "osx"
#define C_CPU_POSIX 1
#define C_POSIX_CRASH_HANDLER 1
#endif
#if !(defined(__has_feature) && __has_feature(cxx_thread_local))
#define C_PTHREAD_TLS 1
#endif
#define C_APPLE 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#ifndef GRPC_CFSTREAM
#define C_SUPPORT_CHANNELS_FROM_FD 1
#endif
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#elif defined(__FreeBSD__)
#define C_PLATFORM_STRING "freebsd"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define C_FREEBSD 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#define C_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#elif defined(__OpenBSD__)
#define C_PLATFORM_STRING "openbsd"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define C_OPENBSD 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#define C_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#elif defined(__sun) && defined(__SVR4)
#define C_PLATFORM_STRING "solaris"
#define C_SOLARIS 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#elif defined(_AIX)
#define C_PLATFORM_STRING "aix"
#ifndef _ALL_SOURCE
#define _ALL_SOURCE
#endif
#define C_AIX 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#elif defined(__NetBSD__)
// NetBSD is a community-supported platform.
// Please contact Thomas Klausner <wiz@NetBSD.org> for support.
#define C_PLATFORM_STRING "netbsd"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define C_NETBSD 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_GCC_TLS 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_GETPID_IN_UNISTD_H 1
#define C_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#elif defined(__native_client__)
#define C_PLATFORM_STRING "nacl"
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#define C_NACL 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#elif defined(__Fuchsia__)
#define GRPC_ARES 0
#define C_FUCHSIA 1
#define C_ARCH_64 1
#define C_PLATFORM_STRING "fuchsia"
#include <features.h>
// Specifying musl libc affects wrap_memcpy.c. It causes memmove() to be
// invoked.
#define C_MUSL_LIBC_COMPAT 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_SYNC 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_STRING 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#define GRPC_ROOT_PEM_PATH "/config/ssl/cert.pem"
#elif defined(__HAIKU__)
#define C_PLATFORM_STRING "haiku"
// Haiku is a community-supported platform.
// Please contact Jerome Duval <jerome.duval@gmail.com> for support.
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#define C_HAIKU 1
#define C_CPU_POSIX 1
#define C_GCC_ATOMIC 1
#define C_POSIX_LOG 1
#define C_POSIX_ENV 1
#define C_POSIX_TMPFILE 1
#define C_POSIX_STAT 1
#define C_POSIX_STRING 1
#define C_POSIX_SUBPROCESS 1
#define C_POSIX_SYNC 1
#define C_POSIX_TIME 1
#define C_HAS_PTHREAD_H 1
#define C_GETPID_IN_UNISTD_H 1
#define C_SUPPORT_CHANNELS_FROM_FD 1
#ifdef _LP64
#define C_ARCH_64 1
#else /* _LP64 */
#define C_ARCH_32 1
#endif /* _LP64 */
#else
#error "Could not auto-detect platform"
#endif
#endif /* C_NO_AUTODETECT_PLATFORM */

#if defined(C_BACKWARDS_COMPATIBILITY_MODE)
/*
 * For backward compatibility mode, reset _FORTIFY_SOURCE to prevent
 * a library from having non-standard symbols such as __asprintf_chk.
 * This helps non-glibc systems such as alpine using musl to find symbols.
 */
#if defined(_FORTIFY_SOURCE) && _FORTIFY_SOURCE > 0
#undef _FORTIFY_SOURCE
#define _FORTIFY_SOURCE 0
#endif
#endif

#if defined(__has_include)
#if __has_include(<atomic>)
#define GRPC_HAS_CXX11_ATOMIC
#endif /* __has_include(<atomic>) */
#endif /* defined(__has_include) */

#ifndef C_PLATFORM_STRING
#warning "C_PLATFORM_STRING not auto-detected"
#define C_PLATFORM_STRING "unknown"
#endif

#ifdef C_GCOV
#undef C_FORBID_UNREACHABLE_CODE
#define C_FORBID_UNREACHABLE_CODE 1
#endif

#ifdef _MSC_VER
#if _MSC_VER < 1700
typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif /* _MSC_VER < 1700 */
#else
#include <stdint.h>
#endif /* _MSC_VER */

/* Type of cycle clock implementation */
#ifdef C_LINUX
/* Disable cycle clock by default.
   TODO(soheil): enable when we support fallback for unstable cycle clocks.
#if defined(__i386__)
#define C_CYCLE_COUNTER_RDTSC_32 1
#elif defined(__x86_64__) || defined(__amd64__)
#define C_CYCLE_COUNTER_RDTSC_64 1
#else
#define C_CYCLE_COUNTER_FALLBACK 1
#endif
*/
#define C_CYCLE_COUNTER_FALLBACK 1
#else
#define C_CYCLE_COUNTER_FALLBACK 1
#endif /* C_LINUX */

/* Cache line alignment */
#ifndef C_CACHELINE_SIZE_LOG
#if defined(__i386__) || defined(__x86_64__)
#define C_CACHELINE_SIZE_LOG 6
#endif
#ifndef C_CACHELINE_SIZE_LOG
/* A reasonable default guess. Note that overestimates tend to waste more
   space, while underestimates tend to waste more time. */
#define C_CACHELINE_SIZE_LOG 6
#endif /* C_CACHELINE_SIZE_LOG */
#endif /* C_CACHELINE_SIZE_LOG */

#define C_CACHELINE_SIZE (1 << C_CACHELINE_SIZE_LOG)

/* scrub GCC_ATOMIC if it's not available on this compiler */
#if defined(C_GCC_ATOMIC) && !defined(__ATOMIC_RELAXED)
#undef C_GCC_ATOMIC
#define C_GCC_SYNC 1
#endif

/* Validate platform combinations */
#if defined(C_GCC_ATOMIC) + defined(C_GCC_SYNC) + \
        defined(C_WINDOWS_ATOMIC) !=                \
    1
#error Must define exactly one of C_GCC_ATOMIC, C_GCC_SYNC, C_WINDOWS_ATOMIC
#endif

#if defined(C_ARCH_32) + defined(C_ARCH_64) != 1
#error Must define exactly one of C_ARCH_32, C_ARCH_64
#endif

#if defined(C_CPU_LINUX) + defined(C_CPU_POSIX) + defined(C_WINDOWS) + \
        defined(C_CPU_IPHONE) + defined(C_CPU_CUSTOM) !=                 \
    1
#error Must define exactly one of C_CPU_LINUX, C_CPU_POSIX, C_WINDOWS, C_CPU_IPHONE, C_CPU_CUSTOM
#endif

/* maximum alignment needed for any type on this platform, rounded up to a
   power of two */
#define C_MAX_ALIGNMENT 16

#ifndef GRPC_ARES
#define GRPC_ARES 1
#endif

#ifndef GRPC_IF_NAMETOINDEX
#define GRPC_IF_NAMETOINDEX 1
#endif

#ifndef GRPC_MUST_USE_RESULT
#if defined(__GNUC__) && !defined(__MINGW32__)
#define GRPC_MUST_USE_RESULT __attribute__((warn_unused_result))
#define C_ALIGN_STRUCT(n) __attribute__((aligned(n)))
#else
#define GRPC_MUST_USE_RESULT
#define C_ALIGN_STRUCT(n)
#endif
#ifdef USE_STRICT_WARNING
/* When building with USE_STRICT_WARNING (which -Werror), types with this
   attribute will be treated as annotated with warn_unused_result, enforcing
   returned values of this type should be used.
   This is added in grpc::Status in mind to address the issue where it always
   has this annotation internally but OSS doesn't, sometimes causing internal
   build failure. To prevent this, this is added while not introducing
   a breaking change to existing user code which may not use returned values
   of grpc::Status. */
#define GRPC_MUST_USE_RESULT_WHEN_USE_STRICT_WARNING GRPC_MUST_USE_RESULT
#else
#define GRPC_MUST_USE_RESULT_WHEN_USE_STRICT_WARNING
#endif
#endif

#ifndef GRPC_UNUSED
#if defined(__GNUC__) && !defined(__MINGW32__)
#define GRPC_UNUSED __attribute__((unused))
#else
#define GRPC_UNUSED
#endif
#endif

#ifndef C_PRINT_FORMAT_CHECK
#ifdef __GNUC__
#define C_PRINT_FORMAT_CHECK(FORMAT_STR, ARGS) \
  __attribute__((format(printf, FORMAT_STR, ARGS)))
#else
#define C_PRINT_FORMAT_CHECK(FORMAT_STR, ARGS)
#endif
#endif /* C_PRINT_FORMAT_CHECK */

#ifndef C_HAS_CPP_ATTRIBUTE
#ifdef __has_cpp_attribute
#define C_HAS_CPP_ATTRIBUTE(a) __has_cpp_attribute(a)
#else
#define C_HAS_CPP_ATTRIBUTE(a) 0
#endif
#endif /* C_HAS_CPP_ATTRIBUTE */

#ifndef C_HAS_ATTRIBUTE
#ifdef __has_attribute
#define C_HAS_ATTRIBUTE(a) __has_attribute(a)
#else
#define C_HAS_ATTRIBUTE(a) 0
#endif
#endif /* C_HAS_ATTRIBUTE */

#if C_HAS_ATTRIBUTE(noreturn)
#define C_ATTRIBUTE_NORETURN __attribute__((noreturn))
#else
#define C_ATTRIBUTE_NORETURN
#endif

#if C_FORBID_UNREACHABLE_CODE
#define C_UNREACHABLE_CODE(STATEMENT)
#else
#ifdef __cplusplus
extern "C" {
#endif
extern void C_unreachable_code(const char* reason, const char* file,
                                 int line) C_ATTRIBUTE_NORETURN;
#ifdef __cplusplus
}
#endif
#define C_UNREACHABLE_CODE(STATEMENT)                   \
  do {                                                    \
    C_unreachable_code(#STATEMENT, __FILE__, __LINE__); \
    STATEMENT;                                            \
  } while (0)
#endif /* C_FORBID_UNREACHABLE_CODE */

#ifndef CAPI
#define CAPI
#endif

#ifndef GRPCAPI
#define GRPCAPI CAPI
#endif

#ifndef CENSUSAPI
#define CENSUSAPI GRPCAPI
#endif

#ifndef C_HAS_FEATURE
#ifdef __has_feature
#define C_HAS_FEATURE(a) __has_feature(a)
#else
#define C_HAS_FEATURE(a) 0
#endif
#endif /* C_HAS_FEATURE */

#ifndef C_ATTRIBUTE_NOINLINE
#if C_HAS_ATTRIBUTE(noinline) || (defined(__GNUC__) && !defined(__clang__))
#define C_ATTRIBUTE_NOINLINE __attribute__((noinline))
#define C_HAS_ATTRIBUTE_NOINLINE 1
#else
#define C_ATTRIBUTE_NOINLINE
#endif
#endif /* C_ATTRIBUTE_NOINLINE */

#ifndef C_NO_UNIQUE_ADDRESS
#if C_HAS_CPP_ATTRIBUTE(no_unique_address)
#define C_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define C_NO_UNIQUE_ADDRESS
#endif
#endif /* C_NO_UNIQUE_ADDRESS */

#ifndef GRPC_DEPRECATED
#if C_HAS_CPP_ATTRIBUTE(deprecated)
#define GRPC_DEPRECATED(reason) [[deprecated(reason)]]
#else
#define GRPC_DEPRECATED(reason)
#endif
#endif /* GRPC_DEPRECATED */

#ifndef C_ATTRIBUTE_WEAK
/* Attribute weak is broken on LLVM/windows:
 * https://bugs.llvm.org/show_bug.cgi?id=37598 */
#if (C_HAS_ATTRIBUTE(weak) || (defined(__GNUC__) && !defined(__clang__))) && \
    !(defined(__llvm__) && defined(_WIN32))
#define C_ATTRIBUTE_WEAK __attribute__((weak))
#define C_HAS_ATTRIBUTE_WEAK 1
#else
#define C_ATTRIBUTE_WEAK
#endif
#endif /* C_ATTRIBUTE_WEAK */

#ifndef C_ATTRIBUTE_NO_TSAN /* (1) */
#if C_HAS_FEATURE(thread_sanitizer)
#define C_ATTRIBUTE_NO_TSAN __attribute__((no_sanitize("thread")))
#endif                        /* C_HAS_FEATURE */
#ifndef C_ATTRIBUTE_NO_TSAN /* (2) */
#define C_ATTRIBUTE_NO_TSAN
#endif /* C_ATTRIBUTE_NO_TSAN (2) */
#endif /* C_ATTRIBUTE_NO_TSAN (1) */

/* GRPC_TSAN_ENABLED will be defined, when compiled with thread sanitizer. */
#ifndef GRPC_TSAN_SUPPRESSED
#if defined(__SANITIZE_THREAD__)
#define GRPC_TSAN_ENABLED
#elif C_HAS_FEATURE(thread_sanitizer)
#define GRPC_TSAN_ENABLED
#endif
#endif

/* GRPC_ASAN_ENABLED will be defined, when compiled with address sanitizer. */
#ifndef GRPC_ASAN_SUPPRESSED
#if defined(__SANITIZE_ADDRESS__)
#define GRPC_ASAN_ENABLED
#elif C_HAS_FEATURE(address_sanitizer)
#define GRPC_ASAN_ENABLED
#endif
#endif

/* GRPC_ALLOW_EXCEPTIONS should be 0 or 1 if exceptions are allowed or not */
#ifndef GRPC_ALLOW_EXCEPTIONS
#ifdef C_WINDOWS
#if defined(_MSC_VER) && defined(_CPPUNWIND)
#define GRPC_ALLOW_EXCEPTIONS 1
#elif defined(__EXCEPTIONS)
#define GRPC_ALLOW_EXCEPTIONS 1
#else
#define GRPC_ALLOW_EXCEPTIONS 0
#endif
#else /* C_WINDOWS */
#ifdef __EXCEPTIONS
#define GRPC_ALLOW_EXCEPTIONS 1
#else /* __EXCEPTIONS */
#define GRPC_ALLOW_EXCEPTIONS 0
#endif /* __EXCEPTIONS */
#endif /* __C_WINDOWS */
#endif /* GRPC_ALLOW_EXCEPTIONS */

/* Use C_LIKELY only in cases where you are sure that a certain outcome is the
 * most likely. Ideally, also collect performance numbers to justify the claim.
 */
#ifdef __GNUC__
#define C_LIKELY(x) __builtin_expect((x), 1)
#define C_UNLIKELY(x) __builtin_expect((x), 0)
#else /* __GNUC__ */
#define C_LIKELY(x) (x)
#define C_UNLIKELY(x) (x)
#endif /* __GNUC__ */

#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

#define GRPC_CALLBACK_API_NONEXPERIMENTAL

/* clang 11 with msan miscompiles destruction of [[no_unique_address]] members
 * of zero size - for a repro see:
 * test/core/compiler_bugs/miscompile_with_no_unique_address_test.cc
 */
#ifdef __clang__
#if __clang__ && __clang_major__ <= 11 && __has_feature(memory_sanitizer)
#undef C_NO_UNIQUE_ADDRESS
#define C_NO_UNIQUE_ADDRESS
#endif
#endif

#endif /* PORT_PLATFORM_H_ */

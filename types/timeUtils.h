#ifndef types_cnets_osblinnikov_github_com_TIMEUTILS_H
#define types_cnets_osblinnikov_github_com_TIMEUTILS_H

#if !defined __MINGW32__ && defined _WIN32
    struct timezone{
        int  tz_minuteswest; /* minutes W of Greenwich */
        int  tz_dsttime;     /* type of dst correction */
    };
#endif /*WIN32 endif*/

#if defined(__MINGW32__) || !defined(_WIN32)
    #include <sys/time.h>
#endif
#if defined __MINGW32__ || defined _WIN32
    #if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
      #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
    #else
      #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
    #endif
    #include <time.h>
    #ifndef HAVE_STRUCT_TIMESPEC
        #define HAVE_STRUCT_TIMESPEC 1
        typedef struct timespec {
            time_t tv_sec;
            long tv_nsec;
        }timespec;
    #endif /* HAVE_STRUCT_TIMESPEC */
#endif
#ifdef __cplusplus
extern "C" {  /* only need to export C interface if used by C++ source code*/
#endif
types_cnets_osblinnikov_github_com_EXPORT_API
    uint64_t curTimeMilisec();
types_cnets_osblinnikov_github_com_EXPORT_API
    struct timespec getTimespecDelay(uint64_t nanosec);
types_cnets_osblinnikov_github_com_EXPORT_API
    int compareTimespec(struct timespec *timeSpec);
types_cnets_osblinnikov_github_com_EXPORT_API
    int compareTwoTimespecs(struct timespec *lTimeSpec,struct timespec *rTimeSpec);
types_cnets_osblinnikov_github_com_EXPORT_API
    int taskDelayTill(struct timespec *end,  void* mutex, void* condition_variable);
types_cnets_osblinnikov_github_com_EXPORT_API
    void taskDelay(uint64_t nanosec);

inline void taskDelayMilisec(uint64_t milisec){
    taskDelay(milisec*1000L*1000L);
}

types_cnets_osblinnikov_github_com_EXPORT_API
    unsigned diffTwoTimespecs(struct timespec *lTimeSpec,struct timespec *rTimeSpec);
#ifdef __cplusplus
} /* only need to export C interface if used by C++ source code*/
#endif

#endif /*types_cnets_osblinnikov_github_com_TIMEUTILS_H*/

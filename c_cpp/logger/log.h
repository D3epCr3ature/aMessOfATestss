
#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>

#if !defined(LOG_MODULE_IS)
# error "This module has no name, please define LOG_MODULE_IS"
#endif

#define VAL_TO_STR(VAL)	#VAL
#define DEF_TO_STR(DEF)	VAL_TO_STR(DEF)

#define CYAN(BOLD)	"\033[" DEF_TO_STR(BOLD) ";36m"
#define PURPLE(BOLD)	"\033[" DEF_TO_STR(BOLD) ";35m"
#define BLUE(BOLD)	"\033[" DEF_TO_STR(BOLD) ";34m"
#define YELLOW(BOLD)	"\033[" DEF_TO_STR(BOLD) ";33m"
#define GREEN(BOLD)	"\033[" DEF_TO_STR(BOLD) ";32m"
#define RED(BOLD)	"\033[" DEF_TO_STR(BOLD) ";31m"
#define NC		"\033[0m"

#define LOG_LVL_DEBUG	0
#define LOG_LVL_INFO	1
#define LOG_LVL_ERROR	2

#ifndef DEBUG_LEVEL
#define DEBUG_LEVEL	LOG_LVL_INFO
#endif

#if DEBUG_LEVEL <= LOG_LVL_DEBUG
#define LOGD(FMT, ...)  printf(LOG_MODULE_IS ":%s"              \
                               CYAN(1) "[D]" NC ":" FMT,        \
                               __func__, ##__VA_ARGS__)
#else
#define LOGD(...)       (void)0
#endif

#if DEBUG_LEVEL <= LOG_LVL_INFO
#define LOGI(FMT, ...)  printf(LOG_MODULE_IS ":%s"              \
                               YELLOW(1) "[I]" NC ":" FMT,      \
                               __func__, ##__VA_ARGS__)
#else
#define LOGI(...)       (void)0
#endif

#if DEBUG_LEVEL <= LOG_LVL_ERROR
#define LOGE(FMT, ...)  fprintf(stderr, LOG_MODULE_IS ":%s"     \
                               RED(1) "[E]" NC ":" FMT,         \
                               __func__, ##__VA_ARGS__)
#else
#define LOGE(...)       (void)0
#endif

#endif /* __LOG_H__ */

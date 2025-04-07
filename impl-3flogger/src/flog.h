#ifndef _FLOG_H
#define _FLOG_H

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include "flog_cfg.h"


#ifndef TAG
#define TAG     "NO_TAG"
#endif


#define FLOG_LVL_ASSERT     0
#define FLOG_LVL_ERROR      1
#define FLOG_LVL_WARNING    2
#define FLOG_LVL_INFO       3

/* 目前日志等级数 */
#define FLOG_LVL_NUMS       4

/* 版本号 */
#define FLOG_VERSION        "0.0.1"



#define FLOG_CUR_LINE       __LINE__
#define FLOG_CUR_FUNC       __FUNCTION__
#define FLOG_CUR_DIR        __FILE__





/* 错误码 */
typedef enum FlogErrCode {
    flog_ok = 0,
    flog_err = 1,
} FlogErrCode;




#ifndef FLOG_OUTPUT_ENABLE
// 若未使能输出，置以下宏输出为空
    #define flog_assert(tag, ...)
    #define flog_error(tag, ...)
    #define flog_warning(tag, ...)
    #define flog_info(tag, ...)
#else
    #define flog_assert(tag, ...) \
        flog_output(FLOG_LVL_ASSERT, tag, FLOG_CUR_DIR, FLOG_CUR_FUNC, FLOG_CUR_LINE, __VA_ARGS__)
#endif



/**
 * @brief 定义输出格式标志位
 */
typedef enum flog_output_fmt {
    FLOG_FMT_TAG            = 1 << 0,       /**< 当前标签名字 */
    FLOG_FMT_LVL            = 1 << 1,       /**< 当前输出等级 */
    FLOG_FMT_TIME           = 1 << 2,       /**< 当前时间 */
    FLOG_FMT_LINE           = 1 << 3,       /**< 当前行数 */
    FLOG_FMT_FUNC           = 1 << 4,       /**< 当前函数名称 */
    FLOG_FMT_DIR            = 1 << 5,       /**< 当前源文件未知 */
    FLOG_FMT_THREAD_INFO    = 1 << 6,       /**< 线程信息 */
    FLOG_FMT_PROCESS_INFO   = 1 << 7,       /**< 进行信息 */
} flog_output_fmt;

#define FLOG_FMT_ALL                                                        \
(FLOG_FMT_TAG | FLOG_FMT_LVL | FLOG_FMT_TIME | FLOG_FMT_LINE |              \
 FLOG_FMT_FUNC |FLOG_FMT_DIR | FLOG_FMT_THREAD_INFO | FLOG_FMT_PROCESS_INFO)

#define FLOG_FMT_MASK_CHECK(mask, bit) (mask & bit)



/**
 * @brief 定义 flowerLogger 结构体
 */
typedef struct FlowerLogger {
    uint8_t output_fmt[FLOG_LVL_NUMS];
} FlowerLogger, *FlowerLogger_t;
extern FlowerLogger_t flowerLogger;






FlogErrCode flog_init(void);
void flog_start(void);
void flog_end(void);
void flog_set_fmt(uint8_t lvl, uint8_t fmt_flag);
void flog_output(uint8_t lvl, char* tag, const char* dir,
    const char* func, const int line, const char* fmt, ...);


void flog_async_init(void);
void flog_async_output(void);




















#endif /* _FLOG_H */
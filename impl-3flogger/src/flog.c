#include "flog.h"
#include "flog_cfg.h"
#include <stdlib.h>

/* 全局变量：flog 结构体 */
FlowerLogger_t flowerLogger;



/**
 * @brief 初始化 flowerlogger
 */
FlogErrCode flog_init(void) {
    flowerLogger = malloc(sizeof(FlowerLogger));
    if (flowerLogger == NULL) {
        return flog_err;
    }
    return flog_ok;
}





/**
 * @brief 设定不同日志等级的输出格式
 * @param lvl 日志等级
 * @param fmt_flag 输出格式位掩码
 */
void flog_set_fmt(uint8_t lvl, uint8_t fmt_flag) {
    flowerLogger->output_fmt[lvl] = fmt_flag;
}


/**
 * @brief 日志输出
 * @param lvl 等级
 * @param tag 标签文本
 * @param dir 当前文件未知
 * @param func 当前函数
 * @param line 当前行数
 * @param fmt 输出模板
 */
void flog_output(uint8_t lvl, char* tag, const char* dir, 
    const char* func, const int line, const char* fmt, ...) {
    
    /* 定义返回的字符串 */
    const char* ret[FLOG_OUTPUT_LINE_MAX_LEN];

    /* 使用 extern 声明在 flog_port.c 中定义的函数 */
    extern const char* flog_port_fmt_get_time(void);
    extern const char* flog_port_fmt_get_thread_info(void);
    extern const char* flog_port_fmt_get_process_info(void);
    
    /* 临时变量 */
    const uint8_t tmp_fmt = flowerLogger->output_fmt[lvl];

    /* 检查标签 */
    if (FLOG_FMT_MASK_CHECK(tmp_fmt, FLOG_FMT_TAG)) {
        printf("%s\t", tag);
    }

    /* 源文件、行数、函数名*/
    if (FLOG_FMT_MASK_CHECK(tmp_fmt, FLOG_FMT_DIR)) {
        printf("%s\t", dir);
    }

    if (FLOG_FMT_MASK_CHECK(tmp_fmt, FLOG_FMT_FUNC)) {
        printf("%s\t", func);
    }

    if (FLOG_FMT_MASK_CHECK(tmp_fmt, FLOG_FMT_LINE)) {
        printf("%d\t", FLOG_CUR_LINE);
    }
    
    /* 线程信息 */
    if (FLOG_FMT_MASK_CHECK(tmp_fmt, FLOG_FMT_THREAD_INFO)) {
        char* tmpbuf = flog_port_fmt_get_thread_info();
        printf("%s\t", tmpbuf);
    }

    /* 进程信息 */
    if (FLOG_FMT_MASK_CHECK(tmp_fmt, FLOG_FMT_PROCESS_INFO)) {
        char* tmpbuf = flog_port_fmt_get_process_info();
        printf("%s\t", tmpbuf);
    }

    /* 时间信息 */
    if (FLOG_FMT_MASK_CHECK(tmp_fmt, FLOG_FMT_TIME)) {
        char* tmpbuf = flog_port_fmt_get_time();
        printf("%s\t", tmpbuf);
    }
    /* fmt 字符串 */
    va_list ap;
    va_start(ap, fmt);
    static char fmt_buf[128];
    int n = vsnprintf(fmt_buf, 128, fmt, ap);
    va_end(ap);

    if (n < 0) {
        return;
    } else {
        printf("%s\n", fmt_buf);
    }


}
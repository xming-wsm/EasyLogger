#ifndef _FLOG_H
#define _FLOG_H

#include "log_cfg.h"




#define FLOG_LVL_ASSERT     0
#define FLOG_LVL_ERROR      1
#define FLOG_LVL_WARNING    2
#define FLOG_LVL_INFO       3



/* 错误码 */
typedef enum flog_err {
    elog_ok = 0,
} FlogErrCode;


// #ifndef 








FlogErrCode flog_init(void);
void flog_start(void);
void flog_end(void);
void flog_output();




















#endif /* _FLOG_H */
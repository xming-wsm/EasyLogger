/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */

#include <unistd.h>
#include <elog.h>
#include <stdio.h>
#include <elog_cfg.h>
#include <pthread.h>
#include <time.h>

#include <sys/types.h>
#include <sys/prctl.h>


static pthread_mutex_t output_mutex_lock;


/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    /* add your code here */
    pthread_mutex_init(&output_mutex_lock, NULL);

    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void) {

    /* add your code here */
    pthread_mutex_destroy(&output_mutex_lock);
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {
    
    /* add your code here */
#ifdef ELOG_OUTPUT_TERMINAL_ENABLE
    printf("%.*s", (int)size, log);
#endif 
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    
    /* add your code here */
    pthread_mutex_lock(&output_mutex_lock);
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    
    /* add your code here */
    pthread_mutex_unlock(&output_mutex_lock);
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    
    /* add your code here */
    static char cur_time_buffer[80] = {0};

    time_t cur_time;
    struct tm cur_tm;

    /* 获取当前时间 */
    time(&cur_time);

    /* 转换为本地时间 */
    localtime_r(&cur_time, &cur_tm);

    strftime(cur_time_buffer, 80, "%Y-%m-%d %H:%M:%S", &cur_tm);
    return cur_time_buffer;
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    
    /* add your code here */
    static char cur_process_name[10] = {0};
    snprintf(cur_process_name, 10, "pid:%5d", getpid());
    return cur_process_name;
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {

    /* add your code here */
    static char cur_thread_name[10] = { 0 };
    prctl(PR_GET_NAME, cur_thread_name);
    return cur_thread_name;
}
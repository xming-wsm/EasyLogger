#define TAG "main"


#include <stdio.h>
#include <flog.h>






int main(int argc, char** argv) {
    flog_init();
    
    flog_set_fmt(FLOG_LVL_ASSERT, FLOG_FMT_ALL);
    flog_assert(TAG, "1234\n");    
    return 0;
}

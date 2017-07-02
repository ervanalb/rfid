#include "ff.h"

FATFS fatfs;

#define msg "Hello, world!"

int sd_startup() {
    FRESULT fr;
    FIL file;
    UINT n;

    f_mount(&fatfs, "", 0);
    fr = f_open(&file, "0:hello.txt", FA_WRITE | FA_CREATE_ALWAYS);
    if(fr) return fr;
    fr = f_write(&file, msg, sizeof(msg)-1, &n);
    f_close(&file);
    if(fr) return fr;
    if(n < sizeof(msg)-1) return -1;
    return 0;
}

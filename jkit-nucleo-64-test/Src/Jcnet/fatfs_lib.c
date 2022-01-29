/*
 * fatfs_lib.c
 *
 *  Created on: 2020. 2. 19.
 *      Author: isjeon
 */


#include "main.h"
#include "fatfs.h"

#define xprintf printf
FATFS FatFs ;
//FIL   Fin   ;
//FIL   Fwrite;
DIR Dir;
DWORD AccSize;              /* Work register for fs command */
WORD AccFiles, AccDirs;

FILINFO Finfo;
FATFS *fs;
#if _USE_LFN
char Lfname[512];
#endif
static
void put_rc (FRESULT rc)
{
    const char *str =
        "OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
        "INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
        "INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
        "LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0";
    FRESULT i;

    for (i = 0; i != rc && *str; i++) {
        while (*str++) ;
    }
    xprintf("rc=%u FR_%s\n", (UINT)rc, str);
}

static int f_num = 0;
void print_dir()
{
    FRESULT res;
    char *ptr, *ptr2;
    long p1, p2, p3;
    unsigned int s1, s2, cnt;
//printf("In print_dir\n\r");
    res = f_opendir(&Dir, "/"); //ptr);
//    printf("Result = "); put_rc(res);
                if (res) { put_rc(res); return; }
                p1 = s1 = s2 = 0;
                for(;;) {
                    res = f_readdir(&Dir, &Finfo);
                    if ((res != FR_OK) || !Finfo.fname[0]) return;
                    if (Finfo.fattrib & AM_DIR) {
                        s2++;
                    } else {
                        s1++; p1 += Finfo.fsize;
                    }
                    f_num ++;
                    xprintf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %-12s  %s\n",
                            (Finfo.fattrib & AM_DIR) ? 'D' : '-',
                            (Finfo.fattrib & AM_RDO) ? 'R' : '-',
                            (Finfo.fattrib & AM_HID) ? 'H' : '-',
                            (Finfo.fattrib & AM_SYS) ? 'S' : '-',
                            (Finfo.fattrib & AM_ARC) ? 'A' : '-',
                            (Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,
                            (Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63,
                            Finfo.fsize, Finfo.fname,
#if _USE_LFN
                            Lfname);
#else
                            "");
#endif
                }
                xprintf("%4u File(s),%10lu bytes total\n%4u Dir(s)", s1, p1, s2);
                res = f_getfree(ptr, (DWORD*)&p1, &fs);
                if (res == FR_OK)
                    xprintf(", %10lu bytes free\n", p1 * fs->csize * 512);
                else
                    put_rc(res);

}

static int mount_flag = 0;
void fatfs_test(void const * argument)
{

  int ret;
  int written,wb;
  uint32_t prev,cur,s,e;
  if(mount_flag == 0)
  {
	  ret = f_mount(&FatFs,"0:", 1);
	  printf("FATFS mount res = %d\n",ret);
  }
  if(!ret) {
	  mount_flag = 1;
	  f_num = 0;
	  print_dir();
	  CLCD_printf(0,1,"FATOK #  = %05d",f_num);
  }
  else
  {
	  CLCD_printf(0,1,"FAT NOT OK     ");
  }
  return;
}


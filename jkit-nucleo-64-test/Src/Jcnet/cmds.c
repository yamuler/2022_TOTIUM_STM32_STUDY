/*
 * cmds.c
 *
 *  Created on: 2020. 2. 26.
 *      Author: isjeon
 */
#include "main.h"
#include "stdio.h"

extern void led_fn(int ac, char *av[]);
extern void fnd_fn(int ac, char *av[]);
extern void buz_fn(int ac, char *av[]);
extern void temp_fn(int ac, char *av[]);
extern void cds_fn(int ac, char *av[]);
extern void switch_fn(int ac, char *av[]);
extern void clcd_fn(int ac, char *av[]);
extern void motor_fn(int ac, char *av[]);
extern void fatfs_fn(int ac, char *av[]);
extern void run_all(int ac, char *av[]);
extern void temp_fn(int ac, char *av[]);
extern void tft_fn(int ac, char *av[]);
void help(int ac, char *av[]);
typedef struct _cmd_node_tag {
	const char *cmd;
	void (*fn)(int ac, char *av[]);
	const char *help;
} cmd_node_t;

const cmd_node_t cmd_tbl[] =
{
		{"led",  led_fn,      "Test Leds"},
		{"fnd",  fnd_fn,      "Test Fnds"},
		{"buz",  buz_fn,      "Test buzz"},
		{"temp", temp_fn,     "Test Temperature"},
		{"cds",  cds_fn,      "Test CDS"},
		{"switch",switch_fn,  "Test switch"},
		{"clcd", clcd_fn,     "Test CLCD"},
		{"motor",motor_fn,    "Test Motor"},
		{"fatfs",fatfs_fn,   "Test fatfs"},
//		{"temp", temp_fn,     "Read Temp"},
		{"tft", tft_fn,     "tftlcd init"},
		{"all",  run_all,    "Run all the function"},
		{"help", help,        ""}
};

void help(int ac, char *av[])
{
	int i;
	printf("CMDS\n");
	for( i = 0 ; i < sizeof(cmd_tbl) / sizeof(cmd_tbl[0]) ; i ++)
	{
		printf("[%s] %s\n",cmd_tbl[i].cmd,cmd_tbl[i].help);
	}
}
#include "string.h"

int exec_cmd(uint8_t *cmd, int ac,char *av[])
{
	int i;
	for( i = 0 ; i < sizeof(cmd_tbl) / sizeof(cmd_tbl[0]) ; i ++)
	{
		if(!strcmp(cmd, cmd_tbl[i].cmd))
		{
			cmd_tbl[i].fn(ac, av);
			return 0;
		}
	}
	return -1;
}

extern void my_putchar(char c);
int get_args(char *buf, char *av[])
{
        int     num, start, end;
        start = end = num = 0;
        while (1)
        {
//printf("buf+start = [%s] start=%d end=%d buf[end]=%x num=%d\n",buf, start,end,buf[end],num);
                if(buf[end] == '\0' || buf[end] == '\n' || buf[end] == '\r')
                {
                        if(buf[end]) buf[end] = '\0';
                        if(start != end)
                        {
                                strcpy(av[num],buf+start);
                                num ++;
                                return num;
                        }
                        else
                        {
                                return num;
                        }
                }
                if(buf[end] != ' ' && buf[end] != '\t' ) {
                        end ++;
                }
                else
                {
                        buf[end] = 0;
                        strcpy(av[num],buf+start);
                        num ++;
                        end ++;
                        start = end ;
                }
        }
        return 0;
}

char avbuf[6][10];
char *av[6] = {
                &avbuf[0][0],
                &avbuf[1][0],
                &avbuf[2][0],
                &avbuf[3][0],
                &avbuf[4][0],
                &avbuf[5][0]
};
const char *prompt="jkit";
char *version="nucleo64";
static char cmd_buf[32]; //,old_buf[64];
static int idx = 0;
int do_cmd(char ch)
{

        char buf[64];
        int ac,i;
        if(ch == '\n' || ch == '\r')
        {
                 my_putchar('\n');
                 cmd_buf[idx] = '\0';
#if 0
                 if(!strncmp(cmd_buf,"!!",2))
                 {
                         strcpy(cmd_buf,old_buf);
                 }
#endif
                 strcpy(buf,cmd_buf);
                 for( i = 0 ; i < 6 ; i ++) av[i] = &avbuf[i][0];
                 ac = get_args(cmd_buf, av);
                 if(idx == 0 || !ac) {
                         idx = 0;
                         printf("%s-%s> ",prompt,version); fflush(stdout);
                         return 0;
                 }
//                 strcpy(old_buf,buf);
                 exec_cmd(av[0],ac, av);
                 printf("%s-%s> ",prompt,version); fflush(stdout);
                 idx = 0;
        }
        else if(ch == '\b')
        {
                 if(idx > 0) { idx --; my_putchar('\b'); my_putchar(' '); my_putchar('\b'); return 0;}
        }
        else if(idx < 63) {
                 cmd_buf[idx++] = ch;   my_putchar(ch);
        }

        return 0;

}

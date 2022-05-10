#include "mySimpleComputer.h"
#include "viewInterface.h"
#include "myReadKey.h"
#include "CommandInterface.h"
#include "ALU.h"
#include "CU.h"

#include "hardMagneticDisks.h"

#include <iostream>

#include <signal.h>
#include <sys/time.h>

#define SECT_SIZE 512
int count = 0; 
double disk;

void show_partitions(tPART *part, int num_parts);
void enter_partitions(tPART *part, tCHS geo, int num_parts);

void workWithTerminal(int signo)
{
	mt_clrScr();
	in_printInterface();

    if (!sc_regGet(IGNORE_TACTS))
	{
		step();
	}
	else
	{
		rk_readKey(1);
	}
}

int main()
{
	setbuf(stdout, 0);
	sc_memoryInit();
	sc_regSet(IGNORE_TACTS, 1);
	initMapCommand();
    initMapALUCommand();
    initMapCUCommand();

    sc_memorySet(0, 0b000100000001010); // 10
    // sc_memorySet(1, 0b000000000000010); // 2
    // sc_memorySet(2, 0b110100000000000); // -2048

	struct itimerval nval, oval;

	signal(SIGALRM, workWithTerminal);

	nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_usec = 100000;
	nval.it_value.tv_sec = 0;
	nval.it_value.tv_usec = 80000;

	setitimer(ITIMER_REAL, &nval, &oval);

	while (1) {
		pause();
	}

	return 0;
}

void show_partitions(tPART *part, int num_parts)
{

    for (int i = 0; i < num_parts; i++) {

        printf("%d", part[i].activ);
	printf("\t");

        printf("%d-%d-%d", part[i].beg.cyl, part[i].beg.head, part[i].beg.sec);
	printf("\t");


        printf("%d-%d-%d", part[i].end.cyl, part[i].end.head, part[i].end.sec);
	printf("\t");

        printf("%d", part[i].lba_beg.lba);
	printf("\t");

	printf("%d", part[i].size);
		printf("\t");

	printf("\n");

    }
}

void enter_partitions(tPART *part, tCHS geo, int num_parts)
{
    int activ = 0;

    for (int i = 0; i < num_parts; i++) {
        if (!activ) 
	    {
            printf("is this part is active? (y\\n): ");
            char ans[3];
            scanf("%s", ans);
            if (ans[0] == 'y') {
                part[i].activ = 1;
                activ++;
            }
        }



        if (i == 0)
            part[i].lba_beg.lba = 1;
        else {
            tLBA lba_tmp = {part[i - 1].lba_beg.lba + part[i - 1].size};
            part[i].lba_beg = lba_tmp;
        }
        
        printf("enter size: ");

        scanf("%d", &part[i].size);
	if (part[i].size == 0)
	{
        count++;
        part[i].size = disk;
        a_lba2chs(geo, part[i].lba_beg, &part[i].beg);
        tLBA lba_tmp = {part[i].lba_beg.lba + part[i].size - 1};
        a_lba2chs(geo, lba_tmp, &part[i].end);
		break;
	}
    disk-= part[i].size;
 	count++;
    if (disk <= 0)
    {
        break;
    }
        a_lba2chs(geo, part[i].lba_beg, &part[i].beg);
        tLBA lba_tmp = {part[i].lba_beg.lba + part[i].size - 1};
        a_lba2chs(geo, lba_tmp, &part[i].end);
    }
    if (activ == 0)
        part[count-1].activ = 1;
}
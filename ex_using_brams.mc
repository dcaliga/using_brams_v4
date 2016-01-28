/* $Id: ex03.mc,v 2.1 2005/06/14 22:16:47 jls Exp $ */

/*
 * Copyright 2005 SRC Computers, Inc.  All Rights Reserved.
 *
 *	Manufactured in the United States of America.
 *
 * SRC Computers, Inc.
 * 4240 N Nevada Avenue
 * Colorado Springs, CO 80907
 * (v) (719) 262-0213
 * (f) (719) 262-0223
 *
 * No permission has been granted to distribute this software
 * without the express permission of SRC Computers, Inc.
 *
 * This program is distributed WITHOUT ANY WARRANTY OF ANY KIND.
 */

#include <libmap.h>


void subr (int64_t I0[], int64_t Out[], int num, int64_t *time, int mapnum) {

    OBM_BANK_A (AL, int64_t, MAX_OBM_SIZE)
    OBM_BANK_B (BL, int64_t, MAX_OBM_SIZE)

    int T0[1024];
    int T1[1024];
    int T2[1024];
    int T3[1024];
    int T4[1024];
    int T5[1024];
    int T6[1024];
    int T7[1024];
    int64_t t0, t1;
    int i, idx;

    Stream_64 SA,SB,SC;





    buffered_dma_cpu (CM2OBM, PATH_0, AL, MAP_OBM_stripe (1,"A"), I0, 1, 8*num*8);


    // copy data into on-chip arrays
    for (i=0; i<num; i++) {
        T0[i] = AL[i];
        T1[i] = AL[num+i];
        T2[i] = AL[2*num+i];
        T3[i] = AL[3*num+i];
        T4[i] = AL[4*num+i];
        T5[i] = AL[5*num+i];
        T6[i] = AL[6*num+i];
        T7[i] = AL[7*num+i];
    }

    read_timer (&t0);

#pragma src parallel sections
{
#pragma src section
{
    streamed_dma_cpu_64 (&SB, STREAM_TO_PORT, Out, num*sizeof(int64_t));
}
# pragma src section
{
    int i;
    int64_t i64;

    for (i=0; i<num; i++) {
       i64 = (T0[i] + T1[i] - T2[i]) * (T3[i] * T4[i] + T5[i]) - (T6[i] & T7[i]);

       put_stream_64 (&SB, i64, 1);
    }
}
}

    read_timer (&t1);

    *time = t1 - t0;

}

/**
 *  \file       publisher.c
 *  \brief      Implementation JSON messaje formating and MQTT publish.
 */

/* -------------------------- Development history -------------------------- */
/*
 *  2018.06.22  DaBa  v1.0.00  Initial version
 */

/* -------------------------------- Authors -------------------------------- */
/*
 *  DaBa Dar�o Bali�a  db@vortexmakes.com
 */

/* --------------------------------- Notes --------------------------------- */
/* ----------------------------- Include files ----------------------------- */
#include "publisher.h"
#include "ioChgDet.h"
#include "anSampler.h"
#include "jWrite.h"
#include "conmgr.h"

/* ----------------------------- Local macros ------------------------------ */
/* ------------------------------- Constants ------------------------------- */
/* ---------------------------- Local data types --------------------------- */
/* ---------------------------- Global variables --------------------------- */
/* ---------------------------- Local variables ---------------------------- */
char dataBuf[1024];

/* ----------------------- Local function prototypes ----------------------- */
/* ---------------------------- Local functions ---------------------------- */
/* ---------------------------- Global functions --------------------------- */
void
publishDimba(AppData *appMsg)
{
    AnSampleSet anSet;
    IOChg ioChg[NUM_DI_SAMPLES_GET];
    int err, n, i, j;

    jwOpen( dataBuf, sizeof(dataBuf), JW_OBJECT, JW_COMPACT );

    
    jwObj_int("id", atoi(ConMgr_ImeiSNR()));

    n = anSampler_getSet(&anSet, NUM_AN_SAMPLES_GET);

    if(n>0)
    {
        jwObj_object("anIn");
            jwObj_double("ts", anSet.timeStamp);
            jwObj_int("tsm", AN_SAMPLING_RATE_SEC);
            jwObj_array("an");
            for(i=0; i < NUM_AN_SIGNALS; ++i)
            {
                jwArr_array();
                for(j=0; j<n; ++j)
                {
                    jwArr_int(anSet.anSignal[i][j]);
                }
                jwEnd();
            }
            jwEnd();
        jwEnd();
    }

    n = IOChgDet_get(ioChg, NUM_DI_SAMPLES_GET);
    if(n > 0)
    {
        jwObj_array("dInChg");
        for(i=0; i < n; ++i)
        {
            jwArr_object();
                jwObj_double("ts", ioChg[i].timeStamp);
                jwObj_int("dIn", ioChg[i].signalId);
                jwObj_int("val", ioChg[i].signalValue);
            jwEnd();
        }
        jwEnd();
    }
    
    err = jwClose();

    appMsg->data = (rui8_t *)dataBuf;
    appMsg->size = (rui16_t)strlen(dataBuf);
}

/* ------------------------------ End of file ------------------------------ */

/************************************************************************/
/*																		*/
/*	System.h Header file defining system/processor dependent code       */
/*																		*/
/************************************************************************/
/*  Author:     Keith Vogel                                             */
/*  Copyright 2013, Digilent Inc.                                       */
/************************************************************************/
/* deIP core network library
*
* Copyright (c) 2013-2014, Digilent <www.digilentinc.com>
* Contact Digilent for the latest version.
*
* This program is free software; distributed under the terms of 
* BSD 3-clause license ("Revised BSD License", "New BSD License", or "Modified BSD License")
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* 1.    Redistributions of source code must retain the above copyright notice, this
*        list of conditions and the following disclaimer.
* 2.    Redistributions in binary form must reproduce the above copyright notice,
*        this list of conditions and the following disclaimer in the documentation
*        and/or other materials provided with the distribution.
* 3.    Neither the name(s) of the above-listed copyright holder(s) nor the names
*        of its contributors may be used to endorse or promote products derived
*        from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/************************************************************************/
/*  Module Description: 												*/
/*																		*/
/*	System dependent code, this module needs to be defined              */
/*	for each processor and/or board                                     */
/*																		*/
/************************************************************************/
/*  Revision History:													*/
/*																		*/
/*	8/15/2012(KeithV): Created											*/
/*																		*/
/************************************************************************/
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <alloca.h>
#include <string.h>
#include "xparameters.h"
#include "xil_types.h"
#include "xil_io.h"
#include "xil_cache.h"
#include "MRF24G/utility/ud_inc/internal/wf_global_includes.h"


#define byte u8
#ifdef XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ
#include "sleep.h"
#include "xtime_l.h"
#define GetSystemClock()        (XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ)
#else
#define GetSystemClock()        (XPAR_CPU_CORE_CLOCK_FREQ_HZ)
#include "MRF24G/utility/ud_inc/shared/wf_stubs.h"
#endif


#if !defined(min)
#define min(_a, _b) ((_a) > (_b) ? (_b) : (_a))
#define max(_a, _b) ((_a) > (_b) ? (_a) : (_b))
#endif

extern uint32_t GetPeripheralClock(void);

// probably not correct for the MX1 & 2
#define FLASH_SPEED_HZ          30000000



static inline uint32_t __attribute__((always_inline)) InitBoard(void)
{
	Xil_ICacheEnable();
	Xil_DCacheEnable();

    return(true);
}

// this will make the size a mult of 4 so the sizes will stall 4 bytes aligned
#define SYSAdjToDerefSize(_sizeAny) ((((uint32_t) (_sizeAny)) + 3) & 0xFFFFFFFC)

#define InitSysClock()
#define SYSTICKSPERSEC      (GetSystemClock())
#define SYSTICKSPERMSEC     (GetSystemClock()/1000)
#define SYSTICKSPERUSEC     (GetSystemClock()/1000000)

// configuration parameters
#define SYSLITTLE_ENDIAN    0
#define SYSBIG_ENDIAN       1

#define NETWORK_ORDER       SYSBIG_ENDIAN                  // RFC 1042
#define MACHINE_ORDER       SYSLITTLE_ENDIAN

void ExEndian(void * pb, int cb);
uint16_t CalculateChecksum(uint16_t sumComplement, void * pv, unsigned int cb);

u64 GetSysTick(void);
void SYSPeriodicTasks(void);
uint32_t SYSGetSecond(void);
uint32_t SYSGetMilliSecond(void);
uint32_t SYSGetMicroSecond(void);
uint32_t SYSGetSeqNumber(void);
void setPmodWifiAddresses(u32 SPI_BASEADDRESS, u32 WFGPIO_BASEADDRESS, u32 WFCS_BASEADDRESS, u32 TIMER_BASEADDRESS);
void setPmodWifiIntVector(u32 VectorNumber);

#endif // _SYSTEM_H_

﻿/*-----------------------------------------------------------------------------
-- File Name: Back_Task.c 
--
-- Copyright 2015 PremierTech as an unpublished work. 
-- All Rights Reserved.
--
-- The information contained herein is confidential property of 
-- Premier Tech.  The use, copying, transfer or disclosure of such
-- information is prohibited except by express written agreement with
-- Premier Tech.
--
-- First written on August, 2015 by Steve Santerre.
--
-- Module Description:
-- This file is dedicated to background_task function
------------------------------------------------------------------------------*/
int ScanTimeStart,ScanTimeEnd,ScanTime_ms,ScanTimeTotal,ScanTimeMax,ScanTime_msMax,ScanTimeBegin;
int ServiceModeStatus,feeddelaystart,feeddelayduration;  //0=Not in SM, 1=in SM, 2=just Out of SM


// Moved to Global functions.c #include "BT_DBases.h"
#include "FlexIOs.c"
#include "BT_Logic.c"

/*------------------------------------------------------------------------- 
--  Procedure Name    : BTInit
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : This function is called to initialize backgroundtask
--                     necessary values prior to use it
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void BTInit(void)
{
InputReg1 = 0;
InputReg2 = 0;

FaultResetReq();

MaxNumbOfIO = ReadMaxNumbOfIO();
if(SeqModeManager==0)  SeqModeManager   = stp_OFF_MODE;
if(SeqMaster==0)       SeqMaster        = stp_INIT;
if(Seq2Master==0)      Seq2Master       = stp_INIT;
if(SeqSpout==0)        SeqSpout         = stp_INIT;
if(SeqWeighPan==0)     SeqWeighPan      = stp_INIT;
if(SeqFeeder==0)       SeqFeeder        = stp_INIT;
if(SeqFeedSTD==0)      SeqFeedSTD       = stp_INIT;
if(SeqManDischarge==0) SeqManDischarge  = stp_INIT;
if(Seq2WeighPan==0)    Seq2WeighPan     = stp_INIT;
if(Seq2Feeder==0)      Seq2Feeder       = stp_INIT;
if(Seq2FeedSTD==0)     Seq2FeedSTD      = stp_INIT;
if(Seq2ManDischarge==0)Seq2ManDischarge = stp_INIT;
if(SeqKicker==0)       SeqKicker = stp_INIT;

ServiceModeStatus = 0;
InitDone = ON;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : IOErrorCheck
--  Created by        : Steve Santerre
--  Last modified on  : 2017/09
--  
--  Purpose           : This function is called to sense
--                     Digital IO errors
--  Value Parameters  : IOErrorMem = Already in Error
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
bool IOErrorCheck(bool IOErrorMem)
{
int error1,error2;
string group[1];  
  
  error1 = 0;
  error2 = 0;
 
  if(MaxNumbOfIO > 0 && MaxNumbOfIO <= 31)
   { 
    error1 = perror(MaxNumbOfIO,0);
   } 
  
  else
   {
    error1 = perror(31,0);
    error2 = perror(MaxNumbOfIO,32);
   }
 
 if(error1 || error2)
  {
   if(!IOErrorMem)
    {
      if(error2 >= 16777216)      group ="8";
      else if(error2 >= 65536)    group ="7";
      else if(error2 >= 256)      group ="6";
      else if(error2 >= 1)        group ="5";
      
      if(error1 >= 16777216)      group ="4";
      else if(error1 >= 65536)    group ="3";
      else if(error1 >= 256)      group ="2";
      else if(error1 >= 1)        group ="1";
      
      SystemErrorCode = concat("307 Digital IO Error - Group ",group);
    }
   return(ON);
  }
  
 else
  return(OFF);     
}

//Verify Discharge Door sensor State when it starts to close
void CheckDischDoor(void)
{ 
      if(O_DischDoorMem != IO_State[O_DischDoor1])
      {
        O_DischDoorMem = IO_State[O_DischDoor1];
        if(!IO_State[O_DischDoor1])
        {
         DischDoorStillClose = Input_State(I_DischDoorClose1);
        } 
      }
} 

//Verify Discharge Door sensor State when it starts to close#2
void CheckDischDoor2(void)
{ 
      if(O_DischDoorMem2 != IO_State[O_DischDoor2])
      {
        O_DischDoorMem2 = IO_State[O_DischDoor2];
        if(!IO_State[O_DischDoor2])
        {
         DischDoorStillClose2 = Input_State(I_DischDoorClose2);
        } 
      }
        
} 

//Verify Catch Gate sensor State when it starts to open
void CheckCatchGate(void)
{
    if(O_CatchGateMem != IO_State[O_CatchGate1])
      {
        O_CatchGateMem = IO_State[O_CatchGate1];
        if(IO_State[O_CatchGate1]) // Catch Gate Just Starts to Open
        {
         CatchGateAlreadyOpen = Input_State(I_CatchGateOpen1);
        } 
      }
}      
  
//Verify Catch Gate sensor State when it starts to open#2
void CheckCatchGate2(void)
{
    if(O_CatchGateMem2 != IO_State[O_CatchGate2])
      {
        O_CatchGateMem2 = IO_State[O_CatchGate2];
        if(IO_State[O_CatchGate2]) // Catch Gate Just Starts to Open
        {
         CatchGateAlreadyOpen2 = Input_State(I_CatchGateOpen2);
        } 
      }
}         

/*------------------------------------------------------------------------- 
--  Procedure Name    : background_task
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : This function runs indefinitely 
--                      as a parallel task to the main
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
//#define USE_INTERRUPT 
 
float ScanTimeOffset,scanavg;
int scan[20],scanmem[20],scanval[100],i,ScanTime_msMaxMem,scancnt,scansum,scanprev,scalestatus;
bool CheckScanTime,IOTestFlagMem;
string CPSource[1024],CPDest[10][63];
bool TESTLIM;

void FillingTask (void)
{
  iQRegisterEventReception ();
  InitDone = OFF;
  Refresh_BTInit=ON;

#ifndef USE_INTERRUPT  
for(;;)
{
#endif
  
  scanFTBegin = systemtimer_ms();
  ScanFTInterval = scanFTBegin - scanFTLast;
  scanFTLast = scanFTBegin;
  
  if(!FillingTaskHeartBeat) 
   {
    FillingTaskHeartBeat = ON;
   } 
  
  
  if (Refresh_BTInit) 
  {
    BTInit();
    Refresh_BTInit=OFF;
  }
    
 

          scan[0] = systemtimer_ms();
  
           ScaleStatus[Scale1] = getweight(Scale1Adm);
           IsSettled[Scale1]      = issettled;
           IsZero[Scale1]         = iszero;
           NetWeight[Scale1]      = net;
           NetWeightHiRes[Scale1] = nethires;
           MaxWeight[Scale1]      = capacity;
           DP[Scale1]             = dp;
           
           ScaleStatus[Scale2] = getweight(Scale2Adm);
           IsSettled[Scale2]      = issettled;
           IsZero[Scale2]         = iszero;
           NetWeight[Scale2]      = net;
           NetWeightHiRes[Scale2] = nethires;
           MaxWeight[Scale2]      = capacity;
           DP[Scale2]             = dp;
           
            if(ServiceModeEntered)
            {
             SMEntered = ON;
            }
             
           if(RestartPopupClosed)
            {
             SMEntered = OFF;
             RestartPopupClosed = OFF;
            } 

               
           if (SMEnteredMEM != SMEntered)
           {    
            SMEnteredMEM = SMEntered;
            ChangeSMStateFlag = Execute;
           }
      
      if(InitDone)
         {     
          scan[1] = systemtimer_ms();
           
           if(!ServiceModeEntered)
               IOError = IOErrorCheck(IOError);
               
              switch (Current_Screen)
              {
               case SCREEN_IOTEST_IN1:
               case SCREEN_IOTEST_IN2:
               case SCREEN_IOTEST_IN3:
                 {
                 InTest = ON;
                 if(!ServiceModeEntered && !IOError)IN_Refresh(); 
                 }
                 break;
               
               case SCREEN_IOCFG_IN1:
               case SCREEN_IOCFG_IN2:
               case SCREEN_IOCFG_IN3:
               case SCREEN_IOCFG_OUT1:
               case SCREEN_IOCFG_OUT2:
               case SCREEN_IOCFG_OUT3:
               case SCREEN_IOCFG_OUT4:
                    IOCFG_Active = ON;
                 break;
                   
               default : 
                         InTest = OFF;
                         IOCFG_Active = OFF;
                         if(!ServiceModeEntered && !IOError)IN_Refresh2();
              }
          scan[2] = systemtimer_ms(); 
            DischReqCheck();    
          scan[3] = systemtimer_ms();    

           SEQ_ModeManager();
          scan[4] = systemtimer_ms(); 
           SEQ_Master();
           SEQ_2Master();
          scan[5] = systemtimer_ms(); 
           SEQ_Feeder();
           SEQ_2Feeder();
          scan[6] = systemtimer_ms(); 
           SEQ_FeedSTD();
           SEQ_2FeedSTD();
          scan[7] = systemtimer_ms(); 
           SEQ_WeighPan();
           SEQ_2WeighPan();
          scan[8] = systemtimer_ms(); 
           SEQ_ManDischarge();
           SEQ_2ManDischarge();
          scan[9] = systemtimer_ms(); 
           SEQ_Spout();
          scan[10] = systemtimer_ms();  
           KnockHammer();
          scan[11] = systemtimer_ms();
          SEQ_Kicker();
          
           
              LimitActuator();
              LimitActuator2();
              
          if(WeighingDataRefreshFlag[Scale1])
          {
           WeighingDataRefresh(1);
           WeighingDataRefreshFlag[Scale1] = OFF;
          } 
 
          if(WeighingDataRefreshFlag[Scale2])
          {
           WeighingDataRefresh(2);
           WeighingDataRefreshFlag[Scale2] = OFF;
          }
     
              switch (Current_Screen)
              {
               case SCREEN_IOTEST_OUT1:
               case SCREEN_IOTEST_OUT2:
               case SCREEN_IOTEST_OUT3:
               case SCREEN_IOTEST_OUT4:
                 {
                   if(iQOutputEnabled[Scale1])iQOutRelease(1);
                   if(iQOutputEnabled[Scale2])iQOutRelease(2);
                   if(!ServiceModeEntered && !IOError)
                    {
                    OutTest = ON;
                    Force_Out ();
                    }
                 }
                 break;
               case SCREEN_ANALOGTEST: 
                 {
                   OutTest = ON;
                   if(!ServiceModeEntered && !IOError)OUT_Refresh();
                 }
                 break;
               
               case SCREEN_IOCFG_IN1:
               case SCREEN_IOCFG_IN2:
               case SCREEN_IOCFG_IN3:
               case SCREEN_IOCFG_OUT1:
               case SCREEN_IOCFG_OUT2:
               case SCREEN_IOCFG_OUT3:
               case SCREEN_IOCFG_OUT4:
                 break;
                   
               default : OutTest = OFF;
                         if(!ServiceModeEntered && !IOError)
                          {
                           if(InTest)
                              {
                               OUT_Refresh();
                              } 
                            else
                             {   
                              RefreshFeederOutputs();
                              OUT_Refresh2();
                             } 
                          }   
              }
              
              IOTestFlag = InTest || OutTest;
              if(!IOTestFlag && IOTestFlagMem)
               {
                OutResetFlag = Execute;
               }
              IOTestFlagMem = IOTestFlag;
               
              if(!ServiceModeEntered && Fault_Type[FLT_GEN] == 0) 
               {
                Flex_Outputs();
                Flex_Counter();
               }

              if(!AutoMode)
               {
                if (Current_Screen==SCREEN_IOCFG_OUT1 || Current_Screen==SCREEN_IOCFG_OUT2 || Current_Screen==SCREEN_IOCFG_OUT3 || Current_Screen==SCREEN_IOCFG_OUT4)
                  {
                   IOCFG_OUT_Flag = ON;
                  }
                else
                 if (IOCFG_OUT_Flag)
                  {
                    IOCFG_OUT_Flag = OFF;
                    CheckOutput = ON;
                  }
               }   
                
              if(CheckOutput)
               {
                CheckOutputConfig();
                CheckOutput = OFF;
               }
              CheckDischDoor2();
              CheckDischDoor();
              CheckCatchGate();
              CheckCatchGate2();
              
              if(TESTLIM)
               {
               CutoffCorrection(1);
               TESTLIM = OFF;
               }
                
             updateio(); 
         }
         scan[12] = systemtimer_ms();

//Scan Equalizing with delay() function  
  if(CheckScanTime)
   {            
    ScanTimeEnd = systemtimer_ms();
    ScanTotal = ScanTimeEnd - ScanTimeBegin;
    ScanTimeBegin = systemtimer_ms();
    ScanTime_ms = (ScanTimeEnd - ScanTimeStart); //*10;
    ScanTimeOffset = Lim(ScanMin,ScanMax,string(ScanMax-(ScanTime_ms/1000.0)));
#ifndef USE_INTERRUPT      
    delay (ScanTimeOffset);                                                      
#endif
    ScanTimeTotal = ScanTime_ms + (ScanTimeOffset*1000);
    if(ScanTimeTotal > ScanTimeMax)   ScanTimeMax =ScanTimeTotal;
    if(ScanTime_ms > ScanTime_msMax)  ScanTime_msMax = ScanTime_ms;        
   }
   

//Scan Average Calculation  
  scanprev = scanval[scancnt];
  scanval[scancnt] = ScanTime_ms;
  scansum = scansum + ScanTime_ms - scanprev;
  scanavg = scansum / 100.0;
  scancnt++;
  if(scancnt>99) scancnt = 0; 
  
//scanmem to log which function is taking scan time  
  if(ScanTime_msMax >= 20)
   {
   ScanTime_msMaxMem = ScanTime_msMax;
   ScanTime_msMax=0;
    for(i=0;i<20;i++)
     {
      scanmem[i] = scan[i];
     }
   }
    
//must stay at the end
  ScanTimeStart= systemtimer_ms();
  CheckScanTime = ON;
        
#ifndef USE_INTERRUPT  
} 
#endif
}
/*-----------------------------------------------------------------------------
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
if(SeqModeManager==0)  SeqModeManager  = stp_OFF_MODE;
if(SeqMaster==0)       SeqMaster       = stp_INIT;
if(SeqSpout==0)        SeqSpout        = stp_INIT;
if(SeqWeighPan==0)     SeqWeighPan     = stp_INIT;
if(SeqFeeder==0)       SeqFeeder       = stp_INIT;
if(SeqFeedSTD==0)      SeqFeedSTD      = stp_INIT;
if(SeqManDischarge==0) SeqManDischarge = stp_INIT;

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
    return (OFF);     
}

//Verify Discharge Door sensor State when it starts to close
void CheckDischDoor(void)
{ 
    if(O_DischDoorMem != IO_State[O_DischDoor])
      {
        O_DischDoorMem = IO_State[O_DischDoor];
        if(!IO_State[O_DischDoor])
        {
         DischDoorStillClose = Input_State(I_DischDoorClose);
        } 
      }
} 

//Verify Catch Gate sensor State when it starts to open
void CheckCatchGate(void)
{
    if(O_CatchGateMem != IO_State[O_CatchGate])
      {
        O_CatchGateMem = IO_State[O_CatchGate];
        if(IO_State[O_CatchGate]) // Catch Gate Just Starts to Open
        {
         CatchGateAlreadyOpen = Input_State(I_CatchGateOpen);
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
int FTcycleCnt;
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
    FTcycleCnt = 0;
   } 
  else FTcycleCnt++;
  
  if (Refresh_BTInit) 
  {
    BTInit();
    Refresh_BTInit=OFF;
  }
    
 

          scan[0] = systemtimer_ms();
  
           ScaleStatus[Scale1] = getweight(Scale1Adm);
           if(ScaleStatus[Scale1]!=0) 
             scalestatus = ScaleStatus[Scale1];
           IsSettled[Scale1]      = issettled;
           NetWeight[Scale1]      = net;
           NetWeightHiRes[Scale1] = nethires;
           MaxWeight[Scale1]      = capacity;
           
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
                 if(!ServiceModeEntered && !IOError)
                 IN_Refresh(); 
                 }
                 break;
               
               case SCREEN_IOCFG_IN1:
               case SCREEN_IOCFG_IN2:
               case SCREEN_IOCFG_IN3:
               case SCREEN_IOCFG_OUT1:
               case SCREEN_IOCFG_OUT2:
               case SCREEN_IOCFG_OUT3:
                    IOCFG_Active = ON;
                 break;
                   
               default : InTest = OFF;
                         IOCFG_Active = OFF;
                         if(!ServiceModeEntered && !IOError)
                         IN_Refresh2();
              }
          
          scan[2] = systemtimer_ms(); 
           DischReqCheck();    
          scan[3] = systemtimer_ms();    
           SEQ_ModeManager();
          scan[4] = systemtimer_ms(); 
           SEQ_Master();
          scan[5] = systemtimer_ms(); 
           SEQ_Feeder();
          scan[6] = systemtimer_ms(); 
           SEQ_FeedSTD();
          scan[7] = systemtimer_ms(); 
           SEQ_Spout();
          scan[8] = systemtimer_ms(); 
           SEQ_WeighPan();
          scan[9] = systemtimer_ms(); 
           SEQ_ManDischarge();
          scan[10] = systemtimer_ms(); 
           KnockHammer();
          scan[11] = systemtimer_ms();
          SEQ_Kicker();
          
           
          LimitActuator();
          
          if(WeighingDataRefreshFlag)
          {
           WeighingDataRefresh();
           WeighingDataRefreshFlag = OFF;
          } 
                   
              switch (Current_Screen)
              {
               case SCREEN_IOTEST_OUT1:
               case SCREEN_IOTEST_OUT2:
               case SCREEN_IOTEST_OUT3:
                 {
                   if(iQOutputEnabled)iQOutRelease();
                   if(!ServiceModeEntered && !IOError)
                    {
                    OutTest = ON;
                    //OUT_Refresh();
                    Force_Out ();
                    }
                 }
                 break;
               case SCREEN_ANALOGTEST: 
                 {
                   OutTest = ON;
                   if(!ServiceModeEntered && !IOError)
                   OUT_Refresh();
                 }
                 break;
               
               case SCREEN_IOCFG_IN1:
               case SCREEN_IOCFG_IN2:
               case SCREEN_IOCFG_IN3:
               case SCREEN_IOCFG_OUT1:
               case SCREEN_IOCFG_OUT2:
               case SCREEN_IOCFG_OUT3:
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
                if (Current_Screen==SCREEN_IOCFG_OUT1 || Current_Screen==SCREEN_IOCFG_OUT2 || Current_Screen==SCREEN_IOCFG_OUT3)
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
               
               CheckDischDoor();
               CheckCatchGate();
               
               if(TESTLIM)
               {
               CutoffCorrection();
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
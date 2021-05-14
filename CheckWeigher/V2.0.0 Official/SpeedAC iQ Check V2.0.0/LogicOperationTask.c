/*-----------------------------------------------------------------------------
-- File Name: LogicOperationTask.c 
--
-- Copyright 2016 PremierTech as an unpublished work. 
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
-- This file is dedicated to LogicOperationTask function
------------------------------------------------------------------------------*/
int scanPLC,scanPLCmem;

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Status_Refresh
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Refresh Different Functions to Updates Values, Flags
--                      Every Cycle
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Limit TMAX to avoid scanning to many timers
--------------------------------------------------------------------------------*/  
void Status_Refresh(void)
{
 bool result[2];

 if(!T_EN[T_FirstScan] && !ServiceModeEntered && InitDone) 
  {
  T_PRE[T_FirstScan]=5.00;
  T_EnOn(T_FirstScan);
  }

 if(T_Dn(T_FirstScan))
 {
  if(!FirstScanBT)
   {
    
    FirstScanBT = ON;
   } 
   
  
  if (Reset_FlexIOFlag != Done)
  {
    Reset_FlexIO();
    Reset_FlexIOFlag = Done;
  }

  if (FlexIO_SetTPresetsFlag != Done)
  {  
    FlexIO_SetTPresets();
    FlexIO_SetTPresetsFlag = Done;
  }

 
  if (ChangeSMStateFlag != Execute && CurrentLevelMem != CurrentLevel)
   {    
     ChangeSMStateFlag = Execute;
   }
 
 
  if(MemRecipe != RecipeMem) 
   {
    
    RecipeMem = MemRecipe;
    TolChanged = ON;
    CopyLearnToNovFlag = Execute;
   }
 
   
  if(VarInitOffFlag != Done)
   {
    VarInitOff();
    VarInitOffFlag = Done;
   }
  
  if(OutResetFlag != Done)
   {
     OutReset();
     OutResetFlag = Done;
   }
  
  //Check All Weight-Release Check Managment
  if(CheckWeightHMI)
   {
   if(CheckWeight_State == ReleaseWeight) CheckWeight_State = CheckAllWeight;
   else CheckWeight_State = ReleaseWeight;
   CheckWeightHMI = OFF;
   }
   
  if(CheckWeight_State != CheckAll) 
  { 
   CheckAll=CheckWeight_State;
   if(!CheckAll) 
    Simul = OFF;
   else
    Simul = SimulInit;
  }    
  
  if(AutoTuneHMI)
  {
   AutoTuneHMI = OFF;
   //AutoTune = AutoTuneON;
   AutoTune = !AutoTune;
  }
  
  if(TD_SetFlag) 
  {
  settime(TD_Year,TD_Month,TD_Day,TD_Hour,TD_Minute,0);
  TD_SetFlag = OFF;
  } 
  
  if(SystemMem == -1)
   {
     CheckSystem(OFF);
     SystemMem = MC.System;
   }  
  
    
  RefreshGrayoutFlag = ON;
 
 }             
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : RegistrationCheck
--  Created by        : Steve Santerre
--  Last modified on  : 2016/06
--  
--  Purpose           : Registration Key Verification on start-up
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void RegistrationCheck(void)
{
int     class, type, value;
string  args[4][255];
string  KeyEntering[14];
bool    RegistrationOK, err;
  
  flashload();
  KeyEntering = "";
    if(!iQRegistrationKeyCheck(RegistrationKey,RTC_MacAdress))
      {
        infobox("");
        WeightDisplayFull(No_Forcing);
        SelectAndWaitPage(PAGE_REGISTRATION);
        widget_text(REGISTRATION_ROW1_INPUT,RTC_MacAdress);
        
        do
        {
       
        
        if (eventreceived())
          {
           readevent (class, type, value, args); 
           if (type !=  EVENT_TYPE_CONNECTION_ESTABLISHED)
            {  
                    switch (value)
                    {
                      case REGISTRATION_ROW2_INPUT:
                      KeyEntering = args[0];
                      break;
                      
                      case REGISTRATION_BUTTON_1:
                      RegistrationOK = iQRegistrationKeyCheck(KeyEntering,RTC_MacAdress);
                      if(RegistrationOK) 
                       {
                         infobox (concat(space(2),"  VALID REGISTRATION KEY  ",space(2)));
                         delay(5);
                         infobox ("");
                         RegistrationKey = KeyEntering;
                         err = flashsave();
                       }
                          
                      else 
                       {
                         infobox (concat(space(2),"  INVALID REGISTRATION KEY  ",space(2)));
                         delay(5);
                         infobox ("");
                         widget_text(REGISTRATION_ROW2_INPUT,"");
                       }
                      break;
                    }
                   dropevents(); 
            }
            else
             {
                RefreshRemoteDisplay(WEIGHT_DISPLAY_FULL);
                widget_text(REGISTRATION_ROW1_INPUT,RTC_MacAdress);
             }          
          }
        delay(0.1);  
        }  
        while(!RegistrationOK);  
        
        
      }      
      else
      {
       infobox (concat(space(2),"  VALID REGISTRATION KEY  ",space(2)));
       delay(10);
       infobox ("");
      }

    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LogicOperationTask
--  Created by        : Steve Santerre
--  Last modified on  : 2016/01
--  
--  Purpose           : This function runs indefinitely 
--                      as a parallel task to the main
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void LogicOperationTask(void)
{
int i,j,LOTcycleCnt;
string time_tempo[6],date_tempo[6];

 for(;;)
 {
 Status_Refresh();
 if(T_Dn(T_FirstScan))
  {
  scanLOTBegin = systemtimer_ms();
  ScanLOTInterval = scanLOTBegin - scanLOTLast;
  scanLOTLast = scanLOTBegin;
  
  if(!OperationTaskHeartBeat) 
   {
    OperationTaskHeartBeat = ON;
    LOTcycleCnt = 0;
   } 
  else LOTcycleCnt++;
  
  if(!IOTestFlag) FaultMonitor();
  
  if(Fault_Status_MEM != Fault_Status || Current_Screen!=Current_ScreenMEM2) 
   {
    Current_ScreenMEM2 = Current_Screen;
    FaultLight_Set();
   }
  
   if(!IOCFG_Active)
    WP_IOs();
  
  if(ResetDataHMI)
   {
     ResetData(OFF);
   }
   
  if(ResetBatchHMI)
   {
     ResetBatch();
   } 
  
  if(ResetLifetimeDataHMI)
   {
     ResetLifetimeData();
   }  
  
  if(RefreshGrayoutFlag)
   {
     RefreshGrayout();
     RefreshGrayoutFlag = OFF;
   } 
  
   if (!TD_SetFlag) 
    {
     gettime();
     time_tempo = "";
     date_tempo = "";
     for(i=0;i<=5;i++)
     {
      time_tempo = concat(time_tempo,char(date[TIME+i]));
      date_tempo = concat(date_tempo,char(date[DATE+i]));
     } 
      Seconds = right(time_tempo,2);
      TimeString = concat(left(time_tempo,2),":",sub(time_tempo,2,2),":",right(time_tempo,2));
      DateNbr = int(date_tempo);
      DateRefreshed = ON;
    } 

  
  if (FB_Detected)
   {
     scanPLCmem = systemtimer_ms();
     PLC_Communication();
     scanPLC = systemtimer_ms()- scanPLCmem;
   }

   
   if (ProdDataReady)
     {
      PrintUnitRecord();
      ProdDataReady = OFF;
     }
   
   if(ProdDataReadyPLC)
    {
     if(!T_EN[T_ProdDataReady])
      {
       T_EnOn(T_ProdDataReady);
      }
      
      if(T_Dn(T_ProdDataReady))
       {
        ProdDataReadyPLC = OFF;
        T_EnOn(T_ProdDataReady);
       }
    }   
        

  
  scanLOT = systemtimer_ms()- scanLOTBegin;
  }                   
   if(!CheckAnalyseStarted && !ZeroAnalyseStarted)
    delay(LOTdelay);
   else
    delay(LOTdelayAT); 
 }

}
 
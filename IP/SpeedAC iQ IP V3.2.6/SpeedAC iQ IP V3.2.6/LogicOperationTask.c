﻿/*-----------------------------------------------------------------------------
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
 int ScreenSaverTimeMem; 
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
    result[0] = SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_SCALE);
    result[1] = iQReadCalFilterSize(SCALE_CHANNEL, SCALE_NUMBER,SMFilterSize);
    FirstScanBT = ON;
   } 

  LowLevelStatus();
  OK4BulkFeed = ON;
  OK4IntermFeed = ON;
  OK4DribbleFeed = ON;
      
  if (IO_Enable[I_HopperEmpty])
  {
   if (Input_State(I_HopperEmpty)&&!I_HopperEmptyMem)
   {
    I_TglEmptyHopper=ON;
    I_HopperEmptyMem=ON;
   }
   else if (!Input_State(I_HopperEmpty)&&I_HopperEmptyMem)
    I_HopperEmptyMem=OFF;
  }
                                                                        
  //Hopper State Display
  if (HopperHMI || I_TglEmptyHopper || (Hopper_State != Hopper_StateMEM && Current_Screen==SCREEN_AUTOMATIC))
               {
                     if (HopperHMI|| I_TglEmptyHopper)
                     {
                       HopperHMI = OFF;
                       I_TglEmptyHopper=OFF;
                     }
                       
                     if (SeqModeManager != stp_OFF_MODE && SeqModeManager != stp_STOP_MODE)  
                     { 
                       if (Hopper_State == HopperFill)  Hopper_State=HopperEmpty;
                       else if (Hopper_State == HopperEmpty)   Hopper_State=HopperFill;
                       Hopper_StateMEM = Hopper_State;
                     }

                     
                     if(Current_Screen==SCREEN_AUTOMATIC)
                     {         
                     HopperStateFlag = Execute;
                     }     

                     EmptyHopper = (Hopper_State == HopperEmpty);
                           
               }
               
  //Discharge Pan States Display
  if (Discharge_State != Discharge_StateMEM && Current_Screen==SCREEN_AUTOMATIC)
    if(DischargeStateFlag != Execute)
               {         
                DischargeStateFlag = Execute;
               }
              
  if(DischargeHMI && Discharge_State == DischPanOff) DischargeHMI = OFF;

  //Check All Weight-Release Check Managment
  if(CheckWeightHMI)
   {
   if(CheckWeight_State == ReleaseWeight) CheckWeight_State = CheckAllWeight;
   else CheckWeight_State = ReleaseWeight;
   CheckWeightHMI = OFF;
   }
   
  if(CheckWeight_State != CheckAll) CheckAll=CheckWeight_State; 

  //Evaluate Target Weight
  if(WP.NominalWeight != NominalWeightMem || WP.Overfill != OverfillMem || CutoffTempMem != CutoffTemp || WP.Cutoff != CutoffTemp || TargetPLC)//commented by namk 21/9/2018  //SADM2 2020 November
   {
    if(TargetPLC) //SADM2 2021
     {
      WP.NominalWeight = NominalWeightMem;
      TargetPLC = OFF;
     }
   
    if(!TargetWeightControlON() && !BulkByWeightON && !BatchByWeightON)//added by namk 21/9/2018
    {//added by namk 21/9/2018
    TargetWeight[Scale1] = WP.NominalWeight + WP.Overfill;
    NominalWeightMem = WP.NominalWeight;
    OverfillMem = WP.Overfill;
    CutoffTemp = WP.Cutoff; //SADM2 2020 November
    CutoffTempMem = CutoffTemp;//added by namk 21/9/2018
    }//added by namk 21/9/2018
    else//added by namk 21/9/2018
    {//added by namk 21/9/2018
     if(LastTwoWeighment)
      {
       CutoffTemp = CutoffTemp; //SADM2 2020 November
      }
      else
      {
       CutoffTemp = WP.Cutoff; //SADM2 2020 November
      }
    CutoffTempMem = CutoffTemp;//added by namk 21/9/2018  //SADM2 2020 November
    TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);  //SADM2 2020 November
    TargetWeight[Scale1] = TargetWeightBatchTemp + WP.Overfill;//added by namk 21/9/2018
    NominalWeightMem = WP.NominalWeight;//added by namk 21/9/2018
    OverfillMem = WP.Overfill;//added by namk 21/9/2018
    //CutoffTempMem = CutoffTemp;//added by namk 21/9/2018  //SADM2 2020 November
    }//added by namk 21/9/2018
    RefreshAutoScreenReq();
   }


  
 //Re-initialize iQFeed Learning
  if(MinFeedingMem != WP.MinFeeding) 
  {
   MinFeedingMem = WP.MinFeeding;
   CopyLearnToNovFlag = Execute;
   if(WP.FeedAlgoType == FeediQSmart)LearniQSmartParam=ON;
   if(WP.FeedAlgoType == FeediQFlash)LearniQFlashParam=ON;
  }
 
  if(MaxFeedingMem != WP.MaxFeeding) 
  {
  MaxFeedingMem = WP.MaxFeeding;
  CopyLearnToNovFlag = Execute;
  if(WP.FeedAlgoType == FeediQSmart)LearniQSmartParam=ON;
  if(WP.FeedAlgoType == FeediQFlash)LearniQFlashParam=ON;
  }
 
  if(TargetWeightMem[Scale1] != TargetWeight[Scale1]) 
  {
  TargetWeightMem[Scale1] = TargetWeight[Scale1];
  CopyLearnToNovFlag = Execute;
  if(WP.FeedAlgoType == FeediQSmart)LearniQSmartParam=ON;
  if(WP.FeedAlgoType == FeediQFlash)LearniQFlashParam=ON;
  }

  if(StdFilterSizeMem != MP.StdFilterSize)
  {
   StdFilterSizeMem = MP.StdFilterSize;
  }
 
  if(iQFlSwitchWeightMem != iQFlSwitchWeight)
  {
   iQFlSwitchWeightMem = iQFlSwitchWeight;
   CopyLearnToNovFlag = Execute;
   if(WP.FeedAlgoType == FeediQFlash)LearniQFlashParam=ON;
  }
  
  if(iQFlReduceOutputMem != iQFlReduceOutput)
  {
   iQFlReduceOutputMem = iQFlReduceOutput;
   CopyLearnToNovFlag = Execute;
   if(WP.FeedAlgoType == FeediQFlash)LearniQFlashParam=ON;
  }
 
  if(iQFlControlTimeMem != iQFlControlTime)
  { 
   iQFlControlTimeMem = iQFlControlTime;
   CopyLearnToNovFlag = Execute;
   if(WP.FeedAlgoType == FeediQFlash)LearniQFlashParam=ON;
  }
 
  if(AutoTuneHMI)
  {
  AutoTuneHMI = OFF;
  if(WP.FeedAlgoType == FeediQSmart)LearniQSmartParam=ON;
  if(WP.FeedAlgoType == FeediQFlash)LearniQFlashParam=ON;
  AutoTune_State = AutoTuneON;
  AutoTuneStateFlag = Execute;
  }

  if(TD_SetFlag) 
  {
  settime(TD_Year,TD_Month,TD_Day,TD_Hour,TD_Minute,0);
  TD_SetFlag = OFF;
  } 

  //AutoMode Flag
  if(SeqModeManager == stp_PREP_MODE || SeqModeManager == stp_AUTO_MODE || SeqModeManager == stp_STOPPING_MODE)
   {
   if(!AutoMode) AutoMode = ON;
   }
  else
   {
   if(AutoMode) AutoMode = OFF;
   }
 
  if(WP.FeedAlgoType != FeedAlgoTypeMem || FirstScanCheckLearn)
  {
  ButtonDisplayRefreshed[SCREEN_GOTO] = OFF;
  FeedAlgoTypeMem = WP.FeedAlgoType;
  CopyLearnToNovFlag = Execute;
  FirstScanCheckLearn = OFF;
  } 

 
  
  if (MP.ScreenSaverTime != ScreenSaverTimeMem)
   {
   writeparameter ("General","LightOffTime",concat(trim(string(MP.ScreenSaverTime))));
   ScreenSaverTimeMem = MP.ScreenSaverTime;
   }
   
  if(SaveiQFeedParamFlag != Done)
   if(SeqModeManager == stp_OFF_MODE || SeqModeManager == stp_STOP_MODE)
   {
     if(WP.FeedAlgoType == FeediQSmart)
     {
        WP.CPSmFastAvgPoints = CPSmFastAvgPointsMem;
        WP.CPSmSlowAvgPoints = CPSmSlowAvgPointsMem;
        WP.CPSmSlowItpPoints = CPSmSlowItpPointsMem;
        WP.CPSmSwitchTime    = CPSmSwitchTimeMem;
     }  
    if(WP.FeedAlgoType == FeediQFlash)
     {
        WP.CPFlFastPoints      = CPFlFastPointsMem;
        WP.CPFlDeviationPoints = CPFlDeviationPointsMem;
     }
   SaveWPFlag = Execute;   
   SaveiQFeedParamFlag = Done;
   }
     
  if(MC.AutoSaveCorrection)
   if(CutoffCorrOffset[Scale1] != 0)
  {
     WP.Cutoff = WP.Cutoff - CutoffCorrOffset[Scale1];
     CutoffCorrOffset[Scale1] = 0;
     SaveWPFlag = Execute;
     KeepSampling = ON;
     
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
    CutoffCorrOffset[Scale1] = 0;
    RecipeMem = MemRecipe;
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
   
  if(MC.NumberOfScale != 1) MC.NumberOfScale = 1;
  
  if(WP.BulkMode == ByTime && WP.FeedAlgoType == FeedStd) BulkOnTime[Scale1] = ON;
  else BulkOnTime[Scale1] = OFF;

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
--  Procedure Name    : HopperRefill
--  Created by        : Steve Santerre
--  Last modified on  : 2016/02
--  
--  Purpose           : This function is called to Activate/Deactivate
--                      Test Weights
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
 void HopperRefill(void)
 {
 if(IO_Enable[O_HopFillReq])
  {
   if(AutoMode && !EmptyHopper && Input_State(I_HighLevelSensor)) //High Level = (0 if Product, 1 if No product)
     {
      if(!T_EN[T_RefillingTimeT] && MC.RefillingTimeT > 0) T_EnOn(T_RefillingTimeT);
      if(T_Dn(T_RefillingTimeT) || MC.RefillingTimeT <= 0 || !Input_State(I_LowLevelSensor)) Output_ON(O_HopFillReq); //Low Level = (0 if NO Product, 1 if Product)
     }
    else
    {
     Output_OFF(O_HopFillReq);
     T_EnOff(T_RefillingTimeT);
    } 
  
  if(!EmptyHopper && IO_Enable[I_HighLevelSensor] && !Input_State(I_HighLevelSensor) && !Input_State(I_LowLevelSensor))
     if(!FaultState(FltS_HopperIllogicalDetection)) FaultHandler(FltS_HopperIllogicalDetection,"");  
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
int SecondMem; //added by namk 05/10/2018
string time_tempo[6],date_tempo[6];
bool FirstChecked;


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
  
  /*
  #ifndef __SIMULATION__ 
  if(LOTHB_main)
  {
  if(LOTcycleCnt >= 50) //50 * 100ms = 5sec
   {
    if(MainTaskStopped()) 
     LOTcycleCnt = 0;
     RebootTerminal();
   }
  }  
  #endif
  */
  
  //added by namk 05/10/2018
  gettime();
  Minute = date[15];
  Second = date[16];  
  TimeOfShift = sub(time,0,5);
  if(!FirstChecked)
  {
    if(LastShiftTime == "") LastShiftTime = ReadPresentDateTime();
    if(LastHourlyTime == "") LastHourlyTime = ReadPresentDateTime();
    if(LastShiftTotalWeightLT == 0) LastShiftTotalWeightLT = ProdTotalWeightLT[Scale1];
    if(LastShiftTotalUnitsLT == 0) LastShiftTotalUnitsLT = ProdTotalUnitsLT[Scale1];
    if(LastHourlyTotalWeightLT == 0)LastHourlyTotalWeightLT = ProdTotalWeightLT[Scale1];
    if(LastHourlyTotalUnitsLT == 0)LastHourlyTotalUnitsLT = ProdTotalUnitsLT[Scale1];
    FirstChecked = ON;
  }
  
  //shift management 
  if((TimeOfShift == MP.EndOfShift1 || TimeOfShift == MP.EndOfShift2 || TimeOfShift == MP.EndOfShift3 || TimeOfShift == MP.EndOfShift4) 
  && Second == 0 && !ProdShiftReady)
  {   
    ProdTotalWeightOfShift = ProdTotalWeightLT[Scale1]- LastShiftTotalWeightLT;
    ProdTotalUnitOfShift = ProdTotalUnitsLT[Scale1]- LastShiftTotalUnitsLT;
    LastShiftTotalWeightLT = ProdTotalWeightLT[Scale1];
    LastShiftTotalUnitsLT = ProdTotalUnitsLT[Scale1];
    
    CurrentShiftTime = ReadPresentDateTime(); 
    STR_SHIFT_CURRENT_PROD = lsub(TX_SHIFT_PAGE);   
    STR_ShiftBeginTime = LastShiftTime;
    STR_ShiftEndTime = CurrentShiftTime;
    STR_ShiftTotalWeight = trim(string(ProdTotalWeightOfShift));
    LastShiftTime = ReadPresentDateTime();  
    PrintReqOnShift = ON;  
    ProdShiftReady = ON;
    //PrintShiftRecord(); //Disable shift record string 10/12/2018
  }
  else if(Second > 0)
  {
    if(ProdShiftReady)
    {
    PrintReqOnShift = OFF; 
    ProdShiftReady = OFF;
    }
  }
  
  //hourly management
  if(Minute == 0 && Second == 0 && !ProdHourlyReady)
  {
    ProdTotalWeightOfHourly = ProdTotalWeightLT[Scale1]- LastHourlyTotalWeightLT;
    ProdTotalUnitOfHourly = ProdTotalUnitsLT[Scale1] - LastHourlyTotalUnitsLT; 
    CurrentShiftUsageWeight = ProdTotalWeightOfShift+(ProdTotalWeightLT[Scale1] - ProdTotalWeightOfShift);
    LastHourlyTotalWeightLT = ProdTotalWeightLT[Scale1];
    LastHourlyTotalUnitsLT = ProdTotalUnitsLT[Scale1]; 
    
    CurrentHourlyTime = ReadPresentDateTime();
    STR_HOURLY_CURRENT_PROD = lsub(TX_HOURLY_PAGE);
    STR_HourlyBeginTime = LastHourlyTime;
    STR_HourlyEndTime = CurrentHourlyTime;
    STR_HourlyTotalWeight = trim(string(ProdTotalWeightOfHourly));
    STR_CurrentShiftUsage = trim(string(CurrentShiftUsageWeight));
    LastHourlyTime = ReadPresentDateTime();
    PrintReqOnHourly = ON;
    ProdHourlyReady = ON;
    //PrintHourlyRecord();////Disable hourly record string 10/12/2018
  }
  else if(Second > 0)
  {
    if(ProdHourlyReady)
    {
    ProdHourlyReady = OFF;
    PrintReqOnHourly = OFF;
    }
  }
    
  //End of added by namk 05/10/2018
  
  if(!IOTestFlag) FaultMonitor();
  
  if(Fault_Status_MEM != Fault_Status || Current_Screen!=Current_ScreenMEM2) 
  {
    Current_ScreenMEM2 = Current_Screen;
    FaultLight_Set();
  }
  
  if(!IOCFG_Active)
    {
     WP_IOs();
    }
    
  HopperRefill();
  
  if(ResetDataHMI)
   {
     ResetData(OFF);
   }
   
  if(ResetBatchHMI)
   {
     ResetBatch();
   }
   
   if(BatchReset)  //SADM2 2020 November
   {
     BatchReset = OFF;  //SADM2 2020 November
     ResetBatch(); //SADM2 2020 November
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
   delay(0.1);
 }

}
 
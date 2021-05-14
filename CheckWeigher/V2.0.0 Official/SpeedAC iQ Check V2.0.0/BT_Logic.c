﻿/*-----------------------------------------------------------------------------
-- File Name: BT_Logic.c 
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
-- This file is dedicated to all control logic and peripheral functions
------------------------------------------------------------------------------*/


//Global Variables
int SeqModeManagerMEM, SeqMasterMEM,SeqAutoTuneMEM;


bool OutOfTol[2];
bool OK4BulkFeed,OK4IntermFeed,OK4DribbleFeed,FirstWeighment=ON;
bool I_StartMem,I_StopMem,DischReq,I_ResetOutofTolAlarmMem,BagAtKickerMem,KickerRetractedOffMem,
     I_ClearFaultsMem,I_TglEmptyHopper,I_HopperEmptyMem,I_ManDischMem,BulkFeedMem,DribbleFeedMem;
int I;
bool WeighingDataRefreshFlag;
bool KnockHammerFlag,KnockHammerOut,KnockHammerFlipped,FeedCycleCancelled;
bool VibrationMem;


/*------------------------------------------------------------------------- 
--  Procedure Name    : OutReset();
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : This function is called to Refresh The Databases
--                     used in Background Task
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void OutReset(void)
{
int i,tata,DoNoReset;

for(i=IO_OUT_MIN;i<=MaxArrayIODbase;i++) 
  {
    if(i==O_Fault||i==O_WPNumbOUT1||i==O_WPNumbOUT2||i==O_WPNumbOUT3||i==O_WPNumbOUT4||i==O_WPNumb_PWM)
     DoNoReset = ON;
    else
     Output_OFF(i);
     
      
    IO_Force[i] = OFF;
    IO_TestState[i] = OFF;

  }
 StopAnalogOut();
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : CheckCompleted
--  Created by        : Steve Santerre 
--  Last modified on  : 2017/02
--  
--  Purpose           : 
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CheckCompleted(void)
{
 decimal TempWeight %8.4;
 bool retval;
 int tare_return;
 
    
    
      ScaleStatus = getweight(ScaleInUse);
      if(ScaleStatus!=0) 
      IsSettled      = issettled;
      NetWeight      = net;
      TareWeight     = tare;
      NetWeightHiRes = nethires;
      MaxWeight      = capacity;
      Div            = division;
      TareMode       = taremode; 
       
    if(!Simul && CheckAll)
    {
     check_acknowledge_weight (CD_HANDLE_BG, CD_SCALE_NO);
     CheckedWeight = NetWeight;                              // only for the display
    }
    else
    {
     msSim = systemtimer_ms();
     msSim = msSim % 100;
     if(msSim < 2)
      TempWeight = WP.NominalWeight - (Div*2);
     else if(msSim >= 2 && msSim < 5)
      TempWeight = WP.NominalWeight - (Div);     
     else if(msSim >= 5 && msSim < 95)
      TempWeight = WP.NominalWeight;
     else if(msSim >= 95 && msSim < 98)
      TempWeight = WP.NominalWeight + (Div); 
     else if(msSim >= 98 && msSim <= 99)
      TempWeight = WP.NominalWeight + (Div*2); 
       
     CheckedWeight = TempWeight;
     
     if(ScaleDriver[SCALECFG1] == "iQ Sim")
     {
      retval = iQSimSetWeight(SCALE_CHANNEL, SCALE_NUMBER,(CheckedWeight*UnitIQtoADM));
     }
     
     else
      tare_return = mantare(CheckedWeight); 
    }
     
    if (WeighingResult.WeightValid || Simul)
    {
      Weight_OK    = ON;             
    }
    else
    {
     Weight_OK    = OFF;
    }
    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : WP_IOs
--  Created by        : Steve Santerre 
--  Last modified on  : 2017/02
--  
--  Purpose           : Indicate actual WP to Outputs
--                      & change WP according to inputs
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/

void WP_IOs(void)
{
 bool ChangeWP_PWM_Mem;
 float tempo;
 int WP_PWM,MemRecipePWM; 

 if(SeqModeManager == stp_OFF_MODE)
 { 
  if(IO_Enable[I_ChangeWPIN1])
  {
    if(Input_State(I_ChangeWPIN1)) setbit(0,RecipeFromExternal);
    else                           clrbit(0,RecipeFromExternal);
    
    if(Input_State(I_ChangeWPIN2)) setbit(1,RecipeFromExternal);
    else                           clrbit(1,RecipeFromExternal);
    
    if(Input_State(I_ChangeWPIN3)) setbit(2,RecipeFromExternal);
    else                           clrbit(2,RecipeFromExternal);
    
    if(Input_State(I_ChangeWPIN4)) setbit(3,RecipeFromExternal);
    else                           clrbit(3,RecipeFromExternal);
    
    if(RecipeFromExternal > MC.NumberOfWP)
     RecipeFromExternal = 0;
    
  }
   
  if(IO_Enable[I_ChangeWP_PWM])
   {
    if(Input_State(I_ChangeWP_PWM))
    {
     if(!ChangeWP_PWM_Mem)
     {
      T_EnOn(T_ChangeWP_PWM);
      ChangeWP_PWM_Mem = ON;
     }
    }
    
    else
    {
     if(ChangeWP_PWM_Mem)
     {
      if(T_EN[T_ChangeWP_PWM])
       {
         tempo = T_Acc(T_ChangeWP_PWM);
         T_EnOff(T_ChangeWP_PWM);
         WP_PWM = tempo / WPTimeBase;
         if(WP_PWM >= 1 && WP_PWM <= MC.NumberOfWP)
          RecipeFromExternal = WP_PWM;
       } 
      ChangeWP_PWM_Mem = OFF;
     } 
    }
   }
   
  if(IO_Enable[I_ChangeWPIN1] || (IO_Enable[I_ChangeWP_PWM] && WP_PWM > 0)) 
   {  
   if(RecipeFromExternal != MemRecipe)
    if(SeqModeManager == stp_OFF_MODE && RecipeFromExternal != 0)
     {
      LoadWPFromExternalFlag = Execute;
      if(IO_Enable[I_ChangeWP_PWM])
       WP_PWM = 0;
     }                         
   }
 }
 
  if(IO_Enable[I_ChangeWPIN1] && IO_Enable[I_ChangeWP_PWM])
  {
   SystemErrorCode = "306 WP selection inputs mismatch";  
  }
  
  
  if(IO_Enable[O_WPNumbOUT1])
  {
//if(SeqModeManager == stp_AUTO_MODE)
//{
     if(MemRecipe!=MemRecipeIO)
     {
      if(MemRecipe>0&&MemRecipe<=15)
       {
        if(bit(0,MemRecipe))Output_ON(O_WPNumbOUT1);
        else Output_OFF(O_WPNumbOUT1);
        if(bit(1, MemRecipe)) Output_ON(O_WPNumbOUT2);
        else Output_OFF(O_WPNumbOUT2);
        if(bit(2, MemRecipe)) Output_ON(O_WPNumbOUT3);
        else Output_OFF(O_WPNumbOUT3);
        if(bit(3, MemRecipe)) Output_ON(O_WPNumbOUT4);
        else Output_OFF(O_WPNumbOUT4);
       }
      
      else
       {
       Output_OFF(O_WPNumbOUT1);
       Output_OFF(O_WPNumbOUT2);
       Output_OFF(O_WPNumbOUT3);
       Output_OFF(O_WPNumbOUT4);
       }
     MemRecipeIO = MemRecipe;
     }
//}
   else MemRecipeIO = 0;  
  }

  if(IO_Enable[O_WPNumb_PWM])
  {
    if(MemRecipePWM != MemRecipe)
    {
      T_EnOff(T_OutWP_PWM);
      Output_ON(O_WPNumb_PWM);
      T_PRE[T_OutWP_PWM] = MemRecipe * WPTimeBase;
      T_EnOn(T_OutWP_PWM);
      MemRecipePWM = MemRecipe;
    }
   if(T_Dn(T_OutWP_PWM))
    {
      Output_OFF(O_WPNumb_PWM); 
      T_EnOff(T_OutWP_PWM);
    }
  }    
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Var_Init_Cycle
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/28
--  
--  Purpose           : Variables to be Initialize Each Weighing Cycle
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void VarInitCycle(void)
{
 decimal NominalWeightMem%6.2,TolUnderRejWeightMem%6.2,TolUnderAccWeightMem%6.2,TolOverAccWeightMem%6.2,TolOverRejWeightMem%6.2;
 bool setratingparamresult;
 float TU1,TU2,TO1,TO2,NW;
 
CheckOIML();

T_PRE[T_PCEntryBlocked] = MP.PCEntryTimeout;
T_PRE[T_PCExitBlocked]  = MP.PCExitTimeout;
T_PRE[T_RejectUnitTime]   = WP.RejectUnitTime;
T_PRE[T_RejectUnitDelay] = WP.RejectUnitDelay;
FlexIO_SetTPresetsFlag = Execute;
Reset_FlexIOFlag = Execute;

  if(NominalWeightMem != WP.NominalWeight || TolUnderRejWeightMem != WP.TolUnderRejWeight || TolUnderAccWeightMem!=WP.TolUnderAccWeight
    || TolOverAccWeightMem != WP.TolOverAccWeight || TolOverRejWeightMem != WP.TolOverRejWeight)
   {  
    TolChanged = ON;
    NominalWeightMem      = WP.NominalWeight;
    TolUnderRejWeightMem  = WP.TolUnderRejWeight;
    TolUnderAccWeightMem  = WP.TolUnderAccWeight;
    TolOverAccWeightMem   = WP.TolOverAccWeight;
    TolOverRejWeightMem   = WP.TolOverRejWeight;
   } 
   
 if(TolChanged && !Simul && CheckAll)
  {
   
    NominalWeightBU      = WP.NominalWeight*UnitIQtoADM;
    TolUnderRejWeightBU  = WP.TolUnderRejWeight*UnitIQtoADM;
    TolUnderAccWeightBU  = WP.TolUnderAccWeight*UnitIQtoADM;
    TolOverAccWeightBU   = WP.TolOverAccWeight*UnitIQtoADM;
    TolOverRejWeightBU   = WP.TolOverRejWeight*UnitIQtoADM; 
      
   setratingparamresult = check_set_rating_parameters (CD_HANDLE_BG,CD_SCALE_NO,0,0,"",
                          NominalWeightBU,TolUnderRejWeightBU,TolUnderAccWeightBU,
                          TolOverAccWeightBU,TolOverRejWeightBU);
   
    TolChanged = OFF;
  }
                                  
RefreshGrayoutFlag = ON;

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Var_Init_OFF_Mode
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/28
--  
--  Purpose           : Variables to be Initialize In Off Mode
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void VarInitOff(void)
{
  int i,j;

ProdCycleUnitsPerMin = 0;

OutReset();
if(Fault_Type[FLT_GEN] == 0) FaultResetReq();
  
for(I=1;I<TMAX;I++) 
 T_EnOff(I);


if(SeqModeManager == stp_OFF_MODE)
{
SeqMaster=stp_INIT;
}

T_PRE[T_CycleDuration]=999.99;

T_PRE[T_UPMDuration]= 6000.0;
T_PRE[T_FaultDisplay] = 3.0;

if(!PCExitBlocked)
 {
  RejectUnit = OFF;
  T_EnOff(T_RejectUnitDelay);
  T_EnOff(T_RejectUnitTime);
 } 

 WPLimitCheck();
 
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : PhotocellsCheck
--  Created by        : Steve Santerre
--  Last modified on  : 2019/11
--  
--  Purpose           : Check Status of Sensor according to Detecting mode
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void PhotocellsCheck(void) 
{
 if(!Simul)
 { 
  
  switch(GenCheckParam.MeasurementStartMode)
  {
   case CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_OPEN:
   #ifdef WL_MODES_OK
   case CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_OPEN_WL:
   #endif
     PCEntryBlocked = Input_State(I_PCEntry);
     break;
     
   case CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_CLOSED:
   #ifdef WL_MODES_OK
   case CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_CLOSED_WL:
   #endif
     PCEntryBlocked = !Input_State(I_PCEntry);
     break;  
     
   default: SystemErrorCode = "707 Invalid Start Mode selected in SM";
    break;
  }  
  
  switch(GenCheckParam.MeasurementStopMode)
  {
   case CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_OPEN:
   #ifdef WL_MODES_OK
   case CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_OPEN_WL:
   #endif
     PCExitBlocked = Input_State(I_PCExit);
     break;
     
   case CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_CLOSED:
   #ifdef WL_MODES_OK
   case CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_CLOSED_WL:
   #endif
     PCExitBlocked = !Input_State(I_PCExit);
     break;  
     
   default: SystemErrorCode = "708 Invalid Stop Mode selected in SM";
    break;
  } 
 }
 
 else
 { 
   PCEntryBlocked = OFF;
   PCExitBlocked = OFF;
 }
    
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Fault Monitor
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/28
--  
--  Purpose           : Variables to Set Low Level
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void FaultMonitor(void)
{
 
 if(T_Dn(T_FirstScan))
  {
   //E-Stop Fault
   
   if (IO_Enable[I_EStop] && !Input_State(I_EStop) && !FaultState(FltG_EmergencyStop)) 
       FaultHandler(FltG_EmergencyStop,"");
       
   //Both Photocells monitoring
   if(SeqModeManager == stp_PREP_MODE)
   {
    if(PCEntryBlocked && PCExitBlocked)
    {
     if(!FaultState(FltB_BothPCsBlocked))
       FaultHandler(FltB_BothPCsBlocked,"");
    }
   }        
   
   //Entry Photocells monitoring
   if(MP.PCEntryTimeout > 0 && IO_State[O_StartCnv] && SeqMaster != stp_INIT)
    {
     if(PCEntryBlocked)
     {
      if(!T_EN[T_PCEntryBlocked])
       T_EnOn(T_PCEntryBlocked);
      if(T_Dn(T_PCEntryBlocked) && !FaultState(FltB_EntryPCBlocked))
      {
       FaultHandler(FltB_EntryPCBlocked,"");
      }
     }
     else  
      T_EnOff(T_PCEntryBlocked);
    }  
    else  
     T_EnOff(T_PCEntryBlocked);
    
    //Exit Photocells monitoring
    if(MP.PCExitTimeout > 0 && IO_State[O_StartCnv] && SeqMaster != stp_INIT)
    {
     if(PCExitBlocked)
     {
      if(!T_EN[T_PCExitBlocked])
       T_EnOn(T_PCExitBlocked);
      if(T_Dn(T_PCExitBlocked) && !FaultState(FltB_ExitPCBlocked))
      {
       FaultHandler(FltB_ExitPCBlocked,"");
      }
     }
     else  
      T_EnOff(T_PCExitBlocked);
    }  
    else  
     T_EnOff(T_PCExitBlocked);
     
  //Exceeded Capacity Fault 
  if(!Simul && CheckAll)
  {  
    if(SeqModeManager==stp_OFF_MODE)
    {
     if ((NetWeight > MaxWeight) && !FaultState(FltB_ExceededCapacity))
        {
         FaultHandler(FltB_ExceededCapacity,"");
        }
    }    
    else
    {
      if ((NetWeight > MaxWeight) && !FaultState(FltG_ExceededCapacity))
        {
         FaultHandler(FltG_ExceededCapacity,"");
        }
    }
  }  
    
    //Motor Failure Fault   
    if (IO_Enable[I_MotorFailure] && !Input_State(I_MotorFailure) && !FaultState(FltG_MotorFailure))
         FaultHandler(FltG_MotorFailure,"");
   
      
   
  
  //Clear Fault Input
  if(IO_Enable[I_ClearFaults] && Input_State(I_ClearFaults) && !I_ClearFaultsMem)
    {
    I_ClearFaultsMem = ON;
    if(Fault_Type[FLT_GEN]||Fault_Type[FLT_BLK]||Fault_Type[FLT_STOP]||Fault_Type[FLT_WRN])FaultResetReq();
    }
    
  if(IO_Enable[I_ClearFaults] && !Input_State(I_ClearFaults) && I_ClearFaultsMem) I_ClearFaultsMem =OFF;                    
 
  
  if(Fault_Type[FLT_GEN] && OutResetFlag != Execute) 
   OutResetFlag = Execute;
  
  }         
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : WeighingDataRefresh
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Production Report Values Refresh
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void WeighingDataRefresh(void)
{
 double ValueToSqrt;
 bool ValueNegFlag;
 string weighingdata_weight[12];
 decimal limit%6.2;
 
 if(Weight_OK && SqareSumWeight<2000000000)
 {
  NbrChecked++; 
  SumWeight = SumWeight + CheckedWeight;
  AvgWeight = SumWeight/NbrChecked;
  SqareSumWeight = SqareSumWeight + (CheckedWeight*CheckedWeight);
  
  //Excel StdevP Formula (entire population)
  ValueToSqrt = (SqareSumWeight - (NbrChecked*(AvgWeight*AvgWeight)))/NbrChecked;
  StdDev = sqrt(ValueToSqrt);
 }
    
    if((NbrChecked > 2 && (AvgWeight < (WP.NominalWeight*0.75)) || (AvgWeight > (WP.NominalWeight*1.25)))
      || NbrChecked < 0)
      {
       ResetData(ON);
      }    

       ResetZones();
       Output_ON(O_UnitChecked);
       UnitChecked = ON;
       T_EnOn(T_UnitChecked);  
       if(WeighingResult.WeightValid)
        {
           if(Simul || !UnitIsBasic)
           { 
             if (CheckedWeight <= WP.TolUnderRejWeight)
                TolType = TolURej;
             else if (CheckedWeight <= WP.TolUnderAccWeight)
                TolType = TolUAcc;
             else if (CheckedWeight < WP.TolOverAccWeight)
                TolType = TolGood;
             else if (CheckedWeight < WP.TolOverRejWeight)
                TolType = TolOAcc;
             else
                TolType = TolORej;
           }
          
          else
          {      
            if(WeighingResult.Zone == zOK)
              TolType = TolGood;
            else if(WeighingResult.Zone == zTU2)
              TolType = TolURej;
            else if(WeighingResult.Zone == zTU1)
              TolType = TolUAcc;
            else if(WeighingResult.Zone == zTO1)
              TolType = TolOAcc;
            else if(WeighingResult.Zone == zTO2)
              TolType = TolORej;
          }
        }
       else
        TolType = TolInvalid;
    
        WP.TolTotalCnt++;
        WP.TolTotalPct = WP.TolTotalCnt/WP.TolTotalCnt*100.0; 
        
        if(Batch.Preset > 0)
          {
           Batch.TolTotalCnt++;
           Batch.TolTotalPct = Batch.TolTotalCnt/Batch.TolTotalCnt*100.0;
           ProdTotalUnitsCnt = Batch.TolTotalCnt;
          }
         else
          {
           ProdTotalUnitsCnt = WP.TolTotalCnt; 
          }
                    
      switch(TolType)
      {  
        case TolURej:
         if(WP.RejectCfg == RejectBoth || WP.RejectCfg == RejectUnderOnly)
           RejectUnit = ON;
         Output_ON(O_TolUnderReject);
         ProdLastTolerance = "-R";
         if(Batch.Preset > 0)
          {
           Batch.TolUnderRejCnt++;
          }
         WP.TolUnderRejCnt++;
         limit = WP.TolUnderRejWeight;  
         break;
         
        case TolUAcc:
         Output_ON(O_TolUnderAccept);
         ProdLastTolerance = "-A";
         if(Batch.Preset > 0)
          {
           Batch.TolUnderAccCnt++;
          }
         WP.TolUnderAccCnt++; 
         limit = WP.TolUnderAccWeight;
         break;
         
        case TolGood:
         Output_ON(O_TolGood);
         ProdLastTolerance = "==";
         if(Batch.Preset > 0)
          {
           Batch.TolGoodCnt++;
          }
         WP.TolGoodCnt++;
         limit = WP.NominalWeight;
         break;
         
        case TolOAcc:
         Output_ON(O_TolOverAccept);
         ProdLastTolerance = "+A";
         if(Batch.Preset > 0)
          {
           Batch.TolOverAccCnt++;
          }
         WP.TolOverAccCnt++;
         limit = WP.TolOverAccWeight;
         break;
         
        case TolORej:
         if(WP.RejectCfg == RejectBoth || WP.RejectCfg == RejectOverOnly)
          RejectUnit = ON;
         Output_ON(O_TolOverReject);
         ProdLastTolerance = "+R";
         if(Batch.Preset > 0)
          {
           Batch.TolOverRejCnt++;
          }
         WP.TolOverRejCnt++;
         limit = WP.TolOverRejWeight;
         break;
         
        case TolInvalid:
         RejectUnit = ON;
         InvalidWeightZones();
         ProdLastTolerance = "!!";
         if(Batch.Preset > 0)
          {
           Batch.TolInvalidCnt++;
          }
         WP.TolInvalidCnt++;
         limit = 0.00; 
         break;
      }      
       
       if(Batch.Preset > 0)
       {
        Batch.TolUnderRejPct = Batch.TolUnderRejCnt/Batch.TolTotalCnt*100.0;
        Batch.TolUnderAccPct = Batch.TolUnderAccCnt/Batch.TolTotalCnt*100.0;
        Batch.TolGoodPct     = Batch.TolGoodCnt/Batch.TolTotalCnt*100.0;
        Batch.TolOverAccPct = Batch.TolOverAccCnt/Batch.TolTotalCnt*100.0;
        Batch.TolOverRejPct = Batch.TolOverRejCnt/Batch.TolTotalCnt*100.0;
        Batch.TolInvalidPct = Batch.TolInvalidCnt/Batch.TolTotalCnt*100.0;
       }
       
        WP.TolUnderRejPct = WP.TolUnderRejCnt/WP.TolTotalCnt*100.0;
        WP.TolUnderAccPct = WP.TolUnderAccCnt/WP.TolTotalCnt*100.0;
        WP.TolGoodPct     = WP.TolGoodCnt/WP.TolTotalCnt*100.0; 
        WP.TolOverAccPct  = WP.TolOverAccCnt/WP.TolTotalCnt*100.0; 
        WP.TolOverRejPct  = WP.TolOverRejCnt/WP.TolTotalCnt*100.0;
        WP.TolInvalidPct  = WP.TolInvalidCnt/WP.TolTotalCnt*100.0;
              
       ProdLastChecked = CheckedWeight;
           
       ProdStdDev = StdDev;
       if(Batch.Preset > 0)Batch.StdDev = StdDev;

       ProdAvgWeight = AvgWeight;
       if(Batch.Preset > 0)Batch.Avg = AvgWeight;
              
       ProdTotalUnitsLT++;
       WP.TotalWeight = WP.TotalWeight + CheckedWeight;
       if(Batch.Preset > 0)Batch_TotalWeight = Batch_TotalWeight + CheckedWeight;
        
       ProdTotalWeightLTkg = ProdTotalWeightLTkg + (CheckedWeight*WP_UnitToKG);
       ProdTotalWeightLT = ProdTotalWeightLTkg / WP_UnitToKG;
       
       weighingdata_weight = concat(adj(CheckedWeight,6,dp),WP.Unit);
         
       WeighingData_StringSource = concat(weighingdata_weight,space(tab),concat(ProdLastTolerance,space(2-length(ProdLastTolerance))),space(tab),
                                              concat(adj(limit,6,dp),WP.Unit),space(tab),concat(adj(EvaluationDuration,4,2),"sec"),space(tab),TimeString);
      RefreshWeighingDataPopup(ON);
                                        
       
       
       //Formating Unit Record String (Ticket Info)
       FileName_Date = getstddate();
       Standard_Date = concat("20",FileName_Date);
       
       Standard_Time = getstdtime();
       TicketInfo = concat("<;", MC.SerialNbr, ";",trim(string(adj(WP.NominalWeight,7,2))), ";",WP.Unit, ";",
                           trim(string(adj(WP.TareWeight,4,2))), ";",trim(string(adj(CheckedWeight,7,2))), ";",                           
                           trim(ProdLastTolerance), ";", trim(string(adj(limit,7,2))), ";",
                           trim(trim(string(adj(ProdTotalUnitsCnt,10,0)))), ";",                                 
                           Standard_Time,";",Standard_Date,";>", CRLF);
       
       fifo_write (FIFO_UNITREC_SHARED, TicketInfo, length (TicketInfo));
       fifo_write (FIFO_UNITREC_USB,    TicketInfo, length (TicketInfo));  
        
       RefreshReportScreenReq();
       RefreshAutoScreenReq();
       if(Batch.Preset > 0)
        {
         SaveBatchFlag = Execute;
         RefreshBatchScreenReq();
        } 
       
       PreSave_DataNoResetFlag = Execute;
       ProdDataReady = ON;
       ProdDataReadyPLC = ON;
       
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : IN_Refresh
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Refresh group of physical Digital Inputs and 
--                      sets the IO_State 
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void IN_Refresh(void)
{
int i,InputRegTest1,InputRegTest2;

if(MaxNumbOfIO > 31)
{
InputRegTest1 = pin(31,0); 
InputRegTest2 = pin(MaxNumbOfIO,32);
}
else 
{
if(MaxNumbOfIO > 0 && MaxNumbOfIO <= 31)InputRegTest1 = pin(MaxNumbOfIO,0);
InputRegTest2 = 0;
}
for(i=IO_IN_MIN;i<=IO_IN_MAX;i++)
{
    if(IO_Input[i]) //Inputs
    { 
        if (!IO_Enable[i]) IO_TestState[i] = OFF;
        else if(IO_Address[i] <=31) IO_TestState[i] = bit(IO_Address[i],InputRegTest1);
        else IO_TestState[i] = bit(IO_Address[i],InputRegTest2);
    }

}
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : IN_Refresh
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Refresh group of physical Digital Inputs
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void IN_Refresh2(void)
{

if(MaxNumbOfIO > 31)
{
  InputReg1 = pin(31,0); 
  InputReg2 = pin(MaxNumbOfIO,32);
}
else 
{
  if(MaxNumbOfIO > 0 && MaxNumbOfIO <= 31)InputReg1 = pin(MaxNumbOfIO,0);
  InputReg2 = 0;
}

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Force_Out
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Outputs set to OFF when accessing IO Test Output page
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      :  
--                      
--------------------------------------------------------------------------*/
void Force_Out (void)
{
int i;
 for(i=IO_OUT_MIN;i<=MaxArrayIODbase;i++)
 {
  if(IO_Enable[i] && IO_Address[i] <= MaxNumbOfIO)
   {
   if (IO_Force[i])  bout((IO_Address[(i)]),1);      
   if (!IO_Force[i]) bout((IO_Address[(i)]),0);  
   IO_TestState[i]=out((IO_Address[(i)]));
   }
 }  
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : OUT_Refresh
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Refresh physical Digital Outputs
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Feeder Outputs will also be refreshed with 
--                      Feeding Instructions - RTCWin
--------------------------------------------------------------------------*/
void OUT_Refresh(void)
{
bool Bit31;
int i,OutputRegTest1,OutputRegTest2;
//int TempOutputs,TempOutputs2;

OutputRegTest1 = 0;
OutputRegTest2 = 0;

for(i=IO_OUT_MIN;i<=IO_OUT_MAX;i++)
{
   
    if(!IO_Input[i]) //Outputs
    { 
        
        if (!IO_Enable[i]) IO_TestState[i] = OFF;
        else
        { 
         if (IO_Address[i]<=31)
         {
          if(IO_TestState[i])
          {
           setbit(IO_Address[i],OutputRegTest1);
          }
          else clrbit(IO_Address[i],OutputRegTest1);
         }
         else
         {
           if(IO_TestState[i])
           {
            setbit(IO_Address[i],OutputRegTest2);
           }
           else clrbit(IO_Address[i],OutputRegTest2);
         }
        }
        
    }
}
    if(MaxNumbOfIO > 31) 
    {
       pout(OutputRegTest1,31,0);
       pout(OutputRegTest2,MaxNumbOfIO,32);
       Bit31 = bit(31,OutputRegTest1);
       bout(31,Bit31);
       if(MaxNumbOfIO == 63)
       {
        Bit31 = bit(31,OutputRegTest2);
        bout(63,Bit31);
       }
    }
    if(MaxNumbOfIO > 0 && MaxNumbOfIO <= 31) pout(OutputRegTest1,MaxNumbOfIO,0);
    
     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : OUT_Refresh
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Refresh physical Digital Outputs
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Feeder Outputs will also be refreshed with 
--                      Feeding Instructions - RTCWin
--------------------------------------------------------------------------*/
void OUT_Refresh2(void)
{
bool Bit31;
//int TempOutputs,TempOutputs2;

//OutputReg1 = 0;
//OutputReg2 = 0;

    if(MaxNumbOfIO > 31) 
    {
       pout(OutputReg1,31,0);
       pout(OutputReg2,MaxNumbOfIO,32);
       Bit31 = bit(31,OutputReg1);
       bout(31,Bit31);
       if(MaxNumbOfIO == 63)
       {
        Bit31 = bit(31,OutputReg2);
        bout(63,Bit31);
       }
    }
    if(MaxNumbOfIO > 0 && MaxNumbOfIO <= 31) pout(OutputReg1,MaxNumbOfIO,0);
    
     
}



bool VerifyStart(void)
{
   if((StartHMI || (IO_Enable[I_Start] && Input_State(I_Start) && !I_StartMem)) && T_Dn(T_FirstScan))
    {
      if(Current_Screen != SCREEN_AUTOMATIC) Force_Screen_Req(SCREEN_AUTOMATIC, LARGE);
      I_StartMem = ON;
      StartHMI=OFF;
      
      
      if(Check_Scale_Cfg())
        {
         SeqModeManager = stp_PREP_MODE;
         if(BatchEnded || (Batch.Preset > 0 && Batch.Count >= Batch.Preset))
           {
             Batch.Count = 0;
             BatchEnded = OFF;
             RefreshAutoScreenReq();
           }
        }
    return(ON);
    }
  else
    return(OFF);
}      


/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_ModeManager
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : Mode Manager Sequence
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/

void SEQ_ModeManager (void)
{
int i;
bool SampledInPauseMem,retval;

if(IO_Enable[I_Start] && !Input_State(I_Start)) 
  I_StartMem = OFF;
if(IO_Enable[I_Stop] && !Input_State(I_Stop)) 
  I_StopMem = OFF;

if(Fault_Type[FLT_GEN]!=0 || OffHMI) 
  {SeqModeManager = stp_OFF_MODE;OffHMI=OFF;}
if((Fault_Type[FLT_GEN]!=0 ||(SeqModeManager!= stp_OFF_MODE )) && StartHMI) 
  StartHMI=OFF;
if((SeqModeManager!= stp_AUTO_MODE) && StopHMI) 
  StopHMI=OFF;

if(TestOffset)
 {
  EPWriteOffset(CD_HANDLE_BG,RecipeMem);
  TestOffset = OFF;
 }
  
if(PauseHMI)
 {
  AutoPause = !AutoPause;
  PauseHMI = OFF;
  CurMode_Set();
 }
if(SampledInPauseMem != SampledInPause)
 {
  
  SampledInPauseMem = SampledInPause;
 }   
    
    switch (SeqModeManager)
    {
      case stp_OFF_MODE:
            if(SeqModeManagerMEM!=SeqModeManager)
              {
               SeqModeManagerMEM = SeqModeManager;
               AutoMode = OFF;
               Start_PauseBtn = StartBtn;
               AutoPause = OFF;
               SampledInPause = OFF;
               KeyLockPTSZI(LAST,LAST,LAST,OFF,LAST);
               VarInitOffFlag = Execute;
               clrtare (CD_SCALE_NO);
               if(!Simul && CheckAll) 
                EnableDynamicMode(OFF,CD_HANDLE_BG);
               VarInitCycle();
               ChangeSMStateFlag = Execute;
               
               if(ScaleDriver[SCALECFG1] == "iQ Sim")
                {
                 retval = iQSimSetWeight(SCALE_CHANNEL, SCALE_NUMBER,0.0);
                } 
              }
              
         if(VarInitOffFlag != Execute) 
          if(Fault_Type[FLT_GEN]==0)
          {    
            if(StepMsg!=lsub(TX_MSGWAITINGFORSTART) && T_Dn(T_FirstScan)) MessageDisplay(lsub(TX_MSGWAITINGFORSTART),Step_Message);
            if(VerifyStart()) 
             {
              VarInitOffFlag = Execute;
              break;
             }   
        
          }                   
         break;
               
      case stp_STOPPING_MODE:
            if(SeqModeManagerMEM != SeqModeManager)
              {
              SeqModeManagerMEM = SeqModeManager;
              AutoMode = OFF;
              }
            if(SeqMaster==stp_INIT)
              SeqModeManager = stp_OFF_MODE;  
            break;
      
      case stp_STOP_MODE:
            if(SeqModeManagerMEM != SeqModeManager)
              {
              SeqModeManagerMEM = SeqModeManager;
              //AutoMode = OFF;
              ZeroOK = OFF;
              DynamicInitDone = OFF;
              }
            if(Fault_Type[FLT_STOP]==0)
            { 
             check_reset_transport_error(CD_HANDLE_BG,CD_SCALE_NO);
             SeqModeManager = stp_AUTO_MODE;
            }  
            break;      
                            
      case stp_PREP_MODE:
        if(SeqModeManagerMEM != SeqModeManager)
           {
            SeqModeManagerMEM = SeqModeManager;
            ChangeSMStateFlag = Execute;
            CheckOutput = Execute;
            VarInitCycle();
           }
         if(Fault_Type[FLT_STOP]==0)
            
            if(VarInitOffFlag != Execute)
             {
              if(CheckOutputConfig())
               if(!PCEntryBlocked || !PCExitBlocked)
                {
                 SeqModeManager = stp_AUTO_MODE;
                }
             }
        break;
             
      case stp_AUTO_MODE:
      if(SeqModeManagerMEM!=SeqModeManager)
          {
           SeqModeManagerMEM = SeqModeManager;
           AutoMode = ON;
           if(!CheckAll)
            AutoTune = OFF;
           Start_PauseBtn = PauseBtn;
           KeyLockPTSZI(LAST,LAST,LAST,ON,LAST);
           if(!Simul && CheckAll)
           {
            classificationcheck = check_classification_enabled(CD_HANDLE_BG,CD_SCALE_NO,ClassificationStatus); 
            if(ClassificationStatus!="1")
             StatusEnableClassification = check_enable_classification (CD_HANDLE_BG, CD_SCALE_NO, ON);
            EvalParamSelected = SelectEvalParam(RecipeMem);
            EPWriteOffset(CD_HANDLE_BG,RecipeMem);
            EnableDynamicMode(ON,CD_HANDLE_BG);
           } 
           TolChanged = ON;
           VarInitCycle();
           if(CheckAll)
           { 
            if(!EvalParamSelected && !Simul)
             { 
              SystemErrorCode = concat("704 Eval. Parameters #",trim(string(RecipeMem))," could not be selected");
             }
            else
             {
              if (WP.TareWeight > 0)
              {
               mantare (ScaleInUse,WP.TareWeight);
              }   
              else
              {
               clrtare (CD_SCALE_NO);
              }
             }
            CheckSystem(OFF);  
           } 
          } 
          
      if(Fault_Type[FLT_STOP]!=0) 
       SeqModeManager = stp_STOP_MODE;
      if(StopHMI || (IO_Enable[I_Stop] && Input_State(I_Stop) && !I_StopMem))
         {  
          SeqModeManager = stp_STOPPING_MODE;
          I_StopMem = ON;
          StopHMI=OFF;
         }
      break;
    }


if(SeqModeManager!= mode_step || Current_Screen!=Current_ScreenMEM)
          {
          RefreshGrayoutFlag = ON;
          if(SeqModeManager == stp_OFF_MODE)
           {
            if (SeqModeManager!= mode_step)BTDelay = CheckingTaskIntervalOff;
            if(Current_Screen != Current_ScreenMEM)
             {
             if(Current_Screen == SCREEN_AUTOMATIC) 
               OutResetFlag = Execute;
             }
           }
          else 
           {
           if (SeqModeManager!= mode_step)BTDelay = CheckingTaskIntervalAuto;
           }   
          if (SeqModeManager!= mode_step) 
          	{
          		mode_step = SeqModeManager; 
          		Clear_ButtonControlRefreshedFlag = ON;
          	}
          Current_ScreenMEM = Current_Screen;
          CurMode_Set();
          }
if( mode_step_MEM != mode_step) CurMode_Set();          
              
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : OutputFunction
--  Created by        : Steve Santerre
--  Last modified on  : 2019/12
--  
--  Purpose           : Function to manage Outputs
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void OutputFunction(void)
{
  bool RejectON;
  
  //Unit Checked Output switching OFF
  if(T_EN[T_UnitChecked])
   {
    if(T_Dn(T_UnitChecked))
    {
      T_EnOff(T_UnitChecked);
      Output_OFF(O_UnitChecked);
      UnitChecked = OFF;
    }
   }   
  
  //Unit Reject Output switching ON
  if(RejectUnit)
  {
   if(!T_EN[T_RejectUnitDelay] && !RejectON && IO_State[O_StartCnv])
    {
      if(WP.RejectUnitDelay >0)
       T_EnOn(T_RejectUnitDelay);
      else
       RejectON = ON; 
    }
   else
    if(T_Dn(T_RejectUnitDelay) || RejectON)
    {   
       Output_ON(O_RejectUnit);
       T_EnOn(T_RejectUnitTime);
       if(!RejectON) RejectON = ON;
       RejectUnit = OFF;
       T_EnOff(T_RejectUnitDelay);
    }
  }    
  
  //Unit Reject Output switching OFF    
   if(RejectON && !RejectUnit)
   {
    if(T_Dn(T_RejectUnitTime) || WP.RejectUnitTime <= 0)
    {
      T_EnOff(T_RejectUnitTime);
      Output_OFF(O_RejectUnit);
      RejectON = OFF;
    }
   } 

}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_Master
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : Weigher Master Sequence
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/

void SEQ_Master (void)
{
bool MsgDownStreamSent,MsgWaitPauseSent,MsgWaitUnitExit,CheckDoneMem,MsgZeroing,MsgWaitDownStream;
bool retval,RestartOnExitBag;
int MsgAtExit; //0=no msg, 1=Exit, 2=Wait dowstream
float TSimOffset;

if(SeqModeManager == stp_OFF_MODE) SeqMaster = stp_INIT;
if(!CheckDone) CheckDoneMem = OFF;

if(!Simul)
 DownStreamRdy = Input_State(I_DownstreamReady);
else
 DownStreamRdy = ON;
  
OutputFunction();

   if(AutoTune && SeqAutoTune == stp_AT_CHECKRECORD)
   {
    if(ATCheckRecordMsg == "")
     ATCheckRecordMsg = concat(lsub(TX_ATCHECKRECORD),space(1),adj(AT.CheckRecordPct,3,0),"%");
   }  
  
switch (SeqMaster)
 {
  case stp_INIT:
            if(SeqMasterMEM != SeqMaster)
                {
                SeqMasterMEM = SeqMaster;
                if(SeqModeManager != stp_OFF_MODE && !BatchEnded) MessageDisplay(lsub(TX_MSGBLANK),Step_Message);
                VarInitCycle();
                RefreshAutoScreenReq();
                T_EnOff(T_EvalTime);
                RestartOnExitBag = OFF;
                }
        
        if(!BatchEnded)
        {  
          if(!Simul && CheckAll)
           classificationcheck = check_classification_enabled(CD_HANDLE_BG,CD_SCALE_NO,ClassificationStatus); 
          
                 
          if(SeqModeManager==stp_AUTO_MODE && (DynamicInitDone || Simul || !CheckAll)) 
          {
            if(Simul)
            {
             T_EnOff(T_Simul);
            }  
            if(!AutoTune || (SeqAutoTune == stp_AT_CHECKRECORD && CheckRecordStarted))
             {
              SeqMaster = stp_STANDBY;
             }
            else if(!AutoTuneActive) 
             {
               AutoTuneActive = ON;
             }  
          }
        } 
         
          break;
            
  case stp_STANDBY:
            if(SeqMasterMEM != SeqMaster) 
             {
              SeqMasterMEM = SeqMaster;
              MsgWaitUnitExit = OFF;
              MsgZeroing = OFF;
              MsgWaitDownStream = OFF;
              T_EnOff(T_RdyToRcv);
              T_PRE[T_RdyToRcv] = SAFETY_DISTANCE / (Lim(BeltSpeedMin,BeltSpeedMax,BeltSpeedMetric) * 1000.0);
              if(CheckAll)
                 {
                  if(!AutoTune)
                   MessageDisplay(lsub(TX_MSGWAITDOWNSTREAM),Step_Message); 
                  else
                   MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGWAITDOWNSTREAM)),Step_Message);
                 }   
              else
               MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGWAITDOWNSTREAM)),Step_Message); 
             }     
            
            if(DownStreamRdy || !PCExitBlocked)
            {
             MsgWaitDownStream = OFF;
             if(!IO_State[O_StartCnv])
              { 
               Output_ON(O_StartCnv);
               T_EnOn(T_RdyToRcv);
              }
             
             if((!PCExitBlocked || T_Dn(T_RdyToRcv))  && !ZeroRequired)
             {
              SeqMaster = stp_RUN;
             }
             else
             {
              if(PCExitBlocked)
              {
               if(!MsgWaitUnitExit)
               {
                if(CheckAll)
                 {
                  if(!AutoTune)
                   MessageDisplay(lsub(TX_MSGWAITINGUNITEXIT),Step_Message); 
                  else
                   MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGWAITINGUNITEXIT)),Step_Message);
                 }   
                else
                 MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGWAITINGUNITEXIT)),Step_Message);
                MsgWaitUnitExit = ON;
               }
              }
               
              else if(ZeroRequired)
              {
                if(!MsgZeroing)
                {
                 MessageDisplay(lsub(TX_MSGZEROING),Step_Message);
                 MsgZeroing = ON;
                }
              }    
              break;
             } 
            }
            else
            {
             if(IO_State[O_StartCnv])
              { 
               Output_OFF(O_StartCnv);
              }
             if(!MsgWaitDownStream)
              {
               if(CheckAll)
                 {
                  if(!AutoTune)
                   MessageDisplay(lsub(TX_MSGWAITDOWNSTREAM),Step_Message); 
                  else
                   MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGWAITDOWNSTREAM)),Step_Message);
                 }   
               else
                MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGWAITDOWNSTREAM)),Step_Message);
               MsgWaitDownStream = ON;
              }  
             break; 
            }  
             
  case stp_RUN:
            if(SeqMasterMEM != SeqMaster) 
            {
            SeqMasterMEM = SeqMaster;
            if(Simul && !T_EN[T_Simul]) 
             T_EnOn(T_Simul);
             if(CheckAll)
             {
              if(!AutoTune)
               MessageDisplay(lsub(TX_MSGWAITINGNEWUNIT),Step_Message);
              else
               MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGWAITINGNEWUNIT)),Step_Message);
             }  
             else
              MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGWAITINGNEWUNIT)),Step_Message);
             if(!IO_State[O_StartCnv])
              { 
               Output_ON(O_StartCnv);
              }
             if(!IO_State[O_RdyToRcv])
              { 
               Output_ON(O_RdyToRcv);
              }  
            } 
            
            if(PCEntryBlocked || (Simul && T_Acc(T_Simul) > (T_PRE[T_Simul]*0.15)))
            {
             SeqMaster = stp_UNITENTRY;
            }
            
            else if(!AutoMode)
            { 
             SeqMaster = stp_INIT;
             break;
            } 
            else
             break;
            
  case stp_UNITENTRY:
            if(SeqMasterMEM != SeqMaster) 
             {
              SeqMasterMEM = SeqMaster;
              if(CheckAll)
                 {
                  if(!AutoTune)
                   MessageDisplay(lsub(TX_MSGUNITENTRY),Step_Message); 
                  else
                   MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGUNITENTRY)),Step_Message);
                 }   
              else
               MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGUNITENTRY)),Step_Message);
              if(WeighingResultInError)
               FaultResetReq();
              CheckDone = OFF; 
              VarInitCycle();
             }       
           
            if((!PCEntryBlocked && !Simul) || (Simul && T_Acc(T_Simul) > (T_PRE[T_Simul]*0.50)))
            {
             if(Simul)
             {
              if(ScaleDriver[SCALECFG1] == "iQ Sim")
              {
               retval = iQSimSetWeight(SCALE_CHANNEL, SCALE_NUMBER,iQSimDashes);
              }
              else
               clrtare (CD_SCALE_NO);
             }   
             SeqMaster = stp_EVALUATION;
            } 
            else
             break;
  
  
  case stp_EVALUATION:
            if(SeqMasterMEM != SeqMaster)
            {
            SeqMasterMEM = SeqMaster;
            if(CheckAll)
                 {
                  if(!AutoTune)
                   MessageDisplay(lsub(TX_MSGUNITEVAL),Step_Message); 
                  else
                   MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGUNITEVAL)),Step_Message);
                 }   
            else
             MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGUNITEVAL)),Step_Message);
            T_EnOn(T_EvalTime);
            Output_OFF(O_RdyToRcv);
            }
                                        
            if(PCExitBlocked || (CheckDone && CheckAll) || (Simul && T_Acc(T_Simul) > (T_PRE[T_Simul]*0.70)))
            {
             SeqMaster = stp_WAITRESULT;
            } 
            else
             break;
            
  case stp_WAITRESULT:
            if(SeqMasterMEM != SeqMaster)
            {
             SeqMasterMEM = SeqMaster;
             MsgWaitPauseSent = OFF;
             EvaluationDuration = T_Acc(T_EvalTime);
             T_EnOff(T_EvalTime);
            }
            
            SampledInPause = AutoPause;
            
            if(!DownStreamRdy || SampledInPause)
            {
             if(IO_State[O_StartCnv] && PCExitBlocked)
              { 
               Output_OFF(O_StartCnv);
              }
             if(IO_State[O_RdyToRcv])
              { 
               Output_OFF(O_RdyToRcv);
              } 
            }
              
          if(((CheckDone || !CheckAll ||(ZeroRequired && !CheckDone && PCExitBlocked)) && !Simul) || (Simul && T_Dn(T_Simul)))
          {
             if(!CheckDoneMem)
             {
              //Units Per Minute Calculation
              if(T_EN[T_UPMDuration])
               {
                ProdCycleUnitsPerMin = 60/T_Acc(T_UPMDuration);
                T_EnOff(T_UPMDuration);
               }
              if(!T_EN[T_UPMDuration])
               T_EnOn(T_UPMDuration);
              
              if(CheckAll)
              {
               if(!CheckDone)
                WeighingResult.WeightValid = OFF;
               CheckCompleted();
               WeighingDataRefreshFlag = ON;
              } 
              CheckDoneMem = ON;
              if(Simul) 
              { 
               T_EnOff(T_Simul);
               if(!T_EN[T_Simul])
               {
                TSimOffset = 5 - (msSim % 10);
                TSimOffset = TSimOffset * 0.01;
                T_PRE[T_Simul] = 3 + TSimOffset ; 
                T_EnOn(T_Simul);
               } 
              }  
              
              if(Batch.Preset > 0)
              {
               Batch.Count++;
               if(Batch.Count >= Batch.Preset)
               {
                BatchEnded = ON;
               }
              }
                
             } 
          
           if(!Fault_Type[FLT_STOP])
           {  
            if(!SampledInPause)
            {  
             if(!ATCheckDone)
             {
              CheckDone = OFF;
              if(!AutoMode || ZeroRequired || BatchEnded || AT.CheckRecordDone || RestartOnExitBag)
              {
               SeqMaster = stp_EXITUNIT;
               break;
              }
            
              else
              {
               if(DownStreamRdy)
               {
                Output_ON(O_RdyToRcv);
                SeqMaster = stp_RUN;
                
                break; 
               }
              
               else
               {
                Output_OFF(O_StartCnv);
                SeqMaster = stp_STANDBY;
                break; 
               } 
              }
             } 
            }
            else if(!MsgWaitPauseSent)
             {
              MessageDisplay(lsub(TX_MSGWAITPAUSE),Step_Message);
              MsgWaitPauseSent = ON;
             }  
           }
           
           else  //Stop fault: Transport Error & Speed Ctrl error
           {
            if(PCExitBlocked) 
             Output_OFF(O_StartCnv);
            Output_OFF(O_RdyToRcv);
            RestartOnExitBag = ON;
           } 
            
          }
              
          break; 
          
  case  stp_EXITUNIT:
            if(SeqMasterMEM != SeqMaster)
            {
             SeqMasterMEM = SeqMaster;
             Output_OFF(O_RdyToRcv);
             MsgAtExit=0;
             RestartOnExitBag = OFF;
            }
            
            if(PCExitBlocked)
            {
             if(DownStreamRdy)
              {
               if(!IO_State[O_StartCnv])
                { 
                 Output_ON(O_StartCnv);
                } 
               if(MsgAtExit!=1)
                {
                 if(CheckAll)
                 {
                  if(!AutoTune)
                   MessageDisplay(lsub(TX_MSGWAITINGUNITEXIT),Step_Message); 
                  else
                   MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGWAITINGUNITEXIT)),Step_Message);
                 }   
                 else
                  MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGWAITINGUNITEXIT)),Step_Message);
                 MsgAtExit=1;
                } 
              }
             else
              {   
               if(IO_State[O_StartCnv])
                { 
                 Output_OFF(O_StartCnv);
                } 
               if(MsgAtExit!=2)
                {
                 if(CheckAll)
                 {
                  if(!AutoTune)
                   MessageDisplay(lsub(TX_MSGWAITDOWNSTREAM),Step_Message); 
                  else
                   MessageDisplay(concat(ATCheckRecordMsg," - ",lsub(TX_MSGWAITDOWNSTREAM)),Step_Message);
                 }   
                 else
                  MessageDisplay(concat(lsub(TX_BYPASS_CHECK)," - ",lsub(TX_MSGWAITDOWNSTREAM)),Step_Message);
                 MsgAtExit=2;
                } 
              }
            }
            
            else
            {
              if(BatchEnded) 
               MessageDisplay(lsub(TX_MSGENDOFBATCH),Step_Message);
              SeqMaster = stp_INIT; 
            }  
        break;
 }
    if(FaultState(FltB_ExitPCBlocked) || FaultState(FltB_EntryPCBlocked))
    { 
     Output_OFF(O_StartCnv);
     Output_OFF(O_RdyToRcv);
     SeqMaster = stp_INIT;
    } 
       
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_AutoTune
--  Created by        : Steve Santerre
--  Last modified on  : 2020/03
--  
--  Purpose           : Check Weigher AutoTuning Sequence
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/

void SEQ_AutoTune(void)
{
 bool    CheckRecordStartedFlag;              
 decimal NominalWeightKg%6.dp;
 float   ZeroRecordPctMem,ZeroAnalysePctMem,CheckRecordPctMem,CheckAnalysePctMem;
 int     ZeroFilterTemp;
 
if(SeqModeManager == stp_OFF_MODE) SeqAutoTune = stp_INIT;
 
   
 
 switch (SeqAutoTune)
  {
   case stp_INIT:
            if(SeqAutoTuneMEM != SeqAutoTune)
                {
                SeqAutoTuneMEM = SeqAutoTune;
                check_abort_zero_recording(CD_HANDLE_BG,CD_SCALE_NO);
                check_abort_zero_analysis(CD_HANDLE_BG,CD_SCALE_NO);
                check_abort_recording(CD_HANDLE_BG,CD_SCALE_NO);
                check_abort_analysis(CD_HANDLE_BG,CD_SCALE_NO);
                CheckRecordStarted = OFF;
                ATWriteConfirm = OFF;
                ATEndSetParamStep = OFF;
                AT.CheckRecordPct = 0;
                ATCheckRecordMsg = "";
                AutoTuneActive = OFF;
                AT.CheckRecordDone = OFF;
                AutoTune = AutoTuneOFF;
                CheckAnalyseStarted = OFF;
                ZeroAnalyseStarted = OFF;
                CheckAnalyseLog(-1);
                }
              
            if(AutoTuneActive)
            {
             if(!PCEntryBlocked && !PCExitBlocked)
              {
               Output_ON(O_StartCnv);
               
               if(ATWithZero)
                SeqAutoTune = stp_AT_ZERORECORD;
               else
                SeqAutoTune = stp_AT_CHECKRECORD; 
               
               break;
              }
             else if(DownStreamRdy)
             {
              if(!IO_State[O_StartCnv])
               { 
                Output_ON(O_StartCnv);
               }
             }
             else
             {
              MessageDisplay(lsub(TX_MSGWAITDOWNSTREAM),Step_Message);
             }
            }   
                
            break;
            
   case stp_AT_ZERORECORD:
            if(SeqAutoTuneMEM != SeqAutoTune)
                {
                 SeqAutoTuneMEM = SeqAutoTune;
                 MessageDisplay(lsub(TX_ATZERORECORD),Step_Message);
                 AT.ZeroRecordTime = 20;
                 ZeroRecordStarted = OFF;
                 AT.ZeroRecordDone = OFF;
                 AT.ZeroRecordPct  = 0;
                 if(check_start_zero_recording(CD_HANDLE_BG,CD_SCALE_NO,AT.ZeroRecordTime))
                  {
                   ZeroRecordStarted = ON;
                  }
                 else
                  {
                   SystemErrorCode = "750 Autotune:Zero record-request failed";
                  }
                }
                
                if(ZeroRecordStarted)
                {
                 if(!check_query_zero_recording(CD_HANDLE_BG,CD_SCALE_NO,ZeroRecordPctMem,AT.ZeroRecordDone))
                 {
                  SystemErrorCode = "751 Autotune:Zero record-status unknown";
                 }
                  
                 else
                 { 
                  AT.ZeroRecordPct = ZeroRecordPctMem*100.0;
                  if(ZeroRecordPct != AT.ZeroRecordPct)
                  {
                   ZeroRecordPct = AT.ZeroRecordPct;
                   MessageDisplay(concat(lsub(TX_ATZERORECORD),space(1),adj(AT.ZeroRecordPct,3,0),"%"),Step_Message);
                  }
                 }  
                }
                
                if(AT.ZeroRecordDone)
                { 
                 SeqAutoTune = stp_AT_ZEROANALYSE;
                } 
            break;
                          
   case stp_AT_ZEROANALYSE:
             if(SeqAutoTuneMEM != SeqAutoTune)
              {
                SeqAutoTuneMEM = SeqAutoTune;
                MessageDisplay(lsub(TX_ATZEROANALYSE),Step_Message);
                AT.ZeroAnalyseMinTime    = int(1000.0/GenCheckParam.SampleRate + 0.5); //300; in MinZeroSettingTime
                AT.ZeroAnalyseMaxTime    = int((PCDistanceMetric/BeltSpeedMetric)/2);
                AT.ZeroAnalyseMatchPct   = 100;
                AT.ZeroAnalyseFullSearch = OFF;
                AT.ZeroAnalyseDone = OFF;
                AT.ZeroAnalysePct  = 0;
                AT.ZeroAnalyseValid = OFF;
                AT.ZeroAnalyseFilterTime = 0;
                
                if(check_start_zero_analysis(CD_HANDLE_BG,CD_SCALE_NO,AT.ZeroAnalyseMinTime,AT.ZeroAnalyseMaxTime,AT.ZeroAnalyseMatchPct,AT.ZeroAnalyseFullSearch))
                {
                  ZeroAnalyseStarted = ON;
                }
                else
                {
                 SystemErrorCode = "752 Autotune:Zero analyse-request failed";
                } 
              }
              
              if(ZeroAnalyseStarted)
              {
               if(!check_fetch_zero_analysis_progress(CD_HANDLE_BG,CD_SCALE_NO,ZeroAnalysePctMem,AT.ZeroAnalyseDone))
               {
                SystemErrorCode = "753 Autotune:Zero analyse-status unknown";
               }
                  
               else
               { 
                AT.ZeroAnalysePct = ZeroAnalysePctMem*100.0;
                if(ZeroAnalysePct != AT.ZeroAnalysePct)
                 {
                  ZeroAnalysePct = AT.ZeroAnalysePct;
                  MessageDisplay(concat(lsub(TX_ATZEROANALYSE),space(1),adj(AT.ZeroAnalysePct,3,0),"%"),Step_Message);
                 }
               } 
              }
               
              if(AT.ZeroAnalyseDone)
                { 
                 ZeroAnalyseStarted = OFF;
                 if(check_fetch_zero_analysis_result(CD_HANDLE_BG,CD_SCALE_NO,AT.ZeroAnalyseFilterTime,AT.ZeroAnalyseNbrOfSettings,AT.ZeroAnalyseValid))
                 {
                  if(AT.ZeroAnalyseValid)
                  {
                   SeqAutoTune = stp_AT_CHECKRECORD;
                  }
                  else
                  {
                   SystemErrorCode = "755 Autotune:Zero analyse-invalid results";
                  }
                 }
                 else
                 {
                  SystemErrorCode = "754 Autotune:Zero analyse-results query fail";
                 }   
                } 
               
            break;
 
   case stp_AT_CHECKRECORD:
           if(SeqAutoTuneMEM != SeqAutoTune)
                {
                SeqAutoTuneMEM = SeqAutoTune;
                MessageDisplay(lsub(TX_ATCHECKRECORD),Step_Message);
                
                if(WP.Unit == TX_KG)
                  NominalWeightKg = WP.NominalWeight;
                else  
                  NominalWeightKg = WP.NominalWeight * LBtoKG;
                  
                AT.CheckRecordPct = 0;
                AT.CheckRecordDone = OFF;
                
                //Number of weighments recommended from OIML R51-1 Edition 2006
                if(NominalWeightKg <= 1)
                 AT.CheckRecordCount = 60;
                else if(NominalWeightKg <= 10)
                 AT.CheckRecordCount = 30;
                else if(NominalWeightKg <= 20)
                 AT.CheckRecordCount = 20;
                else if(NominalWeightKg > 20)
                 AT.CheckRecordCount = 10;
                      
                if(check_start_recording(CD_HANDLE_BG,CD_SCALE_NO,AT.CheckRecordCount))
                  {
                   CheckRecordStartedFlag = ON;
                   MessageDisplay(concat(lsub(TX_ATCHECKRECORD),space(1),adj(AT.CheckRecordCount,2,0),space(1),lsub(TX_ATCHECKRECORDNBR)),Step_Message);
                  }
                 else
                  {
                   SystemErrorCode = "755 Autotune:Check record-request failed";
                  }
                }
                 
                 if(CheckRecordStartedFlag)
                  {
                   //Timer to allow display of Check Record Count prior to Start feeding bags
                   if(!T_EN[T_ATRecDisplay])
                    T_EnOn(T_ATRecDisplay);
                   if(T_Dn(T_ATRecDisplay))
                    {
                     CheckRecordStartedFlag = OFF;
                     CheckRecordStarted     = ON;
                    }
                  }
                  
                  if(CheckRecordStarted && ATCheckDone)
                   {
                     ATCheckDone = OFF;
                     if(!check_query_recording(CD_HANDLE_BG,CD_SCALE_NO,CheckRecordPctMem,AT.CheckRecordDone))
                     {
                      SystemErrorCode = "756 Autotune:Check record-status unknown";
                     }
                      
                     else
                     { 
                      AT.CheckRecordPct = CheckRecordPctMem*100.0;
                      if(CheckRecordPct != AT.CheckRecordPct)
                      {
                       CheckRecordPct = AT.CheckRecordPct;
                       ATCheckRecordMsg = concat(lsub(TX_ATCHECKRECORD),space(1),adj(AT.CheckRecordPct,3,0),"%");
                      }
                      
                     }  
                   }    

                if(AT.CheckRecordDone)
                { 
                 CheckRecordStarted = OFF;
                 if(SeqMaster == stp_INIT)
                  SeqAutoTune = stp_AT_CHECKANALYSE;
                }   
            break;
                            
   case stp_AT_CHECKANALYSE:
           if(SeqAutoTuneMEM != SeqAutoTune)
              {
                SeqAutoTuneMEM = SeqAutoTune;
                MessageDisplay(lsub(TX_ATCHECKANALYSE),Step_Message);
                CheckRecordStarted = OFF;
                CheckAnalyseStarted = OFF;
                AT.CheckAnalyseMatchPct   = 1.0;
                AT.CheckAnalyseFullSearch = OFF;
                AT.CheckAnalyseDone = OFF;
                AT.CheckAnalysePct  = 0;
                AT.CheckAnalysePrimaryTime = 0;
                AT.CheckAnalyseEvalSize    = 0;
                AT.PFmin = 25;
                AT.PFmax = 625;
                AT.EFmin = 5;
                AT.EFmax = 125;
                
                if(!Analyse_Ext)
                 {
                  if(check_start_analysis(CD_HANDLE_BG,CD_SCALE_NO,AT.CheckAnalyseMatchPct,AT.CheckAnalyseFullSearch))
                  {
                   CheckAnalyseStarted = ON;
                   EnableDynamicMode(OFF,CD_HANDLE_BG);
                  }
                 }
                
                else
                 {                
                  if(check_start_analysis_ext(CD_HANDLE_BG,CD_SCALE_NO,AT.PFmin,AT.PFmax,AT.EFmin,AT.EFmax,
                     PCDistanceMetric,BeltSpeedMetric,BagLengthMetric,AT.CheckAnalyseMatchPct,AT.CheckAnalyseFullSearch))
                  {
                   CheckAnalyseStarted = ON;
                   EnableDynamicMode(OFF,CD_HANDLE_BG);
                  }
                 }
                  
                if(!CheckAnalyseStarted)
                {
                 SystemErrorCode = "757 Autotune:Check analyse-request failed";
                } 
              }
               
              if(CheckAnalyseStarted)
              {
               if(!check_fetch_analysis_progress(CD_HANDLE_BG,CD_SCALE_NO,CheckAnalysePctMem,AT.CheckAnalyseDone))
               {
                SystemErrorCode = "758 Autotune:Check analyse-status unknown";
               }  
               
               else
               { 
                AT.CheckAnalysePct = CheckAnalysePctMem*100.0;
                if(CheckAnalysePct != AT.CheckAnalysePct)
                 {
                  CheckAnalysePct = AT.CheckAnalysePct;
                  MessageDisplay(concat(lsub(TX_ATCHECKANALYSE),space(1),adj(AT.CheckAnalysePct,3,0),"%"),Step_Message);
                  CheckAnalyseLog(int(AT.CheckAnalysePct));
                 }
               } 
              }
               
               if(AT.CheckAnalyseDone)
                { 
                 CheckAnalyseStarted = OFF;
                 EnableDynamicMode(ON,CD_HANDLE_BG);
                 if(check_fetch_analysis_result(CD_HANDLE_BG,CD_SCALE_NO,AT.CheckAnalysePrimaryTime,AT.CheckAnalyseEvalSize,AT.CheckAnalyseAvg,AT.CheckAnalyseStdDev))
                 {
                  if(AT.CheckAnalysePrimaryTime > 0 && AT.CheckAnalyseEvalSize > 0)
                  {
                   SeqAutoTune = stp_AT_SETPARAM;
                  }
                  else
                  {
                   SystemErrorCode = "759 Autotune:Check analyse-invalid results";
                  }
                 }
                 else
                 {
                  SystemErrorCode = "760 Autotune:Check analyse-results query fail";
                 }   
                } 
                
            break;
                             
   case stp_AT_SETPARAM:
              if(SeqAutoTuneMEM != SeqAutoTune)
                {
                SeqAutoTuneMEM = SeqAutoTune;
                MessageDisplay(lsub(TX_ATSETPARAM),Step_Message);
                if(ATWithZero)
                 ZeroFilterTemp = AT.ZeroAnalyseFilterTime;
                else
                ZeroFilterTemp = BPZEROFILTER;
                ATWriteConfirmText = concat(lsub(TX_ATSETPARAM),"?\n",
                                            "Primary Filter(ms) ",adj(AT.CheckAnalysePrimaryTime,3,0),"\n",
                                            "Eval. Filter Size ",adj(AT.CheckAnalyseEvalSize,3,0),"\n",
                                            "Zero Filter(ms) ",adj(ZeroFilterTemp,3,0));
                ATWriteConfirmPopup = ON;
                }
              
              if(!ATWriteConfirmPopup)
               if(ATEndSetParamStep)
                {
                 AutoTune = AutoTuneOFF;
                 SeqAutoTune = stp_INIT;
                }
                
            break;
              
  }
  
}                  
/*-----------------------------------------------------------------------------
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
#define TIMECONTROL   //added by namk
#define FACTOR 1

//Global Variables
decimal TargetWeightIPTemp%10.2; //For SEQ_ControlTargetWeight
decimal targetweightiptemp%10.2,dtftemp%10.2,nominalweighttemp%6.2;//For SEQ_ControlTargetWeight
bool BatchEndDone;//added by namk
bool InPauseDone; //added by namk
float RegulatedTime; //added by namk
int SeqModeManagerMEM, SeqMasterMEM, SeqSpoutMEM, SeqWeighPanMEM, SeqFeederMEM,SeqFeedSTDMEM,SeqManDischargeMEM,SeqKickerMEM;
int SeqFlowThroughMEM,SeqBatchingModeMEM,SeqLowFeedRateLimitMEM,SeqCleanOutWeightMEM,SeqPulseTotalWeightMEM,SeqBatchPresetMEM;
int SeqModeManagerNext, SeqMasterNext, SeqSpoutNext, SeqWeighPanNext, SeqFeederNext,SeqFeedSTDNext,SeqManDischargeNext,SeqKickerNext;
int SeqStartWithOpenGates,SeqStartWithOpenGatesMEM;
int ManualModeStep;
bool OutOfTol[2];
bool OK4BulkFeed,OK4IntermFeed,OK4DribbleFeed,FirstWeighment=ON;
bool I_StartMem,I_StopMem,DischReq,I_ResetOutofTolAlarmMem,BagAtKickerMem,KickerRetractedOffMem,
     I_ClearFaultsMem,I_TglEmptyHopper,I_HopperEmptyMem,I_ManDischMem,BulkFeedMem,DribbleFeedMem;
int I;
bool WeighingDataRefreshFlag;
bool KnockHammerFlag,KnockHammerOut,KnockHammerFlipped,FeedCycleCancelled;
void OutReset(void);
bool TargetWeightControlON(void);
/****************Discharge Request Check***************************/
void DischReqCheck(void)
 {
  int SeqModeManagerTemp;
   
  if(!IOTestFlag)
  {
   if(Input_State(I_DischReq))
   {
    //if(!DischReq &&(WP.FeedAlgoType != FeediQSim || (WP.FeedAlgoType == FeediQSim 
    //&& SeqSpout == stp_INIT)))
    //{  
     if((!DischReqInputOn && SeqModeManager == stp_OFF_MODE) || SeqModeManager != stp_OFF_MODE) //Use to make sure that input is taken in account only when in accepted modes
     { 
      DischReq=ON;
     }
    //} 
    DischReqInputOn = ON;
   if(DischReq && SeqModeManager == stp_OFF_MODE && SeqModeManagerTemp != SeqModeManager)
    {
     DischReq=OFF;
     //DischReqMem=OFF;
    } 
   }
        
  if(DischReqMem || DischReqInputOn)
   if(!Input_State(I_DischReq) || (/*WP.FeedAlgoType == FeediQSim &&*/ IO_State[O_Discharge]))//Steve commented 13/03/2019
   {
   if(!T_EN[T_DischReqDebouncing])   
     if(T_PRE[T_DischReqDebouncing]!=0) T_EnOn(T_DischReqDebouncing);
               
   if(T_Dn(T_DischReqDebouncing)|| T_PRE[T_DischReqDebouncing]==0)  
     {
     DischReqMem=OFF;
     DischReq=OFF;
     DischReqInputOn = OFF;
     if(T_EN[T_DischReqDebouncing])T_EnOff(T_DischReqDebouncing);
     }
   }
   if(SeqModeManagerTemp != SeqModeManager)
    SeqModeManagerTemp = SeqModeManager;
  }
 } 
 
 
/****************Hopper Low Level Fault***************************/
bool CheckLowLevel(void)
{
 bool LowLevelOK=OFF;
  if(SeqModeManager!=stp_OFF_MODE && SeqModeManager!=stp_MANUAL_MODE)
    {
     if(LowLevel[Scale1] && !EmptyHopper && IO_Enable[I_LowLevelSensor])//IO_Enable[I_LowLevelSensor] added by namk 20/06/2019 (requested by Paul)
     {
       LowLevelOK=OFF;
       if(!FaultState(FltW_HopperLowLevel)) 
        FaultHandler(FltW_HopperLowLevel,"");
     }
     else 
      {
       if(FaultState(FltW_HopperLowLevel))
        {
         if(!LowLevelManReset || EmptyHopper)FaultResetReq();
        }
       else
        LowLevelOK=ON;
      }
    }
  return(LowLevelOK);   
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckFailSafeON
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/10/18
--  
--  Purpose           : Check fail safe 
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckFailSafeON(void)
{
  if(MP.FailSafe)
  {
    if(FaultState(FltG_EmergencyStop) || FaultState(FltG_MotorFailure) || FaultState(FltB_DischargeTooLong) || FaultState(FltB_ExceededCapacity)
    || FaultState(FltS_ZeroOutOfRange) || FaultState(FltB_FeedGateNotClose))
    { 
       FailSafeON = true;
    }
    else
    {
      FailSafeON = false;
    }
  }
  else
  {
    FailSafeON = false;
  }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckStopWithGatesAndDischDoorOpen
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2019/06/21
--  
--  Purpose           : Check and function if parameter Stop with gates 
--                      and disch door open
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckStopWithGatesAndDischDoorOpen(void)
{
  if(MP.StopWithGatesAndDischDoorOpen)
  {
    if(SeqModeManager == stp_OFF_MODE || SeqModeManager == stp_STOP_MODE || SeqModeManager == stp_MANUAL_MODE || SeqModeManager == stp_PREP_MODE)
    {
      StopWithGatesAndDischDoorOpenON = true;
    }
    else
    {
      StopWithGatesAndDischDoorOpenON = false;
    }
  }
  else
  {
    StopWithGatesAndDischDoorOpenON = false;
  }  
}


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
bool failSafeOnInvert,failSafeOnNoInvert;
failSafeOnInvert = (MP.InvertFeedAndDischOutputs && MP.FailSafe && FailSafeON);
failSafeOnNoInvert =  (MP.FailSafe && FailSafeON && !MP.InvertFeedAndDischOutputs);

  for(i=37;i<=MaxArrayIODbase;i++) 
  {
    if(!failSafeOnInvert)
    {
      if(i == O_Fault || i==O_WatchDog || (i == O_CleanOutWeight && WP.WeighmentsPerUnit > 1) || 
      ((MP.InvertFeedAndDischOutputs || FailSafeON || StopWithGatesAndDischDoorOpenON) && (i==O_BulkFeed || i==O_DribbleFeed || i==O_DischDoor)))
        DoNoReset = ON;
      else
        Output_OFF(i); 
    }
    else
    {
      if(i == O_Fault || i==O_WatchDog || (i == O_CleanOutWeight && WP.WeighmentsPerUnit > 1) || (FailSafeON && (i==O_BulkFeed || i==O_DribbleFeed || i==O_DischDoor)))
        DoNoReset = ON;
      else
        Output_OFF(i); 
    }
    IO_Force[i] = OFF;
    IO_TestState[i] = OFF;
  }
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ClearComparators();
--  Created by        : Steve Santerre
--  Last modified on  : 2017/01
--  
--  Purpose           : This function is called to Clear the Comparators
--                     
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void ClearComparators(void)
{
clrcomparator(SCALE_NUMBER,Scale1CmpBulk);
clrcomparator(SCALE_NUMBER,Scale1CmpInterm);
clrcomparator(SCALE_NUMBER,Scale1CmpDribble);
clrcomparator(SCALE_NUMBER,Scale1CmpCatchGate);
clrcomparator(SCALE_NUMBER,Scale1CmpCatchGateDribble);
Scale1CmpBulkActive = OFF;
Scale1CmpIntermActive = OFF;
Scale1CmpDribbleActive = OFF;
Scale1CmpCatchGateActive = OFF;
}



          
/*------------------------------------------------------------------------- 
--  Procedure Name    : FeedSTDReset();
--  Created by        : Steve Santerre
--  Last modified on  : 2017/01
--  
--  Purpose           : This function is called to Clear the Comparators
--                     
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void FeedSTDReset(void)
{
ClearComparators();
if(!MP.InvertFeedAndDischOutputs)//Invert Feed and Disch outputs function
{
Output_OFF(O_BulkFeed);
Output_OFF(O_DribbleFeed);
}
else
{
Output_ON(O_BulkFeed);
Output_ON(O_DribbleFeed);
}
T_EnOff(T_BulkBlankT);
T_EnOff(T_IntermBlankT);
T_EnOff(T_DribbleBlankT);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : InitStandardFeed();
--  Created by        : Steve Santerre
--  Last modified on  : 2017/04
--  
--  Purpose           : This function is called to Initialize Standard Feed
--                     
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void InitStandardFeed(bool setfilter)
{
bool Pass[10];
  
  OpenConnection();
  Pass[0]=SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_SCALE);
  Pass[1]=iQOutRelease();
  if(setfilter)
   {
    Pass[2]=iQSetSlowFilterSize (SCALE_CHANNEL, SCALE_NUMBER,Lim((SMFilterSize-5),(SMFilterSize+5),MP.StdFilterSize));
   } 
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : HoldCycle
--  Created by        : Steve Santerre 
--  Last modified on  : 2017/24/01
--  
--  Purpose           : Hold Cycle for Standard Feed
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void HoldCycle(void)
{
    FeedSTDReset();
    Output_ON(O_CycleInHold);
    CycleInHoldMem = ON;
    HoldCycleTgl = OFF;
    Start_PauseBtn = StartBtn;
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : UnHoldCycle
--  Created by        : Steve Santerre 
--  Last modified on  : 2017/24/01
--  
--  Purpose           : Hold Cycle for Standard Feed
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/

bool UnHoldCycle(void)
{
  bool UnHoldInDribble;
    
    if(NetWeight[Scale1] > (0.9*WP.BulkCutoff)) UnHoldInDribble = ON; 
    else UnHoldInDribble = OFF;
    Output_OFF(O_CycleInHold);
    CycleInHoldMem = OFF;
    HoldCycleTgl = OFF;
    Start_PauseBtn = PauseBtn;
  return(UnHoldInDribble);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Discharged
--  Created by        : Steve Santerre 
--  Last modified on  : 2017/02
--  
--  Purpose           : Manage Variable when Discharging
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Discharged(void)
{
  WeighPerUnitAcc = 0;
  WeighPerUnitCorrOffset = 0;
  WeighPerUnitSum = 0;
  WeighPerUnitDone = OFF;
  WeighmentAborted = OFF;
  WeighPerUnitSaveFlag = Execute;
  RefreshAutoScreenReq();
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

  if(IO_Enable[I_ChangeWPIN1])
   {
    if(Input_State(I_ChangeWPIN1)) setbit(0,RecipeFromInputs);
    else                           clrbit(0,RecipeFromInputs);
    
    if(Input_State(I_ChangeWPIN2)) setbit(1,RecipeFromInputs);
    else                           clrbit(1,RecipeFromInputs);
    
    if(Input_State(I_ChangeWPIN3)) setbit(2,RecipeFromInputs);
    else                           clrbit(2,RecipeFromInputs);
    
    if(Input_State(I_ChangeWPIN4)) setbit(3,RecipeFromInputs);
    else                           clrbit(3,RecipeFromInputs);

   if(RecipeFromInputs != MemRecipe)
    if(SeqModeManager == stp_OFF_MODE && RecipeFromInputs != 0)
     {
      LoadWPFromInputsFlag = Execute;
     }                         
   }

  if(IO_Enable[O_WPNumbOUT1])
  {
    if(SeqModeManager == stp_AUTO_MODE)
    {
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
    }
   else MemRecipeIO = 0;  
  }


}


/*------------------------------------------------------------------------- 
--  Procedure Name    : iQSimFeed
--  Created by        : Steve Santerre
--  Last modified on  : 2017/02
--  
--  Purpose           : Prepare and Start Simulated Weight for Feeding
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void iQSimFeed(void)
{
decimal BulkDuration%3.1,DribbleDuration%3.1;
decimal BulkM%6.3,BulkB%6.2,DribbleM%6.3,DribbleB%6.2,BulkCO%6.2;
string BulkFormula[64],DribbleFormula[64];




if(WP.TopUpOFFTime > 0) BulkDuration = WP.TopUpOFFTime;
else                    BulkDuration = 1.5;

if(WP.TopUpONTime > 0)  DribbleDuration = WP.TopUpONTime;
else                    DribbleDuration = 2.5;

if(WP.BulkCutoff > 0)   BulkCO = WP.BulkCutoff;                
else                    BulkCO = TargetWeight[Scale1] * 0.75;
  
BulkM = (BulkCO*UnitIQtoADM) / BulkDuration;
BulkB = 0;
DribbleM = ((TargetWeight[Scale1] - BulkCO)*UnitIQtoADM) / DribbleDuration;
DribbleB = BulkCO*UnitIQtoADM;

BulkFormula = concat(string(BulkM)," * t + ",string(BulkB));
DribbleFormula = concat(string(DribbleM)," * t + ",string(DribbleB));

     iQSimFeedProg = concat
       (
        iQSimFormatProgram (BulkFormula, BulkDuration), ":",
        iQSimFormatProgram (DribbleFormula, DribbleDuration)
       );
     
     iQSimSetProgram (SCALE_CHANNEL, SCALE_NUMBER, iQSimFeedProg);
     iQSimSetWeight(SCALE_CHANNEL, SCALE_NUMBER,(TargetWeight[Scale1]*UnitIQtoADM));
     iQSimStartProgram (SCALE_CHANNEL, SCALE_NUMBER);
                 
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : iQSimDischarge
--  Created by        : Steve Santerre
--  Last modified on  : 2017/02
--  
--  Purpose           : Prepare and Start Simulated Weight for Discharge
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void iQSimDischarge(void)
{
decimal DischDuration%4.2;
decimal DischM%6.3,DischB%6.2;
string DischFormula[64];

DischDuration = WP.DischargeTime;
DischM = 0 - (TargetWeight[Scale1]*UnitIQtoADM / DischDuration);
DischB = TargetWeight[Scale1]*UnitIQtoADM;

DischFormula = concat(string(DischM)," * t + ",string(DischB));
  
     iQSimDischProg = concat
       (
        iQSimFormatProgram (DischFormula, DischDuration)
       );
     iQSimSetProgram (SCALE_CHANNEL, SCALE_NUMBER, iQSimDischProg);
     iQSimSetWeight(SCALE_CHANNEL, SCALE_NUMBER,0.0);
     iQSimStartProgram (SCALE_CHANNEL, SCALE_NUMBER);
                 
}
                 
/*------------------------------------------------------------------------- 
--  Procedure Name    : WeighPerUnit
--  Created by        : Steve Santerre
--  Last modified on  : 2017/02
--  
--  Purpose           : Manage Weighing Data
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void WeighPerUnit(void)
{
 WeighPerUnitAcc++;
 
 if(WP.WeighmentsPerUnit > 1)
 {
  
  WeighPerUnitSum = WeighPerUnitSum + CheckedWeight[Scale1];
  if(WeighPerUnitCorrUsed && WeighPerUnitAcc == (WP.WeighmentsPerUnit-1))
   {
     WeighPerUnitCorrOffset = (TargetWeight[Scale1] * (WP.WeighmentsPerUnit-1)) - WeighPerUnitSum;
   }
  else
   {
     WeighPerUnitCorrOffset = 0;
   }     
 }
 else WeighPerUnitCorrOffset = 0;
 
 if(WeighPerUnitAcc >= WP.WeighmentsPerUnit || CleanoutWeighment) 
   WeighPerUnitDone = ON;
 
 WeighPerUnitSaveFlag = Execute;
} 


/*------------------------------------------------------------------------- 
--  Procedure Name    : BulkCutoffCorrection
--  Created by        : Steve Santerre
--  Last modified on  : 2017/04
--  
--  Purpose           : This function is called to Calculate Bulk Cutoff
--                      base on desired Dribble Time & correction
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
 void BulkCutoffCorrection(void)
 {
  float TimeDiff,TimePct,BulkCorrection;
  
  //Bulk Cutoff correction only if Dribble time is between 75% and 125% of Desired time)
  if(ProdDribbleDuration[Scale1] >= (WP.DFTime * 0.75) && ProdDribbleDuration[Scale1] <= (WP.DFTime * 1.25))
   {
     TimeDiff = ProdDribbleDuration[Scale1] - WP.DFTime; //+ if dribble too long
     TimePct = TimeDiff/WP.DFTime;
     BulkCorrection = (MP.DFWeightCorr/100) * TimePct;
     WP.BulkCutoff = WP.BulkCutoff *(1 + BulkCorrection);
     WP.BulkCutoff = Lim((TargetWeight[Scale1] - WP.Cutoff),TargetWeight[Scale1],WP.BulkCutoff);
     SaveWPFlag = Execute;
     RefreshWPScreen_No = SCREEN_RECIPE1;
   }  

 }
 
 
 /*------------------------------------------------------------------------- 
--  Procedure Name    : CutoffCorrection
--  Created by        : Steve Santerre
--  Last modified on  : 2016/02
--  
--  Purpose           : This function is called to Calculate Cutoff
--                      based on desired correction
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
 void CutoffCorrection(void)
 {
 float tempo,tempo1,tempo2,min,max; // we could try tempo3%8.dp 
 float tempo3;
 
 if(!MP.CorrOnAverage) tempo1 = (TargetWeight[Scale1] - CheckedWeight[Scale1]);
 else 
     {
      SumCheckedWeight[Scale1] = SumCheckedWeight[Scale1] + CheckedWeight[Scale1];
      NbrCheckedWeight[Scale1] ++;
      AvgCheckedWeight[Scale1] = SumCheckedWeight[Scale1] / NbrCheckedWeight[Scale1];
      tempo1 = 0;
     
      if(LastCheckedWeight[Scale1]) 
        {
           tempo1 = TargetWeight[Scale1] - AvgCheckedWeight[Scale1];
           AvgCheckedWeight[Scale1] = 0;
           SumCheckedWeight[Scale1] = 0;
           NbrCheckedWeight[Scale1] = 0;
           LastCheckedWeight[Scale1] = OFF; 
        }
     }
 tempo2 = (MP.CutoffCorr/100);
 tempo =  tempo1 * tempo2;
 min = (((100.0 - MP.CutoffCorrLimit)/100)* WP.NominalWeight);
 max = (((100.0 + MP.CutoffCorrLimit)/100)* WP.NominalWeight);
 tempo3 = Lim(min, max,(WP.Cutoff+tempo));
 CutoffCorrOffset[Scale1]= (WP.Cutoff+CutoffCorrOffset[Scale1]) - tempo3;
 RefreshWPScreen_No = SCREEN_RECIPE1;
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

CheckOIML();

ZeroFreqVal = MP.ZeroFreq * MP.SampleFreq;
if (ZeroFreqCnt >= ZeroFreqVal) ZeroFreqCnt=0;
if (SampleFreqCnt >= MP.SampleFreq) SampleFreqCnt=0;


T_PRE[T_StabTimeLimit]=Lim(0.01,20,MP.StabTimeLimit);
T_PRE[T_IntermBlankT] = MC.DribBlankT;
T_PRE[T_DribbleBlankT] = MC.DribBlankT;
T_PRE[T_TopUpONTime]=WP.TopUpONTime;
T_PRE[T_TopUpOFFTime]=WP.TopUpOFFTime;
T_PRE[T_OutOfTolTime]=MP.OutOfTolTime;
T_PRE[T_LowFeedingTime]=MP.LowFeedingTime;
T_PRE[T_DischargeTime]=WP.DischargeTime;
T_PRE[T_FeedDelayTime]=WP.FeedDelayTime;
T_PRE[T_DischDoorMaxTime] = MP.DischDoorMaxTime;
T_PRE[T_SlowCycleTime] = MP.SlowCycleTime;
T_PRE[T_FallingTime] = WP.PresetFeedRate1;
T_PRE[T_DischReqDebouncing] = MC.DischReqDebouncing;
T_PRE[T_CatchGateDelay] = WP.CatchGateDelay;
T_PRE[T_RefillingTimeT] = MC.RefillingTimeT;
T_PRE[T_LowLevelDebounce] = MC.LowLevelDebounceT;
T_PRE[T_PresetCycleTime] = WP.PresetCycleTime;
T_PRE[T_FeedGateMaxTime] = MP.FeedGateMaxTime;
FlexIO_SetTPresetsFlag = Execute;
Reset_FlexIOFlag = Execute;

if(LowLevel[Scale1] && WP.FeedAlgoType != FeediQSim) 
 {
  ZeroFreqCnt = 0;
  SampleFreqCnt = 0;
 }

RefreshGrayoutFlag = ON;

}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ResetFeedRate
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/11
--  
--  Purpose           : This procedure will reset Feed Rate
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void ResetFeedRateRelatedData(void)
{
  ProdFeedRate[Scale1] = 0;
  RefreshAutoScreenReq();
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
ZeroFreqCnt = 0;
SampleFreqCnt = 0;
CleanoutWeighment = OFF;
IsCleanoutDone = OFF;
LastCheckedWeight[Scale1] = OFF;
AvgCheckedWeight[Scale1] = 0;
SumCheckedWeight[Scale1] = 0;
NbrCheckedWeight[Scale1] = 0;
ProdCycleUnitsPerMin[Scale1] = 0;
SeqPulseTotalWeight = stp_InitPTW;
ProdCycleDuration[Scale1] = 0;
FeedRateCalTime = 0;
Wait4FeedTime = 0; 
ResetFeedRateRelatedData(); 
SeqFlowThrough = 0;
FlowThroughGraphCnt = 0;
SampleOn = OFF;
ToleranceCheckOFF = OFF;
StartBatch = OFF; 
SeqBatchingMode = stp_InitWeighment;
SeqBatchPreset = stp_InitBatchPreset;//11/03/2019 to reset Batch count sequence
BatchEndOnReceive = OFF;
ProdRemainBatch = WP.PresetBatch - Batch.Count;
if(BatchEndDone) ResetBatch();
if((MC.WeighingMode == Batching && WP.PresetBatch == 0) || BulkByWeightON)
{
SeqBatchingMode = stp_InitWeighment;
CleanOutWeightDone = OFF;
SeqCleanOutWeight = stp_InitCleanOutWeight;
BatchEndReq = OFF;
BatchCancelled = OFF;
BatchEndDone = OFF;
TotalWeightBatchTemp = Batch.TotalWeight;
}
CutoffTemp = WP.Cutoff;
TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
FirstWeighment=ON;
KnockHammerFlag=OFF;
iQFeedWaitSettled = OFF;
EmtpyBagReadyMem = ON;
 

OutReset();
if(Fault_Type[FLT_GEN] == 0) FaultResetReq();
  
for(I=1;I<TMAX;I++) T_EnOff(I);

if(WP.FeedAlgoType == FeedStd || WP.FeedAlgoType == FeediQSim)
{
//CloseChannelConnection();
ClearComparators();
}

#ifndef __SIMULATION__
  if(WP.FeedAlgoType == FeediQSim)
   { 
    iQSimOpen(SCALE_CHANNEL, SCALE_NUMBER,"127.0.0.1");
   }
  else
   {
    iQSimClose(SCALE_CHANNEL, SCALE_NUMBER);
   }
#endif
  
   
if(WP.FeedAlgoType != FeedStd && WP.FeedAlgoType != FeediQSim)
{
FeedingStop();
GetFillingData(ON);
}
InitiQSmart = ON;
InitiQFlash = ON;

if(SeqModeManager == stp_OFF_MODE)
{
SeqMaster=stp_INIT;
SeqSpout=stp_INIT;
SeqWeighPan=stp_INIT;
SeqFeeder=stp_INIT;
SeqFeedSTD=stp_INIT;
SeqManDischarge = stp_INIT;
ManualModeStep = stp_INIT;

Hopper_State = HopperFill;
Discharge_State = DischMan;

CheckWeight_State = ReleaseWeight;
}

T_PRE[T_BagRelease]=0.50;
T_PRE[T_BulkDuration]=99.99;
T_PRE[T_DribbleDuration]=99.99;
T_PRE[T_CycleDuration]=999.99;
T_PRE[T_iQFeedTimeout]=60.00;
T_PRE[T_UPMDuration]= 6000.0;
T_PRE[T_FaultDisplay] = 3.0;
T_PRE[T_ActuatorON] = 0.3;
T_PRE[T_ActuatorOFF] = 0.15;
T_PRE[T_FlowThroughTime] = 0.5; 
T_PRE[T_RegulatedTime] = 1; 
T_PRE[T_TickEvery1Sec] = 1; 
T_PRE[T_PulseTotalWeight] = 0.5;
if(WP.WeighmentsPerUnit > 1 && WP.FeedAlgoType == FeedStd && MP.SampleSize == MP.SampleFreq) 
    WeighPerUnitCorrUsed = ON;
else
    WeighPerUnitCorrUsed = OFF;
    
RefreshAutoScreenReq();
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ResetDataModeChangeData
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/11/05
--  
--  Purpose           : This procedure will reset data if weighing modes change
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void ResetDataModeChangeData (void)
{
 int WeighingModeTemp,BulkModeIPTemp,TransferSiloTemp;
 bool FirstScanON;
 if(WeighingModeTemp != MC.WeighingMode || BulkModeIPTemp != WP.BulkModeIP || TransferSiloTemp != WP.TransferSilo)
 {
    WeighingModeTemp = MC.WeighingMode;
    BulkModeIPTemp = WP.BulkModeIP;
    TransferSiloTemp = WP.TransferSilo;
    if(FirstScanON)
    {
    ResetBatch();
    VarInitOff();
    }
    FirstScanON = ON;
 }
} 

/*------------------------------------------------------------------------- 
--  Procedure Name    : Low Level
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/28
--  
--  Purpose           : Variables to Set Low Level
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void LowLevelStatus(void)
{
 bool LowLevelMem[2];
 if(!IOTestFlag)
 {
  if(!Input_State(I_LowLevelSensor))
   { 
    //LowLevel is ON when Input is OFF                            
    if(MC.LowLevelDebounceT>0 && !T_EN[T_LowLevelDebounce]) T_EnOn(T_LowLevelDebounce);
    if(MC.LowLevelDebounceT<=0 ||T_Dn(T_LowLevelDebounce))  
    {
     LowLevel[Scale1]=ON;
     Output_ON(O_LowLevel);
    } 
   } 
   
  else 
  {    
   I_LowLevelSensorMEM = ON;
   LowLevel[Scale1]=OFF;
   Output_OFF(O_LowLevel);
   if(T_EN[T_LowLevelDebounce]) T_EnOff(T_LowLevelDebounce);
  }
  
  if(LowLevelMem[Scale1] != LowLevel[Scale1])
  {
   ButtonDisplayRefreshed[SCREEN_AUTOMATIC]= OFF;
   LowLevelMem[Scale1] = LowLevel[Scale1];
  }  
 }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckFeedRateLowLimit
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/28
--  
--  Purpose           : This procedure will check feed rate lower than limit 
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckFeedRateLowLimit (void)
{  
  if(SeqModeManager == stp_AUTO_MODE && (MC.WeighingMode == FeedRateControl || MC.WeighingMode == Monitoring) && WP.FeedRateLowLimit > 0)
  {
    if(MP.LowFeedingTime != 0 && ProdCycleDuration[Scale1] != 0)
    switch(SeqLowFeedRateLimit)
    {
      case stp_InitCheckLowFeedRate:
           if(SeqLowFeedRateLimitMEM != SeqLowFeedRateLimit) 
           {
             SeqLowFeedRateLimitMEM = SeqLowFeedRateLimit;
             FeedRateLowAcc = 0;
           }
           if(ProdFeedRate[Scale1] < WP.FeedRateLowLimit)
           {
             T_EnOn(T_LowFeedingTime);  // start timer
             SeqLowFeedRateLimit = stp_LowFeedRateOccurred;
           } 
           break;
               
      case stp_LowFeedRateOccurred:
           if(SeqLowFeedRateLimitMEM != SeqLowFeedRateLimit)SeqLowFeedRateLimitMEM = SeqLowFeedRateLimit; 
           FeedRateLowAcc = T_Acc(T_LowFeedingTime); // Accumulate timer
           if(FeedRateLowAcc >= MP.LowFeedingTime)
           {
             if(!FaultState(FltW_FeedRateLowLimit))
             {
               FaultHandler(FltW_FeedRateLowLimit,"");
               if(IO_Enable[O_FeedRateLowAlarm])
                 if(!IO_State[O_FeedRateLowAlarm])Output_ON(O_FeedRateLowAlarm);
             }
           }
           if(ProdFeedRate[Scale1] > WP.FeedRateLowLimit) SeqLowFeedRateLimit = stp_ResetLowFeedRate;
           break;
               
      case stp_ResetLowFeedRate:
           if(SeqLowFeedRateLimitMEM != SeqLowFeedRateLimit) 
           {
             SeqLowFeedRateLimitMEM = SeqLowFeedRateLimit;
             T_EnOff(T_LowFeedingTime); // stop timer
             Output_OFF(O_FeedRateLowAlarm);
             FeedRateLowAcc = 0;
             SeqLowFeedRateLimit = stp_InitCheckLowFeedRate;
           }
           break;
    }
    else
    {
      if(IO_State[O_FeedRateLowAlarm]) 
      {
        Output_OFF(O_FeedRateLowAlarm);
        FaultResetReq();
      }
    }
  }    
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckSiloWeight
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/04
--  
--  Purpose           : This procedure will check silo weight 
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckSiloWeight (void)
{
  if(SeqModeManager == stp_OFF_MODE && MC.WeighingMode == Bulk && WP.TransferSilo == YES)
  {  
    if ((ProdSiloNoWeight[WP.SiloNo] <= 0 && ProdSiloNoWeight[WP.SiloNo] < WP.TargetWeightIP) || WP.SiloNo == WP.SiloDest)
    {
      if(!FaultState(FltW_InvalidSiloSource))
      {
        FaultHandler(FltW_InvalidSiloSource,"");
      }
    }
    else
    {
      if(FaultState(FltW_InvalidSiloSource))FaultResetReq();
    }
           
  }    
}
/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckFeedRateHighLimit
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/28
--  
--  Purpose           : This procedure will check feed rate higher than limit 
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckFeedRateHighLimit (void)
{
  if(SeqModeManager == stp_AUTO_MODE && (MC.WeighingMode == FeedRateControl || MC.WeighingMode == Monitoring) && WP.FeedRateHighLimit > 0)
  {  
    if (ProdFeedRate[Scale1] > WP.FeedRateHighLimit)
    {
      if(!FaultState(FltW_FeedRateHighLimit))
      {
        FaultHandler(FltW_FeedRateHighLimit,"");
        if(IO_Enable[O_FeedRateLowAlarm])
          if(!IO_State[O_FeedRateHighAlarm]) Output_ON(O_FeedRateHighAlarm); 
      }
    }
    else
      if(IO_State[O_FeedRateHighAlarm]) 
      {
        Output_OFF(O_FeedRateHighAlarm);
        FaultResetReq();
      }       
  } 
  else
  {
     if(IO_State[O_FeedRateHighAlarm]) 
      {
        Output_OFF(O_FeedRateHighAlarm);
        FaultResetReq();
      }
  }   
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckMaxFeedRateLimit
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/04
--  
--  Purpose           : This procedure will check feed rate higher than Max limit 
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckMaxFeedRateLimit (void)
{
  if(SeqModeManager == stp_AUTO_MODE && (MC.WeighingMode == FeedRateControl || MC.WeighingMode == Monitoring) && MP.MaxFeedRate > 0)
  {  
    if (ProdFeedRate[Scale1] > MP.MaxFeedRate)
    {
      if(!FaultState(FltW_FeedRateMaxLimit))
      {
        FaultHandler(FltW_FeedRateMaxLimit,"");
      }
    }
    else
    {
      if(FaultState(FltW_FeedRateMaxLimit))FaultResetReq();
    }
           
  }    
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckMaintenanceCycle
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/28
--  
--  Purpose           : This procedure will check maintenance cycle reaches
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckMaintenanceCycle (void)
{
  if(SeqModeManager != stp_OFF_MODE && SeqModeManager != stp_MANUAL_MODE && MP.MaintCycle > 0)
  {
      if(ProdTotalUnitsCnt[Scale1] >= (MP.MaintCycle*100))
      {
        if(!FaultState(FltW_MaintenanceCycle))
        {
          FaultHandler(FltW_MaintenanceCycle,"");
          if(IO_Enable[O_MaintenanceCycle])
            if(!IO_State[O_MaintenanceCycle])Output_ON(O_MaintenanceCycle);
        }
      } 
      else
      {
        if(IO_State[O_MaintenanceCycle])
        {
          Output_OFF(O_MaintenanceCycle);
          FaultResetReq();
        }
      }            
  }
  if(SeqModeManager == stp_OFF_MODE) 
    if(IO_State[O_MaintenanceCycle])Output_OFF(O_MaintenanceCycle) ; 
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
   CheckFeedRateLowLimit();    
   CheckFeedRateHighLimit();
   CheckMaintenanceCycle();  
   CheckMaxFeedRateLimit();
   CheckSiloWeight();
   
   //Feed gate not close fault
   if(FeedGateNotClose)
   {
    if(!FaultState(FltB_FeedGateNotClose)) 
     {
      FaultHandler(FltB_FeedGateNotClose,"");
     }
    else
     {
      T_EnOff(T_FeedGateMaxTime);
      FeedGateNotClose = OFF;
      FeedGateStillClose = OFF;
     }
   }  
     
   //E-Stop Fault 
   
   if (IO_Enable[I_EStop] && !Input_State(I_EStop) && !FaultState(FltG_EmergencyStop)) 
       FaultHandler(FltG_EmergencyStop,"");
               
   //Low Air pressure Fault
   if (IO_Enable[I_PressureSW] && !Input_State(I_PressureSW) && !FaultState(FltG_LowAirPressure)) 
        FaultHandler(FltG_LowAirPressure,"");
    
    //Discharge Door Not Closed Fault
    if (IO_Enable[I_DischDoorClose])
    { 
     if(I_DischDoorCloseMem != Input_State(I_DischDoorClose) || ClearFaultON)
     {
        I_DischDoorCloseMem = Input_State(I_DischDoorClose);
        if((!I_DischDoorCloseMem && !MP.StopWithGatesAndDischDoorOpen) && ((!MP.InvertFeedAndDischOutputs && !IO_State[O_DischDoor]) || (MP.InvertFeedAndDischOutputs && IO_State[O_DischDoor])))//modified by namk 21/06/2019
          I_DischDoorCloseLost = ON;
        else
          I_DischDoorCloseLost = OFF;
        ClearFaultON = false;
     }      
           
     if((!Input_State(I_DischDoorClose) || DischDoorStillClose || I_DischDoorCloseLost) && ((!MP.InvertFeedAndDischOutputs && !IO_State[O_DischDoor]) || (MP.InvertFeedAndDischOutputs && IO_State[O_DischDoor])))//modified by namk 21/06/2019
      {
       if(!FaultState(FltG_DischDoorNotClosed))
       {
        if(!T_EN[T_DischDoorMaxTime]&& MP.DischDoorMaxTime!=0) 
         T_EnOn(T_DischDoorMaxTime);
        if(T_Dn(T_DischDoorMaxTime)||MP.DischDoorMaxTime==0 || DischDoorStillClose || I_DischDoorCloseLost) 
         {
          FaultHandler(FltG_DischDoorNotClosed,"");
          T_EnOff(T_DischDoorMaxTime);
          DischDoorStillClose = OFF;
         }
       }
      } 
     else if(T_EN[T_DischDoorMaxTime])
      { 
       T_EnOff(T_DischDoorMaxTime);
      } 
    }
      
    //Exceeded Capacity Fault 
    if(SeqModeManager==stp_OFF_MODE || SeqModeManager==stp_MANUAL_MODE)
    {
     if ((NetWeight[Scale1] > MaxWeight[Scale1]) && !FaultState(FltB_ExceededCapacity))
        {
         FaultHandler(FltB_ExceededCapacity,"");
        }
    }    
    else
    {
      if ((NetWeight[Scale1] > MaxWeight[Scale1]) && !FaultState(FltG_ExceededCapacity))
        {
         FaultHandler(FltG_ExceededCapacity,"");
        }
    }
    
    //Motor Failure Fault   
    if (IO_Enable[I_MotorFailure] && !Input_State(I_MotorFailure) && !FaultState(FltG_MotorFailure))
         FaultHandler(FltG_MotorFailure,"");
   
   //Discharge Too Long
   // FltB_DischargeTooLong not used
   
   //Low Battery
   //FltW_LowBattery not used
   
   //Slow cycle Fault
   if((SeqMaster == stp_FEED && !CycleInHoldMem && OK4IntermFeed && OK4DribbleFeed)|| SeqMaster == stp_TOPUP)
     {
     if (!FaultState(FltW_SlowCycle))
      {
     if(T_PRE[T_SlowCycleTime]!= 0 && !T_EN[T_SlowCycleTime]) T_EnOn(T_SlowCycleTime);
     if((T_Dn(T_SlowCycleTime) || T_PRE[T_SlowCycleTime] == 0)) 
        {
        FaultHandler(FltW_SlowCycle,"");
        T_EnOff(T_SlowCycleTime);
        SlowCycleOccured = ON;
        if (LowLevel[Scale1])//if(EmptyHopper && LowLevel[Scale1])
         {
         IsCleanoutDone = ON;
          //Output_ON(O_CleanoutCompleted); //commented by namk 19/10/2018
         } 
          
        }
      
      }
     else if(!SlowCycleMem) 
      {
       SlowCycleMem=ON;
       CheckOnce = ON;
       Discharge_State = DischPanOn;
       
      }
     }
             
   else
   { 
    if(FaultState(FltW_SlowCycle)||T_EN[T_SlowCycleTime])
     if(!Fault_Type[FLT_GEN] && !Fault_Type[FLT_BLK] && !Fault_Type[FLT_STOP]) 
     {
     T_EnOff(T_SlowCycleTime);
     FaultResetReq();
     }
     
     if(SlowCycleMem) 
      {
      SlowCycleMem=OFF;
      
      } 
   }
   
   //Manage Output Slow Cycle 
   if(FaultState(FltW_SlowCycle))
   {
     if(IO_Enable[O_SlowCycle])if(!IO_State[O_SlowCycle])Output_ON(O_SlowCycle); 
          
   }
   else 
   {
     if(IO_Enable[O_SlowCycle])if(IO_State[O_SlowCycle])Output_OFF(O_SlowCycle);
   }
  
  //Clear Fault Input
  if(IO_Enable[I_ClearFaults] && Input_State(I_ClearFaults) && !I_ClearFaultsMem)
    {
    I_ClearFaultsMem = ON;
    if(Fault_Type[FLT_GEN]||Fault_Type[FLT_BLK]||Fault_Type[FLT_STOP]||Fault_Type[FLT_WRN])FaultResetReq();
    if(Discharge_State == DischUnder || Discharge_State == DischOver) DischargeHMI=ON;
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

if(WeightSampled[Scale1] && !LowLevel[Scale1] && !WeighmentAborted && SqareSumWeight[Scale1]<2000000000 && SeqBatchingMode != stp_LastTwoWeighment)
  {
  NbrChecked[Scale1]++; 
  SumWeight[Scale1] = SumWeight[Scale1] + CheckedWeight[Scale1];
  AvgWeight[Scale1] = SumWeight[Scale1]/NbrChecked[Scale1];
  SqareSumWeight[Scale1] = SqareSumWeight[Scale1] + (CheckedWeight[Scale1]*CheckedWeight[Scale1]);
  
  //Excel StdevP Formula (entire population)
  ValueToSqrt = (SqareSumWeight[Scale1] - (NbrChecked[Scale1]*(AvgWeight[Scale1]*AvgWeight[Scale1])))/NbrChecked[Scale1];
  StdDev[Scale1] = sqrt(ValueToSqrt);

  }
    
   if(NbrChecked[Scale1] > 2 && !InLast2Weighments) 
    if((AvgWeight[Scale1] < (TargetWeight[Scale1]*0.75)) || (AvgWeight[Scale1] > (TargetWeight[Scale1]*1.25)))
    {
    ResetData(ON);
    }    
       ProdLastTolerance[Scale1] = "=";
       
       if(ProdUnderWeightFlag[Scale1])
        {
         ProdUnderWeightCnt[Scale1]++;
         if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && MC.WeighingMode == Batching) || BulkByWeightON || BulkByDischON)Batch.UnderWeightCnt++; 
         ProdLastTolerance[Scale1] = "-";
         ProdUnderWeightFlag[Scale1]=OFF;
        }
        
       if(ProdOverWeightFlag[Scale1])
        {
         ProdOverWeightCnt[Scale1]++;
         if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && MC.WeighingMode == Batching) || BulkByWeightON || BulkByDischON)Batch.OverWeightCnt++; 
         ProdLastTolerance[Scale1] = "+";
         ProdOverWeightFlag[Scale1]=OFF;
        }
                    
       if(WeighPerUnitDone)
          {
           ProdTotalUnitsCnt[Scale1]++;
           if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && (BatchByDischON || BulkByWeightON) ) || BulkByWeightON || BulkByDischON || BatchByWeightON)
            {
             Batch.UnitsDone++;
             Batch.Count++;
             ProdRemainBatch = WP.PresetBatch - Batch.Count;                       
             if(BatchEndReq) 
              BatchCancelled = ON;
            } 
           
           if(WP.CountAll)
            { 
             ProdAcceptUnitCnt[Scale1] =  ProdTotalUnitsCnt[Scale1];
             if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && MC.WeighingMode == Batching) || BulkByWeightON || BulkByDischON)Batch.UnitsAccepted = Batch.UnitsDone; 
            } 
           else
            {           
             ProdAcceptUnitCnt[Scale1] =  ProdTotalUnitsCnt[Scale1] - (ProdUnderWeightCnt[Scale1] + ProdOverWeightCnt[Scale1]);
             if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && MC.WeighingMode == Batching) || BulkByWeightON || BulkByDischON)Batch.UnitsAccepted = Batch.UnitsDone - (Batch.UnderWeightCnt + Batch.OverWeightCnt); //added by namk 24/9/2018
            } 
          }
          
       if(!WeighPerUnitCorrUsed)
        {
           ProdLastChecked[Scale1] = CheckedWeight[Scale1];
        }  
       else
        {
        if(WeighPerUnitDone)
          {
           ProdLastChecked[Scale1] = WeighPerUnitSum;
          }
        }        
       
       if((Batch.Preset > 0 || WP.TargetWeightIP > 0 || BulkByDischON) && WeighmentAborted) Batch.Residue = Batch.Residue + CheckedWeight[Scale1]; 
       
       ProdStdDev[Scale1] = StdDev[Scale1];
       if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && MC.WeighingMode == Batching) || BulkByWeightON || BulkByDischON)Batch.StdDev = StdDev[Scale1];

       ProdAvgWeight[Scale1] = AvgWeight[Scale1];
       if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && MC.WeighingMode == Batching) || BulkByWeightON || BulkByDischON)Batch.Avg = AvgWeight[Scale1];
              
       ProdTotalWeighmentsLT[Scale1]++;
       if(WeighPerUnitDone) ProdTotalUnitsLT[Scale1]++;
       
       //Correction of Cutoffs values
       if(WP.FeedAlgoType == FeedStd  && !WeighmentAborted && !SlowCycleOccured && !LowLevel[Scale1] && SeqBatchingMode != stp_LastTwoWeighment)
       {
        if(WeightSampled[Scale1])
        {
         if(MP.CutoffCorr > 0 && !InLast2Weighments && CheckedWeight[Scale1] > (WP.Cutoff+CutoffCorrOffset[Scale1])) 
          {
           CutoffCorrection();
          } 

        }
        else
         if(WP.DFTime > 0 && MP.DFWeightCorr > 0 && !BulkOnTime[Scale1])
          if(WP.WeighmentsPerUnit == 1 || WeighPerUnitAcc <= (WP.WeighmentsPerUnit-1))
          {
            BulkCutoffCorrection();
          }
       }
        
       if(WeightSampled[Scale1])
       {
       ProdTotalWeight[Scale1] = ProdTotalWeight[Scale1] + CheckedWeight[Scale1];
       if((Batch.Preset > 0 || WP.TargetWeightIP > 0 || BulkByDischON) && (MC.WeighingMode == Bulk || MC.WeighingMode == Batching))
       {
         Batch.TotalWeight = Batch.TotalWeight + CheckedWeight[Scale1]; 
         ProdRemainWeight = (WP.TargetWeightIP+DTFWeight)- Batch.TotalWeight;
       }
       if(MC.WeighingMode == Bulk && WP.BulkModeIP == Ship && WP.TransferSilo == YES) 
       { 
         ProdSiloNoWeight[WP.SiloNo]   -= CheckedWeight[Scale1]; 
         ProdSiloNoWeight[WP.SiloDest] += CheckedWeight[Scale1];
       }
      
       if(MC.WeighingMode == Bulk && WP.BulkModeIP == Receive && WP.TransferSilo == NO) 
       {
         ProdSiloNoWeight[WP.SiloNo]   += CheckedWeight[Scale1];  
       }
       if(ProdTotalWeightLT[Scale1] >= 21474836.48 || ProdTotalWeightLT[Scale1] == -21474836.48)ProdTotalWeightLT[Scale1]= 0;
       ProdTotalWeightLT[Scale1] = ProdTotalWeightLT[Scale1] + (CheckedWeight[Scale1]/FACTOR);
       ProdLastWeight[Scale1] = ProdLastChecked[Scale1];
       ProdLastSampled[Scale1] = ">o<";
       weighingdata_weight = concat("c",adj(ProdLastWeight[Scale1],6,dp),WP.Unit);
       }
       
       else
       {
       ProdTotalWeight[Scale1] = ProdTotalWeight[Scale1] + TargetWeight[Scale1];
       if((Batch.Preset > 0 || WP.TargetWeightIP >  0 || BulkByDischON) && (MC.WeighingMode == Bulk || MC.WeighingMode == Batching))
       {
         Batch.TotalWeight = Batch.TotalWeight + TargetWeight[Scale1]; 
         ProdRemainWeight = (WP.TargetWeightIP+DTFWeight)- Batch.TotalWeight;
       }
       
       if(MC.WeighingMode == Bulk && WP.BulkModeIP == Ship && WP.TransferSilo == YES)
       {
         ProdSiloNoWeight[WP.SiloNo]   -= TargetWeight[Scale1]; 
         ProdSiloNoWeight[WP.SiloDest] += TargetWeight[Scale1];
       }  
           
       if(MC.WeighingMode == Bulk && WP.BulkModeIP == Receive && WP.TransferSilo == NO) 
       {
         ProdSiloNoWeight[WP.SiloNo]   += TargetWeight[Scale1];  
       }
       if(ProdTotalWeightLT[Scale1] >= 21474836.48 || ProdTotalWeightLT[Scale1] == -21474836.48)ProdTotalWeightLT[Scale1]= 0;
       ProdTotalWeightLT[Scale1] = ProdTotalWeightLT[Scale1] + (TargetWeight[Scale1]/FACTOR);
       ProdLastWeight[Scale1] = TargetWeight[Scale1];
       ProdLastSampled[Scale1] = "---";
       weighingdata_weight = concat("u",adj(ProdLastWeight[Scale1],6,dp),WP.Unit);
       }
       
       
     
         
       WeighingData_StringSource[Scale1] = concat(trim(ProdBulkDuration[Scale1]),"s",space(tab),trim(ProdDribbleDuration[Scale1]),"s",
                                              space(tab-3),weighingdata_weight,space(tab-1),TimeString);
                                              
       RefreshWeighingDataPopup(1);
                                        
       
       WeightSampled[Scale1] = OFF;
       FileName_Date = getstddate();//URS TEST
       Standard_Date = concat("20",FileName_Date);//URS TEST
       
       RefreshReportScreenReq();
       RefreshAutoScreenReq();
       RefreshStatDataPopup();
       if(((Batch.Preset > 0 || WP.TargetWeightIP > 0) && MC.WeighingMode == Batching) || BulkByWeightON || BulkByDischON)
        {
         SaveBatchFlag = Execute;
         RefreshBatchScreenReq();
        } 
       
       PreSave_DataNoResetFlag = Execute;
       ProdDataReady = ON;
       ProdDataReadyPLC = ON;
       if(SlowCycleOccured)SlowCycleOccured = OFF;      
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
//for(i=1;i<=36;i++)
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
 for(i=37;i<=MaxArrayIODbase;i++)
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

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshFeederOutputs
--  Created by        : Steve Santerre
--  Last modified on  : 2016/06/08
--  
--  Purpose           : Refresh Feeders Outputs array value
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Feeder Outputs are controlled via 
                        Feeding Instructions - RTCWin
                        Their corresponding array need to be kept updated
--------------------------------------------------------------------------*/
void RefreshFeederOutputs(void)
{
  IO_State[O_DribbleFeed] = out(IO_Address[O_DribbleFeed]);
  if(IO_Enable[O_BulkFeed])         IO_State[O_BulkFeed] = out(IO_Address[O_BulkFeed]);
  
  if(DrCmpOffTime !=0 && !IO_State[O_DribbleFeed])
   {
    DrOutOffTime = systemtimer_ms();
    DrOutOffDiff = DrOutOffTime - DrCmpOffTime;
    DrCmpOffTime =0;
   } 
}

bool VerifyStart(void)
{
   if((StartHMI || (IO_Enable[I_Start] && Input_State(I_Start) && !I_StartMem)) && T_Dn(T_FirstScan))
    {
      if(Current_Screen != SCREEN_AUTOMATIC) Force_Screen_Req(SCREEN_AUTOMATIC, LARGE);
      I_StartMem = ON;
      StartHMI=OFF;
      if(DischargedCall || (!DischReq && WP.WeighmentsPerUnit==1))
       {
        if(DischargedCall)
         Discharged();
        T_EnOn(T_BagRelease);
        DischargedCall = OFF;
       }
                        
      if(Check_Scale_Cfg())
        {
         SeqModeManager = stp_PREP_MODE;
         Discharge_State = DischPanOff;
         if(BatchEnded)
           {
             Batch.Count = 0;
             BatchEnded = OFF;
             Output_OFF(O_BatchEnded);
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
bool SampledInPauseMem;
if(IO_Enable[I_Start] && !Input_State(I_Start)) 
  I_StartMem = OFF;
if(IO_Enable[I_Stop] && !Input_State(I_Stop)) 
  I_StopMem = OFF;
if(IO_Enable[I_ManDisch]&& !Input_State(I_ManDisch))
  I_ManDischMem = OFF;
if(Fault_Type[FLT_GEN]!=0 || OffHMI) 
  {SeqModeManager = stp_OFF_MODE;OffHMI=OFF;}
if((Fault_Type[FLT_GEN]!=0 ||(SeqModeManager!= stp_OFF_MODE && SeqModeManager!= stp_STOP_MODE && 
 ManualModeStep != stp_ManualOkToDisch &&!CycleInHoldMem)) && StartHMI) 
  StartHMI=OFF;
if((SeqModeManager!= stp_AUTO_MODE && SeqModeManager != stp_MANUAL_MODE) && StopHMI) 
  StopHMI=OFF;

if(IO_Enable[I_HoldCycle] && !Input_State(I_HoldCycle) && HoldCycleMem) 
  HoldCycleMem = OFF;

if(PauseHMI || (IO_Enable[I_HoldCycle] && Input_State(I_HoldCycle) && !HoldCycleMem))
 {
  AutoPause = !AutoPause;
  HoldCycleMem = ON;
  PauseHMI = OFF;
  CurMode_Set();
 }
if(SampledInPauseMem != SampledInPause)
 {
  if(SampledInPause)
   Output_ON(O_CycleInHold);
  else
   Output_OFF(O_CycleInHold); 
  SampledInPauseMem = SampledInPause;
 }   
    SeqModeManagerNext = SeqModeManager;
    switch (SeqModeManager)
    {
      case stp_OFF_MODE:
            if(SeqModeManagerMEM!=SeqModeManager)
              {
               SeqModeManagerMEM = SeqModeManager;
               Start_PauseBtn = StartBtn;
               AutoPause = OFF;
               SampledInPause = OFF;
               KeyLockPTSZI(LAST,LAST,LAST,OFF,LAST);
               VarInitOffFlag = Execute;
               VarInitCycle();
               ChangeSMStateFlag = Execute;
               DischReqCheck();
               if(MC.FeederType == FeederNone)MC.FeederType = FeederG; 
               FirstOffMode = OFF;
               StartKeyOn = OFF;
              }
         if(MC.WeighingMode != Batching)WP.WeighmentsPerUnit = 1;      
         if(VarInitOffFlag != Execute) 
          if(Fault_Type[FLT_GEN]==0)
          {    
            if(StepMsg!=lsub(TX_MSGWAITINGFORSTART) && T_Dn(T_FirstScan)) MessageDisplay(lsub(TX_MSGWAITINGFORSTART),Step_Message);
            if(VerifyStart()) 
             {
              VarInitOffFlag = Execute;
              break;
             }   
               if(Discharge_State == DischMan && (DischargeHMI ||(IO_Enable[I_ManDisch]&& Input_State(I_ManDisch)&&!I_ManDischMem)))
                    if(ON || ManualModeStep == stp_ManualOkToDisch) //after modification added by namk 18/9/2018
                        {
                        DischargeHMI = OFF;
                        I_ManDischMem = ON;
                        ManualModeStep = stp_ManualDisch;
                        SeqModeManager = stp_MANUAL_MODE;
                        break;
                        }
                    else 
                       {
                        FaultHandler(FltS_BagNotDetected,"");
                       }
                       
                          
           
          }                   
            break;
               

              
      case stp_STOP_MODE:
      if(SeqModeManagerMEM!=SeqModeManager)
         {
         SeqModeManagerMEM = SeqModeManager;
         Start_PauseBtn = StartBtn;
         KeyLockPTSZI(LAST,LAST,LAST,OFF,LAST);
         Hopper_State = HopperFill;
         StartKeyOn = OFF;
         if(CleanoutWeighment)
         {
          if(Batch.Preset > 0)
          {
           BatchEnded = ON;
           Output_ON(O_BatchEnded);
          } 
          CleanoutWeighment = OFF;
         } 

         Output_OFF(O_CycleInProgress);
         if(BatchEnded || BatchEndOnReceive) 
         {
           MessageDisplay(lsub(TX_MSGENDOFBATCH),Step_Message);
           PrintReqOnBatchEnded = ON;
           Batch.EndTime = ReadPresentDateTime();
         }
         else
         { 
           MessageDisplay(lsub(TX_MSGWAITINGFORSTART),Step_Message);
         }
         StartBatch = OFF; //added by namk 01/10/2018
         if(MC.WeighingMode == Bulk && WP.TransferSilo == YES && BulkByWeightON)  MessageDisplay(lsub(TX_MSGSILOTRANSFERRED),Step_Message);
         }
      if(StartHMI || (IO_Enable[I_Start] && Input_State(I_Start) && !I_StartMem))
                        {
                        if(Current_Screen != SCREEN_AUTOMATIC) Force_Screen_Req(SCREEN_AUTOMATIC, LARGE);
                        I_StartMem = ON;
                        StartHMI=OFF;
                        if(DischargedCall || (!DischReq && WP.WeighmentsPerUnit==1))
                         {
                          if(DischargedCall)
                           Discharged();
                          T_EnOn(T_BagRelease);
                          DischargedCall = OFF;
                         }
                          
                        if(!MP.StopWithGatesAndDischDoorOpen)SeqModeManager = stp_AUTO_MODE;//24/06/2019
                        else SeqModeManager = stp_WAIT_MODE;//24/06/2019
                        Output_ON(O_CycleInProgress);
                        if(BatchEnded)
                         {
                          Batch.Count = 0;
                          BatchEnded = OFF;
                          Output_OFF(O_BatchEnded);
                          RefreshAutoScreenReq();
                         } 
                        }
            break;

      case stp_STOPPING_MODE:
            if(SeqModeManagerMEM != SeqModeManager)
              {
              SeqModeManagerMEM = SeqModeManager;
              }
            if(SeqMaster==stp_INIT && (WeighPerUnitAcc == 0 || CleanoutWeighment))SeqModeManager = stp_STOP_MODE; //commened by namk 25/9/2018
            break;
            
      case stp_MANUAL_MODE:
            if(SeqModeManagerMEM != SeqModeManager)
              {
               SeqModeManagerMEM = SeqModeManager;
               ChangeSMStateFlag = Execute;
              }
            
            if(ManualModeStep == stp_ManualOkToDisch)
             {
              if(Discharge_State == DischMan && (DischargeHMI ||(IO_Enable[I_ManDisch]&& Input_State(I_ManDisch)&&!I_ManDischMem)))
                        {
                        DischargeHMI = OFF;
                        I_ManDischMem = ON;
                        ManualModeStep = stp_ManualDisch;
                        SeqModeManager = stp_MANUAL_MODE;
                        break;
                        }
               
              if(VerifyStart()) 
              {
               break;
              }
             }          
                        
            
            if(SeqManDischarge == stp_DONE || ManualModeStep == stp_DONE) SeqModeManager = stp_OFF_MODE;
            break;               
                            
      case stp_PREP_MODE:
        if(SeqModeManagerMEM != SeqModeManager)
           {
            SeqModeManagerMEM = SeqModeManager;
            ChangeSMStateFlag = Execute;
            CheckOutput = Execute;
           }
         if(Fault_Type[FLT_STOP]==0)
            if(CheckLowLevel())
            {
            VarInitCycle();
            if(VarInitOffFlag != Execute)
             {
              if(CheckOutputConfig())
                 Output_ON(O_CycleInProgress);
                 if(!MP.StopWithGatesAndDischDoorOpen)SeqModeManager = stp_AUTO_MODE;//24/06/2019
                 else SeqModeManager = stp_WAIT_MODE;//24/06/2019
             } 
            }
        break;
        
      case stp_WAIT_MODE:
      if(SeqModeManagerMEM!=SeqModeManager)
      {
        StartKeyOn = ON;
        SeqModeManagerMEM = SeqModeManager;
        T_PRE[T_StopWithGatesAndDischDoorOpen] = 2; // wait for 2 sec before starting Standard Feeding Sequence 
        T_EnOn(T_StopWithGatesAndDischDoorOpen);
        if(!MP.InvertFeedAndDischOutputs)Output_ON(O_DischDoor);
        else Output_OFF(O_DischDoor);
      }
      if(T_Dn(T_StopWithGatesAndDischDoorOpen))
       {
         T_EnOff(T_StopWithGatesAndDischDoorOpen);
         if(!MP.InvertFeedAndDischOutputs)Output_OFF(O_DischDoor);
         else Output_ON(O_DischDoor);
         StartKeyOn = OFF;
         SeqModeManager = stp_AUTO_MODE;
         break;
       }
       else
         break;
      
             
      case stp_AUTO_MODE:
      
      if(SeqModeManagerMEM!=SeqModeManager)
          {
          SeqModeManagerMEM = SeqModeManager;
          Batch.BeginTime = ReadPresentDateTime();//addedby namk 26/9/2018
          ProdRemainBatch = WP.PresetBatch - Batch.Count;//added by namk 26/9/2018
          Start_PauseBtn = PauseBtn;
          KeyLockPTSZI(LAST,LAST,LAST,ON,LAST);
          StartBatch = ON; //added by namk 01/10/2018  
          if(BatchEndOnReceive)ResetBatch();
          BulkByWeightON = OFF;  
          BatchEndOnReceive = OFF;   
          if(MP.StopWithGatesAndDischDoorOpen)StartKeyOn = ON;                       
          } 

          
      if(Fault_Type[FLT_STOP]!=0) SeqModeManager = stp_STOPPING_MODE;
      if(StopHMI || (IO_Enable[I_Stop] && Input_State(I_Stop) && !I_StopMem) || BatchEnded || CleanoutWeighment)
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
            if (SeqModeManager!= mode_step)ScanMax = FillingTaskIntervalOff / 1000.0;
            if(Current_Screen != Current_ScreenMEM)
             {
             if(Current_Screen == SCREEN_AUTOMATIC) 
               OutResetFlag = Execute;
             }
           }
          else 
           {
           if (SeqModeManager!= mode_step)ScanMax = FillingTaskIntervalAuto / 1000.0;
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
--  Procedure Name    : SetFlowThroughOutputs
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/08/29
--  
--  Purpose           : This procedure will set outputs involved Flow Through mode 
--                      
--  Value Parameters  : None 
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SetFlowThroughOutputs (void)
{
  if(MC.WeighingMode == FlowThrough || FlowThroughAfterCleanOutFlag) 
  {
    Output_ON(O_DischDoor);           
    Output_ON(O_BulkFeed);
    Output_ON(O_DribbleFeed);
    Output_ON(O_Aspiration);  
  }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ResetFlowThroughOutputs
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/08/29
--  
--  Purpose           : This procedure will reset outputs involved Flow Through mode 
--                      
--  Value Parameters  : None 
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void ResetFlowThroughOutputs (void)
{
  if(MC.WeighingMode == FlowThrough || FlowThroughAfterCleanOutFlag) //Make sure only Flow Through Mode 
  {
   Output_OFF(O_DischDoor);           
   Output_OFF(O_BulkFeed);
   Output_OFF(O_DribbleFeed);
   Output_OFF(O_Aspiration); 
  }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_FlowThroughMode
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/20
--  
--  Purpose           : This procedure will set outputs involved Flow Through mode 
--                      
--  Value Parameters  : None 
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SEQ_FlowThroughMode (void)
{
  
 if(MC.WeighingMode == FlowThrough || FlowThroughAfterCleanOutFlag)
 switch(SeqFlowThrough)
 {
   case stp_InitFlowThrough:
        if(SeqFlowThroughMEM != SeqFlowThrough)
        { 
          SeqFlowThroughMEM = SeqFlowThrough;
          FlowThroughGraphCnt = 0;
          RefreshAutoScreenReq();
          ResetFlowThroughOutputs();
          MessageDisplay(lsub(TX_MSGFLOWTHROUGHREADY),Step_Message);
        }
        if((SeqModeManager == stp_AUTO_MODE || StartHMI || (IO_Enable[I_Start] && Input_State(I_Start))) || FlowThroughAfterCleanOutFlag) SeqFlowThrough = stp_StartedFlowThrough;
        break;
        
   case stp_StartedFlowThrough:
        if(SeqFlowThroughMEM != SeqFlowThrough) 
        {
          SeqFlowThroughMEM = SeqFlowThrough;
          SetFlowThroughOutputs();
          MessageDisplay(lsub(TX_MSGFLOWTHROUGHSTART),Step_Message);
          MessageDisplay(lsub(TX_MSGFLOWTHROUGHRUNNING),Step_Message);
          if(!T_EN[T_FlowThroughTime]) T_EnOn(T_FlowThroughTime); 
        }
        if(SeqModeManager == stp_STOP_MODE || SeqModeManager == stp_STOPPING_MODE || StopHMI || (IO_Enable[I_Stop] && Input_State(I_Stop))) 
        {
          SeqFlowThrough = stp_StoppedFlowThrough;
          break;
        }
          
        if(AutoPause || PauseHMI || (IO_Enable[I_HoldCycle] && Input_State(I_HoldCycle) && !HoldCycleMem)) 
        {
          SeqFlowThrough = stp_PausedFlowThrough;
          break;
        }
          
        if(T_Dn(T_FlowThroughTime))
        {
          FlowThroughGraphCnt++;
          T_EnOff(T_FlowThroughTime);
          if(FlowThroughGraphCnt > 10) FlowThroughGraphCnt = 0;
          RefreshAutoScreenReq();
          mode_step = stp_AUTO_MODE;
          T_EnOn(T_FlowThroughTime);
        }
        break;
        
   case stp_PausedFlowThrough:
        if(SeqFlowThroughMEM != SeqFlowThrough) 
        {
        SeqFlowThroughMEM = SeqFlowThrough;
        MessageDisplay(lsub(TX_MSGFLOWTHROUGHPAUSE),Step_Message);
        SeqModeManager = stp_STOPPING_MODE;
        ResetFlowThroughOutputs();
        T_EnOff(T_FlowThroughTime);
        }
        
        if(!AutoPause && !InPauseDone)
        {
          SeqFlowThrough = stp_StartedFlowThrough;
          SeqModeManager = stp_AUTO_MODE;
        }
        break;
        
   case stp_StoppedFlowThrough:
        if(SeqFlowThroughMEM != SeqFlowThrough) 
        {
          SeqFlowThroughMEM = SeqFlowThrough;
          FlowThroughGraphCnt = 0;
          RefreshAutoScreenReq();
          ResetFlowThroughOutputs();
          MessageDisplay(lsub(TX_MSGFLOWTHROUGHSTOP),Step_Message);
          SeqModeManager = stp_STOP_MODE; 
          if(BulkByWeightON)
          {
             FlowThroughAfterCleanOutFlag = OFF;
             SeqMaster = stp_INIT;
             ProdRemainWeight = 0;
          }
        }
      
        if(SeqModeManager == stp_AUTO_MODE || StartHMI|| (IO_Enable[I_Start] && Input_State(I_Start)))
        { 
          SeqFlowThrough = stp_StartedFlowThrough;    
        }
        break;
 }
 if(OffHMI || SeqModeManager == stp_OFF_MODE ) SeqFlowThrough = stp_InitFlowThrough;
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : TargetWeightControlON
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/20
--  
--  Purpose           : This procedure will handle target weight control  
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
bool TargetWeightControlON(void)
{
bool result;
  if((MC.WeighingMode == Batching && WP.PresetBatch == 0) || (MC.WeighingMode == Bulk && WP.BulkModeIP == Ship)
  && (SeqBatchingMode == stp_LastTwoWeighment || SeqBatchingMode == stp_SpecialWeightment))
  {
    result = ON;
  }
  else 
  {
    result = OFF;
  }
  return result;
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ResetSubModeFlag
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/10/30
--  
--  Purpose           : This procedure will reset sub mode of batch and bulk modes  
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void ResetSubModeFlag (void)
{
  if(BatchByDischON)BatchByDischON  = OFF;
  if(BatchByWeightON)BatchByWeightON = OFF;
  if(BulkByDischON)BulkByDischON  = OFF;
  if(BulkByWeightON)BulkByWeightON = OFF;

}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckSubModeFlag
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/20
--  
--  Purpose           : This procedure will check sub mode of batch and bulk modes  
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckSubModeFlag(void)
{
  if(MC.WeighingMode == Batching || MC.WeighingMode == Bulk)
  {
   if(MC.WeighingMode == Batching)
    {
     if(WP.PresetBatch > 0)
     {
      if(!BatchByDischON)BatchByDischON  = ON;
      if(BatchByWeightON)BatchByWeightON = OFF;
     }
     else if(WP.PresetBatch == 0 && WP.TargetWeightIP > 0)
     {
      if(BatchByDischON)BatchByDischON  = OFF;
      if(!BatchByWeightON)BatchByWeightON = ON;
      if(!BulkByWeightON)BulkByWeightON = ON;
      
     }
     else
     {
      BatchByDischON  = OFF;
      BatchByWeightON = OFF;
     }
     if(BulkByDischON)BulkByDischON  = OFF;
     if(BulkByWeightON)BulkByWeightON = OFF;//uncomented 05/02/2019
    }
  
    else if(MC.WeighingMode == Bulk)
    {
     if((WP.BulkModeIP == Ship && WP.PresetBatch > 0) || (WP.BulkModeIP == Receive && WP.PresetBatch == 0))
     {
      if(!BulkByDischON)BulkByDischON  = ON;
      if(BulkByWeightON)BulkByWeightON = OFF;
     }
     else if((WP.BulkModeIP == Ship && WP.PresetBatch == 0 && WP.TargetWeightIP > 0) || (WP.TransferSilo == YES && ProdSiloNoWeight[WP.SiloNo] < WP.TargetWeightIP && ProdSiloNoWeight[WP.SiloNo] > 0))
     {
      if(BulkByDischON)BulkByDischON  = OFF;
      if(!BulkByWeightON)BulkByWeightON = ON;
     }
     else
     {
      if(BulkByDischON)BulkByDischON  = OFF;
      if(BulkByWeightON)BulkByWeightON = OFF;
     }
     
      if(BatchByDischON)BatchByDischON  = OFF;
      if(BatchByWeightON)BatchByWeightON = OFF;
    }
  }   
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckFlowThroughAfterCleanOut
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/28
--  
--  Purpose           : This procedure will check to switch mode    
--                      to flow through after cleanout
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckFlowThroughAfterCleanOut(void)
{
  if(MC.WeighingMode == Bulk && WP.BulkModeIP == Ship && WP.FlowThroughAfterCleanout == YES 
  && CleanOutWeightDone && !FlowThroughAfterCleanOutFlag)
  {
    FlowThroughAfterCleanOutFlag = ON;
  }
  else
  {
    if(WP.FlowThroughAfterCleanout == NO)FlowThroughAfterCleanOutFlag = OFF;
  }
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckCleanOutWeight
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/28
--  
--  Purpose           : This procedure will check clean out weight reachs   
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckCleanOutWeight(void)
{
    switch(SeqCleanOutWeight)
    {
    case stp_InitCleanOutWeight:
         if(SeqCleanOutWeightMEM != SeqCleanOutWeight)
         {
           SeqCleanOutWeightMEM = SeqCleanOutWeight;
           if(IO_Enable[O_CleanOutWeight] && IO_State[O_CleanOutWeight])Output_OFF(O_CleanOutWeight);
           CleanOutWeightDone = OFF;
         } 
         
         if(!BatchEnded && StartBatch && !SlowCycleOccured && !LowLevel[Scale1])
         {
            SeqCleanOutWeight = stp_CheckCleanOutWeight;    
         }         
         break;
         
    case stp_CheckCleanOutWeight:
         if(SeqCleanOutWeightMEM != SeqCleanOutWeight)
         {
           SeqCleanOutWeightMEM = SeqCleanOutWeight;
           if(IO_Enable[O_CleanOutWeight] && !IO_State[O_CleanOutWeight])Output_ON(O_CleanOutWeight);
         }
         if(ProdRemainWeight > 0 && ProdRemainWeight <= WP.CleanOutWeightIP && !CleanOutWeightDone && SeqModeManager == stp_AUTO_MODE) 
         {
           SeqCleanOutWeight = stp_StartCleanOutWeight;
         }
         if(SlowCycleOccured || BatchEnded) SeqCleanOutWeight = stp_StartCleanOutWeight;
         break;
    
    case stp_StartCleanOutWeight:
         if(SeqCleanOutWeightMEM != SeqCleanOutWeight)
         {
           SeqCleanOutWeightMEM = SeqCleanOutWeight;
           MessageDisplay(lsub(TX_MSGCLEANOUTWEIGHT),Step_Message);
           CleanOutWeightDone = ON;
           if(IO_Enable[O_CleanOutWeight] && IO_State[O_CleanOutWeight])Output_OFF(O_CleanOutWeight);
           //CheckFlowThroughAfterCleanOut();
         } 
         
         if(SlowCycleOccured || BatchEnded)
         {
           SeqCleanOutWeight = stp_InitCleanOutWeight;
         }
         break;
    } 
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckPulseTotalWeight
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/28
--  
--  Purpose           : This procedure will check pulse total weight reachs   
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void CheckPulseTotalWeight(void)
{   
  decimal TotalWeightPulseTemp%10.2;
  
  switch (SeqPulseTotalWeight)
  {
    case stp_InitPTW:
         if(SeqPulseTotalWeightMEM != SeqPulseTotalWeight)
         {
           SeqPulseTotalWeightMEM = SeqPulseTotalWeight;
           NumOfPulse = 0;
           if(IO_Enable[O_PulseTotalWeight] && IO_State[O_PulseTotalWeight])Output_OFF(O_PulseTotalWeight);
           T_EnOff(T_PulseTotalWeight);
         }
         
         if(TotalWeightPulseTemp != ProdTotalWeightLT[Scale1])
         {
           TotalWeightPulseTemp = ProdTotalWeightLT[Scale1];
           AccPulseTotalWeight = ProdTotalWeightLT[Scale1]-LastPulseTotalWeight+PulseTotalWeightRemain;
         }
         if(AccPulseTotalWeight > 0 && AccPulseTotalWeight >= WP.PulseTotalWeight)
         {
           NumOfPulse = AccPulseTotalWeight/WP.PulseTotalWeight;
           PulseTotalWeightRemain = AccPulseTotalWeight-(NumOfPulse*WP.PulseTotalWeight);
           SeqPulseTotalWeight = stp_StartPTW;
         }
         
         break;
    
    case stp_StartPTW:
         if(SeqPulseTotalWeightMEM != SeqPulseTotalWeight)
         {
           SeqPulseTotalWeightMEM = SeqPulseTotalWeight;
           if(IO_Enable[O_PulseTotalWeight] && !IO_State[O_PulseTotalWeight])Output_ON(O_PulseTotalWeight);
           T_EnOn(T_PulseTotalWeight);
         }
         if(T_Dn(T_PulseTotalWeight))
         {
           NumOfPulse --;
           if(NumOfPulse <= 0)
           {
             SeqPulseTotalWeight = stp_StopPTW;
           }
           else if(NumOfPulse > 0)
           {
             SeqPulseTotalWeight = stp_ContinueGenPTW;
           }
         }    
         
         break;
         
    case stp_ContinueGenPTW:
         if(SeqPulseTotalWeightMEM != SeqPulseTotalWeight)
         {
           SeqPulseTotalWeightMEM = SeqPulseTotalWeight;
           if(IO_Enable[O_PulseTotalWeight] && IO_State[O_PulseTotalWeight])Output_OFF(O_PulseTotalWeight);
           T_EnOff(T_PulseTotalWeight);
           T_EnOn(T_PulseTotalWeight);
         }
         if(T_Dn(T_PulseTotalWeight))
         {
           SeqPulseTotalWeight = stp_StartPTW;
           T_EnOff(T_PulseTotalWeight);
         }
         
         break;
    
    case stp_StopPTW:
         if(SeqPulseTotalWeightMEM != SeqPulseTotalWeight)
         {
           SeqPulseTotalWeightMEM = SeqPulseTotalWeight;
           LastPulseTotalWeight = ProdTotalWeightLT[Scale1];  
           AccPulseTotalWeight = 0;
           SeqPulseTotalWeight = stp_InitPTW;
         }
         break;
  }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_ControlTargetWeight
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/20
--  
--  Purpose           : This procedure will handle Batching mode  
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SEQ_ControlTargetWeight(void)
{ 
   bool FirstScanON;
   
   switch(SeqBatchingMode)
   {       
        case stp_InitWeighment:
             if(SeqBatchingModeMEM != SeqBatchingMode)
             {
               SeqBatchingModeMEM = SeqBatchingMode;
               ToleranceCheckOFF = OFF;
               OffModeOn = OFF;
               InLast2Weighments = OFF;
               RefreshAutoScreenReq();
             }
             //transfer all remainder in silo source
             if(WP.TargetWeightIP <= 0 && BulkByWeightON && WP.TransferSilo == YES)WP.TargetWeightIP = ProdSiloNoWeight[WP.SiloNo]; 
             //re-calculated if related values are changed 
             if(WP.NominalWeight != nominalweighttemp || dtftemp != WP.DTF || targetweightiptemp != WP.TargetWeightIP)
             {
               nominalweighttemp = WP.NominalWeight;
               targetweightiptemp = WP.TargetWeightIP;
               dtftemp = WP.DTF;
               DTFWeight = (WP.DTF/100)*WP.TargetWeightIP;
               ProdRemainWeightCheck = 0;
               if(FirstScanON)ResetBatch();
               FirstScanON = ON;
             }
             
             if(!BatchEndDone)
             {
               if(Batch.TotalWeight <= (WP.TargetWeightIP+DTFWeight))
               {
               ProdRemainWeightCheck = (WP.TargetWeightIP+DTFWeight)-Batch.TotalWeight;
               }
               if(ProdRemainWeightCheck == 0)ResetBatch();
             }
             else 
             {
               ProdRemainWeightCheck = WP.TargetWeightIP+DTFWeight; 
             }
 
             if(SeqModeManager == stp_OFF_MODE || SeqModeManager == stp_STOP_MODE || SeqModeManager == stp_STOPPING_MODE)
             {
               if(ProdRemainWeightCheck > 0)NumOfUnit =  ProdRemainWeightCheck/WP.NominalWeight;
               if(NumOfUnit >= 2)NumOfRegUnit =  NumOfUnit-1;
             }
             
             if(NumOfUnit <= 0)
             {
               if(!SpecialWeighmentReq)SpecialWeighmentReq = ON;//monitor purpose flag
               if(LastTwoWeighmentReq)LastTwoWeighmentReq = OFF;//monitor purpose flag
               if(RegularWeighmentReq)RegularWeighmentReq = OFF;//monitor purpose flag
               if(!DribbleFeedOnly)DribbleFeedOnly = ON;
               if(!ToleranceCheckOFF)ToleranceCheckOFF = ON;
               if(!InLast2Weighments)InLast2Weighments = ON;
               CutoffTemp = ProdRemainWeightCheck-(WP.NominalWeight-WP.Cutoff);
               TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
               if(StartBatch)
               {
                 if(BatchEndDone)
                 {
                 ResetBatch();
                 BatchEndDone = OFF;
                 ProdRemainWeight = (WP.TargetWeightIP+DTFWeight)- Batch.TotalWeight;
                 }
                SeqBatchingMode = stp_SpecialWeightment;
               }
             }
             else if(NumOfUnit == 1)
             {
               if(SpecialWeighmentReq)SpecialWeighmentReq = OFF;//monitor purpose flag
               if(!LastTwoWeighmentReq)LastTwoWeighmentReq = ON;//monitor purpose flag
               if(RegularWeighmentReq)RegularWeighmentReq = OFF;//monitor purpose flag
               if(!DribbleFeedOnly)DribbleFeedOnly = ON;
               if(!ToleranceCheckOFF)ToleranceCheckOFF = ON;
               if(!InLast2Weighments)InLast2Weighments = ON;
               CutoffTemp = ((ProdRemainWeightCheck/2)-(WP.NominalWeight-WP.Cutoff));  
               TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
               if(StartBatch)
               {
                 if(BatchEndDone)
                 {
                 ResetBatch();
                 BatchEndDone = OFF;
                 ProdRemainWeight = (WP.TargetWeightIP+DTFWeight)- Batch.TotalWeight; 
                 }
                 SeqBatchingMode = stp_LastTwoWeighment;
               }
             }
             else if(NumOfUnit >= 2)
             {
               if(SpecialWeighmentReq)SpecialWeighmentReq = OFF;//monitor purpose flag
               if(LastTwoWeighmentReq)LastTwoWeighmentReq = OFF;//monitor purpose flag
               if(!RegularWeighmentReq)RegularWeighmentReq = ON;//monitor purpose flag
               if(DribbleFeedOnly)DribbleFeedOnly = OFF;
               CutoffTemp = WP.Cutoff;  
               TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
               if(StartBatch)
               {
                 if(BatchEndDone)
                 {
                 ResetBatch();
                 BatchEndDone = OFF;
                 ProdRemainWeight = (WP.TargetWeightIP+DTFWeight)- Batch.TotalWeight;
                 }
                 SeqBatchingMode = stp_RegularWeighment;
               }
             }
             if(WP.CleanOutWeightIP > 0)CheckCleanOutWeight();//added 06/03/2019
             break;
        
        case stp_RegularWeighment:
             if(SeqBatchingModeMEM != SeqBatchingMode)
             {
               SeqBatchingModeMEM = SeqBatchingMode;
               DribbleFeedOnly = OFF;
               Batch.BeginTime = ReadPresentDateTime();
               NumOfUnit =  ProdRemainWeightCheck/WP.NominalWeight;
               if(NumOfUnit >= 2)NumOfRegUnit =  NumOfUnit-1;
             }
             if(TotalWeightBatchTemp != Batch.TotalWeight)
             {
               TotalWeightBatchTemp = Batch.TotalWeight;
               CheckedWeightTemp = CheckedWeight[Scale1];//added 21/02/2019
               if(Batch.UnitsDone == NumOfRegUnit)
               {
                 SeqBatchingMode = stp_LastTwoWeighment;
               }               
             }
            if(WP.CleanOutWeightIP > 0)CheckCleanOutWeight();
            //Check batch ended added 04/02/19
            if(BatchCancelled || BatchEnded)
            {
              SeqBatchingMode = stp_BatchEnded;
            }
            
            break;
        break;
        
        case stp_LastTwoWeighment:
             if(SeqBatchingModeMEM != SeqBatchingMode)
             {
               SeqBatchingModeMEM = SeqBatchingMode;
               DribbleFeedOnly = ON;
               InLast2Weighments = ON;
               ToleranceCheckOFF = ON;
               SampleOn = ON;
               ProdRemainWeightCheck = (WP.TargetWeightIP+DTFWeight)-Batch.TotalWeight;
               CutoffTemp = ((ProdRemainWeightCheck+DTFWeight)/2)-(WP.NominalWeight-WP.Cutoff);  
               TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
               RefreshAutoScreenReq();
             }
             if(Weighment2LastCnt <= 0)TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
             if(TotalWeightBatchTemp != Batch.TotalWeight)
             {
               TotalWeightBatchTemp = Batch.TotalWeight;
               Weighment2LastCnt++;
               if(Weighment2LastCnt == 1)
               {
                 CutoffTemp = (WP.TargetWeightIP+DTFWeight-Batch.TotalWeight)-(WP.NominalWeight-WP.Cutoff);
                 TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff); 
               }
               if(Weighment2LastCnt == 2 && !FlowThroughAfterCleanOutFlag)
               {
                 SeqBatchingMode = stp_BatchEnded;
               }
             }
             
             if(WP.CleanOutWeightIP > 0)CheckCleanOutWeight();
             
             //Check batch ended added 04/02/19
             if(BatchCancelled || BatchEnded)
             {
               SeqBatchingMode = stp_BatchEnded;
             }
             break;
        
        case stp_SpecialWeightment:
             if(SeqBatchingModeMEM != SeqBatchingMode)
             {
               SeqBatchingModeMEM = SeqBatchingMode;
               DribbleFeedOnly = ON;
               Batch.BeginTime = ReadPresentDateTime();
               ToleranceCheckOFF = ON;
               SampleOn = ON; 
               TotalWeightBatchTemp = Batch.TotalWeight;  
               CutoffTemp = ProdRemainWeightCheck-(WP.NominalWeight-WP.Cutoff);
               TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
               RefreshAutoScreenReq();
             }
             
             if(TotalWeightBatchTemp != Batch.TotalWeight)
             {
               TotalWeightBatchTemp = Batch.TotalWeight;
               SeqBatchingMode = stp_BatchEnded;
             }
             
             if(WP.CleanOutWeightIP > 0)CheckCleanOutWeight();
             
             //Check batch ended added 04/02/19
             if(BatchCancelled || BatchEnded)
             {
               SeqBatchingMode = stp_BatchEnded;
             }
             break;
        
        case stp_BatchEnded:
             if(SeqBatchingModeMEM != SeqBatchingMode)
             {
               SeqBatchingModeMEM = SeqBatchingMode;
               StartBatch = OFF;
               BatchEnded = ON;
               BatchEndReq = OFF;
               BatchCancelled = OFF;
               Output_ON(O_BatchEnded);
               SampleOn = OFF;
               ToleranceCheckOFF = OFF;
               TotalWeightBatchTemp = 0;
               Weighment2LastCnt = 0;
               CutoffTemp = WP.Cutoff;
               TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);
               DribbleFeedOnly = OFF;
               BatchEndDone = ON;
               RefreshAutoScreenReq();
               CheckedWeight[Scale1] = CheckedWeightTemp;//added 21/02/2019
               SeqBatchingMode = stp_InitWeighment;
             }
             if(WP.CleanOutWeightIP > 0)CheckCleanOutWeight();//added 06/03/2019      
             break;
   }
   
   if((SeqModeManager == stp_STOP_MODE && TargetWeightIPTemp != WP.TargetWeightIP) || TargetWeightIPTemp != WP.TargetWeightIP || (SeqModeManager == stp_OFF_MODE && !OffModeOn)
          || (SeqModeManager == stp_OFF_MODE && TargetWeightIPTemp != WP.TargetWeightIP) || SeqFlowThrough == stp_StoppedFlowThrough)
   {
          OffModeOn = ON;
          if(!BatchEndDone)ProdRemainWeight = (WP.TargetWeightIP+DTFWeight)- Batch.TotalWeight;  
		      if(TargetWeightIPTemp != WP.TargetWeightIP)
		      {
			     TargetWeightIPTemp = WP.TargetWeightIP;
			     SeqBatchingMode = stp_InitWeighment;
		      }
          SeqFlowThrough = stp_InitFlowThrough;
          RefreshAutoScreenReq();
   }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_ControlBatchPreset
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/10/31
--  
--  Purpose           : This procedure will handle batch preset  
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SEQ_ControlBatchPreset (void)
{
  switch(SeqBatchPreset)
  {
   case stp_InitBatchPreset:
        if(SeqBatchPresetMEM != SeqBatchPreset)
        {
          SeqBatchPresetMEM = SeqBatchPreset;
          RefreshAutoScreenReq();
        }
        
        if(StartBatch && !BatchCancelled)
        {
          if(BatchEndDone)
          {
            ResetBatch();
            BatchEndDone = OFF;
            ProdRemainBatch = Batch.Preset;
          }
          else
          {
            ProdRemainBatch = Batch.Preset- Batch.Count; 
          }
         SeqBatchPreset = stp_StartBatchPreset;
        }      
        break;
   
   case stp_StartBatchPreset:
        if(SeqBatchPresetMEM != SeqBatchPreset)
        {
          SeqBatchPresetMEM = SeqBatchPreset;
          RefreshAutoScreenReq();
        }
        if(Batch.Count >= Batch.Preset || BatchCancelled || BatchEnded)
        {
          SeqBatchPreset = stp_EndBatchPreset;
        }          
        break;
   
   case stp_EndBatchPreset:
        if(SeqBatchPresetMEM != SeqBatchPreset)
        {
          SeqBatchPresetMEM = SeqBatchPreset;
          Output_ON(O_BatchEnded);
          StartBatch = OFF;
          BatchEndDone = ON;         
          BatchEnded = ON;
          BatchEndReq = OFF;
          BatchCancelled = OFF;  
          SeqBatchPreset = stp_InitBatchPreset;
          RefreshAutoScreenReq();
        } 
        break;
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
int i,RemainBatchTemp; //added by namk 26/9/2018
bool MsgDownStreamSent,MsgWaitPauseSent;
if(SeqModeManager == stp_OFF_MODE) SeqMaster = stp_INIT;
if(IO_Enable[I_ResetOutofTolAlarm]&&!Input_State(I_ResetOutofTolAlarm))I_ResetOutofTolAlarmMem=OFF;
if(SeqModeManager == stp_OFF_MODE && IO_Enable[I_TotalReset] && Input_State(I_TotalReset))
{
  ProdTotalWeight[Scale1] = 0;
  RefreshAutoScreenReq();
}
if(MC.WeighingMode == Bulk || MC.WeighingMode == Batching)//added by namk 24/9/2018
{
 if(Input_State(I_BatchEnd)&& IO_Enable[I_BatchEnd] && AutoMode && (Batch.Preset > 0 || WP.TargetWeightIP > 0))
 { 
   BatchEndReq = ON; //added by namk 20/9/2018
 }
}
if(SeqModeManager == stp_OFF_MODE)
{
ResetDataModeChangeData();
}

//Check select preset feed rate select from remote input 12/03/2019
if(IO_Enable[I_PresetFeedRate2]&& Input_State(I_PresetFeedRate2))
  ProdPresetFeedRate = WP.PresetFeedRate2;  
else 
  ProdPresetFeedRate = WP.PresetFeedRate1;

SeqMasterNext = SeqMaster;
switch (SeqMaster)
 {
  case stp_INIT:
            if(SeqMasterMEM != SeqMaster)
                {
                SeqMasterMEM = SeqMaster;
                if(SeqModeManager != stp_OFF_MODE) MessageDisplay(lsub(TX_MSGBLANK),Step_Message);
                if(FeedInProcess) WeighmentAborted = ON;
                VarInitCycle();
                EmptyCheckedWeight = NetWeight[Scale1];
                STR_TimeStampEmpty = concat(time);
                RefreshAutoScreenReq();
                }
          if(MC.WeighingMode == FlowThrough || FlowThroughAfterCleanOutFlag)SeqMaster = stp_FLOWTHROUGH;//added by namk 20/9/2018 
          if((SeqModeManager==stp_AUTO_MODE || (SeqModeManager==stp_STOPPING_MODE && WeighPerUnitAcc < WP.WeighmentsPerUnit)) && !CleanoutWeighment)
          {
           if(!T_EN[T_CycleDuration]) T_EnOn(T_CycleDuration); 
           if(!T_EN[T_TickEvery1Sec]) T_EnOn(T_TickEvery1Sec); //added by namk 14/9/2018
           FeedRateCalTime =1;//added by namk 14/9/2018
           
            if((Batch.Preset > 0)  && (Batch.Count >= Batch.Preset || BatchCancelled) && (MC.WeighingMode == Bulk || MC.WeighingMode == Batching)) //added by namk 24/9/2018
            {
              BatchEnded = ON;
              BatchEndReq = OFF;
              BatchCancelled = OFF;
              Output_ON(O_BatchEnded);
            }
           else
            {
            if(FirstWeighment && NetWeight[Scale1] > (MaxWeight[Scale1] * ZeroLimit)){SeqMaster = stp_SAMPLE;break;}
            if ((ZeroFreqCnt == 0 || (WP.FeedAlgoType != FeediQSim && (LowLevel[Scale1] || EmptyHopper)))&& !AutoZeroOff && !WP.ZeroingOpen)
               {
                if((IO_Enable[I_DischDoorClose] && Input_State(I_DischDoorClose))|| !IO_Enable[I_DischDoorClose])
                  {
                   T_EnOff(T_FeedDelayTime);
                   SetZeroStatus[Scale1]=-1;
                   if(CheckLowLevel())
                    SeqMaster = stp_ZERO;
                  }
               }   
            else if(!T_EN[T_FeedDelayTime]||(T_Dn(T_FeedDelayTime)&&T_EN[T_FeedDelayTime]))
             {
              T_EnOff(T_FeedDelayTime);
              if(CheckLowLevel())
              {
               if(NetWeight[Scale1] < (0.8*TargetWeight[Scale1]))
                {
                 SeqMaster = stp_FEED;
                }
               else
                {
                 SystemErrorCode = "601 Weighment not discharged";
                } 
              }
             }
            }
          } 
          break;
            
  case stp_ZERO:
            if(SeqMasterMEM != SeqMaster) 
             {
              SeqMasterMEM = SeqMaster;
             }     
            
            if(SetZeroStatus[Scale1] != 0)
            {
             if(!IsSettled[Scale1])
                {
                  MessageDisplay(lsub(TX_MSGSTABILIZATION),Step_Message);                
                  if(SeqMasterMEM != SeqMaster ||(!T_EN[T_StabTimeLimit]&&!FaultState(FltS_StabTooLong))) {T_EnOn(T_StabTimeLimit);}  
                  else 
                   {
                    if(T_Dn(T_StabTimeLimit)) 
                     {
                      FaultHandler(FltS_StabTooLong,""); 
                      T_EnOff(T_StabTimeLimit);
                      if(!WP.ZeroingOpen)SeqMaster = stp_INIT;
                     }
                   }
                  break;
                }
             else 
               {
                  T_EnOff(T_StabTimeLimit);
                  if(FaultState(FltS_StabTooLong))FaultResetReq();
                  if(WP.FeedAlgoType == FeediQSim) 
                   {
                    iQSimSetWeight(SCALE_CHANNEL, SCALE_NUMBER,0.0);
                    SetZeroStatus[Scale1] = 0;
                   } 
                  else
                   {
                    if(abs(NetWeight[Scale1]) <= (MaxWeight[Scale1] * ZeroLimit)&& SetZeroStatus[Scale1]==-1) SetZeroStatus[Scale1] = setzero(Scale1Adm);
                    else SetZeroStatus[Scale1] = 99;
                   }
               }  
              
            } 
             switch (SetZeroStatus[Scale1]) 
                    {
                    case 99:if(!FaultState(FltS_ZeroOutOfRange))
                             { 
                              FaultHandler(FltS_ZeroOutOfRange,"");
                              if(!WP.ZeroingOpen)SeqMaster = stp_INIT;
                             }
                             SetZeroStatus[Scale1]=-1; 
                             break;
                    case 0: 
                         {
                         if(FaultState(FltS_ZeroOutOfRange))FaultResetReq();
                         MessageDisplay(lsub(TX_MSGZERODONE),Step_Message);
                         WeighmentInPan = OFF;
                         if(WP.WeighmentsPerUnit == 1) 
                           Discharged();
                         if(!WP.ZeroingOpen) 
                          {
                           if(CheckLowLevel())
                            SeqMaster = stp_FEED;
                          }  
                         if(WP.ZeroingOpen)  SeqMaster = stp_DISCHARGING;
                         break;
                         }                                    
                    default:
                          MessageDisplay(concat(lsub(TX_MSGSYSTEMWARNING),100 + SetZeroStatus[Scale1]),Step_Message);
                          SetZeroStatus[Scale1]=-1;
                          break;
                    }
             

             
  case stp_FEED:
            if(SeqMasterMEM != SeqMaster) 
            {
            SeqMasterMEM = SeqMaster;
            MessageDisplay(lsub(TX_MSGFEEDING),Step_Message);
            FeedInProcess = ON;
            ZeroFreqCnt++;
            
            //Units Per Minute Calculation
            if(WeighPerUnitAcc == 0)
             {
              if(T_EN[T_UPMDuration])
               {
                ProdCycleUnitsPerMin[Scale1] = 60/T_Acc(T_UPMDuration);
                T_EnOff(T_UPMDuration);
                RefreshAutoScreenReq();
               }
             }    
            
            if(!T_EN[T_UPMDuration])
             T_EnOn(T_UPMDuration);
            } 
             
            if(SeqFeeder == stp_FEEDDONE && !IsCleanoutDone)
            { 
               FeedInProcess = OFF;
               if (!FeedCycleCancelled)
                 {        
                 if((SampleFreqCnt>=0 && SampleFreqCnt<MP.SampleSize)||(WP.FeedAlgoType != FeediQSim && (LowLevel[Scale1] || EmptyHopper)) 
                    || CheckAll  || iQFeedWaitSettled || CheckOnce || AutoPause || SampleOn)//SampleOn added by namk 21/9/2018
                   {
                    if(T_Dn(T_FaultDisplay))
                     DisplayAlarmDelay = OFF;
                     
                    if(!DisplayAlarmDelay)
                     {
                      CheckOnce = OFF;
                      SampledInPause = AutoPause;
                      SeqMaster = stp_SAMPLE;
                     }
                    
                   } 
                 else 
                  {
                   if(!WeighmentInPan) 
                    {
                     WeighPerUnit();
                     WeighingDataRefreshFlag = ON;
                    } 
                   SeqMaster = stp_RDYTODISCH;
                  } 
                 }
             else  SeqMaster = stp_INIT;
            }       
            
            break;
            
  case stp_SAMPLE:
            if(SeqMasterMEM != SeqMaster) SeqMasterMEM = SeqMaster;      
            if(!IsSettled[Scale1])
                  {
                  MessageDisplay(lsub(TX_MSGSTABILIZATION),Step_Message);                
                  if(SeqMasterMEM != SeqMaster ||(!T_EN[T_StabTimeLimit]&&!FaultState(FltS_StabTooLong))) {T_EnOn(T_StabTimeLimit);}  
                  else {if(T_Dn(T_StabTimeLimit)) {FaultHandler(FltS_StabTooLong,""); T_EnOff(T_StabTimeLimit);}}
                  break;
                  }
            else 
            {
            T_EnOff(T_StabTimeLimit);
            if(FaultState(FltS_StabTooLong))FaultResetReq();
            CheckedWeight[Scale1] = NetWeight[Scale1];
            WeightSampled[Scale1]=ON;
            if(WP.FeedAlgoType != FeediQSim && !SlowCycleOccured) 
             if(CheckedWeight[Scale1] < WP.UnderWeight && WP.TopUpONTime > 0 && !InLast2Weighments) //added && !InLast2Weighments 3/04/2019
              {
               SeqMaster = stp_TOPUP;
               break;
              }
              
            if(!WeighmentInPan)WeighPerUnit();
          if(!ToleranceCheckOFF && NoCheckTolAnyMore) //added by namk 21/9/2018 // NoCheckTolAnyMore requested by Paul
          {//added by namk 21/9/2018
            if(((CheckedWeight[Scale1] < WP.UnderWeight || CheckedWeight[Scale1] > WP.OverWeight) && !WeighPerUnitCorrUsed) ||
              (WeighPerUnitSum < (WP.UnderWeight*WP.WeighmentsPerUnit) || WeighPerUnitSum > (WP.OverWeight*WP.WeighmentsPerUnit))&&(WeighPerUnitCorrUsed && WeighPerUnitDone))
             { 
              ZeroFreqCnt = 0;
              SampleFreqCnt = 0;
              SeqMaster = stp_OUTOFTOL;
              break;
             } 
             else 
             {
             if(!WeighmentInPan) WeighingDataRefreshFlag = ON;
             SeqMaster = stp_RDYTODISCH;
             }
          }//added by namk 21/9/2018
          else//added by namk 21/9/2018
          {//added by namk 21/9/2018
            if(!WeighmentInPan) WeighingDataRefreshFlag = ON;//added by namk 21/9/2018
            SeqMaster = stp_RDYTODISCH;//added by namk 21/9/2018
          }//added by namk 21/9/2018
            break;
            }
            
  case stp_TOPUP:
            if(SeqMasterMEM != SeqMaster) 
             {
              SeqMasterMEM = SeqMaster;
              MessageDisplay(lsub(TX_MSGFEEDTOPUP),Step_Message);
              if(WP.FeedAlgoType != FeedStd)
               {
                InitStandardFeed(OFF);
               }
              
            
             }
            if(NetWeight[Scale1] < TargetWeight[Scale1] && !SlowCycleOccured)//if(NetWeight[Scale1] < WP.UnderWeight && !SlowCycleOccured)
                {
                   
                  if(!T_EN[T_TopUpONTime])
                     {
                     T_EnOn(T_TopUpONTime);
                     Output_ON(O_DribbleFeed);
                     }
                  if((T_Dn(T_TopUpONTime)&&!T_EN[T_TopUpOFFTime]))
                     {
                     T_EnOn(T_TopUpOFFTime);
                     Output_OFF(O_DribbleFeed);
                     }
                  if(T_Dn(T_TopUpOFFTime))
                     {
                     T_EnOff(T_TopUpONTime);
                     T_EnOff(T_TopUpOFFTime);
                     }
                  break;   
                }                            
            else
            {
            
             if(!SlowCycleOccured || (SlowCycleOccured && !DisplayAlarmDelay))
             {
              T_EnOff(T_TopUpONTime);
              T_EnOff(T_TopUpOFFTime);
              Output_OFF(O_DribbleFeed);
              InitiQSmart = ON;
              InitiQFlash = ON;
             }
                     
             if(SlowCycleOccured && !DisplayAlarmDelay) 
              DisplayAlarmDelay = ON;
             if(T_Dn(T_FaultDisplay))
              DisplayAlarmDelay = OFF;
            
             if(!DisplayAlarmDelay)
              {
               SeqMaster = stp_SAMPLE;
              }
             
             break;
            }
            
  case stp_OUTOFTOL:
          
                    
          if(SeqMasterMEM != SeqMaster || (!FaultState(FltB_UnderWeight) && !FaultState(FltB_OverWeight)&& !CleanoutWeighment))
          {    
                     
              if(MP.OutOfTolTime > 0) T_EnOn(T_OutOfTolTime);
              if(((CheckedWeight[Scale1] < WP.UnderWeight) && !WeighPerUnitCorrUsed) ||
              (WeighPerUnitSum < (WP.UnderWeight*WP.WeighmentsPerUnit))&&(WeighPerUnitCorrUsed && WeighPerUnitDone))
              {
                 if(!FaultState(FltB_UnderWeight)&& !CleanoutWeighment) FaultHandler(FltB_UnderWeight,"");
                 if(SeqMasterMEM != SeqMaster)
                 {
                   if(!CleanoutWeighment)
                  {
                   Discharge_State = DischUnder;
                   Output_ON(O_UnderWeightAlarm);
                   Output_ON(O_OutOfTolerance);
                  } 
                  if(!OutOfTol[Scale1] && !WeighmentInPan)
                   {
                    if(WeighPerUnitDone) 
                     {
                      ProdUnderWeightFlag[Scale1]=ON;
                      OutOfTol[Scale1] = ON;
                     } 
                    WeighingDataRefreshFlag = ON;
                   }
                 }
              }
              if(((CheckedWeight[Scale1] > WP.OverWeight) && !WeighPerUnitCorrUsed) ||
              (WeighPerUnitSum > (WP.OverWeight*WP.WeighmentsPerUnit))&&(WeighPerUnitCorrUsed && WeighPerUnitDone))  
              {
               if(!FaultState(FltB_OverWeight)&& !CleanoutWeighment) FaultHandler(FltB_OverWeight,"");
               if(SeqMasterMEM != SeqMaster)
                 {
                  if(!CleanoutWeighment)
                  {
                   Discharge_State = DischOver;
                   Output_ON(O_OverWeightAlarm);
                   Output_ON(O_OutOfTolerance);
                  }
                  if(!OutOfTol[Scale1] && !WeighmentInPan)
                   {
                    if(WeighPerUnitDone) 
                     {
                      ProdOverWeightFlag[Scale1]=ON;
                      OutOfTol[Scale1] = ON;
                     } 
                    WeighingDataRefreshFlag = ON;
                  } 
                 }
              }
              if(SeqMasterMEM != SeqMaster) SeqMasterMEM = SeqMaster;
              break;
          }
                            
          if(DischargeHMI || CleanoutWeighment||(IO_Enable[I_ResetOutofTolAlarm]&&Input_State(I_ResetOutofTolAlarm)&&!I_ResetOutofTolAlarmMem) || T_Dn(T_OutOfTolTime)) 
          {  
            if(IO_Enable[I_ResetOutofTolAlarm]&&Input_State(I_ResetOutofTolAlarm))I_ResetOutofTolAlarmMem=ON; 
            T_EnOff(T_OutOfTolTime);
            Output_OFF(O_UnderWeightAlarm);
            Output_OFF(O_OverWeightAlarm);
            Output_OFF(O_OutOfTolerance);
            Discharge_State = DischPanOff;
            DischargeHMI=OFF;
            FaultResetReq();
            SeqMaster = stp_RDYTODISCH;
            break;
          }  
          else  break;
            
  case stp_RDYTODISCH:
            if(SeqMasterMEM != SeqMaster)
            {
            SeqMasterMEM = SeqMaster;
            MsgWaitPauseSent = OFF;
            if(Discharge_State != DischPanOff) Discharge_State = DischPanOff;
            
            if(AutoPause && SampledInPause) 
             {
              MessageDisplay(lsub(TX_MSGWAITPAUSE),Step_Message);
              MsgWaitPauseSent = ON;
             }  
            else 
             {
              MessageDisplay(lsub(TX_MSGWAITDOWNSTREAM),Step_Message);
             }
            
            if(!WeighmentInPan)
              {
                SampleFreqCnt++;
                if (SampleFreqCnt == MP.SampleSize) LastCheckedWeight[Scale1] = ON;
              }  
            WeighmentInPan = ON; 
            
            //PrintReqOnIndividual = ON; 
            
              if(MC.WeighingMode == Batching && WP.ReportType == Individual)
              {
              PrintReqOnIndividual = ON; 
              }
              else if(MC.WeighingMode == Batching && WP.ReportType == FullEmpty)
              {
              PrintReqOnFullEmpty = ON;  
              }  
              else
              {
              PrintReqOnIndividual = OFF;     
              PrintReqOnFullEmpty = OFF; 
              }
              STR_TimeStampFull = concat(time);                           
            }
            
            if(SeqModeManager==stp_AUTO_MODE||SeqModeManager==stp_STOPPING_MODE)
             {
              if(!(AutoPause && SampledInPause))
              {
               SampledInPause = OFF;
               if(IO_Enable[O_DischReady] && !IO_State[O_DischReady]) 
                 Output_ON(O_DischReady);
                if(DischReq && (!DischReqMem || SeqSpout == stp_SPOUTOKTODISCH)) //modified by namk 18/9/2018 
                //if(DischReqInputOn)//added by namk 13/03/2019
                {
                MsgDownStreamSent = OFF;
                if(WeighPerUnitDone)DischReqMem=ON;
                
                SeqMaster = stp_DISCHARGING;
                
                break;
                }
               else if(!MsgDownStreamSent) 
                       {
                       MessageDisplay(lsub(TX_MSGWAITDOWNSTREAM),Step_Message); 
                       MsgDownStreamSent = ON;
                       MsgWaitPauseSent = OFF;
                       }
              }
              else if(!MsgWaitPauseSent)
               {
                MessageDisplay(lsub(TX_MSGWAITPAUSE),Step_Message);
                MsgWaitPauseSent = ON;
                MsgDownStreamSent = OFF;
               }         
             }
           else if(MsgDownStreamSent) MsgDownStreamSent = OFF;      
               
          break;
            
  case stp_DISCHARGING:
            if(SeqMasterMEM != SeqMaster)
            {
            SeqMasterMEM = SeqMaster;
            FirstWeighment=OFF;
            Output_OFF(O_DischReady);           
            }
            
            if(SeqWeighPan == stp_CLOSEDOORS && (!T_EN[T_FeedDelayTime]|| WP.FeedDelayTime ==0)) 
            {
            OutOfTol[Scale1] = OFF;
            if(WP.FeedDelayTime != 0)T_EnOn(T_FeedDelayTime);
            feeddelaystart = systemtimer_ms();
            //SeqMaster = stp_INIT; //commented by namk
             if(MC.WeighingMode == FeedRateControl || MC.WeighingMode == TimeControl || MC.WeighingMode == Monitoring || MC.WeighingMode == Batching || MC.WeighingMode == Bulk)
             {
              SeqMaster = stp_REGULATETIME; //added by namk
             }
             
             if(FlowThroughAfterCleanOutFlag) //added by namk 25/9/2018 
             {
               SeqMaster = stp_FLOWTHROUGH;  //added by namk 25/9/2018 
             }
            }
            break; 
          
  case stp_REGULATETIME:
            if(SeqMasterMEM != SeqMaster)
            {
              SeqMasterMEM = SeqMaster;
              ProdCycleDuration[Scale1]=T_Acc(T_CycleDuration);
              
              
              
              T_EnOff(T_CycleDuration);
              if(MC.WeighingMode == FeedRateControl || MC.WeighingMode == TimeControl)
              {
                MessageDisplay(lsub(TX_MSGREGULATINGFEEDRATE),Step_Message);
              }
              if(MC.WeighingMode == FeedRateControl)
              {
                Wait4FeedTime = ((3600*CheckedWeight[Scale1])/ProdPresetFeedRate)-ProdCycleDuration[Scale1]; //Waiting Time to regulate feed rate for feed rate control mode
              }
              else if(MC.WeighingMode == TimeControl)
              {
                Wait4FeedTime = WP.PresetCycleTime-ProdCycleDuration[Scale1];////Wait Time to regulate time for time control mode
                ProdEvalFeedRate[Scale1] = (3600*TargetWeight[Scale1])/WP.PresetCycleTime;
              }
              else if(MC.WeighingMode == Monitoring || MC.WeighingMode == Bulk || MC.WeighingMode == Batching)
              {
                Wait4FeedTime = 0; //no time control for these modes
              }
              if(Wait4FeedTime < 0) Wait4FeedTime = 0; //reset Wait4FeedTime 
              if(Wait4FeedTime > 0)
              {
                T_PRE[T_RegulatedTime] = Wait4FeedTime; 
                T_EnOn(T_RegulatedTime);//start regulate time
              }  
                        
              ProdActualFeedRate[Scale1] = (3600 * CheckedWeight[Scale1])/(ProdCycleDuration[Scale1]+Wait4FeedTime);//calculate feed rate related
              RefreshAutoScreenReq();
            }
            
            if(T_Dn(T_RegulatedTime) || Wait4FeedTime <= 0)
            {
              T_EnOff(T_RegulatedTime); 
              SeqMaster = stp_INIT;            
            }
            break;
            
  case stp_FLOWTHROUGH:
            if(SeqMasterMEM != SeqMaster)
            {
             SeqMasterMEM = SeqMaster;
            }
            SEQ_FlowThroughMode();
            break;
 }
 
 //calculate feed rate 
 if(T_Dn(T_TickEvery1Sec))
 {
   if(FeedRateCalTime > ((ProdCycleDuration[Scale1]+Wait4FeedTime)*1.2))
   {
     ProdActualFeedRate[Scale1] = ProdActualFeedRate[Scale1]*(ProdCycleDuration[Scale1]+Wait4FeedTime)/FeedRateCalTime;
   }
   ProdFeedRate[Scale1] = ProdFeedRate[Scale1]+((ProdActualFeedRate[Scale1]-ProdFeedRate[Scale1])*MP.FeedRateFilterRatio);
   FeedRateCalTime++;  
   T_EnOff(T_TickEvery1Sec);
   T_EnOn(T_TickEvery1Sec);
   RefreshAutoScreenReq();
 }
 // end of calculate feed rate 
  
 //Bulk and batch mode related
 if(SeqMaster != stp_FLOWTHROUGH)//commented 5//03/2019
 if((MC.WeighingMode == Batching && WP.PresetBatch == 0) || (MC.WeighingMode == Bulk && WP.BulkModeIP == Ship))
 {
    SEQ_ControlTargetWeight();
    TargetWeightControlON();
    if(WP.PresetBatch != 0 || Batch.Preset != 0)
    {
       WP.PresetBatch = 0;
       Batch.Preset = 0;
       
    }
 }
 else 
 {
   if(DribbleFeedOnly)DribbleFeedOnly = OFF;//added by namk 1/9/2018
 }
 
 if(MC.WeighingMode == Batching && WP.PresetBatch > 0)
 {
   SEQ_ControlBatchPreset();
 }
 
 //Batch mode related 
 if(SeqModeManager == stp_OFF_MODE && MC.WeighingMode == Batching && RemainBatchTemp != WP.PresetBatch)
 {
    RemainBatchTemp = WP.PresetBatch;
    ProdRemainBatch = WP.PresetBatch;
    RefreshAutoScreenReq();
 }
 
 if(MC.WeighingMode == Bulk || MC.WeighingMode == Batching)CheckSubModeFlag(); 
 else ResetSubModeFlag();
 if(SeqModeManager != stp_OFF_MODE && WP.PulseTotalWeight > 0 )
 {
   CheckPulseTotalWeight();
 }
   
}



/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_Feeder
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : Feeder Sequence
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SEQ_Feeder(void)
{
bool FeedingStarted,Aout1On,Aout2On;
int scanmemFeeder[10],startcnt,startdelay,startdelay2;

if(SeqModeManager == stp_OFF_MODE) SeqFeeder = stp_INIT;

if(SeqMaster==stp_FEED && SeqFeeder==stp_INIT)
      { 
      switch(WP.FeedAlgoType)
        {
          case FeedStd:
                 SeqFeeder = stp_FEEDSTD;break;
          case FeediQSim:
                 SeqFeeder = stp_FEEDSTD;break;
          default:   
                 SeqFeeder = stp_FEEDSTD;break;
       }
      }

  SeqFeederNext = SeqFeeder;       
  switch (SeqFeeder)
  {
    case stp_INIT:
            if(SeqFeeder!=SeqFeederMEM) 
              {
                SeqFeederMEM = SeqFeeder;
                iQFeedDone = OFF;
                FeedingStarted = OFF;
                FeedCycleCancelled = OFF;
                EmptyBuffer();
                BulkFeedMem = OFF;
                DribbleFeedMem = OFF;
              }
            break;
            
    case stp_FEEDSTD:
            if(SeqFeederMEM != SeqFeeder)
             {
              SeqFeederMEM = SeqFeeder;
              if(WP.FeedAlgoType == FeediQSim) 
               {
                 iQSimFeed();
               } 
             }
            if(SeqFeedSTD == stp_FSDone)
             {
               if(WP.FeedAlgoType == FeediQSim) iQSimStopProgram (SCALE_CHANNEL, SCALE_NUMBER);
               SeqFeeder = stp_FEEDDONE;
             }
            break;
        
    case stp_FEEDDONE:
            if(SeqFeederMEM != SeqFeeder)SeqFeederMEM = SeqFeeder;          
            if(SeqMaster!=stp_FEED) SeqFeeder = stp_INIT;
            break;
            
  }                                                 
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_FeedSTD
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : Standard Feeder Sequence
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SEQ_FeedSTD(void)
{
bool SlowCycleDone,SlowCycleEndDribble, ResumeInDribble,FirstCycle,DribbleOnly;
bool CmpBulkOn1,CmpBulkOn2,Scale1BulkWeightDirect,StandardFeedInitDone;
int scanmemSTD[10],address;
float BulkBlankLimit,DribbleBlankLimit,Aout1SwitchValue,DribbleSP,TargetSP;
if(SeqModeManager == stp_OFF_MODE) 
 {
  SeqFeedSTD = stp_INIT;
  FirstCycle = ON;
  StandardFeedInitDone = OFF;
  if(T_EN[T_InitAlgo])T_EnOff(T_InitAlgo);
 } 

 if(WP.FeedAlgoType == FeedStd || WP.FeedAlgoType == FeediQSim)
 { 
  //Slow Cycle Alarm Managment
  if(SlowCycleMem || CycleInHoldMem)
             {
              if(!SlowCycleDone)
               if(DischargeHMI || WP.SlowCycleEnd == END_CYCLE) 
                {
                 if(CycleInHoldMem)
                 {
                  UnHoldCycle();
                 }
                SeqFeedSTD = stp_FSDribbleSetPoint;
                DribbleDone=ON;
                CheckOnce = ON;
                DischargeHMI = OFF;
                SlowCycleDone = ON;
                WeighmentAborted = ON;
                }
               
              if(WP.SlowCycleEnd == DRIBBLE_CYCLE && !SlowCycleEndDribble)
                {
                 if(SeqFeedSTD != stp_FSDribbleSetPoint)
                  {
                   FeedSTDReset();
                   SeqFeedSTD = stp_FSDribbleSetPoint;
                  } 

                 SlowCycleEndDribble = ON;
                } 
             }
   else  
             {
              if(SlowCycleDone) SlowCycleDone = OFF;
              if(SlowCycleEndDribble) SlowCycleEndDribble = OFF; 
             }           
 
  //Hold UnHold managment
  if(SeqFeedSTD != stp_INIT)
   {
    //if(IO_Enable[I_HoldCycle] && Input_State(I_HoldCycle) && !HoldCycleMem)
    //{
    //  HoldCycleMem = ON;
    //  HoldCycleTgl = ON;
    //}
  
    if(WP.SlowCycleEnd == HOLD_CYCLE)
    {  
     if(SlowCycleMem)
     {
     if(!CycleInHoldMem) HoldCycleTgl = ON;
     } 
    else if(StartHMI && CycleInHoldMem)
     {
     HoldCycleTgl = ON;
     }
    }   
   
  
    if(HoldCycleTgl)
    {    
     if(!CycleInHoldMem)
      {
      HoldCycle();
      SeqFeedSTD = stp_FSHold;
      MessageDisplay(lsub(TX_MSGCYCLEINHOLD),Step_Message);
      }
     else
      {
      ResumeInDribble = UnHoldCycle();
      SeqFeedSTD = stp_INIT;  
      }
    }  
    //if(IO_Enable[I_HoldCycle] && !Input_State(I_HoldCycle) && HoldCycleMem) HoldCycleMem = OFF;
   }
   
 } 
                
SeqFeedSTDNext = SeqFeedSTD;
switch (SeqFeedSTD)
 {
  case stp_INIT:
       if(SeqFeedSTDMEM != SeqFeedSTD)
        {
         CycleInHoldMem = OFF;
         HoldCycleTgl = OFF;
         BulkDone = OFF;
         IntermDone = OFF;
         DribbleDone = OFF;
         DribbleOnly = OFF;
         SeqFeedSTDMEM = SeqFeedSTD;
        } 
        
        if(InvertFeedAndDischOutputsMem != MP.InvertFeedAndDischOutputs || FailSafeONMem != FailSafeON || StopWithGatesAndDischDoorOpenONMem != StopWithGatesAndDischDoorOpenON || StopWithGatesAndDischDoorOpenON)
        {
           if(InvertFeedAndDischOutputsMem != MP.InvertFeedAndDischOutputs)InvertFeedAndDischOutputsMem = MP.InvertFeedAndDischOutputs;
           else if(FailSafeONMem != FailSafeON) FailSafeONMem = FailSafeON;
           else if(StopWithGatesAndDischDoorOpenONMem != StopWithGatesAndDischDoorOpenON)StopWithGatesAndDischDoorOpenONMem = StopWithGatesAndDischDoorOpenON;
           
           if((!MP.InvertFeedAndDischOutputs && !StopWithGatesAndDischDoorOpenON && !FailSafeON) || (MP.InvertFeedAndDischOutputs && FailSafeON && MP.FailSafe)
           || (MP.InvertFeedAndDischOutputs && StopWithGatesAndDischDoorOpenON && !FailSafeON))
           {
             if(IO_State[O_BulkFeed])    Output_OFF(O_BulkFeed);
             if(IO_State[O_DribbleFeed]) Output_OFF(O_DribbleFeed);
             if(IO_State[O_DischDoor] && !StartKeyOn)   Output_OFF(O_DischDoor);
           }
           else
           {
             if(!IO_State[O_BulkFeed])   Output_ON(O_BulkFeed);
             if(!IO_State[O_DribbleFeed])Output_ON(O_DribbleFeed);
             if(!IO_State[O_DischDoor]&& !StartKeyOn)  Output_ON(O_DischDoor);
           }
        }
        
        
     if(SeqFeeder == stp_FEEDSTD)
     {
         if(FirstCycle)
          {
           InitStandardFeed(ON);
           T_EnOn(T_InitAlgo);
           FirstCycle = OFF;
          }          
        
         if(!StandardFeedInitDone)
         {
          if(T_Dn(T_InitAlgo)) //Allow time for weight filter to init when Setting Algorithm
          {
           StandardFeedInitDone = ON;
          }
         } 
             
       if(StandardFeedInitDone)
       {  
        if(ResumeInDribble || (WP.BulkCutoff == 0 && !BulkOnTime[Scale1]) || (WP.BFTime <= 0 && BulkOnTime[Scale1]) || DribbleFeedOnly) //Dribble Feed Only Requested by External Input
        { 
         if(OK4DribbleFeed)
          {
          SeqFeedSTD = stp_FSDribbleBlank;
          T_EnOn(T_DribbleDuration);
          ResumeInDribble = OFF;
          DribbleOnly = ON;
          break;
          }
        break;  
        }
        
        else
        { 
          if(OK4BulkFeed) 
          { 
            //if(!StartKeyOn)SeqFeedSTD = stp_FSBulkBlank;
            //else SeqFeedSTD =  stp_StopWithGatesAndDischDoorOpen;
            SeqFeedSTD = stp_FSBulkBlank;
          }
           else break;
        }
       }  
       else break;
     }   
     break;
  /*
  case stp_StopWithGatesAndDischDoorOpen:
       if(SeqFeedSTDMEM != SeqFeedSTD)
       {
         SeqFeedSTDMEM = SeqFeedSTD;
         T_PRE[T_StopWithGatesAndDischDoorOpen] = 2; // wait for 2 sec before starting Standard Feeding Sequence 
         T_EnOn(T_StopWithGatesAndDischDoorOpen);
         if(!MP.InvertFeedAndDischOutputs)Output_ON(O_DischDoor);
         else Output_OFF(O_DischDoor);
       }     
       if(T_Dn(T_StopWithGatesAndDischDoorOpen))
       {
         T_EnOff(T_StopWithGatesAndDischDoorOpen);
         if(!MP.InvertFeedAndDischOutputs)Output_OFF(O_DischDoor);
         else Output_ON(O_DischDoor);
         StartKeyOn = OFF;
         SeqFeedSTD = stp_FSBulkBlank;
         break;
       }
       else
         break;
   */    
  case stp_FSBulkBlank:
       if(SeqFeedSTDMEM != SeqFeedSTD) 
            {
            SeqFeedSTDMEM = SeqFeedSTD;
            MessageDisplay(lsub(TX_MSGBULKBLANK),Step_Message);
            T_EnOn(T_BulkDuration);
            if(BulkOnTime[Scale1]) T_PRE[T_BulkBlankT] = WP.BFTime;
            else T_PRE[T_BulkBlankT] = MC.BulkBlankT;
            T_EnOn(T_BulkBlankT);
            if(!MP.InvertFeedAndDischOutputs)Output_ON(O_BulkFeed);
            else Output_OFF(O_BulkFeed);
            if(IO_Enable[O_Agitator])
            {
              if(!IO_State[O_Agitator])    Output_ON(O_Agitator);
            }
             
            if(MC.DribbleOutOnInBulk)
                {
                Output_ON(O_DribbleFeed);
                }
            break;    
            }
      if(T_Dn(T_BulkBlankT)|| T_PRE[T_BulkBlankT]==0 || WP.FeedAlgoType == FeediQSim)  
      {
            if(!BulkOnTime[Scale1])
            {
               SeqFeedSTD = stp_FSBulkSetPoint;
               T_EnOff(T_BulkBlankT);
            }
            else
            {
               if(T_EN[T_BulkDuration])
               {
                Output_OFF(O_BulkFeed);
                ProdBulkDuration[Scale1] = T_Acc(T_BulkDuration);
                T_EnOff(T_BulkDuration);
                //T_EnOn(T_DribbleDuration);
               }
              
               if(OK4DribbleFeed)
               {
                SeqFeedSTD = stp_FSDribbleBlank; 
                BulkDone=OFF;
                T_EnOn(T_SlowCycleTime);
                Output_OFF(O_CycleInHold);
                T_EnOff(T_BulkBlankT);
                T_EnOn(T_DribbleDuration);
                break;
               }
               
               else
               {
                 if(!IO_State[O_CycleInHold]) 
                 {
                  Output_OFF(O_DribbleFeed);
                  T_EnOff(T_SlowCycleTime);
                  Output_ON(O_CycleInHold);
                  MessageDisplay(lsub(TX_MSGCYCLEINHOLD),Step_Message);
                 } 
              } 
                break;     
            }
      } 
      break;
      
  
       
  case stp_FSBulkSetPoint:
       
       if(SeqFeedSTDMEM != SeqFeedSTD)
            {
            SeqFeedSTDMEM = SeqFeedSTD;
            MessageDisplay(lsub(TX_MSGBULKFEED),Step_Message);
            T_EnOn(T_BulkDuration);
            scanmemSTD[0] = systemtimer_ms();
               
             if(IO_Enable[O_BulkFeed])
             {
               if(!MP.InvertFeedAndDischOutputs)
                 setcomparator(SCALE_NUMBER,Scale1CmpBulk,IO_Address[O_BulkFeed],(WP.BulkCutoff+WeighPerUnitCorrOffset)*UnitIQtoADM,"<",1); 
               else                             
                 setcomparator(SCALE_NUMBER,Scale1CmpBulk,IO_Address[O_BulkFeed],(WP.BulkCutoff+WeighPerUnitCorrOffset)*UnitIQtoADM,"<",3);
               Scale1CmpBulkActive = ON;
             }
        
            scanmemSTD[1] = systemtimer_ms();
            if(!MP.InvertFeedAndDischOutputs)Output_OFF(O_BulkFeed);
            else Output_ON(O_BulkFeed);
           
                if(MC.DribbleOutOnInBulk)
                {   
                  if(!MP.InvertFeedAndDischOutputs)Output_ON(O_DribbleFeed);                   
                  else Output_OFF(O_DribbleFeed); 
                }
            break;
            } 
                           
        if(Scale1CmpBulkActive && !tstcomparator(SCALE_NUMBER,Scale1CmpBulk))
          {
           CmpBulkOn1 = ON;
          }
        
        if(Scale1BulkWeightDirect && NetWeight[Scale1] >=(WP.BulkCutoff+WeighPerUnitCorrOffset))
          {
           CmpBulkOn2 = ON;
          }
         
         if(CmpBulkOn1 || CmpBulkOn2)    
         {
          CmpBulkOn1 = OFF;
          CmpBulkOn2 = OFF;
          Scale1BulkWeightDirect = OFF;
          Scale1CmpBulkActive = OFF;
          BulkDone=ON;
          clrcomparator(SCALE_NUMBER,Scale1CmpBulk);
         }
         
       if(BulkDone)
      {
         if(T_EN[T_BulkDuration])
         {
          ProdBulkDuration[Scale1] = T_Acc(T_BulkDuration);
          T_EnOff(T_BulkDuration);
          //T_EnOn(T_DribbleDuration);//uncommented 05/02/2019
         }

         if(OK4DribbleFeed)
         {
            SeqFeedSTD = stp_FSDribbleBlank; 
            BulkDone=OFF;
            T_EnOn(T_SlowCycleTime);
            Output_OFF(O_CycleInHold);
            T_EnOn(T_DribbleDuration);
            break;
         }
         else
         {
          if(!IO_State[O_CycleInHold]) 
          {
           Output_OFF(O_DribbleFeed);
           T_EnOff(T_SlowCycleTime);
           Output_ON(O_CycleInHold);
           MessageDisplay(lsub(TX_MSGCYCLEINHOLD),Step_Message);
          } 
         } 
      }
      else 
         break;
         
       
               
  case stp_FSInterBlank:
       if(SeqFeedSTDMEM != SeqFeedSTD) 
            {
            SeqFeedSTDMEM = SeqFeedSTD;
            MessageDisplay(lsub(TX_MSGINTERMBLANK),Step_Message);
            T_EnOn(T_IntermBlankT);
            if(MC.DribbleOutOnInBulk) Output_ON(O_DribbleFeed);
            break;
            }
      if(T_Dn(T_IntermBlankT)||T_PRE[T_IntermBlankT]==0 || WP.FeedAlgoType == FeediQSim )
           {
           T_EnOff(T_IntermBlankT);
           SeqFeedSTD = stp_FSInterSetPoint;
           }
      else break;   
              
  case stp_FSInterSetPoint:
      if(SeqFeedSTDMEM != SeqFeedSTD)
      {
          SeqFeedSTDMEM = SeqFeedSTD;             
          MessageDisplay(lsub(TX_MSGINTERMFEED),Step_Message);                
          if(MC.DribbleOutOnInBulk)Output_ON(O_DribbleFeed);
          break;
      }   
      
      if(OK4DribbleFeed) 
       {
        SeqFeedSTD = stp_FSDribbleBlank;
        IntermDone = OFF;
       }
      else break;
             
  case stp_FSDribbleBlank:
       if(SeqFeedSTDMEM != SeqFeedSTD) 
            {
            SeqFeedSTDMEM = SeqFeedSTD;
            MessageDisplay(lsub(TX_MSGDRIBBLEBLANK),Step_Message);
            T_EnOn(T_DribbleBlankT);
            if(!MP.InvertFeedAndDischOutputs)Output_ON(O_DribbleFeed);
            else Output_OFF(O_DribbleFeed); 
            
            if(IO_Enable[O_Agitator])
            {
              if(!IO_State[O_Agitator])
               Output_ON(O_Agitator);
            }
            break;
            }
      if(T_Dn(T_DribbleBlankT)||T_PRE[T_DribbleBlankT]==0 || WP.FeedAlgoType == FeediQSim)
           {
           T_EnOff(T_DribbleBlankT);
           SeqFeedSTD = stp_FSDribbleSetPoint;
           }
      else break;
         
  case stp_FSDribbleSetPoint:
  
       if(SeqFeedSTDMEM != SeqFeedSTD) 
       {
       SeqFeedSTDMEM = SeqFeedSTD;
       ResumeInDribble = OFF;
         if(TargetWeightControlON())//added by namk 21/9/2018
         {
          DribbleSP = (CutoffTemp-CutoffCorrOffset[Scale1]+WeighPerUnitCorrOffset)*UnitIQtoADM;//added by namk 21/9/2018
         }
         else //added by namk 21/9/2018
         {
          DribbleSP = (WP.Cutoff-CutoffCorrOffset[Scale1]+WeighPerUnitCorrOffset)*UnitIQtoADM;
         }//added by namk 21/9/2018
         
        if(WP.FeedAlgoType == FeediQSim)
          {
           
           if(TargetWeightControlON())//added by namk 21/9/2018
           {//added by namk 21/9/2018
             TargetSP = TargetWeightBatchTemp*UnitIQtoADM;//added by namk 21/9/2018
             //DribbleSP = CutoffTemp;//added by namk 21/9/2018
             if (DribbleSP >= TargetSP)
             {
              DribbleSP = TargetSP - 0.1;
             }
           }//added by namk 21/9/2018
           else //added by namk 21/9/2018
           {
            TargetSP = TargetWeight[Scale1]*UnitIQtoADM;
            if (DribbleSP >= TargetSP)
            {
              DribbleSP = TargetSP - 0.1;
            }
           }
          }   
       if(!DribbleDone)
        {
         MessageDisplay(lsub(TX_MSGDRIBBLEFEED),Step_Message);
         if(IO_Enable[O_DribbleFeed])
          {
            if(!MP.InvertFeedAndDischOutputs)setcomparator(SCALE_NUMBER,Scale1CmpDribble,IO_Address[O_DribbleFeed],DribbleSP,"<",1);
            else setcomparator(SCALE_NUMBER,Scale1CmpDribble,IO_Address[O_DribbleFeed],DribbleSP,"<",3);
            Scale1CmpDribbleActive = ON;
          } 
         
         if(!MP.InvertFeedAndDischOutputs)Output_OFF(O_DribbleFeed);
         else Output_ON(O_DribbleFeed);
         
         if(IO_Enable[O_Agitator])
         {
          if(IO_State[O_Agitator])    Output_OFF(O_Agitator);
         }
         
           
        }  
       }
       
       if((Scale1CmpDribbleActive && !tstcomparator(SCALE_NUMBER,Scale1CmpDribble)) || (Scale1CmpCatchGateActive && !tstcomparator(SCALE_NUMBER,Scale1CmpCatchGate)) )
         {
         if(!OFF || WP.CatchGateDelay != 0 || (OFF && Scale1CmpCatchGateActive && !tstcomparator(SCALE_NUMBER,Scale1CmpCatchGate))) //added by namk 25/9/2018 test
          {
          DribbleDone=ON;
          ProdDribbleDuration[Scale1] = T_Acc(T_DribbleDuration);
          T_EnOff(T_DribbleDuration);
          
          Scale1CmpDribbleActive = OFF;    
          clrcomparator(SCALE_NUMBER,Scale1CmpDribble);
          DrCmpOffTime = systemtimer_ms();
          }
         }      
        
       if(DribbleDone)
       {
        if(!OFF || WP.CatchGateDelay == 0 || (WP.CatchGateDelay < CATCHGATEDELAYMAX && (T_Dn(T_CatchGateDelay) || !T_EN[T_CatchGateDelay])) 
             ||  WP.CatchGateDelay >= CATCHGATEDELAYMAX)//added by namk 25/9/2018 test
         {
          T_EnOff(T_CatchGateDelay);
          FeedSTDReset();
          if(IO_Enable[I_FeedGateClose])
          {
           SeqFeedSTD = stp_CheckFeedGateClose;
           break;
          } 
          else
          {
           SeqFeedSTD = stp_FSDone;
          } 
         }
         else break;
       }
       else break;
       
  
          
  case stp_FSDone:
       if(SeqFeedSTDMEM != SeqFeedSTD)
        {
        
        
        SeqFeedSTDMEM = SeqFeedSTD;
        if(!BulkOnTime[Scale1] && !DribbleOnly)
        {
         BulkBlankLimit = T_PRE[T_BulkBlankT] + 0.15;
         if(ProdBulkDuration[Scale1] < BulkBlankLimit && WP.FeedAlgoType != FeediQSim)
          {
           if(!WeighmentAborted)
            {
            //FaultHandler(FltW_BulkBlankTooLong,"");
            DisplayAlarmDelay = ON;
            } 
           CheckOnce = ON;
          }
        }
        
        DribbleBlankLimit = T_PRE[T_DribbleBlankT] + 0.15;
        if(ProdDribbleDuration[Scale1] < DribbleBlankLimit && WP.FeedAlgoType != FeediQSim) 
         {
           if(!WeighmentAborted)
           {
            //FaultHandler(FltW_DribbleBlankTooLong,"");
            DisplayAlarmDelay = ON;
           } 
          CheckOnce = ON;
         }
        }
        
       if(DribbleDone && SeqFeeder == stp_FEEDDONE)
             {
             DribbleDone=OFF;
             SeqFeedSTD = stp_INIT;
             }
       break;
       
  case stp_CheckFeedGateClose:
       if(SeqFeedSTDMEM != SeqFeedSTD)
       {
         SeqFeedSTDMEM = SeqFeedSTD;
         T_PRE[T_FeedGateMaxTime] = MP.FeedGateMaxTime; 
       }
         
       if(MP.FeedGateMaxTime > 0 && IO_Enable[I_FeedGateClose]) 
       {
         if(!T_EN[T_FeedGateMaxTime] && !FeedGateNotClose && !FaultState(FltB_FeedGateNotClose)) 
          T_EnOn(T_FeedGateMaxTime);
         if(((T_Dn(T_FeedGateMaxTime) && !Input_State(I_FeedGateClose)) || FeedGateStillClose) && SeqMaster != stp_TOPUP)     
         {
           FeedGateNotClose = ON;
         }
         if((!T_Dn(T_FeedGateMaxTime) && Input_State(I_FeedGateClose) && !FeedGateStillClose && !FaultState(FltB_FeedGateNotClose)) || SeqMaster == stp_TOPUP)
         { 
           T_EnOff(T_FeedGateMaxTime);
           FeedGateNotClose = OFF;
           SeqFeedSTD = stp_FSDone;
         }
       }
       else
       {
        T_EnOff(T_FeedGateMaxTime);
        SeqFeedSTD = stp_FSDone;
       }        
       break;
       
  case stp_FSHold:
       if(SeqFeedSTDMEM != SeqFeedSTD)SeqFeedSTDMEM = SeqFeedSTD;
       break;     
 }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_WeighPan
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : Weighing Pan Sequence
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SEQ_WeighPan(void)
{
if(SeqModeManager == stp_OFF_MODE) SeqWeighPan = stp_INIT;

SeqWeighPanNext = SeqWeighPan;
switch (SeqWeighPan)
       {
       case stp_INIT:
            if(SeqWeighPanMEM != SeqWeighPan)SeqWeighPanMEM = SeqWeighPan;
            if(SeqMaster == stp_DISCHARGING)SeqWeighPan = stp_OPENDOORS;
            else break;
            
       case stp_OPENDOORS:
            if(SeqWeighPan!=SeqWeighPanMEM)
            {
            SeqWeighPanMEM = SeqWeighPan;
            if(WP.DischargeTime>0) {MessageDisplay(lsub(TX_MSGDISCHARGEONTIME),Step_Message);T_EnOn(T_DischargeTime);}
            if(!MP.InvertFeedAndDischOutputs)Output_ON(O_DischDoor);//Invert Feed and Disch outputs function
            else Output_OFF(O_DischDoor);//Invert Feed and Disch outputs function
            
            if(WP.FeedAlgoType == FeediQSim) 
              {
               iQSimDischarge();
              }
            
            if(WeighmentInPan && WeighPerUnitDone) Output_ON(O_ExternalBagCounter);
            KnockHammerFlag = ON;
            WeighmentInPan = OFF;
            if(!IO_Enable[I_DischDoorClose] || !MC.DischOnDoorSensor)
             if(WeighPerUnitDone)
               Output_ON(O_Discharge);
            if(WP.VibratoryDischDoors)Output_ON(O_VibrDischDoor);
            break;
            }
            if(IO_Enable[I_DischDoorClose]&& MC.DischOnDoorSensor &&!Input_State(I_DischDoorClose)&&!IO_State[O_Discharge])
             if(WeighPerUnitDone)
                Output_ON(O_Discharge);
            if(T_Dn(T_DischargeTime))MessageDisplay(lsub(TX_MSGDISCHARGEONWEIGHT),Step_Message);
            if((WP.DischargeTime==0 || T_Dn(T_DischargeTime)) && (WP.DischargeWeight == WP.NominalWeight || NetWeight[Scale1]< WP.DischargeWeight))
            {
               T_EnOff(T_DischargeTime);
               if ((ZeroFreqCnt == 0 || (WP.FeedAlgoType != FeediQSim && (LowLevel[Scale1] || EmptyHopper)))&& !AutoZeroOff && WP.ZeroingOpen)
                {
                SetZeroStatus[Scale1]=-1;
                SeqMaster = stp_ZERO; 
                break;
                }
               else SeqWeighPan = stp_CLOSEDOORS;
            }
            else break;
            
       case stp_CLOSEDOORS:
            if(SeqWeighPanMEM!=SeqWeighPan)
            {
            if(WP.FeedAlgoType == FeediQSim) iQSimStopProgram (SCALE_CHANNEL, SCALE_NUMBER);
            SeqWeighPanMEM = SeqWeighPan;
            if(!MP.InvertFeedAndDischOutputs)Output_OFF(O_DischDoor);//Invert Feed and Disch outputs function
            else Output_ON(O_DischDoor);//Invert Feed and Disch outputs function
            Output_OFF(O_Discharge);
            if(WeighPerUnitDone) 
              Discharged();
            Output_OFF(O_ExternalBagCounter);
            KnockHammerFlag = OFF;
            if(WP.VibratoryDischDoors)Output_OFF(O_VibrDischDoor);
            break;
            }
            if(SeqMaster != stp_DISCHARGING && SeqMaster != stp_ZERO)SeqWeighPan = stp_INIT;
            
       }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SEQ_ManDischarge
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : Weighing Pan Sequence
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SEQ_ManDischarge(void)
{
if(SeqModeManager == stp_OFF_MODE) SeqManDischarge = stp_INIT;

SeqManDischargeNext = SeqManDischarge;
switch (SeqManDischarge)
       {
       case stp_INIT:
            if(SeqManDischargeMEM != SeqManDischarge)SeqManDischargeMEM = SeqManDischarge;
            if(SeqModeManager == stp_MANUAL_MODE && ManualModeStep == stp_ManualDisch)
               SeqManDischarge = stp_OPENDOORS;
            else break;
            
     
       case stp_OPENDOORS:
            if(SeqManDischargeMEM!=SeqManDischarge)
            {
            SeqManDischargeMEM = SeqManDischarge;
            MessageDisplay(lsub(TX_MSGMANUALDISCHARGE),Step_Message);
            if(!MP.InvertFeedAndDischOutputs)Output_ON(O_DischDoor);//Invert Feed and Disch outputs function
            else Output_OFF(O_DischDoor);//Invert Feed and Disch outputs function
            if(WP.FeedAlgoType == FeediQSim) 
              {
               iQSimDischarge();
              }
            Output_ON(O_DischReady);
            if(WeighmentInPan && WeighPerUnitDone) Output_ON(O_ExternalBagCounter);
            KnockHammerFlag = ON;
            WeighmentInPan = OFF;
            if(!IO_Enable[I_DischDoorClose] || !MC.DischOnDoorSensor)
              Output_ON(O_Discharge);
            if(WP.VibratoryDischDoors)Output_ON(O_VibrDischDoor);
            break;
            }
            if(IO_Enable[I_DischDoorClose]&& MC.DischOnDoorSensor &&!Input_State(I_DischDoorClose)&&!IO_State[O_Discharge])
              Output_ON(O_Discharge);
            if(StopHMI || (IO_Enable[I_Stop] && Input_State(I_Stop)&&!I_StopMem) 
               ||(DischargeHMI ||(IO_Enable[I_ManDisch]&& Input_State(I_ManDisch)&&!I_ManDischMem)))
                       SeqManDischarge = stp_CLOSEDOORS;
            else break;
            
       case stp_CLOSEDOORS:
            if(SeqManDischargeMEM != SeqManDischarge)
              {
               T_EnOn(T_BagRelease);
               SeqManDischargeMEM = SeqManDischarge;
               StopHMI=OFF;
               DischargeHMI=OFF;
               I_ManDischMem=ON;
               I_StopMem=ON;
               OutOfTol[Scale1] = OFF;
               if(!MP.InvertFeedAndDischOutputs)Output_OFF(O_DischDoor);//Invert Feed and Disch outputs function
               else Output_ON(O_DischDoor);//Invert Feed and Disch outputs function
               Output_OFF(O_Discharge);
               if(WeighPerUnitDone) //after modification added by namk 18/9/2018
                Discharged();
               Output_OFF(O_DischReady);
               Output_OFF(O_ExternalBagCounter);
               KnockHammerFlag = OFF;
               if(WP.VibratoryDischDoors)Output_OFF(O_VibrDischDoor);
               break;
               }
            if (T_Dn(T_BagRelease))
              {
               T_EnOff(T_BagRelease);
               SeqManDischarge = stp_DONE;
              } 

            else break;
        
       case stp_DONE:
            if(SeqManDischargeMEM != SeqManDischarge)
              {
              SeqManDischargeMEM = SeqManDischarge;
              ManualModeStep = stp_DONE;
              }    
            if(SeqModeManager == stp_OFF_MODE)SeqManDischarge = stp_INIT;
       }
       
if(DischargeHMI) DischargeHMI=OFF;
if(IO_Enable[I_Start] && Input_State(I_Start)) I_StartMem = ON;
if(IO_Enable[I_Stop] && Input_State(I_Stop)) I_StopMem = ON;
if(IO_Enable[I_ManDisch]&& Input_State(I_ManDisch))I_ManDischMem = ON;


}




              
 

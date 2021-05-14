/*------------------------------------------------------------------------------------
-- File Name: Global_Functions.h 
--
-- Copyright 2015 PremierTech as an unpublished work. 
-- All Rights Reserved.
--
-- The information contained herein is confidential property of 
-- Premier Tech.  The use, copying, transfer or disclosure of such
-- information is prohibited except by express written agreement with
-- Premier Tech.
--
-- First written in February, 2015 by Jean-Pierre Doré.
--
-- Module Description:
-- This file is dedicated to miscellaneous functions used throughout the program 
-------------------------------------------------------------------------------------*/

/* *********************************************************************** */
/*                                                                         */
/*       Global functions                                                  */
/*                                                                         */
/* *********************************************************************** */
//convert from char to dec e.g. 0 in char is 48 in dec
enum{zero=48,one,two,tree,four,five,six,seven,eight,nine}
//time digit
enum{digit1,digit2,digit3,digit4,digit5}

void AccessButtonSwitch(bool enable)
{
   if(enable)
    {
     AccessOK = ON;
     widget_image (ACCESS_BUTTON_1,BTN_ACCESS_OK);
    }
   else
    {
     AccessOK = OFF;
     widget_image (ACCESS_BUTTON_1,BTN_NOACCESS);
    }   
}

void RecipeButtonSwitch(int button_nbr, bool enable)
{
 if (enable)
  {
   if(!RecipeButton) RecipeButton = ON;
   widget_image (button_nbr,BTN_RECIPE);
   widget_attribute (button_nbr, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
  }
 if (!enable)
  {
    if(RecipeButton) RecipeButton = OFF;
    widget_image (button_nbr,BTN_RECIPE_GRAYOUT);
    widget_attribute (button_nbr, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
  }
}      

void PageButtonSwitch(int button_nbr, bool enable)
{

string image[64];

 if (enable && (!GotoPageButton[button_nbr-GOTO_PAGE_BUTTON_1+1] || FirstScan))
  {
   GotoPageButton[button_nbr-GOTO_PAGE_BUTTON_1+1] = ON;
   switch(button_nbr)
    {
      case GOTO_PAGE_BUTTON_1:  image = BTN_IO_CONFIG; break;
      case GOTO_PAGE_BUTTON_4:  image = BTN_IO_STATUS; break;
      case GOTO_PAGE_BUTTON_5:  image = BTN_MC;        break;
      case GOTO_PAGE_BUTTON_6:  image = BTN_MP;        break;
      case GOTO_PAGE_BUTTON_9:  image = BTN_FLEXIO;    break;
      case GOTO_PAGE_BUTTON_10: image = BTN_COPY;      break;
    }  
   widget_image (button_nbr,image);
   widget_attribute (button_nbr, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
  }
 
 if (!enable && (GotoPageButton[button_nbr-GOTO_PAGE_BUTTON_1+1] || FirstScan))
  {
    GotoPageButton[button_nbr-GOTO_PAGE_BUTTON_1+1] = OFF;
    switch(button_nbr)
    {
      case GOTO_PAGE_BUTTON_1:  image = BTN_IO_CONFIG_GRAYOUT; break;
      case GOTO_PAGE_BUTTON_4:  image = BTN_IO_STATUS_GRAYOUT; break;
      case GOTO_PAGE_BUTTON_5:  image = BTN_MC_GRAYOUT;        break;
      case GOTO_PAGE_BUTTON_6:  image = BTN_MP_GRAYOUT;        break;
      case GOTO_PAGE_BUTTON_9:  image = BTN_FLEXIO_GRAYOUT;    break;
      case GOTO_PAGE_BUTTON_10: image = BTN_COPY_GRAYOUT;      break;
    }
    widget_image (button_nbr,image);
    widget_attribute (button_nbr, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
  }
}     

void LowLevelResetMode(void)
{

 if(LowLevelManReset)
  { 
   LowLevelManReset = OFF;
   widget_image (GOTO_FCT_BUTTON_8, BTN_LOWLEVEL_AUTORESET);
  }
 else
 {
  LowLevelManReset = ON;
  widget_image (GOTO_FCT_BUTTON_8, BTN_LOWLEVEL_MANRESET);
 }

}  

/* Check if OIML setting hase changeg*/
void CheckOIML(void)
{  
 if(MC.OIML)
  {
   ZeroLimit = 0.019;
   MP.ZeroLimit = ZeroLimit*100.0;
   AutoZeroOff = OFF;
   MP.AutoZeroOff = OFF;
  }
 
 else
  {
   ZeroLimit = Lim(0.1,100,MP.ZeroLimit)/100.0 ;
   AutoZeroOff = MP.AutoZeroOff;
  }

}

/* Check Continuous Output setting hase changeg*/     
bool CheckContOut(int MC_COM2,int MC_ETH)
{
int ContOutPort,ContOutFormat;

 ContOutFormat = readparameter("Continuous Output 1","Format"); //0 = off, !0 = other
 ContOutPort = readparameter("Continuous Output 1","Port"); //15=Eth, SIM2 = 3
 if(!ContOutFormat)
 {
   if (MC_COM2 == COM2FctContinuousOut || MC_ETH == COM2FctContinuousOut)
   {
    SystemErrorCode = "321 Continuous Output:not set in Service Mode";
    return(OFF);   
   }
  
 }
 else
 {
  if(MC_COM2 == COM2FctContinuousOut && MC_ETH == ETHFctContinuousOut)
  {
     SystemErrorCode = "323 Continuous Output:MC port conflict";
     return(OFF);
  }
  
  if((ContOutPort == 3 && MC_COM2 != COM2FctContinuousOut) || (ContOutPort != 3 && MC_COM2 == COM2FctContinuousOut) 
   || (ContOutPort == 15 && MC_ETH != ETHFctContinuousOut) || (ContOutPort != 15 && MC_ETH == ETHFctContinuousOut))
  {
    SystemErrorCode = "322 Continuous Output:SM vs MC port mismatch";
    return(OFF);
  }
  
     
 }
 
 return(ON);  
}

// Printer IP Adress Validation
string CheckPrinterIP(string IPAddress)
{
string IPField[4][3],IPTempo[15];
int i,IPFieldInt,IPFieldLen;

IPTempo = "";

split(IPField,IPAddress,'.');
for(i=0;i<=3;i++)
 {
  IPFieldInt = int(IPField[i]);
  if(IPFieldInt>=0 && IPFieldInt<= 255)
   {
    IPFieldLen = length(IPField[i]);
    if(IPFieldLen>=1 && IPFieldLen<=3)
     {
      IPTempo = concat(IPTempo,IPField[i]);
      if(i<3)  IPTempo = concat(IPTempo,".");
     }
    else 
    { 
      IPTempo = "";
      break;
    }
   } 
  else
   {
   IPTempo = "";
   break;
   }
 }  
return(IPTempo);
}

//Save Production Variables to NOVs
void SaveProdVars(void)
{
 int i,j;
 
 for(i=0;i<=1;i++)
 {
  SumWeightNOV[i]            = SumWeight[i];                
  AvgWeightNOV[i]            = AvgWeight[i];
  SqareSumWeightNOV[i]       = SqareSumWeight[i];
  StdDevNOV[i]               = StdDev[i];
  SqareSumWeightStringNOV[i] = SqareSumWeightString[i];
  SumWeightStringNOV[i]      = SumWeightString[i];
  NbrCheckedNOV[i]           = NbrChecked[i];
  ProdUnderWeightCntNOV[i]   = ProdUnderWeightCnt[i];
  ProdOverWeightCntNOV[i]    = ProdOverWeightCnt[i];
  ProdAcceptUnitCntNOV[i]    = ProdAcceptUnitCnt[i];
  ProdTotalUnitsCntNOV[i]    = ProdTotalUnitsCnt[i];
  ProdStdDevNOV[i]           = ProdStdDev[i];
  ProdAvgWeightNOV[i]        = ProdAvgWeight[i];
  //ProdTotalWeightNOV[i]      = ProdTotalWeight[i];
  ProdTotalWeightNOV[i]      = ProdTotalWeight;
  ProdLastCheckedNOV[i]      = ProdLastChecked[i];
  ProdLastWeightNOV[i]       = ProdLastWeight[i];
  ProdTotalWeighmentsLTNOV[i]= ProdTotalWeighmentsLT[i];
  ProdTotalUnitsLTNOV[i]     = ProdTotalUnitsLT[i];
  ProdTotalWeightLTNOV[i]    = ProdTotalWeightLT; 
  }
  //In process related data
  for(j = 0; j < 52; j++)
  {
  ProdSiloNoWeightNOV[j]     = ProdSiloNoWeight[j];
  } 
  ProdTotalWeightOfShiftNOV  = ProdTotalWeightOfShift;
  ProdTotalUnitOfShiftNOV    = ProdTotalUnitOfShift;
  ProdTotalWeightOfHourlyNOV = ProdTotalWeightOfHourly;
  ProdTotalUnitOfHourlyNOV   = ProdTotalUnitOfHourly;
  LastShiftTotalWeightLTNOV  = LastShiftTotalWeightLT;
  LastShiftTotalUnitsLTNOV   = LastShiftTotalUnitsLT;
  LastHourlyTotalWeightLTNOV = LastHourlyTotalWeightLT;
  LastHourlyTotalUnitsLTNOV  = LastHourlyTotalUnitsLT;
  CurrentShiftUsageWeightNOV = CurrentShiftUsageWeight;
  CurrentShiftTimeNOV        = CurrentShiftTime;
  LastShiftTimeNOV           = LastShiftTime;
  CurrentHourlyTimeNOV       = CurrentHourlyTime;
  LastHourlyTimeNOV          = LastHourlyTime;
  LastPulseTotalWeightNOV    = LastPulseTotalWeight;
  AccPulseTotalWeightNOV     = AccPulseTotalWeight;
  PulseTotalWeightRemainNOV  = PulseTotalWeightRemain;
  WPTargetWeightIPTempNov    = WPTargetWeightIPTemp;
  
  DateNbrMemNOV   = DateNbrMem;
  TrialDaysCntNOV = TrialDaysCnt;

}  

//Load Production Variables from NOVs
void LoadProdVars(void)
{
 int i,j;
 
 for(i=0;i<=1;i++)
 {
  SumWeight[i]            = SumWeightNOV[i];                
  AvgWeight[i]            = AvgWeightNOV[i];
  SqareSumWeight[i]       = SqareSumWeightNOV[i];
  StdDev[i]               = StdDevNOV[i];
  SqareSumWeightString[i] = SqareSumWeightStringNOV[i];
  SumWeightString[i]      = SumWeightStringNOV[i];
  NbrChecked[i]           = NbrCheckedNOV[i];
  ProdUnderWeightCnt[i]   = ProdUnderWeightCntNOV[i];
  ProdOverWeightCnt[i]    = ProdOverWeightCntNOV[i];
  ProdAcceptUnitCnt[i]    = ProdAcceptUnitCntNOV[i];
  ProdTotalUnitsCnt[i]    = ProdTotalUnitsCntNOV[i];
  ProdStdDev[i]           = ProdStdDevNOV[i];
  ProdAvgWeight[i]        = ProdAvgWeightNOV[i];
  //ProdTotalWeight[i]      = ProdTotalWeightNOV[i];
  ProdTotalWeight         = ProdTotalWeightNOV[i];
  ProdLastChecked[i]      = ProdLastCheckedNOV[i];
  ProdLastWeight[i]       = ProdLastWeightNOV[i];
  ProdTotalWeighmentsLT[i]= ProdTotalWeighmentsLTNOV[i];
  ProdTotalUnitsLT[i]     = ProdTotalUnitsLTNOV[i];
  ProdTotalWeightLT    = ProdTotalWeightLTNOV[i];
  }  
  //In process related data
  for(j = 0; j < 52; j++)
  {
  ProdSiloNoWeight[j]     = ProdSiloNoWeightNOV[j];
  } 
  ProdTotalWeightOfShift  = ProdTotalWeightOfShiftNOV;
  ProdTotalUnitOfShift    = ProdTotalUnitOfShiftNOV;
  ProdTotalWeightOfHourly = ProdTotalWeightOfHourlyNOV;
  ProdTotalUnitOfHourly   = ProdTotalUnitOfHourlyNOV;
  LastShiftTotalWeightLT  = LastShiftTotalWeightLTNOV;
  LastShiftTotalUnitsLT   = LastShiftTotalUnitsLTNOV;
  LastHourlyTotalWeightLT = LastHourlyTotalWeightLTNOV;
  LastHourlyTotalUnitsLT  = LastHourlyTotalUnitsLTNOV;
  CurrentShiftUsageWeight = CurrentShiftUsageWeightNOV;
  CurrentShiftTime        = CurrentShiftTimeNOV;
  LastShiftTime           = LastShiftTimeNOV;
  CurrentHourlyTime       = CurrentHourlyTimeNOV;
  LastHourlyTime          = LastHourlyTimeNOV;
  LastPulseTotalWeight    = LastPulseTotalWeightNOV;
  AccPulseTotalWeight     = AccPulseTotalWeightNOV;
  PulseTotalWeightRemain  = PulseTotalWeightRemainNOV;
  WPTargetWeightIPTemp    = WPTargetWeightIPTempNov;
  
  DateNbrMem   = DateNbrMemNOV;
  TrialDaysCnt = TrialDaysCntNOV;

}   

//Copy NOV variables into Weigh per unit values
void WeighPerUnitLoad(void)
{
  WeighPerUnitAcc        = WeighPerUnitAccNOV;
  WeighPerUnitDone       = WeighPerUnitDoneNOV;
  WeighPerUnitCorrOffset = WeighPerUnitCorrOffsetNOV;
  WeighPerUnitSum        = WeighPerUnitSumNOV;
  WeighmentInPan         = WeighmentInPanNOV;      
}

//Copy Weigh per unit variables into NOV values
void WeighPerUnitSave(void)
{
 int scanmem,scanduration;
 
  scanmem = systemtimer_ms(); 
  WeighPerUnitAccNOV        = WeighPerUnitAcc;
  WeighPerUnitDoneNOV       = WeighPerUnitDone;
  WeighPerUnitCorrOffsetNOV = WeighPerUnitCorrOffset;
  WeighPerUnitSumNOV        = WeighPerUnitSum;
  WeighmentInPanNOV         = WeighmentInPan;  
  scanduration = systemtimer_ms()-scanmem; 
}

//Copy NOV variables into Learning values
void CopyNovToLearnParam(void) 
{
MinFeedingMem           = MinFeedingMemNOV;
MaxFeedingMem           = MaxFeedingMemNOV;
req_slow_fill_timeMem   = req_slow_fill_timeMemNOV;
TargetWeightMem[Scale1] = TargetWeightMemNOV[Scale1];
TargetWeightMem[Scale2] = TargetWeightMemNOV[Scale2];
SlowFilterSizeMem       = SlowFilterSizeMemNOV;
FastFilterSizeMem       = FastFilterSizeMemNOV;
FlashFilterSizeMem      = FlashFilterSizeMemNOV;
StdFilterSizeMem        = StdFilterSizeMemNOV;
StreamRegConfigMem      = StreamRegConfigMemNOV;
iQFlSwitchWeightMem     = iQFlSwitchWeightMemNOV;
iQFlReduceOutputMem     = iQFlReduceOutputMemNOV;
iQFlControlTimeMem      = iQFlControlTimeMemNOV;
RecipeMem               = RecipeMemNOV;
FeedAlgoTypeMem         = FeedAlgoTypeMemNOV; 
}

//Copy Learning values into NOV variables
void CopyLearnToNovParam(void) 
{
MinFeedingMemNOV           = MinFeedingMem;
MaxFeedingMemNOV           = MaxFeedingMem;
req_slow_fill_timeMemNOV   = req_slow_fill_timeMem;
TargetWeightMemNOV[Scale1] = TargetWeightMem[Scale1];
TargetWeightMemNOV[Scale2] = TargetWeightMem[Scale2];
SlowFilterSizeMemNOV       = SlowFilterSizeMem;
FastFilterSizeMemNOV       = FastFilterSizeMem;
FlashFilterSizeMemNOV      = FlashFilterSizeMem;
StdFilterSizeMemNOV        = StdFilterSizeMem;
StreamRegConfigMemNOV      = StreamRegConfigMem;
iQFlSwitchWeightMemNOV     = iQFlSwitchWeightMem;
iQFlReduceOutputMemNOV     = iQFlReduceOutputMem;
iQFlControlTimeMemNOV      = iQFlControlTimeMem;
RecipeMemNOV               = RecipeMem;
FeedAlgoTypeMemNOV         = FeedAlgoTypeMem; 
}
   
/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshRecipeInAutoScreen
--  Created by        : Steve Santerre
--  Last modified on  : 2017/02
--  
--  Purpose           : Refresh Text and Background color of Recipe selection
--                      in Auto Screen
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void RefreshRecipeInAutoScreen(void)
{

if(WP.FeedAlgoType == FeediQSim)
         {
          widget_text (ACTIVE_RECIPE_ID, concat(space(1),lsub(WP.Name), space(1),lsub(TX_WPALGOSIMIQ), space(1)));
          widget_style(ACTIVE_RECIPE_ID, AUTOWPBOX_STYLE_RED);
         }
        
        else
         {   
          widget_text (ACTIVE_RECIPE_ID, concat(space(1),lsub(WP.Name), space(1)) );
          if(ActiveRecipeAllowed) widget_style(ACTIVE_RECIPE_ID, AUTOWPBOX_STYLE);
          else widget_style(ACTIVE_RECIPE_ID, AUTOWPBOX_STYLE_GRAY);
         }

}


void InitFeederList(void)
{

  Feeder.Type[FeederNone] = FeederNone;
  Feeder.Name[FeederNone] = TX_DASHES;
  Feeder.Enable[FeederNone] = ON;
  Feeder.NbrOf1stLearn[FeederNone] = 0;
  Feeder.EnableOnAllLearning[FeederNone] = OFF;
  
  Feeder.Type[FeederG] = FeederG;
  Feeder.Name[FeederG] = TX_MCFeederG;
  Feeder.Enable[FeederG] = ON;
  Feeder.NbrOf1stLearn[FeederG] = 1;
  Feeder.EnableOnAllLearning[FeederG] = OFF;
  
  Feeder.Type[FeederGHS] = FeederGHS;
  Feeder.Name[FeederGHS] = TX_MCFeederGHS;
  Feeder.Enable[FeederGHS] = ON;
  Feeder.NbrOf1stLearn[FeederGHS] = 1;
  Feeder.EnableOnAllLearning[FeederGHS] = OFF;
  
  Feeder.Type[FeederV] = FeederV;
  Feeder.Name[FeederV] = TX_MCFeederV;
  Feeder.Enable[FeederV] = ON;
  Feeder.NbrOf1stLearn[FeederV] = 2;
  Feeder.EnableOnAllLearning[FeederV] = ON;
  
  Feeder.Type[FeederGV] = FeederGV;
  Feeder.Name[FeederGV] = TX_MCFeederGV;
  Feeder.Enable[FeederGV] = ON;
  Feeder.NbrOf1stLearn[FeederGV] = 1;
  Feeder.EnableOnAllLearning[FeederGV] = OFF;
  
  Feeder.Type[FeederB] = FeederB;
  Feeder.Name[FeederB] = TX_MCFeederB;
  Feeder.Enable[FeederB] = ON;
  Feeder.NbrOf1stLearn[FeederB] = 2;
  Feeder.EnableOnAllLearning[FeederB] = ON;
  
  Feeder.Type[FeederBHS] = FeederBHS;
  Feeder.Name[FeederBHS] = TX_MCFeederBHS;
  Feeder.Enable[FeederBHS] = OFF;
  Feeder.NbrOf1stLearn[FeederBHS] = 2;
  Feeder.EnableOnAllLearning[FeederBHS] = ON;
  
  Feeder.Type[FeederBSF] = FeederBSF;
  Feeder.Name[FeederBSF] = TX_MCFeederBSF;
  Feeder.Enable[FeederBSF] = OFF;
  Feeder.NbrOf1stLearn[FeederBSF] = 2;
  Feeder.EnableOnAllLearning[FeederBSF] = OFF;
  
  Feeder.Type[FeederBSFHS] = FeederBSFHS;
  Feeder.Name[FeederBSFHS] = TX_MCFeederBSFHS;
  Feeder.Enable[FeederBSFHS] = OFF;
  Feeder.NbrOf1stLearn[FeederBSFHS] = 2;
  Feeder.EnableOnAllLearning[FeederBSFHS] = OFF;
  
  Feeder.Type[FeederSS] = FeederSS;
  Feeder.Name[FeederSS] = TX_MCFeederSS;
  Feeder.Enable[FeederSS] = ON;
  Feeder.NbrOf1stLearn[FeederSS] = 2;
  Feeder.EnableOnAllLearning[FeederSS] = ON;
  
  Feeder.Type[FeederDS] = FeederDS;
  Feeder.Name[FeederDS] = TX_MCFeederDS;
  Feeder.Enable[FeederDS] = ON;
  Feeder.NbrOf1stLearn[FeederDS] = 2;
  Feeder.EnableOnAllLearning[FeederDS] = ON;
}
         
/* *********************************************************************** */
/*                                                                         */
/*       Refresh Stats Data Popup screen display                           */
/*                                                                         */
/* *********************************************************************** */
void RefreshStatDataPopup(void)
{
RefreshStatDataPopupFlag = Execute;
}

/* *********************************************************************** */
/*                                                                         */
/*       Refresh Weighing Data Popup screen display                           */
/*                                                                         */
/* *********************************************************************** */
void RefreshWeighingDataPopup(int ScaleNo)
{
 //ScaleNo:  (0)Reset, (1)Scale1 ,(2)Scale2
 if(ScaleNo>0)
  RefreshWeighingDataPopupFlag[ScaleNo-1] = Execute;
 else
  ResetWeighingDataPopupFlag = Execute; 
}

/* *********************************************************************** */
/*                                                                         */
/*       Refresh Auto screen display Request                               */
/*                                                                         */
/* *********************************************************************** */
void RefreshAutoScreenReq(void)
{
RefreshAutoScreenFlag = Execute;
}

/* *********************************************************************** */
/*                                                                         */
/*       Refresh REPORT screen display                                     */
/*                                                                         */
/* *********************************************************************** */

void RefreshBatchScreenReq(void)
{
   RefreshBatchScreenFlag = Execute;
}

/* *********************************************************************** */
/*                                                                         */
/*       Refresh REPORT screen display                                     */
/*                                                                         */
/* *********************************************************************** */

void RefreshReportScreenReq(void)
{
   RefreshReportScreenFlag = Execute;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ResetStatData
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Statistical Data Reset
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void ResetStatData(void)
{
//Data for Average of Stat Data
ProdFeedDurationLast[Scale1] = 0;
ProdFeedDurationSum[Scale1] = 0;
ProdFeedDurationAvg[Scale1] = 0;
FastFlowAvg[Scale1] = 0;
SlowFlowAvg[Scale1] = 0;
FastFlowSum[Scale1] = 0;
SlowFlowSum[Scale1] = 0;
StatDataCnt[Scale1] = 0;
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ResetSiloData
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/07/25
--  
--  Purpose           : This prcedure will reset all silo data
--                      
--  Value Parameters  : None 
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void ResetSiloData (void)
{
  int i;
  for (i = SiloDefault ; i <= SiloMax ; i++)
  {
   ProdSiloNoWeight[i] = 0;
  }

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ResetData
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Production Report Values Refresh
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void ResetData(bool OnlyAvgAndStdDev)
{
  NbrChecked[Scale1] = 0; 
  SumWeight[Scale1] = 0;
  SqareSumWeight[Scale1] = 0;
  AvgWeight[Scale1] = 0;
  StdDev[Scale1] = 0;
  SqareSumWeightString[Scale1] = "0.0";
  SumWeightString[Scale1] = "0.0";

  if(!OnlyAvgAndStdDev)
  {
   CheckedWeight[Scale1] = 0;
   ProdUnderWeightCnt[Scale1] = 0;
   ProdOverWeightCnt[Scale1] = 0;
   ProdAcceptUnitCnt[Scale1] = 0;
   ProdTotalUnitsCnt[Scale1] = 0;
   ProdLastChecked[Scale1] = 0;
   ProdLastWeight[Scale1] = 0;
   ProdLastSampled[Scale1] = "";
   ProdLastTolerance[Scale1] = "";
   ProdStdDev[Scale1] = 0;
   ProdAvgWeight[Scale1] = 0;
   //ProdTotalWeight[Scale1] = 0;
   ProdTotalWeight = 0;
   ProdBulkDuration[Scale1] = 0;
   ProdDribbleDuration[Scale1] = 0;
   ProdCycleDuration[Scale1] = 0 ;
   ProdCycleUnitsPerMin[Scale1] = 0;
   ProdTotalWeightOfShift = 0;       //added by namk 5/10/2018
   ProdTotalUnitOfShift = 0;         //added by namk 5/10/2018
   LastShiftTotalWeightLT = 0; //added by namk 5/10/2018
   LastShiftTotalUnitsLT = 0;  //added by namk 5/10/2018
   
   ProdTotalWeightOfHourly = 0;       //added by namk 5/10/2018
   ProdTotalUnitOfHourly = 0;         //added by namk 5/10/2018
   LastHourlyTotalWeightLT = 0; //added by namk 5/10/2018
   LastHourlyTotalUnitsLT = 0;  //added by namk 5/10/2018
   CurrentShiftUsageWeight = 0; //added by namk 10/10/2018
   
   WeightDisch = 0; //SADM2 2020
  } 

RefreshWeighingDataPopup(0);

ResetStatData();

ResetDataHMI = OFF;
PreSave_DataNoResetFlag = Execute;
RefreshReportScreenReq();
RefreshBatchScreenReq();
RefreshAutoScreenReq();
RefreshStatDataPopup();
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : ResetLifetimeData
--  Created by        : Jean-Pierre DorÃ©
--  Last modified on  : 2016/06
--  
--  Purpose           : Lifetime Production Report Reset Data
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/

void ResetLifetimeData(void)
{

ProdTotalWeighmentsLT[Scale1] = 0;
ProdTotalUnitsLT[Scale1] = 0;
ProdTotalWeightLT     = 0;
AccPulseTotalWeight = 0; //added by namk 11/10/2018 
PulseTotalWeightRemain = 0; //added by namk 21/03/2019
LastPulseTotalWeight = 0; //added by namk 11/10/2018 
ResetSiloData();//added by namk 25/9/2018
RefreshWeighingDataPopup(0);
ResetStatData();
PreSave_DataNoResetFlag = Execute;
ResetLifetimeDataHMI = OFF;
RefreshReportScreenReq();
RefreshBatchScreenReq();
RefreshAutoScreenReq();
RefreshStatDataPopup();
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
bool TargetWeightControlOnBulk(void)
{
  bool result;
  if(WP.TargetWeightIP > 0 && MC.WeighingMode == Bulk && WP.BulkModeIP == Ship && WP.TransferSilo == NO) result = ON;
  else  result = OFF;
  return result;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ReadPresentDateTime
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/09/26
--  
--  Purpose           : Read Present Date Time
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
string ReadPresentDateTime(void)
{
  string STR_PresentDateTime[22]; 
  //STR_PresentDateTime = concat(space(1),date," ",space(1), time);
  STR_PresentDateTime = concat(date," ",time);
  return STR_PresentDateTime;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ResetBatch
--  Created by        : Steve Santerre
--  Last modified on  : 2017/02/01
--  
--  Purpose           : Batch Values Reset
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void ResetBatch(void)
{
 Batch.TotalWeight     = 0;
 Batch.BeginTime       = ReadPresentDateTime();//namk Batch.MinAccepted     = 0;
 Batch.EndTime         = ReadPresentDateTime();//namk Batch.MaxAccepted     = 0;
 Batch.Residue         = 0;
 Batch.StdDev          = 0;
 Batch.Avg             = 0;
 Batch_TotalWeight     = 0; //SADM2 2020
 Batch.UnitsAccepted   = 0;
 Batch.UnitsDone       = 0;
 Batch.Count           = 0;
 Batch.UnderWeightCnt  = 0;
 Batch.OverWeightCnt   = 0;
 SampleOn = OFF;//added by namk
 ToleranceCheckOFF = OFF;//added by namk
 if(MC.WeighingMode == Batching || BulkByWeightON)//added by namk 24/9/2018
 {
 CleanOutWeightDone = OFF;//added by namk 28/9/2018
 SeqCleanOutWeight = stp_InitCleanOutWeight;//added by namk 28/9/2018
 SeqBatchingMode = stp_InitWeighment;//added by namk 24/9/2018
 ProdRemainWeight = WP.TargetWeightIP+DTFWeight;//added by namk 24/9/2018
 BatchEndReq = OFF;//added by namk
 BatchCancelled = OFF;//added by namk
 TotalWeightBatchTemp = 0;//added by namk
 Weighment2LastCnt = 0;//added by namk
 CutoffTemp = WP.Cutoff;//added by namk 27/9/2018
 TargetWeightBatchTemp = CutoffTemp+(WP.NominalWeight-WP.Cutoff);//added by namk
 ProdRemainBatch = WP.PresetBatch;//added by namk
 NumOfRegUnit = 0;//added by namk
 NumOfRemainUnit = 0;//added by namk
 }

 ResetBatchHMI = OFF;
 SaveBatchFlag = Execute;
 RefreshBatchScreenReq();
}

void LoadBatch(int Nbr)
{
 Batch.Name           = BatchNov.Name[Nbr];
 Batch.Details        = BatchNov.Details[Nbr];
 Batch.TotalWeight    = BatchNov.TotalWeight[Nbr];
 Batch_TotalWeight    = double(Batch.TotalWeight); //SADM2 2020
 Batch.BeginTime      = BatchNov.BeginTime[Nbr];
 Batch.EndTime        = BatchNov.EndTime[Nbr];
 Batch.Residue        = BatchNov.Residue[Nbr];
 Batch.StdDev         = BatchNov.StdDev[Nbr];
 Batch.Avg            = BatchNov.Avg[Nbr];
 Batch.UnitsAccepted  = BatchNov.UnitsAccepted[Nbr];
 Batch.UnitsDone      = BatchNov.UnitsDone[Nbr];
 Batch.Count          = BatchNov.Count[Nbr];
 Batch.UnderWeightCnt = BatchNov.UnderWeightCnt[Nbr];
 Batch.OverWeightCnt  = BatchNov.OverWeightCnt[Nbr];
 Batch.Preset         = BatchNov.Preset[Nbr];
 Batch.CountAll       = BatchNov.CountAll[Nbr];
}

/*********************************************** */
/*                                               */
/*  Init Main Variable                           */
/*                                               */
/* ********************************************* */
void InitVarMain(void)
{
bool result[2];

mode_step=0;
StepMsg = "";
CopyNovToLearnParam();
WeighPerUnitLoad();
Access_Level[0] = Level_OP;
Access_Level[1] = Level_SUP;
Access_Level[2] = Level_PT;
WeightDisplaySize=-1;
iQFeedSettledCnt=0;
IO_Change = OFF;
DischReqInputOn = ON;
step_slow_fill_percentage = 0.2;/* 20% */
offset_slow_fill_time = 0.050;
ScanMax = FillingTaskIntervalOff / 1000.0;
ScanMin = 0.01;
T_PRE[T_HeartbeatON]  = 2.5;
T_PRE[T_HeartbeatOFF] = 2.5;
T_PRE[T_ProdDataReady] = 1.0;
T_PRE[T_InitAlgo]      = 1.0;
Scale1Adm=1;
Scale2Adm=2;
iQStatData_String1 = "NO DATA";
iQStatData_String2 = "NO DATA"; 
iQStatData_String3 = "NO DATA"; 
iQStatData_String4 = "NO DATA"; 
iQStatData_String5 = "NO DATA"; 
iQStatData_String6 = "NO DATA"; 
iQStatData_String7 = "NO DATA";  
iQStatData_String8 = "NO DATA";  
iQStatData_String9 = "NO DATA"; 
StartFeedingDelay = 1.0;
InitiQSmart = ON;
InitiQFlash = ON;
FirstScanCheckLearn = ON;
iQFeedDone=OFF;
SwitchUnitFlag = Execute;
LoadProdVars();
SqareSumWeight[Scale1] = double(SqareSumWeightString[Scale1]);
SumWeight[Scale1]      = double(SumWeightString[Scale1]);
ServiceModeState = MONITOR_FUNCTION_ENABLE_ALL_FUNCTIONS;
KeyLockString = "";
KeyLockP = "";
KeyLockT = "";
KeyLockS = "";
KeyLockZ = "";
KeyLockI = "";

OpenConnection();
result[0]= iQReadCalFilterSize(SCALE_CHANNEL, SCALE_NUMBER,SMFilterSize);
result[1]= SetHiResolutionFactor(SCALE_CHANNEL, SCALE_NUMBER,HIRES_X10);

popen (ETHERNET_UNITRECORD_CHANNEL, ":2500"); //Open port for Unit Record "broadcast"
popen (ETHERNET_PRINTREPORT_CHANNEL,":9101"); //Open port for Print Report "broadcast"

DbDamaged.IO  = OFF;
DbDamaged.WPs = OFF;
DbDamaged.MPs = OFF;
DbDamaged.MCs = OFF;
DbDamaged.Flex = OFF;

MonthSaved = date[MT];


}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CheckOutputConfig
--  Created by        : Steve Santerre
--  Last modified on  : 2017/03
--                    ;
--  Purpose           : Check if 2 Ouptuts are configured with same number
--                    ; 
--                    ;             
--  Value Parameters  : 
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/
bool CheckOutputConfig(void)
{
int i,j,k,number[36];
bool Checked;
    Checked = ON;
    k=0;
    for (i=37;i<IO_ARRAY;i++)
    {
     if(IO_Enable[i])
     {
      number[k] = IO_Address[i];
      k++;
     }
    }
   for(i=0;i<=k-2;i++)
   {
    for(j=i+1;j<=k-1;j++)
    {
     if(number[j] == number[i])
     { 
        Checked = OFF;
        SystemErrorCode = "203 Two Outputs configured with same address";
        return(OFF);
      }
    }
   }    
  return(Checked);     
    

}   



/*********************************************** */
/*                                               */
/*  Service Mode Access Control: lock/unlock     */
/*                                               */
/* ********************************************* */
void ServiceModeControl(int DesiredState)
{
if(DesiredState != ServiceModeState)
 {
  setdisplayoption (DISPLAY_OPTION_MONITOR_FUNCTION_LOCK, DesiredState);
  ServiceModeState = DesiredState;
 }
} 

/*------------------------------------------------------------------------------- 
--  Procedure Name    : RefreshCurrentUser
--  Created by        : Steve Santerre
--  Last modified on  : 2016/11/15
--                    ;
--  Purpose           : Refresh Current User For Language change
--                    ; 
--                    ;             
--  Value Parameters  : 
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void RefreshCurrentUser(void)
{
  if (CurrentLevel == Level_None) CurrentUser  = lsub(TX_NONE);
  if (CurrentLevel == Level_OP) CurrentUser  = lsub(TX_USER3);
  if (CurrentLevel == Level_SUP) CurrentUser  = lsub(TX_USER2);
  if (CurrentLevel == Level_PT && UserForced) CurrentUser = lsub(TX_FORCED);
  if (CurrentLevel == Level_PT && !UserForced) CurrentUser = lsub(TX_USER1);
  widget_text   (ACCESS_LEVEL, concat (space(1), lsub(TX_ACCESS_USER),":", space(1) , CurrentUser));
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SaveCP2WP
--  Created by        : Steve Santerre
--  Last modified on  : 2016/11/15
--                    ;
--  Purpose           : Copy Single string into multi-strings
--                    ; 
--                    ;             
--  Value Parameters  : 
--  Variable Params   : Used For Algo Control Parameters to WPdb
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void SaveCP2WP(void)
{
  string tempstr[1024];
  int i,len;
  
      //Smart Fast Average Points  
        tempstr = WP.CPSmFastAvgPoints;
        i=0;
         do
          {
           len = length(tempstr);
           if (len > 63)
            {
             WPdb.CPSmFastAvgPoints[i] = left(tempstr,63);
             tempstr = right(tempstr,len-63);
            }
           else
            {
             WPdb.CPSmFastAvgPoints[i] = left(tempstr,len);
            }   
            i++;
          }
           while(len > 63);
         
      //Smart Slow Average Points  
        tempstr = WP.CPSmSlowAvgPoints;
        i=0;
         do
          {
           len = length(tempstr);
           if (len > 63)
            {
             WPdb.CPSmSlowAvgPoints[i] = left(tempstr,63);
             tempstr = right(tempstr,len-63);
            }
           else
            {
             WPdb.CPSmSlowAvgPoints[i] = left(tempstr,len);
            }   
            i++;
          }
           while(len > 63);
           
       //Smart Slow ITP Points    
        tempstr = WP.CPSmSlowItpPoints;
        i=0;
         do
          {
           len = length(tempstr);
           if (len > 63)
            {
             WPdb.CPSmSlowItpPoints[i] = left(tempstr,63);
             tempstr = right(tempstr,len-63);
            }
           else
            {
             WPdb.CPSmSlowItpPoints[i] = left(tempstr,len);
            }   
            i++;
          }
           while(len > 63);
       
       //Smart Switch Time
        WPdb.CPSmSwitchTime    = WP.CPSmSwitchTime;
        

      //Flash Fast Points 
       tempstr = WP.CPFlFastPoints;
       i=0;
         do
          {
           len = length(tempstr);
           if (len > 63)
            {
             WPdb.CPFlFastPoints[i] = left(tempstr,63);
             tempstr = right(tempstr,len-63);
            }
           else
            {
             WPdb.CPFlFastPoints[i] = left(tempstr,len);
            }   
            i++;
          }
           while(len > 63);
           
      
      //Flash Deviation Points    
       tempstr = WP.CPFlDeviationPoints;
       i=0;
         do
          {
           len = length(tempstr);
           if (len > 63)
            {
             WPdb.CPFlDeviationPoints[i] = left(tempstr,63);
             tempstr = right(tempstr,len-63);
            }
           else
            {
             WPdb.CPFlDeviationPoints[i] = left(tempstr,len);
            }   
            i++;
          }
           while(len > 63);
  
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : LoadWP2CP
--  Created by        : Steve Santerre
--  Last modified on  : 2016/11/15
--                    ;
--  Purpose           : Copy multi-strings into Single string 
--                    ; 
--                    ;             
--  Value Parameters  : 
--  Variable Params   : Used For Algo Control Parameters From WPdb
--  Side Effects      : 
--------------------------------------------------------------------------------*/
void LoadWP2CP(void)
{
string tempstr[1024];
  int i,len;
  
      //Smart Fast Average Points  
        tempstr = "";
        i=0;
         do
          {
           len = length(WPdb.CPSmFastAvgPoints[i]);
           if (len > 0)
            {
             tempstr = concat (tempstr,WPdb.CPSmFastAvgPoints[i]);
             i++;
            }
           if(i>=2) break;
          }
        while(len > 0);
        WP.CPSmFastAvgPoints = tempstr;
         
      //Smart Slow Average Points
      tempstr = "";
        i=0;
         do
          {
           len = length(WPdb.CPSmSlowAvgPoints[i]);
           if (len > 0)
            {
             tempstr = concat (tempstr,WPdb.CPSmSlowAvgPoints[i]);
             i++;
            }
           if(i>=2) break;
          }
        while(len > 0);
        WP.CPSmSlowAvgPoints = tempstr;  
        
           
       //Smart Slow ITP Points
       tempstr = "";
        i=0;
         do
          {
           len = length(WPdb.CPSmSlowItpPoints[i]);
           if (len > 0)
            {
             tempstr = concat (tempstr,WPdb.CPSmSlowItpPoints[i]);
             i++;
            }
           if(i>=8) break;
          }
        while(len > 0);
        WP.CPSmSlowItpPoints = tempstr;    
        
       
       //Smart Switch Time
        WP.CPSmSwitchTime    = WPdb.CPSmSwitchTime;
        

        //Flash Fast Points
      tempstr = "";
        i=0;
         do
          {
           len = length(WPdb.CPFlFastPoints[i]);
           if (len > 0)
            {
             tempstr = concat (tempstr,WPdb.CPFlFastPoints[i]);
             i++;
            }
           if(i>=2) break;
          }
        while(len > 0);
        WP.CPFlFastPoints = tempstr; 
       
           
      
      //Flash Deviation Points
      tempstr = "";
        i=0;
         do
          {
           len = length(WPdb.CPFlDeviationPoints[i]);
           if (len > 0)
            {
             tempstr = concat (tempstr,WPdb.CPFlDeviationPoints[i]);
             i++;
            }
           if(i>=4) break;
          }
        while(len > 0);
        WP.CPFlDeviationPoints = tempstr;    
       
}


/*********************************************** */
/*                                               */
/*  Clear iQFeed learning                        */
/*                                               */
/* ********************************************* */
void CleariQFeedLearn(void)
{
        //Smart Learning
        WPdb.CPSmFastAvgPoints[0] = "";
        WPdb.CPSmFastAvgPoints[1] = "";
        WPdb.CPSmSlowAvgPoints[0] = "";
        WPdb.CPSmSlowAvgPoints[1] = "";
        WPdb.CPSmSlowItpPoints[0] = "";
        WPdb.CPSmSlowItpPoints[1] = "";
        WPdb.CPSmSlowItpPoints[2] = "";
        WPdb.CPSmSlowItpPoints[3] = "";
        WPdb.CPSmSlowItpPoints[4] = "";
        WPdb.CPSmSlowItpPoints[5] = "";
        WPdb.CPSmSlowItpPoints[6] = "";
        WPdb.CPSmSlowItpPoints[7] = "";
        WPdb.CPSmSwitchTime       = 0 ;
          
        //Flash learning
        WPdb.CPFlFastPoints[0] = "";
        WPdb.CPFlFastPoints[1] = "";
        WPdb.CPFlDeviationPoints[0] = "";
        WPdb.CPFlDeviationPoints[1] = "";
        WPdb.CPFlDeviationPoints[2] = "";
        WPdb.CPFlDeviationPoints[3] = "";
    
     
}
     
/*********************************************** */
/*                                               */
/*  Top bar Page info                            */
/*                                               */
/* ********************************************* */
void TopBarInfo (void)
{
 string pageinfo[128], temp_len[128];
 int spacegap;
 
 //*** 128 characters available in TopBar Info with Clock included
  temp_len = trim(length(concat(lsub(TX_CONTROLLER_ID),space(2),lsub(TX_SCALE_TYPE),space(2),TX_PT_CONTROL_SW_VERS)));
  spacegap = (TOPBARCHARMAX - int(temp_len))/2;
  pageinfo=concat(space(spacegap), lsub(TX_CONTROLLER_ID),space(2),lsub(TX_SCALE_TYPE),space(2),TX_PT_CONTROL_SW_VERS,space(spacegap));
//  pageinfo=concat(space(48), lsub(TX_CONTROLLER_ID),space(2),lsub(TX_SCALE_TYPE),space(2),TX_PT_CONTROL_SW_VERS,space(48));
  setdisplayoption(DISPLAY_OPTION_STATUS_USER_TEXT, pageinfo);
}

/* ********************************************* */
/*                                               */
/*  Various display options                      */
/*                                               */
/* ********************************************* */
void DisplayOptions (void)
{
int i;

  setdisplayoption (DISPLAY_OPTION_KEYBOARD_BEEP_FREQUENCY, BEEP_OFF);
  setdisplayoption (DISPLAY_OPTION_APPLICATION_BEEP_FREQUENCY, BEEP_OFF); 
  setdisplayoption (DISPLAY_OPTION_SCALE_BUTTONS, SCALE_BUTTON_ZERO_SELECT);
  setdisplayoption (DISPLAY_OPTION_STATUS_WIDGETS, STATUS_WIDGET_USER_TEXT_TIME); 
  
  setdisplayoption (DISPLAY_OPTION_SCALE_LINE_FUNCTIONS, SCALE_LINE_BARGRAPH); 
  

  TopBarInfo(); 

i =STATUS_WIDGET_USER_TEXT + STATUS_WIDGET_DATE_TIME;
}


/* *********************************************************************** */
/*                                                                         */
/*   Navigation buttons creation    (Encapsulated)                         */
/*                                                                         */
/* *********************************************************************** */

void CreateNavigButtons (int MaxButtons, int TEST_BUTTON_1, bool forced )
{
 string msg_TEST_BUTTON[24], msg_i[10][2]; 
 int i%2.0, k;
   // GoTo buttons and Function buttons
  beginlayout(LAYOUT_TYPE_HBOX, FCT_BUTTON_EXT_GAP, FCT_BUTTON_DISTANCE_NAVIG); 

 TEST_BUTTON[0] = 0;
 TEST_BUTTON[0] = string(TEST_BUTTON_1);
 k = 0;

// Populate Array with # of enum ID
 for (i=0; i<MaxButtons; i++)
     {
     msg_i[i] = string(i);      
     
     TEST_BUTTON[i] = TEST_BUTTON[0]+i;

     } 
    
    if (MaxButtons > 0) createwidget (TEST_BUTTON[0], WIDGET_TYPE_TEXT_OUTPUT);
    if (MaxButtons > 1 && !forced) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH);
    if (MaxButtons > 1) createwidget (TEST_BUTTON[1], WIDGET_TYPE_TEXT_OUTPUT); 
    if (MaxButtons > 2) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 2) createwidget (TEST_BUTTON[2], WIDGET_TYPE_TEXT_OUTPUT); 
    if (MaxButtons > 3) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 3) createwidget (TEST_BUTTON[3], WIDGET_TYPE_TEXT_OUTPUT); 
    if (MaxButtons > 4) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 4) createwidget (TEST_BUTTON[4], WIDGET_TYPE_TEXT_OUTPUT); 
    if (MaxButtons > 5) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 5) createwidget (TEST_BUTTON[5], WIDGET_TYPE_TEXT_OUTPUT); 
    if (MaxButtons > 6) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 6) createwidget (TEST_BUTTON[6], WIDGET_TYPE_TEXT_OUTPUT); 
    if (MaxButtons > 7) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 7) createwidget (TEST_BUTTON[7], WIDGET_TYPE_TEXT_OUTPUT);
    if (MaxButtons > 8) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 8) createwidget (TEST_BUTTON[8], WIDGET_TYPE_TEXT_OUTPUT);
    if (MaxButtons > 9) createwidget (ID_STRETCH,WIDGET_TYPE_STRETCH); 
    if (MaxButtons > 9) createwidget (TEST_BUTTON[9], WIDGET_TYPE_TEXT_OUTPUT);

  k= 1;
  endlayout();  // End button line
}

/* *********************************************************************** */
/*                                                                         */
/*   Refresh Navigation buttons                                            */
/*                                                                         */
/* *********************************************************************** */

void DrawNavButtons (int Scrn_No, bool forced, string BTN1, string BTN2, string BTN3, string BTN4, string BTN5,
                                             string BTN6, string BTN7, string BTN8, string BTN9,   string BTN10 )       
                                     
{
int langvalue;
int ScrnNumbNav=Scrn_No, Scrn_IO=Scrn_No;

  //Navig buttons options:
  if (Scrn_No==SCREEN_RECIPE1 || Scrn_No==SCREEN_RECIPE2 || Scrn_No==SCREEN_RECIPE3 || Scrn_No==SCREEN_RECIPE4 || Scrn_No==SCREEN_IOCFG_IN1 || Scrn_No==SCREEN_IOCFG_IN2 || Scrn_No==SCREEN_IOCFG_IN3
      || Scrn_No==SCREEN_IOCFG_OUT1 || Scrn_No==SCREEN_IOCFG_OUT2 || Scrn_No==SCREEN_IOCFG_OUT3 || Scrn_No==SCREEN_IOTEST_IN1 || Scrn_No==SCREEN_IOTEST_IN2 
      || Scrn_No==SCREEN_IOTEST_IN3 || Scrn_No==SCREEN_IOTEST_OUT1 || Scrn_No==SCREEN_IOTEST_OUT2 || Scrn_No==SCREEN_IOTEST_OUT3 || Scrn_No==SCREEN_MP1 
      || Scrn_No==SCREEN_MP2 || Scrn_No==SCREEN_MP3 || Scrn_No==SCREEN_MP4 || Scrn_No==SCREEN_MC1 || Scrn_No==SCREEN_MC2 || Scrn_No==SCREEN_MC3 || Scrn_No==SCREEN_MC4 
      || Scrn_No== SCREEN_WPMANAGECOPY || Scrn_No== SCREEN_WPMANAGERENAME|| Scrn_No== SCREEN_WPMANAGEDELETE || Scrn_No== SCREEN_TDMANAGE
      || Scrn_No==SCREEN_FLEXIO_1 || Scrn_No==SCREEN_FLEXIO_2 || Scrn_No==SCREEN_FLEXIO_3) 
   ScrnNumbNav=SCREEN_RECIPES; 
  if (Scrn_No==SCREEN_REPORT || Scrn_No==SCREEN_GOTO || Scrn_No==SCREEN_ACCESS || Scrn_No==SCREEN_INFO || Scrn_No==SCREEN_BATCH) 
    ScrnNumbNav=NIL_SCREEN;

// begindraw();
    if ( tmpBTN1!=BTN1 || forced ) //Button #1
    {
      tmpBTN1  = BTN1;  
      widget_attribute (NAV_FCT_BUTTON_1, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
      widget_image (NAV_FCT_BUTTON_1,BTN_AUTO);
      if (Scrn_No == SCREEN_AUTOMATIC) widget_attribute (NAV_FCT_BUTTON_1, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
      
    }
    if ( tmpBTN2!=BTN2 || forced ) //Button #2  
    {
      tmpBTN2  = BTN2;  
      widget_attribute (NAV_FCT_BUTTON_2, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
      widget_image (NAV_FCT_BUTTON_2,BTN_RECIPE);
      if (Scrn_No == SCREEN_RECIPE1) widget_attribute (NAV_FCT_BUTTON_2, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
    }
    if ( tmpBTN3!=BTN3 || forced ) //Button #3  
    {
      tmpBTN3  = BTN3;  
      widget_attribute (NAV_FCT_BUTTON_3, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
      widget_image (NAV_FCT_BUTTON_3,BTN_REPORT);
      if (Scrn_No == SCREEN_REPORT) widget_attribute (NAV_FCT_BUTTON_3, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
    }
    
    if ( tmpBTN4!=BTN4 || forced ) //Button #3  
    {
      tmpBTN4  = BTN4;  
      widget_attribute (NAV_FCT_BUTTON_4, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
      widget_image (NAV_FCT_BUTTON_4,BTN_NAVIG);
      if (Scrn_No == SCREEN_GOTO) widget_attribute (NAV_FCT_BUTTON_4, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
    }
    if ( tmpBTN5!=BTN5 || forced ) //Button #5  
    {
      tmpBTN5 = BTN5;  
      widget_attribute (NAV_FCT_BUTTON_5, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
      widget_image (NAV_FCT_BUTTON_5,BTN_ALARM);
    }  
    
    
    switch (ScrnNumbNav)
    {
      case SCREEN_AUTOMATIC: 
                  // Button #6
                  // Image actualization directly by selection
              if ( tmpBTN6 != BTN6 || forced )
              {
                tmpBTN6  = BTN6;
                switch (Discharge_State)
                {
                   case DischPanOff:   widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_PAN_OFF);   break;
                   case DischPanOn:    widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_PAN_ON);    break; 
                   case DischMan:      widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_MAN);       break;
                   case DischUnder:    widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_UNDER);     break;
                   case DischOver:     widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_OVER);      break;
                   default :           widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_PAN_OFF);   break;    
                }
                widget_attribute (NAV_FCT_BUTTON_6, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
              }   
              if ( tmpBTN7!=BTN7 || forced ) //Button #7   
              {  
                tmpBTN7  = BTN7; 
                widget_image (NAV_FCT_BUTTON_7, BTN_OFF);
                widget_attribute (NAV_FCT_BUTTON_7, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);                
              }  
              if ( tmpBTN8!=BTN8 || forced ) //Button #8  
              {  
                tmpBTN8  = BTN8;  
                switch (Hopper_State)
                {
                   case HopperFill:     widget_image (NAV_FCT_BUTTON_8, HOPPER_FILL);   break;
                   case HopperEmpty:    widget_image (NAV_FCT_BUTTON_8, HOPPER_EMPTY);  break;
                   default :            widget_image (NAV_FCT_BUTTON_8, HOPPER_FILL);   break;
                }
                widget_attribute (NAV_FCT_BUTTON_8, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
              }    
              if ( tmpBTN9!=BTN9 || forced ) //Button #9  
              {  
                tmpBTN9  = BTN9;
                {
                   widget_image (NAV_FCT_BUTTON_9,BTN_START);
                   widget_attribute (NAV_FCT_BUTTON_9, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                }   
              }
              if ( tmpBTN10!=BTN10 || forced ) //Button #10   
              {  
                tmpBTN10  = BTN10;    
                widget_image (NAV_FCT_BUTTON_10, BTN_STOP);
                widget_attribute (NAV_FCT_BUTTON_10, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
              }
            break;
           
                          
      case SCREEN_RECIPES: 
              ScrnNumbNav =Scrn_No;
              if (Scrn_No==SCREEN_IOCFG_IN1 || Scrn_No==SCREEN_IOCFG_IN2 || Scrn_No==SCREEN_IOCFG_IN3 || Scrn_No==SCREEN_IOTEST_IN1 || Scrn_No==SCREEN_IOTEST_IN2 || Scrn_No==SCREEN_IOTEST_IN3) 
                  Scrn_IO =SCREEN_INPUT_PAGES;
              if (Scrn_No==SCREEN_IOCFG_OUT1 || Scrn_No==SCREEN_IOCFG_OUT2 || Scrn_No==SCREEN_IOCFG_OUT3 || Scrn_No==SCREEN_IOTEST_OUT1 || Scrn_No==SCREEN_IOTEST_OUT2 || Scrn_No==SCREEN_IOTEST_OUT3) 
                  Scrn_IO =SCREEN_OUTPUT_PAGES;
                  
              if ( tmpBTN6!=BTN6 || forced ) //Button #6   
              {  
                tmpBTN6  = BTN6; 
                widget_attribute (NAV_FCT_BUTTON_6, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                switch (Scrn_IO) 
                {
                   case SCREEN_RECIPE1:        widget_image (NAV_FCT_BUTTON_6, BTN_BATCH);     break;
                   case SCREEN_RECIPE2:        widget_image (NAV_FCT_BUTTON_6, BTN_BATCH);     break;
                   case SCREEN_RECIPE3:        widget_image (NAV_FCT_BUTTON_6, BTN_BATCH);     break;
                   case SCREEN_RECIPE4:        widget_image (NAV_FCT_BUTTON_6, BTN_BATCH);     break;
                   case SCREEN_MP1:            widget_image (NAV_FCT_BUTTON_6, BTN_TIMEDATE); break;
                   case SCREEN_INPUT_PAGES:    widget_image (NAV_FCT_BUTTON_6, BTN_OUTPUT);   break;
                   case SCREEN_OUTPUT_PAGES:   widget_image (NAV_FCT_BUTTON_6, BTN_INPUT);    break;
                   case SCREEN_WPMANAGECOPY:   widget_image (NAV_FCT_BUTTON_6, BTN_COPY);     break;
                   case SCREEN_WPMANAGERENAME: widget_image (NAV_FCT_BUTTON_6, BTN_COPY);     break;
                   case SCREEN_WPMANAGEDELETE: widget_image (NAV_FCT_BUTTON_6, BTN_COPY);     break;
                   default :                   widget_image (NAV_FCT_BUTTON_6, BTN_NIL_GRAYOUT); 
                                               widget_attribute (NAV_FCT_BUTTON_6, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE); break;
                }
                                          
              } 
              if ( tmpBTN7!=BTN7 || forced ) //Button #7   
              {  
                tmpBTN7  = BTN7;  
                widget_attribute (NAV_FCT_BUTTON_7, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                switch (Scrn_No)
                {
                  case SCREEN_IOTEST_IN1:     widget_image (NAV_FCT_BUTTON_7, BTN_NIL_GRAYOUT);   break;
                  case SCREEN_IOTEST_OUT1:    widget_image (NAV_FCT_BUTTON_7, BTN_NIL_GRAYOUT);   break;
                  case SCREEN_WPMANAGECOPY:   widget_image (NAV_FCT_BUTTON_7, BTN_RENAME);   break;
                  case SCREEN_WPMANAGERENAME: widget_image (NAV_FCT_BUTTON_7, BTN_RENAME);   break;
                  case SCREEN_WPMANAGEDELETE: widget_image (NAV_FCT_BUTTON_7, BTN_RENAME);   break;
                  default :                   widget_image (NAV_FCT_BUTTON_7, BTN_NIL_GRAYOUT); 
                                              widget_attribute (NAV_FCT_BUTTON_7, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE); break;
                  
                }
              }
              if ( tmpBTN8!=BTN8 || forced ) //Button #8  
              {  
                tmpBTN8  = BTN8;  
                widget_attribute (NAV_FCT_BUTTON_8, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                switch (Scrn_No)
                {
                  case SCREEN_WPMANAGECOPY:   widget_image (NAV_FCT_BUTTON_8, BTN_DEL);      break;
                  case SCREEN_WPMANAGERENAME: widget_image (NAV_FCT_BUTTON_8, BTN_DEL);      break;
                  case SCREEN_WPMANAGEDELETE: widget_image (NAV_FCT_BUTTON_8, BTN_DEL);      break;
                  default :                   widget_image (NAV_FCT_BUTTON_8, BTN_NIL_GRAYOUT); 
                                              widget_attribute (NAV_FCT_BUTTON_8, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE); break;                  
                  
                }
              }    
              if ( tmpBTN9!=BTN9 || forced ) //Button #9  
              {  
                tmpBTN9  = BTN9;
                widget_attribute (NAV_FCT_BUTTON_9, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                switch (ScrnNumbNav)
                {   
//                  case SAVE_PAGES:      widget_image (NAV_FCT_BUTTON_9, BTN_SAVE);     break;
                  case SCREEN_RECIPE2:      widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_RECIPE3:      widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_RECIPE4:      widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_MP2:          widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_MP3:          widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_MP4:          widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_MC2:          widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_MC3:          widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_MC4:          widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOCFG_IN2:    widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOCFG_IN3:    widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOTEST_IN2:   widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOTEST_IN3:   widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOCFG_OUT2:   widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOCFG_OUT3:   widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOTEST_OUT2:  widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_IOTEST_OUT3:  widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_TDMANAGE:     widget_image (NAV_FCT_BUTTON_9, BTN_SAVE);     break;
                  case SCREEN_FLEXIO_2:     widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  case SCREEN_FLEXIO_3:     widget_image (NAV_FCT_BUTTON_9, BTN_PREV);     break;
                  default :                 widget_image (NAV_FCT_BUTTON_9, BTN_NIL_GRAYOUT); 
                                            widget_attribute (NAV_FCT_BUTTON_9, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE); break;
                }  
              }
              if ( tmpBTN10!=BTN10 || forced ) //Button #10   
              {  
                tmpBTN10  = BTN10;
                widget_attribute (NAV_FCT_BUTTON_10, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                switch (ScrnNumbNav)
                {   
                  case SCREEN_RECIPE1:      widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_RECIPE2:      widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_RECIPE3:      widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_MP1:          widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_MP2:          widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_MP3:          widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_MC1:          widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_MC2:          widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_MC3:          widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOCFG_IN1:    widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOCFG_IN2:    widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOTEST_IN1:   widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOTEST_IN2:   widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOCFG_OUT1:   widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOCFG_OUT2:   widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOTEST_OUT1:  widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_IOTEST_OUT2:  widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_TDMANAGE:     widget_image (NAV_FCT_BUTTON_10, BTN_REFRESH);  break;
                  case SCREEN_FLEXIO_1:     widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  case SCREEN_FLEXIO_2:     widget_image (NAV_FCT_BUTTON_10, BTN_NEXT);     break;
                  default :                 widget_image (NAV_FCT_BUTTON_10, BTN_NIL_GRAYOUT); 
                                            widget_attribute (NAV_FCT_BUTTON_10, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE); break;
                }    
              }              
            break;
      
      case SCREEN_FAULT: 
              if ( tmpBTN6!=BTN6 || forced ) //Button #6   
              {  
                tmpBTN6  = BTN6; 
                widget_image (NAV_FCT_BUTTON_6, BTN_NIL_GRAYOUT); 
                widget_attribute (NAV_FCT_BUTTON_6, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);               
              }  
              if ( tmpBTN7!=BTN7 || forced ) //Button #7   
              {  
                tmpBTN7  = BTN7; 
                widget_image (NAV_FCT_BUTTON_7, BTN_FIRST_PAGE); 
                widget_attribute (NAV_FCT_BUTTON_7, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);               
              }  
              if ( tmpBTN8!=BTN8 || forced ) //Button #8   
              {  
                tmpBTN8  = BTN8; 
                widget_image (NAV_FCT_BUTTON_8, BTN_PAGE_UP);
                widget_attribute (NAV_FCT_BUTTON_8, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);                
              }    
              if ( tmpBTN9!=BTN9 || forced ) //Button #9   
              {  
                tmpBTN9  = BTN9; 
                widget_image (NAV_FCT_BUTTON_9, BTN_PAGE_DOWN);
                widget_attribute (NAV_FCT_BUTTON_9, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);                
              }
              if ( tmpBTN10!=BTN10 || forced ) //Button #10   
              {  
                tmpBTN10  = BTN10;    
                widget_image (NAV_FCT_BUTTON_10, BTN_LAST_PAGE);
                widget_attribute (NAV_FCT_BUTTON_10, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
              }
            break;
              
      case NIL_SCREEN:
              if ( tmpBTN6!=BTN6 || forced ) //Button #6   
              {  
                tmpBTN6  = BTN6; 
                widget_attribute (NAV_FCT_BUTTON_6, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                if (Scrn_No == SCREEN_REPORT)   widget_image (NAV_FCT_BUTTON_6, BTN_BATCH);
                else if(Scrn_No == SCREEN_GOTO) widget_image (NAV_FCT_BUTTON_6, BTN_BATCH);
                else  {widget_image      (NAV_FCT_BUTTON_6, BTN_NIL_GRAYOUT); widget_attribute (NAV_FCT_BUTTON_6, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);}             
              } 
              if ( tmpBTN7!=BTN7 || forced ) //Button #7   
              {  
                tmpBTN7  = BTN7; 
                widget_attribute (NAV_FCT_BUTTON_7, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                if (Scrn_No == SCREEN_REPORT || Scrn_No == SCREEN_BATCH) widget_image      (NAV_FCT_BUTTON_7, BTN_PRINT);
                else  {widget_image (NAV_FCT_BUTTON_7, BTN_NIL_GRAYOUT); widget_attribute (NAV_FCT_BUTTON_7, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);}
              }  
              if ( tmpBTN8!=BTN8 || forced ) //Button #8  
              {  
                tmpBTN8  = BTN8;  
                if (Scrn_No == SCREEN_REPORT || Scrn_No == SCREEN_BATCH)
                {
                 widget_image (NAV_FCT_BUTTON_8, BTN_WEIGHING_DATA);
                 widget_attribute (NAV_FCT_BUTTON_6, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
                }
                else
                {   
                 widget_image (NAV_FCT_BUTTON_8, BTN_NIL_GRAYOUT);
                 widget_attribute (NAV_FCT_BUTTON_8, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
                } 

              }    
              if ( tmpBTN9!=BTN9 || forced ) //Button #9  
              {  
                tmpBTN9  = BTN9;    
                widget_image      (NAV_FCT_BUTTON_9, BTN_NIL_GRAYOUT);
                widget_attribute (NAV_FCT_BUTTON_9, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);
              }
              if ( tmpBTN10!=BTN10 || forced ) //Button #10   
              {  
                tmpBTN10  = BTN10; 
                widget_attribute (NAV_FCT_BUTTON_10, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);   
                if (Scrn_No == SCREEN_REPORT || Scrn_No == SCREEN_BATCH) widget_image      (NAV_FCT_BUTTON_10, BTN_REPORTRESET);
                else  {widget_image      (NAV_FCT_BUTTON_10, BTN_NIL_GRAYOUT); widget_attribute (NAV_FCT_BUTTON_10, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE);}
              }
              break;  
                                                              
    }
 
// enddraw();
}                     


/* *********************************************************************** */
/*                                                                         */
/*   Draw Generic Buttons in GoTo page buttons                             */
/*                                                                         */
/* *********************************************************************** */
                                    
void DrawGenericButtons (int Scrn_No, bool forced, int MaxButtons, int TEST_BUTTON_1, string BTN1, string BTN2, string BTN3, string BTN4, 
                                                      string BTN5, string BTN6, string BTN7, string BTN8, string BTN9, string BTN10)

{
 string msg_TEST_BUTTON[24], msg_i[10][2]; 
 int i%2.0, k;


BTN[0] = BTN1; BTN[1] = BTN2; BTN[2] = BTN3;BTN[3] = BTN4; BTN[4] = BTN5; 
BTN[5] = BTN6; BTN[6] = BTN7; BTN[7] = BTN8; BTN[8] = BTN9; BTN[9] = BTN10;

 msg_TEST_BUTTON = string(TEST_BUTTON_1);
 for (i=0; i<MaxButtons; i++)
 {
 TEST_BUTTON[i] = 0;
 msg_i[i] = "";
 }
 TEST_BUTTON[0] = msg_TEST_BUTTON;
 for (i=0; i<MaxButtons; i++)
     {
       msg_i[i] = string(i);
       
       TEST_BUTTON[i] = TEST_BUTTON[0]+i;
       
       if ( MaxButtons > i)
       {
         if ( tmpBTN[i] != BTN[i] || forced || fscan)
         {
           tmpBTN[i]  = BTN[i];  
           widget_image (TEST_BUTTON[i],BTN[i]);
         }
         else tmpBTN[i]  = "";
       }  
     }   
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : Priority_Loop
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/09
--  
--  Purpose           : Compare highest priority in stack
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 

int Priority_Loop (int Priority)
{
int i, Highest,Start_i, End_i;
     Highest = ((Priority +1) * 32);
     Start_i = 32-1;
     End_i = 0;
     for (i=Start_i; i>=End_i; i--)
     {  
      if (bit(i, Fault_Type[Priority]) && i<Highest)
      {
        Highest = i+(Priority*32);
        
      } 
     } 
      if (Highest == ((Priority +1) * 32)) Highest = -1;
      return (Highest);
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : FaultLight_Set
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/08
--  
--  Purpose           :  Display management of fault icon in upper right of screen
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void FaultLight_Set (void)
{
FaultLightSetFlag = Execute;
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CurMode_Set
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/21
--  
--  Purpose           :  Display management of mode icon in upper right of screen
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void CurMode_Set (void)
{
 CurModeSetFlag = Execute;
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SetFaultTime
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/12/11
--  
--  Purpose           : Get system time and fill fault list string array
--                    ;   
--                    ;               
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/  
void SetFaultTime (void)
{
  FaultMsgTime[Fault_Pointer] = concat (space(1), time, space(1), "/", space(1), date);
}  

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ShiftFaultArray
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/12/10
--  
--  Purpose           : Shifts the values of the string array down one position
--                    ;   
--                    ;               
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/  
void ShiftFaultArray (void)
{
int i, Start_i, End_i;

  Start_i = FltArrayMax-1;
  End_i   = 0;
  for (i=Start_i; i>=End_i; i--)
  {
    if (i > End_i)
    {
      FaultMessage[i] = FaultMessage[i-1]; 
      FaultClrMsg[i]  = FaultClrMsg[i-1];
      FaultMsgTime[i] = FaultMsgTime[i-1];
    }  
  }

}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : MessageDisplayOutput
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/12/
--  
--  Purpose           : Display current message to status line on bottom of 
--                    ; Automatic page  
--                    ;               
--  Value Parameters  : Msg: Text message to display,  Fault_No: Active fault #
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/
bool MessageDisplayOutput(string Msg, int Fault_No)
{
string backcolor[12], TempColor[12], Flt_Msg_Str[FltStringLen],TextAdd[255];
int i, Temp_Loop, High_Msg, Flt_Msg_Int,
    PRIORITY = Fault_No / 32, //Division
    BIT      = Fault_No % 32; //Modulo 


  if ((Fault_No==Step_Message)) 
  {
    StepMsg  = trim(Msg);

  }

  if ((Fault_No!=Step_Message)) 
  {

     High_Msg = Priority_Loop(PRIORITY);

  }

  Flt_Msg_Int = Fault_No;
  Flt_Msg_Str = trim(Msg);

 begindraw();
  if (High_Msg != -1)
  {
      if (PRIORITY == FLT_GEN)
      {
        if (OldMsg!=Msg || AutoPage_FS)
        {
          if(High_Msg == FltG_SystemError)
           TextAdd = trim(Fault_TxtOutput);
          else
           TextAdd = "";
          
          MessageColor = "red";
          HiResColor = "red";
          MessageText = concat ( trim(Fault_Txt[High_Msg]),space(1),TextAdd);
            
          OldMsg= trim(Msg); 
          AutoPage_FS = OFF;
        }
      }
      else
      if (PRIORITY == FLT_BLK && Fault_Type[FLT_GEN]==0)
      {
        if (OldMsg!=Msg || AutoPage_FS)
        {
          MessageColor = "red";
          HiResColor = "red";
          MessageText = concat ( trim(Fault_Txt[High_Msg])); 
                
          OldMsg= trim(Msg);
          AutoPage_FS = OFF;
        }
      }
      else
      if (PRIORITY == FLT_STOP && Fault_Type[FLT_GEN]==0 && Fault_Type[FLT_BLK]==0)
      {
        if (OldMsg!=Msg || AutoPage_FS)
        {
        
          MessageColor = "red";
          HiResColor = "red";
          MessageText = concat ( trim(Fault_Txt[High_Msg]));
      
          OldMsg= trim(Msg);
          AutoPage_FS = OFF;
        }
      }
      else
      if (PRIORITY == FLT_WRN && Fault_Type[FLT_GEN]==0 && Fault_Type[FLT_BLK]==0 && Fault_Type[FLT_STOP]==0)
      {
        if (OldMsg!=Msg && PRIORITY!=Step_Message || AutoPage_FS)
        {  
          if(High_Msg == FltW_SystemWarning)
           TextAdd = trim(Fault_TxtOutput);
          else
           TextAdd = "";
            
            MessageColor = "yellow";
            HiResColor = "yellow";
            MessageText = concat ( trim(Fault_Txt[High_Msg]),space(1),TextAdd);
    
            OldMsg= trim(Msg);
            AutoPage_FS = OFF;
        }
      }
  }
  
      if (Fault_Type[FLT_GEN] == 0 && Fault_Type[FLT_BLK] == 0 && Fault_Type[FLT_STOP] == 0 && Fault_Type[FLT_WRN] == 0)
      {
        MessageColor = CL_PT_GRAY;
        HiResColor = CL_PT_GRAY;
        MessageText = concat ( trim(StepMsg));
        
        AutoPage_FS = OFF;
      }
  
  if(MessageTextTemp != MessageText)
  {
   widget_background     (MESSAGE_DISPLAY, MessageColor);
   widget_text           (MESSAGE_DISPLAY, MessageText);
   widget_background     (HIRESWEIGHT, HiResColor);
   MessageTextTemp = MessageText;
  } 
  
 enddraw();
  High_Msg_MDisplay = High_Msg;
  StepMsg_MDisplay  = trim(StepMsg);
  Msg_MDisplay      = trim(Msg);
  PRIORITY_MDisplay = PRIORITY;
  FaultLight_Set();
    
return(ON);  
}


/* *********************************************************************** */
/*                                                                         */
/*   Message display                                                         */
/*                                                                         */
/* *********************************************************************** */

// Draw message line only when it is necessary !
// Each display command needs a lot of CPU load !
void MessageDisplay(string Msg, int Fault_No /*string backcolor*/ )
{
 if(Fault_No == 128)
  {
   MessageOutStp = trim (Msg);
   Fault_NoOutStp = trim(Fault_No);
  }
 else
  {
   MessageOutFault = trim (Msg);
   Fault_NoOutFault = trim(Fault_No);
   DisplayFault = ON;
  } 
 Message_DisplayFlag   = Execute;
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Msg_Display_Refresh
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/12/14
--  
--  Purpose           : Refresh the message display in Automatic page
--                    ;  
--                    ;              
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/  
void Msg_Display_Refresh (void)
{
begindraw();
 if(!LT_GEN && !LT_BLK && !LT_STOP && !LT_WRN)
 {
  if (StepMsg != "" )
  {
   MessageColor = CL_PT_GRAY;
   HiResColor = CL_PT_GRAY;
   MessageText = concat ( trim(StepMsg));
  }
  else
  {
   MessageColor = "White";
   HiResColor = "White";
   MessageText = "";
  }
  
  if(MessageTextTemp != MessageText)
  {
   widget_text           (MESSAGE_DISPLAY, MessageText);
   widget_background     (MESSAGE_DISPLAY, MessageColor);
   widget_background     (HIRESWEIGHT, HiResColor);
   MessageTextTemp = MessageText;
  } 
 }
enddraw();
}  

/*------------------------------------------------------------------------------- 
--  Procedure Name    : FaultState
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/07
--  
--  Purpose           : 
--                    ; Fault_Priority[0] = Fault_Gen, [1] = Fault_Block, [2] = Fault_Stop,  
--                    ; [3] = Fault_Warn,              
--  Value Parameters  :
--  Variable Params   : Fault_No = Fault message enum 
--  Side Effects      : 
--------------------------------------------------------------------------------*/  
bool FaultState(int Fault_No)
{
int PRIORITY , BIT;
bool test;
 PRIORITY = Fault_No / 32; //Division
 BIT      = Fault_No % 32; //Modulo

    return (bit(BIT, Fault_Type[PRIORITY])); 
}



/*------------------------------------------------------------------------------- 
--  Procedure Name    : FaultHandler
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/07
--                    ;
--  Purpose           : 
--                    ; Fault_Priority[0] = Fault_Gen, [1] = Fault_Block, [2] = Fault_Stop,
--                    ; [3] = Fault_Warn,            
--  Value Parameters  : 
--  Variable Params   : Fault_No = Fault message enum 
--  Side Effects      : 
--------------------------------------------------------------------------------*/  
void FaultHandlerOutput(int Fault_No,string Fault_TxtAdd)
{
int PRIORITY , BIT, i;
string Flt_Letter[1], Flt_No[3],FaultString[255];
 PRIORITY = Fault_No / 32; //Division
 BIT      = Fault_No % 32; //Modulo
 
    setbit(BIT, Fault_Type[PRIORITY]);
    
    // Light up corresponding fault to fault type lamp  
    for (i=0; i<4; i++)
    {
      LT_GEN  = (Fault_Type[0] != 0);
      LT_BLK  = (Fault_Type[1] != 0);
      LT_STOP = (Fault_Type[2] != 0);
      LT_WRN  = (Fault_Type[3] != 0);
    }
    FaultString = concat (Fault_Txt[Fault_No],space(1),Fault_TxtAdd);
    MessageDisplay(FaultString,Fault_No);
    Fault_Status = Fault_No;
    

    
    Flt_No = trim(string(Fault_No));
    if (Fault_No < 32)
    {
     Flt_Letter = "G";
     if (Fault_No < 10) Flt_No = concat("0",Flt_No);
    }
     else if (Fault_No < 64) Flt_Letter = "B";
      else if (Fault_No < 96) Flt_Letter = "S";
       else if (Fault_No < 128 )Flt_Letter = "W";
    
    if (Fault_Pointer > 99) Fault_Pointer = 0;
    if (Fault_Pointer < 0) Fault_Pointer = FltArrayMax-1;    
    FaultMessage[Fault_Pointer] = concat(trim(Flt_Letter),trim(Flt_No),space(1), FaultString); 
    FaultClrMsg[Fault_Pointer]  = OFF;
    SetFaultTime();
    Fault_Pointer--;
    
    if(LT_GEN || LT_BLK || LT_STOP)
     if(!IOTestFlag)
      Output_ON (O_Fault);
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : FaultResetReq
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/07
--  
--  Purpose           : Reset all fault bits and messages request
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void FaultResetReq(void)
{
FaultResetFlag = Execute;
}
/*------------------------------------------------------------------------------- 
--  Procedure Name    : FaultReset
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/07
--  
--  Purpose           : Reset all fault bits and messages 
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void FaultReset (void)
{
int i;
 
 OldMsg = ""; 

if (!FaultResetFlag)
{

 if (Fault_Pointer > 99) Fault_Pointer = 0;
 if (Fault_Pointer < 0) Fault_Pointer = FltArrayMax-1;
 FaultMessage[Fault_Pointer] = lsub(TX_FAULT_RESET);
 FaultClrMsg[Fault_Pointer]  = ON;
 SetFaultTime(); 
 Fault_Pointer--;
}

 // Light up corresponding fault to fault type lamp 
 for (i=0; i<4; i++)
 {
   Fault_Type[i] = 0;
   LT_GEN  = (Fault_Type[FLT_GEN]  != 0);
   LT_BLK  = (Fault_Type[FLT_BLK]  != 0);
   LT_STOP = (Fault_Type[FLT_STOP] != 0);
   LT_WRN  = (Fault_Type[FLT_WRN]  != 0);
 }
 
 FaultLight_Set(); 
 Output_OFF(O_Fault);
 Msg_Display_Refresh();
 IOError = OFF;
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : ReadMaxNumbOfIO
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : This function is Used To Read the Maximum 
--                      Number of IO configured in Service Mode
--  Value Parameters  :
--  Variable Params   : return maxio
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
int ReadMaxNumbOfIO (void)
{
int i, maxio=0, disabledIO;
string s1[9][10];
string s2[9][10];

  disabledIO = 9;
  for (i=1; i<=8; i++)
  {
    s1[i-1] = readparameter (concat("BIO",adj(i,1,0)),"Type");   
    if (s1[i-1] == "0" && disabledIO ==9) disabledIO = i;
    if (s1[i-1] == "1") PIMoffset = (i-1) * 8;
    if(i>disabledIO) writeparameter (concat("BIO",adj(i,1,0)),"Type",adj(0,1,0));
  }
   for (i=1; i<=8; i++) s2[i-1] =  readparameter (concat("BIO",adj(i,1,0)),"Type");
  if (s1[0] == "0")
    maxio = 0;
  else 
    maxio = ((disabledIO-1)*8)-1;  // Attention: read I/O´s from 0 to 7 and not from 1 to 8 
  return (maxio);
}




/* ****************************************************************** */
/*Insertion of a mode status and fault status for Demo purposes       */
/* ****************************************************************** */
void CreateModeFltDisplay (void)
{
  createwidget (MODE_BOX, WIDGET_TYPE_TEXT_OUTPUT);
    widget_background      (MODE_BOX,   "White" );
    widget_foreground      (MODE_BOX,   CL_PT_WHITE);
    widget_fontsize        (MODE_BOX,   FT_MEDIUM_SIZE);
    widget_size_policy     (MODE_BOX,   SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
    widget_text_alignment  (MODE_BOX,   WIDGET_TEXT_ALIGN_VCENTER );
    widget_dimensions      (MODE_BOX,   96, 45);
    widget_maximum_size    (MODE_BOX,   96, 45);
    widget_image           (MODE_BOX,   BTN_BLANK);
    widget_content_margins (MODE_BOX,   2,0,0,0);
    widget_attribute       (MODE_BOX,   WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE); 

  createwidget (FAULT_BOX, WIDGET_TYPE_TEXT_OUTPUT);
    widget_background      (FAULT_BOX,  "White" );
    widget_foreground      (FAULT_BOX,  CL_PT_WHITE);
    widget_fontsize        (FAULT_BOX,  FT_MEDIUM_SIZE);
    widget_size_policy     (FAULT_BOX,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
    widget_text_alignment  (FAULT_BOX,  WIDGET_TEXT_ALIGN_VCENTER );
    widget_dimensions      (FAULT_BOX,  96, 45);
    widget_maximum_size    (FAULT_BOX ,  96, 45);
    widget_image           (FAULT_BOX,  BTN_BLANK);
    widget_content_margins (FAULT_BOX,  0,0,2,0); 
    widget_attribute       (FAULT_BOX,  WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE); 
}

/* *********************************************************************** */
/*                                                                         */
/*   Create items Section                                                  */
/*                                                                         */
/* *********************************************************************** */

/* *********************************************** */
/*   Create Header                                 */                                                                 
/* *********************************************** */
void CreateHeader (int id, int width, int height, string image, bool align_Hcenter, string text, int font_size, int widget_lock)
{
  createwidget (id, WIDGET_TYPE_TEXT_OUTPUT);
    widget_size_policy    (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);  
    widget_dimensions     (id,  width, height);    
    widget_fontsize       (id,  font_size);       
    widget_foreground     (id,  CL_PT_BLUE);
    if (align_Hcenter)
    { 
    widget_text_alignment (id,  WIDGET_TEXT_ALIGN_CENTER );
    }
    else
    {
    widget_text_alignment (id,  WIDGET_TEXT_ALIGN_VCENTER );
    }
    widget_text           (id,  text );
    widget_background     (id,  CL_PT_WHITE );
    widget_fontface       (id,  FT_RTC_BOLD); 
    widget_image          (id,   image);
    if (widget_lock) widget_maximum_size   (id,  width, height);  
}

/* *********************************************** */
/*   Create Prompt field                           */                                                            
/* *********************************************** */
void CreatePromptField(int id, string fg_color, bool bold, string text, int font_size, int width, int height, int margin, int widget_lock )
{
  createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);     
    widget_size_policy  (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);//SIZE_POLICY_MINIMUM
    widget_foreground   (id,  fg_color); 
    widget_background   (id,  CL_WHITE);
    widget_fontsize     (id,  font_size); 
    widget_dimensions   (id,  width, height);
  if (widget_lock) widget_maximum_size (id,  width, height);  
    widget_text         (id,  text);
    
  if (bold) widget_fontface  (id,  FT_RTC_BOLD);
  else widget_fontface  (id,  FT_RTC);
  
    widget_content_margins (id, margin,0,0,0);     
}

/* *********************************************** */
/*   Create Prompt field Throughput                */                                                            
/* *********************************************** */
void CreatePromptField2(int id, string fg_color, bool bold, string text, int font_size,int alignment, int width, int height, int margin, int widget_lock )
{
  createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);     
    widget_size_policy  (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);//SIZE_POLICY_MINIMUM
    widget_foreground   (id,  fg_color); 
    widget_background   (id,  CL_WHITE);
    widget_fontsize     (id,  font_size); 
    widget_text_alignment (id,  alignment);
    widget_dimensions   (id,  width, height);
  if (widget_lock) widget_maximum_size (id,  width, height);  
    widget_text         (id,  text);
    
  if (bold) widget_fontface  (id,  FT_RTC_BOLD);
  else widget_fontface  (id,  FT_RTC);
  
    widget_content_margins (id, margin,0,0,0);     
}



/* *********************************************** */
/*   Create Unapproved weight display Header       */                                                            
/* *********************************************** */
void CreateUnapprovedHeader(void)
{
createwidget (UNAPPROVED_HEADER, WIDGET_TYPE_TEXT_OUTPUT);
          widget_dimensions      (UNAPPROVED_HEADER,  800, 33); //FCT_BUTTON_WIDTH, FCT_BUTTON_HEIGHT);      
          widget_fontsize        (UNAPPROVED_HEADER,  7);
          widget_size_policy     (UNAPPROVED_HEADER,  SIZE_POLICY_MINIMUM, SIZE_POLICY_MINIMUM);     //SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_MINIMUM      
          widget_foreground      (UNAPPROVED_HEADER,  CL_PT_WHITE);
          widget_background      (UNAPPROVED_HEADER,  CL_PT_BLUE );
          widget_fontface        (UNAPPROVED_HEADER,  FT_RTC_BOLD); 
          widget_content_margins (UNAPPROVED_HEADER, 0,0,0,0);
}

/* *********************************************** */
/*   Create Output Text field                      */                                                            
/* *********************************************** */
void CreateOutputTextField (int id, string text, int width, int height, int widget_lock)
{
  createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);
    widget_size_policy  (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);   //SIZE_POLICY_MINIMUM
    widget_fontsize     (id,  FT_STANDARD_SIZE);
    widget_background   (id,  CL_WHITE);
    widget_dimensions   (id,  width, height);
  if (widget_lock) widget_maximum_size (id,  width, height);  
    widget_text         (id,  text);       
    widget_text         (id,  text);
}



/* *********************************************** */
/*   Create Output Data field                      */                                                            
/* *********************************************** */
void CreateOutputDataField (int id, int font_face, int font_size, int alignment, int width, int height, bool widget_lock )
{
  createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);
    widget_size_policy  (id,  SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_FIXED);//SIZE_POLICY_MINIMUMEXPANDING
    widget_background   (id,  CL_WHITE); 
    widget_foreground   (id,  CL_PT_BLUE);
    widget_fontsize       (id,  font_size); 
    widget_fontface       (id,  font_face);
    widget_text_alignment (id,  alignment);
    widget_dimensions     (id,  width, height);
  if (widget_lock) widget_maximum_size     (id,  width, height);
//    widget_content_margins (id, 0,0,0,0); 
}

/* *********************************************** */
/*   Create Unit field                             */                                                            
/* *********************************************** */
void CreateUnitField (int id, int font_face, int font_size, string text, int width, int height, int widget_lock )
{
  createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);
    widget_size_policy    (id,  SIZE_POLICY_MINIMUM, SIZE_POLICY_FIXED);
    widget_background     (id,  CL_WHITE); 
    widget_foreground     (id,  CL_PT_BLUE);
    widget_fontsize       (id,  font_size); 
    widget_fontface       (id,  font_face); 
    widget_text_alignment (id,  WIDGET_TEXT_ALIGN_VCENTER_L);//WIDGET_TEXT_ALIGN_VCENTER_L
    widget_text           (id,  text);
    widget_dimensions     (id,  width, height);
  if (widget_lock) widget_maximum_size     (id,  width, height);
//    widget_content_margins (id, 0,0,0,0); 
}

/* *********************************************** */
/*   Create Input field                            */                                                            
/* *********************************************** */
void CreateInputField (int id, int font_size, int font_face, int format, int len, int decs, int align_center, string text, int width, int height, bool widget_lock )
{
  createwidget(id, WIDGET_TYPE_TEXT_INPUT);
    widget_size_policy    (id,  SIZE_POLICY_MINIMUM, SIZE_POLICY_FIXED);
    widget_fontsize       (id,  font_size);
    widget_fontface       (id,  font_face);
    widget_format         (id,  format, len, decs);
    widget_label          (id,  text); 
  if (align_center)  widget_text_alignment (id,  WIDGET_TEXT_ALIGN_CENTER);
    widget_dimensions     (id,  width, height);
  if (widget_lock) widget_maximum_size     (id,  width, height);
    widget_content_margins (id, 0,0,0,0); 

}

/* *********************************************** */
/*   Create Checkbox selection field               */                                                            
/* *********************************************** */
void CreateCheckBoxField (int id, int font_face, int alignment, int sel_1, string text_1, int sel_2, string text_2)
{
  createwidget(id, WIDGET_TYPE_CHECKBOX);
    widget_size_policy    (id,  SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_MINIMUM);
    widget_fontsize       (id,  FT_STANDARD_SIZE); 
    widget_fontface       (id,  font_face);
    widget_text_alignment (id,  alignment);
    
}

/* *********************************************** */
/*   Create ON/OFF Box         field               */                                                            
/* *********************************************** */
void CreateOnOffBoxField (int id, int font_face, int alignment, bool image, string image_ON, string image_OFF)
{
  createwidget (id, WIDGET_TYPE_ONOFF);
    
    widget_size_policy    (id,  SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_MINIMUM);
    widget_fontsize       (id,  FT_STANDARD_SIZE); 
    widget_fontface       (id,  font_face);
    widget_text_alignment (id,  alignment);
    widget_content_margins (id, 0,0,0,0); 
    
    if (image)
    {
      widget_image_index (id, image_ON, 1);
      widget_image_index (id, image_OFF, 0);    
    }
}

/* *********************************************** */
/*   Create Language List field selection          */                                                            
/* *********************************************** */
void CreateLanguageListField (int id, int font_face, int alignment, string text, int width, int height, int widget_lock)
{
  createwidget(id, WIDGET_TYPE_LIST);
    widget_size_policy     (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);   
    widget_fontsize        (id,  FT_STANDARD_SIZE);
    widget_fontface        (id,  font_face);
    widget_dimensions      (id,  width, height);
    widget_text_alignment  (0,WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER);
  if (widget_lock) widget_maximum_size     (id,  width, height);       
    widget_text            (id,  text);
    widget_content_margins (id, 0,0,0,0);
}
/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateComboBoxField
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Creation of Combo box selection field  
--                    : 
--  Value Parameters  :
--  Variable Params   : id = entity enum number ex: RECIPE_SEARCH_ID 
                      : sel_x = integer value, text_x string to be displayed in drop down list
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateComboBoxField (int id, int font_size, int font_face, string text_1, string text_2, string text_3, string text_4, string text_5, int width, int height, int widget_lock)
{
  createwidget(id, WIDGET_TYPE_COMBOBOX);
    widget_size_policy  (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
    widget_fontsize     (id,  font_size); 
    widget_fontface     (id,  font_face); 
    widget_text         (id,  text_1, 0);
    widget_text         (id,  text_2, 1);
    if ( text_3!="" )
      widget_text       (id,  text_3, 2);
    if ( text_4!="" )
      widget_text       (id,  text_4, 3);
    if ( text_5!="" )
      widget_text       (id,  text_5, 4);  
    widget_dimensions   (id,  width, height); 
  if (widget_lock) widget_maximum_size     (id,  width, height);    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateComboBoxFieldForWeighingMode
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/06/29
--  
--  Purpose           : Creation of Combo box selection field for 6 items  
--                    : 
--  Value Parameters  :
--  Variable Params   : id = entity enum number ex: RECIPE_SEARCH_ID 
                      : sel_x = integer value, text_x string to be displayed in drop down list
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateComboBoxFieldForWeighingMode (int id, int font_size, int font_face, string text_1, string text_2, string text_3, string text_4, string text_5, string text_6, int width, int height, int widget_lock)
{
  createwidget(id, WIDGET_TYPE_COMBOBOX);
    widget_size_policy  (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
    widget_fontsize     (id,  font_size); 
    widget_fontface     (id,  font_face); 
    widget_text         (id,  text_1, 0);
    widget_text         (id,  text_2, 1);
    if ( text_3!="" )
      widget_text       (id,  text_3, 2);
    if ( text_4!="" )
      widget_text       (id,  text_4, 3);
    if ( text_5!="" )
      widget_text       (id,  text_5, 4);
    if ( text_6!="" )
      widget_text       (id,  text_6, 5);  
    widget_dimensions   (id,  width, height); 
  if (widget_lock) widget_maximum_size     (id,  width, height);    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateComboBoxFeeder
--  Created by        : Steve Santerre
--  Last modified on  : 06/09/2018 by Kittipong Namvichai
--                      Modified to show Feeder only type G   
--  Purpose           : Creation of Combo box selection field  
--                    : 
--  Value Parameters  :
--  Variable Params   : id = entity enum number ex: RECIPE_SEARCH_ID 
                      : sel_x = integer value, text_x string to be displayed in drop down list
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateComboBoxFeeder (int id, int font_size, int font_face,int width, int height, int widget_lock)
{
int i,j;
    InitFeederList();
    createwidget(id, WIDGET_TYPE_COMBOBOX);
    widget_size_policy  (id,  SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_FIXED);//SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_MINIMUM); 
    widget_fontsize     (id,  font_size); 
    widget_fontface     (id,  font_face);
    j=0;
    for(i=FeederG;i<FeederGHS;i++) 
     {
      if(Feeder.Enable[i]) 
       {
        widget_text(id,  Feeder.Name[i],j);
        Feeder.ListNbr[j] = i;
        Feeder.ListItem[i] = j;
        j++;
       } 
      
     }  
    widget_dimensions   (id,  width, height); 
  if (widget_lock) widget_maximum_size     (id,  width, height);    
}

/* *********************************************** */
/*   Create invisible spacing field               */                                                            
/* *********************************************** */
void CreateSpacingField (int id, string fg_color, int font_size, string text)
{
createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);                                              
  widget_size_policy (id, SIZE_POLICY_MAXIMUM, SIZE_POLICY_MINIMUM); 
  widget_foreground  (id, fg_color);
  widget_fontsize    (id, font_size); 
  widget_text        (id, text);
}

/* *********************************************** */
/*   Create PT Logo in Header                      */                                                            
/* *********************************************** */
void CreatePTLogoHeader (void)
{
  CreateHeader         (LOGO_BOX, WD_PTLOGO, HT_PTLOGO, BTN_LOGO_PTC, align_vcenter, "" , FT_MEDIUM_SIZE, widget_unlocked);
  widget_image         (LOGO_BOX,   BTN_LOGO_PTC);
  widget_attribute     (LOGO_BOX, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE);
  widget_maximum_size  (LOGO_BOX, 140, 45); 
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Arg2Bool
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/03/02
--  
--  Purpose           : Transforms string value to boolean
--                      
--  Value Parameters  :
--  Variable Params   : arg: string input value 
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool Arg2Bool (string arg)
{
  if (int (arg) == 0)
    return (false);
  else
    return (true);
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : FormaTime
--  Created by        : Kittipong Namvichai
--  Last modified on  : 2018/10/05
--  
--  Purpose           : Returns the entered value within time format 
--                      
--  Value Parameters  :
--  Variable Params   : entry = keyboard entry 
--  Side Effects      : 
--------------------------------------------------------------------------*/
string FormatTime(string Entry)
{ 
  string result[5];
  if(length(Entry)==5)result = Entry;
  else if(length(Entry)== 1 || length(Entry) == 2) result = "00:00";
  else if(length(Entry)== 3 && Entry[digit3] == ':') result = "00:00";
  else if(length(Entry)== 3 && Entry[digit1] == ':') result = "00:00";
  else if(length(Entry)== 3 && Entry[digit2] == ':' && int(Entry[digit3]) < six)  result = "0"+Entry+"0"; 
  else if(length(Entry)== 3 && Entry[digit2] == ':' && Entry[digit3] >= six)result = "0"+sub(Entry,0,2)+"0"+Entry[digit3];   
  else if(length(Entry)== 4 && Entry[digit3] == ':' && Entry[digit4] <= five) result =  Entry + "0";    
  else if(length(Entry)== 4 && Entry[digit3] == ':' && Entry[digit3] >=six)result = sub(Entry,0,3)+"0"+Entry[digit4];    
  else if(length(Entry)== 4 && Entry[digit2] == ':' && Entry[digit3] <six)result =  "0"+Entry;     
  return result;
}

/* *********************************************************************** */
/*                                                                         */
/*   Refresh Weight Display per specific screen                            */
/*                                                                         */
/* *********************************************************************** */
void WeightDisplayFull(bool forced)
{
         if (WeightDisplaySize != WgtDisplFull || forced)
         {
             weightdisplay (WEIGHT_DISPLAY_FULL);
             setdisplayoption (DISPLAY_OPTION_SCALE_BUTTONS, SCALE_BUTTON_ZERO_SELECT);
             setdisplayoption (DISPLAY_OPTION_SHOW_WIDGET, DISPLAY_WIDGET_HEAD_LINE);
             setdisplayoption (DISPLAY_OPTION_SCALE_LINE_FUNCTIONS, SCALE_LINE_BARGRAPH);
             WeightDisplaySize = WgtDisplFull; 
         }                 
}
void WeightDisplaySmall (bool forced)
{
        if (WeightDisplaySize != WgtDisplSmall || forced)
         {
             weightdisplay (WEIGHT_DISPLAY_SMALL);
             setdisplayoption (DISPLAY_OPTION_SCALE_BUTTONS, SCALE_BUTTON_ZERO_SELECT);
             WeightDisplaySize = WgtDisplSmall;
         }           
}
void WeightDisplayInfo (bool forced)
{
         if (WeightDisplaySize != WgtDisplInfo || forced)
         {
             weightdisplay (WEIGHT_DISPLAY_INFO);
             WeightDisplaySize = WgtDisplInfo;
         }    
}             

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshRemoteDisplay
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Force Weight display refresh when remote display connected  
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshRemoteDisplay (int WgtDisplay)
{
   DisplayOptions ();
   ButtonDisplayRefreshed[Current_Screen] = OFF;
   FaultLightSetFlag = Execute;
   CurModeSetFlag = Execute;
   switch (WgtDisplay)
   { 
     case WEIGHT_DISPLAY_FULL:  WeightDisplayFull(Force_Display);  break;
     case WEIGHT_DISPLAY_SMALL: WeightDisplaySmall(Force_Display); break;
     case WEIGHT_DISPLAY_INFO:  WeightDisplayInfo(Force_Display);  break;
    break;                    
   }
  
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Force_Screen_Req
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/20
--  
--  Purpose           : Request to force selected screen
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : Scrn_No = Screen you want to force, 
--                    : Display_Size = Weight display size in forced screen
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void Force_Screen_Req (int Scrn_No, int Display_Size)
{
      ForceScreen_ScrnNo      = Scrn_No;
      ForceScreen_DisplaySize = Display_Size;
      ForceScreen_Req         = ON;
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : Force_Screen_Req
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/20
--  
--  Purpose           : Request to force selected screen while loading correct size display for the page
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : Scrn_No = Screen you want to force, Display_Size = Weight display size in forced screen
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void Force_Screen (void)
{
 switch (ForceScreen_DisplaySize)
      {
        case LARGE:   WeightDisplayFull(No_Forcing);
                    break;
                    
        case SMALL:   WeightDisplaySmall(No_Forcing);
                    break;
      } 
    ForceScreen_Req         = OFF;
}          

/*------------------------------------------------------------------------- 
--  Procedure Name    : Clear_ButtonControlRefreshed
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/21
--  
--  Purpose           : Clears the ButtonDisplayRefreshed[LAST_SCREEN] bool
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void  Clear_ButtonControlRefreshed (void)
{
int i;

  for (i=0; i<LAST_SCREEN; i++)
  {
    ButtonDisplayRefreshed[i] = OFF;
  
  }
}
/*------------------------------------------------------------------------- 
--  Procedure Name    : Clear_ModeRefreshed
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/11/21
--  
--  Purpose           : Clears the ModeRefreshed[LAST_SCREEN] bool
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void  Clear_ModeRefreshed (void)
{
int i;

  for (i=0; i<LAST_SCREEN; i++)
  {
    ModeRefreshed[i] = OFF;
  
  }
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshGrayout
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08
--  
--  Purpose           : This function is called to Grayout the unused Inputs
--                      in WP, MP & MC Databases
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void RefreshGrayout(void)
{
bool flexIOoff,UserSupOrLess;
bool MC_Grayout_18_Mem;

UserSupOrLess = CurrentLevel <= Level_SUP;

flexIOoff = (!(IO_Enable[O_FlexIO_1] || IO_Enable[O_FlexIO_2]));

//WP screen #1
Recipe_Grayout[2] = ON;
Recipe_Grayout[3] = (WP.FeedAlgoType != FeedStd && WP.FeedAlgoType != FeediQSim);
Recipe_Grayout[4]= (BulkOnTime[Scale1] ||(WP.FeedAlgoType != FeedStd && WP.FeedAlgoType != FeediQSim));  
Recipe_Grayout[5] = WP.FeedAlgoType != FeedStd || WP.BulkMode == ByTime ;
Recipe_Grayout[6]= !BulkOnTime[Scale1];
Recipe_Grayout[7] = ON;
Recipe_Grayout[8] = ON;
Recipe_Grayout[9] = OFF;
Recipe_Grayout[12]= !(MC.WeighingMode == Batching);


//WP screen #2
Recipe_Grayout[13]= !(MC.WeighingMode == FeedRateControl || MC.WeighingMode == Monitoring);
Recipe_Grayout[14]= !(MC.WeighingMode == FeedRateControl || MC.WeighingMode == Monitoring);
Recipe_Grayout[15]= !(((MC.WeighingMode == Bulk && WP.BulkModeIP == Ship)|| (MC.WeighingMode == Batching && WP.PresetBatch == 0)) && (SeqModeManager == stp_STOP_MODE || SeqModeManager == stp_OFF_MODE)); 
Recipe_Grayout[16]= !(MC.WeighingMode == Bulk && WP.BulkModeIP == Ship && (SeqModeManager == stp_STOP_MODE || SeqModeManager == stp_OFF_MODE));
Recipe_Grayout[17]= !(MC.WeighingMode == Bulk && SeqModeManager == stp_OFF_MODE); 
Recipe_Grayout[18]= (MC.WeighingMode != Batching);
Recipe_Grayout[19]= !(MC.WeighingMode == FeedRateControl);
Recipe_Grayout[20]= !(MC.WeighingMode == FeedRateControl);
Recipe_Grayout[21]=!IO_Enable[O_VibrDischDoor];
Recipe_Grayout[23] = !(WP.FeedAlgoType == FeedStd) && !(WP.FeedAlgoType == FeediQSim);
Recipe_Grayout[24]=0;   

//WP screen #3
Recipe_Grayout[25] = OFF;
Recipe_Grayout[26] = OFF;
//Recipe_Grayout[27] = OFF;
Recipe_Grayout[28] = !(MC.WeighingMode == Bulk);
Recipe_Grayout[29] = !(WP.TransferSilo == ON && MC.WeighingMode == Bulk);
Recipe_Grayout[30] = !(MC.WeighingMode == TimeControl);
Recipe_Grayout[31]= (CurrentLevel < Level_SUP || SeqModeManager != stp_OFF_MODE);
Recipe_Grayout[32] = (SeqModeManager != stp_OFF_MODE);
Recipe_Grayout[33]= !(MC.WeighingMode == Bulk && SeqModeManager == stp_OFF_MODE);
Recipe_Grayout[34]= !(MC.WeighingMode == Bulk && SeqModeManager == stp_OFF_MODE);
Recipe_Grayout[35]= !(WP.FeedAlgoType == FeedStd);
Recipe_Grayout[36]= !(MC.WeighingMode == Monitoring || (MC.WeighingMode == Bulk && WP.BulkModeIP == Ship && 
                    (WP.TransferSilo == YES || WP.TransferSilo == NO)) && (SeqModeManager == stp_STOP_MODE || SeqModeManager == stp_OFF_MODE));//modified by namk 25/9/2018

//WP screen #4
Recipe_Grayout[37] = flexIOoff;
Recipe_Grayout[38] = flexIOoff;
Recipe_Grayout[39] = !IO_Enable[O_FlexIO_3];
Recipe_Grayout[43] = flexIOoff;
Recipe_Grayout[44] = flexIOoff;
Recipe_Grayout[45] = !(MC.WeighingMode == Batching);


//MP screen #1
MP_Grayout[4]= MC.OIML; 
MP_Grayout[5]= MC.OIML; 
MP_Grayout[6] =  0;                                                                                                
MP_Grayout[7] = (!IO_Enable[I_DischDoorClose]);
MP_Grayout[9] = (!IO_Enable[I_FeedGateClose]);//namk I_CatchGateOpen
MP_Grayout[10] = ON;
MP_Grayout[11]= 0;//commented by namk 18/9/2018

                 
//MP screen #2
MP_Grayout[13]= 0;
MP_Grayout[14]= 0;
MP_Grayout[15]= 0;
MP_Grayout[16]= 0;


 
MP_Grayout[19]= 0;
MP_Grayout[20]= 0;
MP_Grayout[21]= 0;
MP_Grayout[22]= (!(WP.FeedAlgoType == FeedStd));
MP_Grayout[23]= 0;

//MP screen #3
MP_Grayout[25]= flexIOoff;
MP_Grayout[26]= flexIOoff;
MP_Grayout[27]= !IO_Enable[O_FlexIO_3];

MP_Grayout[31]= flexIOoff;
MP_Grayout[32]= flexIOoff;

//MC screen #1
if(WP.FeedAlgoType == FeedStd || WP.FeedAlgoType == FeediQSim) {MC_Grayout[1]= 0;
                                                                MC_Grayout[2]= 0;}
else                                                           {MC_Grayout[1]= 1;
                                                                MC_Grayout[2]= 1;}
                                
MC_Grayout[4]= (!IO_Enable[O_HopFillReq]);

MC_Grayout[5] = UserSupOrLess;
MC_Grayout[6] = UserSupOrLess;

MC_Grayout[7] = ON;
MC_Grayout[8]= ON || UserSupOrLess;
MC_Grayout[9] = UserSupOrLess;
MC_Grayout[10]= ON; //Always leave Language #1 grayout - Fixed to English

                

//MC screen #2
MC_Grayout[13]= (UserSupOrLess || PrintByassed); /* Production report port */ 
MC_Grayout[14]= (UserSupOrLess || PrintByassed); /* Unit record print config */   
if(WP.FeedAlgoType == FeedStd || WP.FeedAlgoType == FeediQSim) {MC_Grayout[15]= 0;}
else                                                           {MC_Grayout[15]= 1;}
MC_Grayout[17]= (UserSupOrLess || PrintByassed); /* Print port continuous output */ 
MC_Grayout[18]= UserSupOrLess || MC.PortETHCfg != ETHFctReportToPrinter;

if(MC_Grayout_18_Mem != MC_Grayout[18])
{
 MC_Grayout_18_Mem = MC_Grayout[18];
 RefreshMCScreen_No = SCREEN_MC2;
} 

MC_Grayout[19]=(!IO_Enable[I_DischDoorClose]) || UserSupOrLess;
MC_Grayout[20] = UserSupOrLess;
MC_Grayout[22] = UserSupOrLess;

//MC screen #3
MC_Grayout[27]=1; // PT Password - Always Grayout
MC_Grayout[28] = UserSupOrLess;
MC_Grayout[29] = UserSupOrLess;
MC_Grayout[30] = UserSupOrLess;
MC_Grayout[33] = UserSupOrLess;
MC_Grayout[34] = UserSupOrLess;
MC_Grayout[35] = UserSupOrLess;
MC_Grayout[36] = UserSupOrLess;
 if(Current_Screen >= SCREEN_RECIPE1 && Current_Screen <= SCREEN_RECIPE4)  RefreshWPScreen_No = Current_Screen;                     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : find_db
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/06
--  
--  Purpose           : Controls the synchro when loading a database  
--                      
--  Value Parameters  :
--  Variable Params   : db = the database you want to access
--  Side Effects      : 
--------------------------------------------------------------------------*/
int find_db (int db)
{ 
int err,cnt=0,cntmax=10;
 while (Db_InUse[db] && cnt < cntmax) 
 {
  cnt++;
  if(cnt > cntmem) cntmem = cnt;
  delay (0.05);
 }
 if (cnt >= cntmax)
  { 
    if(db == WP_Db)     SystemErrorCode = "311 Database: WP access request timeout";
    if(db == MP_Db)     SystemErrorCode = "312 Database: MP access request timeout";
    if(db == MC_Db)     SystemErrorCode = "313 Database: MC access request timeout";
    if(db == FlexIO_Db) SystemErrorCode = "314 Database: FlexIO access request timeout";
  }   
 else
 {
   Db_InUse[db] = true;
   switch (db)
   {
    case WP_Db : err = find(WPdb);
                break; 

    case MP_Db : err = find(MPdb);
                break;
                
    case MC_Db : err = find(MCdb);
                break;
    
    case FlexIO_Db : err = find(FlexIO);
                break;            
                      
   }  
   Db_InUse[db] = false;
   return(err);
 } 

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : save_db
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/06
--  
--  Purpose           : Controls the synchro when saving a database  
--                      
--  Value Parameters  :
--  Variable Params   : db = the database you want to access
--  Side Effects      : 
--------------------------------------------------------------------------*/
int save_db (int db)
{ 
int err,cnt=0,cntmax=10;
string errorcode[3];
 while (Db_InUse[db] && cnt < cntmax) 
 {
  cnt++;
  if(cnt > cntmem) cntmem = cnt;
  delay (0.05);
 }
 if (cnt >= cntmax)
  {
    if(db == WP_Db)     SystemErrorCode = "311 Database: WP access request timeout";
    if(db == MP_Db)     SystemErrorCode = "312 Database: MP access request timeout";
    if(db == MC_Db)     SystemErrorCode = "313 Database: MC access request timeout";
    if(db == FlexIO_Db) SystemErrorCode = "314 Database: FlexIO access request timeout";
  }   
 else
 {
   Db_InUse[db] = true;
   switch (db)
   {
    case WP_Db : err = insert(WPdb);
                break; 

    case MP_Db : err = insert(MPdb);
                break;
                
    case MC_Db : err = insert(MCdb);
                break;
    
    case FlexIO_Db : err = insert(FlexIO);
                break;                  
   }  
   Db_InUse[db] = false;
   return(err);
 } 

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadDb2WP
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2019/04/04 (By NAMK)
--  
--  Purpose           : Load WPdb Database to WP Struc
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int LoadDb2WP (void)
{
int err;

err = find(WPdb);
WPdb.UnderWeight = 0;
WPdb.OverWeight = 0;
WPdb.Overfill = 0;
/* "Need logic to skip the writing of the following if err = 1 or 2"*/
   //WP Page1
   WP.No                  = WPdb.No;                 
   WP.Name                = WPdb.Name;
   WP.NominalWeight       = WPdb.NominalWeight;
   WP.Overfill            = WPdb.Overfill;          
   WP.Cutoff              = WPdb.Cutoff;
   WP.BulkCutoff          = WPdb.BulkCutoff;
   WP.DFTime              = WPdb.DFTime;
   WP.BFTime              = WPdb.BFTime;      
   WP.UnderWeight         = WPdb.UnderWeight;
   WP.OverWeight          = WPdb.OverWeight;
   WP.DischargeWeight     = WPdb.DischargeWeight;
   WP.DischargeTime       = WPdb.DischargeTime;
   WP.FeedDelayTime       = WPdb.FeedDelayTime;
   WP.WeighmentsPerUnit   = WPdb.WeighmentsPerUnit; 
   //WP Page2
   WP.FeedRateLowLimit    = WPdb.FeedRateLowLimit;  
   WP.FeedRateHighLimit   = WPdb.FeedRateHighLimit;
   WP.TargetWeightIP      = WPdb.TargetWeightIP; 
   WP.CleanOutWeightIP    = WPdb.CleanOutWeightIP;
   WP.BulkModeIP          = WPdb.BulkModeIP;
   WP.PresetBatch         = WPdb.PresetBatch;
   WP.PresetFeedRate1     = WPdb.PresetFeedRate1;
   WP.PresetFeedRate2     = WPdb.PresetFeedRate2;        
   WP.VibratoryDischDoors = WPdb.VibratoryDischDoors;  
   WP.ZeroingOpen         = WPdb.ZeroingOpen;
   WP.SlowCycleEnd        = WPdb.SlowCycleEnd;
   WP.ProductCode         = WPdb.ProductCode;
   //WP Page3
   WP.TopUpOFFTime        = WPdb.TopUpOFFTime;
   WP.TopUpONTime         = WPdb.TopUpONTime;
   WP.PulseTotalWeight    = WPdb.PulseTotalWeight;
   WP.SiloNo              = WPdb.SiloNo;
   WP.SiloDest            = WPdb.SiloDest; 
   WP.PresetCycleTime     = WPdb.PresetCycleTime;              
   WP.FeedAlgoType        = WPdb.FeedAlgoType; 
   WP.Unit                = WPdb.Unit;
   WP.TransferSilo        = WPdb.TransferSilo; 
   WP.FlowThroughAfterCleanout   = WPdb.FlowThroughAfterCleanout;
   WP.BulkMode            = WPdb.BulkMode;
   WP.DTF                 = WPdb.DTF;
   //WP Page4
   WP.FlexCounter         = WPdb.FlexCounter;  
   WP.FlexSP1             = WPdb.FlexSP1;
   WP.FlexSP2             = WPdb.FlexSP2;
   WP.FlexT1              = WPdb.FlexT1;
   WP.FlexT2              = WPdb.FlexT2;
   WP.ReportType          = WPdb.ReportType;
   //Report Page
   WP.CountAll            = WPdb.CountAll;   
   WP.ProdSiloNo          = WPdb.ProdSiloNo;
   //Remain from Net 
   WP.CatchGateDelay      = WPdb.CatchGateDelay;
   WP.MinFeeding          = WPdb.MinFeeding; 
   WP.MaxFeeding          = WPdb.MaxFeeding;
   WP.RegMinFeeding       = WPdb.RegMinFeeding;
   WP.RegMaxFeeding       = WPdb.RegMaxFeeding;         
   WP.ActuatorPos         = WPdb.ActuatorPos;
   WP.EnabledScale        = WPdb.EnabledScale; 
   
   if(WPdb.ProdTotalUnitsCnt[Scale1] >= (WPdb.ProdUnderWeightCnt[Scale1]  + WPdb.ProdOverWeightCnt[Scale1]))
    {
     WP.ProdUnderWeightCnt_1  = WPdb.ProdUnderWeightCnt[Scale1];
     WP.ProdOverWeightCnt_1   = WPdb.ProdOverWeightCnt[Scale1];
     WP.ProdTotalUnitsCnt_1   = WPdb.ProdTotalUnitsCnt[Scale1];
     //WP.ProdTotalWeight_1     = WPdb.ProdTotalWeight[Scale1];
     WP.ProdTotalWeight_1     = WPdb.ProdTotalWeight; 
     
    }
   else
    {
     WP.ProdUnderWeightCnt_1           = 0; 
     WPdb.ProdUnderWeightCnt[Scale1]   = 0;
     WP.ProdOverWeightCnt_1            = 0;
     WPdb.ProdOverWeightCnt[Scale1]    = 0;
     WP.ProdTotalUnitsCnt_1            = 0;
     WPdb.ProdTotalUnitsCnt[Scale1]    = 0;
     WP.ProdTotalWeight_1              = 0;
     //WPdb.ProdTotalWeight[Scale1]      = 0;
     WPdb.ProdTotalWeight      = 0;
     SaveWPFlag = Execute;
    }   
   
   if(WPdb.ProdTotalUnitsCnt[Scale2] >= (WPdb.ProdUnderWeightCnt[Scale2]  + WPdb.ProdOverWeightCnt[Scale2]))
    {
     WP.ProdUnderWeightCnt_2  = WPdb.ProdUnderWeightCnt[Scale2];
     WP.ProdOverWeightCnt_2   = WPdb.ProdOverWeightCnt[Scale2];
     WP.ProdTotalUnitsCnt_2   = WPdb.ProdTotalUnitsCnt[Scale2];
     //WP.ProdTotalWeight_2     = WPdb.ProdTotalWeight[Scale2];
     WP.ProdTotalWeight_2     = WPdb.ProdTotalWeight; 
    }
   else
    {
     WP.ProdUnderWeightCnt_2           = 0; 
     WPdb.ProdUnderWeightCnt[Scale2]   = 0;
     WP.ProdOverWeightCnt_2            = 0;
     WPdb.ProdOverWeightCnt[Scale2]    = 0;
     WP.ProdTotalUnitsCnt_2            = 0;
     WPdb.ProdTotalUnitsCnt[Scale2]    = 0;
     WP.ProdTotalWeight_2              = 0;
     //WPdb.ProdTotalWeight[Scale2]      = 0;
     WPdb.ProdTotalWeight     = 0;
     SaveWPFlag = Execute;
    } 
    
   LoadWP2CP();
   
   if(WP.WeighmentsPerUnit < 1) 
   {
    WP.WeighmentsPerUnit = 1;
    SaveWPFlag = Execute;
   }
   
return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : SaveWP2Db
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Save WP Struc to WPdb Database  
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int SaveWP2Db (void)
{
int err;

   if(WPdb.NominalWeight != WP.NominalWeight || WPdb.Unit != WP.Unit) 
     {
     CreateWPNameListFlag = Execute;
     }

/* "Need logic to skip the writing of the following if err = 1 or 2"*/
   //WP Page1
   WPdb.No                  = WP.No;                 
   WPdb.Name                = WP.Name;
   WPdb.NominalWeight       = WP.NominalWeight;
   WPdb.Overfill            = WP.Overfill;          
   WPdb.Cutoff              = WP.Cutoff;
   WPdb.BulkCutoff          = WP.BulkCutoff;
   WPdb.DFTime              = WP.DFTime;
   WPdb.BFTime              = WP.BFTime;
   WPdb.UnderWeight         = WP.UnderWeight;
   WPdb.OverWeight          = WP.OverWeight;
   WPdb.DischargeWeight     = WP.DischargeWeight;
   WPdb.DischargeTime       = WP.DischargeTime;
   WPdb.FeedDelayTime       = WP.FeedDelayTime;
   WPdb.WeighmentsPerUnit   = WP.WeighmentsPerUnit;
   
   
   //WP Page2
   WPdb.FeedRateLowLimit    = WP.FeedRateLowLimit; 
   WPdb.FeedRateHighLimit   = WP.FeedRateHighLimit; 
   WPdb.TargetWeightIP      = WP.TargetWeightIP;
   WPdb.CleanOutWeightIP    = WP.CleanOutWeightIP; 
   WPdb.BulkModeIP          = WP.BulkModeIP; 
   WPdb.PresetBatch         = WP.PresetBatch; 
   WPdb.PresetFeedRate1     = WP.PresetFeedRate1;
   WPdb.PresetFeedRate2     = WP.PresetFeedRate2;
   WPdb.VibratoryDischDoors = WP.VibratoryDischDoors;
   WPdb.ZeroingOpen         = WP.ZeroingOpen; 
   WPdb.SlowCycleEnd        = WP.SlowCycleEnd;
   WPdb.EnabledScale        = WP.EnabledScale; 
   WPdb.ProductCode         = WP.ProductCode;
   //WP Page3
   WPdb.TopUpOFFTime        = WP.TopUpOFFTime;
   WPdb.TopUpONTime         = WP.TopUpONTime;
   WPdb.PulseTotalWeight    = WP.PulseTotalWeight;   
   WPdb.SiloNo              = WP.SiloNo;       
   WPdb.SiloDest            = WP.SiloDest; 
   WPdb.PresetCycleTime     = WP.PresetCycleTime;
   WPdb.Unit                = WP.Unit;     
   WPdb.FeedAlgoType        = WP.FeedAlgoType; 
   WPdb.TransferSilo        = WP.TransferSilo;
   WPdb.FlowThroughAfterCleanout = WP.FlowThroughAfterCleanout;
   WPdb.BulkMode            = WP.BulkMode;
   WPdb.DTF                 = WP.DTF;
   //WP Page4                 
   WPdb.FlexT1              = WP.FlexT1;
   WPdb.FlexT2              = WP.FlexT2;
   WPdb.FlexCounter         = WP.FlexCounter;
   WPdb.FlexSP1             = WP.FlexSP1;
   WPdb.FlexSP2             = WP.FlexSP2;
   WPdb.ReportType          = WP.ReportType;  
   //Report Page
   WPdb.CountAll                    = WP.CountAll;  
   WPdb.ProdSiloNo                  = WP.ProdSiloNo;      
   WPdb.ProdUnderWeightCnt[Scale1]  = WP.ProdUnderWeightCnt_1;
   WPdb.ProdUnderWeightCnt[Scale2]  = WP.ProdUnderWeightCnt_2;
   WPdb.ProdOverWeightCnt[Scale1]   = WP.ProdOverWeightCnt_1;
   WPdb.ProdOverWeightCnt[Scale2]   = WP.ProdOverWeightCnt_2;
   WPdb.ProdTotalUnitsCnt[Scale1]   = WP.ProdTotalUnitsCnt_1;
   WPdb.ProdTotalUnitsCnt[Scale2]   = WP.ProdTotalUnitsCnt_2;
   //WPdb.ProdTotalWeight[Scale1]     = WP.ProdTotalWeight_1;
   //WPdb.ProdTotalWeight[Scale2]     = WP.ProdTotalWeight_2;
   WPdb.ProdTotalWeight     = WP.ProdTotalWeight_1;
   WPdb.ProdTotalWeight     = WP.ProdTotalWeight_2;    
   //Remain from Net
   WPdb.CatchGateDelay      = WP.CatchGateDelay;      
   WPdb.MinFeeding          = WP.MinFeeding; 
   WPdb.MaxFeeding          = WP.MaxFeeding; 
   WPdb.RegMinFeeding       = WP.RegMinFeeding; 
   WPdb.RegMaxFeeding       = WP.RegMaxFeeding;         
   WPdb.ActuatorPos         = WP.ActuatorPos;   
   SaveCP2WP();
err = insert(WPdb);
return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadDb2MC
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Load MCdb Database to MC Struc
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int LoadDb2MC (void)
{
int err;

err = find(MCdb);

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

      MC.No                  = MCdb.No;                         
      MC.Name                = MCdb.Name;     
      MC.BulkBlankT          = MCdb.BulkBlankT;
      MC.DribBlankT          = MCdb.DribBlankT;
      MC.LowLevelDebounceT   = MCdb.LowLevelDebounceT;
      MC.RefillingTimeT      = MCdb.RefillingTimeT;       
      MC.NumberOfWP          = MCdb.NumberOfWP;
      MC.OIML                = MCdb.OIML; 
      MC.WeighingMode        = MCdb.WeighingMode;                       
      MC.FeederType          = MCdb.FeederType;                 
      MC.NumberOfScale       = MCdb.NumberOfScale;
      MC.Language1           = MCdb.Language1;                  
      MC.Lang1Text           = MCdb.Lang1Text;                  
      MC.Language2           = MCdb.Language2;                  
      MC.Lang2Text           = MCdb.Lang2Text;
      MC.Language3           = MCdb.Language3;                  
      MC.Lang3Text           = MCdb.Lang3Text;
      MC.PortCOM2Cfg         = MCdb.PortCOM2Cfg;    
      MC.PortUSBCfg          = MCdb.PortUSBCfg;
      MC.AutoSaveCorrection  = MCdb.AutoSaveCorrection;        
      MC.DischReqDebouncing  = MCdb.DischReqDebouncing;
      MC.PortETHCfg          = MCdb.PortETHCfg;
      MC.PrinterIP           = MCdb.PrinterIP;          
      MC.DischOnDoorSensor   = MCdb.DischOnDoorSensor;        
      MC.DribbleOutOnInBulk  = MCdb.DribbleOutOnInBulk;         
      MC.SerialNbr           = MCdb.SerialNbr;
      MC.PlantLineName       = MCdb.PlantLineName;
      MC.CustomerName        = MCdb.CustomerName;
      MC.CustomerLocation    = MCdb.CustomerLocation;      
      MC.SupportPhoneNbr     = MCdb.SupportPhoneNbr;
      MC.SupportFaxNbr       = MCdb.SupportFaxNbr;
      MC.SupportEmail        = MCdb.SupportEmail;
      MC.PartsPhoneNbr       = MCdb.PartsPhoneNbr;
      MC.PartsFaxNbr         = MCdb.PartsFaxNbr;
      MC.PartsEmail          = MCdb.PartsEmail;
      MC.iQVersion           = MCdb.iQVersion;
      MC.TrialDays           = MCdb.TrialDays; 
      //SADM2
      MC.Mouse               = MCdb.Mouse; 

return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : SaveMC2Db
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Save MC Struc to MCdb Database  
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int SaveMC2Db (void)
{
int err;

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

      MCdb.No                  = MC.No;                         
      MCdb.Name                = MC.Name;     
      MCdb.BulkBlankT          = MC.BulkBlankT;
      MCdb.DribBlankT          = MC.DribBlankT;
      MCdb.LowLevelDebounceT   = MC.LowLevelDebounceT;
      MCdb.RefillingTimeT      = MC.RefillingTimeT;       
      MCdb.NumberOfWP          = MC.NumberOfWP;
      MCdb.OIML                = MC.OIML; 
      MCdb.WeighingMode        = MC.WeighingMode;                       
      MCdb.FeederType          = MC.FeederType;                 
      MCdb.NumberOfScale       = MC.NumberOfScale;
      MCdb.Language1           = MC.Language1;                  
      MCdb.Lang1Text           = MC.Lang1Text;                  
      MCdb.Language2           = MC.Language2;                  
      MCdb.Lang2Text           = MC.Lang2Text;
      MCdb.Language3           = MC.Language3;                  
      MCdb.Lang3Text           = MC.Lang3Text;
      MCdb.PortCOM2Cfg         = MC.PortCOM2Cfg;    
      MCdb.PortUSBCfg          = MC.PortUSBCfg;
      MCdb.AutoSaveCorrection  = MC.AutoSaveCorrection;        
      MCdb.DischReqDebouncing  = MC.DischReqDebouncing;
      MCdb.PortETHCfg          = MC.PortETHCfg;
      MCdb.PrinterIP           = MC.PrinterIP;         
      MCdb.DischOnDoorSensor   = MC.DischOnDoorSensor;        
      MCdb.DribbleOutOnInBulk  = MC.DribbleOutOnInBulk;         
      MCdb.SerialNbr           = MC.SerialNbr;
      MCdb.PlantLineName       = MC.PlantLineName;
      MCdb.CustomerName        = MC.CustomerName;
      MCdb.CustomerLocation    = MC.CustomerLocation;      
      MCdb.SupportPhoneNbr     = MC.SupportPhoneNbr;
      MCdb.SupportFaxNbr       = MC.SupportFaxNbr;
      MCdb.SupportEmail        = MC.SupportEmail;
      MCdb.PartsPhoneNbr       = MC.PartsPhoneNbr;
      MCdb.PartsFaxNbr         = MC.PartsFaxNbr;
      MCdb.PartsEmail          = MC.PartsEmail;
      MCdb.iQVersion           = MC.iQVersion;
      MCdb.TrialDays           = MC.TrialDays;
      //SADM2
      MCdb.Mouse               = MC.Mouse;
      
err = insert(MCdb);   
return(err);   
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : SaveMC2Flash
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Save MC Struc to Flash Struc
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SaveMC2Flash (void)
{
bool err;

err = flashload();

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

    if (err)
    {
      Default_MC = MC;                         
      
     err = flashsave();
    }
     
return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadDefault_MC
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Write Flash Struc to MC Struc
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool LoadDefault_MC (void)
{
bool err;

err = flashload();

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

    if (err)
    {
      MC = Default_MC;                         
    }  
  
return(err);   
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadDb2MP
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Load MPdb Database to MP Struc
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int LoadDb2MP (void)
{
int err;
MP.OutOfTolTime = 0;
err = find(MPdb);

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

      MP.No                  = MPdb.No; 
      MP.Name                = MPdb.Name;    
      MP.SampleFreq          = MPdb.SampleFreq;
      MP.SampleSize          = MPdb.SampleSize;
      MP.CutoffCorr          = MPdb.CutoffCorr;
      MP.DFWeightCorr        = MPdb.DFWeightCorr;
      MP.StabTimeLimit       = MPdb.StabTimeLimit;
      MP.SlowCycleTime       = MPdb.SlowCycleTime;
      MP.DischDoorMaxTime    = MPdb.DischDoorMaxTime;
      MP.FlexCounter         = MPdb.FlexCounter;
      MP.FeedGateMaxTime     = MPdb.FeedGateMaxTime;
      MP.OutOfTolTime        = MPdb.OutOfTolTime;
      MP.FeedRateFilterRatio = MPdb.FeedRateFilterRatio; 
      MP.ZeroFreq            = MPdb.ZeroFreq;
      MP.CorrOnAverage       = MPdb.CorrOnAverage;      
      MP.CutoffCorrLimit     = MPdb.CutoffCorrLimit;
      MP.ZeroLimit           = MPdb.ZeroLimit;      
      MP.AutoZeroOff         = MPdb.AutoZeroOff;          
      MP.EndOfShift1         = MPdb.EndOfShift1;
      MP.EndOfShift2         = MPdb.EndOfShift2;
      MP.FlexSP1             = MPdb.FlexSP1;
      MP.FlexSP2             = MPdb.FlexSP2;
      MP.FlexT1              = MPdb.FlexT1;
      MP.FlexT2              = MPdb.FlexT2;
      MP.EndOfShift3         = MPdb.EndOfShift3;
      MP.ScreenSaverTime     = MPdb.ScreenSaverTime;
      MP.StdFilterSize       = MPdb.StdFilterSize;
      MP.EndOfShift4         = MPdb.EndOfShift4;
      MP.MaxFeedRate         = MPdb.MaxFeedRate;    
      MP.LowFeedingTime      = MPdb.LowFeedingTime; 
      MP.MaintCycle          = MPdb.MaintCycle;     
      MP.FailSafe            = MPdb.FailSafe; 
      MP.InvertFeedAndDischOutputs = MPdb.InvertFeedAndDischOutputs;
      MP.StopWithGatesAndDischDoorOpen = MPdb.StopWithGatesAndDischDoorOpen;  
return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : SaveMP2Db
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Save MP Struc to MPdb Database  
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int SaveMP2Db (void)
{
int err;

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

      MPdb.No                  = MP.No; 
      MPdb.Name                = MP.Name;    
      MPdb.SampleFreq          = MP.SampleFreq;
      MPdb.SampleSize          = MP.SampleSize;
      MPdb.CutoffCorr          = MP.CutoffCorr;
      MPdb.DFWeightCorr        = MP.DFWeightCorr;
      MPdb.StabTimeLimit       = MP.StabTimeLimit;
      MPdb.SlowCycleTime       = MP.SlowCycleTime;
      MPdb.DischDoorMaxTime    = MP.DischDoorMaxTime;
      MPdb.FlexCounter         = MP.FlexCounter;
      MPdb.FeedGateMaxTime     = MP.FeedGateMaxTime;
      MPdb.OutOfTolTime        = MP.OutOfTolTime;
      MPdb.FeedRateFilterRatio = MP.FeedRateFilterRatio;
      MPdb.ZeroFreq            = MP.ZeroFreq;
      MPdb.CorrOnAverage       = MP.CorrOnAverage;      
      MPdb.CutoffCorrLimit     = MP.CutoffCorrLimit;
      MPdb.ZeroLimit           = MP.ZeroLimit;      
      MPdb.AutoZeroOff         = MP.AutoZeroOff;          
      MPdb.EndOfShift1         = MP.EndOfShift1 ;
      MPdb.EndOfShift2         = MP.EndOfShift2 ;
      MPdb.FlexSP1             = MP.FlexSP1;
      MPdb.FlexSP2             = MP.FlexSP2;
      MPdb.FlexT1              = MP.FlexT1;
      MPdb.FlexT2              = MP.FlexT2;
      MPdb.EndOfShift3         = MP.EndOfShift3;
      MPdb.ScreenSaverTime     = MP.ScreenSaverTime;
      MPdb.StdFilterSize       = MP.StdFilterSize;
      MPdb.EndOfShift4         = MP.EndOfShift4;
      MPdb.MaxFeedRate         = MP.MaxFeedRate;    
      MPdb.LowFeedingTime      = MP.LowFeedingTime; 
      MPdb.MaintCycle          = MP.MaintCycle;     
      MPdb.FailSafe            = MP.FailSafe;    
      MPdb.InvertFeedAndDischOutputs = MP.InvertFeedAndDischOutputs; 
      MPdb.StopWithGatesAndDischDoorOpen = MP.StopWithGatesAndDischDoorOpen;  

err = insert(MPdb);  
return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : SaveMP2Flash
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Save MP Struc to Flash Struc
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SaveMP2Flash (void)
{
bool err;

err = flashload();

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

    if (err)
    {
      Default_MP = MP;
      
     err = flashsave();
    } 
return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadDefault_MP
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Write Flash Struc to MP Struc  
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool LoadDefault_MP (void)
{
bool err;

err = flashload();

/* "Need logic to skip the writing of the following if err = 1 or 2"*/

    if (err)
    {
      MP = Default_MP;    
      
    } 
return(err);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadIONames
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/06
--  
--  Purpose           : Load IO_Names from Language.h List 
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void LoadIONames(void)
{

IO_Name[0]  = "";
//Inputs
IO_Name[1]  = lsub(TX_I_ESTOP);
IO_Name[2]  = lsub(TX_I_DISCHREQ);
IO_Name[3]  = lsub(TX_I_DISCHDOORCLOSE);
IO_Name[4]  = lsub(TX_I_FEEDGATECLOSE);
IO_Name[5]  = lsub(TX_I_HIGHLEVELSENSOR);
IO_Name[6]  = lsub(TX_I_STOP);
IO_Name[7]  = lsub(TX_I_HOPPEREMPTY);
IO_Name[8]  = lsub(TX_I_PRESSURESW);
IO_Name[9]  = lsub(TX_I_MOTORFAILURE);
IO_Name[10] = lsub(TX_I_LOWLEVELSENSOR);
IO_Name[11] = lsub(TX_I_START);
IO_Name[12] = lsub(TX_I_MANDISCH);
IO_Name[13] = lsub(TX_I_TOTALRESET);
IO_Name[14] = lsub(TX_I_CLEARFAULTS);
IO_Name[15] = lsub(TX_I_BATCHEND);
IO_Name[16] = lsub(TX_I_RESETOUTOFTOLALARM);
IO_Name[17] = lsub(TX_I_HOLDCYCLE);
IO_Name[18] = lsub(TX_I_PRESETFEEDRATE2);//12/03/2019
IO_Name[19] = lsub(TX_IO_UNUSED);
IO_Name[20] = lsub(TX_IO_UNUSED);
IO_Name[21] = lsub(TX_IO_UNUSED);
IO_Name[22] = lsub(TX_IO_UNUSED);
IO_Name[23] = lsub(TX_IO_UNUSED);
IO_Name[24] = lsub(TX_IO_UNUSED);
IO_Name[25] = lsub(TX_I_CHANGEWPIN1);
IO_Name[26] = lsub(TX_I_CHANGEWPIN2);
IO_Name[27] = lsub(TX_I_CHANGEWPIN3);
IO_Name[28] = lsub(TX_I_CHANGEWPIN4);
IO_Name[29] = lsub(TX_I_FLEXIO_1);
IO_Name[30] = lsub(TX_I_FLEXIO_2);
IO_Name[31] = lsub(TX_IO_UNUSED);
IO_Name[32] = lsub(TX_IO_UNUSED);
IO_Name[33] = lsub(TX_IO_UNUSED);
IO_Name[34] = lsub(TX_IO_UNUSED);
IO_Name[35] = lsub(TX_IO_UNUSED);
IO_Name[36] = lsub(TX_IO_UNUSED);
//Outputs
IO_Name[37] = lsub(TX_O_FAULT);
IO_Name[38] = lsub(TX_O_FEEDRATELOWALARM);
IO_Name[39] = lsub(TX_O_FEEDRATEHIGHALARM);
IO_Name[40] = lsub(TX_O_VIBRDISCHDOOR);
IO_Name[41] = lsub(TX_O_WATCHDOG);
IO_Name[42] = lsub(TX_O_DISCHARGE);
IO_Name[43] = lsub(TX_O_DISCHDOOR);
IO_Name[44] = lsub(TX_O_BULKFEED);
IO_Name[45] = lsub(TX_O_DRIBBLEFEED);
IO_Name[46] = lsub(TX_O_HOPFILLREQ);
IO_Name[47] = lsub(TX_O_DISCHREADY);
IO_Name[48] = lsub(TX_O_LOWLEVEL);
IO_Name[49] = lsub(TX_O_OUTOFTOLERANCE);
IO_Name[50] = lsub(TX_O_OVERWEIGHTALARM);
IO_Name[51] = lsub(TX_O_UNDERWEIGHTALARM);
IO_Name[52] = lsub(TX_O_CYCLEINPROGRESS);
IO_Name[53] = lsub(TX_O_EXTERNALBAGCOUNTER);
IO_Name[54] = lsub(TX_O_CYCLEINHOLD);
IO_Name[55] = lsub(TX_O_ASPIRATION);
IO_Name[56] = lsub(TX_O_CLEANOUTWEIGHT);
IO_Name[57] = lsub(TX_O_MAINTENANCECYCLE);
IO_Name[58] = lsub(TX_O_PULSETOTALWEIGHT);
IO_Name[59] = lsub(TX_O_SLOWCYCLE);
IO_Name[60] = lsub(TX_O_BATCHENDED);
IO_Name[61] = lsub(TX_O_FLEXIO_1);
IO_Name[62] = lsub(TX_O_FLEXIO_2);
IO_Name[63] = lsub(TX_O_FLEXIO_3);
IO_Name[64] = lsub(TX_O_AGITATOR);
IO_Name[66] = lsub(TX_IO_UNUSED);
IO_Name[66] = lsub(TX_IO_UNUSED);
IO_Name[67] = lsub(TX_O_WPNUMBOUT1);
IO_Name[68] = lsub(TX_O_WPNUMBOUT2);
IO_Name[69] = lsub(TX_O_WPNUMBOUT3);
IO_Name[70] = lsub(TX_O_WPNUMBOUT4);
IO_Name[71] = lsub(TX_IO_UNUSED);
IO_Name[72] = lsub(TX_IO_UNUSED);
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadIONamesEnglish
--  Created by        : Steve Santerre
--  Last modified on  : 2017/04
--  
--  Purpose           : Load English IO_Names from Language.h List 
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void LoadIONamesEnglish(void)
{
 int i;
 
 writeparameter ("General","Language","0");
 LoadIONames();

 for(i=0;i<=MAX_IO;i++)
 {
  IO_NameEn[i] = IO_Name[i];
 }
  
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Init_Fault_Txt
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/08
--  
--  Purpose           : Load TX_ defined text messages into a string array
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void Init_Fault_Txt (void)
{
//General Faults
Fault_Txt[FltG_EmergencyStop] = lsub(TX_FltG_EmergencyStop);
Fault_Txt[FltG_LowAirPressure] = lsub(TX_FltG_LowAirPressure);
Fault_Txt[FltG_CatchGateNotOpen] = lsub(TX_FltG_CatchGateNotOpen);
Fault_Txt[FltG_SystemError] = lsub(TX_FltG_SystemError);
Fault_Txt[FltG_DischDoorNotClosed] = lsub(TX_FltG_DischDoorNotClosed);
Fault_Txt[FltG_ExceededCapacity] = lsub(TX_FltG_ExceededCapacity);
Fault_Txt[FltG_MotorFailure] = lsub(TX_FltG_MotorFailure);

//Blocking Faults
Fault_Txt[FltB_UnderWeight] = lsub(TX_FltB_UnderWeight);
Fault_Txt[FltB_OverWeight] = lsub(TX_FltB_OverWeight);
Fault_Txt[FltB_DischargeTooLong] = lsub(TX_FltB_DischargeTooLong);
Fault_Txt[FltB_ExceededCapacity] = lsub(TX_FltG_ExceededCapacity);
Fault_Txt[FltB_FeedGateNotClose] = lsub(TX_FltG_FeedGateNotClose);

//Stopping Faults
Fault_Txt[FltS_StabTooLong] = lsub(TX_FltS_StabTooLong);
Fault_Txt[FltS_ZeroOutOfRange] = lsub(TX_FltS_ZeroOutOfRange);
Fault_Txt[FltS_BagNotDetected] = lsub(TX_FltS_BagNotDetected);
Fault_Txt[FltS_HopperIllogicalDetection] = lsub(TX_FltS_HopperIllogicalDetection);


//Warning Faults
Fault_Txt[FltW_LowBattery] = lsub(TX_FltW_LowBattery);
Fault_Txt[FltW_SlowCycle] = lsub(TX_FltW_SlowCycle);
Fault_Txt[FltW_BulkBlankTooLong] = lsub(TX_FltW_BulkBlankTooLong);
Fault_Txt[FltW_DribbleBlankTooLong] = lsub(TX_FltW_DribbleBlankTooLong);
Fault_Txt[FltW_SystemWarning] = lsub(TX_FltW_SystemWarning);
Fault_Txt[FltW_HopperLowLevel] = lsub(TX_FltS_HopperLowLevel);

Fault_Txt[FltW_FeedRateLowLimit] = lsub(TX_FltW_FeedRateLowLimit);   // Added by namk 26/9/2018
Fault_Txt[FltW_FeedRateHighLimit] = lsub(TX_FltW_FeedRateHighLimit); // Added by namk 26/9/2018
Fault_Txt[FltW_MaintenanceCycle] = lsub(TX_FltW_MaintenanceCycle);   // Added by namk 26/9/2018
Fault_Txt[FltW_FeedRateMaxLimit] =  lsub(TX_FltW_FeedRateMaxLimit);   // Added by namk 26/9/2018
Fault_Txt[FltW_InvalidSiloSource] =  lsub(TX_FltW_InvalidSiloSource);   // Added by namk 26/9/2018
//Fault_Txt[FltW_SlioWeightLowerZero] = lsub(TX_FltW_SlioWeightLowerZero);   // Added by namk 26/9/2018
//Fault_Txt[FltW_InvalidSiloNo] = lsub(TX_FltW_InvalidSiloNo);   // Added by NAMK 26/9/2018
//Fault_Txt[FltW_SiloWeightOverCapacity] = lsub(TX_FltW_SiloWeightOverCapacity);   // Added by namk 26/9/2018


}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshLanguage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Refresh language texts in selected page 
--                    : 
--  Value Parameters  :
--  Variable Params   : Scrn_No: Current screen  to refresh language
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshLanguage(int Scrn_No)
{

/* ******************************** */
/*       Auto page                  */
/* ******************************** */
int Scrn_No_Temp;

  begindraw();
   
   Scrn_No_Temp = Scrn_No;
   if (Scrn_No == SCREEN_IOCFG_IN1 || Scrn_No == SCREEN_IOTEST_IN1) Scrn_No_Temp = SCREEN_INPUT_PAGE1;
   if (Scrn_No == SCREEN_IOCFG_IN2 || Scrn_No == SCREEN_IOTEST_IN2) Scrn_No_Temp = SCREEN_INPUT_PAGE2;
   if (Scrn_No == SCREEN_IOCFG_IN3 || Scrn_No == SCREEN_IOTEST_IN3) Scrn_No_Temp = SCREEN_INPUT_PAGE3;
   if (Scrn_No == SCREEN_IOCFG_OUT1 || Scrn_No == SCREEN_IOTEST_OUT1) Scrn_No_Temp = SCREEN_OUTPUT_PAGE1;
   if (Scrn_No == SCREEN_IOCFG_OUT2 || Scrn_No == SCREEN_IOTEST_OUT2) Scrn_No_Temp = SCREEN_OUTPUT_PAGE2;
   if (Scrn_No == SCREEN_IOCFG_OUT3 || Scrn_No == SCREEN_IOTEST_OUT3) Scrn_No_Temp = SCREEN_OUTPUT_PAGE3;
   
   switch(Scrn_No_Temp)
   {

    case SCREEN_AUTOMATIC:
      // Header
        RefreshRecipeInAutoScreen();     
        
        // First Column                                
              // First Row Info 
              widget_text       (AUTO_ROW1_ID,   lsub(TX_NOMINAL_WEIGHT_ID));        
              // 2nd Row Info 
              widget_text       (AUTO_ROW2_ID,   lsub(TX_AVERAGE_ID));                                               
              // Third Row Info 
               widget_text      (AUTO_ROW3_ID,   lsub(TX_TOTAL_WEIGHT_ID)); //commented by namk                                             
              // Fourth Row Info 
              widget_text       (AUTO_ROW4_ID,   lsub(TX_LAST_CHECKED_ID));    
              // Fifth Row Info
              widget_text       (AUTO_ROW5_ID,    lsub(TX_ACTUALFEEDRATE_ID)); //added by namk                                          
              
        // Second Column                               
                                              
              // First Row Info 
              widget_text       (AUTO_ROW11_ID,   lsub(TX_UNITS_ACCEPTED_ID));        
              // 2nd Row Info 
              widget_text       (AUTO_ROW12_ID,   lsub(TX_WEIGHS_PER_UNIT_ID));                                               
              // Third Row Info 
              widget_text       (AUTO_ROW13_ID,   lsub(TX_UNITS_DONE_ID));                                            
              // Fourth Row Info 
              widget_text       (AUTO_ROW14_ID,   lsub(TX_PRESETS_PER_UNIT_ID));
              // Fifth Row Info
              widget_text       (AUTO_ROW15_ID,   lsub(TX_PRESETFEEDRATE_ID)); //added by namk
                            
        // ThirdColumn                               
                                              
              // First Row Info 
              widget_text       (AUTO_ROW21_ID,   lsub(TX_UNITSPERMIN_ID));      
              // 2nd Row Info 
              widget_text       (AUTO_ROW22_ID,   lsub(TX_BULK_TIME_ID));                                               
              // Third Row Info 
              widget_text       (AUTO_ROW23_ID,   lsub(TX_DRIBBLE_TIME_ID));                                              
              // Fourth Row Info 
              widget_text       (AUTO_ROW24_ID,   lsub(TX_CYCLE_TIME_ID));         

     break;        
      
    case SCREEN_RECIPE1:  
      /* ******************************** */
      /*       Recipe page 1              */
      /* ******************************** */ 
      
      //  Header
      
             
        // First Column                                
                                              
              // First Row Info 
              widget_text       (RECIPE_ROW1_ID, lsub(TX_WPNOMINALWEIGHT));
              widget_label      (RECIPE_ROW1_INPUT, lsub(TX_WPNOMINALWEIGHT));
              // 2nd Row Info 
              widget_text       (RECIPE_ROW2_ID, lsub(TX_WPOVERFILL));
              widget_label      (RECIPE_ROW2_INPUT, lsub(TX_WPOVERFILL));                                              
              // Third Row Info 
              widget_text       (RECIPE_ROW3_ID, lsub(TX_WPCUTOFFWEIGHT));
              widget_label      (RECIPE_ROW3_INPUT, lsub(TX_WPCUTOFFWEIGHT));                                              
              // Fourth Row Info 
              widget_text       (RECIPE_ROW4_ID, lsub(TX_WPDRIBBLEFEEDWEIGHT));
              widget_label      (RECIPE_ROW4_INPUT, lsub(TX_WPDRIBBLEFEEDWEIGHT));                                               
              // Fifth Row Info 
              widget_text       (RECIPE_ROW5_ID, lsub(TX_WPDRIBBLEFEEDTIME));
              widget_label      (RECIPE_ROW5_INPUT, lsub(TX_WPDRIBBLEFEEDTIME));                                              
              // Sixth Row Info 
              widget_text       (RECIPE_ROW6_ID, lsub(TX_WPBULKFEEDTIME));
              widget_label      (RECIPE_ROW6_INPUT, lsub(TX_WPBULKFEEDTIME));
              
        // Second Column                               
                                              
              // First Row Info 
              widget_text       (RECIPE_ROW7_ID, lsub(TX_WPUNDERWEIGHT));
              widget_label      (RECIPE_ROW7_INPUT, lsub(TX_WPUNDERWEIGHT));       
              // 2nd Row Info 
              widget_text       (RECIPE_ROW8_ID, lsub(TX_WPOVERWEIGHT));
              widget_label      (RECIPE_ROW8_INPUT, lsub(TX_WPOVERWEIGHT));                                              
              // Third Row Info 
              widget_text       (RECIPE_ROW9_ID,    lsub(TX_WPFEEDDELAYTIME));
              widget_label      (RECIPE_ROW9_INPUT, lsub(TX_WPFEEDDELAYTIME)); 
                                                            
              // Fourth Row Info 
              widget_text       (RECIPE_ROW10_ID, lsub(TX_WPDISCHARGEWEIGHT));
              widget_label      (RECIPE_ROW10_INPUT, lsub(TX_WPDISCHARGEWEIGHT));                                              
              // Fifth Row Info 
              widget_text       (RECIPE_ROW11_ID, lsub(TX_WPDISCHARGETIME));
              widget_label      (RECIPE_ROW11_INPUT, lsub(TX_WPDISCHARGETIME));                                             
              // Sixth Row Info 
              widget_text       (RECIPE_ROW12_ID,    lsub(TX_WPWEIGHMENTSPERUNIT));
              widget_label      (RECIPE_ROW12_INPUT, lsub(TX_WPWEIGHMENTSPERUNIT)); 
              
     break;
     
    case SCREEN_RECIPE2:  
      /* ******************************** */
      /*       Recipe page 2              */
      /* ******************************** */ 
      
      //  Header
      
     
        // First Column                                
                                              
              // First Row Info
              if(MC.WeighingMode == None)//added by namk 18/9/2018
              {
              widget_text       (RECIPE_ROW13_ID, lsub(TX_WPMINFEEDING));
              widget_label      (RECIPE_ROW13_INPUT, lsub(TX_WPMINFEEDING));
              }
              else
              {
              widget_text       (RECIPE_ROW13_ID, lsub(TX_WPFEEDRATELOWLIMIT));//added by namk 18/9/2018
              widget_label      (RECIPE_ROW13_INPUT, lsub(TX_WPFEEDRATELOWLIMIT));//added by namk 18/9/2018
              }  
                   
              // 2nd Row Info
              if(MC.WeighingMode == None)//added by namk 18/9/2018
              { 
              widget_text       (RECIPE_ROW14_ID, lsub(TX_WPMAXFEEDING));
              widget_label      (RECIPE_ROW14_INPUT, lsub(TX_WPMAXFEEDING));
              }
              else
              {
              widget_text       (RECIPE_ROW14_ID, lsub(TX_WPFEEDRATEHIGHLIMIT));//added by namk 18/9/2018
              widget_label      (RECIPE_ROW14_INPUT, lsub(TX_WPFEEDRATEHIGHLIMIT));//added by namk 18/9/2018
              }                                               
              // Third Row Info
              if(MC.WeighingMode == None)//added by namk 18/9/2018
              { 
              widget_text       (RECIPE_ROW15_ID, lsub(TX_WPREGMINFEEDING));
              widget_label      (RECIPE_ROW15_INPUT, lsub(TX_WPREGMINFEEDING));
              }
              else
              {
              widget_text       (RECIPE_ROW15_ID, lsub(TX_WPTARGETWEIGHTIP));//added by namk 18/9/2018
              widget_label      (RECIPE_ROW15_INPUT, lsub(TX_WPTARGETWEIGHTIP));//added by namk 18/9/2018
              }                                              
              // Fourth Row Info
              if(MC.WeighingMode == None)//added by namk 18/9/2018 
              {
              widget_text       (RECIPE_ROW16_ID, lsub(TX_WPREGMAXFEEDING));
              widget_label      (RECIPE_ROW16_INPUT, lsub(TX_WPREGMAXFEEDING));
              }
              else
              {
              widget_text       (RECIPE_ROW16_ID, lsub(TX_WPCLEANOUTWEIGHTIP));//added by namk 18/9/2018
              widget_label      (RECIPE_ROW16_INPUT, lsub(TX_WPCLEANOUTWEIGHTIP));//added by namk 18/9/2018
              }                                               
              // Fifth Row Info 
              widget_text       (RECIPE_ROW17_ID,    lsub(TX_WPBULKMODEIP));
              widget_text       (RECIPE_ROW17_SELECT, lsub(TX_WPSHIP), 0);
              widget_text       (RECIPE_ROW17_SELECT, lsub(TX_WPRECEIVE), 1);
              // Sixth Row Info 
              if(MC.WeighingMode == None)//added by namk 18/9/2018
              {
              widget_text       (RECIPE_ROW18_ID,    lsub(TX_WPACTUATORPOS));
              widget_label      (RECIPE_ROW18_INPUT, lsub(TX_WPACTUATORPOS));
              }
              else
              {
              widget_text       (RECIPE_ROW18_ID,    lsub(TX_WPPRESETBATCH));
              widget_label      (RECIPE_ROW18_INPUT, lsub(TX_WPPRESETBATCH));
              }
              
        // Second Column                               
                                              
              // First Row Info 
              widget_text       (RECIPE_ROW19_ID, lsub(TX_WPPRESETFEEDRATE1));     
              widget_label      (RECIPE_ROW19_INPUT, lsub(TX_WPPRESETFEEDRATE1));        
              // 2nd Row Info 
              widget_text       (RECIPE_ROW20_ID,    lsub(TX_WPPRESETFEEDRATE2));
              widget_label      (RECIPE_ROW20_INPUT, lsub(TX_WPPRESETFEEDRATE2));                                               
              // Third Row Info 
              widget_text       (RECIPE_ROW21_ID,     lsub(TX_WPVIBRATORYDISCHDOOR));
              widget_text       (RECIPE_ROW21_SELECT, lsub(TX_OFF), 0);
              widget_text       (RECIPE_ROW21_SELECT, lsub(TX_ON), 1);                                              
              // Fourth Row Info 
              widget_text       (RECIPE_ROW22_ID,     lsub(TX_WPZEROINGOPEN));
              widget_text       (RECIPE_ROW22_SELECT, lsub(TX_WPDOOR_CLOSED), 0);
              widget_text       (RECIPE_ROW22_SELECT, lsub(TX_WPDOOR_OPEN), 1);                                               
              // Fifth Row Info 
              widget_text       (RECIPE_ROW23_ID,     lsub(TX_WPSLOWCYCLEEND));
              widget_text       (RECIPE_ROW23_SELECT, lsub(TX_WPHOLD_CYCLE), HOLD_CYCLE);
              widget_text       (RECIPE_ROW23_SELECT, lsub(TX_WPEND_CYCLE), END_CYCLE); 
              widget_text       (RECIPE_ROW23_SELECT, lsub(TX_WPDRIBBLEEND), DRIBBLE_CYCLE);                                            
              // Sixth Row Info 
              widget_text       (RECIPE_ROW24_ID, lsub(TX_WPPRODUCTCODE));
              widget_label      (RECIPE_ROW24_INPUT, lsub(TX_WPPRODUCTCODE));     
     break;

    case SCREEN_RECIPE3:  
      /* ******************************** */
      /*       Recipe page 3              */
      /* ******************************** */ 
      
      //  Header
        
        // First Column                                
                                              
              // First Row Info 
              
              if(WP.FeedAlgoType == FeediQSim) 
              {
                widget_text       (RECIPE_ROW25_ID,    concat("iQSim ",lsub(TX_BULK_TIME_ID)));
                widget_label      (RECIPE_ROW25_INPUT, concat("iQSim ",lsub(TX_BULK_TIME_ID)));
              }  
              else
              {
                widget_text       (RECIPE_ROW25_ID,    lsub(TX_WPTOPUPOFFTIME));
                widget_label      (RECIPE_ROW25_INPUT, lsub(TX_WPTOPUPOFFTIME));
              }  
              // 2nd Row Info 
              if(WP.FeedAlgoType == FeediQSim)
              {
                widget_text       (RECIPE_ROW26_ID,    concat("iQSim ",lsub(TX_DRIBBLE_TIME_ID)));
                widget_label      (RECIPE_ROW26_INPUT, concat("iQSim ",lsub(TX_DRIBBLE_TIME_ID)));
              }  
              else 
              {
                widget_text       (RECIPE_ROW26_ID,    lsub(TX_WPTOPUPONTIME));
                widget_label      (RECIPE_ROW26_INPUT, lsub(TX_WPTOPUPONTIME));
              }  
              // Third Row Info 
              widget_text       (RECIPE_ROW27_ID,    lsub(TX_WPPULSETOTALWEIGHT));
              widget_label      (RECIPE_ROW27_INPUT, lsub(TX_WPPULSETOTALWEIGHT));
              // Fourth Row Info 
              widget_text       (RECIPE_ROW28_ID,    lsub(TX_WPSILONO));
              widget_label      (RECIPE_ROW28_INPUT, lsub(TX_WPSILONO));
              // 5th Row Info 
              widget_text       (RECIPE_ROW29_ID,    lsub(TX_WPSILODEST));
              widget_label      (RECIPE_ROW29_INPUT, lsub(TX_WPSILODEST));
              // 6th Row Info 
              widget_text       (RECIPE_ROW30_ID,    lsub(TX_WPPRESETCYCLETIME)); //commented by namk 19/9/2018
              widget_label      (RECIPE_ROW30_INPUT, lsub(TX_WPPRESETCYCLETIME)); //commented by namk 19/9/2018
              
              
        // Second Column                               
                                              
              // First Row Info 
              widget_text       (RECIPE_ROW31_ID, lsub(TX_WPUNITSELECTION));
              widget_text       (RECIPE_ROW31_SELECT, lsub(TX_WPUNITKG), 0);
              widget_text       (RECIPE_ROW31_SELECT, lsub(TX_WPUNITLB), 1);
              widget_text       (RECIPE_ROW31_SELECT, lsub(TX_WPUNITTON), 2);
              // 2nd Row Info 
              widget_text       (RECIPE_ROW32_ID, lsub(TX_WPFEEDALGOTYPE));
              widget_text       (RECIPE_ROW32_SELECT, lsub(TX_WPALGOSTD), 0);
              widget_text       (RECIPE_ROW32_SELECT, lsub(TX_WPALGOSIMIQ), 1); //Test 4 org is 2
              // 3rd Row Info 
              widget_text       (RECIPE_ROW33_ID, lsub(TX_WPTRANSFERSILO));
              widget_text       (RECIPE_ROW33_SELECT, lsub(TX_WPNO), 0);
              widget_text       (RECIPE_ROW33_SELECT, lsub(TX_WPYES), 1);
             
              // 4th Row Info 
              widget_text       (RECIPE_ROW34_ID,     lsub(TX_WPFTAFTERCLEANOUT));
              widget_text       (RECIPE_ROW34_SELECT, lsub(TX_WPNO), 0);
              widget_text       (RECIPE_ROW34_SELECT, lsub(TX_WPYES), 1);
              // 5th Row Info 
              widget_text       (RECIPE_ROW35_ID,     lsub(TX_WPBULKMODE));
              widget_text       (RECIPE_ROW35_SELECT, lsub(TX_BYWEIGHT), ByWeight);
              widget_text       (RECIPE_ROW35_SELECT, lsub(TX_BYTIME), ByTime);
                                                            
              // 6th Row Info 
              widget_text       (RECIPE_ROW36_ID,    lsub(TX_WPDTF)); 
              widget_label      (RECIPE_ROW36_INPUT, lsub(TX_WPDTF)); 
                      
     break;      
    
    case SCREEN_RECIPE4:  
      /* ******************************** */
      /*       Recipe page 4              */
      /* ******************************** */ 
      
      //  Header
        
        // First Column                                
                                              
                                                            
              // 1st Row Info 
              widget_text       (RECIPE_ROW37_ID, lsub(TX_WPT1));
              widget_label      (RECIPE_ROW37_INPUT, lsub(TX_WPT1));                                               
              // 2nd Row Info 
              widget_text       (RECIPE_ROW38_ID, lsub(TX_WPT2));
              widget_label      (RECIPE_ROW38_INPUT, lsub(TX_WPT2));
              // 3rd Row Info 
              widget_text       (RECIPE_ROW39_ID, lsub(TX_FLEXCOUNTER));
              widget_label      (RECIPE_ROW39_INPUT, lsub(TX_FLEXCOUNTER));
              
              
        // Second Column                               
                                              
              // 1st Row Info 
              widget_text       (RECIPE_ROW43_ID, lsub(TX_WPSP1));
              widget_label      (RECIPE_ROW43_INPUT, lsub(TX_WPSP1)); 
              // 2nd Row Info 
              widget_text       (RECIPE_ROW44_ID, lsub(TX_WPSP2));
              widget_label      (RECIPE_ROW44_INPUT, lsub(TX_WPSP2));
              
              widget_text       (RECIPE_ROW45_ID,     lsub(TX_MCREPORTTYPE));     
              widget_text       (RECIPE_ROW45_SELECT, lsub(TX_NONE), 0);           
              widget_text       (RECIPE_ROW45_SELECT, lsub(TX_MCINDIVIDUAL), 1); 
              widget_text       (RECIPE_ROW45_SELECT, lsub(TX_MCFULLEMPTY), 2);
                      
     break;      
     
    case SCREEN_INPUT_PAGE1:
              // First Column                                
                                              
              // HEADER
              widget_text      (IO_ID_HEADER1, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER1, lsub(TX_IO_ADDRESS));
              switch (Scrn_No)
              {
                case SCREEN_IOCFG_IN1:  widget_text(IO_CHECK_HEADER1, lsub(TX_IO_ENABLE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_ENABLE));
                                     break;
                case SCREEN_IOTEST_IN1: 
                                        widget_text(IO_STATE_HEADER1, lsub(TX_IO_STATE));
                                        widget_text(IO_STATE_HEADER2, lsub(TX_IO_STATE));
                                     break;
              }
              // First Row Info 
              widget_text       (IO_ID_ROW1,     lsub(TX_I_ESTOP));
              widget_label      (IO_INPUT_ROW1,  lsub(TX_I_ESTOP));
              widget_text       (IO_ID_ROW2,     lsub(TX_I_DISCHREQ));
              widget_label      (IO_INPUT_ROW2,  lsub(TX_I_DISCHREQ));
              widget_text       (IO_ID_ROW3,     lsub(TX_I_DISCHDOORCLOSE));
              widget_label      (IO_INPUT_ROW3,  lsub(TX_I_DISCHDOORCLOSE));
              widget_text       (IO_ID_ROW4,     lsub(TX_I_FEEDGATECLOSE));
              widget_label      (IO_INPUT_ROW4,  lsub(TX_I_FEEDGATECLOSE));
              widget_text       (IO_ID_ROW5,     lsub(TX_I_HIGHLEVELSENSOR));
              widget_label      (IO_INPUT_ROW5,  lsub(TX_I_HIGHLEVELSENSOR));
              widget_text       (IO_ID_ROW6,     lsub(TX_I_STOP));
              widget_label      (IO_INPUT_ROW6,  lsub(TX_I_STOP));

              
              // Second Column                               
                                              
              // HEADER
              widget_text      (IO_ID_HEADER2, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER2, lsub(TX_IO_ADDRESS));
              
              // First Row Info 
              widget_text       (IO_ID_ROW7,     lsub(TX_I_HOPPEREMPTY));
              widget_label      (IO_INPUT_ROW7,  lsub(TX_I_HOPPEREMPTY));
              widget_text       (IO_ID_ROW8,     lsub(TX_I_PRESSURESW));
              widget_label      (IO_INPUT_ROW8,  lsub(TX_I_PRESSURESW));
              widget_text       (IO_ID_ROW9,     lsub(TX_I_MOTORFAILURE));
              widget_label      (IO_INPUT_ROW9,  lsub(TX_I_MOTORFAILURE));
              widget_text       (IO_ID_ROW10,    lsub(TX_I_LOWLEVELSENSOR));
              widget_label      (IO_INPUT_ROW10, lsub(TX_I_LOWLEVELSENSOR));
              widget_text       (IO_ID_ROW11,    lsub(TX_I_START));
              widget_label      (IO_INPUT_ROW11, lsub(TX_I_START));
              widget_text       (IO_ID_ROW12,    lsub(TX_I_MANDISCH));
              widget_label      (IO_INPUT_ROW12, lsub(TX_I_MANDISCH));
     break;
     
    case SCREEN_INPUT_PAGE2:
              // First Column                                
                                              
              // HEADER
              widget_text      (IO_ID_HEADER1, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER1, lsub(TX_IO_ADDRESS));
              switch (Scrn_No)
              {
                case SCREEN_IOCFG_IN2:  widget_text(IO_CHECK_HEADER1, lsub(TX_IO_ENABLE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_ENABLE));
                                     break;
                case SCREEN_IOTEST_IN2: 
                                        widget_text(IO_STATE_HEADER1, lsub(TX_IO_STATE));
                                        widget_text(IO_STATE_HEADER2, lsub(TX_IO_STATE));
                                     break;
              }
              // First Row Info 
              widget_text       (IO_ID_ROW1,     lsub(TX_I_TOTALRESET));
              widget_label      (IO_INPUT_ROW1,  lsub(TX_I_TOTALRESET));
              widget_text       (IO_ID_ROW2,     lsub(TX_I_CLEARFAULTS));
              widget_label      (IO_INPUT_ROW2,  lsub(TX_I_CLEARFAULTS));
              widget_text       (IO_ID_ROW3,     lsub(TX_I_HOLDCYCLE));
              widget_label      (IO_INPUT_ROW3,  lsub(TX_I_HOLDCYCLE));
              widget_text       (IO_ID_ROW4,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW4,  lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW5,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW5,  lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW6,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW6,  lsub(TX_IO_UNUSED));

              
              // Second Column                               
                                              
              // HEADER
              widget_text      (IO_ID_HEADER2, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER2, lsub(TX_IO_ADDRESS));

              // First Row Info 
              widget_text       (IO_ID_ROW7,     lsub(TX_I_BATCHEND));
              widget_label      (IO_INPUT_ROW7,  lsub(TX_I_BATCHEND));
              widget_text       (IO_ID_ROW8,     lsub(TX_I_RESETOUTOFTOLALARM));
              widget_label      (IO_INPUT_ROW8,  lsub(TX_I_RESETOUTOFTOLALARM));
              widget_text       (IO_ID_ROW9,     lsub(TX_I_PRESETFEEDRATE2));//12/03/2019
              widget_label      (IO_INPUT_ROW9,  lsub(TX_I_PRESETFEEDRATE2));//12/03/2019
              widget_text       (IO_ID_ROW10,    lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW10, lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW11,    lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW11, lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW12,    lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW12, lsub(TX_IO_UNUSED));
     break;
     
    case SCREEN_INPUT_PAGE3:
              // First Column                                
                                              
              // HEADER
              widget_text      (IO_ID_HEADER1, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER1, lsub(TX_IO_ADDRESS));
              switch (Scrn_No)
              {
                case SCREEN_IOCFG_IN3:  widget_text(IO_CHECK_HEADER1, lsub(TX_IO_ENABLE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_ENABLE));
                                     break;
                case SCREEN_IOTEST_IN3: 
                                        widget_text(IO_STATE_HEADER1, lsub(TX_IO_STATE));
                                        widget_text(IO_STATE_HEADER2, lsub(TX_IO_STATE));
                                     break;
              }
              // First Row Info 
              widget_text       (IO_ID_ROW1,     lsub(TX_I_CHANGEWPIN1));
              widget_label      (IO_INPUT_ROW1,  lsub(TX_I_CHANGEWPIN1));
              widget_text       (IO_ID_ROW2,     lsub(TX_I_CHANGEWPIN2));
              widget_label      (IO_INPUT_ROW2,  lsub(TX_I_CHANGEWPIN2));
              widget_text       (IO_ID_ROW3,     lsub(TX_I_CHANGEWPIN3));
              widget_label      (IO_INPUT_ROW3,  lsub(TX_I_CHANGEWPIN3));
              widget_text       (IO_ID_ROW4,     lsub(TX_I_CHANGEWPIN4));
              widget_label      (IO_INPUT_ROW4,  lsub(TX_I_CHANGEWPIN4));
              widget_text       (IO_ID_ROW5,     lsub(TX_I_FLEXIO_1));
              widget_label      (IO_INPUT_ROW5,  lsub(TX_I_FLEXIO_1));
              widget_text       (IO_ID_ROW6,     lsub(TX_I_FLEXIO_2));
              widget_label      (IO_INPUT_ROW6,  lsub(TX_I_FLEXIO_2));
              

              
              // Second Column                               
                                              
              // HEADER
              widget_text      (IO_ID_HEADER2, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER2, lsub(TX_IO_ADDRESS));

              // First Row Info 
              widget_text       (IO_ID_ROW7,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW7,  lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW8,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW8,  lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW9,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW9,  lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW10,    lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW10, lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW11,    lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW11, lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW12   , lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW12, lsub(TX_IO_UNUSED));
     break;
     
    case SCREEN_OUTPUT_PAGE1:
              // First Column                                
                                              
              // HEADER
              widget_text      (IO_ID_HEADER1, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER1, lsub(TX_IO_ADDRESS));
              switch (Scrn_No)
              {
                case SCREEN_IOCFG_OUT1: widget_text(IO_CHECK_HEADER1, lsub(TX_IO_ENABLE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_ENABLE));
                                     break;
                case SCREEN_IOTEST_OUT1: 
                                        widget_text(IO_STATE_HEADER1, lsub(TX_IO_STATE));
                                        widget_text(IO_CHECK_HEADER1, lsub(TX_IO_TEST));
                                        widget_text(IO_STATE_HEADER2, lsub(TX_IO_STATE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_TEST));
                                     break;
              }
              // First Row Info 
              widget_text       (IO_ID_ROW1,     lsub(TX_O_FAULT));
              widget_label      (IO_INPUT_ROW1,  lsub(TX_O_FAULT));
              widget_text       (IO_ID_ROW2,     lsub(TX_O_FEEDRATELOWALARM));
              widget_label      (IO_INPUT_ROW2,  lsub(TX_O_FEEDRATELOWALARM));
              widget_text       (IO_ID_ROW3,     lsub(TX_O_FEEDRATEHIGHALARM));
              widget_label      (IO_INPUT_ROW3,  lsub(TX_O_FEEDRATEHIGHALARM));
              widget_text       (IO_ID_ROW4,     lsub(TX_O_VIBRDISCHDOOR));
              widget_label      (IO_INPUT_ROW4,  lsub(TX_O_VIBRDISCHDOOR));
              widget_text       (IO_ID_ROW5,     lsub(TX_O_WATCHDOG));
              widget_label      (IO_INPUT_ROW5,  lsub(TX_O_WATCHDOG));
              widget_text       (IO_ID_ROW6,     lsub(TX_O_DISCHARGE));
              widget_label      (IO_INPUT_ROW6,  lsub(TX_O_DISCHARGE));
              

              
              // Second Column                               
                                              
              // HEADER
              widget_text      (IO_ID_HEADER2, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER2, lsub(TX_IO_ADDRESS));

              // First Row Info 
              widget_text       (IO_ID_ROW7,     lsub(TX_O_DISCHDOOR));
              widget_label      (IO_INPUT_ROW7,  lsub(TX_O_DISCHDOOR));
              widget_text       (IO_ID_ROW8,     lsub(TX_O_BULKFEED));
              widget_label      (IO_INPUT_ROW8,  lsub(TX_O_BULKFEED));
              widget_text       (IO_ID_ROW9,     lsub(TX_O_DRIBBLEFEED));
              widget_label      (IO_INPUT_ROW9,  lsub(TX_O_DRIBBLEFEED));
              widget_text       (IO_ID_ROW10,    lsub(TX_O_HOPFILLREQ));
              widget_label      (IO_INPUT_ROW10, lsub(TX_O_HOPFILLREQ));
              widget_text       (IO_ID_ROW11,    lsub(TX_O_DISCHREADY));
              widget_label      (IO_INPUT_ROW11, lsub(TX_O_DISCHREADY));
              widget_text       (IO_ID_ROW12,    lsub(TX_O_LOWLEVEL));
              widget_label      (IO_INPUT_ROW12, lsub(TX_O_LOWLEVEL));
     break; 
     
    case SCREEN_OUTPUT_PAGE2:
              // First Column                                
                                              
              // HEADER
              widget_text      (IO_ID_HEADER1, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER1, lsub(TX_IO_ADDRESS));
              switch (Scrn_No)
              {
                case SCREEN_IOCFG_OUT2: widget_text(IO_CHECK_HEADER1, lsub(TX_IO_ENABLE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_ENABLE));
                                     break;
                case SCREEN_IOTEST_OUT2: 
                                        widget_text(IO_STATE_HEADER1, lsub(TX_IO_STATE));
                                        widget_text(IO_CHECK_HEADER1, lsub(TX_IO_TEST));
                                        widget_text(IO_STATE_HEADER2, lsub(TX_IO_STATE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_TEST));
                                     break;
              }
              // First Row Info 
              widget_text       (IO_ID_ROW1,     lsub(TX_O_OUTOFTOLERANCE));
              widget_label      (IO_INPUT_ROW1,  lsub(TX_O_OUTOFTOLERANCE));
              widget_text       (IO_ID_ROW2,     lsub(TX_O_OVERWEIGHTALARM));
              widget_label      (IO_INPUT_ROW2,  lsub(TX_O_OVERWEIGHTALARM));
              widget_text       (IO_ID_ROW3,     lsub(TX_O_UNDERWEIGHTALARM));
              widget_label      (IO_INPUT_ROW3,  lsub(TX_O_UNDERWEIGHTALARM));
              widget_text       (IO_ID_ROW4,     lsub(TX_O_CYCLEINPROGRESS));
              widget_label      (IO_INPUT_ROW4,  lsub(TX_O_CYCLEINPROGRESS));
              widget_text       (IO_ID_ROW5,     lsub(TX_O_EXTERNALBAGCOUNTER));
              widget_label      (IO_INPUT_ROW5,  lsub(TX_O_EXTERNALBAGCOUNTER));
              widget_text       (IO_ID_ROW6,     lsub(TX_O_CYCLEINHOLD));
              widget_label      (IO_INPUT_ROW6,  lsub(TX_O_CYCLEINHOLD));

              
              // Second Column                               
                                              
              // HEADER
              widget_text      (IO_ID_HEADER2, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER2, lsub(TX_IO_ADDRESS));

              // First Row Info 
              widget_text       (IO_ID_ROW7,     lsub(TX_O_ASPIRATION));
              widget_label      (IO_INPUT_ROW7,  lsub(TX_O_ASPIRATION));
              widget_text       (IO_ID_ROW8,     lsub(TX_O_CLEANOUTWEIGHT));
              widget_label      (IO_INPUT_ROW8,  lsub(TX_O_CLEANOUTWEIGHT));
              widget_text       (IO_ID_ROW9,     lsub(TX_O_MAINTENANCECYCLE));
              widget_label      (IO_INPUT_ROW9,  lsub(TX_O_MAINTENANCECYCLE));
              widget_text       (IO_ID_ROW10,    lsub(TX_O_PULSETOTALWEIGHT));
              widget_label      (IO_INPUT_ROW10, lsub(TX_O_PULSETOTALWEIGHT));
              widget_text       (IO_ID_ROW11,    lsub(TX_O_SLOWCYCLE));
              widget_label      (IO_INPUT_ROW11, lsub(TX_O_SLOWCYCLE));
              widget_text       (IO_ID_ROW12,     lsub(TX_O_BATCHENDED));
              widget_label      (IO_INPUT_ROW12,  lsub(TX_O_BATCHENDED));
              
     break;
          
    case SCREEN_OUTPUT_PAGE3:
              // First Column                                
                                              
              // HEADER
              widget_text      (IO_ID_HEADER1, lsub(TX_IO_NAME));
              widget_text      (IO_INPUT_HEADER1, lsub(TX_IO_ADDRESS));
              switch (Scrn_No)
              {
                case SCREEN_IOCFG_OUT3: widget_text(IO_CHECK_HEADER1, lsub(TX_IO_ENABLE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_ENABLE));
                                     break;
                case SCREEN_IOTEST_OUT3: 
                                        widget_text(IO_STATE_HEADER1, lsub(TX_IO_STATE));
                                        widget_text(IO_CHECK_HEADER1, lsub(TX_IO_TEST));
                                        widget_text(IO_STATE_HEADER2, lsub(TX_IO_STATE));
                                        widget_text(IO_CHECK_HEADER2, lsub(TX_IO_TEST));
                                     break;
              }
              // First Row Info 
              
              widget_text       (IO_ID_ROW1,     lsub(TX_O_FLEXIO_1));
              widget_label      (IO_INPUT_ROW1,  lsub(TX_O_FLEXIO_1));
              widget_text       (IO_ID_ROW2,     lsub(TX_O_FLEXIO_2));
              widget_label      (IO_INPUT_ROW2,  lsub(TX_O_FLEXIO_2));
              widget_text       (IO_ID_ROW3,     lsub(TX_O_FLEXIO_3));
              widget_label      (IO_INPUT_ROW3,  lsub(TX_O_FLEXIO_3));
              widget_text       (IO_ID_ROW4,     lsub(TX_O_AGITATOR));
              widget_label      (IO_INPUT_ROW4,  lsub(TX_O_AGITATOR));
              widget_text       (IO_ID_ROW5,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW5,  lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW6,     lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW6,  lsub(TX_IO_UNUSED));
              
              // Second Column                               
                                              
              // HEADER
              widget_text       (IO_ID_HEADER2, lsub(TX_IO_NAME));
              widget_text       (IO_INPUT_HEADER2, lsub(TX_IO_ADDRESS));

              // First Row Info 
              widget_text       (IO_ID_ROW7,     lsub(TX_O_WPNUMBOUT1));
              widget_label      (IO_INPUT_ROW7,  lsub(TX_O_WPNUMBOUT1));
              widget_text       (IO_ID_ROW8,     lsub(TX_O_WPNUMBOUT2));
              widget_label      (IO_INPUT_ROW8,  lsub(TX_O_WPNUMBOUT2));
              widget_text       (IO_ID_ROW9,     lsub(TX_O_WPNUMBOUT3));
              widget_label      (IO_INPUT_ROW9,  lsub(TX_O_WPNUMBOUT3));
              widget_text       (IO_ID_ROW10,    lsub(TX_O_WPNUMBOUT4));
              widget_label      (IO_INPUT_ROW10, lsub(TX_O_WPNUMBOUT4));
              widget_text       (IO_ID_ROW11,    lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW11, lsub(TX_IO_UNUSED));
              widget_text       (IO_ID_ROW12,    lsub(TX_IO_UNUSED));
              widget_label      (IO_INPUT_ROW12, lsub(TX_IO_UNUSED));
     break;     
    
    
    case SCREEN_MP1:  
      /* ******************************** */
      /*          MP page 1               */
      /* ******************************** */ 
      
        // First Column                                
                                              
              // First Row Info 
              widget_text       (MP_ROW1_ID,    lsub(TX_MPSAMPLEFREQUENCY));
              widget_label      (MP_ROW1_INPUT, lsub(TX_MPSAMPLEFREQUENCY));
        
              // 2nd Row Info 
              widget_text       (MP_ROW2_ID,    lsub(TX_MPSAMPLESIZE));
              widget_label      (MP_ROW2_INPUT, lsub(TX_MPSAMPLESIZE));
                                               
              // Third Row Info 
              widget_text       (MP_ROW3_ID,    lsub(TX_MPZEROFREQUENCY)); 
              widget_label      (MP_ROW3_INPUT, lsub(TX_MPZEROFREQUENCY));       
                                              
              // Fourth Row Info
              widget_text       (MP_ROW4_ID,    lsub(TX_MPZEROLIMIT));
              widget_label      (MP_ROW4_INPUT, lsub(TX_MPZEROLIMIT));
                                               
              // Fifth Row Info
              widget_text       (MP_ROW5_ID,     lsub(TX_MPAUTOZEROOFF));
              widget_text       (MP_ROW5_SELECT, lsub(TX_OFF), 0);
              widget_text       (MP_ROW5_SELECT, lsub(TX_ON), 1);
                                   
              // Sixth Row Info 
              widget_text       (MP_ROW6_ID,    lsub(TX_MPSCREENSAVERTIME)); 
              widget_label      (MP_ROW6_INPUT, lsub(TX_MPSCREENSAVERTIME));       
              
        // Second Column                               

              // First Row Info 
              widget_text       (MP_ROW7_ID,    lsub(TX_MPDISCHDOORMAXTIME)); 
              widget_label      (MP_ROW7_INPUT, lsub(TX_MPDISCHDOORMAXTIME));
        
              // 2nd Row Info
              widget_text       (MP_ROW8_ID,    lsub(TX_MPSLOWCYCLETIME));
              widget_label      (MP_ROW8_INPUT, lsub(TX_MPSLOWCYCLETIME));
               
              // Third Row Info 
              widget_text       (MP_ROW9_ID,    lsub(TX_MPFEEDGATEMAXTIME));
              widget_label      (MP_ROW9_INPUT, lsub(TX_MPFEEDGATEMAXTIME));
                                            
              // Fourth Row Info 
              widget_text       (MP_ROW10_ID,    lsub(TX_MPOUTOFTOLTIME));
              widget_label      (MP_ROW10_INPUT, lsub(TX_MPOUTOFTOLTIME));
                                               
              // Fifth Row Info 
              widget_text       (MP_ROW11_ID,    lsub(TX_MPFEEDRATEFILTERRATIO));
              widget_label      (MP_ROW11_INPUT, lsub(TX_MPFEEDRATEFILTERRATIO));
                                              
              // Sixth Row Info 
              widget_text       (MP_ROW12_ID,    lsub(TX_MPSTABTIMELIMIT));
              widget_label      (MP_ROW12_INPUT, lsub(TX_MPSTABTIMELIMIT));
              
              
     break;        

    case SCREEN_MP2:  
      /* ******************************** */
      /*          MP page 2               */
      /* ******************************** */ 
      
        // First Column                                
                                              
              // First Row Info 
              widget_text       (MP_ROW13_ID,     lsub(TX_MPCORRECTIONONAVERAGE));
              widget_text       (MP_ROW13_SELECT, lsub(TX_OFF), 0);
              widget_text       (MP_ROW13_SELECT, lsub(TX_ON), 1);
        
              // 2nd Row Info 
              widget_text       (MP_ROW14_ID,    lsub(TX_MPCUTOFFCORRECTIONLIMIT));
              widget_label      (MP_ROW14_INPUT, lsub(TX_MPCUTOFFCORRECTIONLIMIT));
                                               
              // Third Row Info 
              widget_text       (MP_ROW15_ID,    lsub(TX_MPDFWEIGHTCORRECTION));
              widget_label      (MP_ROW15_INPUT, lsub(TX_MPDFWEIGHTCORRECTION));
                                              
              // Fourth Row Info 
              widget_text       (MP_ROW16_ID,    lsub(TX_MPCUTOFFCORRECTION));
              widget_label      (MP_ROW16_INPUT, lsub(TX_MPCUTOFFCORRECTION));
                           
              // Fifth Row Info 
              widget_text       (MP_ROW17_ID,    lsub(TX_MPMAXFEEDRATE));
              widget_label      (MP_ROW17_INPUT, lsub(TX_MPMAXFEEDRATE));
                                              
              // Sixth Row Info 
              widget_text       (MP_ROW18_ID,    lsub(TX_MPLOWFEEDINGTIME));
              widget_label      (MP_ROW18_INPUT, lsub(TX_MPLOWFEEDINGTIME));
              
              
        // Second Column                               

              // First Row Info 
              widget_text       (MP_ROW19_ID,    lsub(TX_MPENDOFSHIFT1));
              widget_label      (MP_ROW19_INPUT, lsub(TX_MPENDOFSHIFT1));
        
              // 2nd Row Info
              widget_text       (MP_ROW20_ID,    lsub(TX_MPENDOFSHIFT2));
              widget_label      (MP_ROW20_INPUT, lsub(TX_MPENDOFSHIFT2));
                                               
              // Third Row Info 
              widget_text       (MP_ROW21_ID,    lsub(TX_MPENDOFSHIFT3));
              widget_label      (MP_ROW21_INPUT, lsub(TX_MPENDOFSHIFT3));
                                            
              // Fourth Row Info 
              widget_text       (MP_ROW22_ID,    lsub(TX_MPSTDFILTER));
              widget_label      (MP_ROW22_INPUT, lsub(TX_MPSTDFILTER));
              
              // Fifth Row Info 
              widget_text       (MP_ROW23_ID,    lsub(TX_MPENDOFSHIFT4));
              widget_label      (MP_ROW23_INPUT, lsub(TX_MPENDOFSHIFT4));
              
              widget_text       (MP_ROW24_ID,    lsub(TX_MPMAINTCYCCLE));
              widget_label      (MP_ROW24_INPUT, lsub(TX_MPMAINTCYCCLE));
                                               

              
                                                
     break;

    case SCREEN_MP3:  
      /* ******************************** */
      /*          MP page 3               */
      /* ******************************** */ 
      
        // First Column                                
                                              
              // First Row Info 
              widget_text       (MP_ROW25_ID,    lsub(TX_MPT1));
              widget_label      (MP_ROW25_INPUT, lsub(TX_MPT1));
        
              // 2nd Row Info
              widget_text       (MP_ROW26_ID,    lsub(TX_MPT2));
              widget_label      (MP_ROW26_INPUT, lsub(TX_MPT2));
                                               
              // Third Row Info 
              widget_text       (MP_ROW27_ID,    lsub(TX_FLEXCOUNTER));
              widget_label      (MP_ROW27_INPUT, lsub(TX_FLEXCOUNTER));
              
              // Fourth Row Info 
              widget_text       (MP_ROW28_ID,     lsub(TX_MPINVERTFEEDANDDISCHOUTPUTS));
              widget_text       (MP_ROW28_SELECT, lsub(TX_OFF), 0);
              widget_text       (MP_ROW28_SELECT, lsub(TX_ON), 1);
              
        // Second Column   
        
              // First Row Info 
              widget_text       (MP_ROW31_ID,    lsub(TX_MPSP1)); 
              widget_label      (MP_ROW31_INPUT, lsub(TX_MPSP1));
        
              // 2nd Row Info
              widget_text       (MP_ROW32_ID,    lsub(TX_MPSP2));
              widget_label      (MP_ROW32_INPUT, lsub(TX_MPSP2)); 
              
              // 3rd Row Info
              widget_text       (MP_ROW33_ID,     lsub(TX_MPFAILSAFE));
              widget_text       (MP_ROW33_SELECT, lsub(TX_OFF), 0);
              widget_text       (MP_ROW33_SELECT, lsub(TX_ON), 1);
              
              // 4rd Row Info
              widget_text       (MP_ROW34_ID,     lsub(TX_STOPWITHGATESANDDISCHOPEN));
              widget_text       (MP_ROW34_SELECT, lsub(TX_OFF), 0);
              widget_text       (MP_ROW34_SELECT, lsub(TX_ON), 1);                           

                                                
     break;

    case SCREEN_MP4:  
      /* ******************************** */
      /*          MP page 4               */
      /* ******************************** */ 
      
        // First Column                                
                                              
              // First Row Info 
              widget_text       (MP_ROW39_ID,    lsub(TX_SaveMP2Def));
        
              // 2nd Row Info 
              widget_text       (MP_ROW45_ID,    lsub(TX_RestDef2MP));

     break;

    case SCREEN_TDMANAGE:  
      /* ******************************** */
      /*     Time & Management Page       */
      /* ******************************** */ 
      
              widget_text       (TDMANAGE_ID,    lsub(TX_TDMANAGE_MENU));
              widget_text       (TDMANAGE_TIME_DISPLAY, concat (space(1),lsub(TX_TDMANAGE_DATE),space(1), date, space(2),lsub(TX_TDMANAGE_TIME), space(1), time , space(1)));

        
             RefreshCurrentUser();                                 
        
        // First Column                                
                                              
              // First Row Info 
              widget_text       (TDMANAGE_DAY_ID,       lsub(TX_TDMANAGE_DAY_ID));
              widget_label      (TDMANAGE_DAY_INPUT,    lsub(TX_TDMANAGE_DAY_ID));
              widget_text       (TDMANAGE_HOUR_ID,      lsub(TX_TDMANAGE_HOUR_ID));
              widget_label      (TDMANAGE_HOUR_INPUT,   lsub(TX_TDMANAGE_HOUR_ID));
        
              // 2nd Row Info 
              widget_text       (TDMANAGE_MONTH_ID,     lsub(TX_TDMANAGE_MONTH_ID));
              widget_label      (TDMANAGE_MONTH_INPUT,  lsub(TX_TDMANAGE_MONTH_ID));
              widget_text       (TDMANAGE_MINUTE_ID,    lsub(TX_TDMANAGE_MINUTE_ID));
              widget_label      (TDMANAGE_MINUTE_INPUT, lsub(TX_TDMANAGE_MINUTE_ID));
              
              // 3rd Row Info 
              widget_text       (TDMANAGE_YEAR_ID,     lsub(TX_TDMANAGE_YEAR_ID)); 
              widget_label      (TDMANAGE_YEAR_INPUT,  lsub(TX_TDMANAGE_YEAR_ID)); 

     break;


    case SCREEN_MC1:  
      /* ******************************** */
      /*          MC page 1               */
      /* ******************************** */ 
      
        // First Column     
                                              
              // First Row Info 
              widget_text       (MC_ROW1_ID,    lsub(TX_MCBULKBLANKTIME));
              widget_label      (MC_ROW1_INPUT, lsub(TX_MCBULKBLANKTIME));
        
              // 2nd Row Info 
              widget_text       (MC_ROW2_ID,    lsub(TX_MCDRIBBLANKTIME));
              widget_label      (MC_ROW2_INPUT, lsub(TX_MCDRIBBLANKTIME));
                                               
              // Third Row Info 
              widget_text       (MC_ROW3_ID,    lsub(TX_MCLOWLEVELDEBOUNCETIME));
              widget_label      (MC_ROW3_INPUT, lsub(TX_MCLOWLEVELDEBOUNCETIME));
                                              
              // Fourth Row Info 
              widget_text       (MC_ROW4_ID,    lsub(TX_MCREFILLINGTIME));
              widget_label      (MC_ROW4_INPUT, lsub(TX_MCREFILLINGTIME));
                                               
              // Fifth Row Info 
              widget_text       (MC_ROW5_ID,    lsub(TX_MCNUMBEROFWP));
              widget_label      (MC_ROW5_INPUT, lsub(TX_MCNUMBEROFWP));
                                              
              // Sixth Row Info 
              widget_text       (MC_ROW6_ID,     lsub(TX_MCWEIGHINGMODE));
              widget_text       (MC_ROW6_SELECT, lsub(TX_MCMONITORING), 0);
              widget_text       (MC_ROW6_SELECT, lsub(TX_MCTIMECONTROL), 1);
              widget_text       (MC_ROW6_SELECT, lsub(TX_MCFEEDRATECONTROL), 2);
              widget_text       (MC_ROW6_SELECT, lsub(TX_MCBATCH), 3);
              widget_text       (MC_ROW6_SELECT, lsub(TX_MCBULK), 4);
              widget_text       (MC_ROW6_SELECT, lsub(TX_MCFLOWTHROUGH), 5);
              
        // Second Column                               

              // First Row Info 
              widget_text       (MC_ROW7_ID,     lsub(TX_MCFEEDERTYPE));
              // 2nd Row Info 
              widget_text       (MC_ROW8_ID,    lsub(TX_MCNBROFSCALE));
              widget_label      (MC_ROW8_INPUT, lsub(TX_MCNBROFSCALE));
                                               
              // Third Row Info 
              widget_text       (MC_ROW10_ID,     lsub(TX_MCLANGUAGE1));     
                                            
              // Fourth Row Info
              widget_text       (MC_ROW11_ID, lsub(TX_MCLANGUAGE2)); 
                                               
              // Fifth Row Info 
              widget_text       (MC_ROW12_ID, lsub(TX_MCLANGUAGE3)); 
                                              
              // Sixth Row Info 
              widget_text       (MC_ROW9_ID,     lsub(TX_MCOIML));
              widget_text       (MC_ROW9_SELECT, lsub(TX_WPNO), 0);
              widget_text       (MC_ROW9_SELECT, lsub(TX_WPYES), 1); 
       
     break;        

    case SCREEN_MC2:  
      /* ******************************** */
      /*          MC page 2               */
      /* ******************************** */ 
      
        // First Column                                
                    
              // First Row Info 
              widget_text       (MC_ROW13_ID,     lsub(TX_PortCom2));
              widget_text       (MC_ROW13_SELECT, lsub(TX_MCNone), COM2FctNone);
              widget_text       (MC_ROW13_SELECT, lsub(TX_FctContinuousOut),COM2FctContinuousOut);
              widget_text       (MC_ROW13_SELECT, lsub(TX_FctUnitRecString),COM2FctUnitRecString);
              widget_text       (MC_ROW13_SELECT, lsub(TX_FctReportToPrinter),COM2FctReportToPrinter);
        
              // 2nd Row Info 
              widget_text       (MC_ROW14_ID,     lsub(TX_PortUSB));
              widget_text       (MC_ROW14_SELECT, lsub(TX_MCNone), USBFctNone);
              widget_text       (MC_ROW14_SELECT, lsub(TX_FctUnitRecString),USBFctUnitRecString);
              widget_text       (MC_ROW14_SELECT, lsub(TX_FctUnitRecFile), USBFctUnitRecFile);
              widget_text       (MC_ROW14_SELECT, lsub(TX_FctReportToPrinter),USBFctReportToPrinter);
              //widget_text       (MC_ROW14_SELECT, lsub(TX_FctReportToFile),USBFctReportToFile);
                                               
              // Third Row Info 
              widget_text       (MC_ROW15_ID,     lsub(TX_MCAUTOSAVECORRECTION));
              widget_text       (MC_ROW15_SELECT, lsub(TX_WPNO), 0);
              widget_text       (MC_ROW15_SELECT, lsub(TX_WPYES), 1);
                                              
              // Fourth Row Info 
              widget_text       (MC_ROW16_ID,    lsub(TX_MCDISCHREQDEBOUNCING));
              widget_label      (MC_ROW16_INPUT, lsub(TX_MCDISCHREQDEBOUNCING));
                                                 
              // Fifth Row Info 
              widget_text       (MC_ROW17_ID,     lsub(TX_PortEthernet));
              widget_text       (MC_ROW17_SELECT, lsub(TX_MCNone), ETHFctNone);
              widget_text       (MC_ROW17_SELECT, lsub(TX_FctContinuousOut),ETHFctContinuousOut);
              widget_text       (MC_ROW17_SELECT, lsub(TX_FctReportToPrinter),ETHFctReportToPrinter);  
                                              
              // Sixth Row Info 
              widget_text       (MC_ROW18_ID,     lsub(TX_PrinterIP));
              widget_text       (MC_ROW18_INPUT, lsub(TX_PrinterIP));
              
              
        // Second Column                               

              // First Row Info 
              widget_text       (MC_ROW19_ID,     lsub(TX_MCDISCHARGEONDOORSENSOR)); 
              widget_text       (MC_ROW19_SELECT, lsub(TX_WPNO), 0);
              widget_text       (MC_ROW19_SELECT, lsub(TX_WPYES), 1);
        
              // 2nd Row Info 
              widget_text       (MC_ROW20_ID,     lsub(TX_MCDRIBBLEOUTONINBULK));
              widget_text       (MC_ROW20_SELECT, lsub(TX_OFF), 0);
              widget_text       (MC_ROW20_SELECT, lsub(TX_ON), 1);
                                               
              // Third Row Info 
              widget_text       (MC_ROW21_ID,    lsub(TX_MCPLANTLINENAME));
              widget_label      (MC_ROW21_INPUT, lsub(TX_MCPLANTLINENAME));
                                            
              // Fourth Row Info 
              widget_text       (MC_ROW22_ID,    lsub(TX_MCSERIALNBR));
              widget_label      (MC_ROW22_INPUT, lsub(TX_MCSERIALNBR));
                                               
              // Fifth Row Info 
              widget_text       (MC_ROW23_ID,    lsub(TX_MCCUSTOMERNAME));
              widget_label      (MC_ROW23_INPUT, lsub(TX_MCCUSTOMERNAME));
                                              
              // Sixth Row Info  
              widget_text       (MC_ROW24_ID,    lsub(TX_MCCUSTOMERLOCATION)); 
              widget_label      (MC_ROW24_INPUT, lsub(TX_MCCUSTOMERLOCATION));       
     break;

    case SCREEN_MC3:  
      /* ******************************** */
      /*          MC page 3               */
      /* ******************************** */ 
      
        // First Column                                
                                              
              // First Row Info 
              widget_text       (MC_ROW25_ID,    lsub(TX_MCPASSWORDOP));
              widget_label      (MC_ROW25_INPUT, lsub(TX_MCPASSWORDOP));
        
              // 2nd Row Info 
              widget_text       (MC_ROW26_ID,    lsub(TX_MCPASSWORDSUP));
              widget_label      (MC_ROW26_INPUT, lsub(TX_MCPASSWORDSUP));
                                               
              // Third Row Info 
              widget_text       (MC_ROW27_ID,    lsub(TX_MCPASSWORDPT));
              widget_label      (MC_ROW27_INPUT, lsub(TX_MCPASSWORDPT));
                                              
              // Fourth Row Info 
              widget_text       (MC_ROW28_ID,    lsub(TX_MCSUPPORTPHONENBR));
              widget_label      (MC_ROW28_INPUT, lsub(TX_MCSUPPORTPHONENBR));
                                               
              // Fifth Row Info 
              widget_text       (MC_ROW29_ID,    lsub(TX_MCSUPPORTEMAIL));
              widget_label      (MC_ROW29_INPUT, lsub(TX_MCSUPPORTEMAIL));
                                              
              // Sixth Row Info 
              widget_text       (MC_ROW30_ID,    lsub(TX_MCTRIALDAYS));
              widget_label      (MC_ROW30_INPUT, lsub(TX_MCTRIALDAYS));

                            
        // Second Column                               

              // First Row Info 
              widget_text       (MC_ROW31_ID,    lsub(TX_MCLOGOUTDELAYOP)); 
              widget_label      (MC_ROW31_INPUT, lsub(TX_MCLOGOUTDELAYOP));
        
              // 2nd Row Info 
              widget_text       (MC_ROW32_ID,    lsub(TX_MCLOGOUTDELAYSUP));
              widget_label      (MC_ROW32_INPUT, lsub(TX_MCLOGOUTDELAYSUP));
                                               
              // Third Row Info 
              widget_text       (MC_ROW33_ID,    lsub(TX_MCLOGOUTDELAYPT));
              widget_label      (MC_ROW33_INPUT, lsub(TX_MCLOGOUTDELAYPT));
                                            
              // Fourth Row Info 
              widget_text       (MC_ROW34_ID,    lsub(TX_MCPARTSPHONENBR));
              widget_label      (MC_ROW34_INPUT, lsub(TX_MCPARTSPHONENBR));
                                               
              // Fifth Row Info
              widget_text       (MC_ROW35_ID,    lsub(TX_MCPARTSEMAIL));
              widget_label      (MC_ROW35_INPUT, lsub(TX_MCPARTSEMAIL));
                                              
              // Sixth Row Info
              widget_text       (MC_ROW36_ID,    lsub(TX_MCUSBMOUSE)); 
              widget_label      (MC_ROW36_INPUT, lsub(TX_MCUSBMOUSE)); 
                  
     break;

    case SCREEN_MC4:  
      /* ******************************** */
      /*          MC page 4               */
      /* ******************************** */ 
      
        // First Column                                
                                              
              // First Row Info 
              widget_text       (MC_ROW39_ID,    lsub(TX_SaveMC2Def));
        
              // 2nd Row Info 
              widget_text       (MC_ROW45_ID,    lsub(TX_RestDef2MC));

     break;

    case SCREEN_FLEXIO_1:  
      /* ******************************** */
      /*          Flex IO page 1          */
      /* ******************************** */ 
      
      LoadIONames();
      
        // First Column                                 
           widget_text       (FLEX_ROW5_UNIT,     concat (lsub(TX_OUTPUT), space(1),"1", space(1),lsub(TX_ON))); 
           widget_text       (FLEX_ROW1_ID,     lsub(TX_FLEXIOTYPE));
           widget_text       (FLEX_ROW1_SELECT, lsub(TX_INPUT),0);
           widget_text       (FLEX_ROW1_SELECT, lsub(TX_OUTPUT),1);
           widget_text       (FLEX_ROW1_SELECT, lsub(TX_FLEXSETPOINT),2);
           widget_text       (FLEX_ROW2_ID,     lsub(TX_FLEXSETPOINT));
           widget_text       (FLEX_ROW2_SELECT, lsub(TX_LES),0);
           widget_text       (FLEX_ROW2_SELECT, lsub(TX_GRT),1);
           widget_text       (FLEX_ROW3_SELECT, lsub(TX_FLEXWPSP1),0);
           widget_text       (FLEX_ROW3_SELECT, lsub(TX_FLEXWPSP2),1);
           widget_text       (FLEX_ROW3_SELECT, lsub(TX_FLEXMPSP1),2);
           widget_text       (FLEX_ROW3_SELECT, lsub(TX_FLEXMPSP2),3);
           widget_text       (FLEX_ROW4_ID,     lsub(TX_FLEXIO));
           widget_text       (FLEX_ROW4_INPUT,  IO_Name[FlexIO_IOEnum[Flex_Out1][ON]]);
           widget_text       (FLEX_ROW5_ID,     lsub(TX_FLEXSWITCH));
           widget_text       (FLEX_ROW5_SELECT, lsub(TX_FLEXOFF),0);
           widget_text       (FLEX_ROW5_SELECT, lsub(TX_FLEXON),1);
           widget_text       (FLEX_ROW6_ID,     lsub(TX_FLEXTIMER));
           widget_text       (FLEX_ROW6_SELECT, lsub(TX_NONE),0);
           widget_text       (FLEX_ROW6_SELECT, lsub(TX_FLEXWPT1),1);
           widget_text       (FLEX_ROW6_SELECT, lsub(TX_FLEXWPT2),2);
           widget_text       (FLEX_ROW6_SELECT, lsub(TX_FLEXMPT1),3);
           widget_text       (FLEX_ROW6_SELECT, lsub(TX_FLEXMPT2),4);
              
        // Second Column  
           widget_text       (FLEX_ROW11_UNIT,     concat (lsub(TX_OUTPUT), space(1),"1", space(1),lsub(TX_OFF))); 
           widget_text       (FLEX_ROW7_ID,      lsub(TX_FLEXIOTYPE));
           widget_text       (FLEX_ROW7_SELECT,  lsub(TX_INPUT),0);
           widget_text       (FLEX_ROW7_SELECT,  lsub(TX_OUTPUT),1);
           widget_text       (FLEX_ROW7_SELECT,  lsub(TX_FLEXSETPOINT),2);
           widget_text       (FLEX_ROW8_ID,      lsub(TX_FLEXSETPOINT));
           widget_text       (FLEX_ROW8_SELECT,  lsub(TX_LES),0);
           widget_text       (FLEX_ROW8_SELECT,  lsub(TX_GRT),1);
           widget_text       (FLEX_ROW9_SELECT,  lsub(TX_FLEXWPSP1),0);
           widget_text       (FLEX_ROW9_SELECT,  lsub(TX_FLEXWPSP2),1);
           widget_text       (FLEX_ROW9_SELECT,  lsub(TX_FLEXMPSP1),2);
           widget_text       (FLEX_ROW9_SELECT,  lsub(TX_FLEXMPSP2),3);
           widget_text       (FLEX_ROW10_ID,     lsub(TX_FLEXIO));
           widget_text       (FLEX_ROW10_INPUT,  IO_Name[FlexIO_IOEnum[Flex_Out1][OFF]]);
           widget_text       (FLEX_ROW11_ID,     lsub(TX_FLEXSWITCH));
           widget_text       (FLEX_ROW11_SELECT, lsub(TX_FLEXOFF),0);
           widget_text       (FLEX_ROW11_SELECT, lsub(TX_FLEXON),1);
           widget_text       (FLEX_ROW12_ID,     lsub(TX_FLEXTIMER));
           widget_text       (FLEX_ROW12_SELECT, lsub(TX_NONE),0);
           widget_text       (FLEX_ROW12_SELECT, lsub(TX_FLEXWPT1),1);
           widget_text       (FLEX_ROW12_SELECT, lsub(TX_FLEXWPT2),2);
           widget_text       (FLEX_ROW12_SELECT, lsub(TX_FLEXMPT1),3);
           widget_text       (FLEX_ROW12_SELECT, lsub(TX_FLEXMPT2),4);
      
       

     break;

    case SCREEN_FLEXIO_2:  
      /* ******************************** */
      /*          Flex IO page 2          */
      /* ******************************** */ 
      
        // First Column                                 
           widget_text       (FLEX_ROW17_UNIT,     concat (lsub(TX_OUTPUT), space(1),"2", space(1),lsub(TX_ON))); 
           widget_text       (FLEX_ROW13_ID,     lsub(TX_FLEXIOTYPE));
           widget_text       (FLEX_ROW13_SELECT, lsub(TX_INPUT),0);
           widget_text       (FLEX_ROW13_SELECT, lsub(TX_OUTPUT),1);
           widget_text       (FLEX_ROW13_SELECT, lsub(TX_FLEXSETPOINT),2);
           widget_text       (FLEX_ROW14_ID,     lsub(TX_FLEXSETPOINT));
           widget_text       (FLEX_ROW14_SELECT, lsub(TX_LES),0);
           widget_text       (FLEX_ROW14_SELECT, lsub(TX_GRT),1);
           widget_text       (FLEX_ROW15_SELECT, lsub(TX_FLEXWPSP1),0);
           widget_text       (FLEX_ROW15_SELECT, lsub(TX_FLEXWPSP2),1);
           widget_text       (FLEX_ROW15_SELECT, lsub(TX_FLEXMPSP1),2);
           widget_text       (FLEX_ROW15_SELECT, lsub(TX_FLEXMPSP2),3);
           widget_text       (FLEX_ROW16_ID,     lsub(TX_FLEXIO));
           widget_text       (FLEX_ROW16_INPUT,  IO_Name[FlexIO_IOEnum[Flex_Out2][ON]]);
           widget_text       (FLEX_ROW17_ID,     lsub(TX_FLEXSWITCH));
           widget_text       (FLEX_ROW17_SELECT, lsub(TX_FLEXOFF),0);
           widget_text       (FLEX_ROW17_SELECT, lsub(TX_FLEXON),1);
           widget_text       (FLEX_ROW18_ID,     lsub(TX_FLEXTIMER));
           widget_text       (FLEX_ROW18_SELECT, lsub(TX_NONE),0);
           widget_text       (FLEX_ROW18_SELECT, lsub(TX_FLEXWPT1),1);
           widget_text       (FLEX_ROW18_SELECT, lsub(TX_FLEXWPT2),2);
           widget_text       (FLEX_ROW18_SELECT, lsub(TX_FLEXMPT1),3);
           widget_text       (FLEX_ROW18_SELECT, lsub(TX_FLEXMPT2),4);
              
        // Second Column  
           widget_text       (FLEX_ROW23_UNIT,     concat (lsub(TX_OUTPUT), space(1),"2", space(1),lsub(TX_OFF))); 
           widget_text       (FLEX_ROW19_ID,     lsub(TX_FLEXIOTYPE));
           widget_text       (FLEX_ROW19_SELECT, lsub(TX_INPUT),0);
           widget_text       (FLEX_ROW19_SELECT, lsub(TX_OUTPUT),1);
           widget_text       (FLEX_ROW19_SELECT, lsub(TX_FLEXSETPOINT),2);
           widget_text       (FLEX_ROW20_ID,     lsub(TX_FLEXSETPOINT));
           widget_text       (FLEX_ROW20_SELECT, lsub(TX_LES),0);
           widget_text       (FLEX_ROW20_SELECT, lsub(TX_GRT),1);
           widget_text       (FLEX_ROW21_ID,     lsub(TX_FLEXSWITCH));
           widget_text       (FLEX_ROW21_SELECT, lsub(TX_FLEXWPSP1),0);
           widget_text       (FLEX_ROW21_SELECT, lsub(TX_FLEXWPSP2),1);
           widget_text       (FLEX_ROW21_SELECT, lsub(TX_FLEXMPSP1),2);
           widget_text       (FLEX_ROW21_SELECT, lsub(TX_FLEXMPSP2),3);
           widget_text       (FLEX_ROW22_ID,     lsub(TX_FLEXIO));
           widget_text       (FLEX_ROW22_INPUT,  IO_Name[FlexIO_IOEnum[Flex_Out2][OFF]]);
           widget_text       (FLEX_ROW23_ID,     lsub(TX_FLEXSWITCH));
           widget_text       (FLEX_ROW23_SELECT, lsub(TX_FLEXOFF),0);
           widget_text       (FLEX_ROW23_SELECT, lsub(TX_FLEXON),1);
           widget_text       (FLEX_ROW24_ID,     lsub(TX_FLEXTIMER));
           widget_text       (FLEX_ROW24_SELECT, lsub(TX_NONE),0);
           widget_text       (FLEX_ROW24_SELECT, lsub(TX_FLEXWPT1),1);
           widget_text       (FLEX_ROW24_SELECT, lsub(TX_FLEXWPT2),2);
           widget_text       (FLEX_ROW24_SELECT, lsub(TX_FLEXMPT1),3);
           widget_text       (FLEX_ROW24_SELECT, lsub(TX_FLEXMPT2),4);

     break;

    case SCREEN_FLEXIO_3:  
      /* ******************************** */
      /*          Flex IO page 3          */
      /* ******************************** */ 
      
        // First Column                                 
           widget_text       (FLEX_ROW29_UNIT,   lsub(TX_FLEXCONFIG)); 
           widget_text       (FLEX_ROW25_ID,     lsub(TX_FLEXCNTMODE));
           widget_text       (FLEX_ROW25_SELECT, lsub(TX_FLEXCNTPRESET),0);
           widget_text       (FLEX_ROW25_SELECT, lsub(TX_FLEXCNTPULSE),1);
           widget_text       (FLEX_ROW26_ID,     lsub(TX_FLEXIOTYPE));
           widget_text       (FLEX_ROW26_SELECT, lsub(TX_INPUT),0);
           widget_text       (FLEX_ROW26_SELECT, lsub(TX_OUTPUT),1);
           widget_text       (FLEX_ROW27_ID,     lsub(TX_FLEXIO));
           widget_text       (FLEX_ROW27_INPUT,  IO_Name[FlexIO_IOEnum[Flex_Out3][ON]]);
           widget_text       (FLEX_ROW28_ID,     lsub(TX_FLEXPRESOURCE));
           widget_text       (FLEX_ROW28_SELECT, lsub(TX_FLEXWPCOUNTER),0);
           widget_text       (FLEX_ROW28_SELECT, lsub(TX_FLEXMPCOUNTER),1);

              
        // Second Column  
           widget_text       (FLEX_ROW35_UNIT,   lsub(TX_FLEXTIMERS)); 
           widget_text       (FLEX_ROW31_ID,     lsub(TX_FLEXINITDELAY));
           widget_label      (FLEX_ROW31_INPUT,  lsub(TX_FLEXINITDELAY));
           widget_text       (FLEX_ROW32_ID,     lsub(TX_FLEXONTIME));
           widget_label      (FLEX_ROW32_INPUT,  lsub(TX_FLEXONTIME));
           widget_text       (FLEX_ROW33_ID,     lsub(TX_FLEXOFFTIME));
           widget_label      (FLEX_ROW33_INPUT,  lsub(TX_FLEXOFFTIME));

     break;
     
    case SCREEN_REPORT:   
      
      /* ******************************** */
      /*       Report page                */
      /* ******************************** */
      
      // Header
        widget_text       (REPORT_SEARCH_ID, lsub(TX_REPORT_PAGE));
     
        // First Column                                
                                              
              widget_text       (REPORT_ROW7_ID, lsub(TX_ID_ACTUAL_PROD));
              
              // First Row Info 
              widget_text       (REPORT_ROW1_ID, lsub(TX_ID_NOMINAL_WEIGHT));
        
              // 2nd Row Info 
              widget_text       (REPORT_ROW2_ID, lsub(TX_ID_UNITS_DONE));
                                               
              // Third Row Info 
              widget_text       (REPORT_ROW3_ID, lsub(TX_ID_UNITS_ACCEPTED));
              
                                              
              // Fourth Row Info 
              widget_text       (REPORT_ROW4_ID, lsub(TX_ID_UNDERWEIGHT));
                                               
              // Fifth Row Info 
              widget_text       (REPORT_ROW5_ID, lsub(TX_ID_OVERWEIGHT));
                                              
              // Sixth Row Info 
              widget_text       (REPORT_ROW6_ID, lsub(TX_ID_TOTAL_WEIGHT));
              
        // Second Column                               
                                              
              widget_text       (REPORT_ROW14_ID, lsub(TX_ID_LIFETIME_PROD));
              
              // First Row Info 
              widget_text       (REPORT_ROW8_ID, lsub(TX_ID_TOTAL_WEIGHMENTS));
        
              // 2nd Row Info 
              widget_text       (REPORT_ROW9_ID, lsub(TX_ID_TOTAL_UNITS));
                                               
              // Third Row Info 
              widget_text       (REPORT_ROW10_ID, lsub(TX_ID_TOTAL_WEIGHT)/*+"x1000"*/);
              
              // Fifth Row Info
              widget_text       (REPORT_ROW12_ID, lsub(TX_SILOSTOCK_ID));
              
              // Sixth Row Info
              widget_text       (REPORT_ROW13_ID, lsub(TX_SILONO_ID));
              

        /* Print Ticket form text */ 
        RefreshProdRepTexts();
    
     break;
    
    case SCREEN_BATCH:
          // Header
               widget_text       (REPORT_SEARCH_ID, lsub(TX_BATCH_PAGE));
               widget_text       (REPORT_ROW7_ID, concat(lsub(TX_BATCH_CURRENT_PROD),":"));
               
               widget_text         (REPORT_ROW7_INPUT,  concat("(",lsub(WP.Name),")"));
                                                
                // First Row Info 
                widget_text       (REPORT_BATCHNAME_ID,    lsub(TX_BATCH_NAME));
                widget_label      (REPORT_BATCHNAME_INPUT, lsub(TX_BATCH_NAME));
          
                // 2nd Row Info 
                widget_text       (REPORT_BATCHPRESET_ID,    lsub(TX_BATCH_PRESET));
                widget_label      (REPORT_BATCHPRESET_INPUT, lsub(TX_BATCH_PRESET));
                                                 
                // Third Row Info 
                widget_text       (REPORT_ROW3_ID,    lsub(TX_ID_UNITS_DONE));
                                                
                // Fourth Row Info 
                widget_text       (REPORT_ROW4_ID,    lsub(TX_ID_UNITS_ACCEPTED));
                                                 
                // Fifth Row Info 
                widget_text       (REPORT_ROW5_ID,    lsub(TX_ID_UNDERWEIGHT));
                                                
                // Sixth Row Info 
                widget_text       (REPORT_ROW6_ID,    lsub(TX_ID_OVERWEIGHT));
                
                // Seventh Row Info 
                widget_text       (REPORT_BATCHDETAILS_ID,    lsub(TX_BATCH_DETAILS));
                widget_label      (REPORT_BATCHDETAILS_INPUT, lsub(TX_BATCH_DETAILS));
                
                
          // Second Column                               
                                                
                // First Row Info  
                widget_text       (REPORT_ROW8_ID,    lsub(TX_ID_TOTAL_WEIGHT)); 
          
                // 2nd Row Info 
                widget_text       (REPORT_ROW9_ID,    lsub(TX_BATCH_BEGIN_TIME)); //namk TX_BATCH_MIN_ACCEPTED
                                                 
                // Third Row Info 
                widget_text       (REPORT_ROW10_ID,    lsub(TX_BATCH_END_TIME));//TX_BATCH_MAX_ACCEPTED
                                                
                // Fourth Row Info 
                widget_text       (REPORT_ROW11_ID,    lsub(TX_BATCH_RESIDUE)); 
                                                 
                // Fifth Row Info 
                widget_text       (REPORT_ROW12_ID,    lsub(TX_STD_DEV));
                                                
                // Sixth Row Info 
                widget_text       (REPORT_ROW13_ID, lsub(TX_AVERAGE));
                
                // Seventh Row Info
                widget_text       (REPORT_BATCHCOUNTALL_ID,    lsub(TX_BATCH_COUNTALL));

        /* Print Ticket form text */ 
        RefreshBatchRepTexts();
        
     
          break;

     
    case SCREEN_GOTO:          

      /* ******************************** */
      /*       GoTo page                  */
      /* ******************************** */
      
      // Header
          widget_text (GOTO_RECIPE_ID, concat(space(1),lsub(WP.Name), space(1)));
          
      
          RefreshCurrentUser();                                 
      
      // Other Pages                                
          widget_text (GOTO_PAGE_HEADER, concat (space(1), lsub(TX_GOTO_PAGE), space(1)) ); 
       
      // Other Functions                                
          widget_text (GOTO_FNCT_HEADER, concat (space(1), lsub(TX_GOTO_FNCT), space(1)) );  
    
     break;
    
    case SCREEN_ACCESS:
     
      /* ******************************** */
      /*       Access page                */
      /* ******************************** */
      
      // Header
          widget_text (ACCESS_ID, concat (space(1), lsub(TX_ACCESS_PAGE), space(1)));
          
     // Login User
     
      
      // Username                               
          widget_text (ACCESS_USER_ID,           lsub(TX_USER) ); 
          widget_text (ACCESS_USER_SELECT,       lsub(TX_USER3),1);
          widget_text (ACCESS_USER_SELECT,       lsub(TX_USER2),2);
          widget_text (ACCESS_USER_SELECT,       lsub(TX_USER1),3);
       
      // Password                                
          widget_text  (ACCESS_PW_ID,             lsub(TX_PW) ); 
          widget_label (ACCESS_PW,                lsub(TX_PW) ); 
          
     break;
     
    case SCREEN_INFO:
 
      /* ******************************** */
      /*       Info page                */
      /* ******************************** */
      
      // Header
          widget_text (INFO_ID, concat (space(1), lsub(TX_INFO_PAGE), space(1)));
      
      // First Column
           // Customer Name 
           widget_text (INFO_ROW1_ID, lsub(TX_MCCUSTOMERNAME));
           
           // Customer Location 
           widget_text (INFO_ROW2_ID, lsub(TX_MCCUSTOMERLOCATION));
           
           // Plant Line Number
           widget_text (INFO_ROW3_ID, lsub(TX_MCPLANTLINENAME));

           
           // Systec indicator model 
           widget_text (INFO_ROW4_ID, lsub(TX_DEVICE_MODE));
           widget_text (INFO_ROW4_OUTPUT, lsub(RTC_Platform));
           
           // MAC address
           widget_text (INFO_ROW5_ID, concat (lsub(TX_MAC_ADDRESS), space(1), lsub(TX_IO_ADDRESS)));
           widget_text (INFO_ROW5_OUTPUT, RTC_MacAdress);
  
           // IP address

           widget_text (INFO_ROW6_ID, concat (lsub(TX_IP_ADDRESS), space(1), lsub(TX_IO_ADDRESS)));
           widget_text (INFO_ROW6_OUTPUT, IP_Address);
           
           // Serial number 
           widget_text (INFO_ROW7_ID, lsub(TX_MCSERIALNBR));
           
           // Scale type 
           widget_text (INFO_ROW8_ID, lsub(TX_SCALE_TYPE_ID));
           widget_text (INFO_ROW8_OUTPUT, lsub(TX_SCALE_TYPE));
           
       // Second Column     
           // Tech. Support 
           widget_text (INFO_ROW9_ID, lsub(TX_INFO_TECH_SUPPORT));
           
           // Telephon 
           widget_text (INFO_ROW10_ID, lsub(TX_INFO_TELEPHONE)); 
           
           // Fax
           //widget_text (INFO_ROW11_ID, lsub(TX_INFO_FAX));
           
           // E-mail
           widget_text (INFO_ROW12_ID, lsub(TX_INFO_EMAIL));
           
           // Tech. Support 
           widget_text (INFO_ROW13_ID, lsub(TX_INFO_PARTS));
           
            // Tech. Support 
           widget_text (INFO_ROW14_ID, lsub(TX_INFO_TELEPHONE));
           
           // Fax
           widget_text (INFO_ROW15_ID, lsub(TX_INFO_FAX));
           
           // E-mail
           widget_text (INFO_ROW16_ID, lsub(TX_INFO_EMAIL));
           
     break; 
            
    case SCREEN_FAULT: 
     
      /* ******************************** */
      /*       Fault page                 */
      /* ******************************** */

      // Header
          widget_text (FAULT_ID, concat (space(1), lsub(TX_FAULT_PAGE), space(1)));
          
      // Details
          widget_text (FAULT_LINE_HEADER, concat(space(FAULT_DETAIL_SPACE),lsub(TX_FAULT_DETAILS)));
          
      // Date
          widget_text  (FAULT_TIME_HEADER, concat(space(FAULT_TIME_SPACE),lsub(TX_FAULT_DATE))); 
     break;

    case SCREEN_WP_LIST_POPUP: 
      
      /* ******************************** */
      /*     Recipe List Popup page       */
      /* ******************************** */

      // Header
          widget_text           (ID_HEADLINE,   concat(space(1), lsub(TX_RECIPE_ID), space(5), lsub(TX_PRESSHERE)) );
        
     break;

    case SCREEN_LANG_LIST_POPUP:

      /* ******************************** */
      /*     Language List Popup page     */
      /* ******************************** */

      // Header
          widget_text           (ID_HEADLINE,   concat(space(1), lsub(TX_LANGUAGE_ID), space(5), lsub(TX_PRESSHERE)) );
        
     break;

    case SCREEN_FLEXIO_LIST_POPUP:

      /* ******************************** */
      /*     FlexIO Lisit Popup page      */
      /* ******************************** */

      // Header
          widget_text           (FLEX_DBASE_ID,   concat(space(1), lsub(TX_FLEXIOSELECT), space(5), lsub(TX_PRESSHERE)) );   
        
     break;

    case SCREEN_WPMANAGECOPY:

      /* ******************************** */
      /*     WP Management Copy Page      */
      /* ******************************** */

      // Header
          
          widget_text           (WPMANAGE_PAGE_HEADER,      concat (space(1), lsub(TX_WPMANAGECOPY_PAGE), space(1)) );  
          widget_text           (WPMANAGE_COPYSRCE_ID,      lsub(TX_WPMANAGE_CPY_SRCE) );  
          widget_text           (WPMANAGE_COPYDEST_ID,      lsub(TX_WPMANAGE_CPY_DEST) );  
        
     break;

    case SCREEN_WPMANAGERENAME:

      /* ******************************** */
      /*     WP Management Renam Page      */
      /* ******************************** */

      // Header
 
          
          widget_text           (WPMANAGE_PAGE_HEADER,     concat (space(1), lsub(TX_WPMANAGERENAME_PAGE), space(1)) );  
          widget_text           (WPMANAGE_RENSRCE_ID,      lsub(TX_WPMANAGE_REN_STR_SRCE) );  
          widget_text           (WPMANAGE_RENNEW_ID,       lsub(TX_WPMANAGE_REN_STR_NEW) );  
        
     break;

    case SCREEN_WPMANAGEDELETE:

      /* ******************************** */
      /*     WP Management Renam Page      */
      /* ******************************** */

      // Header
 
          
          widget_text           (WPMANAGE_PAGE_HEADER,      concat (space(1), lsub(TX_WPMANAGEDELETE_PAGE), space(1)) );  
          widget_text           (WPMANAGE_DELETE_ID,        lsub(TX_WPMANAGE_DEL_SRCE) );  
        
     break;
      
   }   
  enddraw();
 Init_Fault_Txt(); 
 Msg_Display_Refresh();
 LangRefreshed[Scrn_No] = ON;
}

/*------------------------------------------------------------------------------ 
--  Procedure Name    : iQRegistrationKeyCheck
--  Created by        : Steve Santerre
--  Last modified on  : 2016/06
--  
--  Purpose           : This function is called to Verify If the Key corresponds
--                      To Mac Address
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
-------------------------------------------------------------------------------*/ 
bool iQRegistrationKeyCheck(string EnteredKey,string MacAdress); 

/*------------------------------------------------------------------------- 
--  Procedure Name    : iQ_PT_Access
--  Created by        : Steve Santerre
--  Last modified on  : 2017/03
--  
--  Purpose           : This function is called to Verify If Login password
--                      corresponds to the coded formula
--                  
--------------------------------------------------------------------------*/ 
int iQ_PT_Access (void);

/***********************/
/* include the sources */
/***********************/
#ifdef IQ_HIDDEN_FUNCTIONS_DEBUG
  #include "iQHiddenFunctions.ccf"
#else
  #binary "iQHiddenFunctions.obj"
#endif


#include "Recipe.c"
#include "MachineParameters.c"
#include "MachineConfig.c"
#include "Report.c"
#include "Access.c"
#include "Fault.c"
#include "GoToPage.c"
#include "AutoPage.c"
#include "IO.c"




/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateConfirmPopupBox
--  Created by        : Steve Santerre
--  Last modified on  : 2017/10/18
--  
--  Purpose           : Confirm Popup window creation    
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateConfirmPopupBox (void)         
{
  begindraw();
    createwindow (CONFIRM_POPUP_WINDOW, WINDOW_TYPE_POPUP, "Popup Window");//  windowstyle (WD_INFO_BOX, ST_BOX_STYLE);
    windowstyle (CONFIRM_POPUP_WINDOW, POPUP_OUTBOX_STYLE);
      
      beginlayout (LAYOUT_TYPE_VBOX,0);
      
        beginlayout (LAYOUT_TYPE_VBOX,0);
         //Info Text
          createwidget (CONFIRM_POPUP, WIDGET_TYPE_TEXT_OUTPUT);
            widget_size_policy    (CONFIRM_POPUP,  SIZE_POLICY_MINIMUM, SIZE_POLICY_MINIMUM);
            widget_style          (CONFIRM_POPUP,  POPUP_BOXTEXT_STYLE);
            widget_fontsize       (CONFIRM_POPUP,  30);                                
            widget_text_alignment (CONFIRM_POPUP,  WIDGET_TEXT_ALIGN_HCENTER);
        endlayout();
       
        //Button Confirm" 
        beginlayout(LAYOUT_TYPE_HBOX, STD_EDGE_DISTANCE_NAVIG, FCT_BUTTON_DISTANCE_NAVIG);
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
          createwidget (YES_BOX,     WIDGET_TYPE_TEXT_OUTPUT);
          widget_image (YES_BOX,BTN_CHECK);
        
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
        endlayout();
      
      endlayout();
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateYesNoPopupBox
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/21
--  
--  Purpose           : Yes / No Popup window creation    
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateYesNoPopupBox (void)         
{
  begindraw();
    createwindow (YESNO_POPUP_WINDOW, WINDOW_TYPE_POPUP, "Popup Window");//  windowstyle (WD_INFO_BOX, ST_BOX_STYLE);
    windowstyle (YESNO_POPUP_WINDOW, POPUP_OUTBOX_STYLE);
//    page_background (YESNO_POPUP_WINDOW, BackgroundColor);
//    pagestyle (YESNO_POPUP_WINDOW, "background: White;");      
      
      beginlayout (LAYOUT_TYPE_VBOX,0);
      
        beginlayout (LAYOUT_TYPE_VBOX,0);
         //Info Text
          createwidget (YESNO_POPUP, WIDGET_TYPE_TEXT_OUTPUT);
            widget_size_policy    (YESNO_POPUP,  SIZE_POLICY_MINIMUM, SIZE_POLICY_MINIMUM);
            widget_style          (YESNO_POPUP,  POPUP_BOXTEXT_STYLE);
            widget_fontsize       (YESNO_POPUP,  30);                                
            widget_text_alignment (YESNO_POPUP,  WIDGET_TEXT_ALIGN_HCENTER);
        endlayout();
       
        //Button #1 "YES" 
        beginlayout(LAYOUT_TYPE_HBOX, STD_EDGE_DISTANCE_NAVIG, FCT_BUTTON_DISTANCE_NAVIG);
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
          createwidget (YES_BOX,     WIDGET_TYPE_TEXT_OUTPUT);
          widget_image (YES_BOX,BTN_CHECK);
        
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
          
          //Button #2 "NO"        
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
          createwidget (NO_BOX, WIDGET_TYPE_TEXT_OUTPUT);
          widget_image (NO_BOX,BTN_X);
            
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
        endlayout();
      
      endlayout();
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateWPNameListDb
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Create a WP name list db for leaner scan time   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
int CreateWPNameListDb(void)
{
int     err;


  WPNameList.No=0;
  RebuildWPList = ON;
  while ( findnext(WPNameList)==0 )
   { 
    err = delete(WPNameList);
   }
  
  WPdb.No=0; 
  while ( findnext(WPdb)==0 )
  {
    if(WPdb.No > MC.NumberOfWP) 
     break;
    WPNameList.No = WPdb.No;
    WPNameList.Name = WPdb.Name;
    wpNameList[WPdb.No] = WPNameList.Name;
    WPNameList.NominalWeight = WPdb.NominalWeight;
    WPNameList.Unit = WPdb.Unit;
    
    err = insert(WPNameList); 
  }
    WPdb.No = MemRecipe;
    find_db (WP_Db);
    return (err); 
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : Clear_LangRefreshed
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/21
--  
--  Purpose           : Clears the LangRefresh[14] bool
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void  Clear_LangRefreshed (void)
{
int i;

  for (i=0; i<LAST_SCREEN; i++)
  {
    LangRefreshed[i] = OFF;
  
  }
  RefreshProdRepText = OFF;
  RefreshBatchRepText = OFF;
}



/* *********************************************************************** */
/*                                                                         */
/*   Language selection                                                    */
/*                                                                         */
/* *********************************************************************** */
void LanguageSelection (void)
{

  if (Language_Cnt>3 || Language_Cnt<=0) 
    Language_Cnt=1;

 begindraw();
  switch (Language_Cnt)
  {
         case 1: 
             writeparameter ("General","Language","0"); //Always English
             LangValue = readparameter("General","Language");
             Language_Cnt = ++Language_Cnt;
           break;
   
         case 2: 
            if(MC.Language2 >0 && MC.Language2 <= MAX_LANG)
             {
              writeparameter ("General","Language",concat(trim(string(MC.Language2-1))));  
              LangValue = readparameter("General","Language");
             } 
            Language_Cnt = ++Language_Cnt;
           break;    
           
         case 3: 
            if(MC.Language3 >0 && MC.Language3 <= MAX_LANG)
             {
              writeparameter ("General","Language",concat(trim(string(MC.Language3-1))));  
              LangValue = readparameter("General","Language");
             } 
            Language_Cnt = ++Language_Cnt;
           break;
                              
  } 
 enddraw();  
 
 MemLanguage = LangValue;
 MemLanguage_Cnt = Language_Cnt;
 Clear_LangRefreshed();
 CurMode_Set();
 FaultLight_Set();
 TopBarInfo();
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : PreSave_Data
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/04
--  
--  Purpose           : Save current CountAll,  ProdUnderWeightCnt,
--                      ProdOverWeightCnt and ProdAcceptUnitCnt
--                      values to the current WP before changing WP.
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : WP_No: Actual WP.No
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void PreSave_Data (int WP_No,bool reset)
{
  
  if(Batch.CountAll) WP.CountAll = ON;
  else                    WP.CountAll = OFF;
  
  WP.ProdUnderWeightCnt_1  = ProdUnderWeightCnt[Scale1];
  WP.ProdUnderWeightCnt_2  = ProdUnderWeightCnt[Scale2];
  WP.ProdOverWeightCnt_1   = ProdOverWeightCnt[Scale1];
  WP.ProdOverWeightCnt_2   = ProdOverWeightCnt[Scale2];
  WP.ProdTotalUnitsCnt_1   = ProdTotalUnitsCnt[Scale1];
  WP.ProdTotalUnitsCnt_2   = ProdTotalUnitsCnt[Scale2];
  //WP.ProdTotalWeight_1     = ProdTotalWeight[Scale1];
  //WP.ProdTotalWeight_2     = ProdTotalWeight[Scale2];
  WP.ProdTotalWeight_1     = ProdTotalWeight;
  WP.ProdTotalWeight_2     = ProdTotalWeight;
  SaveWP2Db();
  if(reset)
   {
    ResetData(OFF);
   } 
     
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : PostLoad_Data
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/04
--  
--  Purpose           : Load current CountAll,  ProdUnderWeightCnt,
--                      ProdOverWeightCnt and ProdAcceptUnitCnt
--                      values to the current report page after changing WP.
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void PostLoad_Data (void)
{  
  ProdUnderWeightCnt[Scale1]  = WP.ProdUnderWeightCnt_1;
  ProdUnderWeightCnt[Scale2]  = WP.ProdUnderWeightCnt_2;  
  ProdOverWeightCnt[Scale1]   = WP.ProdOverWeightCnt_1;
  ProdOverWeightCnt[Scale2]   = WP.ProdOverWeightCnt_2;  
  ProdTotalUnitsCnt[Scale1]   = WP.ProdTotalUnitsCnt_1;
  ProdTotalUnitsCnt[Scale2]   = WP.ProdTotalUnitsCnt_2;
  //ProdTotalWeight[Scale1]     = WP.ProdTotalWeight_1;
  //ProdTotalWeight[Scale2]     = WP.ProdTotalWeight_2;
  ProdTotalWeight     = WP.ProdTotalWeight_1;
  ProdTotalWeight     = WP.ProdTotalWeight_2;
  
  if(WP.CountAll)
   {
    Batch.CountAll = ON;
    ProdAcceptUnitCnt[Scale1] =  ProdTotalUnitsCnt[Scale1];
    ProdAcceptUnitCnt[Scale2] =  ProdTotalUnitsCnt[Scale2];
   } 
  else
   {
    Batch.CountAll = OFF;
    ProdAcceptUnitCnt[Scale1] =  ProdTotalUnitsCnt[Scale1] - (ProdUnderWeightCnt[Scale1] + ProdOverWeightCnt[Scale1]);
    ProdAcceptUnitCnt[Scale2] =  ProdTotalUnitsCnt[Scale2] - (ProdUnderWeightCnt[Scale2] + ProdOverWeightCnt[Scale2]);
   } 
  
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : ChangeWPinDB
--  Created by        : Steve Santerre
--  Last modified on  : 2017/02
--  
--  Purpose           : Load new WP while presaving and post-saving infos
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : None
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void ChangeWPinDB(int Old,int New)
 {
    PreSave_Data(Old,ON);
    WPdb.No = New;
    find_db (WP_Db); //command to load the active # desired from the recipe dbase                              
    LoadDb2WP();
    MemRecipe = WPdb.No;
    PostLoad_Data();
    LoadBatch(MemRecipe);
    Batch.Count = 0;
 }
 




/*------------------------------------------------------------------------- 
--  Procedure Name    : SaveLanguageDb
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Save Language db  
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int SaveLanguageDb (int Index)
{
int err;

      Language.No              = Index+1;                         
      Language.Name            = TransLang[Index]; //SADM2 
      Language.Translated      = LangTranslated[Index];   
            
err = insert(Language);   
return (err);   
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateLanguageDb
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Fill Language db with Pragma Language string  
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateLanguageDb (void)
{
int i, Lang_lenght, test;
string PRAGMASplit[MAX_LANG][24], Translated[MAX_LANG][24], TempPragmaSplit[24], TempPragmaLang[24];

split (PRAGMASplit,PragmaLanguages, ';');

  for (i=0; i<MAX_LANG; i++)
  {
    TempPragmaLang = "";
    TempPragmaSplit = PRAGMASplit[i];  
    Lang_lenght = pos(TempPragmaSplit,',');
    //copy(TempPragmaSplit,Lang_lenght,TempPragmaLang); //replaced by left() below - bug in V4.I6_R8921_20180509
    TempPragmaLang = left(TempPragmaSplit,Lang_lenght);
    PRAGMALanguage[i] = TempPragmaLang;
    
    Translated[i] = translate (TX_LANG_TRANSLATED, PRAGMALanguage[i]);
    LangTranslated[i] = (Translated[i] == "Yes");
    //SADM2
    TransLang[i] = translate (TX_LanguageName, PRAGMALanguage[i]);
    
    SaveLanguageDb(i);   
  }  
}

/* *********************************************************************** */
/*                                                                         */
/*       Show SpeedAC iQ Startup Message                                   */
/* *********************************************************************** */
void iQShowStartupMessage(string msg)
{     

  show_startup_message ("",concat("<H1 ALIGN=CENTER><font size=5>",INIT_MSG (msg),"</font size></H1>"));

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Permission
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/12
--  
--  Purpose           : Controller permission to change data 
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool Check_Permission(void)
{
  if (Controller == local || CurrentLevel == Level_PT)
  return(true);
  else
  return(false);
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Check_Scale_Cfg
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Check if scales configured in correct order
--                      
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
bool Check_Scale_Cfg (void)
{
bool CheckOK;

CheckOK = ON;

 #ifndef __SIMULATION__
 
  if (WP.FeedAlgoType != FeediQSim)
  { 
   if (ScaleDriver_No[0] != iQ_Feeding) {SystemErrorCode = "411 Scale #1 only iQFeeding driver permitted"; CheckOK = OFF;}
  }

  else
  {
    if (ScaleDriver_No[0] != iQ_Sim) {SystemErrorCode = "421 Scale #1 iQSim driver not installed"; CheckOK = OFF;}
  }
  
  if (ScaleDriver_No[1] != Lbs && ScaleDriver_No[1] != No_Scale){SystemErrorCode = "412 Scale #2 only LBS driver permitted"; CheckOK = OFF;}
  
 #else
  if (WP.FeedAlgoType == FeediQSim) {SystemErrorCode = "441 iQSim Algorithm not allowed in simulator"; CheckOK = OFF;}
   
 #endif
 
 return(CheckOK);
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Check_Scale
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Check which scale is active
--                      
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void Check_Scale (void)
{
  Scale_No = indicatedscale ();
  Scale_No = Scale_No-1;
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ScaleManagement
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Scale Management for future scale selection
--                      
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void ScaleManagement (void)
{
int i;

  ActiveScales = scales;
  Check_Scale();

 if (ActiveScales == 0)
 {
   for (i=0; i<MaxScales; i++)
   {
     ScaleDriver[i] = "None";
     ScaleModul[i]  = "None";
   }  
 }
 else
 {
   for (i=0; i<ActiveScales; i++)
   {
     ScaleDriver[i] = readparameter (concat("Scale", trim(string(i+1))) , "Driver");
     ScaleModul[i]  = readparameter (concat("Scale", trim(string(i+1))) , "source_scale");
      
      
     if (ScaleDriver[i] != "None") ScaleModul[i]  = trim (string(int(ScaleModul[i])+1));

   }

   for (i=(MaxScales-(MaxScales - ActiveScales)); i<MaxScales; i++)
   {
     ScaleDriver[i] = "None";
     ScaleModul[i]  = "None";
   }  

//#ifndef __SIMULATION__   
  
   for (i=0; i<MaxScales; i++)
   {
  
     if (ScaleDriver[i] == "iQ feeding") 
      {
       ScaleDriver_No[i] = iQ_Feeding;
       KeyLockPTSZI(LAST,LAST,LAST,OFF,LAST);
      } 
     else if (ScaleDriver[i] == "lbs")   ScaleDriver_No[i] = Lbs;
     
     else if (ScaleDriver[i] == "iQ Sim") 
      {
       ScaleDriver_No[i] = iQ_Sim;
       KeyLockPTSZI(LAST,LAST,LAST,ON,LAST);
      } 
     
     else if (ScaleDriver[i] == "ADM")   ScaleDriver_No[i] = A_D_M;
     
     else if (ScaleDriver[i] == "None")  ScaleDriver_No[i] = No_Scale;
     
     else
      { 
      if(i==0) SystemErrorCode = "431 Scale #1: wrong scale driver";
      if(i==1) SystemErrorCode = "432 Scale #2: wrong scale driver";
      }

   }  
 }  
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Scale_Switch
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/10
--  
--  Purpose           : Scale switching Logic
--                      
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void Scale_Switch (void)
{
int ScaleTemp, Start, i;

  ScaleTemp = Scale_No;
  Start = Scale_No;  
    
  if (Scale_No < ActiveScales-1)
  {  
    for (i=Start+1; i<ActiveScales; i++)
    {
      if (ScaleDriver_No[Scale_No] == ScaleDriver_No[i])
      {
        ScaleTemp = i; 
        break;
      }    
      else Start = -1;  
    }
  }
  else Start = -1;  

  if (Start == -1)
  {                        
    for (i=Start+1; i<ActiveScales; i++)
    {
      if (ScaleDriver_No[Scale_No] == ScaleDriver_No[i])
      {
        ScaleTemp = i; 
        break;
      }    
      else ScaleTemp = Scale_No;  
    } 
  }
  
 indicatescale (ScaleTemp+1);                                 
 Check_Scale(); 
}


//Initialize and Load DBs
void InitDBs(void)
{
  LoadIONames();
  IOFillDb_Init();
  LoadIOTableDB();
  LoadAccessTableDB();
  Init_Fault_Txt();
  WPFillDb_Init();
  MCFillDb_Init();
  MPFillDb_Init();
  FlexFillDb_Init();
  // Load Databases
  MPdb.No = 1;
  LoadDb2MP ();
  MCdb.No = 1;
  LoadDb2MC (); 
  
  if(RecipeMem < 1 || RecipeMem > MC.NumberOfWP)
  {
   RecipeMem = 1;
   MemRecipe = RecipeMem;
  }
   
  WPdb.No = MemRecipe;
  LoadDb2WP();
  PostLoad_Data();
  LoadBatch(RecipeMem);
  MoveFlexIoDbs2Vars();
  
  CreateWPNameListDb();
  
  MC.iQVersion = concat(translate (TX_SCALE_TYPE,"English"),space(1),TX_PT_CONTROL_SW_VERS);
  SaveMC2Db();


}  

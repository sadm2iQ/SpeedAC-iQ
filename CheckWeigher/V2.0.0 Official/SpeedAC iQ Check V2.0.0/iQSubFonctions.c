﻿/*-----------------------------------------------------------------------------
-- File Name: iQSubFunctions.c 
--
-- Copyright 2015 PremierTech as an unpublished work. 
-- All Rights Reserved.
--
-- The information contained herein is confidential property of 
-- Premier Tech.  The use, copying, transfer or disclosure of such
-- information is prohibited except by express written agreement with
-- Premier Tech.
--
-- First written on October, 2015 by Steve Santerre.
--
-- Module Description:
-- This file is dedicated to all iQ Feed Algorithm  Sub-functions
------------------------------------------------------------------------------*/

//#define SYSTEC_DATA_DEBUG

  

#define DEFAULT_SLOW_FILTER_SIZE    11
#define DEFAULT_FAST_FILTER_SIZE    7

// status
#define FILLING_STATUS_FINISHED                       "finished"
#define FILLING_STATUS_ABORTED                        "aborted"
#define FILLING_STATUS_SETTLED                        "settled"
#define FILLING_STATUS_EMERGENCY                      "emergency"

#define THRESHOLD_PERCENT         10

bool iQFeedStatusFinished,iQFeedStatusAborted,iQFeedStatusSettled,iQFeedStatusEmergency;
bool iQFeedWaitSettled = ON;

DynGenPar  GenCheckParam;
DynEvaPar  EvalParam;


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


/*------------------------------------------------------------------------- 
--  Procedure Name    : Lim
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/17
--  
--  Purpose           : Returns the entered value within set limits 
--                      
--  Value Parameters  :
--  Variable Params   : entry = keyboard entry, min = Minimum value, max = Maximum value 
--  Side Effects      : 
--------------------------------------------------------------------------*/
float Lim(float min, float max, float Entry )
{
float result;
      
             result = Entry;
             if (result < min) result = min;
             if (result > max) result = max;
             
             return (result) ;                
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : LimRound
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/17
--  
--  Purpose           : Returns the entered value within set limits 
--                      
--  Value Parameters  :
--  Variable Params   : entry = keyboard entry, min = Minimum value, max = Maximum value 
--  Side Effects      : 
--------------------------------------------------------------------------*/
float LimRound(float min, float max, float Entry ,float factor)
{
float result;
decimal factorDec%4.dp,resultDec%6.dp;
             
             result = Entry;
             if (result < min) result = min;
             if (result > max) result = max;
             
             factorDec = factor;
             resultDec = result;
             resultDec = int(resultDec/factorDec) * factorDec;
                          
             return (resultDec) ;                
}


//PbZero values verification from Service mode data
void ReadUnitScale1(string *UnitScale1)
{
 string caracter[1],buffer[40],buffer2[40],UnitString[4];
 int FileNbr=5;
 bool GoodScale = OFF;
 
 UnitString = "Unit";
  
 if(fopen(FileNbr,SMFile)==0)
  if(fseek(FileNbr,0,0) ==0)
  {
   buffer = "";
   while(fread(FileNbr,caracter,1)!=0)
    {
     buffer = concat(buffer,caracter);
     if(caracter == LF)
     {
      buffer2 = left(buffer,length(buffer)-2);
      if(left(buffer2, 4) == UnitString) 
       {
        UnitScale1 = trim(sub(buffer2,4,length(buffer2)-4));
        break;
       } 
     buffer = "";
     }
    }  
  }
  
 fclose(FileNbr);     
}

//Read Service mode values & Store to a file
void ReadServiceMode(void)
{
 int servicedatasaved = saveservicedata (SMFile);
 ReadUnitScale1(BasicUnit);
}


//Field Bus type verification from Service mode data
string CheckFieldBus(void)
{
 string FieldBusType[25],caracter[1],buffer[40],buffer2[40];
 int FileNbr=5;
 
 FieldBusType = "Off";
 if(fopen(FileNbr,SMFile)==0)
  if(fseek(FileNbr,0,0) ==0)
  {
   buffer = "";
   while(fread(FileNbr,caracter,1)!=0)
    {
     buffer = concat(buffer,caracter);
     if(caracter == LF)
     {
      buffer2 = left(buffer,length(buffer)-2); 
      if(left(buffer2, 8) == "Fieldbus")
       {
        FieldBusType = trim(sub(buffer2,9,length(buffer2)-9));
        break;
       }
     buffer = "";
     }
    }  
  }
 fclose(FileNbr);     
 return(FieldBusType);
}

//Read FieldBus config & card
void FieldBusDetect(void)
{
  // Field bus detection test
  hardwaretest = GetHardwareInfo(FB_SPU,FB_PIO,FB_NWU,FB_Profibus,FB_Profinet,FB_EthernetIP);
  FieldBusType = CheckFieldBus();
  if(FB_EthernetIP && FieldBusType == "") FieldBusType = FB_ETX;
  FB_Detected = (FieldBusType != FB_OFF);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : DriverSwitch
--  Created by        : Steve Santerre
--  Last modified on  : 2020/02
--  
--  Purpose           : Change Driver iQ Feeding/iQ Sim and Reboot iQ
--                      When in Simulation to allow real weight 
--                      and Simulated weight toggle
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void DriverSwitch(void)
{
 int      class, type, value;
 string   args[4][255];
 char     ch;
 bool     yes;
 
 messagebox("Are you sure you want to change Driver?","YES;NO");
 ch = button;
 if(ch==17) //F1-YES
 { 
  yes = ON;
  #ifndef __SIMULATION__
   #ifdef SIMUL_IN_REAL_IQ
    if(ScaleDriver[SCALECFG1] != "iQ feeding")
    {
     writeparameter("Scale1","Driver","iQ feeding");
     infobox("Driver changed to iQFeeding .... delay before restart");
     delay(5);
     RebootTerminal();
    }
   
    else if(ScaleDriver[SCALECFG1] != "iQ Sim")
    {
     writeparameter("Scale1","Driver","iQ Sim");
     infobox("Driver changed to iQSim .... delay before restart");
     delay(5);
     RebootTerminal();
    }
   #endif
  #endif
 }
 
 else
 {
  yes = OFF;
 }  
}   


/*------------------------------------------------------------------------- 
--  Procedure Name    : MainTaskStopped
--  Created by        : Steve Santerre
--  Last modified on  : 2017/08/09
--  
--  Purpose           : Confirm Restart of Program After Exiting Service mode
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
bool MainTaskStopped(void)
{
 int     class, type, value;
 bool    val;
 string  args[4][255];
  
  begindraw();
    selectwindow (CONFIRM_POPUP_WINDOW);
    widget_text  (CONFIRM_POPUP, "Main task stopped\nconfirm reboot?");     
    showwindow   (CONFIRM_POPUP_WINDOW );
  enddraw();      

  for(;;)
  {
   if(eventreceived())
   { 
    readevent (class, type, value, args);
    switch (value)
    {
      case YES_BOX : 
                     val = ON;
                     hidewindow (CONFIRM_POPUP_WINDOW);
                     return(val);
    }
   }
   else delay (0.2);
  }    
}
/*------------------------------------------------------------------------- 
--  Procedure Name    : Output_ON
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/02
--  
--  Purpose           : Sets specific Digital Output ON
--                      
--  Value Parameters  :
--  Variable Params   : io_name = IO name (enum) to set
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void Output_ON (int io_name)
{
   
    if(!IO_Input[io_name]) //Outputs
    { 
        
       if (!IO_Enable[io_name]) 
         IO_State[io_name] = OFF;
       else
       {  
         if (IO_Address[io_name]<=31)
         {
           setbit(IO_Address[io_name],OutputReg1);
         }
         else
         {
            setbit(IO_Address[io_name],OutputReg2);
         }
       }
      IO_State[io_name] = ON;       
    }  
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Output_OFF
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/02
--  
--  Purpose           : Sets specific Digital Output OFF
--                      
--  Value Parameters  :
--  Variable Params   : io_name = IO name (enum) to set
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void Output_OFF(int io_name)
{

    if(!IO_Input[io_name]) //Outputs
    { 
        
        if (!IO_Enable[io_name]) IO_State[io_name] = OFF;
        else
        { 
         if (IO_Address[io_name]<=31)
         {
           clrbit(IO_Address[io_name],OutputReg1);
         }
         else
         {
           clrbit(IO_Address[io_name],OutputReg2);
         }
        }
      IO_State[io_name] = OFF;  
    }  
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Input_State
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/02
--  
--  Purpose           : Interrogate specific Digital Input
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool Input_State(int io_name)
{

  if(IO_Input[io_name]) //Inputs
  { 
    if (!IO_Enable[io_name]) 
      IO_State[io_name] = OFF;
    else if(IO_Address[io_name] <=31) 
      IO_State[io_name] = bit(IO_Address[io_name],InputReg1);
    else 
      IO_State[io_name] = bit(IO_Address[io_name],InputReg2);
  }
return (IO_State[io_name]);
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : TON_On
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Start Timer Function
--                      
--                                
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Limit TMAX to avoid scanning too many timers
--------------------------------------------------------------------------------*/  
void T_EnOn(int timername)
{
  if (!TD_SetFlag)
  {
    if (!T_EN[timername])
    {
      if (timeout(T[timername])||T_TT[timername]) 
       {
         T_DN[timername]=OFF;
         T_TT[timername]=OFF;
         T_ACC[timername]=0;
         stoptimer(T[timername]);
       }
    
      if(!T_TT[timername] && !T_DN[timername] && T_ACC[timername]!= T_PRE[timername])
       {
         T_TT[timername]=ON;
         T_EN[timername]=ON;
         starttimer(T[timername],T_PRE[timername]);
       }
    }   
  }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : TON_Off
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Stop Timer Function
--                      
--                                
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Limit TMAX to avoid scanning too many timers
--------------------------------------------------------------------------------*/  
void T_EnOff(int timername)
{
if (!TD_SetFlag)
  {
    if (T_EN[timername])
    {
      T_ACC[timername] = 0;
      T_DN[timername]=OFF;
      T_TT[timername]=OFF;
      T_EN[timername]=OFF;
      stoptimer(T[timername]);
    }  
  }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : TON_Dn
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Verify if Timer is Done Function
--                      
--                                
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Limit TMAX to avoid scanning too many timers
--------------------------------------------------------------------------------*/
bool T_Dn(int timername)
{

if (!TD_SetFlag) 
 {
    if(T_TT[timername]) 
     if(timeout(T[timername])) {T_ACC[timername] = T_PRE[timername];T_DN[timername]=ON;T_TT[timername]=OFF;stoptimer(T[timername]);}
   
 }
    return (T_DN[timername]);

}  


/*------------------------------------------------------------------------------- 
--  Procedure Name    : TON_Acc
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/25
--  
--  Purpose           : Retreive Accumulated Value
--                      
--                                
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : Limit TMAX to avoid scanning too many timers
--------------------------------------------------------------------------------*/  
decimal T_Acc(int timername)
{
  if (!TD_SetFlag)
  {
    if(T_TT[timername] && !T_DN[timername])
    if(T_TT[timername] && !T_DN[timername]) 
     {
      Remain = remain(T[timername]);
      T_ACC[timername]=T_PRE[timername]-Remain;
     } 
    if (T_DN[timername]) T_ACC[timername]=T_PRE[timername];
    if (!T_EN[timername]) T_ACC[timername]= 0;
  }
    return (T_ACC[timername]);
}



void KeyLockPTSZI(int valP, int valT, int valS, int valZ, int valI)
{
 //PTSZ
 switch(valP)
  {
   case ON:
         KeyLockP = "P";
         break;
   case OFF:
         KeyLockP = "";
         break;
   case LAST:
         break;
   default: break;      
  }
  
  switch(valT)
  {
   case ON:
         KeyLockT = "T";
         break;
   case OFF:
         KeyLockT = "";
         break;
   case LAST:
         break;
   default: break;      
  }       
  
  switch(valS)
  {
   case ON:
         KeyLockS = "S";
         break;
   case OFF:
         KeyLockS = "";
         break;
   case LAST:
         break;
   default: break;      
  }
  
  switch(valZ)
  {
   case ON:
         KeyLockZ = "Z";
         break;
   case OFF:
         KeyLockZ = "";
         break;
   case LAST:
         break;
   default: break;      
  }
  
  switch(valI)
  {
   case ON:
         KeyLockI = "I";
         break;
   case OFF:
         KeyLockI = "";
         break;
   case LAST:
         break;
   default: break;      
  }
  KeyLockString = concat(KeyLockP,KeyLockT,KeyLockS,KeyLockZ,KeyLockI);
  keylock(KeyLockString); 
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
void FaultHandler(int Fault_No, string Fault_Txt)
{
int PRIORITY , BIT;
bool test;
 PRIORITY = Fault_No / 32; //Division
 BIT      = Fault_No % 32; //Modulo

 Fault_NoOutput = Fault_No;
 Fault_TxtOutput = Fault_Txt;
 FaultHandlerFlag = Execute;
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : EmptyBuffer
--  Created by        : Steve Santerre
--  Last modified on  : 2015/08/28
--  
--  Purpose           : Emptying buffer to Scale ADM
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void EmptyBuffer(void)
{
int   msgcnt=0;

//Init Event Reception

  while (msgread (0) >= 0)
    msgcnt++;
    
  if (msgcnt > 0)
    msgcnt = msgcnt;
}    


void InitCheckSimul(void)
{
  
  GenCheckParam.ApprovalFlag = OFF;             // approved_weighing,
  GenCheckParam.CatchWeigherFlag = OFF;         // catchweigher,
  GenCheckParam.CheckDynFlag = ON;             // dynamic_mode,
  GenCheckParam.SampleRate = 429;
  GenCheckParam.MinZeroSettingTime = 0.3; //seconds
  GenCheckParam.AutomaticZeroMode = CHECK_ZERO_MODE_AUTOMATIC;
  GenCheckParam.AutomaticZeroPeriod = 15; //Minutes
  GenCheckParam.MinimumOffBeltDistance = 0; //mm
  GenCheckParam.MaximumMeasuringTime = 3000; //ms
  GenCheckParam.MeasurementStartMode = CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_CLOSED;
  GenCheckParam.MeasurementStopMode = CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_CLOSED;
  GenCheckParam.LightBarrierDebounceTime = 20; //ms
  GenCheckParam.WarmUpTime = 0; //min             
  GenCheckParam.MinimumLoad = 20; //d - interval             
  GenCheckParam.TranspControlMode = TRANSPORT_CONTROL_MODE_OFF;           
  GenCheckParam.SpeedControlMode = SPEED_CONTROL_MODE_OFF;   
  GenCheckParam.SpeedControlPlusTol = 0.0;   //%      
  GenCheckParam.SpeedControlMinusTol = 0.0;  //%       
  GenCheckParam.SpeedControlDistance = 1346; //mm
  GenCheckParam.ClassificationEnable = OFF;
  GenCheckParam.EvaluationControlMode = EVALUATION_CONTROL_MODE_OFF;
  
  WeighingResult.WeightValid    = ON;
  WeighingResult.WeightError    = CHECK_ERROR_NO_ERROR;
  WeighingResult.Price          = 0.00;
  WeighingResult.Zone           = zOK;
  WeighingResult.WeightAvg      = WP.NominalWeight;     
  WeighingResult.WeightStdDev   = 0.00;  
  WeighingResult.DevAvg         = 0.00;
  WeighingResult.DevStddev      = 0.00;
  WeighingResult.Speed          = 1.00; //m/s
  WeighingResult.StatisticValues= 0;  
  WeighingResult.PieceMissed    = 0;
                  
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ResetZones
--  Created by        : Steve Santerre
--  Last modified on  : 2019/11
--  
--  Purpose           : Reset All Zones Outputs
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void ResetZones(void)
{
  Output_OFF(O_TolOverReject);
  Output_OFF(O_TolOverAccept);
  Output_OFF(O_TolGood);
  Output_OFF(O_TolUnderAccept);
  Output_OFF(O_TolUnderReject);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : InvalidWeightZones
--  Created by        : Steve Santerre
--  Last modified on  : 2019/11
--  
--  Purpose           : Turn ON all Out of Tol Outputs for incorrect weighment
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void InvalidWeightZones(void)
{
  Output_ON(O_TolOverReject);
  Output_ON(O_TolOverAccept);
  Output_OFF(O_TolGood);
  Output_ON(O_TolUnderAccept);
  Output_ON(O_TolUnderReject);
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : CheckSystem
--  Created by        : Steve Santerre
--  Last modified on  : 2020/04
--  
--  Purpose           : Check System for lenght & speed values 
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CheckSystem(bool tgl)
{
 
 if(!MC.System) //Metric
  {
   SpeedUnit = 1.0;
   SpeedText = "m/s";
   LengthUnit = 1.0;
   LengthText = "mm";
   MP.PhotocellsDistance = GenCheckParam.SpeedControlDistance;
   if(tgl)
    {
      MP.BeltSpeed  = MP.BeltSpeed * 0.00508;
      WP.BagLength  = WP.BagLength * 25.4;
      SaveMPFlag = Execute;
      SaveWPFlag = Execute;
    } 
  }
 else         //Imperial
  {
   SpeedUnit = 0.00508;  // '/m -> m/s
   SpeedText = " '/m";
   LengthUnit = 25.4;    // " -> mm
   LengthText = " \"";
   MP.PhotocellsDistance = GenCheckParam.SpeedControlDistance / 25.4;
   if(tgl)
    {
      MP.BeltSpeed  = MP.BeltSpeed / 0.00508;
      WP.BagLength  = WP.BagLength / 25.4;
      SaveMPFlag = Execute;
      SaveWPFlag = Execute;
    } 
  }
  
  
  
  BeltSpeedMetric  = MP.BeltSpeed * SpeedUnit;
  PCDistanceMetric = MP.PhotocellsDistance * LengthUnit;
  BagLengthMetric  = WP.BagLength * LengthUnit;
} 
        

/*------------------------------------------------------------------------- 
--  Procedure Name    : EnableDynamicMode
--  Created by        : Steve Santerre
--  Last modified on  : 2019/06
--  
--  Purpose           : Verify And Select needed Evaluation Parameters
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void EnableDynamicMode(bool Enable,int handle)
{
 
 if(!Simul && CheckAll)
 {
  if(Enable)
  { 
    if(!check_dynamic_mode (handle,CD_SCALE_NO))
    {
     SystemErrorCode = "705 Driver Not in Dynamic";
    }
  }
 
  else   
  { 
   ZeroOK = OFF;
   DynamicInitDone = OFF;
   
    if(!check_static_mode (handle,CD_SCALE_NO))
    {
     SystemErrorCode = "706 Driver Not in Static";
    }
  }
  
 }
 
}  

/*------------------------------------------------------------------------- 
--  Procedure Name    : SelectEvalParam
--  Created by        : Steve Santerre
--  Last modified on  : 2019/06
--  
--  Purpose           : Verify And Select needed Evaluation Parameters
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SelectEvalParam(int evalparamnbr)
{
 bool retvalue[2];
 int ActualEvalParam;
 
 retvalue[0] = check_selected_parameters(CD_HANDLE_BG,CD_SCALE_NO,ActualEvalParam);
 
 
 if(ActualEvalParam != evalparamnbr-1)
 {
  retvalue[1] = check_select_parameters(CD_HANDLE_BG,CD_SCALE_NO, evalparamnbr-1, WP.Name);

  return(retvalue[0] && retvalue[1]);
 } 
 
 else
  return(retvalue[0]);
}  

/*------------------------------------------------------------------------- 
--  Procedure Name    : EPWriteBeltSpeed
--  Created by        : Steve Santerre
--  Last modified on  : 2020/04
--  
--  Purpose           : This function is called to Write Belt Speed to
--                      Evaluation Parameter set (1-30 as per WP#)
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void EPWriteBeltSpeed(int handle,int recipe_nbr)
{
 int set_mask;
 bool valid;
  
  EvalParam.BeltSpeed = BeltSpeedMetric;
  set_mask = 0;
 
  setbit (ID_CHECK_PARNAME_BELT_SPEED, set_mask);
 
  valid = check_set_parameter_details (handle, CD_SCALE_NO, recipe_nbr-1, EvalParam, set_mask);
} 

/*------------------------------------------------------------------------- 
--  Procedure Name    : EPWriteOffset
--  Created by        : Steve Santerre
--  Last modified on  : 2020/04
--  
--  Purpose           : This function is called to Write Offset to
--                      Evaluation Parameter set (1-30 as per WP#)
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void EPWriteOffset(int handle,int recipe_nbr)
{
 int set_mask;
 bool valid;
 float EPalpha,EPbeta;
 decimal EPoffset%5.3,WPOffset%5.3;
 string EPCP[10][40];
  
  WPOffset = WP.DynamicOffset * UnitIQtoADM;
  split(EPCP,EvalParam.CorrectingPolynomial,'/');
  EPalpha  = float(EPCP[0]);
  EPbeta   = float(EPCP[1]);
  EPoffset = float(EPCP[2]);
  
  if(EPoffset != WPOffset)
  {
   EPoffset = WPOffset;
   EvalParam.CorrectingPolynomial = concat(trim(adj(EPalpha,8,6)),"/",trim(adj(EPbeta,8,6)),"/",trim(adj(EPoffset,8,6)));
   set_mask = 0;
   setbit (ID_CHECK_PARNAME_CORRECTING_POLYNOMIAL, set_mask);
//   valid = check_set_parameter_details (handle, CD_SCALE_NO, recipe_nbr-1, EvalParam, set_mask);
   valid = check_set_corrpoly (handle, CD_SCALE_NO, recipe_nbr-1, EvalParam.CorrectingPolynomial);
  } 
} 
 
/*------------------------------------------------------------------------- 
--  Procedure Name    : EvalParamWrite
--  Created by        : Steve Santerre
--  Last modified on  : 2020/03
--  
--  Purpose           : This function is called to Write values to
--                     Evaluation Parameter set (1-30 as per WP#)
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void EvalParamWrite(bool ATParam,int handle,int recipe_nbr,bool EPinvalid)
{
 int set_mask,TempoEP;
 bool valid,modedynamic,result[4],ep_bypasswrite;
 
   
   ep_bypasswrite = OFF;
   modedynamic = IsDynamicModeActive();
   CheckSystem(OFF);
   
   /****Called by Auto-Tune****/
 if(ATParam) 
 {
   if(modedynamic)
   {
    EnableDynamicMode(OFF,handle);
   }
   
   if(recipe_nbr == RecipeMem)
   {
    TempoEP = recipe_nbr + 1;
    if(TempoEP == MAX_WP) TempoEP = 1; 
    SelectEvalParam(TempoEP);
   }
    
   EvalParam.PrimaryFilterTime     = AT.CheckAnalysePrimaryTime;
   EvalParam.EvaluationFilterSize  = AT.CheckAnalyseEvalSize;
 }
   
   /****Called when loading a NON-configured Eval Param set****/
 else if(EPinvalid) 
 {
      //WP is valid ... use WP
   if(WP.PrimaryFilter > 0 && WP.EvaluationFilter > 0)
   {
     EvalParam.PrimaryFilterTime    = WP.PrimaryFilter;
     EvalParam.EvaluationFilterSize = WP.EvaluationFilter;
   }  
     //WP not valid ... use Basic Param.
   else
   {
    EvalParam.PrimaryFilterTime    = BPPRIMARYFILTER;
    EvalParam.EvaluationFilterSize = BPEVALFILTER; 
   } 
 }
 
  /****Called when loading a configured Eval Param set****/
 else if(!EPinvalid) 
 {
       //WP not valid ... use EP
   if(WP.PrimaryFilter  <= 0 || WP.EvaluationFilter <= 0)
   {
     WP.PrimaryFilter    = EvalParam.PrimaryFilterTime;
     WP.EvaluationFilter = EvalParam.EvaluationFilterSize;
     SaveWPFlag = Execute;
     ep_bypasswrite = ON;
   }
      
      //WP is valid
   else
   {    
       //EP != WP
    if(EvalParam.PrimaryFilterTime != WP.PrimaryFilter || EvalParam.EvaluationFilterSize != WP.EvaluationFilter) 
    {   
       //EP == Basic Parameters ... use WP
     if(EvalParam.PrimaryFilterTime == BPPRIMARYFILTER && EvalParam.EvaluationFilterSize == BPEVALFILTER)
      {
       EvalParam.PrimaryFilterTime      = WP.PrimaryFilter;
       EvalParam.EvaluationFilterSize   = WP.EvaluationFilter;
      }
        
        //EP != Basic Parameters ... use EP
     else
      {
       WP.PrimaryFilter    = EvalParam.PrimaryFilterTime;
       WP.EvaluationFilter = EvalParam.EvaluationFilterSize;
       SaveWPFlag = Execute;
       ep_bypasswrite = ON;
      }
    }
       //EP == WP ... use EP & let WP as is - Bypass Write
    else
    {
     ep_bypasswrite = ON;
    } 
    
   } 
        
 }
 
 if(!ATWithZero)
  EvalParam.ZeroSettingFilterTime = BPZEROFILTER;
 EvalParam.BeltSpeed = BeltSpeedMetric;
 set_mask = 0;
   
 if(!ep_bypasswrite)
 {
  setbit (ID_CHECK_PARNAME_PRIMARY_FILTER_TIME, set_mask);
  setbit (ID_CHECK_PARNAME_EVALUATION_FILTER_SIZE, set_mask);
  setbit (ID_CHECK_PARNAME_ZERO_SETTING_FILTER_TIME, set_mask);
  setbit (ID_CHECK_PARNAME_BELT_SPEED, set_mask);
 
  valid = check_set_parameter_details (handle, CD_SCALE_NO, recipe_nbr-1, EvalParam, set_mask);
  
  WP.PrimaryFilter    = EvalParam.PrimaryFilterTime;
  WP.EvaluationFilter = EvalParam.EvaluationFilterSize;
  WP.ZeroFilter       = EvalParam.ZeroSettingFilterTime;
  SaveWPFlag = Execute;
 }
 
 if(ATParam)
 {
   if(modedynamic)
   {
    EnableDynamicMode(ON,handle);
   }
   
   if(recipe_nbr == RecipeMem)
   {
    SelectEvalParam(recipe_nbr);
   }
 }
 
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : EvalParamSet
--  Created by        : Steve Santerre
--  Last modified on  : 2020/03
--  
--  Purpose           : This function is called to Set the desired
--                     Evaluation Parameter set (1-30 as per WP#)
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void EvalParamSet(int recipe_nbr)
{
 bool Status_check_param_details;
 bool EvalParamValid;
    
    EvalParamValid=OFF;
    
    Status_check_param_details = check_parameter_details (CD_HANDLE,CD_SCALE_NO,int(Lim(0,MAX_WP-1,recipe_nbr-1)),EvalParam,EvalParamValid);
    if(!EvalParamValid)
     {
      EvalParamWrite(OFF,CD_HANDLE,recipe_nbr,ON);
      Status_check_param_details = check_parameter_details (CD_HANDLE,CD_SCALE_NO,int(Lim(0,MAX_WP-1,recipe_nbr-1)),EvalParam,EvalParamValid);
      if(!EvalParamValid)
       SystemErrorCode = "701 Evaluation Parameters not Valid";
     }
    if(EvalParamValid)
     EvalParamWrite(OFF,CD_HANDLE,recipe_nbr,OFF); 
}   
  
/*------------------------------------------------------------------------- 
--  Procedure Name    : InitCheck
--  Created by        : Steve Santerre
--  Last modified on  : 2019/06
--  
--  Purpose           : Verify And Initialize Check Driver
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void InitCheck(void)
{
 bool Status_Check_Driver,Status_set_ack_weights,Status_check_cfg_param,Status_check_set_pusher;
 
  if(Simul) 
  { 
   InitCheckSimul();
  }
  
  else //if(CheckAll)
  {
   Status_Check_Driver = start_check_driver (CD_HANDLE,CD_HANDLE_BG,CD_SCALE_NO,io_offset,fOnly_Pim_Configured,"Driver Not OK","No PIM Installed"); //Offset,fOnlyPimConfigured,lsub (TX_ShowDriverNotInstalled),lsub (TX_NO_PIM_INSTALLED));
   Status_set_ack_weights =check_set_acknowledge_weights (CD_HANDLE, CD_SCALE_NO, ON);
   Status_check_cfg_param = check_config_parameters (CD_HANDLE, CD_SCALE_NO,GenCheckParam);
   
   Status_check_set_pusher = check_set_pusher (CD_HANDLE,CD_SCALE_NO,PUSHER_TRIGGER_CONTROL_OFF,"","",""); 
   
   if(GenCheckParam.CheckDynFlag)
   {
      EvalParamSet(MemRecipe);
   }
  
   else
   {
    SystemErrorCode = "702 Dynamic mode not selected in SM";
   } 
  
   if (GenCheckParam.CatchWeigherFlag)
    {
     SystemErrorCode = "703 Catch weigher selected in SM";
    }
  } 
  
  SystemMem = -1;  
}    
//Log Check Analyse % of completion
void CheckAnalyseLog(int value)
{
 int i;
  
  for(i=98;i>=0;i--)
  {
   if(value == -1)
    AnalyseLog[i] = 0;
   AnalyseLog[i+1] = AnalyseLog[i];
  }
  AnalyseLog[0] = value;
}  
//Log the Check Driver events
void DriverEventStack(int event)
{
 int i;
  for(i=18;i>=0;i--)
  {
   DriverEvent[i+1] = DriverEvent[i];
  }
  DriverEvent[0] = event;
}  
    

/*------------------------------------------------------------------------- 
--  Procedure Name    : handle_driver_status
--  Created by        : Steve Santerre
--  Last modified on  : 2019/10
--  
--  Purpose           : This function is called to know the status
--                     of the ADM Check driveer
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void handle_driver_status (void)
{
  int   status;
  bool  f,zerostatus;
  float power_up_zero,current_zero;
  
  if (check_status_msg (CD_SCALE_NO, status))
  {
    DriverEventStack(status);
    switch (status)
    {
      case CHECK_STATUS_UNSET:
      case CHECK_STATUS_CALIBRATION_ERROR:  
      case CHECK_STATUS_ADM_THREAD_NOT_RUNNING:
      case CHECK_STATUS_NOT_INITIALIZED:
      case CHECK_STATUS_OK:
           break;
     
           
      case CHECK_STATUS_ZERO_SETTING_RECOMMENDED:
             ZeroRecommended = ON;                                    
             Output_ON(O_ZeroReq);
           break;

      case CHECK_STATUS_ZERO_SETTING_REQUIRED:
              Output_ON(O_ZeroReq);
              ZeroRequired = ON;
           break;
      
      case CHECK_STATUS_ZERO_SETTING_SUCCEEDED:
             Output_OFF(O_ZeroReq);
             ZeroRecommended = OFF;
             ZeroRequired = OFF;
             ZeroOK = ON;
             zerostatus = check_zero_weight (CD_HANDLE_BG,CD_SCALE_NO,power_up_zero,current_zero);
           break;
      
      case CHECK_STATUS_ZERO_SETTING_SKIPPED:
             Output_OFF(O_ZeroReq);
             ZeroRecommended = OFF;
             ZeroRequired = OFF;
             ZeroOK = ON;
           break;
      
      case CHECK_STATUS_INITIALIZATION_DONE:
             DynamicInitDone = ON;
           break;                                       
      
      //case CHECK_STATUS_ZERO_SETTING_ACTIVE:
      //      
      //    break;

      case CHECK_STATUS_TRANSPORT_ERROR:
           if(!FaultState(FltS_TransportError))
           {
            FaultHandler(FltS_TransportError,"");
           }
           break;

      case CHECK_STATUS_SPEED_ERROR:
           if(!FaultState(FltS_SpeedCtrlError))
           {
            FaultHandler(FltS_SpeedCtrlError,"");
           }
           break;


      //case CHECK_STATUS_POWER_UP_ZERO:
      //       
      //     break;

      //case CHECK_STATUS_AUTOMATIC_TARE:
      //      
      //     break;

      //case CHECK_STATUS_SERVICE_MODE:  
      //      
      //     break;


      case CHECK_STATUS_CALCULATION_SCHEDULING_ERROR:
             // critical
            SystemErrorCode = "766 DYN Check:Calculation Schedul. error";
           break;

      case CHECK_STATUS_ADM_READ_ERROR:
             // critical
            SystemErrorCode = "767 DYN Check: ADM read Error"; 
           break;

      
      //case CHECK_STATUS_EVALUATION_ERROR:  // only if GenCheckParam.EvaluationControlMode == EVALUATION_CONTROL_MODE_STOP
      //        
      //     break;
    }
  }
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ReadCheckEvents
--  Created by        : Steve Santerre
--  Last modified on  : 2019/11
--  
--  Purpose           : Read Events from Scale ADM Check driver
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void ReadCheckEvents (void)
{
  bool result;
  int status,typeofmsg;
  int type;
  int iPos;
  int iLen;
  int tProcessState;
  int ZeroRemainMin,ZeroRemainSec;
  string ZeroRemainTime[10];
  float msgtime=0;

 if(!Simul && CheckAll)
 {       
    typeofmsg = msgread (msgtime);
    if(typeofmsg >= 0)
    {    
        if(typeofmsg != SYSTEM_EVENT_SCALE_DRIVER_STATUS)
         DriverEventStack(typeofmsg+100);
        
        switch (typeofmsg)   
         {
          case SYSTEM_EVENT_SCALE_DRIVER_WEIGHT:  // only dynamic mode
               check_weight_msg (CD_SCALE_NO,WeighingResult);
//                                    WeightValid,  // if true then err == 0
//                                    ErrorCode,
//                                    Price,
//                                    Zone,
//                                    WeightAvg,
//                                    WeightStdDev,
//                                    DevAvg,
//                                    DevStddev,
//                                    Speed,
//                                    StatisticValues);
                 CheckDone = ON;
                 if(AutoTune) ATCheckDone = ON;
                 
                 if(!WeighingResult.WeightValid)
                 {
                   WeighingResult.Zone = "";
                   switch (WeighingResult.WeightError)
                   {
                      case CHECK_ERROR_NO_WEIGHT:
                                SystemWarningCode = "750 DYN Check: No Weight Detected";                
                           break;
                      case CHECK_ERROR_NO_DATA:
                                SystemWarningCode = "751 DYN Check: No Data";
                           break;     
                      case CHECK_ERROR_NO_MAXIMUM:
                                SystemWarningCode = "752 DYN Check: No Maximum Detected";
                           break;     
                      case CHECK_ERROR_CALCULATE_VALUE:
                                SystemWarningCode = "753 DYN Check: Calculate value";
                           break;
                      case CHECK_ERROR_TRANSPORT:  
                           // this event will not be send from the driver
                           break;               
                      case CHECK_ERROR_PEAK_TOO_SHORT:
                                SystemWarningCode = "754 DYN Check: Peak too short";
                           break;     
                      case CHECK_ERROR_PEAK_TOO_LONG:
                                SystemWarningCode = "755 DYN Check: Peak too long";
                           break;     
                      case CHECK_ERROR_CALCULATE_DERIVATIVE:
                                SystemWarningCode = "756 DYN Check: Calc. Derivative";
                           break;     
                      case CHECK_ERROR_NO_PEAK_PLATEAU:
                                SystemWarningCode = "757 DYN Check: No peak plateau";
                           break;     
                      case CHECK_ERROR_FILTER_CALCULATION:
                              SystemWarningCode = "758 DYN Check: No filter Calculation";
                           break;     
                      case CHECK_ERROR_SCHEDULING_CALCULATION:
                              SystemWarningCode = "759 DYN Check: Scheduling Calculation";
                           break;     
                      case CHECK_ERROR_WEIGHT_BELOW_MINIMUM_LOAD:
                              SystemWarningCode = "760 DYN Check: Weight Below Minimum";
                           break;     
                      case CHECK_ERROR_SPEED_OUTSIDE_RANGE:
                                //SystemWarningCode = "761 DYN Check: Speed outside range";
                                if(!FaultState(FltS_SpeedCtrlError))
                                {
                                 FaultHandler(FltS_SpeedCtrlError,"");
                                }
                                
                           break;     
                      case CHECK_ERROR_WEIGHT_ABOVE_MAXIMUM_LOAD:
                              SystemWarningCode = "762 DYN Check: Weight Above Maximum";
                           break;     
                      case CHECK_ERROR_ADM_READ:
                              SystemWarningCode = "763 DYN Check: ADM read error";
                           break;     
                      case CHECK_ERROR_OBJECT_IGNORED:  
                              SystemWarningCode = "764 DYN Check: Object ignored";
                           break;     
                      case CHECK_ERROR_PLATEAU_INCORRECTLY_DETECTED:  
                              SystemWarningCode = "765 DYN Check: Plateau detection incorrect";
                           break;     
                   }
                   if(SystemWarningCode != "")
                    WeighingResultInError = ON;
                   
                 }
                 lSpeed = WeighingResult.Speed;
                 TotalNumberOfWeighings = WeighingResult.StatisticValues;
               break;
          case SYSTEM_EVENT_SCALE_DRIVER_STATUS:  // only dynamic mode
               handle_driver_status ();
               break;
          case SYSTEM_EVENT_SCALE_DRIVER_MESSAGE:     // only dynamic mode
               check_scale_msg_type (CD_SCALE_NO,type);
               break;
         }
    }
   
   result = check_remaining_uptime(CD_HANDLE_BG,CD_SCALE_NO,ZeroRemainMin,ZeroRemainSec,ZeroRemainTime);
                             
 }      
 else
 {
  if(SeqMaster == stp_WAITRESULT)
  { 
   CheckDone = ON;
  }
 }  
}

                                        
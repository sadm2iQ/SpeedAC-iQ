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

bool iQFeedStatusFinished[2],iQFeedStatusAborted[2],iQFeedStatusSettled[2],iQFeedStatusEmergency[2];
bool iQFeedWaitSettled[2] = ON;

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CursorModeSet
--  Created by        : Steve Santerre
--  Last modified on  : 2020/06
--  
--  Purpose           : 
--                    ; Set the control via Mouse or Touch Pad  
--                    ;            
--  Value Parameters  :
--  Variable Params   : Do it on power-up or if MC.Mouse is toggled in screen
--  Side Effects      : 
--------------------------------------------------------------------------------*/  
void CursorModeSet(void)
{
 int enabled_inputs;
 
  if(!MC.Mouse)
  { 
   enabled_inputs = 0;
   setbit (CURSOR_INPUT_TOUCHSCREEN ,enabled_inputs);
   setdisplayoption (DISPLAY_OPTION_CURSOR_INPUT, enabled_inputs);
   setdisplayoption (DISPLAY_OPTION_CURSOR_TYPE,"-1");
  }
 
  else  
  { 
   enabled_inputs = 0;
   setbit (CURSOR_INPUT_TOUCHSCREEN ,enabled_inputs);
   setbit (CURSOR_INPUT_MOUSE       ,enabled_inputs);
   setdisplayoption (DISPLAY_OPTION_CURSOR_INPUT, enabled_inputs);
   setdisplayoption (DISPLAY_OPTION_CURSOR_TYPE,CURSOR_TYPE_ARROW); 
  } 
  
} 

/*------------------------------------------------------------------------- 
--  Procedure Name    : Lim
--  Created by        : Jean-Pierre DorÃ©
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

/*
------------------------------------------------------------------------- 
--  Procedure Name    : LimActuator
--  Created by        : Steve Santerre
--  Last modified on  : 2019/07
--  
--  Purpose           : Returns the entered value within set limits 
--                      
--  Value Parameters  :
--  Variable Params   : entry = keyboard entry, min = Minimum value, max = Maximum value 
--  Side Effects      : 
--------------------------------------------------------------------------*/

float LimActuator(float min, float max, float Entry )
{
float result;
      
      if(!MC.ActuatorPosInvert)
       {
        if(MC.ActuatorExtendLimit < max && MC.ActuatorExtendLimit > 0)
         max = MC.ActuatorExtendLimit;
       }
      else
       {
        if(MC.ActuatorExtendLimit > min)
         min = MC.ActuatorExtendLimit;
       }   
             result = Entry;
             if (result < min) 
              result = min;
             if (result > max) 
              result = max;
             
             return (result) ;                
}

//Field Bus type verification from Service mode data
string CheckFieldBus(void)
{
 string File [25]= "shared/ServiceData.txt";
 string FieldBusType[25],caracter[1],buffer[40],buffer2[40];
 int FileNbr=5;
 
 FieldBusType = "Off";
 
 int servicedatasaved = saveservicedata (File);
 if(fopen(FileNbr,File)==0)
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
--  Procedure Name    : OpenConnection
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Open Connection to Channel for iQ Algo
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void OpenConnection(int ScaleNo)
{
  int scale_channel,scale_number;

 if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
 
//To initialize Channel Connection
if (!iQOpenConnection (scale_channel, "127.0.0.1")) 
  SystemErrorCode = concat("#",trim(string(scale_number)),"-","140 iQFeeding connection not established");                  
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : CountChar
--  Created by        : Steve Santerre
--  Last modified on  : 2016/11/14
--                    ;
--  Purpose           : Count the number of Char in String
--                    ; 
--                    ;             
--  Value Parameters  : 
--  Variable Params   : Return number of found "char to find"
--  Side Effects      : 
--------------------------------------------------------------------------------*/
int CountChar(string RefStr,char CharToFind)
{
  string tempstr[1024];
  int count=0;
  
  tempstr = RefStr;

   while (pos(tempstr,CharToFind) != -1)
    {
     tempstr = right(tempstr,(length(tempstr) - pos(tempstr,CharToFind)-1));
     count++;
    }
 return(count);
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



/*------------------------------------------------------------------------- 
--  Procedure Name    : iQOutRelease
--  Created by        : Steve Santerre
--  Last modified on  : 2016/04/01
--  
--  Purpose           : Release Outputs from iQSmartFEED
--                      To Allow For Output Tests
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool iQOutRelease(int ScaleNo)
{
bool result1,result2;
int scale_channel,scale_number;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
 
result1 = iQSetEnableSignalOutput (scale_channel, scale_number, -1,OFF);
result2 = iQSmSetDigitalOutput(scale_channel, scale_number,-1,-1,0);
iQOutputEnabled[ScaleNo-1] = OFF;
return(result1 && result2);
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : iQOutActivate
--  Created by        : Steve Santerre
--  Last modified on  : 2016/04/01
--  
--  Purpose           : Release Outputs from iQSmartFEED
--                      To Allow For Output Tests
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool iQOutActivate(int ScaleNo)
{
int EnableOutput,AddressBulk,AddressDribble,AddressGate;
bool noerr1,noerr2,EnableBulk,EnableDribble,EnableGate,EnableOutOn1St;
int scale_channel,scale_number;
   
    //Enable behavior on 1st Learning: 
    // 0=OFF if Fast/Slow OFF
    // 1=ON all cycle
    // 2=ON until First Slow goes OFF(allow Catch gate to let Product of Fast to Fall in the Pan)
  
    if(!Feeder.EnableOnAllLearning[MC.FeederType])
     EnableOutOn1St = 0;
    else
     EnableOutOn1St = 2;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
  
  if(MC.FeederType == FeederB && !IO_Enable[O_BulkFeed1] && (AOUTModule[AIO1] == PIM3))
  {
   EnableBulk    = ON;
   AddressBulk    = BULK1ADDRESS;
   FeederBWithAout[ScaleNo-1] = ON;
  }
  else
  {
   EnableBulk    = IO_Enable[O_BulkFeed1];
   AddressBulk    = IO_Address[O_BulkFeed1];
   FeederBWithAout[ScaleNo-1] = OFF;
  }
    
  EnableDribble = IO_Enable[O_DribbleFeed1];
  EnableGate    = IO_Enable[O_CatchGate1];
  AddressDribble = IO_Address[O_DribbleFeed1];
  AddressGate    = IO_Address[O_CatchGate1];
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
  
  if(MC.FeederType == FeederB && !IO_Enable[O_BulkFeed2] && AOUTModule[AIO2] == PIM4)
  {
   EnableBulk    = ON;
   AddressBulk    = BULK2ADDRESS;
   FeederBWithAout[ScaleNo-1] = ON;
  }
  else
  {
   EnableBulk    = IO_Enable[O_BulkFeed2];
   AddressBulk    = IO_Address[O_BulkFeed2];
   FeederBWithAout[ScaleNo-1] = OFF;
  }
  
  EnableDribble = IO_Enable[O_DribbleFeed2];
  EnableGate    = IO_Enable[O_CatchGate2];
  AddressDribble = IO_Address[O_DribbleFeed2];
  AddressGate    = IO_Address[O_CatchGate2];
 }
 
noerr1 = ON;
noerr2 = ON;

   if (EnableGate)
    {
    noerr1 = iQSetEnableSignalOutput (scale_channel, scale_number, AddressGate-PIMoffset,EnableOutOn1St);
    iQOutputEnabled[ScaleNo-1] = ON;
    }
    
   
   if(EnableDribble)
   {
    if(EnableBulk)  
    {
    noerr2 = iQSmSetDigitalOutput(scale_channel, scale_number,AddressBulk-PIMoffset,AddressDribble-PIMoffset,MC.DribbleOutOnInBulk);
    iQOutputEnabled[ScaleNo-1] = ON;
    }
    
    else if(EnableGate)  
    {
    noerr2 = iQSmSetDigitalOutput(scale_channel, scale_number,AddressGate-PIMoffset,AddressDribble-PIMoffset,MC.DribbleOutOnInBulk);
    iQOutputEnabled[ScaleNo-1] = ON;
    }
   } 
    
   else 
    {
         
     if(EnableBulk)
      {
       SystemErrorCode = concat("#",trim(string(ScaleNo)),"-","306 Output Dribble Feed not configured");
      }
    }     

return(noerr1 && noerr2);
}                 


/*------------------------------------------------------------------------- 
--  Procedure Name    : SetAlgorithm
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Set Algorithm To iQSmartFEED or iQFlashFEED
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SetiQFeedAlgorithm (string Algo,int ScaleNo)
{
 int scale_channel,scale_number;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
  
  bool result = iQSetAlgorithm (scale_channel, scale_number, Algo);
  if(result) iQFeedAlgorithmName[ScaleNo-1] = Algo;
  return (result);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : SetAnalogOutputVal
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Set Analog Output Values
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SetAnalogOutputVal (float slow_percentage, float fast_percentage,int ScaleNo)
{
  bool result,aout_active;
  int scale_channel,scale_number,aout_mode,aout_no,type,out_index=0;
  string aout_name[10];

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
  aout_active = AOUTActive[AIO1];
  aout_mode   = AOUTMode[AIO1];
  type        = AOUTType[AIO1];
  aout_name   = AOUTName[type];
  aout_no     = AOUTModule[AIO1];
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
  aout_active = AOUTActive[AIO2];
  aout_mode   = AOUTMode[AIO2];
  type        = AOUTType[AIO2];
  aout_name   = AOUTName[type];
  aout_no     = AOUTModule[AIO2];
 }
 
  if (aout_active && MC.FeederType != FeederGV && MC.FeederType != FeederDS)
   {
    if (slow_percentage == 0.0 || fast_percentage == 0.0)
       fast_percentage = 1.0;
    if (slow_percentage < 0.0 || slow_percentage > 100.0)
      return (OFF);
    if (fast_percentage < 0.0 || fast_percentage > 100.0)
      return (OFF);
    if (slow_percentage >= fast_percentage)
      return (OFF);
    
    result = iQSmSetAnalogOutput (scale_channel, scale_number,out_index,aout_name, aout_no, aout_mode, slow_percentage/100.0, fast_percentage/100.0);
    return (result);
   }
  else return(ON);  
}
 

/*------------------------------------------------------------------------- 
--  Procedure Name    : SetTargetValue
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Set Target Value related iQ Functions
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SetTargetValue (float targetvalue,int ScaleNo)
{
bool   result;
int scale_channel,scale_number;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
 
  result  = iQSetTargetWeight (scale_channel, scale_number, targetvalue);
  
  if (!iQSetThreshold (scale_channel, scale_number, targetvalue*(THRESHOLD_PERCENT/100), 0.05))
  {
    return (OFF);
  }

  if (!iQSetEmergencyStopFast (scale_channel, scale_number, targetvalue * 1.6))
  {
    return (OFF);
  }
  return (result);
}  

/*------------------------------------------------------------------------- 
--  Procedure Name    : SetFastFilterSize
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Set Fast Feeding Filter Size
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SetFastFilterSize (int size,int ScaleNo)
{
bool result;
int  fast_filter_size;
int scale_channel,scale_number;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
 
  if (size < 0 || size > 20)
    fast_filter_size = DEFAULT_FAST_FILTER_SIZE;
  else
    fast_filter_size = size;
    result = iQSetFastFilterSize (scale_channel, scale_number, fast_filter_size);
  return (result);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : SetSlowFilterSize
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Set Slow Feeding Filter Size
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool SetSlowFilterSize (int size,int ScaleNo)
{
bool result;
int  slow_filter_size;
int scale_channel,scale_number;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
   

  if (size < 0 || size > 20)
    slow_filter_size = DEFAULT_SLOW_FILTER_SIZE;
  else
    slow_filter_size = size;
    result = iQSetSlowFilterSize (scale_channel, scale_number, slow_filter_size);
  return (result);
}

bool SmSetControlParameters(int ScaleNo)
{
 string  CPSmFastAvgPointsTemp[128],CPSmSlowAvgPointsTemp[128],CPSmSlowItpPointsTemp[512];
 float   CPSmSwitchTimeTemp;
 int scale_channel,scale_number;
 bool res;
  
 if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
  
  CPSmFastAvgPointsTemp = CPSmFastAvgPointsMem[ScaleNo-1];
  CPSmSlowAvgPointsTemp = CPSmSlowAvgPointsMem[ScaleNo-1];
  CPSmSlowItpPointsTemp = CPSmSlowItpPointsMem[ScaleNo-1];
  CPSmSwitchTimeTemp    = CPSmSwitchTimeMem[ScaleNo-1];
  res = iQSmSetControlParameters(scale_channel,scale_number,CPSmFastAvgPointsTemp,CPSmSlowAvgPointsTemp,CPSmSlowItpPointsTemp,CPSmSwitchTimeTemp*CPSmSwitchTimePct);
  if(res) InitCPSmSwitchTime[ScaleNo-1] = OFF;
  
 return(res);
}  

/*------------------------------------------------------------------------- 
--  Procedure Name    : InitStartiQSmart
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Start Event Reception
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/

void InitStartiQSmart(int ScaleNo)
{
 //bool noerror,noerror2,noerror3,noerror4;
 bool noerror[5];
 bool SetError;
 bool DeadTimeSetOK;
 float iQDeadTimeReadTemp;
 int scanmem[20];
 int scale_channel,scale_number;
 float minfeed,maxfeed;
 float   iQSuspendPct;

   if(!Feeder.SuspendLearn_InitialImpact[MC.FeederType])
    iQSuspendPct = 0.0;
   else
    iQSuspendPct = 0.35;                      

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
  minfeed = WP.MinFeeding1;
  maxfeed = WP.MaxFeeding1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
  minfeed = WP.MinFeeding2;
  maxfeed = WP.MaxFeeding2;
 }
// Initialize filling parameters
   noerror[0] = OFF;
   noerror[1] = OFF;
   noerror[2] = OFF;
   noerror[3] = OFF;
   noerror[4] = OFF;
   
   scanmem[0] = systemtimer_ms();
   OpenConnection(ScaleNo);
   scanmem[1] = systemtimer_ms();
   if(SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_SMART,ScaleNo))
   {
   scanmem[2] = systemtimer_ms();
    if(SetTargetValue(TargetWeight[ScaleNo-1]*UnitIQtoADM,ScaleNo))
    {
    scanmem[3] = systemtimer_ms();
     if (SetAnalogOutputVal(minfeed, maxfeed,ScaleNo))
     {
      scanmem[4] = systemtimer_ms();
     {
       
        if (SetSlowFilterSize (MP.SlowFilterSize,ScaleNo))
         if (SetFastFilterSize (MP.FastFilterSize,ScaleNo))
          if (iQSetSlowFillTimes (scale_channel,scale_number,0.050,req_slow_fill_time)) 
           if (iQSmSetLearnDelay1(scale_channel,scale_number,1.0))
            if (iQSmSetLearnSuspendPercentage1(scale_channel,scale_number,iQSuspendPct))
            {
             noerror[0] = ON;
            }
     }
     }
     
         if(iQSmSetFillSuspendPercentage(scale_channel,scale_number,iQSuspendPct))
         //if(iQSmSetFastSlowZeroPercentage(scale_channel,scale_number,iQFastSlowPct)) //Percentage of Slow flow to detect Fast to Slow flow transition- not 0 sometimes
           {
             noerror[1] = ON;
           } 
           

    }
   }  
      scanmem[5] = systemtimer_ms();
    if(iQSmSetFastFillRequiresFlowMaximum(scale_channel, scale_number,OFF))   //Default ON
     if(iQSmSetMinimumSwitchTimePercentage(scale_channel, scale_number,0.5))   //Default 0.0
      {
       noerror[4] = ON;
      } 
        
   if(LearniQSmartParam[ScaleNo-1] || LearniQSmartParamMem[ScaleNo-1])
   { 
    if(iQClearControlParameters (scale_channel, scale_number))
     {      
           scanmem[6] = systemtimer_ms();
           InitCPSmSwitchTime[ScaleNo-1] = ON;
           CPSmSwitchTimeMem[ScaleNo-1]  = 0;
           iQSmartLearnNbr[ScaleNo-1]=0;
           noerror[2] = ON;
           iQFeedSettledCnt[ScaleNo-1]=0;
           if(LearniQSmartParam[ScaleNo-1]) 
            {
             LearniQSmartParamMem[ScaleNo-1] = ON;
             LearniQSmartParam[ScaleNo-1] = OFF;
             NbrOf1stLearned[ScaleNo-1] = 1;
            }  
           else
             NbrOf1stLearned[ScaleNo-1]++;
           
           
           if(NbrOf1stLearned[ScaleNo-1] >= Feeder.NbrOf1stLearn[MC.FeederType])
           {
            LearniQSmartToSave[ScaleNo-1] = ON;
            LearniQSmartParamMem[ScaleNo-1]= OFF;
            NbrOf1stLearned[ScaleNo-1] = 0;
           } 
     }   
   }                                                
   else
     {
       noerror[2] = SmSetControlParameters(ScaleNo);
      if( noerror[2])
       {
        iQDeadTimeReadTemp = iQDeadTimeRead[ScaleNo-1];
        DeadTimeSetOK = iQSmSetDeadTime(scale_channel, scale_number,iQDeadTimeReadTemp);
       } 
      scanmem[6] = systemtimer_ms();
     }
       
   
   noerror[3] = iQOutActivate(ScaleNo);             
   scanmem[7] = systemtimer_ms();
   if(!noerror[0] || !noerror[1] || !noerror[2] || !noerror[4]) 
    {
     SystemErrorCode = concat("#",trim(string(scale_number)),"-","130 iQ Smart variables Learning not initialized");
    }
   
     if(!noerror[3])  
    {
     SystemErrorCode = concat("#",trim(string(scale_number)),"-","134 iQ Smart Outputs must be on the PIMs");
    }

    //EmptyBuffer();
    scanmem[8] = systemtimer_ms();
    InitiQSmart[ScaleNo-1] = OFF;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : InitStartiQFlash
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Start Event Reception
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/

void InitStartiQFlash(int ScaleNo)
{
bool  noerror ,noerror2,noerror3;
float ReduceOutput; 
float SwitchWeight;
int scale_channel,scale_number,aout_mode,aout_no,type;
float minfeed,maxfeed;
string aout_name[10];
string  CPFlFastPointsTemp[128],CPFlDeviationPointsTemp[256];

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
  minfeed = WP.MinFeeding1;
  maxfeed = WP.MaxFeeding1;
  aout_mode = AOUTMode[AIO1];
  type        = AOUTType[AIO1];
  aout_name = AOUTName[type];
  aout_no   = AIO1 + 1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
  minfeed = WP.MinFeeding2;
  maxfeed = WP.MaxFeeding2;
  aout_mode = AOUTMode[AIO2];
  type        = AOUTType[AIO2];
  aout_name = AOUTName[type];
  aout_no   = AIO2 + 1;
 }
// Initialize filling parameters

 
   noerror = OFF;
   noerror2 = OFF;
   noerror3 = OFF;
   
   ReduceOutput = (minfeed+((maxfeed-minfeed)*(iQFlReduceOutput/100.0)))/100.0;
   SwitchWeight = (TargetWeight[ScaleNo-1]*UnitIQtoADM)*(iQFlSwitchWeight/100.0);
                                         

   OpenConnection(ScaleNo);
   SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_FLASH,ScaleNo);
    if(iQFlSetAnalogOutput(scale_channel, scale_number,aout_name,aout_no,aout_mode, minfeed/100.0, maxfeed/100.0))
     if(SetTargetValue(TargetWeight[Scale1]*UnitIQtoADM,ScaleNo))
      if(iQFlSetFeedingLimits(scale_channel, scale_number,maxfeed/100.0, minfeed/100.0))
      {
        if (SetSlowFilterSize (MP.SlowFilterSize,ScaleNo))
         if (SetFastFilterSize (MP.FlashFilterSize,ScaleNo))
          if(iQFlSetSwitchWeight(scale_channel, scale_number,SwitchWeight))
           if(iQFlSetControlTime(scale_channel, scale_number,iQFlControlTime))
            if(iQFlSetReduceOutput(scale_channel, scale_number,ReduceOutput))
              {
               noerror = ON;
              }
      }
   
   
   if(LearniQFlashParam[ScaleNo-1])
   {
      if (iQClearControlParameters (scale_channel, scale_number))
          {
            noerror2 = ON;
            iQFlashLearnNbr[ScaleNo-1]=0;
            LearniQFlashToSave[ScaleNo-1] = ON;
            LearniQFlashParam[ScaleNo-1]=OFF;
            iQFeedSettledCnt[ScaleNo-1]=0;
          }
   }
        
   else
   {        
   CPFlFastPointsTemp      = CPFlFastPointsMem[ScaleNo-1];
   CPFlDeviationPointsTemp = CPFlDeviationPointsMem[ScaleNo-1];
   
   if(iQFlSetControlParameters(scale_channel,scale_number,CPFlFastPointsTemp,CPFlDeviationPointsTemp))
      {
       noerror2 = ON;
      }
   }
      
   noerror3 = iQOutActivate(ScaleNo);             
 
   if(!noerror || !noerror2 || !noerror3) 
    {
     SystemErrorCode = concat("#",trim(string(scale_number)),"-","120 iQ Flash variables not initialized");
    }
   
    //EmptyBuffer();
    InitiQFlash[ScaleNo-1] = OFF;
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : FeedingStop
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Stop iQFeeding process
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void FeedingStop(int ScaleNo)
{
int scale_channel,scale_number;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
//To stop iQ Feed
iQFeedingStop (scale_channel, scale_number);
}


/*------------------------------------------------------------------------- 
--  Procedure Name    :StartFeeding
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Start Feeding for iQ algo
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool StartFeeding(int ScaleNo)
{

bool noerror,waitsettled;
int scale_channel,scale_number;

if(ScaleNo == 1)
 {
  scale_channel = SCALE_CHANNEL1;
  scale_number  = SCALE_NUMBER1;
 } 
 
 if(ScaleNo == 2)
 {
  scale_channel = SCALE_CHANNEL2;
  scale_number  = SCALE_NUMBER2;
 }
 
//Start iQ Feeding
waitsettled = iQFeedWaitSettled[ScaleNo-1];
noerror = iQFeedingStart (scale_channel, scale_number,waitsettled);   // ON => activate parameter waiting for settled
return(noerror);
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : GetFillingData
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Get Data From iQ Filling after cycle completed
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void GetFillingData(bool emptybuffer)
{

int     ScaleNo,i;
string  status[256],status_msg[5][64];
float   weight;
float   fast_slow_switch_weight;
float   slow_fill_duration;
float   fast_fill_duration;
float   filling_duration;
float   overall_duration;
float   fastCO,slowCO;
bool    iQReadEventStatus,validscale;
bool    iQFlashLearned[2];
bool    iQSmartLearned[2];
int     scale_channel,scale_number,msg_no;
string  CPSmFastAvgPointsTemp[128],CPSmSlowAvgPointsTemp[128],CPSmSlowItpPointsTemp[512];
float   CPSmSwitchTimeTemp;
bool    iQSmartLearnedTemp;
string  CPFlFastPointsTemp[128],CPFlDeviationPointsTemp[256];
bool    iQFlashLearnedTemp;
float   ctrl_fast_timeTemp,ctrl_slow_timeTemp,fast_flowTemp,slow_flowTemp,fast_flow_varTemp,slow_flow_varTemp;
float   FastCutoff_kg,SlowCutoff_kg;
bool    DeadTimeGetOK;
float   iQDeadTimeReadTemp;

//Read Data from iQ Feed after feeding completed
 msg_no = msgread (0);
 if (msg_no == 6)
 {
    iQReadEventStatus = iQReadEvent (ScaleNo,weight,status,FastCutoff_kg,SlowCutoff_kg,slow_fill_duration,
                                     fast_fill_duration,filling_duration,overall_duration);
           
           fastCO = FastCutoff_kg * UnitADMtoIQ;
           slowCO = SlowCutoff_kg * UnitADMtoIQ;

    //Statistical Data Comming from Smart Feed
    if(iQReadEventStatus && (ScaleNo == 1 || ScaleNo == 2))
     if(iQReadEventStats(ScaleNo,ctrl_fast_timeTemp,ctrl_slow_timeTemp,fast_flowTemp,slow_flowTemp,fast_flow_varTemp,slow_flow_varTemp))
      {
       stat_controlled_fast_time[ScaleNo-1]   = ctrl_fast_timeTemp;
       stat_controlled_slow_time[ScaleNo-1]   = ctrl_slow_timeTemp;
       stat_stable_fast_flow[ScaleNo-1]       = fast_flowTemp;
       stat_stable_slow_flow[ScaleNo-1]       = slow_flowTemp;
       stat_fast_flow_fluctuation[ScaleNo-1]  = fast_flow_varTemp;
       stat_slow_flow_fluctuation[ScaleNo-1]  = slow_flow_varTemp;
      }
                                        
  validscale = OFF;
  if(ScaleNo == 1)
  {
   scale_channel = SCALE_CHANNEL1;
   scale_number  = SCALE_NUMBER1;
   validscale = ON;
  } 
 
  if(ScaleNo == 2)
  {
   scale_channel = SCALE_CHANNEL2;
   scale_number  = SCALE_NUMBER2;
   validscale = ON;
  }
                                    
  if(!emptybuffer)
   {  
    if(iQReadEventStatus && validscale)                 
    { 
     i = 0;
     FastCutoff[ScaleNo-1] = fastCO;
     SlowCutoff[ScaleNo-1] = slowCO;
     iQFeedStatusFinished[ScaleNo-1] = OFF;
     iQFeedStatusAborted[ScaleNo-1] = OFF;
     iQFeedStatusSettled[ScaleNo-1] = OFF;
     iQFeedStatusEmergency[ScaleNo-1] = OFF; 
     
     
     split (status_msg[0], status, ',');
     while(status_msg[i] != "" && i<=3)
      {
      
       if(status_msg[i] == FILLING_STATUS_FINISHED) 
            iQFeedStatusFinished[ScaleNo-1] = ON; 
       if(status_msg[i] == FILLING_STATUS_ABORTED)
           { 
            if(!WeighmentAborted[ScaleNo-1])
             {
              iQFeedStatusAborted[ScaleNo-1] = ON;
              if(WP.FeedAlgoType == FeediQFlash)SystemErrorCode = concat("#",trim(string(scale_number)),"-","121 iQ Flash weighment aborted");
              if(WP.FeedAlgoType == FeediQSmart)SystemErrorCode = concat("#",trim(string(scale_number)),"-","131 iQ Smart weighment aborted");
             }
           }  
      if(status_msg[i] == FILLING_STATUS_SETTLED)
            iQFeedStatusSettled[ScaleNo-1] = ON; 
      if(status_msg[i] == FILLING_STATUS_EMERGENCY)
            {
            iQFeedStatusEmergency[ScaleNo-1] = ON;
            if(WP.FeedAlgoType == FeediQFlash)SystemErrorCode = concat("#",trim(string(scale_number)),"-","122 iQ Flash emergency weight detected");
            if(WP.FeedAlgoType == FeediQSmart)SystemErrorCode = concat("#",trim(string(scale_number)),"-","132 iQ Smart emergency weight detected");
            }
      i++;      
      }  
      
      if(!iQFeedStatusFinished[ScaleNo-1] && iQFeedStatusSettled[ScaleNo-1] && !iQFeedStatusAborted[ScaleNo-1] && !iQFeedStatusEmergency[ScaleNo-1])
        iQFeedStatusFinished[ScaleNo-1] = ON;
        
      if (iQFeedStatusFinished[ScaleNo-1] && !WeighmentAborted[ScaleNo-1])
      {  
      ProdBulkDuration[ScaleNo-1]     = fast_fill_duration;
      ProdDribbleDuration[ScaleNo-1] = filling_duration - fast_fill_duration;
      }
      iQFeedDone[ScaleNo-1]=ON;
      
     #if defined SYSTEC_DATA_DEBUG
      writestring (0, concat (date,";",
                              time,";",
                              TargetWeight[ScaleNo-1],unit,";",
                              weight,";",
                              status,";",
                              fast_slow_switch_weight,";",
                              slow_fill_duration,";",
                              fast_fill_duration,";",
                              filling_duration,";",
                              overall_duration,";"));
     #endif
    
  
     
     if(WP.FeedAlgoType == FeediQFlash)
     {
       if(iQFeedWaitSettled[ScaleNo-1])
       {
       if(!iQFlGetControlParameters(scale_channel, scale_number, CPFlFastPointsTemp,CPFlDeviationPointsTemp,iQFlashLearnedTemp))
          SystemErrorCode = concat("#",trim(string(scale_number)),"-","128 iQ Flash could not get control parameters");
       else
        {
         CPFlFastPointsMem[ScaleNo-1]      = CPFlFastPointsTemp;
         CPFlDeviationPointsMem[ScaleNo-1] = CPFlDeviationPointsTemp;
         iQFlashLearned[ScaleNo-1]         = iQFlashLearnedTemp;
         
         if((iQFlashLearned[ScaleNo-1] || iQFeedSettledCnt[ScaleNo-1] == IQFEEDSETTLEDNBR)&& 
          ((LearniQFlashToSave[ScaleNo-1] ||(SampleFreqCnt[ScaleNo-1] == (MP.SampleSize-1))) && !LowLevel[ScaleNo-1] && !EmptyHopper && !SlowCycleMem[ScaleNo-1]))
          {
           SaveiQFeedParamFlag[ScaleNo-1] = Execute;
           LearniQFlashToSave[ScaleNo-1] = OFF;
          }
        }    
       }
     }  
     
     if(WP.FeedAlgoType == FeediQSmart)
     {
      if(iQFeedWaitSettled[ScaleNo-1])
       {
       if(!iQSmGetControlParameters(scale_channel,scale_number,CPSmFastAvgPointsTemp,CPSmSlowAvgPointsTemp,CPSmSlowItpPointsTemp,CPSmSwitchTimeTemp,iQSmartLearnedTemp))
        SystemErrorCode = concat("#",trim(string(scale_number)),"-","138 iQ Smart could not get control parameters");
       else
        {
         CPSmFastAvgPointsMem[ScaleNo-1] = CPSmFastAvgPointsTemp;
         CPSmSlowAvgPointsMem[ScaleNo-1] = CPSmSlowAvgPointsTemp;
         CPSmSlowItpPointsMem[ScaleNo-1] = CPSmSlowItpPointsTemp;
         if(CPSmSwitchTimeMem[ScaleNo-1] == 0)
         {  
          CPSmSwitchTimeMem[ScaleNo-1] = CPSmSwitchTimeTemp;
         }
         DeadTimeGetOK = iQSmGetDeadTime(scale_channel,scale_number,iQDeadTimeReadTemp);
         iQDeadTimeRead[ScaleNo-1] = iQDeadTimeReadTemp;
          
         iQSmartLearned[ScaleNo-1] = iQSmartLearnedTemp;
         
         if((iQSmartLearned[ScaleNo-1] || iQFeedSettledCnt[ScaleNo-1] == IQFEEDSETTLEDNBR) 
          && ((LearniQSmartToSave[ScaleNo-1] || (SampleFreqCnt[ScaleNo-1]==(MP.SampleSize-1))) && !LowLevel[ScaleNo-1] && !EmptyHopper && !SlowCycleMem[ScaleNo-1]))
         {
         SaveiQFeedParamFlag[ScaleNo-1] = Execute;
         LearniQSmartToSave[ScaleNo-1] = OFF;
         }
        } 
       } 
     } 
                                                                                                                                                                  
    }
   }  
 }
}

                                                          
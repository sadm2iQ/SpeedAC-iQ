/*-----------------------------------------------------------------------------
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
             if (result < min) 
              result = min;
             if (result > max) 
              result = max;
             
             return (result) ;                
}

/*------------------------------------------------------------------------- 
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


void ReadServiceMode(void)
{
 int servicedatasaved = saveservicedata (SMFile);
}

//PbZero values verification from Service mode data
void CheckPBZeroValues(string scalenbr, int *PBZeroPlus)
{
 string caracter[1],buffer[40],buffer2[40],ScaleString[10];
 int FileNbr=5;
 bool GoodScale = OFF;
 
 ScaleString = concat("Scale ",scalenbr);
  
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
      if(left(buffer2, 7) == ScaleString) 
       {
        GoodScale = ON;
       } 
     
     if(GoodScale) 
      if(left(buffer2, 12) == "PbZero (%) +")
       {
        PBZeroPlus = int(trim(sub(buffer2,13,length(buffer2)-13)));
        break;
       }
      
     buffer = "";
     }
    }  
  }
  
 fclose(FileNbr);     
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
bool OpenConnection(void)
{
 //To initialize Channel Connection
 if (!iQOpenConnection (SCALE_CHANNEL, "127.0.0.1")) 
  SystemErrorCode = "140 iQFeeding connection not established";
 else
  return(ON);                   
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
--  Procedure Name    : ValidateAlgoType
--  Created by        : Steve Santerre
--  Last modified on  : 2018/08/31
--  
--  Purpose           : Verify if Selected Algo is Allowed with this Feeder
--                      
--  Value Parameters  :
--  Variable Params   : return the "limited" algo type
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
int ValidateAlgoType(int Feeder,int RequestedAlgo,int LastAlgo)
{

  switch(Feeder)
  {
    case FeederNone:  
      {
       return(FeedStd);
      }
       
    case FeederG:
    case FeederB:
    case FeederGV:
    case FeederV:
    case FeederSS:
    case FeederDS:
      {
       if(RequestedAlgo == FeedStd || RequestedAlgo == FeediQSmart || RequestedAlgo == FeediQSim)
        return(RequestedAlgo);
       else if (LastAlgo == FeedStd || LastAlgo == FeediQSmart || LastAlgo == FeediQSim)
        return(LastAlgo);
       else 
        return(FeediQSmart);
      }   
    
    case FeederGHS:
      {
       if(RequestedAlgo == FeedStd || RequestedAlgo == FeediQSmart || RequestedAlgo == FeediQFlash
          || RequestedAlgo == FeediQSim || RequestedAlgo == FeedGHSSmartPlus)
        return(RequestedAlgo);
       else if (LastAlgo == FeedStd || LastAlgo == FeediQSmart || LastAlgo == FeediQFlash 
          || LastAlgo == FeediQSim || RequestedAlgo == FeedGHSSmartPlus)
        return(LastAlgo); 
       else
        return(FeediQSmart);
      }   
    
    case FeederBHS:
      {
       if(RequestedAlgo == FeediQSmart || RequestedAlgo == FeedPLoop || RequestedAlgo == FeediQSim)
        return(RequestedAlgo);
       else if(LastAlgo == FeediQSmart || LastAlgo == FeedPLoop || LastAlgo == FeediQSim)
        return(LastAlgo);
       else 
        return(FeediQSmart);
      } 
        
    case FeederBSF:
      {
       if(RequestedAlgo == FeedStd || RequestedAlgo == FeediQSim)
        return(RequestedAlgo);
       else if(LastAlgo == FeedStd || LastAlgo == FeediQSim)
        return(LastAlgo);
       else 
        return(FeedStd);
      } 
      
    case FeederBSFHS:
     {
       if(RequestedAlgo == FeedPLoop || RequestedAlgo == FeediQSim)
        return(RequestedAlgo);
       else if(LastAlgo == FeedPLoop || LastAlgo == FeediQSim)
        return(LastAlgo);
       else 
        return(FeedPLoop);
      } 
    
    
  }
}  
/*------------------------------------------------------------------------- 
--  Procedure Name    : ConfirmRestart
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
bool iQOutRelease(void)
{
 bool result1,result2;
 
 result1 = OFF;
 result2 = OFF;
 
 result1 = iQSetEnableSignalOutput (SCALE_CHANNEL, SCALE_NUMBER, -1,OFF);
 
 if(iQFeedAlgorithmName == IQ_FEEDING_ALGORITHM_SMART)
 { 
  result2 = iQSmSetDigitalOutput(SCALE_CHANNEL, SCALE_NUMBER,-1,-1,0);
 }
 
 else if(iQFeedAlgorithmName == IQ_FEEDING_ALGORITHM_LIGHT)
 { 
  result2 = iQLightSetDigitalOutput(SCALE_CHANNEL, SCALE_NUMBER,-1,-1,0);
 }
 
 else
 { 
  result2 = ON;
 }
   
iQOutputEnabled = OFF;
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
bool iQOutActivate(void)
{
int EnableOutput,AddressBulk,EnableOutOn1St;
bool noerr1,noerr2,EnableBulk;

 //Enable behavior on 1st Learning: 
 // 0=OFF if Fast/Slow OFF
 // 1=ON all cycle
 // 2=ON until First Slow goes OFF(allow Catch gate to let Product of Fast to Fall in the Pan)
  
  if(!Feeder.EnableOnAllLearning[MC.FeederType])
    EnableOutOn1St = 0;
  else
    EnableOutOn1St = 2;
      
 noerr1 = ON;
 noerr2 = ON;

   if (IO_Enable[O_CatchGate])
    {
    noerr1 = iQSetEnableSignalOutput (SCALE_CHANNEL, SCALE_NUMBER, IO_Address[O_CatchGate]-PIMoffset,EnableOutOn1St);
    iQOutputEnabled = ON;
    }
   
   if((MC.FeederType == FeederB || MC.FeederType == FeederBHS) && !IO_Enable[O_BulkFeed] && AOUTActive[AIO1])
    {
     EnableBulk    = ON;
     AddressBulk    = BULKADDRESS+PIMoffset;
     FeederBWithAout = ON;
    }
   else
    {
     EnableBulk    = IO_Enable[O_BulkFeed];
     AddressBulk    = IO_Address[O_BulkFeed];
     FeederBWithAout = OFF;
    }  
   
   if(IO_Enable[O_DribbleFeed])
   { 
    if(EnableBulk)
    {
    noerr2 = iQSmSetDigitalOutput(SCALE_CHANNEL, SCALE_NUMBER,AddressBulk-PIMoffset,IO_Address[O_DribbleFeed]-PIMoffset,MC.DribbleOutOnInBulk);
    iQOutputEnabled = ON;
    }
   else if(IO_Enable[O_CatchGate]) 
    {
     noerr2 = iQSmSetDigitalOutput(SCALE_CHANNEL, SCALE_NUMBER,IO_Address[O_CatchGate]-PIMoffset,IO_Address[O_DribbleFeed]-PIMoffset,MC.DribbleOutOnInBulk);
     iQOutputEnabled = ON;
    }
   }  
   else 
     if(IO_Enable[O_BulkFeed])
      {
       SystemErrorCode = "306 Output Dribble Feed not configured";
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
bool SetiQFeedAlgorithm (string Algo)
{
  bool result = iQSetAlgorithm (SCALE_CHANNEL, SCALE_NUMBER, Algo);
  if(result) iQFeedAlgorithmName = Algo;
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
bool SetAnalogOutputVal(float slow_percentage, float fast_percentage,int OutNbr)
{
  bool result;
  int  type;
  string aout_name[10];
  
  if (AOUTActive[OutNbr] && MC.FeederType != FeederGV && MC.FeederType != FeederDS)
   {
    if (slow_percentage == 0.0 || fast_percentage == 0.0)
       fast_percentage = 1.0;
    if (slow_percentage < 0.0 || slow_percentage > 100.0)
      return (OFF);
    if (fast_percentage < 0.0 || fast_percentage > 100.0)
      return (OFF);
    if (slow_percentage >= fast_percentage)
      return (OFF);
   
   type        = AOUTType[OutNbr];
   aout_name   = AOUTName[type];
   
    result = iQSmSetAnalogOutput (SCALE_CHANNEL, SCALE_NUMBER,OutNbr,aout_name, AOUTModul[OutNbr],AOUTMode[OutNbr], slow_percentage/100.0, fast_percentage/100.0);
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
bool SetTargetValue (float targetvalue)
{
bool   result;

  result  = iQSetTargetWeight (SCALE_CHANNEL, SCALE_NUMBER, targetvalue);
  
  if (!iQSetThreshold (SCALE_CHANNEL, SCALE_NUMBER, targetvalue*(THRESHOLD_PERCENT/100), 0.05))
  {
    return (OFF);
  }

  if (!iQSetEmergencyStopFast (SCALE_CHANNEL, SCALE_NUMBER, targetvalue * 1.6))
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
bool SetFastFilterSize (int size)
{
bool result;
int  fast_filter_size;

  if (size < 0 || size > 20)
    fast_filter_size = DEFAULT_FAST_FILTER_SIZE;
  else
    fast_filter_size = size;
    result = iQSetFastFilterSize (SCALE_CHANNEL, SCALE_NUMBER, fast_filter_size);
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
bool SetSlowFilterSize (int size)
{
bool result;
int  slow_filter_size;
  

  if (size < 0 || size > 20)
    slow_filter_size = DEFAULT_SLOW_FILTER_SIZE;
  else
    slow_filter_size = size;
    result = iQSetSlowFilterSize (SCALE_CHANNEL, SCALE_NUMBER, slow_filter_size);
  return (result);
}

bool SmSetControlParameters(void)
{
 bool res;
  
  res = iQSmSetControlParameters(SCALE_CHANNEL,SCALE_NUMBER,CPSmFastAvgPointsMem,CPSmSlowAvgPointsMem,CPSmSlowItpPointsMem,CPSmSwitchTimeMem*CPSmSwitchTimePct);
  if(res) InitCPSmSwitchTime = OFF;
  
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

void InitStartiQSmart(void)
{
//bool noerror,noerror2,noerror3,noerror4;
bool noerror[5];
bool SetError;
bool DeadTimeSetOK;
int scanmem[20];
float iQSuspendPct;

// Initialize filling parameters

   if(!Feeder.SuspendLearn_InitialImpact[MC.FeederType])
    iQSuspendPct = 0.0;
   else
    iQSuspendPct = 0.35;                      

   noerror[0] = OFF;
   noerror[1] = OFF;
   noerror[2] = OFF;
   noerror[3] = OFF;
   noerror[4] = OFF;
   

   scanmem[0] = systemtimer_ms();
   OpenConnection();
   scanmem[1] = systemtimer_ms();
   if(SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_SMART))
   {
   scanmem[2] = systemtimer_ms();
    if(SetTargetValue(TargetWeight[Scale1]*UnitIQtoADM))
    {
    scanmem[3] = systemtimer_ms();
     if (SetAnalogOutputVal(WP.MinFeeding, WP.MaxFeeding,AIO1))
     {
      scanmem[4] = systemtimer_ms();
     {
      if (SetAnalogOutputVal(WP.RegMinFeeding, WP.RegMaxFeeding,AIO2))
        if (SetSlowFilterSize (MP.SlowFilterSize))
         if (SetFastFilterSize (MP.FastFilterSize))
          if (iQSetSlowFillTimes (SCALE_CHANNEL,SCALE_NUMBER,0.050,req_slow_fill_time))
          if (iQSmSetLearnDelay1(SCALE_CHANNEL,SCALE_NUMBER,1.0))
           if (iQSmSetLearnSuspendPercentage1(SCALE_CHANNEL,SCALE_NUMBER,iQSuspendPct))
            {
             noerror[0] = ON;
            } 
     }
     }
     
        if(iQSmSetFillSuspendPercentage(SCALE_CHANNEL,SCALE_NUMBER,iQSuspendPct))
         //if(iQSmSetFastSlowZeroPercentage(SCALE_CHANNEL,SCALE_NUMBER,iQFastSlowPct)) //Percentage of Slow flow to detect Fast to Slow flow transition- not 0 sometimes
           {
             noerror[1] = ON;
           } 
           

    }
   }  
      scanmem[5] = systemtimer_ms();
      
    if(iQSmSetFastFillRequiresFlowMaximum(SCALE_CHANNEL, SCALE_NUMBER,OFF))   //Default ON
     if(iQSmSetMinimumSwitchTimePercentage(SCALE_CHANNEL, SCALE_NUMBER,0.5))   //Default 0.0
      {
       noerror[4] = ON;
      } 
      
   if(LearniQSmartParam || LearniQSmartParamMem)
   { 
    if(iQClearControlParameters (SCALE_CHANNEL, SCALE_NUMBER))
     {      
           scanmem[6] = systemtimer_ms();
           InitCPSmSwitchTime = ON;
           CPSmSwitchTimeMem  = 0;
           iQSmartLearnNbr=0;
           noerror[2] = ON;
           iQFeedSettledCnt=0;
           if(LearniQSmartParam) 
            {
             LearniQSmartParamMem = ON;
             LearniQSmartParam = OFF;
             NbrOf1stLearned = 1;
            }  
           else
             NbrOf1stLearned++;
           
           
           if(NbrOf1stLearned >= Feeder.NbrOf1stLearn[MC.FeederType])
           {
            LearniQSmartToSave = ON;
            LearniQSmartParamMem = OFF;
            NbrOf1stLearned = 0;
           } 
     }   
   }                                                
   else
     {
     noerror[2] = SmSetControlParameters();
     if(noerror[2])
      DeadTimeSetOK = iQSmSetDeadTime(SCALE_CHANNEL,SCALE_NUMBER,iQDeadTimeRead);
     scanmem[6] = systemtimer_ms();
     }
       
   
   noerror[3] = iQOutActivate();             
   scanmem[7] = systemtimer_ms();
   
    if(!noerror[0] || !noerror[1] || !noerror[2] || !noerror[4])  
    {
     SystemErrorCode = "130 iQ Smart variables Learning not initialized";
    }
    
    if(!noerror[3])  
    {
     SystemErrorCode = "134 iQ Smart Outputs must be on the PIMs";
    }


    EmptyBuffer();
    scanmem[8] = systemtimer_ms();
    InitiQSmart = OFF;
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

void InitStartiQFlash(void)
{
bool  noerror ,noerror2,noerror3;
float ReduceOutput; 
float SwitchWeight;
int    type;
string aout_name[10];

// Initialize filling parameters
   
 
   noerror = OFF;
   noerror2 = OFF;
   noerror3 = OFF;
   
   type        = AOUTType[AIO1];
   aout_name   = AOUTName[type];
  
   ReduceOutput = (WP.MinFeeding+((WP.MaxFeeding-WP.MinFeeding)*(iQFlReduceOutput/100.0)))/100.0;
   SwitchWeight = (TargetWeight[Scale1]*UnitIQtoADM)*(iQFlSwitchWeight/100.0);
                                         

   OpenConnection();
   SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_FLASH);
    if(iQFlSetAnalogOutput(SCALE_CHANNEL, SCALE_NUMBER,aout_name,AOUTModul[AIO1],AOUTMode[AIO1], WP.MinFeeding/100.0, WP.MaxFeeding/100.0))
     if(SetTargetValue(TargetWeight[Scale1]*UnitIQtoADM))
      if(iQFlSetFeedingLimits(SCALE_CHANNEL, SCALE_NUMBER,WP.MaxFeeding/100.0, WP.MinFeeding/100.0))
      {
        if (SetSlowFilterSize (MP.SlowFilterSize))
         if (SetFastFilterSize (MP.FlashFilterSize))
          if(iQFlSetSwitchWeight(SCALE_CHANNEL, SCALE_NUMBER,SwitchWeight))
           if(iQFlSetControlTime(SCALE_CHANNEL, SCALE_NUMBER,iQFlControlTime))
            if(iQFlSetReduceOutput(SCALE_CHANNEL, SCALE_NUMBER,ReduceOutput))
              {
               noerror = ON;
              }
      }
   
   
   if(LearniQFlashParam)
   {
      if (iQClearControlParameters (SCALE_CHANNEL, SCALE_NUMBER))
          {
            noerror2 = ON;
            iQFlashLearnNbr=0;
            LearniQFlashToSave = ON;
            LearniQFlashParam=OFF;
            iQFeedSettledCnt=0;
          }
   }
        
   else
   {        
   if(iQFlSetControlParameters(SCALE_CHANNEL,SCALE_NUMBER,CPFlFastPointsMem,CPFlDeviationPointsMem))
      {
       noerror2 = ON;
      }
   }
      
   noerror3 = iQOutActivate();             
 
   if(!noerror || !noerror2 || !noerror3) 
    {
     SystemErrorCode = "120 iQ Flash variables not initialized";
    }
   
    EmptyBuffer();
    InitiQFlash = OFF;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : InitStartiPLoop
--  Created by        : Steve Santerre
--  Last modified on  : 2018/09
--  
--  Purpose           : Start Event Reception
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/

void InitStartPLoop(void)
{
  int i,imax = 10;
  bool  noerror[10];
  float Kp1,Kp2;
  
// Initialize filling parameters
 
  for(i=0;i<imax;i++)
   {
    noerror[i] = ON;
   } 
   
   if(InitPLoop)
   {
    noerror[0] = OpenConnection();
    noerror[1] = SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_PLOOP);
    noerror[2] = iQOutRelease();
    noerror[3] = iQSetSlowFilterSize (SCALE_CHANNEL, SCALE_NUMBER,Lim((SMFilterSize-5),(SMFilterSize+5),MP.StdFilterSize));
    noerror[4] = iQSetTargetWeight (SCALE_CHANNEL, SCALE_NUMBER, TargetWeight[Scale1]*UnitIQtoADM);
   } 
    
    
   if (AOUTActive[AIO1])
    { 
     if(InitPLoop)
     {
      noerror[5] = iQPLoopSetAnalogOutput(SCALE_CHANNEL,SCALE_NUMBER,AIO1,IQ_FEEDING_ANALOG_MODULE_DAU,AOUTModul[AIO1],AOUTMode[AIO1]);
     }
     Kp1 = ((WP.MaxFeeding - WP.MinFeeding)/100.0) / (sqrt((WP.Cutoff-CutoffCorrOffset[Scale1]) - WP.BulkCutoff));
     noerror[6] = iQPLoopSetParameters  (SCALE_CHANNEL,SCALE_NUMBER,AIO1,WP.MinFeeding/100.0,WP.MaxFeeding/100.0,(WP.Cutoff-CutoffCorrOffset[Scale1])*UnitIQtoADM,Kp1);
    }
    
   if (AOUTActive[AIO2])
    { 
     if(InitPLoop)
     {
      noerror[7] = iQPLoopSetAnalogOutput(SCALE_CHANNEL,SCALE_NUMBER,AIO2,IQ_FEEDING_ANALOG_MODULE_DAU,AOUTModul[AIO2],AOUTMode[AIO2]);
     }
     
     if(MC.FeederType == FeederBSFHS) Aout2SwitchVal = WP.IntermCutoff;
     if(MC.FeederType == FeederBHS)   Aout2SwitchVal = WP.BulkCutoff+WeighPerUnitCorrOffset;
     Kp2 = ((WP.RegMaxFeeding - WP.RegMinFeeding)/100.0) / (sqrt((WP.Cutoff-CutoffCorrOffset[Scale1]) - Aout2SwitchVal));
     noerror[8] = iQPLoopSetParameters(SCALE_CHANNEL,SCALE_NUMBER,AIO2,WP.RegMinFeeding/100.0,WP.RegMaxFeeding/100.0,(WP.Cutoff-CutoffCorrOffset[Scale1])*UnitIQtoADM,Kp2);
    } 
   
   for(i=0;i<imax;i++)
   {
    if(!noerror[i])
    {
     SystemErrorCode = "150 PLOOP variables not initialized";
    }
   }
   
    EmptyBuffer();
    InitPLoop = OFF;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : InitStartGHSSmartPlus
--  Created by        : Steve Santerre
--  Last modified on  : 2019/08
--  
--  Purpose           : Start Event Reception
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/

void InitStartGHSSmartPlus(void)
{
  int i,imax = 10,type,modul,mode;
  bool  noerror[10];
  string aout_name[10];
  float SlowFlowValuesTimePct = 0.30;
    
     type        = AOUTType[AIO1];
     aout_name   = AOUTName[type];
     modul       = AOUTModul[AIO1];
     mode        = AOUTMode[AIO1];
     
// Initialize filling parameters
 
  for(i=0;i<imax;i++)
   {
    noerror[i] = ON;
   } 
   
    noerror[0] = OpenConnection();
    noerror[1] = SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_LIGHT);
    noerror[2] = SetSlowFilterSize (MP.SlowFilterSize);
    noerror[3] = SetFastFilterSize (MP.FastFilterSize);
    noerror[4] = SetTargetValue(TargetWeight[Scale1]*UnitIQtoADM);
    noerror[5] = iQLightSetSlowStatsPercentage(SCALE_CHANNEL, SCALE_NUMBER,SlowFlowValuesTimePct);
    
    
   
   InitSmartPlus = OFF;
   
   
   
   if(LearnSmartPlusParam)
   { 
    if(iQClearControlParameters (SCALE_CHANNEL, SCALE_NUMBER))
     {      
           noerror[6] = ON;
           iQFeedSettledCnt=0;
           CPSmSwitchTimeMem  = 0;
           LearniQSmartToSave = ON;
           LearnSmartPlusParam = OFF;
           SmartPlusSetDribbleCutoff = OFF;
     }   
   }                                                
   else
   {
    noerror[6] = iQLightSetControlParameters(SCALE_CHANNEL,SCALE_NUMBER,CPSmSlowAvgPointsMem,CPSmSlowItpPointsMem,CPSmSwitchTimeMem);
    SmartPlusSetDribbleCutoff = ON;
   }
     
  for(i=0;i<imax;i++)
   {
    if(!noerror[i])
    {
     SystemErrorCode = "160 GHS-Smart+ variables not initialized";
     InitSmartPlus = ON;
    }
   }
    
    EmptyBuffer();
    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CloseChannelConnection
--  Created by        : Steve Santerre
--  Last modified on  : 2015/10/27
--  
--  Purpose           : Close Channel Connection if not iQ Feed Algo
--                      
--  Value Parameters  :
--  Variable Params   : none
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CloseChannelConnection(void)
{
iQCloseConnection(SCALE_CHANNEL);
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
void FeedingStop(void)
{
//To stop iQ Feed
iQFeedingStop (SCALE_CHANNEL, SCALE_NUMBER);
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
bool StartFeeding(bool WaitSettled)
{

bool noerror;
//Start iQ Feeding
noerror = iQFeedingStart (SCALE_CHANNEL, SCALE_NUMBER, WaitSettled);   // ON => activate parameter waiting for settled
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

int     scaleno,i;
string  status[256],status_msg[5][64];
float   weight;
float   fast_slow_switch_weight;
float   slow_fill_duration;
float   fast_fill_duration;
float   filling_duration;
float   overall_duration;
float   FastCutoff_kg,SlowCutoff_kg;
float   CPSmSwitchTimeTemp;
bool    iQReadEventStatus;
bool    iQFlashLearned;
bool    iQSmartLearned;
bool    DeadTimeGetOK;
float   controlled_slow_time;
float   slow_flow_average,slow_flow_stddev;
float   fast_weight_maximum,fast_weight_minimum;

//Read Data from iQ Feed after feeding completed
 if (msgread (0) >= 0)
 {
    if(WP.FeedAlgoType != FeedGHSSmartPlus)
     {
      iQReadEventStatus = iQReadEvent (scaleno,weight,status,FastCutoff_kg,SlowCutoff_kg,slow_fill_duration,
                                     fast_fill_duration,filling_duration,overall_duration);
     }
    
    else
     {
      iQReadEventStatus = iQLightReadEvent(scaleno,weight,status,FastCutoff_kg,SlowCutoff_kg,slow_fill_duration,
                                           filling_duration,overall_duration,controlled_slow_time,fast_weight_maximum,
                                           fast_weight_minimum,slow_flow_average,slow_flow_stddev);
      
      fast_fill_duration = filling_duration - slow_fill_duration; //WP.BFTime; 
     }                                                          
       
       FastCutoff = FastCutoff_kg * UnitADMtoIQ;
       SlowCutoff = SlowCutoff_kg * UnitADMtoIQ;

                                     
  if(!emptybuffer)
   {  
    if(iQReadEventStatus)                 
    { 
     i = 0;
     iQFeedStatusFinished = OFF;
     iQFeedStatusAborted = OFF;
     iQFeedStatusSettled = OFF;
     iQFeedStatusEmergency = OFF; 
     
     
     split (status_msg[0], status, ',');
     while(status_msg[i] != "" && i<=3)
      {
      
       if(status_msg[i] == FILLING_STATUS_FINISHED) 
            iQFeedStatusFinished = ON; 
       if(status_msg[i] == FILLING_STATUS_ABORTED)
           { 
            if(!WeighmentAborted)
             {
              iQFeedStatusAborted = ON;
              if(WP.FeedAlgoType == FeediQFlash)SystemErrorCode = "121 iQ Flash weighment aborted";
              if(WP.FeedAlgoType == FeediQSmart)SystemErrorCode = "131 iQ Smart weighment aborted";
              if(WP.FeedAlgoType == FeedPLoop)  SystemErrorCode = "151 PLoop weighment aborted";
              if(WP.FeedAlgoType == FeedGHSSmartPlus) SystemErrorCode = "161 GHS Smart+ weighment aborted";
             }
           }  
      if(status_msg[i] == FILLING_STATUS_SETTLED)
            iQFeedStatusSettled = ON; 
      if(status_msg[i] == FILLING_STATUS_EMERGENCY)
            {
            iQFeedStatusEmergency = ON;
            if(WP.FeedAlgoType == FeediQFlash)SystemErrorCode = "122 iQ Flash emergency weight detected";
            if(WP.FeedAlgoType == FeediQSmart)SystemErrorCode = "132 iQ Smart emergency weight detected";
            if(WP.FeedAlgoType == FeedPLoop)  SystemErrorCode = "152 PLoop emergency weight detected";
            if(WP.FeedAlgoType == FeedGHSSmartPlus) SystemErrorCode = "161 GHS Smart+ emergency weight detected";
            }
      i++;      
      }  
      
      if(!iQFeedStatusFinished && iQFeedStatusSettled && !iQFeedStatusAborted && !iQFeedStatusEmergency)
        iQFeedStatusFinished = ON;
        
      if ((iQFeedStatusFinished && !WeighmentAborted) || WP.FeedAlgoType == FeedPLoop)
      {  
      ProdBulkDuration[Scale1]     = fast_fill_duration;
      ProdDribbleDuration[Scale1] = filling_duration - fast_fill_duration;
      }
      iQFeedDone=ON;
      
     #if defined SYSTEC_DATA_DEBUG
      writestring (0, concat (date,";",
                              time,";",
                              TargetWeight[Scale1],unit,";",
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
       if(iQFeedWaitSettled)
       {
       if(!iQFlGetControlParameters(SCALE_CHANNEL, SCALE_NUMBER, CPFlFastPointsMem,CPFlDeviationPointsMem,iQFlashLearned))
          SystemErrorCode = "128 iQ Flash could not get control parameters";
       else
        {
         if((iQFlashLearned || iQFeedSettledCnt == IQFEEDSETTLEDNBR)&& ((LearniQFlashToSave ||(SampleFreqCnt == (MP.SampleSize-1))) && !LowLevel[Scale1] && !EmptyHopper && !SlowCycleMem))
          {
           SaveiQFeedParamFlag = Execute;
           LearniQFlashToSave = OFF;
          }
        }    
       }
     }  
     
     if(WP.FeedAlgoType == FeediQSmart)
     {
       //Statistical Data Comming from Smart Feed
     iQReadEventStats (scaleno,stat_controlled_fast_time, stat_controlled_slow_time, stat_stable_fast_flow,
                           stat_stable_slow_flow, stat_fast_flow_fluctuation, stat_slow_flow_fluctuation);
      
      if(iQFeedWaitSettled)
       {
       if(!iQSmGetControlParameters(SCALE_CHANNEL,SCALE_NUMBER,CPSmFastAvgPointsMem,CPSmSlowAvgPointsMem,CPSmSlowItpPointsMem,CPSmSwitchTimeTemp,iQSmartLearned))
        SystemErrorCode = "138 iQ Smart could not get control parameters";
       else
        {
         if(CPSmSwitchTimeMem == 0) 
          CPSmSwitchTimeMem = CPSmSwitchTimeTemp;
         DeadTimeGetOK = iQSmGetDeadTime(SCALE_CHANNEL,SCALE_NUMBER,iQDeadTimeRead);
         if((iQSmartLearned || iQFeedSettledCnt == IQFEEDSETTLEDNBR) && ((LearniQSmartToSave || (SampleFreqCnt==(MP.SampleSize-1))) && !LowLevel[Scale1] && !EmptyHopper && !SlowCycleMem))
         {
         SaveiQFeedParamFlag = Execute;
         LearniQSmartToSave = OFF;
         }
        } 
       } 
     } 
     
     if(WP.FeedAlgoType == FeedGHSSmartPlus)
     {
      if(iQFeedWaitSettled)
       {
       if(!iQLightGetControlParameters(SCALE_CHANNEL,SCALE_NUMBER,CPSmSlowAvgPointsMem,CPSmSlowItpPointsMem,CPSmSwitchTimeTemp,iQSmartLearned))
        SystemErrorCode = "168 GHSSmart+ could not get control parameters";
       else
        {
         if(CPSmSwitchTimeMem == 0) 
          CPSmSwitchTimeMem = CPSmSwitchTimeTemp;
         if((iQSmartLearned || iQFeedSettledCnt >= IQFEEDSETTLEDNBR-5) && ((LearniQSmartToSave || (SampleFreqCnt==(MP.SampleSize-1))) && !LowLevel[Scale1] && !EmptyHopper && !SlowCycleMem))
         {
         SaveiQFeedParamFlag = Execute;
         LearniQSmartToSave = OFF;
         }
        } 
       } 
     }
                                                                                                                                                                  
    }
   }  
 }
}

                                                          
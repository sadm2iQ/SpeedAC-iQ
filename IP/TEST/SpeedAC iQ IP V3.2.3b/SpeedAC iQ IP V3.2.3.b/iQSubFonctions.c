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
void OpenConnection(void)
{
//To initialize Channel Connection
if (!iQOpenConnection (SCALE_CHANNEL, "127.0.0.1")) 
  SystemErrorCode = "140 iQFeeding connection not established";                  
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

result1 = iQSetEnableSignalOutput (SCALE_CHANNEL, SCALE_NUMBER, -1,OFF);
result2 = iQSmSetDigitalOutput(SCALE_CHANNEL, SCALE_NUMBER,-1,-1,0);
iQOutputEnabled = OFF;
return(result1 && result2);
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
bool StartFeeding(void)
{

bool noerror;
//Start iQ Feeding
noerror = iQFeedingStart (SCALE_CHANNEL, SCALE_NUMBER, iQFeedWaitSettled);   // true => activate parameter waiting for settled
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
bool    iQReadEventStatus;
bool    iQFlashLearned;
bool    iQSmartLearned;




//Read Data from iQ Feed after feeding completed
 if (msgread (0) >= 0)
 {
    iQReadEventStatus = iQReadEvent (scaleno,weight,status,FastCutoff,SlowCutoff,slow_fill_duration,
                                     fast_fill_duration,filling_duration,overall_duration);
                                     
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
             }
           }  
      if(status_msg[i] == FILLING_STATUS_SETTLED)
            iQFeedStatusSettled = ON; 
      if(status_msg[i] == FILLING_STATUS_EMERGENCY)
            {
            iQFeedStatusEmergency = ON;
            if(WP.FeedAlgoType == FeediQFlash)SystemErrorCode = "122 iQ Flash emergency weight detected";
            if(WP.FeedAlgoType == FeediQSmart)SystemErrorCode = "132 iQ Smart emergency weight detected";
            }
      i++;      
      }  
      
      if(!iQFeedStatusFinished && iQFeedStatusSettled && !iQFeedStatusAborted && !iQFeedStatusEmergency)
        iQFeedStatusFinished = ON;
        
      if (iQFeedStatusFinished && !WeighmentAborted)
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
       if(!iQSmGetControlParameters(SCALE_CHANNEL,SCALE_NUMBER,CPSmFastAvgPointsMem,CPSmSlowAvgPointsMem,CPSmSlowItpPointsMem,CPSmSwitchTimeMem,iQSmartLearned))
        SystemErrorCode = "138 iQ Smart could not get control parameters";
       else
        {
         if((iQSmartLearned || iQFeedSettledCnt == IQFEEDSETTLEDNBR) && ((LearniQSmartToSave || (SampleFreqCnt==(MP.SampleSize-1))) && !LowLevel[Scale1] && !EmptyHopper && !SlowCycleMem))
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

                                                          
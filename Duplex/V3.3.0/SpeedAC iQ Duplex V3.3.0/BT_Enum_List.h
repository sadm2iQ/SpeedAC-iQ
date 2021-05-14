﻿// From BT_Logic
enum    //Timers
{
T_FirstScan,
T_StabTimeLimit,
T_BulkBlankT,
T_DribbleBlankT,
T_LowLevelDebounce,
T_TopUpONTime,
T_TopUpOFFTime,
T_OutOfTolTime,
T_DischargeTime,
T_FeedDelayTime, 
T_BulkDuration, //10
T_DribbleDuration,
T_CycleDuration,
T_AccessTimeout,
T_SlowCycleTime,
T_DischDoorMaxTime,
T_CatchGateMaxTime,
T_BagDetectionTime,
T_DischReqDebouncing,
T_RefillingTimeT, 
T_BagInflationTime, //20
T_FallingTime,
T_BagRelease,
T_KnockningTime,
T_CatchGateDelay,
T_StreamRegHigh,
T_FlexOut1Off,
T_FlexOut1On,
T_FlexOut2Off, 
T_FlexOut2On, 
T_FlexOut3OnTime, //30
T_FlexOut3InitOn,
T_FlexOut3OffTime,
T_iQFeedTimeout,
T_UPMDuration,
T_FaultDisplay,
T_ActuatorON,
T_ActuatorOFF,
T_KickerCenterTime,
T_KickerActivateTime, 
T_HeartbeatON, //40
T_HeartbeatOFF,
T_ProdDataReady,
T_StabTimeLimit2,  //Scale #2
T_BulkBlankT2,
T_DribbleBlankT2,
T_LowLevelDebounce2,
T_TopUpONTime2,
T_TopUpOFFTime2,
T_OutOfTolTime2,
T_DischargeTime2, //50
T_FeedDelayTime2, 
T_BulkDuration2, 
T_DribbleDuration2,
T_CycleDuration2,
T_SlowCycleTime2,
T_DischDoorMaxTime2,
T_CatchGateMaxTime2,
T_CatchGateDelay2,
T_StreamRegHigh2,
T_iQFeedTimeout2, //60
T_FaultDisplay2,
T_ActuatorON2,
T_ActuatorOFF2,
T_VibrationPeriod,
T_VibrationPeriod2,
T_AbnormalFeed,
T_AbnormalFeed2,
T_InitAlgo,
T_InitAlgo2,
T_BSFBulkOffDelay1,
T_BSFBulkOffDelay2,
}

// Fault Message enum
enum
{
//General Faults
FltG_EmergencyStop=0,
FltG_LowAirPressure,
FltG_CatchGateNotOpen,
FltG_SystemError,
FltG_DischDoorNotClosed,
FltG_ExceededCapacity,
FltG_MotorFailure,

FltG_CatchGateNotOpen2=10, //Bit 10
FltG_DischDoorNotClosed2,
FltG_ExceededCapacity2,

//Blocking Faults 
FltB_UnderWeight=32,
FltB_OverWeight,
FltB_ExceededCapacity,

FltB_UnderWeight2=42, //Bit 10
FltB_OverWeight2,
FltB_ExceededCapacity2,

//Stopping Faults  
FltS_StabTooLong=64,
FltS_ZeroOutOfRange,
FltS_BagNotDetected,
FltS_HopperIllogicalDetection,


FltS_StabTooLong2=74, //Bit 10
FltS_ZeroOutOfRange2,


//Warning Faults  
FltW_LowBattery=96,
FltW_SlowCycle,
FltW_BulkBlankTooLong,
FltW_DribbleBlankTooLong,
FltW_SystemWarning,
FltW_HopperLowLevel,

FltW_SlowCycle2=106,  //Bit 10
FltW_BulkBlankTooLong2,
FltW_DribbleBlankTooLong2,
FltW_HopperLowLevel2,

Step_Message = 128
}

//enum for Inputs and Outputs in Relation to DBase IOdb.No
enum
{
I_EStop = 1,      //1
I_PressureSW,
I_MotorFailure,
I_LowLevelSensor1,
I_DischDoorClose1,
I_CatchGateOpen1,

I_DischReq,      //7
I_HopperEmpty,
I_HighLevelSensor,
I_LowLevelSensor2,
I_DischDoorClose2,
I_CatchGateOpen2,

I_Start,         //13
I_Stop,
I_ManDisch1,
I_EmptyBagReady,
I_ClearFaults,
I_HoldCycle,

I_BagAtKicker,   //19
I_KickerRetracted,
I_ManDisch2,
I_ResetOutofTolAlarm,
I_BatchEnd,
I_Free3,

I_ChangeWPIN1,   //25
I_ChangeWPIN2,
I_ChangeWPIN3,
I_ChangeWPIN4,
I_FlexIO_1,
I_FlexIO_2,

I_Free4,      //31
I_Free5,
I_Free6,
I_Free7,
I_Free8,
I_Free9, // = 36,

O_BulkFeed1,// = 37
O_DribbleFeed1, 
O_CatchGate1,
O_StreamRegulator1,
O_DischDoor1,
O_VibrDischDoor1,

O_BulkFeed2,// = 43
O_DribbleFeed2, 
O_CatchGate2,
O_StreamRegulator2,
O_DischDoor2,
O_VibrDischDoor2,

O_DischReady, //49
O_HopFillReq,
O_KnockHammer,
O_KickerActivate,
O_DischDoor12,
O_CleanoutCompleted1,

O_Discharge, //55
O_BagHolder,
O_InflateBag,
O_BagRelease,
O_DischDoor22,
O_CleanoutCompleted2,

O_Fault, //61
O_LowLevel1,
O_OutOfTolerance1,
O_OverWeightAlarm1,
O_UnderWeightAlarm1,
O_ExternalBagCounter,

O_CycleInProgress, //67
O_LowLevel2,
O_OutOfTolerance2,
O_OverWeightAlarm2,
O_UnderWeightAlarm2,
O_CycleInHold,


O_ExtendActuator1, //73
O_RetractActuator1,
O_WPNumbOUT1,
O_WPNumbOUT2,
O_WPNumbOUT3,
O_WPNumbOUT4,

O_ExtendActuator2, //79
O_RetractActuator2,
O_FlexIO_1,
O_FlexIO_2,
O_FlexIO_3,
O_BatchEnded, // =84


IO_Max_Array
}



enum  //Steps names for any sequence
{
stp_INIT=1,
stp_ZERO,
stp_FEED,
stp_SAMPLE,
stp_TOPUP,        //5
stp_OUTOFTOL,
stp_RDYTODISCH,
stp_DISCHARGING,
stp_OPENDOORS,
stp_CLOSEDOORS,   //10
stp_DETECTBAG,
stp_INFLATEBAG,
stp_SPOUTOKTODISCH,
stp_FALLINGTIME,
stp_FEEDSTD,       //15
stp_FEEDSMART,
stp_FEEDFLASH,
stp_FEEDDONE,
stp_FSBulkBlank,
stp_FSBulkSetPoint,    //20
stp_FSDribbleBlank,
stp_FSDribbleSetPoint,
stp_FSDone,
stp_FSHold,
stp_DONE,             //25
stp_ManualDisch1,
stp_ManualDisch2,
stp_ManualSpout,
stp_ManualOkToDisch,
stp_CENTERBAG,        //30
stp_KICKBAG
}



enum  //Algorithm Types
{
FeedStd,
FeediQSmart,
FeediQFlash,
FeediQSim
}

enum //Hopper State Images
{
HopperFill,
HopperEmpty
}

enum //Start-Pause btn states
{
StartBtn,
PauseBtn
}

enum //Auto Tune Button Images
{
AutoTuneOFF,
AutoTuneON
}

enum //Check all weighs Images
{
ReleaseWeight,
CheckAllWeight
}

enum //Discharge Images
{
DischPanOff,
DischPanOn,
DischMan,
DischUnder,
DischOver,
DischPan,
}

enum //Feeder Type
  {
  FeederNone=0,
  FeederG=1,
  FeederGHS,
  FeederB,
  FeederGV,
  FeederV,
  FeederBHS,
  FeederBSF,
  FeederBSFHS,
  FeederSS,
  FeederDS,
  FeederLast
  }

enum
{
StreamRegLow,
StreamRegHigh,
StreamRegAutoRaiseAtEnd,
StreamRegAutoRaiseAtRun
}

enum
{
ByWeight,
ByTime
}
enum
{
DDLarge=0,
DDSmall,
DDMedium,
}
enum
{
HOLD_CYCLE,
END_CYCLE,
DRIBBLE_CYCLE
}

enum
{
Scale1Only,
Scale2Only,
Scale1And2
}

enum
{
NotUsed = 99999
}

enum
{
local = 1,
remote
}
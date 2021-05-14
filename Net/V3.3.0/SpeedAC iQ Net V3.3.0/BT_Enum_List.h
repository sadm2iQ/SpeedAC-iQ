﻿// From BT_Logic
enum    //Timers
{
T_FirstScan,
T_StabTimeLimit,
T_BulkBlankT,
T_IntermBlankT,
T_DribbleBlankT,
T_LowLevelDebounce,
T_TopUpONTime,
T_TopUpOFFTime,
T_OutOfTolTime,
T_DischargeTime,
T_FeedDelayTime, //10
T_BulkDuration, 
T_DribbleDuration,
T_CycleDuration,
T_AccessTimeout,
T_SlowCycleTime,
T_DischDoorMaxTime,
T_CatchGateMaxTime,
T_BagDetectionTime,
T_DischReqDebouncing,
T_RefillingTimeT, //20
T_BagInflationTime,
T_FallingTime,
T_BagRelease,
T_KnockningTime,
T_CatchGateDelay,
T_StreamRegHigh,
T_FlexOut1Off,
T_FlexOut1On,
T_FlexOut2Off, 
T_FlexOut2On, //30
T_FlexOut3OnTime,
T_FlexOut3InitOn,
T_FlexOut3OffTime,
T_iQFeedTimeout,
T_UPMDuration,
T_FaultDisplay,
T_ActuatorON,
T_ActuatorOFF,
T_KickerCenterTime,
T_KickerActivateTime, //40
T_HeartbeatON,
T_HeartbeatOFF,
T_ProdDataReady,
T_VibrationPeriod,
T_AbnormalFeed,
T_InitAlgo,
T_DelayEthernetSend, //SADM2
T_1Sec,
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

//Blocking Faults 
FltB_UnderWeight=32,
FltB_OverWeight,
FltB_DischargeTooLong,
FltB_ExceededCapacity,

//Stopping Faults  
FltS_StabTooLong=64,
FltS_ZeroOutOfRange,
FltS_BagNotDetected,
FltS_HopperIllogicalDetection,


//Warning Faults  
FltW_LowBattery=96,
FltW_SlowCycle,
FltW_BulkBlankTooLong,
FltW_DribbleBlankTooLong,
FltW_SystemWarning,
FltW_HopperLowLevel,

Step_Message = 128
}

//enum for Inputs and Outputs in Relation to DBase IOdb.No
enum
{
I_EStop = 1,
I_DischReq,
I_DischDoorClose,
I_CatchGateOpen,
I_HighLevelSensor,
I_Stop,
I_HopperEmpty,
I_PressureSW,
I_MotorFailure,
I_LowLevelSensor,
I_Start,
I_ManDisch,
I_DribbleFeedOnly,
I_OK4BulkFeed,
I_OK4IntermFeed,
I_OK4DribbleFeed,
I_EmptyBagReady,
I_ClearFaults,
I_BagAtKicker,
I_KickerRetracted,
I_BatchEnd,
I_ResetOutofTolAlarm,
I_Free2,
I_Free3,
I_ChangeWPIN1,
I_ChangeWPIN2,
I_ChangeWPIN3,
I_ChangeWPIN4,
I_FlexIO_1,
I_FlexIO_2,
I_HoldCycle,
I_Free4,
I_Free5,
I_Free6,
I_Free7,
I_Free8,// = 36,
O_Fault, // = 37,
O_CatchGate,
O_VibrDischDoor,
O_IntermFeed,
O_Discharge,
O_StreamRegulator,
O_DischDoor,
O_BulkFeed,
O_DribbleFeed, // = 46,
O_HopFillReq,
O_DischReady,
O_DischDoor2,
O_OutOfTolerance,
O_OverWeightAlarm,
O_UnderWeightAlarm,
O_CycleInProgress,
O_ExternalBagCounter,
O_CycleInHold,
O_CatchGateInterm,
O_BagHolder,
O_InflateBag,
O_BagRelease,
O_KnockHammer,
O_KickerActivate,
O_BatchEnded,
O_ExtendActuator,
O_RetractActuator,
O_FlexIO_1,
O_FlexIO_2,
O_FlexIO_3,
O_WPNumbOUT1,
O_WPNumbOUT2,
O_WPNumbOUT3,
O_WPNumbOUT4,
O_LowLevel,
O_CleanoutCompleted,// =72
IO_Max_Array
}



enum  //Steps names for any sequence
{
stp_INIT=1,
stp_ZERO,
stp_FEED,
stp_SAMPLE,
stp_TOPUP,
stp_OUTOFTOL,
stp_RDYTODISCH,
stp_DISCHARGING,
stp_OPENDOORS,
stp_CLOSEDOORS,         //10
stp_DETECTBAG,
stp_INFLATEBAG,
stp_SPOUTOKTODISCH,
stp_FALLINGTIME,
stp_FEEDSTD,
stp_FEEDSMART,
stp_FEEDFLASH,
stp_FEEDPLOOP,
stp_FEEDGHSSMARTPLUS,
stp_FEEDDONE,          //20
stp_FSBulkBlank,  
stp_FSBulkSetPoint,
stp_FSInterBlank,
stp_FSInterSetPoint,
stp_FSDribbleBlank,
stp_FSDribbleSetPoint,
stp_FSDone,
stp_FSHold,
stp_DONE,
stp_ManualDisch,      //30
stp_ManualSpout, 
stp_ManualOkToDisch, 
stp_CENTERBAG,
stp_KICKBAG
}



enum  //Algorithm Types
{
FeedStd,
FeediQSmart,
FeediQFlash,
FeediQSim,
FeedPLoop,
FeedGHSSmartPlus,
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
StreamRegAutoRaiseAtRun,
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
NotUsed = 99999
}

enum
{
local = 1,
remote
}
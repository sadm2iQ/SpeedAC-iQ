// From BT_Logic
enum    //Timers
{
T_FirstScan,
T_StabTimeLimit,
T_CycleDuration,
T_AccessTimeout,
T_SlowCycleTime,
T_FlexOut1Off,
T_FlexOut1On,
T_FlexOut2Off, 
T_FlexOut2On,
T_FlexOut3OnTime,
T_FlexOut3InitOn, //10
T_FlexOut3OffTime,
T_UPMDuration,
T_FaultDisplay,
T_HeartbeatON,
T_HeartbeatOFF,
T_ProdDataReady,
T_InitAlgo,
T_ChangeWP_PWM,
T_OutWP_PWM,
T_PCEntryBlocked, //20
T_PCExitBlocked,
T_RejectUnitTime,
T_UnitChecked,
T_EvalTime,
T_RejectUnitDelay,
T_Simul,
T_AutoRefresh,
T_ATRecDisplay,
T_RdyToRcv,
}

// Fault Message enum
enum
{
//General Faults
FltG_EmergencyStop=0,
FltG_SystemError,
FltG_ExceededCapacity,
FltG_MotorFailure,

//Blocking Faults
FltB_BothPCsBlocked=32,
FltB_ExceededCapacity,
FltB_EntryPCBlocked,
FltB_ExitPCBlocked,

//Stopping Faults  
FltS_StabTooLong=64,
FltS_ZeroOutOfRange,
FltS_TransportError,
FltS_SpeedCtrlError,

//Warning Faults  
FltW_SystemWarning=96,

Step_Message = 128
}

//enum for Inputs and Outputs in Relation to DBase IOdb.No
enum
{
/* INPUTS*/
I_PCEntry = 1,
I_PCExit,
I_DownstreamReady,
I_Start,
I_Free5,
I_Free6,
I_EStop,
I_MotorFailure,
I_ClearFaults,
I_Stop,
I_Free11,
I_Free12,
I_ChangeWPIN1,  //=13
I_ChangeWPIN2,
I_ChangeWPIN3,
I_ChangeWPIN4,
I_Free17,
I_Free18,
I_ChangeWP_PWM,
I_FlexIO_1,
I_FlexIO_2,
I_Free22,
I_Free23,
I_Free24,// = 24
/* OUTPUTS*/
O_StartCnv, // = 25
O_RdyToRcv,
O_Fault, 
O_ZeroReq,
O_RejectUnit,
O_UnitChecked,
O_TolOverReject,
O_TolOverAccept,
O_TolGood,
O_TolUnderAccept,
O_TolUnderReject,
O_Free36,
O_WPNumbOUT1, //37
O_WPNumbOUT2,
O_WPNumbOUT3,
O_WPNumbOUT4,
O_Free41,
O_Free42,
O_WPNumb_PWM,
O_FlexIO_1,
O_FlexIO_2,
O_FlexIO_3,
O_Free47,
O_Free48, // =48
IO_Max_Array
}



enum  //Steps names for any sequence
{
stp_INIT=1,
stp_STANDBY,
stp_RUN,
stp_UNITENTRY,
stp_EVALUATION,
stp_WAITRESULT,
stp_EXITUNIT,
stp_AT_ZERORECORD,
stp_AT_ZEROANALYSE,
stp_AT_CHECKRECORD,
stp_AT_CHECKANALYSE,
stp_AT_SETPARAM,
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

enum
{
TolURej=1,
TolUAcc,
TolGood,
TolOAcc,
TolORej,
TolInvalid,
}

enum
{
RejectBoth=0,
RejectUnderOnly,
RejectOverOnly,
}

enum
{
local = 1,
remote
}
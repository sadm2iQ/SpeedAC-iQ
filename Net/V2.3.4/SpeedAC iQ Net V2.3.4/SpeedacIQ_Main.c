 /* ***************************************************************** */
/* ****************************************************************** */
/* *                                                                * */
/* *                                                                * */
/* *                                                                * */
/* *                        RTC-Program                             * */
/* *                                                                * */
/* *                                                                * */
/* *                                                                * */
/* ****************************************************************** */
/* ****************************************************************** */
/*

Important information for programmers:

1. Display commands to be used only in the main task. Display drawing from 
   the background task isn´t allowed !
2. If the main/display task uses display commands in a for(;;) or while loop
   it´s necessary to use a delay() with 100ms or 200ms (it depends on the application).
   Furthermore, the display should be updated only when something has changed, 
   to reduce the CPU load.
3. All page layouts in the file "qtfunctions.c" must be inialized once 
   after the ITx000ET is started up. Then, the pages could be selected
   with the command selectpage()
4. The ITx000ET is event based ! therefore should be used no blocking functions like "readkey()". 
   - Drop all currently waiting events if a new page layout is selected with function dropevents(). 
     This might be useful if the screen page is changed and all events caused 
     by the previous page shall be dropped.
   - The function "readkey" must be replaced with the function "readevent()".
   - The function "keypressed" must be replaced with the function "eventreceived()".
*/   
   
   
/*****************************************************************************/

/*-------------------------------------------------------------------------  
-- Check Firmware versions valid before starting application   
--------------------------------------------------------------------------*/
#define MIN_INTERPRETER_VERSION(m,n,p)\
      (__RTC_MAJOR_VERSION__ >m ||\
      (__RTC_MAJOR_VERSION__ ==m && __RTC_MINOR_VERSION__ >n) ||\
      (__RTC_MAJOR_VERSION__ ==m && __RTC_MINOR_VERSION__ ==n && __RTC_PATCH_LEVEL__ >=p))


#if MIN_INTERPRETER_VERSION (6, 0, 18)
/**************************************************************************** 
  Variables
*****************************************************************************/


//#define BETA_RELEASE
//#define LOGIN_DEBUG
//#define LAYOUT_TEST
//#define STRING2LONGTEST
//#define BYPASS_SERVICEMODE_RESTART
//#define IQ_HIDDEN_FUNCTIONS_DEBUG
//#define FIFO_PERSISTENT
//#define SAVE_DBS_IN_SIMUL

#include "SpeedACiQ_Net_V2.3.4.h"

#define OFF 0
#define ON 1
#define LAST 2

#define Done 0
#define Execute 1

#define AIO1   0
#define AIO2   1
#define AIO3   2
#define AIO4   3

#define BULKADDRESS 7

// for use with built-in date[xx] function
#define YY   13
#define MT   12
#define DD   11
#define HH   14
#define MM   15
#define SS   16
#define DATE 17
#define TIME 23

#define SCALECFG1 0
#define SCALECFG2 1
#define SCALECFG3 2
#define SCALECFG4 3

#define FB_OFF "Off"
#define FB_ETX "ETHERNET-IP"
#define FB_PNX "PROFINET"
#define FB_PBX "Profibus DP"
#define FB_MBX "Modbus TCP"

#define CRLF   "\r\n"
#define LF     "\n"
#define HT     "\t"
#define tab    7


#define FltArrayMax   100
#define FltStringLen  255
#define FltSpacing      5
#define FltDispLines   10
#define WP_NAME_LENGTH 24
#define MAX_WP        100
#define WPdbSIZE      101 //MAX_WP+1
#define MAX_MC          2
#define MAX_MP          2
#define MAX_LANG       18
#define MAX_IO         72
#define IO_ARRAY       73
#define IO_IN_MIN      1
#define IO_IN_MAX      36
#define IO_OUT_MIN     37
#define IO_OUT_MAX     72
#define MAX_FLEXIO      3
#define MAX_DB          5
#define T_ARRAY        50
#define MAXUSERS        3
#define NOSELECTION    -1
#define MAX_LOG_FILES  25
#define InvalidNbr     100

#ifndef SCALE_CHANNEL
  #define SCALE_CHANNEL  10 
#endif  

#ifndef SCALE_NUMBER
  #define SCALE_NUMBER   1 
#endif

#define IQ_FEEDING_ALGORITHM_NONE     ""

#include "BT_DBases.h"
#include "Enum_List.h"

//------------------------------------------\\
//--                                      --\\
//--        STRUC DECLARATIONS            --\\
//------------------------------------------\\

//------------------\\
struct WeighProgram
//------------------\\
{
      int       No;                 
      string    Name[WP_NAME_LENGTH];
      decimal   NominalWeight%6.2;
      decimal   Overfill%6.2;          
      decimal   Cutoff%6.2;
      decimal   BulkCutoff%6.2;
      decimal   DFTime%5.2;
      decimal   CatchGateDelay%5.2;      
      decimal   UnderWeight%6.2;
      decimal   OverWeight%6.2;
      decimal   IntermCutoff%6.2;
      decimal   DischargeWeight%6.2;
      decimal   DischargeTime%5.2;
      decimal   FallingTime%5.2;
      decimal   MinFeeding%6.2;        //%
      decimal   MaxFeeding%6.2;        //%
      decimal   RegMinFeeding%6.2;     //%
      decimal   RegMaxFeeding%6.2;     //%
      int       StreamRegConfig;       //enum list Low-High-Auto
      decimal   ActuatorPos%6.2;     //% 
      decimal   WeighmentsPerUnit%5.0; 
      decimal   FeedDelayTime%5.2;
      bool      VibratoryDischDoors;   //enum list ON-OFF
      bool      ZeroingOpen;           //enum list Door Open-Door Close
      int       SlowCycleEnd;          //enum list Dribble Feed-Hold Cycle-Cycle End
      int       EnabledScale;          //enum list 1Only-2Only-1And2     
      decimal   TopUpOFFTime%5.2;
      decimal   TopUpONTime%5.2;
      decimal   KnockningTime%5.2;
      decimal   BagInflationTime%5.2;
      int       FeedAlgoType;          //enum list Standard-iQSMARTFeed-iQFLASHFeed
      string    Unit[4];                  //enum list kg-lb-oz
      decimal   FlexSP1%6.2;
      decimal   FlexSP2%6.2;
      decimal   FlexT1%5.2;
      decimal   FlexT2%5.2;
      bool      CountAll;
      decimal   ProdUnderWeightCnt_1%10.0;
      decimal   ProdUnderWeightCnt_2%10.0;
      decimal   ProdOverWeightCnt_1%10.0;
      decimal   ProdOverWeightCnt_2%10.0;
      decimal   ProdTotalUnitsCnt_1%10.0;
      decimal   ProdTotalUnitsCnt_2%10.0;
      double    ProdTotalWeight_1;
      double    ProdTotalWeight_2;
      int       SlowFillFactor;
      string    CPSmFastAvgPoints[128];
      string    CPSmSlowAvgPoints[128];
      string    CPSmSlowItpPoints[512];
      float     CPSmSwitchTime;
      string    CPFlFastPoints[128];
      string    CPFlDeviationPoints[256];
      decimal   KickerCenterTime%4.2;
      decimal   KickerActivateTime%4.2;
      bool      TuneiQFeed;
      decimal   FlexCounter%6.0;
      decimal   BFTime%5.2;
      bool      BulkMode;
      decimal   VibrationAmplitude%4.2;
      decimal   VibrationPeriod%4.2;
      int       DischDoorMode;
}
WeighProgram WP;
 
//------------------\\
struct MachineConfig
//------------------\\
{
      int     No;                     
      string  Name[24];      
      decimal BulkBlankT%4.2;
      decimal DribBlankT%4.2;
      decimal LowLevelDebounceT%4.2;
      decimal RefillingTimeT%5.2;        
      int     NumberOfWP;
      bool    OIML;                       //enum list yes-no   
      int     FeederType;                 //enum list all feeders
      int     NumberOfScale;
      int     CFGBagHolder;               //enum list NO-S4-Bird Beak
      int     Language1;                  
      string  Lang1Text[24];                  
      int     Language2;                  
      string  Lang2Text[24];
      int     Language3;                  
      string  Lang3Text[24];
      int     PortCOM2Cfg;    
      int     PortUSBCfg;
      bool    AutoSaveCorrection;         //enum list yes-no
      decimal DischReqDebouncing%4.2;
      int     PortETHCfg;
      string  PrinterIP[15];              //IP address of printer xxx.xxx.xxx.xxx
      bool    DischOnDoorSensor;          //enum list yes-no
      bool    DribbleOutOnInBulk;         //enum list ON-OFF
      int     PasswordOP;
      int     PasswordSUP;
      int     PasswordPT;
      int     LogoutOP;
      int     LogoutSUP;
      int     LogoutPT;
      string  SerialNbr[24];
      string  PlantLineName[24];
      string  CustomerName[24];
      string  CustomerLocation[24];      
      string  SupportPhoneNbr[24];
      string  SupportFaxNbr[24];
      string  SupportEmail[24];
      string  PartsPhoneNbr[24];
      string  PartsFaxNbr[24];
      string  PartsEmail[24];
      string  iQVersion[30];
      int     TrialDays;
      bool      ActuatorPosInvert;
      decimal   ActuatorExtendLimit%2.0;
}
MachineConfig MC;


//----------------------\\
struct MachineParameters
//----------------------\\
{
      int     No;                  
      string  Name[24];    
      int     SampleFreq%7.0;
      int     SampleSize%7.0;
      decimal CutoffCorr%6.2;
      decimal DFWeightCorr%3.1;
      decimal StabTimeLimit%5.2;
      decimal SlowCycleTime%5.2;
      decimal DischDoorMaxTime%5.2;
      decimal FlexCounter%6.0;
      decimal CatchGateMaxTime%5.2;
      decimal OutOfTolTime%7.2;
      decimal BagDetectionTime%5.2;
      int     ZeroFreq%7.0;
      bool    CorrOnAverage;       //enum list yes-no
      int     CutoffCorrLimit%3.0;
      decimal ZeroLimit%3.1;      //%
      bool    AutoZeroOff;           //enum list yes-no
      int     SlowFilterSize;
      int     FastFilterSize;
      decimal FlexSP1%6.2;
      decimal FlexSP2%6.2;
      decimal FlexT1%5.2;
      decimal FlexT2%5.2;
      int     FlashFilterSize;
      int     ScreenSaverTime;
      int     StdFilterSize;
      decimal SmartStabWindow%3.1;
}
MachineParameters MP;

// Production Data
struct BatchStruct
{
string  Name[24];
string  Details[48];
decimal TotalWeight%10.2;
decimal MinAccepted%6.2;
decimal MaxAccepted%6.2;
decimal Residue%6.2;
decimal StdDev%6.4;
decimal Avg%6.2;
int     UnitsAccepted%6.0;
int     UnitsDone%6.0;
int     Count;
int     UnderWeightCnt%6.0;
int     OverWeightCnt%6.0;
int     Preset%6.0;
bool    CountAll;
}
BatchStruct Batch;


struct FeederSt
{
string  Name[10];
int     Type;
int     ListNbr;
int     ListItem;
bool    Enable;
int     NbrOf1stLearn;
bool    EnableOnAllLearning;
bool    SuspendLearn_InitialImpact;
}
FeederSt Feeder[15];

struct DB_broken
{
bool IO;
bool WPs;
bool MPs;
bool MCs;
bool Flex;
}
DB_broken DbDamaged;

//*******************************\\
// ##### FLASH declaration ##### \\
//*******************************\\

flash string  RegistrationKey[14];
flash int     Access_PW[3], Access_Timeout[3];
flash MachineParameters Default_MP;
flash MachineConfig     Default_MC;

//*****************************\\
// ##### NOV declaration ##### \\
//*****************************\\
nov int     MemRecipe,MemLanguage, MemLanguage_Cnt;


nov int     Fault_Pointer;
nov string  FaultMessage[FltArrayMax][FltStringLen], FaultMsgTime[FltArrayMax][FltStringLen];
nov bool    FaultClrMsg[FltArrayMax];

//Production Report & Auto Page Related Data
nov double  SumWeightNOV[2],AvgWeightNOV[2],SqareSumWeightNOV[2],StdDevNOV[2];
nov string  SqareSumWeightStringNOV[2][256],SumWeightStringNOV[2][256];
nov int     NbrCheckedNOV[2];
nov decimal ProdUnderWeightCntNOV%10.0[2],ProdOverWeightCntNOV%10.0[2],ProdAcceptUnitCntNOV%10.0[2],ProdTotalUnitsCntNOV%10.0[2];
nov decimal ProdStdDevNOV%6.4[2],ProdAvgWeightNOV%6.2[2];
nov double  ProdTotalWeightNOV[2];
nov decimal ProdLastCheckedNOV%7.3[2], ProdLastWeightNOV%7.3[2];

//LifeTime Production Data
nov decimal ProdTotalWeighmentsLTNOV%10.0[2],ProdTotalUnitsLTNOV%10.0[2];
nov double  ProdTotalWeightLTNOV[2];

//Print options
nov string  USBFileNameMem[64],SHAREDFileNameMem[64]; 

nov decimal   MinFeedingMemNOV%6.2,MaxFeedingMemNOV%6.2,TargetWeightMemNOV%6.2[2];
nov int       SlowFilterSizeMemNOV,FastFilterSizeMemNOV,FlashFilterSizeMemNOV,StdFilterSizeMemNOV,StreamRegConfigMemNOV;
nov float     iQFlSwitchWeightMemNOV,iQFlReduceOutputMemNOV,iQFlControlTimeMemNOV,req_slow_fill_timeMemNOV;
nov int       RecipeMemNOV,FeedAlgoTypeMemNOV;

nov BatchStruct  BatchNov[101];
nov decimal      WeighPerUnitAccNOV%5.0;
nov bool         WeighPerUnitDoneNOV,WeighmentInPanNOV;
nov float        WeighPerUnitCorrOffsetNOV,WeighPerUnitSumNOV;
nov bool         LowLevelManReset;
nov int          DateNbrMemNOV,TrialDaysCntNOV;
//************************************\\
// ##### End of NOV declaration ##### \\
//************************************\\

//Language Section
#define PragmaLanguages   "English,0,[GB,US,CA];Arabic,0,[GB,US,CA];Chinese,0,[GB,US,CA];"\
                          "Czech,0,[GB,US,CA];Danish,0,[GB,US,CA];Dutch,0,[GB,US,CA];"\
                          "French,0,FR;German,0,DE;Hungarian,0,ES;Italian,0,[GB,US,CA];"\
                          "Polish,0,[GB,US,CA];Portuguese,0,[GB,US,CA];Romanian,0,[GB,US,CA];Russian,0,[GB,US,CA];"\
                          "Slovak,0,[GB,US,CA];Spanish,0,ES;Thai,0,[GB,US,CA];Turkish,0,[GB,US,CA];"
#pragma (languages, PragmaLanguages);
string PRAGMALanguage[MAX_LANG][24]; bool LangTranslated[MAX_LANG];

//Disable waiting for scale on startup - Yellow Screen
#pragma (wait_for_scale, "0");

//Production Report & Auto Page Related Data
double  SumWeight[2],AvgWeight[2],SqareSumWeight[2],StdDev[2];
string  SqareSumWeightString[2][256],SumWeightString[2][256];
int     NbrChecked[2];
decimal ProdUnderWeightCnt%10.0[2],ProdOverWeightCnt%10.0[2],ProdAcceptUnitCnt%10.0[2],ProdTotalUnitsCnt%10.0[2];
decimal ProdStdDev%6.4[2],ProdAvgWeight%6.2[2];
double  ProdTotalWeight[2];
decimal ProdLastChecked%7.3[2], ProdLastWeight%7.3[2];

//LifeTime Production Data
decimal ProdTotalWeighmentsLT%10.0[2],ProdTotalUnitsLT%10.0[2];
double  ProdTotalWeightLT[2];

//Production Report & Auto Page Related Data
float        CheckedWeight[2], CorrWeight[2];
bool         ProdUnderWeightFlag[2],ProdOverWeightFlag[2],ProdDataReady, ProdDataReadyPLC;

decimal      ProdBulkDuration%6.2[2], ProdDribbleDuration%6.2[2],ProdCycleDuration%6.2[2], ProdCycleUnitsPerMin%6.2[2];
float        FastCutoff,SlowCutoff;
decimal      WeighPerUnitAcc%5.0;
bool         WeighPerUnitDone,WeighPerUnitCorrUsed,WeighmentInPan;
bool         TopUp;
float        WeighPerUnitCorrOffset,WeighPerUnitSum;
bool         WeighPerUnitSaveFlag;
string       ProdLastSampled[2][24], ProdLastTolerance[2][4];

string       MasterPassword[4],MasterPasswordTemp[4];
bool         ChangeSMStateFlag;
bool         SMEntered,SMEnteredMEM;
int          ServiceModeState,CurrentLevelMem;
int          SMFilterSize;
bool         InitDone,ContinueUnitFlag,DischargedCall;
bool         LOTHB_main,FTHB_main,BypassTasksMonitor;

bool         fscan,AccessOK; // First scan indicator
bool         FirstScanBT,FirstScanCheckLearn;
bool         Refresh_BTInit,VarInitOffFlag,OutResetFlag;
bool         ServiceModeEntered, BypassSMRestart,Simul;
bool         StartHMI, StopHMI, OffHMI, DischargeHMI, HopperHMI, ResetDataHMI,ResetBatchHMI, ResetLifetimeDataHMI, CheckWeightHMI, AutoTuneHMI, AutoMode; 

string       OldMsg[255], StepMsg[255];
string       pagetext[256], BackgroundColor[8];
string       DatePrefix[4];

string       SMFile[25]= "shared/ServiceData.txt";
int          PBZeroPlus1,PBZeroPlus2;

int          mode_step, mode_step_MEM, Fault_Status, Fault_Status_MEM, Hopper_State, AutoTune_State, AutoTune_StateMEM, 
             Discharge_State, CheckWeight_State, CheckWeight_StateMem, Language_Cnt, ToggleBT_Cnt,NumberOfWPMem, Lang_No_Mem;
int          MemRecipeIO,RecipeFromInputs;
bool         LoadWPFromInputsFlag;             
             
int          PRIORITY_MDisplay, High_Msg_MDisplay,Fault_NoOut,Fault_NoOutStp,Fault_NoOutFault,Fault_NoOutput;
string       Msg_MDisplay[255], StepMsg_MDisplay[255], MessageOut[255],Fault_TxtOutput[255],MessageOutStp[255],MessageOutFault[255];
bool         OffRequest, Permission;
bool         FaultLightSetFlag, Message_DisplayFlag, CurModeSetFlag,HopperStateFlag,AutoTuneStateFlag, DischargeStateFlag, FaultResetFlag, 
             RefreshAutoScreenFlag, RefreshStatDataPopupFlag, RefreshReportScreenFlag, RefreshBatchScreenFlag, FaultHandlerFlag, Clear_ButtonControlRefreshedFlag, 
             RefreshFaultScreenFlag, Reset_FlexIOFlag, FlexIO_SetTPresetsFlag, SaveWPFlag,PreSave_DataNoResetFlag,CreateWPNameListFlag,CopyLearnToNovFlag,
             RefreshWeighingDataPopupFlag[2],ResetWeighingDataPopupFlag;
bool         ActiveRecipeAllowed;             
int          RefreshWPScreen_No,RefreshMPScreen_No,RefreshMCScreen_No;              
string       wpNameList[101][24];              
             
//DORJ2 Added vars
int          LangValue, scrn_index, Controller, Access_Level[3];
int          Access_MCPage3, Access_MPPage3;

//Managing learning of iQ Algorithms
decimal   MinFeedingMem%6.2,MaxFeedingMem%6.2,TargetWeightMem%6.2[2];
decimal   NominalWeightMem%6.2,OverfillMem%6.2,ActuatorPosMem%6.2;
int       SlowFilterSizeMem,FastFilterSizeMem,FlashFilterSizeMem,StdFilterSizeMem,StreamRegConfigMem;
float     iQFlSwitchWeightMem,iQFlReduceOutputMem,iQFlControlTimeMem,req_slow_fill_timeMem,iQDeadTimeRead;
int       RecipeMem,FeedAlgoTypeMem;
bool      RecipeButton,GotoPageButton[11];
bool      FirstScan;
bool      VibrationEnabled;
decimal   BulkCO%6.2;
float Open2ndDoorLastPart = 0.4;

int scanLOTBegin,ScanLOTInterval,scanLOTLast,scanLOT;
int scanFTBegin,ScanFTInterval,scanFTLast;

/*******************************************************************/
/*#################################################################*/
/*###            PLC Com Test Variables declaration             ###*/
/*#################################################################*/
/*******************************************************************/
///* Scan Time Tests */
//int ScanTimeStart,ScanTimeEnd,ScanTime_ms,ScanTimeTotal,ScanTimeMax,ScanTime_msMax, ScanTime_msMin = 100;
//float ScanTimeOffset,scanavg;
//int scan[20],scanmem[20],scanval[100],i,ScanTime_msMaxMem,scancnt,scansum,scanprev;

// Move to Global variables in iQ Project
int return_string[25];
float return_value[32];

int OUT_Command, OUT_Parameter, OUT_Value_DoubleWord[64], OUT_SeqMaster, OUT_SeqModeManager, OUT_FaultGen
    OUT_FaultBlock, OUT_FaultStopping, OUT_FaultWarn, OUT_LiveWeight_MSB, OUT_LiveWeight_LSB;
int OUT_dp,OUT_ScaleStatus, OUT_Scale1_WP,OUT_WeightUnit;
int OUT_LiveWeight_MSB_SpeedTest, OUT_LiveWeight_LSB_SpeedTest;

int IN_Command, IN_Parameter,IN_Handshake;
int IN_CommandMem,IN_ParameterMem;
float IN_Value,IN_ValueMem;
bool  OUT_Handshake;


/*******************************************************************/
/*#################################################################*/
/*###            PLC Com Variables END                          ###*/
/*#################################################################*/
/*******************************************************************/

/*******************************************************************/
/*#################################################################*/
/*###                 Print & Data Collector                    ###*/
/*#################################################################*/
/*******************************************************************/

int taskid_print, FullDate, SecondModulo, SecondMem, MinuteMem, 
    Cur_Date_Int,
    UnitRecCount, PrtPort;
bool PrintRequest, RefreshProdRepText, RefreshBatchRepText,
     DeleteLogBypass;
string LogFiles[MAX_LOG_FILES][40], FormFeed[2] = "\012",
       Current_Date[8], Current_Time[8];
string FiFoUnitRecBuffer[1024], FiFoContOutBuffer[1024], FileName[64], Standard_Date[40],FileName_Date[40], Standard_Time[40];
int    FiFoUnitRecLen, FiFoContOutLen,CurLogFiles, err;       
bool WriteUSBStick = false,Synchro_Test,TestFifo;
string FIFOStringTempo[1023] PrtPortPara[20],TicketInfo[256];        
/*******************************************************************/
/*#################################################################*/
/*###         Print & Data Collector Variables END              ###*/
/*#################################################################*/
/*******************************************************************/

#define MaxScales 4 
int          ScaleDriver_No[MaxScales], ActiveScales, Scale_No = -1;
string       ScaleDriver[MaxScales][32], ScaleModul[MaxScales][32], Detail[32];
string       iQSimFeedProg[256],iQSimDischProg[256],iQFeedAlgorithmName[24];


// WP Management

int          WP_ActiveWP_No, WP_Delete_No, WP_Rename_No, WP_CopySrce_No, WP_CopyDest_No;
string       WP_Rename_String[WP_NAME_LENGTH], WP_CopySrce_String[WP_NAME_LENGTH], WP_CopyDest_String[WP_NAME_LENGTH], WP_Delete_String[WP_NAME_LENGTH];


int          Current_Screen, CurScreenMEM, ForceScreen_ScrnNo, ForceScreen_DisplaySize, WeightDisplaySize;
bool         ForceScreen_Req, iQStatData_Popup, iQStatData_PopupMEM,WeighingData_Popup,WeighingData_PopupMEM;
string       HiResColor[20],MessageText[100],MessageColor[20];

#define BTN_LENGTH 36
#define BTN_NUMB 10
string       tmpBTN1[BTN_LENGTH], tmpBTN2[BTN_LENGTH], tmpBTN3[BTN_LENGTH], tmpBTN4[BTN_LENGTH], tmpBTN5[BTN_LENGTH];
string       tmpBTN6[BTN_LENGTH], tmpBTN7[BTN_LENGTH], tmpBTN8[BTN_LENGTH], tmpBTN9[BTN_LENGTH], tmpBTN10[BTN_LENGTH];
string       tmpBTN[BTN_NUMB][BTN_LENGTH], BTN[BTN_NUMB][BTN_LENGTH];
string       CurrentUser[24];
int          CurrentLevel;
bool         UserForced;
decimal      CurrentTimeout%5.0;
int          MaxNumbOfIO;    
int  TEST_BUTTON[10], TEST_ID[73], TEST_VALUE[73], TEST_CHECK[73], TEST_POINTER[73], TEST_STATE[73], TEST_SELECT[73], TEST_UNITS[73], Test_No, Test_PW;
timer AccessTimeoutT;
bool AccessTimer_ON, TouchScreenTimerEnable;
string RTC_Version[24]=__RTC_VERSION__, RTC_Platform[24]=__PLATFORM__,RTC_MacAdress[24] = __MACADDRESS__, IP_Address[24];
string dateformat[25],dateformat2[25],yearprefix[2],stddate[10],stdtime[8],FieldBusType[12],FieldBusTypeMem[12];

int cntmem;
bool RebuildWPList;

decimal AOUTPreset%5.1[4],AINValue%5.1[2];
bool AOUTActive[4],AINActive[2];
string AOUTType[4][1],AINType[2][1],AOUTName[5][10];
int AOUTMode[4],AOUTModul[4];
float ActuatorPosition,ActuatorLivePos;

//Temp DORJ2 Test vars
bool Continuous_Output, AutoPage_FS, RT_AutoPage;
bool LowLevel[2], ResetRegistryKey, PrintByassed;
int MinuteInAccess;

//Hardware dection tests
bool FB_SPU,FB_PIO,FB_NWU,FB_Profibus,FB_Profinet,FB_EthernetIP, FB_Detected, SwapDWBits;
int hardwaretest;
bool ContOutInitOK,ContOutCOM2EditOK,ContOutETHEditOK;

#define WPSpacing 9

//string FaultMessage[FltArrayMax][FltStringLen], FaultMsgTime[FltArrayMax][FltStringLen];
//bool FaultClrMsg[FltArrayMax]; 
string FaultMsgTimeMem[FltStringLen];
bool FS_Flt;
int FltLine_Pointer, Flt_Counter;

string Access_User[MAXUSERS][24], SystemErrorCode[128], SystemWarningCode[128];
string KeyLockString[5],KeyLockP[1],KeyLockT[1],KeyLockS[1],KeyLockZ[1],KeyLockI[1];

int iQFeedSettledCnt;
int iQSmartLearnNbr,iQFlashLearnNbr;
// IO Write test
int MaxArrayIODbase, MaxArrayAccessDbase, MaxArrayWPDbase, MaxArrayFlexIODbase;
bool IO_Change, InTest,OutTest,IOTestFlag,CheckOutput,IOCFG_OUT_Flag,IOError;
bool DBsToUSBSaved,DBsToUSBLoaded,LoadDBsFlag,PopConfirmLoad,PeriodicDBsSave;
int  MonthSaved;
float SaveToUSBTime,LoadFromUSBTime;

int  IO_Address[IO_ARRAY], IO_No[IO_ARRAY],
     FlexIO_Type[MAX_FLEXIO][2], FlexIO_SP[MAX_FLEXIO][2], FlexIO_IO[MAX_FLEXIO][2], FlexIO_Timer[MAX_FLEXIO][2], FlexIO_IoSwitch[MAX_FLEXIO][2], FlexIO_IOEnum[MAX_FLEXIO][2], 
     FlexIO_CntMode[MAX_FLEXIO][2], FlexIO_CntPreSource[MAX_FLEXIO][2], FlexCNT_PRE, FlexCounter, FlexPulseCnt;
decimal FlexIO_InitDelay%4.2[MAX_FLEXIO][2], FlexIO_OnTime%4.2[MAX_FLEXIO][2], FlexIO_OffTime%4.2[MAX_FLEXIO][2];
decimal FlexIO_SP_Pre%6.2[2][2];
bool IO_Input[IO_ARRAY], IO_Enable[IO_ARRAY],IO_State[IO_ARRAY],IO_TestState[IO_ARRAY], IO_Force[IO_ARRAY], IO_EnableBool[IO_ARRAY], Recipe_Grayout[49], MP_Grayout[37], MC_Grayout[37], 
     FlexIO_Grayout[37], RefreshGrayoutFlag, FlexIO_SPSign[MAX_FLEXIO][2], FlexIO_Valid[MAX_FLEXIO][2], FlexIO_Output[MAX_FLEXIO][2], FlexIO_TestOnFlag[MAX_FLEXIO][2], FlexIO_SetOnFlag[MAX_FLEXIO][2],
     FlexIO_SetOnFlag2[MAX_FLEXIO][2], Flex_FS_Test, Flex_Pulse_On;
string FlexIO_IONameON[MAX_FLEXIO][24], FlexIO_IONameOFF[MAX_FLEXIO][24];
string IO_Name[IO_ARRAY][50], IO_NameEn[IO_ARRAY][50];

int InputReg1, InputReg2, OutputReg1, OutputReg2,PIMoffset;

bool KeepSampling;
bool Db_InUse[MAX_DB];
//Fault message managment
string Fault_Txt[129][255];
//int    Fault_Type[MaxFlts];
bool LT_GEN, LT_BLK, LT_STOP, LT_WRN;

// Set time & date
int TD_Year,TD_Month,TD_Day,TD_Hour,TD_Minute,TD_YearDigits;
bool TD_SetFlag;
 
// From BT_Logic
timer T[T_ARRAY];
//Timer Arrays
int TMAX = T_ARRAY; //Number of timers declared
bool T_DN[T_ARRAY],T_EN[T_ARRAY],T_TT[T_ARRAY];
float T_ACC[T_ARRAY],T_PRE[T_ARRAY],Remain;

float req_slow_fill_time;
float step_slow_fill_percentage;
float offset_slow_fill_time;

#define FillingTaskIntervalAuto 15  //Desired Scan Time in ms
#define FillingTaskIntervalOff  100 //Desired Scan Time in ms
float   ScanMax;
float   ScanMin;
float   ScanTotal;
bool    OperationTaskHeartBeat,FillingTaskHeartBeat;
int     FillingTaskHeartBeatCnt,OperationTaskHeartBeatCnt;
int     taskid_filling,taskid_operation;
bool    DisableGoto[11],DisableNavig[11];
int     SeqMaster, SeqSpout, SeqWeighPan, SeqFeeder,SeqFeedSTD,SeqManDischarge,SeqKicker;
int     printTime,PrintEnd,PrintBegin;

//From Back_Task.c
//Scale dependant Variables
enum {Scale1=0,Scale2=1}
int Scale1Adm,Scale2Adm;
enum {Scale1CmpBulk=1,Scale1CmpInterm=2,Scale1CmpDribble=3,Scale1CmpCatchGate=4,Scale1CmpCatchGateInterm=5,
      Scale1CmpAout1=6,Scale1CmpAout2=7}
bool Scale1CmpBulkActive,Scale1CmpIntermActive,Scale1CmpDribbleActive,Scale1CmpCatchGateActive,Scale1CmpCatchGateIntermActive;      
bool IsSettled[2],FeederBWithAout;
int ZeroFreqCnt, SampleFreqCnt;
bool BulkDone,IntermDone,DribbleDone,EmptyHopper,CheckAll,CheckOnce, I_LowLevelSensorMEM,SlowCycleMem;
bool SlowCycleOccured,IsCleanoutDone,CleanoutWeighment,DischReqInputOn;
int ZeroFreqVal,Hopper_StateMEM,Discharge_StateMEM,Current_ScreenMEM,Current_ScreenMEM2;
#define KGtoLB 2.2046226218488
#define LBtoKG 1/KGtoLB
string UnitMem[4];
float UnitADMtoIQ,UnitIQtoADM;
bool SwitchUnitFlag;
bool RestartPopupClosed;
string TimeString[8];
string  MessageTextTemp[100];
int     DateNbr,DateNbrMem,TrialDaysCnt;
bool    DateRefreshed;

int SeqModeManager, ScaleStatus[2],ScaleStatusMem[2];
int SetZeroStatus[2],NbrCheckedWeight[2];
float NetWeight[2],AvgCheckedWeight[2],SumCheckedWeight[2];
float MaxWeight[2],NetWeightHiRes[2];



decimal TargetWeight%6.2[2],CutoffCorrOffset%6.2[2];
bool BulkOnTime[2],WeightSampled[2],LastCheckedWeight[2];

bool WeighmentAborted,FeedInProcess, HoldCycleMem, HoldCycleTgl, CycleInHoldMem, DisplayAlarmDelay,BlockMessage,DisplayFault;
bool DischReqMem,EmtpyBagReadyMem;
//Batch Production Data
bool BatchCountBool,SaveBatchFlag,BatchEnded,BatchEndReq,BatchCancelled;

float ZeroLimit;
bool AutoZeroOff;



//Printed Report Strings
string STR_AVERAGE[20];
string STR_BATCH_COUNTALL[20];
string STR_BATCH_CURRENT_PROD[20];
string STR_BATCH_DETAILS[20];
string STR_BATCH_MAX_ACCEPTED[20];
string STR_BATCH_MIN_ACCEPTED[20];
string STR_BATCH_NAME[20];
string STR_BATCH_PRESET[20];
string STR_BATCH_RESIDUE[20];
string STR_ID_ACTUAL_PROD[20];
string STR_ID_PRODUCTIONREPORT[20];
string STR_ID_LIFETIME_PROD[20];
string STR_ID_NOMINAL_WEIGHT[20];
string STR_ID_OVERWEIGHT[20];
string STR_ID_TOTAL_UNITS[20];
string STR_ID_TOTAL_WEIGHMENTS[20];
string STR_ID_TOTAL_WEIGHT[20];
string STR_ID_UNDERWEIGHT[20];
string STR_ID_UNITS_ACCEPTED[20];
string STR_ID_UNITS_DONE[20];
string STR_STD_DEV[20];

string STR_BatchTotalWeight[10];
string STR_BatchPreset[10];
string STR_BatchMinAccepted[10];
string STR_BatchUnitsDone[10];
string STR_BatchMaxAccepted[10];
string STR_BatchUnitsAccepted[10];
string STR_BatchResidue[10];
string STR_BatchUnderWeightCnt[10];
string STR_BatchStdDev[10];
string STR_BatchOverWeightCnt[10];
string STR_BatchAvg[10];
string STR_WPName[24];
string STR_BatchName[24];
string STR_WPUnit[2];
string STR_BatchDetails[48];
string STR_Date[10];
string STR_Time[8];
string STR_BatchCount[3];

string STR_WPNominalWeight[10];
string STR_ProdTotalWeighmentsLT_Scale1[10];
string STR_ProdTotalUnitsCnt_Scale1[10];
string STR_ProdTotalUnitsLT_Scale1[10];
string STR_ProdAcceptUnitCnt_Scale1[10];
string STR_ProdTotalWeightLT_Scale1[17];
string STR_ProdUnderWeightCnt_Scale1[10];
string STR_ProdOverWeightCnt_Scale1[10];
string STR_ProdTotalWeight_Scale1[14];


// Flash Feed
string      CPSmFastAvgPointsMem[128],CPSmSlowAvgPointsMem[128]CPSmSlowItpPointsMem[512];
string      CPFlFastPointsMem[128],CPFlDeviationPointsMem[256];
float       CPSmSwitchTimeMem,CPSmSwitchTimePct=0.85;
bool        LearniQSmartParam,LearniQSmartParamMem,LearniQFlashParam,iQFeedDone,LearniQSmartToSave,LearniQFlashToSave;
bool        InitiQSmart,InitiQFlash,iQOutputEnabled,InitPLoop,InitCPSmSwitchTime;  
bool        SaveiQFeedParamFlag;
int         NbrOf1stLearned;
float iQFlSwitchWeight = 90; //Percentage of Switching Weight for 1st Flash Feed weighment
float iQFlReduceOutput = 60; //Percentage(from min to max) of "controlled" output
float iQFlControlTime = 0.2; //total duration of the closing process
#define IQFEEDSETTLEDNBR  10

#define CATCHGATEDELAYMAX 5

//iQReadEventStats Production data
string WeighingData_StringSource[2][64],WeighingData_StringW1[10][64],WeighingData_StringW2[10][64]; 

//iQReadEventStats Production data
string iQStatData_String1[128], 
       iQStatData_String2[128], 
       iQStatData_String3[128], 
       iQStatData_String4[128], 
       iQStatData_String5[128], 
       iQStatData_String6[128], 
       iQStatData_String7[128],  
       iQStatData_String8[128],  
       iQStatData_String9[128]; 

//Smart Feed Data
float stat_controlled_fast_time,
      stat_controlled_slow_time, 
      stat_stable_fast_flow, 
      stat_stable_slow_flow, 
      stat_fast_flow_fluctuation, 
      stat_slow_flow_fluctuation;


float StartFeedingDelay,Aout2SwitchVal;

bool LangRefreshed[LAST_SCREEN], ButtonDisplayRefreshed[LAST_SCREEN], ModeRefreshed[LAST_SCREEN];
int    Fault_Type[MaxFlts];

int Start_PauseBtn,Start_PauseBtnMem;
bool AutoPause,PauseHMI,SampledInPause;
bool FirstPageLoading = ON;
bool O_CatchGateMem,CatchGateAlreadyOpen,O_DischDoorMem,DischDoorStillClose;

/* *********************************************************************************************************************** */
/*                 Definitions                                                                                             */
/* *********************************************************************************************************************** */

/**************************************************************************** 
  Includes  
*****************************************************************************/
#include "GetHardwareInfo.h"
#include "RTC_Constants_PTech.h"
#include "Language.h"

// Startup Message
#define INIT_MSG(msg) concat (lsub(TX_CONTROLLER_ID), space(1), lsub(TX_SCALE_TYPE),space(1), TX_PT_CONTROL_SW_VERS, msg)

#include "qtmonitor_PTech.h"
#include "BT_Enum_List.h"
#include "PT_Databases.h"  
#include "iQFeeding.h"
#include "iQSimulation.h" 	
#include "Print_Routines.c"
#include "Images.h"

#include "iQSubFonctions.c"
#include "Global_Functions.h"
#include "DisplayHandling.c"
#include "Back_Task.c"
#include "PLC_Com.c"
#include "LogicOperationTask.c"


/*------------------------------------------------------------------------- 
--  Procedure Name    : ProdDataPopup
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/03/17
--  
--  Purpose           : Stats Data Popup window display    
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void ProdDataPopup(void)              
{
int     class, type, value, err;
string  args[4][255];

  iQStatData_Popup = ON;
  begindraw();
    selectwindow (PRODDATA_POPUP_WINDOW);
    showwindow   (PRODDATA_POPUP_WINDOW );
  enddraw();      
      
  for(;;)
  {
   if ( eventreceived() )
   {
    readevent (class, type, value, args);
    
    iQStatData_Popup = OFF;
    iQStatData_PopupMEM = OFF;
    hidewindow (PRODDATA_POPUP_WINDOW);
    
    break;

   }
   else
    DisplayHandling ();   
   
  }
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : WeighingDataPopup
--  Created by        : Jean-Pierre DorÃ©
--  Last modified on  : 2018/03/14
--  
--  Purpose           : Weighing Data Popup window display    
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void WeighingDataPopup(void)              
{
int     class, type, value, err;
string  args[4][255];

  WeighingData_Popup = ON;
  begindraw();
    selectwindow (WEIGHINGDATA_POPUP_WINDOW);
    showwindow   (WEIGHINGDATA_POPUP_WINDOW );
  enddraw();      
      
  for(;;)
  {
   if ( eventreceived() )
   {
    readevent (class, type, value, args);
    
    
      WeighingData_Popup = OFF;
      WeighingData_PopupMEM = OFF;
      hidewindow (WEIGHINGDATA_POPUP_WINDOW);
      if(Current_Screen == SCREEN_REPORT) WeightDisplaySmall(No_Forcing);
      break;

   }
   else
    DisplayHandling ();   
   
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       RECIPE APPLICATION                                                */
/*                                                                         */
/* *********************************************************************** */
int ApplicationRecipe (void)
{
int     class, type, value;
string  args[4][255], Temp_args[255];

  //##### Page Init #####
  SelectAndWaitPage(PAGE_RECIPE_1);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);    
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  RefreshWPScreen (Current_Screen);
   
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      Controller = eventreceived();
      Permission = Check_Permission();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             { 
                case RECIPE_SEARCH_ID :
                             if (Permission)
                             { 
                              Change_Recipe(SCREEN_WP_LIST_POPUP,PAGE_RECIPE_1,MemRecipe,Current_Screen,List_Page);
                              Current_Screen = SCREEN_RECIPE1;
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshWPScreen (Current_Screen);  
                             }                 
                            break;         
                                                
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
//                case NAV_FCT_BUTTON_2 : 
//                            if(RecipeButton)
//                            {           
//                              WeightDisplayInfo(No_Forcing);
//                              return (SCREEN_RECIPE1);
//                            }                           
//                            break;
                            
                case NAV_FCT_BUTTON_3 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :// Navigation Page "Other screens"
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 
                                                 
                case NAV_FCT_BUTTON_5 : // Fault Reset
                              FaultReset();
                            break;
                            
                case NAV_FCT_BUTTON_6 :// Batch report page
                             WeightDisplayInfo(No_Forcing);
                             SelectAndWaitPage(PAGE_BATCH);
                             Current_Screen = SCREEN_BATCH;
                             if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
                             if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
                             widget_enable     (NAV_FCT_BUTTON_7,ON);
                             RefreshReportScreen(Current_Screen);
                             return (SCREEN_BATCH);
                            break;                            
                            
                case NAV_FCT_BUTTON_7 : 
                                
                            break;   
                                    
                case NAV_FCT_BUTTON_8 : 
                              
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :
                              switch (Current_Screen)
                              {
                                 case SCREEN_RECIPE2 : 
//                                           widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(10), "1" , space(1), TX_FSLASH, space(1), "4", space(1)) );
                                           SelectAndWaitPage(PAGE_RECIPE_1);
                                           Current_Screen = SCREEN_RECIPE1;
                                         break; 
                                 
                                 case SCREEN_RECIPE3 :  
//                                           widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(10), "2" , space(1), TX_FSLASH, space(1), "4", space(1)) ); 
                                           SelectAndWaitPage(PAGE_RECIPE_2);
                                           Current_Screen = SCREEN_RECIPE2;                                                                                              
                                         break;
                                  
                                 case SCREEN_RECIPE4 : 
//                                           widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(10), "3" , space(1), TX_FSLASH, space(1), "4", space(1)) );
                                           SelectAndWaitPage(PAGE_RECIPE_3);
                                           Current_Screen = SCREEN_RECIPE3;                                                                                              
                                         break;        
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshWPScreen (Current_Screen);
                            break;
                                       
                case NAV_FCT_BUTTON_10 :
                              switch (Current_Screen)
                              {
                                case SCREEN_RECIPE1 :
//                                           widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(10), "2" , space(1), TX_FSLASH, space(1), "4", space(1)) );
                                           SelectAndWaitPage(PAGE_RECIPE_2);
                                           Current_Screen = SCREEN_RECIPE2;                                                                        
                                         break; 
                                         
                                 case SCREEN_RECIPE2 :
//                                           widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(10), "3" , space(1), TX_FSLASH, space(1), "4", space(1)) );
                                           SelectAndWaitPage(PAGE_RECIPE_3);
                                           Current_Screen = SCREEN_RECIPE3;                                           
                                         break;
                                         
                                 case SCREEN_RECIPE3 :
//                                           widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(10), "4" , space(1), TX_FSLASH, space(1), "4", space(1)) );
                                           SelectAndWaitPage(PAGE_RECIPE_4);
                                           Current_Screen = SCREEN_RECIPE4;                                           
                                         break;        
                                          
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshWPScreen (Current_Screen); 
                            break; 
             }
           break;
        // Assign entered text to database variables
        case EVENT_TYPE_TEXT_ENTERED:   
           
           if (Permission)
           {  
              RefreshRecipeInputEntry(Current_Screen, value,args[0]);
              SaveWP2Db();
           }   
           RefreshWPScreen (Current_Screen);
             
        break;
        
        // Assign selected variable from combobox to database
        case EVENT_TYPE_COMBOBOX_ACTIVATED :   
           
           if (Permission)
           { 
              RefreshRecipeComboBoxEntry(Current_Screen, value, int(args[0]), string(args[1]));
              SaveWP2Db();
           }   
           RefreshWPScreen (Current_Screen);
             
        break;      

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                      
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshWPScreen (Current_Screen);
         break;
      }
 
    }
    else
      DisplayHandling();
      TimeoutUser();
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       MACHINE PARAMETERS APPLICATION                                    */
/*                                                                         */
/* *********************************************************************** */
int ApplicationMP (void)
{
int     class, type, value;
string  args[4][255], Temp_args[255];

  //##### Page Init #####
  SelectAndWaitPage(PAGE_MP_1);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);    
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  RefreshMPScreen (Current_Screen);  

  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      Controller = eventreceived();
      Permission = Check_Permission();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             {                                     
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                          if(RecipeButton)
                            {  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }                           
                            break;
                            
                case NAV_FCT_BUTTON_3 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;

                case NAV_FCT_BUTTON_4 :// Navigation Page "Other screens"
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 
                                                 
                case NAV_FCT_BUTTON_5 : // Fault Reset
                              FaultReset();
                            break;
                            
                case NAV_FCT_BUTTON_6 : //  Time & date management page
                             if (Current_Screen == SCREEN_MP1)
                              {
                                 WeightDisplaySmall(No_Forcing);
                                 SelectAndWaitPage(PAGE_TDMANAGE);
                                 Current_Screen = SCREEN_TDMANAGE;
                                 if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                                 if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
                                 RefreshTDManageScreen(ON);
                              }
                             break;                            
                            
                case NAV_FCT_BUTTON_7 : 
                                
                            break;   
                                    
                case NAV_FCT_BUTTON_8 : 
                              
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :
                              switch (Current_Screen)
                              {
                                 case SCREEN_MP2 :
                                           SelectAndWaitPage(PAGE_MP_1);
                                           Current_Screen = SCREEN_MP1;
                                           if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                                           RefreshMPScreen (Current_Screen);
                                         break;

                                 case SCREEN_MP3 :
                                           SelectAndWaitPage(PAGE_MP_2);
                                           Current_Screen = SCREEN_MP2;
                                           if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                                           RefreshMPScreen (Current_Screen);
                                         break;
                                         
                                  case SCREEN_MP4 :
                                           SelectAndWaitPage(PAGE_MP_3);
                                           Current_Screen = SCREEN_MP3;
                                           if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                                           RefreshMPScreen (Current_Screen);
                                         break; 
                                   
                                  case SCREEN_TDMANAGE :
                                           if (!TD_SetFlag) TD_SetFlag = ON; 
                                         break;       
                              }           
                            break;
                                       
                case NAV_FCT_BUTTON_10 :
                              switch (Current_Screen)
                              {
                                case SCREEN_MP1 :
                                           SelectAndWaitPage(PAGE_MP_2);
                                           Current_Screen = SCREEN_MP2;
                                           if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                                           RefreshMPScreen (Current_Screen);                                                                                                   
                                         break; 
                                         
                                 case SCREEN_MP2 :
                                           SelectAndWaitPage(PAGE_MP_3);
                                           Current_Screen = SCREEN_MP3;
                                           if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                                           RefreshMPScreen (Current_Screen); 
                                           if (Access_MPPage3 != SCREEN_MP3)  ButtonDisplayControl(SCREEN_MP3);                                                                                           
                                         break;
                                         
                                 case SCREEN_MP3 :
                                           SelectAndWaitPage(PAGE_MP_4);
                                           Current_Screen = SCREEN_MP4;
                                           if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                                           RefreshMPScreen (Current_Screen);                                                                                           
                                         break;
                                         
                                 case SCREEN_TDMANAGE :
                                           RefreshTDManageScreen(ON); 
                                         break;
                              }           
                            break; 
  
                case MP_SAVE2DEFAULT :
                              
                              YesNoPopupMessage (lsub(TX_CONFIRM_SAVE2DEFAULT), CONFIG_PAGES, MP_SAVE2DEFAULT, MP_Db);
                            break; 
                            
                case MP_RESTOREDEFAULT :
                              YesNoPopupMessage (lsub(TX_CONFIRM_RESTOREDEFAULT), CONFIG_PAGES, MP_RESTOREDEFAULT, MP_Db);
                            break;                           
             }
        break;
        // Assign enterd text to database variables
        case EVENT_TYPE_TEXT_ENTERED:   
                      
             if (Current_Screen == SCREEN_TDMANAGE) RefreshTDManageInputEntry(value, args[0]);
             else
             {
              if (Permission)
              { 
                RefreshMPInputEntry(Current_Screen, value, args[0]);
                 SaveMP2Db();
              }
              RefreshMPScreen (Current_Screen);
             }  
        break;
        
        // Assign selected variable from combobox to database
        case EVENT_TYPE_COMBOBOX_ACTIVATED :   
           
           if (Permission)
              {  
                 RefreshMPComboBoxEntry(Current_Screen, value, args[0]);  
                 SaveMP2Db();
              }   
              RefreshMPScreen (Current_Screen);     
        break;          

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                      
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshTDManageScreen(ON);
                       RefreshMPScreen    (Current_Screen); 
            break;
      }
 
    }
    else
      DisplayHandling ();
      TimeoutUser();
      if (Current_Screen == SCREEN_TDMANAGE) RefreshTDManageScreen(OFF);
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }    
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       MACHINE CONFIG APPLICATION                                        */
/*                                                                         */
/* *********************************************************************** */
int ApplicationMC (void)
{
int     class, type, value, err;
string  args[4][255], Temp_args[255];

  //##### Page Init #####
  SelectAndWaitPage(PAGE_MC_1);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);    
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  RefreshMCScreen (Current_Screen);  
   
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      Controller = eventreceived();
      Permission = Check_Permission();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             {                 
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }                        
                            break;
                            
                case NAV_FCT_BUTTON_3 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :// Navigation Page "Other screens"
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 
                                                 
                case NAV_FCT_BUTTON_5 : // Fault reset
                              FaultReset();
                            break;
                            
                case NAV_FCT_BUTTON_6 : 
                              
                            break;                            
                            
                case NAV_FCT_BUTTON_7 : 
                                
                            break;   
                                    
                case NAV_FCT_BUTTON_8 : 
                              
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :
                              switch (Current_Screen)
                              {
                                 case SCREEN_MC2 :
                                           SelectAndWaitPage(PAGE_MC_1);
                                           Current_Screen = SCREEN_MC1;
                                         break; 
                                 
                                 case SCREEN_MC3 :
                                           SelectAndWaitPage(PAGE_MC_2);
                                           Current_Screen = SCREEN_MC2;                                                                                                         
                                         break;
                                         
                                case SCREEN_MC4 :
                                           SelectAndWaitPage(PAGE_MC_3);
                                           Current_Screen = SCREEN_MC3;                                                                                                 
                                         break;
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshMCScreen (Current_Screen);
                            break;
                                       
                case NAV_FCT_BUTTON_10 :
                              switch (Current_Screen)
                              {
                                case SCREEN_MC1 :
                                           SelectAndWaitPage(PAGE_MC_2);
                                           Current_Screen = SCREEN_MC2;                                                                     
                                         break; 
                                         
                                 case SCREEN_MC2 :
                                           SelectAndWaitPage(PAGE_MC_3);
                                           Current_Screen = SCREEN_MC3;
                                        if (Access_MCPage3 != SCREEN_MC3)   ButtonDisplayControl(SCREEN_MC3);
                                         break;
                                 
                                 case SCREEN_MC3 :
                                           SelectAndWaitPage(PAGE_MC_4);
                                           Current_Screen = SCREEN_MC4;
                                         break;
                                          
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshMCScreen (Current_Screen); 
                            break;          

                case MC_SAVE2DEFAULT :
                              
                              YesNoPopupMessage (lsub(TX_CONFIRM_SAVE2DEFAULT), CONFIG_PAGES, MC_SAVE2DEFAULT, MC_Db);
                               
                            break; 
                            
                case MC_RESTOREDEFAULT :
                              YesNoPopupMessage (lsub(TX_CONFIRM_RESTOREDEFAULT), CONFIG_PAGES, MC_RESTOREDEFAULT, MC_Db);
                              
                            break;    

             }
        break;
        // Assign entered text to database variables
        case EVENT_TYPE_TEXT_ENTERED:   
           
           if (Permission)
           {
             RefreshMCInputEntry(Current_Screen, value, args[0]);
             SaveMC2Db();
             WriteAccessTableDB();
           }
           RefreshMCScreen (Current_Screen);     
             
        break;
        
        // Assign selected variable from combobox to database
        case EVENT_TYPE_COMBOBOX_ACTIVATED :   
           
           if (Permission)
           {
             RefreshMCComboBoxEntry(Current_Screen, value,args[0]);
             SaveMC2Db();
           }
           RefreshMCScreen (Current_Screen);           
        break;

        case EVENT_TYPE_LIST_ITEM_SELECTED :   
           if (Permission)
           {
             CurScreenMEM = Current_Screen;
             Current_Screen = SCREEN_LANG_LIST_POPUP;       
             if (value == MC_ROW11_SELECT) Lang_No_Mem = MC.Language2;
             else Lang_No_Mem = MC.Language3;
             Language.No = ShowDbaseLanguageList();
             Current_Screen = CurScreenMEM;
             SelectAndWaitPage(PAGE_MC_1);
             err = find(Language);
               switch (value)
               {
  //               case MC_ROW10_SELECT:
  //                                     MC.Language1 = Language.No;
  //                                     MC.Lang1Text = Language.Name;
  //                                  break;  
                 case MC_ROW11_SELECT:
                                       MC.Language2 = Language.No;
                                       MC.Lang2Text = Language.Name;
                                    break;                    
                 case MC_ROW12_SELECT:
                                       MC.Language3 = Language.No;
                                       MC.Lang3Text = Language.Name;
                                    break;
               }
             
             SaveMC2Db();
           }  
           RefreshMCScreen (Current_Screen);      
           
        break;          

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                      
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshMCScreen    (Current_Screen); 
            break;
      }
 
    }
    else
      DisplayHandling ();
      TimeoutUser();
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }    
  }
}

/* *********************************************************************** */
/*                                                                         */
/*             FLEXIBLE IOs APPLICATION                                    */
/*                                                                         */
/* *********************************************************************** */
int ApplicationFlexIO (void)
{
int     class, type, value, err;
string  args[4][255], Temp_args[255];

  //##### Page Init #####
  SelectAndWaitPage(PAGE_FLEXIO_1);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);    
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  FlexIO.No = 1;
  find_db (FlexIO_Db);
  RefreshFlexIOScreen (Current_Screen);

  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      Controller = eventreceived();
      Permission = Check_Permission();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             {                                           
                
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                    
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }                           
                            break;
                            
                case NAV_FCT_BUTTON_3 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;

                case NAV_FCT_BUTTON_4 :// Navigation Page "Other screens"
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 
                                                 
                case NAV_FCT_BUTTON_5 : // Fault Reset
                              FaultReset();
                            break;
                            
                case NAV_FCT_BUTTON_6 : 
                             
                             break;                            
                            
                case NAV_FCT_BUTTON_7 : 
  
                            break;   
                                    
                case NAV_FCT_BUTTON_8 : 

                            break;  
                                       
                case NAV_FCT_BUTTON_9 :
                                         switch (Current_Screen)
                                          {
                                            case SCREEN_FLEXIO_2 :
                                                       SelectAndWaitPage(PAGE_FLEXIO_1);
                                                       Current_Screen = SCREEN_FLEXIO_1;
                                                       FlexIO.No =1;
                                                       find_db (FlexIO_Db);                                                                     
                                                     break; 
                                                     
                                             case SCREEN_FLEXIO_3 :
                                                       SelectAndWaitPage(PAGE_FLEXIO_2);
                                                       Current_Screen = SCREEN_FLEXIO_2;
                                                       FlexIO.No =2;
                                                       find_db (FlexIO_Db);
                                                     break;
                                                      
                                          }

                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshFlexIOScreen (Current_Screen);        
                            break;
                                       
                case NAV_FCT_BUTTON_10 :
                                          switch (Current_Screen)
                                          {
                                            case SCREEN_FLEXIO_1 :
                                                       SelectAndWaitPage(PAGE_FLEXIO_2);
                                                       Current_Screen = SCREEN_FLEXIO_2;
                                                       FlexIO.No =2;
                                                       find_db (FlexIO_Db);                                                                     
                                                     break; 
                                                     
                                             case SCREEN_FLEXIO_2 :
                                                       SelectAndWaitPage(PAGE_FLEXIO_3);
                                                       Current_Screen = SCREEN_FLEXIO_3;
                                                       FlexIO.No =3;
                                                       find_db (FlexIO_Db);
                                                     break;
                                                      
                                          }
                              

                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshFlexIOScreen (Current_Screen);
                            break; 
             }
        break;
        
        // Assign entered text to database variables
        case EVENT_TYPE_TEXT_ENTERED:   
           
           if (Permission)
           {
               RefreshFlexIOInputEntry(Current_Screen, value, args[0]);
               save_db (FlexIO_Db);
               MoveFlexIoDbs2Vars();
               Reset_FlexIO();
           }
           RefreshFlexIOScreen (Current_Screen);     
             
        break;
        
        // Assign selected variable from combobox to database
        case EVENT_TYPE_COMBOBOX_ACTIVATED :   
            
           if (Permission)
           { 
               RefreshFlexIOComboBoxEntry(Current_Screen, value, args[0]); 
               save_db (FlexIO_Db);
               MoveFlexIoDbs2Vars();
               Reset_FlexIO();
           }
           RefreshFlexIOScreen (Current_Screen);     
        break; 
        
        case EVENT_TYPE_LIST_ITEM_SELECTED :   
           
           if (Permission)
           {  
               CurScreenMEM = Current_Screen;
               Current_Screen = SCREEN_FLEXIO_LIST_POPUP;
               IOdb.No = ShowAvailableIOList(value);
               Current_Screen = CurScreenMEM;
                 
               RefreshFlexIOListEntry (Current_Screen, value, IOdb.No); 
               if (IOdb.No != 9999)
               {
                 save_db (FlexIO_Db);
                 MoveFlexIoDbs2Vars(); 
                 RefreshFlexIOScreen (Current_Screen);
                 Reset_FlexIO();
               }     
           }
        break;          

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                      
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshFlexIOScreen (Current_Screen);
            break;
      }
 
    }
    else
      DisplayHandling ();
      TimeoutUser();
    
    if (mode_step == stp_OFF_MODE) RefreshFlexIOScreen(Current_Screen);
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }    
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       IO CONFIG APPLICATION                                             */
/*                                                                         */
/* *********************************************************************** */
int ApplicationIOConfig (void)
{
int     class, type, value, err;
string  args[4][255];

  //##### Page Init #####
  SelectAndWaitPage(PAGE_IO_INPUT_1);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);      
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  RefreshIOConfigScreen (Current_Screen); 
   
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      Controller = eventreceived();
      Permission = Check_Permission();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             {                                            
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :  
                           if(RecipeButton)
                            {                                
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }                        
                            break;
                            
                case NAV_FCT_BUTTON_3 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;

                case NAV_FCT_BUTTON_4 :// Navigation Page "Other screens"
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 
                                                 
                case NAV_FCT_BUTTON_5 : // Fault reset
                              FaultReset();
                            break;
                            
                case NAV_FCT_BUTTON_6 : 
                              if (Current_Screen==SCREEN_IOCFG_IN1 || Current_Screen==SCREEN_IOCFG_IN2 || Current_Screen==SCREEN_IOCFG_IN3) 
                              Current_Screen=SCREEN_IOCFG_IN1;
                              if (Current_Screen==SCREEN_IOCFG_OUT1 || Current_Screen==SCREEN_IOCFG_OUT2 || Current_Screen==SCREEN_IOCFG_OUT3) 
                              Current_Screen=SCREEN_IOCFG_OUT1;
                              switch (Current_Screen)
                              {
                                 case SCREEN_IOCFG_IN1 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_OUTPUT_1);
                                           Current_Screen = SCREEN_IOCFG_OUT1;
                                         break; 
                                 
                                 case SCREEN_IOCFG_OUT1 : 
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") ); 
                                           SelectAndWaitPage(PAGE_IO_INPUT_1);
                                           Current_Screen = SCREEN_IOCFG_IN1;                                                                                                   
                                         break;
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshIOConfigScreen (Current_Screen);  
                            break;                            
                            
                case NAV_FCT_BUTTON_7 : 
                                
                            break;   
                                    
                case NAV_FCT_BUTTON_8 : 
                              
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :
                              switch (Current_Screen)
                              {
                                 case SCREEN_IOCFG_IN2 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUT_1);
                                           Current_Screen = SCREEN_IOCFG_IN1;
                                         break; 
                                 
                                 case SCREEN_IOCFG_IN3 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "3" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUT_2);
                                           Current_Screen = SCREEN_IOCFG_IN2;
                                         break;
                                 
                                 case SCREEN_IOCFG_OUT2 : 
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") ); 
                                           SelectAndWaitPage(PAGE_IO_OUTPUT_1);
                                           Current_Screen = SCREEN_IOCFG_OUT1;                                                                                                
                                         break;
                                 
                                 case SCREEN_IOCFG_OUT3 : 
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "3" , space(1), TX_FSLASH, space(1), "3") ); 
                                           SelectAndWaitPage(PAGE_IO_OUTPUT_2);
                                           Current_Screen = SCREEN_IOCFG_OUT2;                                                                                                       
                                         break;
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshIOConfigScreen (Current_Screen);
                            break;
                                       
                case NAV_FCT_BUTTON_10 : 
                              switch (Current_Screen)
                              {
                                case SCREEN_IOCFG_IN1 :
//                                          widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUT_2);
                                           Current_Screen = SCREEN_IOCFG_IN2;                                                                                                              
                                         break; 
                                 
                                 case SCREEN_IOCFG_IN2 :
//                                          widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUT_3);
                                           Current_Screen = SCREEN_IOCFG_IN3;                                                                                                            
                                         break;
                                         
                                 case SCREEN_IOCFG_OUT1 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_OUTPUT_2);
                                           Current_Screen = SCREEN_IOCFG_OUT2;                                      
                                         break; 
                                         
                                  case SCREEN_IOCFG_OUT2 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_OUTPUT_3);
                                           Current_Screen = SCREEN_IOCFG_OUT3;                                             
                                         break;        
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshIOConfigScreen (Current_Screen); 
                            break; 
             }
        break;
        // Assign entered text to database variables
        case EVENT_TYPE_TEXT_ENTERED:   
           if (Permission)
           {
             switch (Current_Screen)
             {
                case SCREEN_IOCFG_IN1 :  
                             IOdb.No = (value)-IO_INPUTBOX_MARKER;
                           break;
                case SCREEN_IOCFG_IN2 :  
                             IOdb.No = (value)-IO_INPUTBOX_MARKER+12;
                           break;
                case SCREEN_IOCFG_IN3 :  
                             IOdb.No = (value)-IO_INPUTBOX_MARKER+24;
                           break;
                case SCREEN_IOCFG_OUT1 :  
                             IOdb.No = (value)-IO_INPUTBOX_MARKER+36;
                           break;
                case SCREEN_IOCFG_OUT2 :  
                             IOdb.No = (value)-IO_INPUTBOX_MARKER+48;
                           break;
                case SCREEN_IOCFG_OUT3 :  
                             IOdb.No = (value)-IO_INPUTBOX_MARKER+60;
                           break;                                                                                                                                                         
             }
             WriteIOSingleEntryDB (IOdb.No, int (Lim(0,(MaxNumbOfIO),args[0])),InputBox,ON);
           }     
           RefreshIOConfigScreen (Current_Screen); 
        break; 
        
        // Assign selected variable from combobox to database
        case EVENT_TYPE_ONOFFBOX_CHANGED :   
           if (Permission)
           {
             switch (Current_Screen)
             {
                case SCREEN_IOCFG_IN1 :  
                             IOdb.No = (value)-IO_CHECKBOX_MARKER;
                             RefreshIOGrayOut(Current_Screen, 12,0);
                           break;
                case SCREEN_IOCFG_IN2 :  
                             IOdb.No = (value)-IO_CHECKBOX_MARKER+12;
                             RefreshIOGrayOut(Current_Screen, 12,12);
                           break;
                case SCREEN_IOCFG_IN3 :  
                             IOdb.No = (value)-IO_CHECKBOX_MARKER+24;
                             RefreshIOGrayOut(Current_Screen, 12,24);
                           break;
                case SCREEN_IOCFG_OUT1 :  
                             IOdb.No = (value)-IO_CHECKBOX_MARKER+36;
                             RefreshIOGrayOut(Current_Screen, 12,36);
                           break;
                case SCREEN_IOCFG_OUT2 :  
                             IOdb.No = (value)-IO_CHECKBOX_MARKER+48;
                             RefreshIOGrayOut(Current_Screen, 12,48);
                           break;
                case SCREEN_IOCFG_OUT3 :  
                             IOdb.No = (value)-IO_CHECKBOX_MARKER+60;
                             RefreshIOGrayOut(Current_Screen,12,60);
                           break;  
             }
             WriteIOSingleEntryDB (IOdb.No, (args[0]),CheckBox,ON);
           }
           RefreshIOConfigScreen (Current_Screen); 
         break;

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                      
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshIOConfigScreen (Current_Screen); 
            break;
      }
 
    }
    else
      DisplayHandling ();
      TimeoutUser();
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }
  }    
}

/* *********************************************************************** */
/*                                                                         */
/*       IO TEST APPLICATION                                               */
/*                                                                         */
/* *********************************************************************** */
int ApplicationIOTest (void)
{
int     class, type, value, err, object_id;
string  args[4][255];

  //##### Page Init #####
  SelectAndWaitPage(PAGE_IO_INPUTTEST_1);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen); 
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);    
  RefreshIOTestScreen (Current_Screen); 
  RefreshIOGrayOut(Current_Screen, 12,0);
   
  widget_enable(NAV_FCT_BUTTON_7,ON);  

  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      Controller = eventreceived();
      Permission = Check_Permission();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             {                                 
               
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                    
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }                               
                            break;
                            
                case NAV_FCT_BUTTON_3 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;

                case NAV_FCT_BUTTON_4 :// Navigation Page "Other screens"
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 
                                                 
                case NAV_FCT_BUTTON_5 : // Fault reset
                              FaultReset();
                            break;
                            
                case NAV_FCT_BUTTON_6 : 
                              if (Current_Screen==SCREEN_IOTEST_IN1 || Current_Screen==SCREEN_IOTEST_IN2 || Current_Screen==SCREEN_IOTEST_IN3 || Current_Screen==SCREEN_ANALOGTEST)  
                              Current_Screen=SCREEN_IOTEST_IN1;
                              if (Current_Screen==SCREEN_IOTEST_OUT1 || Current_Screen==SCREEN_IOTEST_OUT2 || Current_Screen==SCREEN_IOTEST_OUT3)
                              Current_Screen=SCREEN_IOTEST_OUT1;
                              
                              switch (Current_Screen)
                              {
                                 case SCREEN_IOTEST_IN1 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_OUTPUTTEST_1);
                                           Current_Screen = SCREEN_IOTEST_OUT1;
                                           RefreshIOGrayOut(Current_Screen, 12,36);                                           
                                         break; 
                                 
                                 case SCREEN_IOTEST_OUT1 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUTTEST_1);
                                           Current_Screen = SCREEN_IOTEST_IN1;                                       
                                           RefreshIOGrayOut(Current_Screen, 12,0);                                                                                                                                                        
                                         break;

                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshIOTestScreen (Current_Screen);  
                            break;                            
                            
                case NAV_FCT_BUTTON_7 : 
                              switch (Current_Screen)
                              {
                                 case SCREEN_IOTEST_IN1 :
                                            SelectAndWaitPage(PAGE_IO_ANALOGTEST);
                                            Current_Screen = SCREEN_ANALOGTEST;
                                         break;
                                 
                                 case SCREEN_IOTEST_OUT1 :
                                 case SCREEN_IOTEST_OUT2 :
                                 case SCREEN_IOTEST_OUT3 :
                                            SelectAndWaitPage(PAGE_IO_ANALOGTEST);
                                            Current_Screen = SCREEN_ANALOGTEST;                                
                                         break;
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshAnalogTestScreen (Current_Screen);  
                            break;   
                                    
                case NAV_FCT_BUTTON_8 : 
                              
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :
                              switch (Current_Screen)
                              {                                
                                 case SCREEN_IOTEST_IN2 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUTTEST_1);
                                           Current_Screen = SCREEN_IOTEST_IN1;
                                           RefreshIOGrayOut(Current_Screen, 12,0);                                           
                                         break; 
                                 
                                 case SCREEN_IOTEST_IN3 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUTTEST_2);
                                           Current_Screen = SCREEN_IOTEST_IN2;                                          
                                           RefreshIOGrayOut(Current_Screen, 12,12);                                           
                                         break;
                                 
                                 case SCREEN_IOTEST_OUT2 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") ); 
                                           SelectAndWaitPage(PAGE_IO_OUTPUTTEST_1);
                                           Current_Screen = SCREEN_IOTEST_OUT1;                                         
                                           RefreshIOGrayOut(Current_Screen, 12,36);                                                                                                                                                   
                                         break;
                                 
                                 case SCREEN_IOTEST_OUT3 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_OUTPUTTEST_2);
                                           Current_Screen = SCREEN_IOTEST_OUT2;                                         
                                           RefreshIOGrayOut(Current_Screen, 12,48);                                                                                                                                                       
                                         break;
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshIOTestScreen (Current_Screen);
                            break;
                                       
                case NAV_FCT_BUTTON_10 :
                              switch (Current_Screen)
                              {
                                case SCREEN_IOTEST_IN1 :
//                                          widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUTTEST_2);
                                           Current_Screen = SCREEN_IOTEST_IN2;      
                                           RefreshIOGrayOut(Current_Screen, 12,12);                                                                                                                                                         
                                         break; 
                                 
                                 case SCREEN_IOTEST_IN2 :
//                                          widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(5), "3" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_INPUTTEST_3);
                                           Current_Screen = SCREEN_IOTEST_IN3;                                           
                                           RefreshIOGrayOut(Current_Screen, 12,24);                                                                                                                                                       
                                         break;
                                         
                                 case SCREEN_IOTEST_OUT1 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_OUTPUTTEST_2);
                                           Current_Screen = SCREEN_IOTEST_OUT2;                                          
                                           RefreshIOGrayOut(Current_Screen, 12,48);                                                                                 
                                         break; 
                                         
                                  case SCREEN_IOTEST_OUT2 :
//                                           widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(5), "3" , space(1), TX_FSLASH, space(1), "3") );
                                           SelectAndWaitPage(PAGE_IO_OUTPUTTEST_3);
                                           Current_Screen = SCREEN_IOTEST_OUT3;                                          
                                           RefreshIOGrayOut(Current_Screen, 12,60);                                                                                   
                                         break;        
                              }
                              if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
                              RefreshIOTestScreen (Current_Screen);
                            break; 
             }
        break;
        
        // Assign entered text to database variables
        case EVENT_TYPE_TEXT_ENTERED:   
           if (Permission)
           { 
             switch (value)
             {
                case IO_STATE_ROW7 :  
                             AOUTPreset[AIO1] = Lim(0,100,args[0]);
                           break;
                case IO_STATE_ROW8 :  
                             AOUTPreset[AIO2] = Lim(0,100,args[0]);
                           break;
                case IO_STATE_ROW9 :  
                             AOUTPreset[AIO3] = Lim(0,100,args[0]);
                           break;
                case IO_STATE_ROW10 :  
                             AOUTPreset[AIO4] = Lim(0,100,args[0]);
                           break;                                 
             }
           }
           RefreshAnalogTestScreen(Current_Screen);  
          break;   
        // Assign selected variable from combobox to database
        case EVENT_TYPE_ONOFFBOX_CHANGED :   
           if (Permission)
           {
             switch (Current_Screen)
             {
                case SCREEN_IOTEST_OUT1 :  
                             object_id = (value)-IO_CHECKBOX_MARKER+36;
                             IO_Force[object_id] = (!Arg2Bool(args[0])&& !LT_GEN); 
                           break;
                case SCREEN_IOTEST_OUT2 :  
                             object_id = (value)-IO_CHECKBOX_MARKER+48;
                             IO_Force[object_id] = (!Arg2Bool(args[0])&& !LT_GEN);
                           break;
                case SCREEN_IOTEST_OUT3 :  
                             object_id = (value)-IO_CHECKBOX_MARKER+60;
                             IO_Force[object_id] = (!Arg2Bool(args[0])&& !LT_GEN);
                           break;  
                          
             }
           }  
         break;

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                       
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshIOTestScreen (Current_Screen); 
            break;
      }
 
    }
    else
      DisplayHandling ();
      TimeoutUser();
      
      if (Current_Screen == SCREEN_ANALOGTEST) RefreshAnalogTestScreen(Current_Screen);    
      else RefreshIOTestScreen(Current_Screen);
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }     
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       REPORT APPLICATION                                                */
/*                                                                         */
/* *********************************************************************** */
                              
int ApplicationReport (bool ReportPage)
{
int     class, type, value;
string  args[4][255];

  // ##### Page init #####
 if(ReportPage)
 { 
  SelectAndWaitPage(PAGE_REPORT);
  if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
  if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  RefreshReportScreen(Current_Screen); 
  widget_enable     (NAV_FCT_BUTTON_7, ON);
 }  
                       
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             { 
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }  
                            break;
                            
                case NAV_FCT_BUTTON_3 : 
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :// Navigation Page "Other screens"
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 

                case NAV_FCT_BUTTON_5 : // Fault reset
                             FaultReset();
                            break;
                                                 
                case NAV_FCT_BUTTON_6 : // Batch report page
                             WeightDisplayInfo(No_Forcing);
                             SelectAndWaitPage(PAGE_BATCH);
                             Current_Screen = SCREEN_BATCH;
                             if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
                             if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
                             widget_enable     (NAV_FCT_BUTTON_7,ON);
                             RefreshReportScreen(Current_Screen);
                            break;
                                                        
                case NAV_FCT_BUTTON_7 :  // Print Page   
                               PrintRequest = ON;
                            break;   
                                    
                case NAV_FCT_BUTTON_8 :  // not used 
                               WeightDisplayInfo(No_Forcing);          
                               WeighingDataPopup();       
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :  // Reset Lifetime Production Report 
                              if (Current_Screen == SCREEN_REPORT && CurrentLevel == Level_PT) YesNoPopupMessage (TX_CONFIRM_RESETLIFETIME, SCREEN_REPORT, Current_Screen, NO_Db);
                            break; 
                                       
                case NAV_FCT_BUTTON_10 : // Reset production
                              if (Current_Screen == SCREEN_REPORT) ResetDataHMI = ON;
                              if (Current_Screen == SCREEN_BATCH) ResetBatchHMI = ON;
                            break; 
             }
            break; 
            
        // Assign entered text to database variables
        case EVENT_TYPE_TEXT_ENTERED:   
             switch (value)
             { 
                case REPORT_BATCHNAME_INPUT: Batch.Name =  args[0]; 
                                        RefreshReportScreen(SCREEN_BATCH);
                                      break;
                case REPORT_BATCHPRESET_INPUT: Batch.Preset = int(args[0]); 
                                        RefreshReportScreen(SCREEN_BATCH);
                                      break;
                case REPORT_BATCHDETAILS_INPUT: Batch.Details = args[0]; 
                                        RefreshReportScreen(SCREEN_BATCH);
                                      break;
                                                            
             }
          SaveBatchFlag = Execute;   
        break;
        
        // Assign selected variable from combobox to database
        case EVENT_TYPE_ONOFFBOX_CHANGED :   
           
            Batch.CountAll = Arg2Bool(args[0]);
            SaveBatchFlag = Execute;
            PreSave_DataNoResetFlag = Execute;
           break;
      
        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                       
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_SMALL);
                       RefreshReportScreen (Current_Screen);
         break;      
      }
 
    }
    else
      DisplayHandling ();
      TimeoutUser();
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }    
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       GOTO APPLICATION                                                  */
/*                                                                         */
/* *********************************************************************** */
                              
int ApplicationGoTo (void)
{
int     class, type, value;
string  args[4][255];

  // ##### Page init #####
  SelectAndWaitPage(PAGE_GOTO);
 
  if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);    
  if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  RefreshGoToScreen ();                      
  
    for(;;)
    {
      if ( eventreceived() )
      {
        ResetTouchScreenTimeout();
        Controller = eventreceived();
        Permission = Check_Permission();
        readevent (class, type, value, args); 
        switch (type)
        {
               // Button events
          case EVENT_TYPE_BUTTON_PRESS:   
               switch (value)
               { 
                  case LOGO_BOX :
                                WeightDisplayInfo(No_Forcing);
                                return (SCREEN_INFO);
                              break;
                  
                  case FAULT_BOX :       
                                WeightDisplayInfo(No_Forcing);
                                return (SCREEN_FAULT);
                              break;       
                                        
                  case MODE_BOX :  
                                WeightDisplayFull(No_Forcing);
                                return (SCREEN_AUTOMATIC);                
                              break;     
                                               
                  case NAV_FCT_BUTTON_1 :
                                WeightDisplayFull(No_Forcing);
                                return (SCREEN_AUTOMATIC);
                              break;
                              
                  case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                    
                                WeightDisplayInfo(No_Forcing);
                                return (SCREEN_RECIPE1);
                            }  
                              break;
                              
                  case NAV_FCT_BUTTON_3 : 
                                WeightDisplaySmall(No_Forcing);
                                return (SCREEN_REPORT);
                              break;
                              
//                  case NAV_FCT_BUTTON_4 :
//                                WeightDisplaySmall(No_Forcing);
//                                return (SCREEN_GOTO);
//                              break; 
  
                  case NAV_FCT_BUTTON_5 : // Fault reset
                               FaultReset();
                              break;
                                                   
                  case NAV_FCT_BUTTON_6 : // Batch report page
                             WeightDisplayInfo(No_Forcing);
                             SelectAndWaitPage(PAGE_BATCH);
                             Current_Screen = SCREEN_BATCH;
                             if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
                             if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
                             widget_enable     (NAV_FCT_BUTTON_7,ON);
                             RefreshReportScreen(Current_Screen);
                             return (SCREEN_BATCH);
                             break;
                                                          
  //                case NAV_FCT_BUTTON_7 :  // not used 
  //                            break;   
                                      
  //                case NAV_FCT_BUTTON_8 :  // not used 
  //                            break;  
                                         
  //                case NAV_FCT_BUTTON_9 :  // not used 
  //                            break; 
                                         
  //                case NAV_FCT_BUTTON_10 : // not used
  //                            break; 
                  case GOTO_PAGE_BUTTON_1 :
                              if(GotoPageButton[1])
                                {   
                                 WeightDisplayInfo(No_Forcing);
                                 return (SCREEN_IOCFG_IN1);
                                } 
                              break;
                              
                  case GOTO_PAGE_BUTTON_2 :
                                WeightDisplayInfo(No_Forcing);
                                return (SCREEN_FAULT);
                              break;
                  case GOTO_PAGE_BUTTON_3 :
                                WeightDisplayInfo(No_Forcing);
                                return (SCREEN_INFO);
                              break;
                              
                  case GOTO_PAGE_BUTTON_4 :
                               if(GotoPageButton[4])
                                {
                                 WeightDisplayInfo(No_Forcing);
                                 return (SCREEN_IOTEST_IN1);
                                } 
                              break;
  
                  case GOTO_PAGE_BUTTON_5 :
                               if(GotoPageButton[5])
                                {
                                 WeightDisplayInfo(No_Forcing);
                                 return (SCREEN_MC1);
                                }
                              break;
                              
                  case GOTO_PAGE_BUTTON_6 :
                               if(GotoPageButton[6])
                                { 
                                 WeightDisplayInfo(No_Forcing);
                                 return (SCREEN_MP1);
                                } 
                              break;
  
                  case GOTO_PAGE_BUTTON_7 :
                                WeightDisplaySmall(No_Forcing);
                                return (SCREEN_ACCESS);
                              break;
                              
  //                case GOTO_PAGE_BUTTON_8 :
  //                              return (SCREEN_RECIPE1);
  //                            break;
              
                  case GOTO_PAGE_BUTTON_9 :
                                if(GotoPageButton[9])
                                {
                                 WeightDisplayInfo(No_Forcing);
                                 return (SCREEN_FLEXIO_1);
                                } 
                              break;
                              
                  case GOTO_PAGE_BUTTON_10 :
                               if(GotoPageButton[10])
                               { 
                                WeightDisplaySmall(No_Forcing);
                                return (SCREEN_WPMANAGECOPY);
                               } 
                              break;
  
  //                case GOTO_FCT_BUTTON_1 :
  
  //                            break;
  
  
                  case GOTO_FCT_BUTTON_2 :
                                if (Permission)
                                CheckWeightHMI = ON;
                              break;
                  
  //                case GOTO_FCT_BUTTON_3 :
  //                              return (SCREEN_RECIPE1);
  //                            break;            
  
 
                  case GOTO_FCT_BUTTON_4 :
                                if (Permission)
                                AutoTuneHMI = ON; 
                              break;

  //                case GOTO_FCT_BUTTON_5 :
  //                              return (SCREEN_RECIPE1);
  //                            break;
   
 
                  case GOTO_FCT_BUTTON_6 :
                                if (Permission)
                                {
                                  LanguageSelection (); 
                                  RefreshLanguage(SCREEN_GOTO);
                                }
                              break;

  //                case GOTO_FCT_BUTTON_7 :
  //                              return (SCREEN_RECIPE1);
  //                            break;
   
                  case GOTO_FCT_BUTTON_8 :
                                LowLevelResetMode();
                              break;
  
  //                case GOTO_FCT_BUTTON_9 :
  //                              return (SCREEN_RECIPE1);
  //                            break;
  
                  case GOTO_FCT_BUTTON_10 :
                                YesNoPopupMessage (TX_CONFIRM_LOAD_DBS, SCREEN_UPLOAD_DBS, Current_Screen, NO_Db);
                              break;
               }
              break; 

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                       
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_SMALL);
                       RefreshGoToScreen ();
          break;      
        }
   
      }
      else
        DisplayHandling ();
        TimeoutUser();
      
      if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
      if (ForceScreen_Req)
      { 
        Force_Screen ();
        return (ForceScreen_ScrnNo);
      }
    }
 
}

/* *********************************************************************** */
/*                                                                         */
/*       WP Management                                                     */
/*                                                                         */
/* *********************************************************************** */
                              
int ApplicationWPManagement (void)
{
int     class, type, value;
string  args[4][255];

  // ##### Page init #####
  SelectAndWaitPage(PAGE_WPMANAGECOPY);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);    
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  WPManagePageClear ();
  RefreshWPManageScreen (Current_Screen); 
                        
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             {                 
                case WPMANAGE_COPYSRCE_SEARCH_ID :

                              Current_Screen = SCREEN_WP_LIST_POPUP;
                              WP_CopySrce_No = ShowDbaseRecipeList(WPManage_List,RebuildWPList);
                              
                             if(WP_CopySrce_No != NOSELECTION)
                             { 
                              WPdb.No = WP_CopySrce_No;
                              find_db (WP_Db);
                              WP_CopySrce_String = WPdb.Name;
                              WPdb.No = MemRecipe;
                              LoadDb2WP();
                             }
                              
                              SelectAndWaitPage(PAGE_WPMANAGECOPY);
                              Current_Screen = SCREEN_WPMANAGECOPY;     
                              if(WP_CopySrce_No != NOSELECTION) widget_text (WPMANAGE_COPYSRCE_SEARCH_ID, trim(concat (string(WP_CopySrce_No), ":", space(1), WP_CopySrce_String)));        
                            break;
                            
                case WPMANAGE_COPYDEST_SEARCH_ID :

                              WP_CopyDest_No = ShowDbaseRecipeList(WPManage_List,RebuildWPList);
                              
                             if(WP_CopyDest_No != NOSELECTION)
                             { 
                              WPdb.No = WP_CopyDest_No;
                              find_db (WP_Db);
                              WP_CopyDest_String = WPdb.Name;
                              WPdb.No = MemRecipe;
                              LoadDb2WP();
                             } 
                              
                              SelectAndWaitPage(PAGE_WPMANAGECOPY);
                              Current_Screen = SCREEN_WPMANAGECOPY;     
                              if(WP_CopyDest_No != NOSELECTION) widget_text (WPMANAGE_COPYDEST_SEARCH_ID, trim(concat (string(WP_CopyDest_No), ":", space(1), WP_CopyDest_String)));    
                            break;            
                
                case WPMANAGE_RENSRCE_SEARCH_ID :

                              WP_Rename_No = ShowDbaseRecipeList(WPManage_List,RebuildWPList);
                                                           
                             if(WP_Rename_No != NOSELECTION)
                             { 
                              WPdb.No = WP_Rename_No;
                              find_db (WP_Db);
                              WP_Rename_String = WPdb.Name;
                              WPdb.No = MemRecipe;
                              LoadDb2WP();
                             } 
                              
                              SelectAndWaitPage(PAGE_WPMANAGERENAME);
                              Current_Screen = SCREEN_WPMANAGERENAME;     
                              if(WP_Rename_No != NOSELECTION) widget_text (WPMANAGE_RENSRCE_SEARCH_ID, trim(concat (string(WP_Rename_No), ":", space(1), WP_Rename_String)));     
                            break;
                
                case WPMANAGE_DELETE_SEARCH_ID :

                              WP_Delete_No = ShowDbaseRecipeList(WPManage_List,RebuildWPList);
                              
                             if(WP_Delete_No != NOSELECTION)
                             { 
                              WPdb.No = WP_Delete_No;
                              find_db (WP_Db);
                              WP_Delete_String = WPdb.Name;
                              WPdb.No = MemRecipe;
                              LoadDb2WP();
                             }
                              
                              SelectAndWaitPage(PAGE_WPMANAGEDELETE);
                              Current_Screen = SCREEN_WPMANAGEDELETE;     
                              if(WP_Delete_No != NOSELECTION) widget_text (WPMANAGE_DELETE_SEARCH_ID, trim(concat (string(WP_Delete_No), ":", space(1), WP_Delete_String)));     
                            break;
                
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO);
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }  
                            break;
                            
                case NAV_FCT_BUTTON_3 : 
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 

                case NAV_FCT_BUTTON_5 : // Fault reset
                             FaultReset();
                            break;
                                                 
                case NAV_FCT_BUTTON_6 : // WP Copy Page
                             SelectAndWaitPage(PAGE_WPMANAGECOPY);
                             Current_Screen = SCREEN_WPMANAGECOPY;
                             if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
                             if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
                             RefreshWPManageScreen (Current_Screen);
                            break;
                                                        
                case NAV_FCT_BUTTON_7 :  // WP Rename Page
                             SelectAndWaitPage(PAGE_WPMANAGERENAME);
                             Current_Screen = SCREEN_WPMANAGERENAME;
                             if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
                             if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
                             RefreshWPManageScreen (Current_Screen);
                            break;   
                                    
                case NAV_FCT_BUTTON_8 :  // WP Delete Page
                             SelectAndWaitPage(PAGE_WPMANAGEDELETE);
                             Current_Screen = SCREEN_WPMANAGEDELETE;
                             if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
                             if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
                             RefreshWPManageScreen (Current_Screen);
                            break;  
                                       
//                case NAV_FCT_BUTTON_9 :  // not used 
//                            break; 
                                       
//                case NAV_FCT_BUTTON_10 : // not used 
//                            break; 
                case WPMANAGE_RENAME_BUTTON :
                              YesNoPopupMessage(lsub(TX_RENAME_WPMANAGE), SCREEN_WPMANAGE, Current_Screen, WP_Db);
                            break;
                            
                case WPMANAGE_COPY_BUTTON :
                              YesNoPopupMessage(lsub(TX_COPY_WPMANAGE), SCREEN_WPMANAGE, Current_Screen, WP_Db);
                            break;
                case WPMANAGE_DELETE_BUTTON :
                              YesNoPopupMessage(lsub(TX_DELETE_WPMANAGE), SCREEN_WPMANAGE, Current_Screen, WP_Db);
                            
                            break;
                            
//                case WPMANAGE_PAGE_BUTTON_4 :
//                               return (SCREEN_IOTEST_IN1);
//                            break;

             }
          break;  
      
        case EVENT_TYPE_TEXT_ENTERED:  
                              WP_Rename_String = string (args[0]);                              
                              widget_text (WPMANAGE_RENNEW_SEARCH_ID, trim(concat (string(WP_Rename_No), ":", space(1), WP_Rename_String)));
          break;                                   
                                      

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                       
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_SMALL);
                       RefreshWPManageScreen (Current_Screen); 
          break;
        break;
                                                                           
      }
 
    }
    else 
    {	
      DisplayHandling ();
    }  
      TimeoutUser();
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen); 
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    } 
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       ACCESS APPLICATION                                                */
/*                                                                         */
/* *********************************************************************** */
                              
int ApplicationAccess (void)
{
int     class, type, value, i;
string  TempUser[24];
string  args[4][255];

  // ##### Page init #####
  SelectAndWaitPage(PAGE_ACCESS);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);  
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
  RefreshAccessScreen(OFF);       
  
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             { 
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO);
                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }  
                            break;
                            
                case NAV_FCT_BUTTON_3 : 
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 

                case NAV_FCT_BUTTON_5 : // Fault reset
                             FaultReset();
                            break;
                                                 
//                case NAV_FCT_BUTTON_6 : // not used 
                             
//                            break;
                                                        
//                case NAV_FCT_BUTTON_7 :  // not used 
//                            break;   
                                    
//                case NAV_FCT_BUTTON_8 :  // not used 
//                            break;  
                                       
//                case NAV_FCT_BUTTON_9 :  // not used 
//                            break; 
                                       
//                case NAV_FCT_BUTTON_10 : // not used 
//                            break; 

                case ACCESS_BUTTON_1 :  
                       if(AccessOK)
                       { 
                        Login();
                        RefreshAccessScreen(OFF);
                       } 
                       else
                       { 
                        Logout(SCREEN_ACCESS);
                        RefreshAccessScreen(OFF);
                       } 
                       break;
             }
             break;
             
        case EVENT_TYPE_COMBOBOX_ACTIVATED: // User Name Box
                   Test_No = decimal (args[0]);
                   Test_No = Test_No - 1;
               
             break;

        case EVENT_TYPE_TEXT_ENTERED: // PassWord box
                   Test_PW = int (args[0]); 
               
             break;

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                       
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshAccessScreen(OFF);
            break;
      }
 
    }
    else
      DisplayHandling ();
      TimeoutUser();
      if(date[MM] != MinuteInAccess) RefreshAccessScreen(ON);
      

    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }    
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       INFO APPLICATION                                                */
/*                                                                         */
/* *********************************************************************** */
                              
int ApplicationInfo (void)
{
int     class, type, value;
string  args[4][255];

  // ##### Page init #####
  SelectAndWaitPage(PAGE_INFO);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
   RefreshInfoScreen();  
  
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             { 
//                case LOGO_BOX :
//                              WeightDisplayInfo(No_Forcing);
//                              return (SCREEN_INFO); 
//                            break;
                
                case FAULT_BOX :       
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_FAULT);
                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }
                            break;
                            
                case NAV_FCT_BUTTON_3 : 
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 

                case NAV_FCT_BUTTON_5 : // Fault reset
                             FaultReset();
                            break;
                                                 
//                case NAV_FCT_BUTTON_6 : // not used 
                   
//                            break;
                                                        
//                case NAV_FCT_BUTTON_7 :  // not used 
//                            break;   
                                    
//                case NAV_FCT_BUTTON_8 :  // not used 
//                            break;  
                                       
//                case NAV_FCT_BUTTON_9 :  // not used 
//                            break; 
                                       
//                case NAV_FCT_BUTTON_10 : // not used 
//                            break; 

             }
          break;

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                       
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       RefreshInfoScreen();
            break;
      }  
   
    }
    else
      DisplayHandling ();
    TimeoutUser();
    
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }    
  }
}

/* *********************************************************************** */
/*                                                                         */
/*       FAULT APPLICATION                                                 */
/*                                                                         */
/* *********************************************************************** */
                              
int ApplicationFault (void)
{
int     class, type, value;
string  args[4][255];

  // ##### Page init #####
  SelectAndWaitPage(PAGE_FAULT);
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);   
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);   
FltLine_Pointer = 0;
FS_Flt = ON;
RefreshFaultScreenReq();  
  
  for(;;)
  {
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      readevent (class, type, value, args); 
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:   
             switch (value)
             { 
                case LOGO_BOX :
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_INFO); 
                            break;
                
//                case FAULT_BOX :       
//                              WeightDisplayInfo(No_Forcing);
//                              return (SCREEN_FAULT);
//                            break;       
                                      
                case MODE_BOX :  
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);                
                            break;     
                                             
                case NAV_FCT_BUTTON_1 :
                              WeightDisplayFull(No_Forcing);
                              return (SCREEN_AUTOMATIC);
                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }  
                            break;
                            
                case NAV_FCT_BUTTON_3 : 
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break; 

                case NAV_FCT_BUTTON_5 : // Fault reset
                             FaultReset();
                            break;
                                                 
//                case NAV_FCT_BUTTON_6 : // not used 
                             
//                            break;
                                                        
                case NAV_FCT_BUTTON_7 :  // Fault Home Page
                            FltLine_Pointer = 0;
                            FS_Flt = ON;
                            break;   
                                    
                case NAV_FCT_BUTTON_8 :  // Fault Previous Page
                            FltLine_Pointer = FltLine_Pointer - 10;
                            if (FltLine_Pointer < 0) FltLine_Pointer = 0;
                            FS_Flt = ON;
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :  // Fault Next Page 
                            FltLine_Pointer = FltLine_Pointer + 10;
                            if (FltLine_Pointer > 90) FltLine_Pointer = 90;
                            FS_Flt = ON;
                            break; 
                                       
                case NAV_FCT_BUTTON_10 : // Fault Last Page
                            FltLine_Pointer = 90;
                            FS_Flt = ON;
                            break; 

             }
          break;

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                       
                       RefreshRemoteDisplay(WEIGHT_DISPLAY_INFO);
                       FS_Flt = ON;
                       RefreshFaultScreenReq();
            break;
      }

    }
    else
      DisplayHandling ();
    TimeoutUser();
    
//    if (Fault_Refresh_MEM != Fault_Refresh) 
    RefreshFaultScreenReq();
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }    
  }
}

/* *********************************************************************** */
/*                                                                         */
/*      SMALL AUTOMATIC APPLICATION                                        */
/*                                                                         */
/* *********************************************************************** */
int ApplicationAutomatic (void)
{
int      class, type, value;
string   args[4][255],ContinueUnit[255];
int      err;
bool     SMlocked;

  //##### Page init #####     
  SelectAndWaitPage(PAGE_AUTO);
  
//ButtonDisplayRefreshed[Current_Screen]= OFF; 
if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);       
if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);

  AutoPage_FS = ON;
  RT_AutoPage = ON;
  
  RefreshAutoScreen(ON);
  Msg_Display_Refresh();

  for(;;)
  {  
  
    if ( eventreceived() )
    {
      ResetTouchScreenTimeout();
      Controller = eventreceived();
      Permission = Check_Permission();
      readevent (class, type, value, args);
      if(SMlocked)
       {
        SMlocked = OFF;
        infobox ("");
       }
       
      switch (type)
      {
             // Button events
        case EVENT_TYPE_BUTTON_PRESS:
             
             switch (value)
             { 
               case LOGO_BOX :
                                WeightDisplayInfo(No_Forcing);
                                return (SCREEN_INFO);                    
                            break;
               
               case ACTIVE_RECIPE_ID :
                             if (Permission)
                             {
                               WeightDisplayInfo(No_Forcing);
                               Change_Recipe(SCREEN_WP_LIST_POPUP,PAGE_AUTO,MemRecipe,Current_Screen,List_Page);
                               RefreshAutoScreen(OFF);
                               RefreshRecipeInAutoScreen();
                               
                             }  
                           break;
                                                
                case FAULT_BOX :
                             WeightDisplayInfo(No_Forcing);
                             return (SCREEN_FAULT);
                            
                           break;       
                                      
                case MODE_BOX :  // If User Logged high enough; display Stats Data Popup   
                             //if (CurrentLevel >= Level_SUP && CurrentLevel != Level_None)
                             //  ProdDataPopup();
                             //else  
                             // { 
                                WeightDisplaySmall(No_Forcing);
                                return (SCREEN_ACCESS);
                             // } 
                           break;     
                                             
                case NAV_FCT_BUTTON_1 : 

                            break;
                            
                case NAV_FCT_BUTTON_2 :
                           if(RecipeButton)
                            {                  
                              WeightDisplayInfo(No_Forcing);
                              return (SCREEN_RECIPE1);
                            }  
                            break;
                            
                case NAV_FCT_BUTTON_3 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_REPORT);
                            break;
                            
                case NAV_FCT_BUTTON_4 :
                              WeightDisplaySmall(No_Forcing);
                              return (SCREEN_GOTO);
                            break;

                case NAV_FCT_BUTTON_5 : // Fault reset
                             FaultReset();
                            break;
                                                 
                case NAV_FCT_BUTTON_6 : // Discharge 
                              if (Permission)
                               DischargeHMI = ON;
                            break;
                                                        
                case NAV_FCT_BUTTON_7 : // Reset automatic mode
                              if (Permission)
                              {
                                OffRequest = ON;
                                YesNoPopupMessage(lsub(TX_CONFIRM_OFF), SCREEN_AUTOMATIC, NIL, NO_Db);
                              }  
                            break;   
                                    
                case NAV_FCT_BUTTON_8 : // Hopper control
                              if (Permission)
                              HopperHMI = ON;  
                            break;  
                                       
                case NAV_FCT_BUTTON_9 :
                              if (Permission)
                              {
                               if(Start_PauseBtn == StartBtn)
                               {
                                if(SeqModeManager == stp_OFF_MODE || SeqModeManager == stp_STOP_MODE || ManualModeStep == stp_ManualOkToDisch)
                                 if(WP.WeighmentsPerUnit > 1 && WeighPerUnitAcc > 0)
                                 {
                                  ContinueUnit = concat(lsub(TX_WEIGHS_PER_UNIT_ID),space(2),trim(WeighPerUnitAcc),"/",trim(WP.WeighmentsPerUnit),"\n",lsub(TX_CONTINUEUNIT));
                                  ContinueUnitFlag = ON;
                                  YesNoPopupMessage(ContinueUnit,SCREEN_AUTOMATIC, NIL, NO_Db);
                                 } 
                                StartHMI = ON;
                                ContinueUnitFlag = OFF; 
                               }
                               
                               if(Start_PauseBtn == PauseBtn)
                               { 
                                 PauseHMI = ON;
                               }
                              } 
                                                               
                            break;
                                       
                case NAV_FCT_BUTTON_10 :
                              if (Permission)
                              StopHMI =ON;                               
                            break;
             }
           break;
           


        case EVENT_TYPE_MONITOR_FUNCTION:
                       
                       infobox(TX_SM_INFOBOX);
                       SMlocked = ON;
           break;

        case EVENT_TYPE_CONNECTION_ESTABLISHED:   
                              
                               RefreshRemoteDisplay(WEIGHT_DISPLAY_FULL);
                               Message_DisplayFlag = Execute;
                               RefreshAutoScreenReq ();
           break;
      }
 
    }
    else
      {
       if(IsCleanoutDone)
        {
         YesNoPopupMessage(concat(lsub(TX_CLEANOUTCOMPLETED),"?"), SCREEN_AUTOMATIC, NIL, NO_Db);
        }
        
       else if(PopConfirmLoad)
        {
         YesNoPopupMessage (TX_CONFIRM_LOAD_DBS, SCREEN_UPLOAD_DBS, Current_Screen, NO_Db);  
         PopConfirmLoad = OFF;
        }   
        
       else
        DisplayHandling();
      } 
    
    
      TimeoutUser();
      
      if(SampledInPause)
       { 
        widget_text(HIRESWEIGHT,   concat(adj(NetWeightHiRes[Scale1],6,dp+1),space(1),WP.Unit,space(1)));
       }
      else   
       { 
        widget_text(HIRESWEIGHT,"");
       }
      
       
    if (!ButtonDisplayRefreshed[Current_Screen])  ButtonDisplayControl(Current_Screen);
    if (ForceScreen_Req)
    { 
      Force_Screen ();
      return (ForceScreen_ScrnNo);
    }


  }
}


/* *********************************************************************** */
/*                                                                         */
/*      MAIN Application                                                   */
/*                                                                         */
/* *********************************************************************** */

void MainApplication (void)
{
  
  #ifndef __SIMULATION__ 
   hide_startup_message();
   RegistrationCheck();
  #endif 
  
  dropevents();
  Current_Screen = SCREEN_AUTOMATIC;
  WeightDisplayFull(No_Forcing);
  mode_step_MEM    = -1;
  Fault_Status_MEM = -1; 
  
  // ##### Assigned target weight only for test 
  
  //#ifndef __SIMULATION__ 
  //  hide_startup_message ();
  //#endif 
  
  for(;;)
  {
    switch ( Current_Screen )
    {
                     
      case SCREEN_AUTOMATIC : 
                       Current_Screen = ApplicationAutomatic();
                     break; 
                                            
      case SCREEN_RECIPE1 : 
                       Current_Screen = ApplicationRecipe();
                     break;
                              
      case SCREEN_REPORT : 
                       Current_Screen = ApplicationReport(ON);
                     break;
                      
      case SCREEN_BATCH : 
                       Current_Screen = ApplicationReport(OFF);
                     break; 
                                     
      case SCREEN_GOTO : 
                       Current_Screen = ApplicationGoTo();
                     break;

      case SCREEN_WPMANAGECOPY : 
                       Current_Screen = ApplicationWPManagement();
                     break;                     
        
      case SCREEN_ACCESS : 
                       Current_Screen = ApplicationAccess();
                     break;
      
      case SCREEN_INFO : 
                       Current_Screen = ApplicationInfo();
                     break;               
                     
      case SCREEN_FAULT :
                       Current_Screen = ApplicationFault();
                     break; 
                    
      case SCREEN_IOCFG_IN1 :
                       Current_Screen = ApplicationIOConfig();
                     break; 
                
      case SCREEN_IOTEST_IN1 :
                       Current_Screen = ApplicationIOTest();
                     break;                                    

      case SCREEN_MP1 :
                       Current_Screen = ApplicationMP();
                     break;

      case SCREEN_MC1 :
                       Current_Screen = ApplicationMC();
                     break;

      case SCREEN_FLEXIO_1 :
                       Current_Screen = ApplicationFlexIO();
                     break;
                                                          
      default :        Current_Screen = ApplicationAutomatic();  
                     break;                                                          
    }
   
   
  }
  
  if(FirstScan) FirstScan = OFF;
}  


/* *********************************************************************** */
/*                                                                         */
/*       Init                                                              */
/* *********************************************************************** */
void Init (void)
{
int i;
bool err;

  FirstScan = ON;   
  #ifndef __SIMULATION__ 
    iQShowStartupMessage(concat(space(1),lsub(TX_STARTING),"..."));
    delay(0.1);
  #endif 
  
  
  InitVarMain();   
  
  setpassword("2234");
  KeyLockPTSZI(OFF,OFF,ON,OFF,ON);
  
  
  err = flashload();
  CreateLanguageDb();
 
  
   
  LoadIONamesEnglish();  //must stay before language switching                                                   
  if (MemLanguage <0 || MemLanguage >= MAX_LANG) MemLanguage = 0;
  writeparameter ("General","Language",concat(trim(string(MemLanguage)))); 
  LangValue = readparameter("General","Language");
  if (LangValue <0 || LangValue >= MAX_LANG) LangValue = 0; 
  MemLanguage = LangValue;
  Language_Cnt = MemLanguage_Cnt;
  if (Language_Cnt==4) Language_Cnt=1;
  
  ScaleManagement();
  
  AnalogIOCheck();
  
  IP_Address = readparameter("Network","IP");

  
  
  writeparameter ("General","LightOffTime",concat(trim(string(MP.ScreenSaverTime)))); 
  MaxNumbOfIO = ReadMaxNumbOfIO();
  
  AccessTimer_ON    = OFF;
  TouchScreenTimerEnable = OFF;
  fscan             = ON;  

  Clear_LangRefreshed();
  Clear_ButtonControlRefreshed();
  
  InitDBs();
  
  #if defined LAYOUT_TEST
  BackgroundColor = "blue";
  #else
  BackgroundColor = "white";
  #endif
     
  // record all commands that are issued to create pages in order
  // to send those commands automatically to externally connected
  // monitors on connection establishment
  recorddisplay // All display commands are memorized in a buffer. Useful for multiple display monitors ex: On a PC.
  {
    CreateRecipePages();
    CreateTimeDateManagePage();
    CreateReportPage();
    CreateBatchReportPage();
    CreateGoToPage();
    CreateAccessPage();
    CreateInfoPage();
    CreateFaultPage();
    CreateYesNoPopupBox();
    CreateConfirmPopupBox();
    CreateProdDataPopupBox();
    CreateWeighingDataPopupBox();
    CreateIOConfigPages();
    CreateIOTestPages();
    CreateLanguageListPage();
    CreateAnalogTestPage();
    CreateMPPages();
    CreateMCPages();
    CreateWPManageCopyPage();
    CreateWPManageRenamePage();
    CreateWPManageDeletePage();
    CreateFlexIOPages();
    CreateRegistrationPage();
    CreateAutoScreen();    
  }         
  dropevents();
  
  DisplayOptions();
  
  ReadServiceMode();
  //CheckPBZeroValues("1",PBZeroPlus1);
  //CheckPBZeroValues("2",PBZeroPlus2);
  FieldBusDetect();
  
  ContOutInitOK = CheckContOut(MC.PortCOM2Cfg,MC.PortETHCfg);
  
  // Variable initialization 
  OffRequest    = OFF;
  mode_step     = 0;
  Fault_Status  = 0;
  tmpBTN1  = "";
  tmpBTN2  = "";
  tmpBTN3  = "";
  tmpBTN4  = "";
  tmpBTN5  = "";
  tmpBTN6  = "";
  tmpBTN7  = "";
  tmpBTN8  = "";
  tmpBTN9  = "";
  tmpBTN10 = "";
  
  for (i=0; i<BTN_NUMB; i++)
  {
   tmpBTN[i] = "";
   BTN[i] = "";
  }

  ResetUserLogin();

// "Disable User Login"
#if defined LOGIN_DEBUG
  CurrentLevel = Level_PT;
  UserForced = ON;
  KeyLockPTSZI(LAST,LAST,ON,LAST,OFF);
#else
  UserForced = OFF;
#endif

 ServiceModeControl(MONITOR_FUNCTION_ENABLE_ALL_FUNCTIONS);

// "Disable User Login"
#if defined BYPASS_SERVICEMODE_RESTART
BypassSMRestart = ON;
#else
BypassSMRestart = OFF;
#endif

#if defined __SIMULATION__
BypassSMRestart = ON;
Simul = ON;
#else
BypassSMRestart = OFF;
Simul = OFF;
#endif

  fscan       = OFF;
  AutoPage_FS = ON;

#ifdef FIFO_PERSISTENT
  
  if (fifo_used (FIFO_UNITREC_SHARED) + fifo_free (FIFO_UNITREC_SHARED) == 0)
  {
    // fifo has zero size, so it needs to be initialized for the first time
    fifo_init (FIFO_UNITREC_SHARED, FIFO_UNITREC_SIZE, true); //true = persistent
  }
  
  if (fifo_used (FIFO_UNITREC_USB) + fifo_free (FIFO_UNITREC_USB) == 0)
  {
    // fifo has zero size, so it needs to be initialized for the first time
    fifo_init (FIFO_UNITREC_USB, FIFO_UNITREC_SIZE, true); //true = persistent
  }
#else
  fifo_init (FIFO_UNITREC_SHARED, FIFO_UNITREC_SIZE, false);
  fifo_init (FIFO_UNITREC_USB,    FIFO_UNITREC_SIZE, false);
#endif


 /* Start printing task */
   taskid_print = starttask (PrintTask); 
   //setpriority (taskid_print, 5);

  
#ifdef USE_INTERRUPT  
  /*
    If the execution of more than 10 subsequent cycles of the FillingTask
    needs each more time than the requested cycle time, the application is
    aborted. The interrupt task runs at real time priority and the system
    would freeze completely otherwise.
    Therefore, the FillingTask must not contain any delays. 
    (Currently, "FindDb" contains a 50ms delay.)
  */

  startinterrupt(FillingTask, FillingTaskInterval); // Interval in ms cycle
#else
// Start background task
  taskid_filling = starttask( FillingTask );   
  
#endif
  setpriority (taskid_filling, 1);
      
  // Start Logic Operation task
  taskid_operation = starttask(LogicOperationTask);
  //setpriority (taskid_operation, 3);   
    
  msgsetfilter (concat(trim(MSG_SERVICE_MODE_ENTERED),";",trim(MSG_SERVICE_MODE_LEFT),";"));
  

}

/* *********************************************************************** */
/*                                                                         */
/*       Main                                                              */
/*                                                                         */
/* *********************************************************************** */


void main(void)
{
#if defined STRING2LONGTEST
writeparameter("System","Stoponstringtoolong","1"); // Used to disable the String too long Watcher. For test purposes only
#else 
writeparameter("System","Stoponstringtoolong","0"); // Used to disable the String too long Watcher. For test purposes only
#endif

  Init(); 

  MainApplication();
}
#else 
void main (void)
{
// version too old, so display message about
// minimum required firmware version
  infobox ("Version too old.\nPlease update firmware");
  for (;;) 
    delay (10.0);
}
#endif

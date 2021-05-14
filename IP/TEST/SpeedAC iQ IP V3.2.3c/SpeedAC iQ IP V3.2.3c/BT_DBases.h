
//Database Names
#define TX_DBWEIGHPROGRAM         "Weigh Program"
#define TX_DBMACHINECONFIG        "Machine Configuration"
#define TX_DBMACHINEPARAM         "Machine Parameters"


//Weigh Program Data base
dbase TX_DBWEIGHPROGRAM WPdb[WPdbSIZE]
{     
      int       No;                    selectmode=input;
      string    Name[WP_NAME_LENGTH];
      //WP Page1
      decimal   NominalWeight%6.2;
      decimal   Overfill%6.2;          
      decimal   Cutoff%6.2;
      decimal   BulkCutoff%6.2;
      decimal   DFTime%5.2;
      decimal   BFTime%5.2;
      decimal   UnderWeight%6.2;
      decimal   OverWeight%6.2;
      decimal   DischargeWeight%6.2;
      decimal   DischargeTime%5.2;
      decimal   FeedDelayTime%5.2;
      decimal   WeighmentsPerUnit%5.0;
      //WP Page2 
      decimal   FeedRateLowLimit%10.2;
      decimal   FeedRateHighLimit%10.2;
      decimal   TargetWeightIP%10.2; 
      decimal   CleanOutWeightIP%10.2; 
      int       BulkModeIP;  
      decimal   PresetBatch%6.0; 
      decimal   PresetFeedRate1%10.2; 
      decimal   PresetFeedRate2%10.2;
      bool      VibratoryDischDoors;   //enum list ON-OFF
      bool      ZeroingOpen;           //enum list Door Open-Door Close
      int       SlowCycleEnd;          //enum list Dribble Feed-Hold Cycle-Cycle End
      string    ProductCode[24];
      //WP Page3
      decimal   TopUpOFFTime%5.2;
      decimal   TopUpONTime%5.2;
      decimal   PulseTotalWeight%10.2;  
      int       SiloNo;                 
      int       SiloDest;   
      decimal   PresetCycleTime%4.2;
      string    Unit[4];                //enum list kg-lb-oz
      int       FeedAlgoType;          //enum list Standard-iQSMARTFeed-iQFLASHFeed
      int       TransferSilo;
      bool      FlowThroughAfterCleanout;
      bool      BulkMode;
      decimal   DTF%5.2;
      //WP Page4
      decimal   FlexT1%5.2;
      decimal   FlexT2%5.2;
      decimal   FlexSP1%6.2;
      decimal   FlexSP2%6.2;
      int       ReportType;
      //Report Page
      int       ProdSiloNo;
      bool      CountAll;
      decimal   ProdUnderWeightCnt%6.0[2];
      decimal   ProdOverWeightCnt%6.0[2];
      decimal   ProdTotalUnitsCnt%6.0[2];
      double    ProdTotalWeight;  //SADM2 2020 NOVEMBER
      decimal   FlexCounter%6.0;
      //Remain from Net
      int       EnabledScale;          //enum list 1Only-2Only-1And2  
      decimal   CatchGateDelay%5.2;      
      decimal   MinFeeding%6.2;        //%
      decimal   MaxFeeding%6.2;        //%
      decimal   RegMinFeeding%6.2;     //%
      decimal   RegMaxFeeding%6.2;     //%
      decimal   ActuatorPos%6.2;       //% 
      string    CPSmFastAvgPoints[2][63];
      string    CPSmSlowAvgPoints[2][63];
      string    CPSmSlowItpPoints[8][63];
      float     CPSmSwitchTime;
      string    CPFlFastPoints[2][63];
      string    CPFlDeviationPoints[4][63];
}

/**************************************************************************** 
  WP Name list
*****************************************************************************/
dbase  WPNameList[MAX_WP]
{
    int       No;                    selectmode=input;
    string    Name[WP_NAME_LENGTH];
    decimal   NominalWeight%6.2;
    string    Unit[4];
}

/*********************************************** */
/*                                               */
/*  Text definitions moved to Language.h file    */
/*                                               */
/* ********************************************* */


//Machine Config Data base
dbase TX_DBMACHINECONFIG MCdb[MAX_MC]
{
      int     No;                         selectmode=input;
      string  Name[24];      
      //MC Page1
      int     WeighingMode;               //enum list weighing mode //after modification added by namk 18/9/2018
      decimal BulkBlankT%4.2;
      decimal DribBlankT%4.2;
      decimal LowLevelDebounceT%4.2;
      decimal RefillingTimeT%5.2;        
      int     NumberOfWP;
      int     FeederType;                 //enum list all feeders
      int     NumberOfScale;
      int     Language1;                  
      string  Lang1Text[24];                  
      int     Language2;                  
      string  Lang2Text[24];
      int     Language3;                  
      string  Lang3Text[24];
      bool    OIML;                     //enum list yes-no
      //MC Page2
      int     PortCOM2Cfg;    
      int     PortUSBCfg;
      bool    AutoSaveCorrection;         //enum list yes-no
      decimal DischReqDebouncing%4.2;
      int     PortETHCfg;
      string  PrinterIP[15];              //IP address of printer xxx.xxx.xxx.xxx
      bool    DischOnDoorSensor;          //enum list yes-no
      bool    DribbleOutOnInBulk;         //enum list ON-OFF
      string  SerialNbr[24];
      string  PlantLineName[24];
      string  CustomerName[24];
      string  CustomerLocation[24];    
      //MC Page3  
      string  SupportPhoneNbr[24];
      string  SupportFaxNbr[24];
      string  SupportEmail[24];
      string  PartsPhoneNbr[24];
      string  PartsFaxNbr[24];
      string  PartsEmail[24];
      string  iQVersion[30];
      int     TrialDays;
      bool    Mouse;  //OFF-ON //SADM2
}

//Machine Param Data base
dbase TX_DBMACHINEPARAM MPdb[MAX_MP]
{
      int     No;                   selectmode=input;
      string  Name[24];    
      //MP Page1
      int     SampleFreq%7.0;
      int     SampleSize%7.0;
      int     ZeroFreq%7.0;
      decimal ZeroLimit%3.1;      //%
      bool    AutoZeroOff;           //enum list yes-no
      int     ScreenSaverTime;
      decimal DischDoorMaxTime%5.2;
      decimal SlowCycleTime%5.2;
      decimal FeedGateMaxTime%5.2;
      decimal OutOfTolTime%7.2;
      decimal StabTimeLimit%5.2;
      decimal FeedRateFilterRatio%5.3;
      //MP Page2
      bool    CorrOnAverage;       //enum list yes-no
      int     CutoffCorrLimit%3.0;
      decimal CutoffCorr%6.2;
      decimal DFWeightCorr%3.1;
      decimal MaxFeedRate%10.2; 
      decimal LowFeedingTime%4.2; 
      int     StdFilterSize;
      decimal MaintCycle%6.0; 
      string  EndOfShift1[5];
      string  EndOfShift2[5];
      string  EndOfShift3[5];
      string  EndOfShift4[5];
      //MP Page3
      decimal FlexT1%5.2;
      decimal FlexT2%5.2;
      decimal FlexCounter%6.0;
      bool    InvertFeedAndDischOutputs;
      decimal FlexSP1%6.2;
      decimal FlexSP2%6.2;
      bool    FailSafe;   
      bool    StopWithGatesAndDischDoorOpen;        
}





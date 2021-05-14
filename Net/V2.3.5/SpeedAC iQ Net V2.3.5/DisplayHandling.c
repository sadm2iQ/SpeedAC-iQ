﻿

//Save Databases to USB on Power-Cycle
float SaveDBsToUSB(void)
{
 string path[32];
 int Begin = systemtimer_ms();
 bool SaveDbs;
  
  #if defined __SIMULATION__
   path = "internal";
  #else
   path = "usbstick";
  #endif
  
  #ifndef __SIMULATION__
   SaveDbs = ON;
   #elif defined SAVE_DBS_IN_SIMUL
    SaveDbs = ON;
  #else
    SaveDbs = OFF;
  #endif    
  
  if(SaveDbs)
  {
   if (dopen (DBsBACKUP,path))
   {
    save (IOdb,   concat(path,"/IOdb.csv"));
    save (FlexIO, concat(path,"/FlexIO.csv"));
    save (WPdb,   concat(path,"/WPdb.csv"));
    save (MCdb,   concat(path,"/MCdb.csv"));
    save (MPdb,   concat(path,"/MPdb.csv"));
    infobox ("");
   }
   else if(path == "usbstick")
    {
     infobox("USB device connection failed\nDatabases could not be saved!");
     delay(5);
     infobox ("");
    } 
  }  
 
 float elapsed = (systemtimer_ms() - Begin)/1000.0;
 
 return(elapsed);
}

//Load Databases From USB on Power-Cycle or Manually via Other Screen Button
float LoadDBsFromUSB(void)
{
 string path[32];
 int Begin = systemtimer_ms();
  
  #if defined __SIMULATION__
   path = "internal";
  #else
   path = "usbstick";
  #endif
  
  
   if (dopen (DBsBACKUP,path))
   {
    load (IOdb,   concat(path,"/IOdb.csv"));
    load (FlexIO, concat(path,"/FlexIO.csv"));
    load (WPdb,   concat(path,"/WPdb.csv"));
    load (MCdb,   concat(path,"/MCdb.csv"));
    load (MPdb,   concat(path,"/MPdb.csv"));
    
    infobox ("");
   }
  
 
 float elapsed = (systemtimer_ms() - Begin)/1000.0;
 
 return(elapsed);
}


//Analog IOs validation
void AnalogIOCheck(void)
{
  AOUTName[AOUT_NONE] = "";
  AOUTName[AOUT_MAI]  = "mai";
  AOUTName[AOUT_DAU8] = IQ_FEEDING_ANALOG_MODULE_DAU;
  AOUTName[AOUT_DAU15] = IQ_FEEDING_ANALOG_MODULE_DAU;
  AOUTName[AOUT_DAM] = IQ_FEEDING_ANALOG_MODULE_DAM;
  
  AOUTType[AIO1]  = readparameter("AOut1","Type");
  AOUTType[AIO2]  = readparameter("AOut2","Type");
  AOUTType[AIO3]  = readparameter("AOut3","Type");
  AOUTType[AIO4]  = readparameter("AOut4","Type");
  AOUTMode[AIO1]  = readparameter("AOut1","Mode");
  AOUTMode[AIO2]  = readparameter("AOut2","Mode");
  AOUTMode[AIO3]  = readparameter("AOut3","Mode");
  AOUTMode[AIO4]  = readparameter("AOut4","Mode");
  AOUTModul[AIO1] = readparameter("AOut1","Modul");
  AOUTModul[AIO2] = readparameter("AOut2","Modul");
  AOUTModul[AIO3] = readparameter("AOut3","Modul");
  AOUTModul[AIO4] = readparameter("AOut4","Modul");
  AOUTActive[AIO1] = Arg2Bool(AOUTType[AIO1]);
  AOUTActive[AIO2] = Arg2Bool(AOUTType[AIO2]) && AOUTActive[AIO1];
  AOUTActive[AIO3] = Arg2Bool(AOUTType[AIO3]) && AOUTActive[AIO2];
  AOUTActive[AIO4] = Arg2Bool(AOUTType[AIO4]) && AOUTActive[AIO3];
  
  AINType[AIO1] = readparameter("AIn1","Type");
  AINType[AIO2] = readparameter("AIn2","Type");
  AINActive[AIO1] = Arg2Bool(AINType[AIO1]);
  AINActive[AIO2] = Arg2Bool(AINType[AIO2]) && AINActive[AIO1];
}

/************************************************************/
/******************* Set Service Mode Access if needed*******/
/************************************************************/
void ServiceModeCheck(void)
{  
    if(ChangeSMStateFlag != Done && (T_Dn(T_FirstScan)||SMEntered))
    {
     if(SeqModeManager != stp_OFF_MODE)
      {
       ServiceModeControl(MONITOR_FUNCTION_SERVICE_MODE_ACCESS);  
      }
     if(SeqModeManager == stp_OFF_MODE)
      {
       if (CurrentLevel > Level_OP && !SMEntered) 
         ServiceModeControl(MONITOR_FUNCTION_ENABLE_ALL_FUNCTIONS);
       else 
         ServiceModeControl(MONITOR_FUNCTION_SERVICE_MODE_ACCESS);
      }
     CurrentLevelMem   = CurrentLevel;  
     ChangeSMStateFlag = Done;
    }
}   

/*------------------------------------------------------------------------- 
--  Procedure Name    : DisplayHandlingLogic
--  Created by        : Steve Santerre
--  Last modified on  : 2017/10/20
--  
--  Purpose           : Logic Always scan thru main task
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
void DisplayHandlingLogic(void)
{
 int ShownScale,ShowScale;
 int CMTimeLast,CMTimeCurrent,CMTimeElapsed;
 int SaveProdDataDuration,SaveProdDataBegin;
 int i;
    
    if (Message_DisplayFlag != Done)// && Current_Screen == SCREEN_AUTOMATIC)
    {
      if(!DisplayFault && MessageOutFault != "")
        {
          DisplayFault = ON;
        }
      
      if(DisplayFault && T_Dn(T_FaultDisplay))
       {
       DisplayFault = OFF;
       T_EnOff(T_FaultDisplay);
       }
      if(DisplayFault && !T_EN[T_FaultDisplay])
       T_EnOn(T_FaultDisplay);
      
      if(!DisplayFault && !T_Dn(T_FaultDisplay) && T_EN[T_FaultDisplay]) 
           BlockMessage = ON;
      else 
           BlockMessage = OFF;
           
      if(!BlockMessage)
      {
       if(DisplayFault)
        {
         MessageOut = MessageOutFault;
         Fault_NoOut = Fault_NoOutFault;
         MessageOutFault = "";
         Fault_NoOutFault = 0;
        }
       else
        {
         MessageOut = MessageOutStp;
         Fault_NoOut = Fault_NoOutStp;
         MessageOutStp = "";
         Fault_NoOutStp = 0;
        }  
       MessageDisplayOutput(MessageOut,Fault_NoOut);
       if(MessageOutFault == "" && MessageOutStp == "" && !DisplayFault) Message_DisplayFlag = Done;
      }
       
    }
	  
    else if(DisplayAlarmDelay)
    {
     T_EnOff(T_FaultDisplay);
     DisplayAlarmDelay = OFF;
    }
        
    if (Clear_ButtonControlRefreshedFlag != Done)
    {
    Clear_ButtonControlRefreshed();
    Clear_ButtonControlRefreshedFlag = Done;
    }

    if(CheckWeight_StateMem != CheckWeight_State)
    if (Current_Screen == SCREEN_GOTO)
    {

      switch (CheckWeight_State)
      {
         case ReleaseWeight:     widget_image (GOTO_FCT_BUTTON_2, BTN_RELWGT); 
                                 break;   
         case CheckAllWeight:    widget_image (GOTO_FCT_BUTTON_2, BTN_CHKWGT);
                                 break;    
         default :               widget_image (GOTO_FCT_BUTTON_2, BTN_RELWGT);
                                 break;   
      }
      CheckWeight_StateMem = CheckWeight_State;
    }

 
    if (AutoTuneStateFlag != Done)
    if (Current_Screen == SCREEN_GOTO)
    {
      switch (AutoTune_State)
      {
        case AutoTuneON:   widget_image (GOTO_FCT_BUTTON_4, BTN_AUTOTUNEON);          
                           break;                   
        case AutoTuneOFF:  widget_image (GOTO_FCT_BUTTON_4, BTN_AUTOTUNEDONE);         
                           break;
        default :          widget_image (GOTO_FCT_BUTTON_4, BTN_AUTOTUNEDONE);
                           break;                    
      }
     AutoTune_StateMEM = AutoTune_State;
     AutoTuneStateFlag = Done; 
    }
    
        
 
//Fault Reset  
    if (FaultResetFlag != Done)
    {  
      if(!T_EN[T_FaultDisplay])
      {
      FaultReset();
      FaultResetFlag = Done;
      }
    }
//Fault Handler  
    if (FaultHandlerFlag != Done)
    {  
      FaultHandlerOutput(Fault_NoOutput,Fault_TxtOutput);
      FaultHandlerFlag = Done;
    }
    
//Refresh Auto Screen 
    if (RefreshAutoScreenFlag != Done && Current_Screen == SCREEN_AUTOMATIC && T_Dn(T_FirstScan))
    {  
      RefreshAutoScreen(OFF);
      RefreshAutoScreenFlag = Done;
    }    

//Refresh Stats Data Popup 
    if (RefreshStatDataPopupFlag != Done && iQStatData_Popup == ON)
    {
      if (CurrentLevel > Level_SUP) 
      {  
       //Refresh Prod Data:
        widget_text  (PRODDATA_STRING1, iQStatData_String1);
        widget_text  (PRODDATA_STRING2, iQStatData_String2);
        widget_text  (PRODDATA_STRING3, iQStatData_String3);
        widget_text  (PRODDATA_STRING4, iQStatData_String4);
        widget_text  (PRODDATA_STRING5, iQStatData_String5);
        widget_text  (PRODDATA_STRING6, iQStatData_String6);
        widget_text  (PRODDATA_STRING7, iQStatData_String7);
        widget_text  (PRODDATA_STRING8, iQStatData_String8);  
        widget_text  (PRODDATA_STRING9, iQStatData_String9);
        RefreshStatDataPopupFlag = Done;
        iQStatData_PopupMEM = iQStatData_Popup;
      } 
    } 

 //Reset Weighing Data Popup 
     if (ResetWeighingDataPopupFlag != Done)
    {
       //Refresh Prod Data:
       for(i=0;i<10;i++)
       {
        WeighingData_StringW1[i] = concat("0.00s",space(tab),"0.00s",space(tab),"0.00kg",space(tab),"00:00:00");
       } 

        ResetWeighingDataPopupFlag = Done;
    }
    
    if (RefreshWeighingDataPopupFlag[Scale1] != Done || WeighingData_Popup)
    {
       //Refresh Prod Data:
       for(i=9;i>=0;i--)
       {
        if(!WeighingData_Popup)
        {
        if(i==0)WeighingData_StringW1[i] = WeighingData_StringSource[Scale1];
        else WeighingData_StringW1[i] = WeighingData_StringW1[i-1];
        }
        if(WeighingData_StringW1[i] =="") WeighingData_StringW1[i] = concat("0.00s",space(tab),"0.00s",space(tab),"0.00kg",space(tab),"00:00:00");
        widget_text  (WEIGHINGDATA_STRING1_1+i, WeighingData_StringW1[i]);
       } 

        RefreshWeighingDataPopupFlag[Scale1] = Done;
        WeighingData_Popup = OFF;
    }
    
    
    

//Refresh Report Screen 
    if (RefreshReportScreenFlag != Done && Current_Screen == SCREEN_REPORT)
    {  
      RefreshReportScreen(SCREEN_REPORT);
      RefreshReportScreenFlag = Done;
    }          

//Refresh Batch Screen 
    if (RefreshBatchScreenFlag != Done && Current_Screen == SCREEN_BATCH)
    {  
      RefreshReportScreen(SCREEN_BATCH);
      RefreshBatchScreenFlag = Done;
    } 

//Refresh Fault Screen 
    if (RefreshFaultScreenFlag != Done && Current_Screen == SCREEN_FAULT)
    {  
      RefreshFaultScreen();
      RefreshFaultScreenFlag = Done;
    }

    if (FaultLightSetFlag != Done)
    {
      begindraw();
      if (LT_GEN)       widget_image  (FAULT_BOX,GENERAL_FAULT); 
      else if (LT_BLK)  widget_image  (FAULT_BOX,BLOCKING_FAULT);
      else if (LT_STOP) widget_image  (FAULT_BOX,STOPPING_FAULT);  
      else if (LT_WRN)  widget_image  (FAULT_BOX,WARNING_FAULT);
      else              widget_image  (FAULT_BOX,NO_FAULT);  
      enddraw();
      Fault_Status_MEM = Fault_Status;
      FaultLightSetFlag = Done;
    }

    if (SaveWPFlag != Done && SeqModeManager == stp_OFF_MODE)
     {
      SaveWP2Db();
      SaveWPFlag = Done;
     }

    if (PreSave_DataNoResetFlag != Done) // && SeqModeManager == stp_OFF_MODE)
     {
      SaveProdDataBegin = systemtimer_ms();
      SqareSumWeightString[Scale1] = trim(string(SqareSumWeight[Scale1]));
      SumWeightString[Scale1] = trim(string(SumWeight[Scale1]));
      SaveProdVars();
      PreSave_Data(MemRecipe,OFF);
      PreSave_DataNoResetFlag = Done;
      SaveProdDataDuration = systemtimer_ms()- SaveProdDataBegin;
     }
     
    if(NumberOfWPMem != MC.NumberOfWP || CreateWPNameListFlag != Done)
     {
      CreateWPNameListDb();
      NumberOfWPMem = MC.NumberOfWP;
      CreateWPNameListFlag = Done;
     }
      
    if(LoadWPFromInputsFlag != Done)
     {
      ChangeWPinDB(MemRecipe,RecipeFromInputs);
      LoadWPFromInputsFlag = Done;
     }
      
    if(SaveBatchFlag != Done)
     {
      BatchNov[RecipeMem] = Batch;
      SaveBatchFlag = Done;
     } 
    
    if(WeighPerUnitSaveFlag != Done)
     {
      WeighPerUnitSave();
      WeighPerUnitSaveFlag = Done;
     } 
     
    if (RefreshWPScreen_No != Done)
    {
    if (RefreshWPScreen_No == Current_Screen) RefreshWPScreen(RefreshWPScreen_No);
    RefreshWPScreen_No = Done;
    }

    if (RefreshMPScreen_No != Done)
    {
    if (RefreshMPScreen_No == Current_Screen) RefreshMPScreen(RefreshMPScreen_No);
    RefreshMPScreen_No = Done;
    }
    
    if (RefreshMCScreen_No != Done)
    {
    if (RefreshMCScreen_No == Current_Screen) RefreshMCScreen(RefreshMCScreen_No);
    RefreshMCScreen_No = Done;
    }

 
  
    if (CurModeSetFlag != Done)
    {
      
     CMTimeCurrent = systemtimer_ms();
     CMTimeElapsed = CMTimeCurrent - CMTimeLast;
     if(CMTimeElapsed >= 2000 || CMTimeLast == 0) //Wait 2 seconds between mode refresh
     {
      CMTimeLast = CMTimeCurrent; 
      begindraw();
      switch (mode_step)
      {
        case stp_OFF_MODE:    
                   widget_foreground (MODE_BOX,   "White");
                   widget_image      (MODE_BOX,OFF_MODE);
                 break;
                          
        case stp_MANUAL_MODE:    
                   widget_foreground (MODE_BOX,   "Yellow");
                   widget_image      (MODE_BOX,MAN_MODE);
                 break;
                             
        case stp_STOPPING_MODE:
                 if(AutoPause)
                  {  
                   widget_foreground (MODE_BOX,   "Yellow");
                   widget_image      (MODE_BOX,PAUSE_MODE);
                  }
                 else
                  {  
                   widget_foreground (MODE_BOX,   "Red");
                   widget_image      (MODE_BOX,STOPPING_MODE);
                  }  
                 break;                            
                 
        case stp_STOP_MODE:
                   widget_foreground (MODE_BOX,   "Red");
                   widget_image      (MODE_BOX,STOP_MODE);
                 break;
                 
        case stp_PREP_MODE:
                   widget_foreground (MODE_BOX,   "Blue");
                   widget_image      (MODE_BOX,PREP_MODE);
                 break;
                 
        case stp_AUTO_MODE:
                  if(AutoPause)
                  {  
                   widget_foreground (MODE_BOX,   "Yellow");
                   widget_image      (MODE_BOX,PAUSE_MODE);
                  }
                 else
                  {           
                   widget_foreground (MODE_BOX,   "White");
                   widget_image      (MODE_BOX,AUTO_MODE);
                  } 
                 break;
      }
      enddraw();
      mode_step_MEM = mode_step;
      CurModeSetFlag = Done;
     }  
    }
  
    if (HopperStateFlag != Done && Current_Screen == SCREEN_AUTOMATIC)
    {
      switch (Hopper_State)
      {
        case HopperFill:   widget_image (NAV_FCT_BUTTON_8, HOPPER_FILL);
                           break;
                    
        case HopperEmpty:  widget_image (NAV_FCT_BUTTON_8, HOPPER_EMPTY);
                           break;
      }
     Hopper_StateMEM = Hopper_State;
     HopperStateFlag = Done; 
    }

   if (Start_PauseBtnMem != Start_PauseBtn && Current_Screen == SCREEN_AUTOMATIC && !IsCleanoutDone)
    {
      switch (Start_PauseBtn)
      {
        case StartBtn:   widget_image (NAV_FCT_BUTTON_9, BTN_START);
                           break;
                    
        case PauseBtn:  widget_image (NAV_FCT_BUTTON_9, BTN_PAUSE);
                           break;
      }
     Start_PauseBtnMem = Start_PauseBtn;
    }
    
        
  
    if (DischargeStateFlag != Done && Current_Screen == SCREEN_AUTOMATIC)
    {
      switch (Discharge_State) 
      {
        case DischMan:     widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_MAN);
                           break;
                    
        case DischUnder:   widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_UNDER);
                           break;
                                                    
        case DischOver:    widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_OVER);
                           break;
                                                    
        case DischPanOff:  widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_PAN_OFF);
                           break;
        case DischPanOn:   widget_image (NAV_FCT_BUTTON_6, BTN_DISCH_PAN_ON);
                           break;                   
      } 
      Discharge_StateMEM = Discharge_State;
      DischargeStateFlag = Done;
    }
    
    
  if((WP.Unit != "lb" && WP.Unit != "kg") || (WP.Unit == "lb" && (ScaleDriver[SCALECFG2]!="lbs" || MC.OIML)))
   {
     WP.Unit = "kg";
     SaveWP2Db();
     RefreshAutoScreenReq();
     RefreshWPScreen_No = SCREEN_RECIPE3;
     SwitchUnitFlag = Execute;    
   }
  
  if(UnitMem != WP.Unit) SwitchUnitFlag = Execute;
   
  if(SwitchUnitFlag)
  {
  UnitMem = WP.Unit;
  ShownScale = indicatedscale();
  #ifndef __SIMULATION__
    if (WP.Unit == "lb") 
     {
      ShowScale = 2;
      Scale1Adm = 2;
      UnitADMtoIQ = KGtoLB;
      UnitIQtoADM = LBtoKG;
     }
    else                 
     {
     ShowScale = 1;
     Scale1Adm = 1;
     UnitADMtoIQ = 1.0;
     UnitIQtoADM = 1.0;
     }
    if (ShownScale != ShowScale) indicatescale(ShowScale);
  #else
    ShowScale = 1;
    Scale1Adm = 1;
    UnitADMtoIQ = 1.0;
    UnitIQtoADM = 1.0;
  #endif 
  SwitchUnitFlag = Done;
  }
  
  
 
 #ifndef __SIMULATION__ 
  if(!BypassTasksMonitor && !SMEntered)
  {
   //Filling Task Heart Beat monitoring 
    if (FillingTaskHeartBeat)
    {
      FillingTaskHeartBeatCnt = 0;
      FillingTaskHeartBeat = OFF;
      FTHB_main = ON;
    }
   else
    {
     FillingTaskHeartBeatCnt++;
     if(FillingTaskHeartBeatCnt > 100) //20seconds
      {
      SystemErrorCode = "201 Filling Task Stopped";
      //taskid_filling = starttask( FillingTask );
      }
    }
      
      
  //Operation Task Heart Beat monitoring   
   if (OperationTaskHeartBeat)
    {
      OperationTaskHeartBeatCnt = 0;
      OperationTaskHeartBeat = OFF;
      LOTHB_main = ON;
    }
   else
    {
     OperationTaskHeartBeatCnt++;
     if(OperationTaskHeartBeatCnt > 100) //20seconds
      {
      SystemErrorCode = "202 Logic Operation Task Stopped";
      //taskid_operation = starttask(LogicOperationTask);
      }
    }
  }   
 #endif
   
   if((WP.No>0 && WP.No<=MAX_WP)&& (WP.NominalWeight==0 || WP.DischargeTime==0))
    {
     SystemErrorCode = "301 WP not configured or database not loaded";
    } 
     
   if((!IO_Enable[O_DribbleFeed] && !IO_Enable[O_CatchGate]) || !IO_Enable[I_DischReq])
    {
     SystemErrorCode = "302 I/Os not configured or database not loaded";
    } 
   
   if(MC.FeederType==0 || MC.NumberOfWP == 0)   
    {
     SystemErrorCode = "303 MC not configured or database not loaded";
    } 
   
   if (RT_AutoPage)
   {
     if(MP.SampleFreq==0 || MP.SampleSize == 0 || MP.ZeroFreq==0 || (WP.FeedAlgoType == FeediQSmart && (MP.FastFilterSize ==0 || MP.SlowFilterSize ==0 || MP.SmartStabWindow ==0)) 
       || (WP.FeedAlgoType == FeediQFlash && MP.FlashFilterSize ==0) || (WP.FeedAlgoType == FeedStd && MP.StdFilterSize ==0))
      {
       SystemErrorCode = "304 MP not configured or database not loaded";
      }
      
      RT_AutoPage = OFF;  
   }
   
   if(FieldBusType != FieldBusTypeMem)
    {
     if((FieldBusType != FB_OFF && ((FieldBusType == FB_ETX&& FB_EthernetIP) || (FieldBusType == FB_PNX && FB_Profinet) || FieldBusType == FB_PBX && FB_Profibus)
      || (FieldBusType == FB_MBX && !FB_Profibus && !FB_Profinet && !FB_EthernetIP))|| FieldBusType == FB_OFF)
      {
        FieldBusTypeMem = FieldBusType;
      }
     else SystemErrorCode = "324 FieldBus mismatch: config. VS module";   
    }  
   
   //if(PBZeroPlus1 < MP.ZeroLimit && SeqModeManager == stp_PREP_MODE)
   // {
   //  SystemErrorCode = "325 SM PbZero+ greater than MP Zero Limit";
   // } 
    
   //Config Error Fault 
    if (SystemErrorCode != "") 
     {
       if(!FaultState(FltG_SystemError))
       {
         FaultHandler(FltG_SystemError, SystemErrorCode);
       }  
       SystemErrorCode = ""; 
     }

        //Config Warning error Fault 
    if (SystemWarningCode != "") 
     {
       if(!FaultState(FltW_SystemWarning))
       {
         FaultHandler(FltW_SystemWarning, SystemWarningCode);
       }  
       SystemWarningCode = ""; 
     }
     
     if(CopyLearnToNovFlag != Done)
      {
       CopyLearnToNovParam();
       CopyLearnToNovFlag = Done;
      } 

     

     if (ResetRegistryKey != Done)
     {
       flashload();
       RegistrationKey = "";
       flashsave();
       ResetRegistryKey = Done;
     }
     
     if(ScaleStatusMem[Scale1]!=ScaleStatus[Scale1])
      {
       ScaleStatusMem[Scale1]=ScaleStatus[Scale1];
       if(ScaleStatus[Scale1]==0)   
        setdisplayoption (DISPLAY_OPTION_SCALE_LINE_FUNCTIONS, SCALE_LINE_BARGRAPH);
       else 
        setdisplayoption (DISPLAY_OPTION_SCALE_LINE_FUNCTIONS, SCALE_LINE_TARE_WEIGHT);
      }
      
    
    if(MonthSaved != date[MT] && !PeriodicDBsSave)
    {
     PeriodicDBsSave = ON;
    }
     
    if (SeqModeManager == stp_OFF_MODE)
    {
     
       if((!DbDamaged.IO && !DbDamaged.Flex && !DbDamaged.WPs && !DbDamaged.MCs && !DbDamaged.MPs) || PeriodicDBsSave)
       {
        if(!DBsToUSBSaved || PeriodicDBsSave)
        {  
         SaveToUSBTime = SaveDBsToUSB(); 
         DBsToUSBSaved = ON;
         PeriodicDBsSave = OFF;
         MonthSaved = date[MT];
        }
       } 
      else
       { 
        if(!DBsToUSBLoaded)
        {
         SystemErrorCode = "300 Verify DBs:could be Damaged or Empty";
         DBsToUSBLoaded = ON;
        } 
       }
    
     if(LoadDBsFlag)
     {
      LoadFromUSBTime = LoadDBsFromUSB();
      InitDBs();
      LoadDBsFlag = OFF;
     }
    } 
    
    if(DateNbrMem != DateNbr && DateRefreshed)
    {
      DateNbrMem = DateNbr;
      if(MC.TrialDays > 0)
       TrialDaysCnt++;
      else if(TrialDaysCnt != 0)
       TrialDaysCnt=0;
     PreSave_DataNoResetFlag = Execute;  
    }
    
    if(MC.TrialDays > 0 && TrialDaysCnt > MC.TrialDays && Fault_Type[FLT_GEN]==0)
    {
     SystemErrorCode = "330 Trial period elapsed-Contact Premier Tech";
    }
    
    if(TrialDaysCnt > 0 && MC.TrialDays == 0)
    {
      TrialDaysCnt = 0;
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
bool ConfirmRestart(void)
{
 int     class, type, value;
 bool    val;
 string  args[4][255];
 bool    SM_saved;
 int     ScaleStatusMem[2];
 float   SMExitTime = 5.0;
 
 
  
     
  ScaleStatusMem[Scale1] = -1;
  SM_saved = OFF;
  
  
  begindraw();
    selectwindow (YESNO_POPUP_WINDOW);
    widget_enable(YES_BOX,OFF);
    widget_text  (YESNO_POPUP, "Do you really want\nto restart program?\n(Service Mode Saving)");
    showwindow   (YESNO_POPUP_WINDOW );
  enddraw();      
  
  delay(SMExitTime);
  
  for(;;)
  {
   
   if(ScaleStatusMem[Scale1] != ScaleStatus[Scale1] && !SM_saved)
   { 
    if(ScaleStatus[Scale1] != 33 && ScaleStatus[Scale1] != 66 ) // 66 = In SM, 33 = Saving SM params
     {
      widget_enable(YES_BOX,ON);
      widget_text  (YESNO_POPUP, "Do you really want\nto restart program?\n(Service Mode Saved)");
      SM_saved = ON;
     }
    ScaleStatusMem[Scale1] = ScaleStatus[Scale1];
   }
     
   if(eventreceived())
   { 
    readevent (class, type, value, args);
    switch (value)
    {
      case YES_BOX : 
                     val = ON;
                     hidewindow (YESNO_POPUP_WINDOW);
                     RestartPopupClosed = ON;
                     return(val);
      
      case NO_BOX  :
                     val = OFF;
                     hidewindow (YESNO_POPUP_WINDOW);
                     RestartPopupClosed = ON;
                     return(val);
    }
   }
   else 
    {
     DisplayHandlingLogic();
     delay(0.2);
    } 
  }    
} 

/*------------------------------------------------------------------------- 
--  Procedure Name    : DisplayHandling
--  Created by        : Steve Santerre
--  Last modified on  : 2017/10/20
--  
--  Purpose           : Logic Always scan thru main task
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--                      
--------------------------------------------------------------------------*/
enum {MSG_NONE, MSG_SERVICE_MODE_ENTERED, MSG_SERVICE_MODE_LEFT, MSG_APPL_CONFIG=9, MSG_APPL_SETTINGS, MSG_APPL_JSON};

void DisplayHandling(void)
{
int err,mode,modeMEM;

 
    mode =  msgread(0.4); // wait 200ms until msg is received 
    if(mode != -1)
     modeMEM = mode;
    switch (mode)  
    {
      case MSG_SERVICE_MODE_ENTERED: InitDone    = OFF;
                                     ServiceModeEntered = ON;
                                     FirstScanBT = OFF;
                                     T_EnOff(T_FirstScan);
                                     MaxNumbOfIO = 0;
                                     break;
      case MSG_SERVICE_MODE_LEFT:    if(ServiceModeEntered)
                                       {
                                       ServiceModeEntered = OFF;
                                       ReadServiceMode();
                                       FieldBusDetect();
                                        if(!BypassSMRestart)
                                         {
                                          if(ConfirmRestart())
                                           { 
                                            SeqModeManager=0;
                                            SeqMaster=0;
                                            SeqSpout=0;
                                            SeqWeighPan=0;
                                            SeqFeeder=0;
                                            SeqFeedSTD=0;
                                            SeqManDischarge=0;
                                            FeedingStop();
                                            RebootTerminal();
                                           }
                                          else  
                                           {
                                            Refresh_BTInit=ON;
                                            AnalogIOCheck();
                                            ScaleManagement();
                                            SetHiResolutionFactor(SCALE_CHANNEL, SCALE_NUMBER,HIRES_X10);
                                           } 
                                          } 
                                         else  
                                          {
                                           Refresh_BTInit=ON;  
                                           AnalogIOCheck();
                                           ScaleManagement();
                                           SetHiResolutionFactor(SCALE_CHANNEL, SCALE_NUMBER,HIRES_X10);
                                          }                      
                                       }  
                                     break;
      default :                      break;               
    }
  ServiceModeCheck();
  if(!ServiceModeEntered && T_Dn(T_FirstScan)) DisplayHandlingLogic();

}  
    


/*------------------------------------------------------------------------- 
--  Procedure Name    : SelectAndWaitPage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Wait for page changed feedback from QTMonitor 
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int SelectAndWaitPage(int requested_page)
{
int      class, type, value;
string   args[4][255];
timer    page_timer;
float    PageLoadingTime,SelectTime,DropTime,DropTime2;
int      SelectPre_ms,SelectPost_ms;
int      DropPre_ms,DropPost_ms;
float    page_timer_preset;

 if(FirstPageLoading)
  {
   page_timer_preset = 20;
   FirstPageLoading = OFF;
  } 
 else
  {
   page_timer_preset = 5;
  } 
  
DropPre_ms=systemtimer_ms();
dropevents();
DropPost_ms=systemtimer_ms();
DropTime = (DropPost_ms-DropPre_ms) /1000.0;

SelectPre_ms=systemtimer_ms();
selectpage(requested_page);
SelectPost_ms=systemtimer_ms();
SelectTime = (SelectPost_ms-SelectPre_ms) /1000.0;


  starttimer (page_timer, page_timer_preset);
  for (;;)
  {
    if (eventreceived ())
    {
      readevent (class, type, value, args); 
      if (type == EVENT_TYPE_PAGE_SELECTED)
      {
        PageLoadingTime = page_timer_preset - remain(page_timer);
        
        DropPre_ms=systemtimer_ms();
        dropevents();
        DropPost_ms=systemtimer_ms();
        DropTime2 = (DropPost_ms-DropPre_ms) /1000.0;
        
        if(value == requested_page)
         {
          return (requested_page);
         } 
        else
         {
          SystemErrorCode = "801 Invalid Page Selected";
          return(PAGE_SELECTWRONG);
         }  
      }
    } 
  
    //else 
    //{
     //DisplayHandling();
     delay (0.2);
     if (timeout (page_timer))
     {
      SystemErrorCode = "802 Page Select Timeout";
      return (PAGE_SELECTTIMEOUT);
     }
    //} 
    
    
  }
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ShowDbaseLanguageList
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Recipe page database search display  
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
int ShowDbaseLanguageList(void)
{
int     i=0,ID_GENERIC_DBASE_LIST, Lang_No[MAX_LANG], result;
int     class, type, value,spacenbr;
string  args[4][255];

  SelectAndWaitPage(PAGE_LANGUAGE_DBASE_LIST); 
  if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
  Language.No=0;
  ID_GENERIC_DBASE_LIST=ID_LANGUAGE_DBASE_LIST;
  widget_clear(ID_GENERIC_DBASE_LIST);
  while ( findnext(Language)==0 )
  {
    spacenbr = 3;
    if(Language.No > 9) spacenbr = 1;
      if (Language.Translated)
      {
        widget_text (ID_GENERIC_DBASE_LIST, concat(trim(Language.No), ".", space(spacenbr),Language.Name, space(1)), i );  
        if(Language.No == Lang_No_Mem)
        {  
          widget_set_index(ID_GENERIC_DBASE_LIST,i,0);
          result = i;
        }
        Lang_No[i] = Language.No;
        i++; 
      }

  }
  
  for(;;)
  {
   if(eventreceived())
   { 
    readevent (class, type, value, args);
    if (class == EVENT_CLASS_APPLICATION &&
        (type == EVENT_TYPE_LIST_ITEM_SELECTED || type == EVENT_TYPE_BUTTON_PRESS))
    {
      if (value != 0) result = (int(args[0]));
      return (Lang_No[result]);
    }
   }
   else DisplayHandling();
  }
 return (Lang_No[result]);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : ShowDbaseRecipeList
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Recipe page database search display  
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
int ShowDbaseRecipeList(bool WPManage,bool *rebuildlist)
{
int     i=0,ID_GENERIC_DBASE_LIST, result;
int     class, type=0, value,spacenbr;
string  args[4][255];

  SelectAndWaitPage(PAGE_RECIPE_DBASE_LIST);
  if (!LangRefreshed[Current_Screen]) RefreshLanguage(Current_Screen);
  
 if(rebuildlist || WPManage)
 { 
  ID_GENERIC_DBASE_LIST=ID_RECIPE_DBASE_LIST;
  widget_clear(ID_GENERIC_DBASE_LIST);

  WPNameList.No=0;
  while ( findnext(WPNameList)==0 )
  {
    spacenbr = 5;
    if (WPNameList.No > 9)  spacenbr = 3;
    if (WPNameList.No > 99) spacenbr = 1;
    widget_text (ID_GENERIC_DBASE_LIST, concat(trim(WPNameList.No), ".", space(spacenbr),WPNameList.Name, space(1), WPNameList.NominalWeight,space(1),WPNameList.Unit), i ); 
      
    i++;
  }
  rebuildlist = OFF;
 }
 
 if(!WPManage)
    {
      widget_set_index(ID_GENERIC_DBASE_LIST,MemRecipe-1,0);  
      result = MemRecipe;
    }
  
  for(;;)
  {  
   if(eventreceived())
   {  
    readevent (class, type, value, args);
    if (class == EVENT_CLASS_APPLICATION &&
        (type == EVENT_TYPE_LIST_ITEM_SELECTED || type == EVENT_TYPE_BUTTON_PRESS))
    {
      if (value != 0) result = (int(args[0])+1);
      else result = NOSELECTION;
      return (result);
    }
   }
   else DisplayHandling();
  }
 return (result);

}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : Change_Recipe
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/04
--  
--  Purpose           : Load new recipe while memorizing data to old WP
--                      and load new WP data to report data.
--                      
--                                 
--  Value Parameters  :
--  Variable Params   : WP_No: Actual WPdb.No, Listpage: WP List page
--  Side Effects      : display: Choose List_Page or Numeric_Keyboard
--------------------------------------------------------------------------------*/ 
void Change_Recipe (int Scrn_Popup, int Listpage, int WP_No, int Scrn_No, bool display)
{
 int newWP;
 
 if (display == Numeric_Keyboard)
 {
   newWP = requestinput(KEYBOARD_MODE_NUMERIC, lsub(TX_RECIPE_ID), "",
                       INPUT_FORMAT_INTEGER, 3, 0);
   newWP = int (Lim(1,MC.NumberOfWP,newWP));
 }
 else
  {
    Current_Screen = Scrn_Popup;                             
    newWP = ShowDbaseRecipeList(WP_List, RebuildWPList);
  } 
  Current_Screen = Scrn_No;
  switch (Scrn_No)
  {
    case SCREEN_AUTOMATIC : WeightDisplayFull(No_Forcing); break;
  } 
  SelectAndWaitPage(Listpage);                              
  if (newWP != MemRecipe && newWP != NOSELECTION)
  {
    ChangeWPinDB(MemRecipe,newWP);
  }
} 

/*------------------------------------------------------------------------- 
--  Procedure Name    : YesNoPopupMessage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/21
--  
--  Purpose           : Yes / No Popup window display    
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void YesNoPopupMessage(string text, int Special_Scrn, int Selected_Screen, int db )              
{
int     class, type, value, err;
string  args[4][255];

  begindraw();
    selectwindow (YESNO_POPUP_WINDOW);
	widget_enable(YES_BOX,ON);
    widget_text  (YESNO_POPUP, text);     
    showwindow   (YESNO_POPUP_WINDOW );
  enddraw();      
err=0;      
  for(;; )
  {
   if(eventreceived())
   { 
    readevent (class, type, value, args);
    switch (value)
    {
      case YES_BOX : switch (Special_Scrn)
                      {
                        case CONFIG_PAGES: 
                                     
                                    hidewindow (YESNO_POPUP_WINDOW);
                                    switch (db)
                                    {
                                      case MC_Db : 
                                                   switch (Selected_Screen)
                                                   {                                
                                                     case MC_SAVE2DEFAULT: 
//                                                                           MCdb.No = 1;                              
//                                                                           find_db (MC_Db);
//                                                                           MCdb.No = 2;
//                                                                           MCdb.Name = "Default";
//                                                                           save_db(MC_Db);
                                                                           SaveMC2Flash ();
                                                                      break;
                                                    
                                                      case MC_RESTOREDEFAULT: 
//                                                                              MCdb.No = 2;                              
//                                                                              find_db (MC_Db);
//                                                                              MCdb.No = 1;
//                                                                              MCdb.Name = "Active";
//                                                                              save_db(MC_Db);
                                                                              LoadDefault_MC ();
                                                                       break;
                                                   }                    
                                                  break;
                                                  
                                       case MP_Db : 
                                                   switch (Selected_Screen)
                                                   {                                
                                                     case MP_SAVE2DEFAULT: 
//                                                                           MPdb.No = 1;                              
//                                                                           find_db (MP_Db);
//                                                                           MPdb.No = 2;
//                                                                           MPdb.Name = "Default";
//                                                                           save_db(MP_Db);
                                                                           SaveMP2Flash ();
                                                                      break;
                                                    
                                                      case MP_RESTOREDEFAULT: 
//                                                                              MPdb.No = 2;                              
//                                                                              find_db (MP_Db);
//                                                                              MPdb.No = 1;
//                                                                              MPdb.Name = "Active";
//                                                                              save_db(MP_Db);
                                                                              LoadDefault_MP ();
                                                                       break;
                                                   }
                                                  break; 
                                    } 
                                   break;
                                   
                        case SCREEN_AUTOMATIC:  
                                    if (OffRequest)
                                    {
                                      hidewindow (YESNO_POPUP_WINDOW);
                                      OffHMI = ON;
                                      OffRequest = OFF;
                                    }
                                    
                                    if(IsCleanoutDone)
                                    {
                                        hidewindow (YESNO_POPUP_WINDOW);
                                        IsCleanoutDone = OFF;
                                        CleanoutWeighment = ON;
                                        if(WP.SlowCycleEnd != END_CYCLE || WP.FeedAlgoType != FeedStd)
                                        { 
                                         DischargeHMI = ON;
                                        }
                                    }
                                    
                                    if(ContinueUnitFlag)
                                     {
                                      hidewindow (YESNO_POPUP_WINDOW);
                                      DischargedCall = OFF;
                                      DischReqMem=OFF;
                                     } 
                                    
                                   break;
                                   
                        case SCREEN_WPMANAGE:  
                                  
                                  switch (Selected_Screen)
                                  {
                                    
                                    case SCREEN_WPMANAGERENAME:
                                                                  hidewindow (YESNO_POPUP_WINDOW);
                                                                  WP_ActiveWP_No = MemRecipe;
                                                                  WPdb.No = WP_Rename_No;
                                                                  find_db (WP_Db);
                                                                  WPdb.Name = WP_Rename_String;
                                                                  save_db(WP_Db);
                                                                  WP_Rename_No = 0;
                                                                  WPdb.No = WP_ActiveWP_No;
                                                                  LoadDb2WP();
                                                                  widget_text (WPMANAGE_RENSRCE_SEARCH_ID, "");
                                                                  widget_text (WPMANAGE_RENNEW_SEARCH_ID, "");
                                                                  RefreshWPManageScreen(SCREEN_WPMANAGERENAME);
                                                                  
                                                                  CreateWPNameListDb();
                                                                 
                                                               break;
                                    
                                    case SCREEN_WPMANAGECOPY:
                                                                  hidewindow (YESNO_POPUP_WINDOW);
                                                                  WP_ActiveWP_No = MemRecipe;
                                                                  WPdb.No = WP_CopySrce_No;
                                                                  find_db (WP_Db);  
                                                                  WPdb.No = WP_CopyDest_No;
                                                                  WPdb.Name = concat (WPdb.Name,"Copy");
                                                                  CleariQFeedLearn();
                                                                  save_db(WP_Db);
                                                                  WP_CopySrce_No = 0;
                                                                  WP_CopyDest_No = 0;
                                                                  WPdb.No = WP_ActiveWP_No;
                                                                  LoadDb2WP();
                                                                  widget_text (WPMANAGE_COPYSRCE_SEARCH_ID, "");
                                                                  widget_text (WPMANAGE_COPYDEST_SEARCH_ID, "");
                                                                  RefreshWPManageScreen(SCREEN_WPMANAGECOPY);
                                                                  
                                                                  CreateWPNameListDb();
                                                                  
                                                               break;
                                    
                                    
                                    case SCREEN_WPMANAGEDELETE:
                                    
                                                                  hidewindow (YESNO_POPUP_WINDOW);
                                                                  WP_ActiveWP_No = MemRecipe;
                                                                  WPdb.No = WP_Delete_No;
                                                                  find_db (WP_Db);  
                                                                  delete (WPdb);
                                                                  WPdb.No = WP_Delete_No;
                                                                  WPdb.Name = concat ("Free", space(1), trim(string(WP_Delete_No)));
                                                                  WPdb.Unit = "kg";
                                                                  CleariQFeedLearn();
                                                                  save_db(WP_Db);
                                                                  WP_Delete_No = 0;
                                                                  WPdb.No = WP_ActiveWP_No;
                                                                  LoadDb2WP();
                                                                  widget_text (WPMANAGE_DELETE_SEARCH_ID, "");
                                                                  RefreshWPManageScreen(SCREEN_WPMANAGEDELETE);
                                                                  
                                                                  CreateWPNameListDb();
                                                                  
                                                                break;
                                    
                                    
                                  }  
                                 break;
                      
                        case SCREEN_REPORT:
                                 hidewindow (YESNO_POPUP_WINDOW);
                                 ResetLifetimeDataHMI = ON;
                               break;
                          
                        case SCREEN_UPLOAD_DBS:
                                 hidewindow (YESNO_POPUP_WINDOW);
                                 LoadDBsFlag = ON;
                               break;                
                        
                        default:  
                                hidewindow (YESNO_POPUP_WINDOW);
                               break;                             
                      }
                    break;
                      
      case NO_BOX :  switch (Special_Scrn)
                      {
                        
                        case SCREEN_AUTOMATIC:  
                                    
                                     if (OffRequest)
                                    {
                                      hidewindow (YESNO_POPUP_WINDOW);
                                      OffHMI = OFF;
                                      OffRequest = OFF;
                                    }
                                    
                                    if(IsCleanoutDone)
                                    {
                                        hidewindow (YESNO_POPUP_WINDOW);
                                        IsCleanoutDone = OFF;
                                        CleanoutWeighment = OFF;
                                        if(WP.SlowCycleEnd != END_CYCLE || WP.FeedAlgoType != FeedStd)
                                        { 
                                         DischargeHMI = ON;
                                        }
                                    }
                                    
                                    if(ContinueUnitFlag)
                                     {
                                      hidewindow (YESNO_POPUP_WINDOW);
                                      DischargedCall = ON;
                                     }
                                    
                                   break;
                        
                        case SCREEN_WPMANAGE:
                                            switch (Selected_Screen)
                                            {
                                              case SCREEN_WPMANAGERENAME:
                                            
                                                                          hidewindow (YESNO_POPUP_WINDOW);
                                                                          WP_Rename_No = 0;
                                                                          widget_text (WPMANAGE_RENSRCE_SEARCH_ID, "");
                                                                          widget_text (WPMANAGE_RENNEW_SEARCH_ID, "");
                                                                        break;
                                              
                                              case SCREEN_WPMANAGECOPY:
                                            
                                                                          hidewindow (YESNO_POPUP_WINDOW);
                                                                          WP_CopySrce_No = 0;
                                                                          WP_CopyDest_No = 0;
                                                                          widget_text (WPMANAGE_COPYSRCE_SEARCH_ID, "");
                                                                          widget_text (WPMANAGE_COPYDEST_SEARCH_ID, ""); 
                                                                        break;
                                              
                                              case SCREEN_WPMANAGEDELETE:
                                            
                                                                          hidewindow (YESNO_POPUP_WINDOW);
                                                                          WP_Delete_No = 0;
                                                                          widget_text (WPMANAGE_DELETE_SEARCH_ID, ""); 
                                                                        break;
                        
                                            }
                                            WPdb.No = MemRecipe;
                                          
                        case SCREEN_UPLOAD_DBS:
                                 hidewindow (YESNO_POPUP_WINDOW);
                                 LoadDBsFlag = OFF;
                               break;  
                        
                        default:   hidewindow (YESNO_POPUP_WINDOW);
                                  break;
                                    
                      
                      
      
                      
                      }
//                      if (db !=0)
//                      {
                          switch (db)
                          {
                            case WP_Db : LoadDb2WP();
                                         break;
//                            case MP_Db : find_db (MP_Db);
//                                         break;
//                            case MC_Db : find_db (MC_Db);
//                                         LoadAccessTableDB();
//                                         break;
                           
                          }
//                      }      
                    break;
    }
    if(value==YES_BOX || value==NO_BOX)  
      break;
   }
   else DisplayHandling();    
  }
}

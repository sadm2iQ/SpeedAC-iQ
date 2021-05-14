﻿enum 
{
No_Operation = 0, 
Modify_WP = 1, 
Modify_MP = 2, 
Modify_MC = 3, 
Modify_BatchName = 4, 
Select_WP = 10, 
Select_Scale = 11, 
Set_AnalogOutput = 12, 
Reset_ProdReport = 20, 
Reset_FaultRecord = 21, 
Reset_BatchReport = 22, 
Run = 30, 
Stop = 31, 
Manual_Discharge1 = 32,
Manual_Discharge2 = 33,
Cancel_Cycle = 34, 
Clear_Fault = 35, 
State_Check_Weight = 36, 
State_Hopper = 37, 
ZeroTheScale1 = 40,
ZeroTheScale2 = 41,  
Batch_End = 42, 
Reset_Comm = 99
}

enum
{
HighBit,
LowBit
}

// Assignment of fieldbus registers
  
  /* DataWord Output address mapping 0 to 63 */ 
  
  #define OUT_PLC_SeqModeManager       0
  #define OUT_PLC_SeqMaster1           1
  #define OUT_PLC_SeqMaster2           2
  #define OUT_PLC_FaultGen             3
  #define OUT_PLC_FaultBlock           4
  #define OUT_PLC_FaultStopping        5
  #define OUT_PLC_FaultWarn            6
  #define OUT_PLC_LiveWeightMSB1       7
  #define OUT_PLC_LiveWeightLSB1       8
  #define OUT_PLC_LiveWeightMSB2       9
  #define OUT_PLC_LiveWeightLSB2       10
  #define OUT_PLC_ScaleStatus          11
  #define OUT_PLC_WeighProgram         12
  #define OUT_PLC_WeightUnit           13
  #define OUT_PLC_dp                   14
  #define OUT_PLC_free1                15
  #define OUT_PLC_free2                16
  #define OUT_PLC_free3                17
  #define OUT_PLC_Command             18
  #define OUT_PLC_Parameter           19
  #define OUT_PLC_StartReg            20
  #define OUT_PLC_EndReg              63
  
  /* DataWord Input address mapping 64 to 127 */ 
  #define IN_PLC_Command              64
  #define IN_PLC_Parameter            66
  #define IN_PLC_Value                68
  #define IN_PLC_Handshake            70


/* Digital IO write commands from PLC*/
/* Write commands from PLC*/
  #define DW_Write                     304
/* Read commands from PLC*/
  #define DW_Read                      320



  #define b_SCL_Service_Mode1           0
  #define b_SCL_Overload1               1
  #define b_SCL_Motion1                 2
  #define b_SCL_Scale_Error1            3
  #define b_SCL_Service_Mode2           4
  #define b_SCL_Overload2               5
  #define b_SCL_Motion2                 6
  #define b_SCL_Scale_Error2            7
  #define b_SCL_Heartbeat               8
  #define b_SCL_HopperState             9
  #define b_SCL_ProdDataReady           10
  #define b_SCL_BatchEnded              11
  #define b_SCL_WeightChecked1          12
  #define b_SCL_WeightChecked2          13
  #define b_SCL_Handshake               14 
 
enum //Write commands
{
ActionsToDo      = 31,
ChangeWP         = 32,
}

enum //Read commands
{
Read_Auto_Page1   = 32,
Read_Auto_Page2   = 33,
Read_Report_Page = 40,
Read_Batch_Page  = 50,
Read_WP_Page1    = 61,
Read_WP_Page2    = 62,
Read_WP_Page3    = 63,
Read_WP_Page4    = 64,
Read_MC_Page1    = 71,
Read_MC_Page2    = 72,
Read_MC_Page3    = 73,
Read_MP_Page1    = 81,
Read_MP_Page2    = 82,
Read_MP_Page3    = 83,
Read_WPNameList  = 98, //Added by NAMK 
Read_String      = 99,
ParameterMax  //Must stay the last
}

enum
{
Read_WP_Name               =  1,
Read_Batch_Name            =  2,
Read_Batch_Details         =  3,
Read_MC_PlantLineName      =  4,
Read_MC_SerialNbr          =  5,
Read_MC_CustomerName       =  6,
Read_MC_CustomerLocation   =  7,
Read_MC_SupportPhoneNbr    =  8,
Read_MC_SupportFaxNbr      =  9,
Read_MC_SupportPhoneEmail  = 10,
Read_MC_PartsPhoneNbr      = 11,
Read_MC_PartsFaxNbr        = 12,
Read_MC_PartsPhoneEmail    = 13,
Read_MC_Language1Text      = 14,
Read_MC_Language2Text      = 15,
Read_MC_Language3Text      = 16,
Read_MC_PrinterIP          = 17,
Read_UnitRecord            = 18,
Read_iQVersion             = 19
}

bool SwapBytes;
int ScaleNbr;
int dw_temp[64];

// Toggle Scale Number for Additional Live Info
int ToggleScale(void)
{
  switch(ScaleNbr)
  { 
   case 1 : ScaleNbr = 2;
            break;
   case 2 : ScaleNbr = 1;
            break;
   default: ScaleNbr = 1;
            break;
  }
  return(ScaleNbr);
}                              
            
            
/*------------------------------------------------------------------------- 
--  Procedure Name    : HeartBeat
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : This heart beat is used to send a live signal to an 
--                    : external device for communication purposes
--  Value Parameters  :
--  Variable Params   : bool = Returns current state of heart beat
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
bool HeartBeat (void)
{
  if(!T_EN[T_HeartbeatON]) T_EnOn(T_HeartbeatON);
  if(T_Dn(T_HeartbeatON) && !T_EN[T_HeartbeatOFF]) T_EnOn(T_HeartbeatOFF);
  if(T_Dn(T_HeartbeatOFF)){T_EnOff(T_HeartbeatON);T_EnOff(T_HeartbeatOFF);}
  
  return  (!T_EN[T_HeartbeatOFF]);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Set_ActionToDo
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Function used to send an action to the indicator 
--                    : 
--  Value Parameters  :
--  Variable Params   : Code 100 = invalid instructions
                      : Code 101 and more instruction not possible 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int Set_ActionToDo (int IN_Value)
{
int Tempo, err;

  switch (IN_Value)
  {
    case Modify_WP: 
                            Tempo = InvalidNbr;     
       break;
    
    case Modify_MP:   
                            Tempo = InvalidNbr;  
       break;
    
    case Modify_MC:   
                            Tempo = InvalidNbr;  
       break;
    
    case Modify_BatchName:  
                            Tempo = InvalidNbr;   
       break;  
   
    case Select_Scale:
                            Tempo = InvalidNbr;     
       break;
   
    case Set_AnalogOutput: 
                            Tempo = InvalidNbr;    
       break;
   
    case Reset_ProdReport:   
                              ResetDataHMI = ON;
                              Tempo = Reset_ProdReport; 
       break;       
   
    case Reset_FaultRecord:   
                              Tempo = InvalidNbr;  
       break;
   
    case Reset_BatchReport:   
                              ResetBatchHMI = ON;
                              Tempo = Reset_BatchReport; 
       break;
   
    case Run: 
                              StartHMI = ON;           
                              Tempo = Run;
       break;
   
    case Stop:    
                              StopHMI = ON;           
                              Tempo = Stop;
       break;
    
    case Manual_Discharge1:     
                              DischargeHMI1 = ON;
                              Tempo = Manual_Discharge1;
       break; 
    
    case Manual_Discharge2:     
                              DischargeHMI2 = ON;
                              Tempo = Manual_Discharge2;
       break; 
       
    case Cancel_Cycle:  
                              OffHMI = ON;           
                              Tempo = Cancel_Cycle;
       break;
    
    case Clear_Fault:  
                              FaultReset();      //   FaultResetReq ();    
                              Tempo = Clear_Fault;
       break;
    
    case State_Check_Weight: //Toggle_Checkweight     

                               if(CheckWeight_State == ReleaseWeight) 
                               {
                                 CheckWeight_State = CheckAllWeight;
                                 Tempo = State_Check_Weight;
                               }
                               else if (CheckWeight_State == CheckAllWeight) 
                                    {
                                      CheckWeight_State = ReleaseWeight;
                                      Tempo = State_Check_Weight;
                                    }
                                    else Tempo = State_Check_Weight+100;
       break;

    
    case State_Hopper: // Toggle_Hopper  
    
                              if (SeqModeManager != stp_OFF_MODE)  
                              { 
                               if (Hopper_State == HopperFill)
                               {
                                 Hopper_State = HopperEmpty;
                                 Tempo = State_Hopper;
                               }
                               else if (Hopper_State == HopperEmpty)
                                    {
                                      Hopper_State = HopperFill;
                                      Tempo = State_Hopper;
                                    }
                              }
                              else  Tempo = State_Hopper + InvalidNbr;  

       break; 
    
        
    case ZeroTheScale1: 
                               if (mode_step == stp_OFF_MODE )
                               {
                                 err = setzero(Scale1Adm); 
                                 if (err == 0)  Tempo = ZeroTheScale1;
                                 else Tempo = ZeroTheScale1 + InvalidNbr;
                               }    
       break;
    
    case ZeroTheScale2: 
                               if (mode_step == stp_OFF_MODE )
                               {
                                 err = setzero(Scale2Adm); 
                                 if (err == 0)  Tempo = ZeroTheScale2;
                                 else Tempo = ZeroTheScale2 + InvalidNbr;
                               }    
       break;
       
    case Batch_End:       
                   BatchEndViaComm = ON;
                   Tempo = Batch_End;
       break;
    
    case Reset_Comm:   
                   Tempo = InvalidNbr;  
       break; 
       
    /* Input Value Invalid*/
    default: Tempo = InvalidNbr;
        break; 
  
  }

 
  
  return (Tempo);

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_AdditionalLiveInfo
--  Created by        : Steve Santerre            
--  Last modified on  : 2019/02
--  
--  Purpose           : Displays Additional Live Info for Data Collector
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_AdditionalLiveInfo(int ScaleNo)
{
  int DW_Pointer; 
  double ProdTotalWeightTemp;
     
        if(ScaleNo == 1)
        {
         ProdTotalWeightTemp = ProdTotalWeight1;
        } 
        if(ScaleNo == 2)
        {
        ProdTotalWeightTemp = ProdTotalWeight2;
        }
        
     DW_Pointer = 1;
                                                            //Fieldbus Word index                          
     
     return_value[DW_Pointer] = ScaleNo;                        //22
     DW_Pointer++;
     return_value[DW_Pointer] = TargetWeight[ScaleNo - 1];      //24
     DW_Pointer++;
     return_value[DW_Pointer] = ProdAvgWeight[ScaleNo - 1];     //26
     DW_Pointer++;
     return_value[DW_Pointer] = ProdAcceptUnitCnt[ScaleNo - 1]; //28
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdLastChecked[ScaleNo - 1];   //30
     DW_Pointer++; 
     return_value[DW_Pointer] = WeighPerUnitAcc;                //32
     DW_Pointer++;
     return_value[DW_Pointer] = WP.WeighmentsPerUnit;           //34
     DW_Pointer++;
     return_value[DW_Pointer] = ProdTotalUnitsCnt[ScaleNo - 1]; //36 
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.Count;                    //38
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.Preset;                   //40
     DW_Pointer++;                       
     return_value[DW_Pointer] = ProdCycleUnitsPerMin;           //42
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdBulkDuration[ScaleNo - 1];     //44
     DW_Pointer++;
     return_value[DW_Pointer] = ProdDribbleDuration[ScaleNo - 1];  //46
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdCycleDuration[ScaleNo - 1];    //48
     DW_Pointer++;
     return_value[DW_Pointer] = ProdTotalWeightTemp;               //50
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdTotalWeighmentsLT;             //52
     DW_Pointer++;
     return_value[DW_Pointer] = ProdTotalUnitsLT;                  //54
     DW_Pointer++;
     return_value[DW_Pointer] = ProdTotalWeightLT;                 //56
     DW_Pointer++;
     return_value[DW_Pointer] = WP.UnderWeight;                //58
     DW_Pointer++;
     return_value[DW_Pointer] = WP.OverWeight;                 //60
      DW_Pointer++;
     return_value[DW_Pointer] = ScaleNo;                            //62
     
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_Auto_Page
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in Auto page 
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_Auto_Page (int ScaleNo)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     if(ScaleNo == 1) return_value[DW_Pointer] = Read_Auto_Page1; //32
     else             return_value[DW_Pointer] = Read_Auto_Page2; //33
     DW_Pointer++;
     return_value[DW_Pointer] = WP.No;
     DW_Pointer++;                                     
     return_value[DW_Pointer] = TargetWeight[ScaleNo-1];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdAvgWeight[ScaleNo-1];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdStdDev[ScaleNo-1];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdLastChecked[ScaleNo-1]; 
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdAcceptUnitCnt[ScaleNo-1];
     DW_Pointer++; 
     return_value[DW_Pointer] = WeighPerUnitAcc;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.WeighmentsPerUnit;
     DW_Pointer++;
     return_value[DW_Pointer] = ProdTotalUnitsCnt[ScaleNo-1];
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.Count;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.Preset;
     DW_Pointer++;                       
     return_value[DW_Pointer] = ProdCycleUnitsPerMin;
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdBulkDuration[ScaleNo-1];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdDribbleDuration[ScaleNo-1];
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdCycleDuration[ScaleNo-1];  
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_Report_Page
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in Report page 
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_Report_Page (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                            
     return_value[DW_Pointer] = Read_Report_Page; //40
     DW_Pointer++;
     return_value[DW_Pointer] = WP.NominalWeight;
     DW_Pointer++;                                     
     return_value[DW_Pointer] = ProdTotalUnitsCnt[Scale1];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdAcceptUnitCnt[Scale1];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdUnderWeightCnt[Scale1];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdOverWeightCnt[Scale1];
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdTotalWeight1;
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdTotalUnitsCnt[Scale2];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdAcceptUnitCnt[Scale2];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdUnderWeightCnt[Scale2];
     DW_Pointer++;
     return_value[DW_Pointer] = ProdOverWeightCnt[Scale2];
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdTotalWeight2;
     DW_Pointer++; 
     return_value[DW_Pointer] = ProdTotalWeighmentsLT;
     DW_Pointer++;
     return_value[DW_Pointer] = ProdTotalUnitsLT;
     DW_Pointer++;
     return_value[DW_Pointer] = ProdTotalWeightLT;     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_Batch_Page
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in Batch Report page 
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_Batch_Page (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_Batch_Page; //50
     DW_Pointer++; 
     return_value[DW_Pointer] = Batch.Preset;
     DW_Pointer++;                                     
     return_value[DW_Pointer] = Batch.UnitsDone;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.UnitsAccepted;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.UnderWeightCnt;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.OverWeightCnt;
     DW_Pointer++; 
     return_value[DW_Pointer] = Batch.TotalWeight;
     DW_Pointer++; 
     return_value[DW_Pointer] = Batch.MinAccepted;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.MaxAccepted;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.Residue;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.StdDev;
     DW_Pointer++; 
     return_value[DW_Pointer] = Batch.Avg;
     DW_Pointer++;
     return_value[DW_Pointer] = Batch.CountAll;     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_WP_Page1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in WP page 1
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_WP_Page1 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_WP_Page1; //61
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.NominalWeight;
     DW_Pointer++;                                     
     return_value[DW_Pointer] = WP.Overfill1;
     DW_Pointer++;
     return_value[DW_Pointer] = adj((WP.Cutoff1-CutoffCorrOffset[Scale1]),6,2);
     DW_Pointer++;
     return_value[DW_Pointer] = WP.BulkCutoff1;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.DFTime;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.BFTime1;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.Overfill2;
     DW_Pointer++;
     return_value[DW_Pointer] = adj((WP.Cutoff2-CutoffCorrOffset[Scale2]),6,2);
     DW_Pointer++;
     return_value[DW_Pointer] = WP.BulkCutoff2;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.BFTime2;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.UnderWeight;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.OverWeight;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.DischargeWeight;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.DischargeTime;
     DW_Pointer++;                       
     return_value[DW_Pointer] = WP.FallingTime;     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_WP_Page2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in WP page 2
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_WP_Page2 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_WP_Page2; //62
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.MinFeeding1;
     DW_Pointer++;                                     
     return_value[DW_Pointer] = WP.MaxFeeding1;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.MinFeeding2;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.MaxFeeding2;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.StreamRegConfig;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.ActuatorPos1;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.ActuatorPos2;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.WeighmentsPerUnit;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.FeedDelayTime;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.VibratoryDischDoors;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.ZeroingOpen;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.SlowCycleEnd;
     DW_Pointer++;                       
     return_value[DW_Pointer] = WP.EnabledScale;    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_WP_Page3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in WP page 3
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_WP_Page3 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_WP_Page3; //63
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.TopUpOFFTime;
     DW_Pointer++;                                    
     return_value[DW_Pointer] = WP.TopUpONTime;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.KnockningTime;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.BagInflationTime;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.KickerCenterTime;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.KickerActivateTime;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.Unit==TX_WPUNITLB;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.FeedAlgoType;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.SlowFillFactor;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.TuneiQFeed;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.BulkMode;
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.CatchGateDelay;
        
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_WP_Page4
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in WP page 4
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_WP_Page4 (void)
{
int DW_Pointer; 
     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_WP_Page4;  //64
     DW_Pointer++; 
     return_value[DW_Pointer] = WP.FlexT1;
     DW_Pointer++;                                    
     return_value[DW_Pointer] = WP.FlexT2;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.FlexCounter;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.DischDoorMode;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.FlexSP1;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.FlexSP2;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.VibrationAmplitude;
     DW_Pointer++;
     return_value[DW_Pointer] = WP.VibrationPeriod;      
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_MC_Page1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in MC page 1
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_MC_Page1 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_MC_Page1; //71
     DW_Pointer++; 
     return_value[DW_Pointer] = MC.BulkBlankT;
     DW_Pointer++;                                    
     return_value[DW_Pointer] = MC.DribBlankT;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.LowLevelDebounceT;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.RefillingTimeT;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.DischReqDebouncing;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.OIML;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.FeederType;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.NumberOfWP;
     DW_Pointer++; 
     return_value[DW_Pointer] = MC.CFGBagHolder;
     DW_Pointer++; 
     //return_value[DW_Pointer] = MC.Language1;
     //DW_Pointer++;
     return_value[DW_Pointer] = MC.Language2;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.Language3;
    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_MC_Page2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in MC page 2
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_MC_Page2 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_MC_Page2; //72
     DW_Pointer++; 
     return_value[DW_Pointer] = MC.PortCOM2Cfg;
     DW_Pointer++;                                    
     return_value[DW_Pointer] = MC.PortUSBCfg;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.PortETHCfg;
     DW_Pointer++; 
     return_value[DW_Pointer] = MC.ContPort;
     DW_Pointer++; 
     return_value[DW_Pointer] = MC.ContRate;
     DW_Pointer++; 
     return_value[DW_Pointer] = MC.DischOnDoorSensor;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.DribbleOutOnInBulk;
     DW_Pointer++;
     return_value[DW_Pointer] = MC.AutoSaveCorrection;
     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_MC_Page3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in MC page 3
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_MC_Page3 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_MC_Page3; //73
     DW_Pointer++;
     return_value[DW_Pointer] = Access_PW[0];
     DW_Pointer++;                                    
     return_value[DW_Pointer] = Access_PW[1];
     DW_Pointer++;
      return_value[DW_Pointer] = MC.ActuatorPosInvert;
     DW_Pointer++; 
     return_value[DW_Pointer] = Access_Timeout[0];
     DW_Pointer++;
     return_value[DW_Pointer] = Access_Timeout[1];
     DW_Pointer++;
     return_value[DW_Pointer] = Access_Timeout[2];
     DW_Pointer++;
     return_value[DW_Pointer] = MC.Mouse;
     DW_Pointer++; 
     return_value[DW_Pointer] = MC.ActuatorExtendLimit;
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_MP_Page1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in MP page 1
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_MP_Page1 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_MP_Page1; //81
     DW_Pointer++; 
     return_value[DW_Pointer] = MP.SampleFreq;
     DW_Pointer++;                                    
     return_value[DW_Pointer] = MP.SampleSize;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.ZeroFreq;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.ZeroLimit;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.AutoZeroOff;
     DW_Pointer++; 
     return_value[DW_Pointer] = MP.ScreenSaverTime;
     DW_Pointer++; 
     return_value[DW_Pointer] = MP.DischDoorMaxTime;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.SlowCycleTime;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.CatchGateMaxTime;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.OutOfTolTime;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.BagDetectionTime;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.StabTimeLimit;     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_MP_Page2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in MP page 2
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_MP_Page2 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_MP_Page2; //82
     DW_Pointer++; 
     return_value[DW_Pointer] = MP.CorrOnAverage;
     DW_Pointer++;                                    
     return_value[DW_Pointer] = MP.CutoffCorrLimit;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.DFWeightCorr;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.CutoffCorr;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.SlowFilterSize;
     DW_Pointer++; 
     return_value[DW_Pointer] = MP.FastFilterSize;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.FlashFilterSize;    
     DW_Pointer++;
     return_value[DW_Pointer] = MP.StdFilterSize;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.SmartStabWindow; 
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_MP_Page3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays all data visible in MP page 3
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Display_MP_Page3 (void)
{
int DW_Pointer; 

     DW_Pointer = 0;
                                             
     return_value[DW_Pointer] = Read_MP_Page3; //83
     DW_Pointer++;
     return_value[DW_Pointer] = MP.FlexT1;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.FlexT2;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.FlexCounter;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.FlexSP1;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.FlexSP2;
     DW_Pointer++;
     return_value[DW_Pointer] = MP.BSFBulkOffDelay;     
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Display_String
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Displays string in a CHAR format for double Data Word
--                    : transmission
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : Only extended ASCII (0-255) is supported for now
--------------------------------------------------------------------------*/
/* */
void Display_String (string Text) //99
{
int i,len,NbrOf4CharReg,NbrOfCharInLast,NbrOfReg,intval;

  len = length(Text);
  NbrOf4CharReg = len/4;
  NbrOfCharInLast = len%4;
  NbrOfReg = NbrOf4CharReg+1;
  
  
  for (i=1; i<=NbrOfReg; i++)
  {
  if(i<NbrOfReg)
    {
    
    intval =(char(Text[(i*4)-4])<<24) | (char(Text[(i*4)-3])<<16) | (char(Text[(i*4)-2])<<8) | (char(Text[(i*4)-1]));
    }
  else
   {
    switch(NbrOfCharInLast)
    {
    case 0:  intval = 0; 
     break;             
    
    case 1:  intval = (char(Text[(i*4)-4])<<24); 
     break; 
    
    case 2:  intval = (char(Text[(i*4)-4])<<24) | (char(Text[(i*4)-3])<<16); 
     break; 
     
    case 3:  intval = (char(Text[(i*4)-4])<<24) | (char(Text[(i*4)-3])<<16) | (char(Text[(i*4)-2])<<8); 
     break;
    }   
   }

    memcpy(intval,return_value[i]);   
  }
  
  return_value[0] = len;                                                       
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Scale_Status
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           :  
--                    : 
--  Value Parameters  :
--  Variable Params   : 
                      : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
int Scale_Status (void)
{
  
  if ( ScaleStatus[Scale1]==66 )    setbit(b_SCL_Service_Mode1,  dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Service_Mode1,  dw_temp[OUT_PLC_ScaleStatus]);
  if ( ScaleStatus[Scale1]==12 )    setbit(b_SCL_Overload1,      dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Overload1,      dw_temp[OUT_PLC_ScaleStatus]);
  if ( !IsSettled[Scale1]      )    setbit(b_SCL_Motion1,        dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Motion1,        dw_temp[OUT_PLC_ScaleStatus]);
  if ( ScaleStatus[Scale1]!=0 )     setbit(b_SCL_Scale_Error1,   dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Scale_Error1,   dw_temp[OUT_PLC_ScaleStatus]);
  if ( ScaleStatus[Scale2]==66 )    setbit(b_SCL_Service_Mode2,  dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Service_Mode2,  dw_temp[OUT_PLC_ScaleStatus]);
  if ( ScaleStatus[Scale2]==12 )    setbit(b_SCL_Overload2,      dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Overload2,      dw_temp[OUT_PLC_ScaleStatus]);
  if ( !IsSettled[Scale2]      )    setbit(b_SCL_Motion2,        dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Motion2,        dw_temp[OUT_PLC_ScaleStatus]);
  if ( ScaleStatus[Scale2]!=0 )     setbit(b_SCL_Scale_Error2,   dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Scale_Error2,   dw_temp[OUT_PLC_ScaleStatus]);
  if ( HeartBeat() )                setbit(b_SCL_Heartbeat,      dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Heartbeat,      dw_temp[OUT_PLC_ScaleStatus]);
  if ( Hopper_State  )              setbit(b_SCL_HopperState,    dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_HopperState,    dw_temp[OUT_PLC_ScaleStatus]);
  if ( ProdDataReadyPLC )           setbit(b_SCL_ProdDataReady,  dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_ProdDataReady,  dw_temp[OUT_PLC_ScaleStatus]);
  if ( BatchEnded )                 setbit(b_SCL_BatchEnded,     dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_BatchEnded,     dw_temp[OUT_PLC_ScaleStatus]);
  if ( WeightSampled[Scale1] )      setbit(b_SCL_WeightChecked1, dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_WeightChecked1, dw_temp[OUT_PLC_ScaleStatus]);
  if ( WeightSampled[Scale2] )      setbit(b_SCL_WeightChecked2, dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_WeightChecked2, dw_temp[OUT_PLC_ScaleStatus]);
  if ( IN_Handshake != 0 )          setbit(b_SCL_Handshake,      dw_temp[OUT_PLC_ScaleStatus]); else clrbit(b_SCL_Handshake,      dw_temp[OUT_PLC_ScaleStatus]);

 return(dw_temp[OUT_PLC_ScaleStatus]);
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Swap_DW_Bits_Input
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           :  Swap ABCD to CDAB Bit order (For AB PLCs) for
--                    :  Data received from Input
--  Value Parameters  :
--  Variable Params   : Systec Word/Bit structure       A    B    C    D
                      :   dw = 304                    0000 0001 0011 0000
--  Side Effects      : AB Word/Bit structure           C    D    A    B
--                    :   dw = 304                    0011 0000 0000 0001 
--------------------------------------------------------------------------*/
int Swap_DW_Bits_Input (int StartDW)
{
int Value = int((dw[StartDW] & 0x00FF) << 8) + ((dw[StartDW] >> 8) & 0x00FF);
return (Value);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Swap_DW_Bits_Output
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           :  Swap ABCD to CDAB Bit order (For AB PLCs) for 
--                    :  Data sent to Output
--  Value Parameters  :
--  Variable Params   : Systec Word/Bit structure       A    B    C    D
                      :   dw = 304                    0000 0001 0011 0000
--  Side Effects      : AB Word/Bit structure           C    D    A    B
--                    :   dw = 304                    0011 0000 0000 0001 
--------------------------------------------------------------------------*/
int Swap_DW_Bits_Output (int DataIn)
{
int Value = ((DataIn & 0xFF00) >> 8) + ((DataIn << 8) & 0xFF00);
return (Value);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Convert_DoubleWord2SingleWord
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Converts a double word into a single word 
--                    :  
--  Value Parameters  :
--  Variable Params   : 
                      :   
--  Side Effects      : 
--------------------------------------------------------------------------*/
float Convert_DoubleWord2SingleWord(int StartDW, bool swap)  
{
float f1;
int   i1,Tmp_MSW, Tmp_LSW;

if (swap)//(FB_EthernetIP)
{
 Tmp_MSW  = Swap_DW_Bits_Input(StartDW+1);
 Tmp_LSW  = Swap_DW_Bits_Input(StartDW);
  i1= (Tmp_MSW << 16) + (Tmp_LSW & 0xFFFF);
 memcpy( i1, f1);
}
else
{
  i1= int((dw[StartDW] << 16) + (dw[StartDW+1] & 0xFFFF));
  memcpy( i1, f1);
}

  return(f1);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Convert_Single2Double
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Converts a single word into a double word 
--                    :  
--  Value Parameters  :
--  Variable Params   : 
                      :   
--  Side Effects      : 
--------------------------------------------------------------------------*/
int Convert_Single2Double(float DataIn, int BitPriority )  
{
int   int_temp, bit_string;
 switch (BitPriority)
 {
   case HighBit:
                  memcpy(DataIn, int_temp);
                  bit_string = int_temp >> 16;
        break; 
   
   case LowBit:    
                  memcpy(DataIn, int_temp);
                  bit_string = int_temp & 0xFFFF;
        break;

 
 }
 return(bit_string);
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : Clear_DataWords
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Clears all Output Data words in a loop
--                    :  
--  Value Parameters  :
--  Variable Params   : 
                      :   
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Clear_DataWords (void)
{
int i;
  for (i=OUT_PLC_StartReg; i<=OUT_PLC_EndReg; i++)
  {
    dw[i] = 0;
  }
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Read_PLC
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Reads the Data words from external device
--                    :  
--  Value Parameters  :
--  Variable Params   : 
                      :   
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Read_PLC (bool Swap)
{
   IN_Command   = Convert_DoubleWord2SingleWord(IN_PLC_Command, Swap);
   IN_Parameter = Convert_DoubleWord2SingleWord(IN_PLC_Parameter, Swap);
   IN_Value     = Convert_DoubleWord2SingleWord(IN_PLC_Value, Swap);
   IN_Handshake = Convert_DoubleWord2SingleWord(IN_PLC_Handshake, Swap);
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : Write_PLC
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Writes into output Data words to external device
--                    :  
--  Value Parameters  :
--  Variable Params   : 
                      :   
--  Side Effects      : 
--------------------------------------------------------------------------*/
void Write_PLC (bool Swap)
{
int i,ts,tt,tmax;

 if (Swap)//(FB_EthernetIP) /* AB Ethernet IP Swap Bits ABCD-->CDAB */
 {
   dw_temp[OUT_PLC_SeqModeManager]    = Swap_DW_Bits_Output(OUT_SeqModeManager);
   dw_temp[OUT_PLC_SeqMaster1]         = Swap_DW_Bits_Output(OUT_SeqMaster[Scale1]);
   dw_temp[OUT_PLC_SeqMaster2]         = Swap_DW_Bits_Output(OUT_SeqMaster[Scale2]);
   dw_temp[OUT_PLC_FaultGen]          = Swap_DW_Bits_Output(OUT_FaultGen);
   dw_temp[OUT_PLC_FaultBlock]        = Swap_DW_Bits_Output(OUT_FaultBlock);
   dw_temp[OUT_PLC_FaultStopping]     = Swap_DW_Bits_Output(OUT_FaultStopping);
   dw_temp[OUT_PLC_FaultWarn]         = Swap_DW_Bits_Output(OUT_FaultWarn);
   dw_temp[OUT_PLC_LiveWeightMSB1]     = Swap_DW_Bits_Output(OUT_LiveWeight_LSB[Scale1]);
   dw_temp[OUT_PLC_LiveWeightLSB1]     = Swap_DW_Bits_Output(OUT_LiveWeight_MSB[Scale1]);
   dw_temp[OUT_PLC_LiveWeightMSB2]     = Swap_DW_Bits_Output(OUT_LiveWeight_LSB[Scale2]);
   dw_temp[OUT_PLC_LiveWeightLSB2]     = Swap_DW_Bits_Output(OUT_LiveWeight_MSB[Scale2]);
   dw_temp[OUT_PLC_ScaleStatus]       = Swap_DW_Bits_Output(OUT_ScaleStatus);
   dw_temp[OUT_PLC_WeighProgram]         = Swap_DW_Bits_Output(OUT_WeighProgram);    
   dw_temp[OUT_PLC_WeightUnit]        = Swap_DW_Bits_Output(OUT_WeightUnit);
   dw_temp[OUT_PLC_dp]                = Swap_DW_Bits_Output(OUT_dp);
   dw_temp[OUT_PLC_Command]           = Swap_DW_Bits_Output(OUT_Command);
   dw_temp[OUT_PLC_Parameter]         = Swap_DW_Bits_Output(OUT_Parameter);
   
     for (i=OUT_PLC_StartReg; i<OUT_PLC_EndReg; i=i+2)
     {
       dw_temp[i]   = Swap_DW_Bits_Output(OUT_Value_DoubleWord[i+1]);
       dw_temp[i+1] = Swap_DW_Bits_Output(OUT_Value_DoubleWord[i]);
     }

 }
 else 
 {
   dw_temp[OUT_PLC_SeqModeManager]    = OUT_SeqModeManager;
   dw_temp[OUT_PLC_SeqMaster1]         = OUT_SeqMaster[Scale1];
   dw_temp[OUT_PLC_SeqMaster2]         = OUT_SeqMaster[Scale2];
   dw_temp[OUT_PLC_FaultGen]          = OUT_FaultGen;
   dw_temp[OUT_PLC_FaultBlock]        = OUT_FaultBlock;
   dw_temp[OUT_PLC_FaultStopping]     = OUT_FaultStopping;
   dw_temp[OUT_PLC_FaultWarn]         = OUT_FaultWarn;
   dw_temp[OUT_PLC_LiveWeightMSB1]     = OUT_LiveWeight_MSB[Scale1];
   dw_temp[OUT_PLC_LiveWeightLSB1]     = OUT_LiveWeight_LSB[Scale1];
   dw_temp[OUT_PLC_LiveWeightMSB2]     = OUT_LiveWeight_MSB[Scale2];
   dw_temp[OUT_PLC_LiveWeightLSB2]     = OUT_LiveWeight_LSB[Scale2];
   dw_temp[OUT_PLC_ScaleStatus]       = OUT_ScaleStatus;   
   dw_temp[OUT_PLC_WeighProgram]      = OUT_WeighProgram;
   dw_temp[OUT_PLC_WeightUnit]        = OUT_WeightUnit;
   dw_temp[OUT_PLC_dp]                = OUT_dp;

   dw_temp[OUT_PLC_Command]           = OUT_Command;
   dw_temp[OUT_PLC_Parameter]         = OUT_Parameter;

     for (i=OUT_PLC_StartReg; i<OUT_PLC_EndReg; i=i+2)
     {
       dw_temp[i]   = OUT_Value_DoubleWord[i];
       dw_temp[i+1] = OUT_Value_DoubleWord[i+1];
     }
 }
    ts = systemtimer_ms(); 
    for (i=0; i<=OUT_PLC_EndReg; i++)
     {
       dw[i] = dw_temp[i];
     }
    tt = systemtimer_ms() - ts;
    if(tt>tmax) tmax = tt; 
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : PLC_Monitor
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : 
--                    :  
--  Value Parameters  :
--  Variable Params   : 
                      :   
--  Side Effects      : 
--------------------------------------------------------------------------*/
int PLC_Monitor (void) 
{
int i, j=0, err, DW_Pointer;

  if(IN_Command != DW_Write)
  {
   IN_ValueMem = 0;
   IN_CommandMem = 0;
   IN_ParameterMem = 0;
  }

    switch (IN_Command)
    {      
      case DW_Write:
      
               if(IN_ValueMem == IN_Value && IN_CommandMem == IN_Command && IN_ParameterMem == IN_Parameter)
                {
                    Clear_DataWords ();
                    return_value[0] = InvalidNbr*2;
                }
               
               else
                {             
                         switch (IN_Parameter)
                         {
                           case ActionsToDo:
                            if (IN_Value > 0 && IN_Value < ParameterMax)
                            return_value[0] = Set_ActionToDo (IN_Value);
                            else return_value[0] = -1;
                            Clear_DataWords ();
                            break;

                          case ChangeWP: /* Select WP*/ 
                           if(SeqModeManager == stp_OFF_MODE && IN_Value <= MC.NumberOfWP)
                            {
                             if (IN_Value != MemRecipe)
                              {
                                ChangeWPinDB(MemRecipe,IN_Value);
                                return_value[0] = ChangeWP;
                              }
                              else return_value[0] = ChangeWP + InvalidNbr;
                            }
                            else return_value[0] = ChangeWP + InvalidNbr;
                            break;
                         
                          default:
                           Clear_DataWords ();
                           return_value[0] = InvalidNbr;
                           break;
                         }
                 
                 IN_ValueMem = IN_Value;
                 IN_CommandMem = IN_Command;
                 IN_ParameterMem = IN_Parameter;
                }           
           
           Display_AdditionalLiveInfo(ToggleScale());
                           
           break; 
                    
      case DW_Read:
                        /* Clear return_value*/
                        for (i=0; i<32; i++)
                        {
                          return_value[i] = 0;
                        }
                        
                        switch (IN_Parameter)
                        {
//                           case ActionsToDo: 
//                                                  if (Temp_Value > 0 && Temp_Value < ParameterMax)
//                                                  return_value[0] = Set_ActionToDo (Temp_Value);
//                                break;
                        
                           case Read_Auto_Page1:
                                                  Display_Auto_Page(1);
                                break;
                           
                           case Read_Auto_Page2:
                                                  Display_Auto_Page(2);
                                break;
                                     
                           case Read_Report_Page:
                                                  Display_Report_Page();
                                break;
                                
                           case Read_Batch_Page:   
                                                  Display_Batch_Page();                           
                                break;
                                
                           case Read_WP_Page1:
                                                  Display_WP_Page1();
                                break;                  
                           
                           case Read_WP_Page2:
                                                  Display_WP_Page2();
                                break;
                                
                           case Read_WP_Page3:
                                                  Display_WP_Page3();
                                break;
                                
                           case Read_WP_Page4:
                                                  Display_WP_Page4();
                                break; 
                                
                           case Read_MC_Page1:
                                                  Display_MC_Page1();
                                break; 
                                
                           case Read_MC_Page2:
                                                  Display_MC_Page2();
                                break;  
                                
                           case Read_MC_Page3:
                                                  Display_MC_Page3();
                                break; 
                                
                           case Read_MP_Page1:
                                                  Display_MP_Page1();
                                break; 
                                
                           case Read_MP_Page2:
                                                  Display_MP_Page2();
                                break;   
                                
                           case Read_MP_Page3:
                                                  Display_MP_Page3();
                                break;
                                        
                                        //Added by NAMK       
                           case Read_WPNameList:
                                                  Display_String(wpNameList[int(IN_Value)]);
                                                  return_value[31] = IN_Value;
                                break;

                           case Read_String:
                                                 
                                                 switch (int(IN_Value))
                                                 {
                                                   case Read_WP_Name: 
                                                                                   Display_String (WP.Name);
                                                        break;
                                                        
                                                   case Read_Batch_Name: 
                                                                                   Display_String (Batch.Name);
                                                        break;
                                                        
                                                   case Read_Batch_Details: 
                                                                                   Display_String (Batch.Details);
                                                        break;
                                                        
                                                   case Read_MC_PlantLineName: 
                                                                                   Display_String (MC.PlantLineName);
                                                        break;
                                                        
                                                   case Read_MC_SerialNbr: 
                                                                                   Display_String (MC.SerialNbr);
                                                        break;
                                                        
                                                   case Read_MC_CustomerName: 
                                                                                   Display_String (MC.CustomerName);
                                                        break;
                                                        
                                                   case Read_MC_CustomerLocation: 
                                                                                   Display_String (MC.CustomerLocation);
                                                        break;
                                                        
                                                   case Read_MC_SupportPhoneNbr: 
                                                                                   Display_String (MC.SupportPhoneNbr);
                                                        break;
                                                        
                                                   case Read_MC_SupportFaxNbr: 
                                                                                   Display_String (MC.SupportFaxNbr);
                                                        break;
                                                        
                                                   case Read_MC_SupportPhoneEmail: 
                                                                                   Display_String (MC.SupportEmail);
                                                        break;
                                                        
                                                   case Read_MC_PartsPhoneNbr: 
                                                                                   Display_String (MC.PartsPhoneNbr);
                                                        break;
                                                        
                                                   case Read_MC_PartsFaxNbr: 
                                                                                   Display_String (MC.PartsFaxNbr);
                                                        break;
                                                        
                                                   case Read_MC_PartsPhoneEmail: 
                                                                                   Display_String (MC.PartsEmail);
                                                        break;
                                                   
                                                   case Read_MC_Language1Text: 
                                                                                   Display_String (MC.Lang1Text);
                                                        break;
                                                   
                                                   case Read_MC_Language2Text: 
                                                                                   Display_String (MC.Lang2Text);
                                                        break;
                                                   
                                                   case Read_MC_Language3Text: 
                                                                                   Display_String (MC.Lang3Text);
                                                        break;
                                                                       
                                                   case Read_MC_PrinterIP: 
                                                                                   Display_String (MC.PrinterIP);
                                                        break;                                                            
                                                   
                                                   case Read_UnitRecord:
                                                                                   Display_String (TicketInfo);
                                                        break;
                                                        
                                                   case Read_iQVersion:
                                                                                   Display_String (MC.iQVersion);
                                                        break;
                                                                                               
                                                   default: 
                                                                                   Clear_DataWords ();
                                                                                   return_value[0] = -1;
                                                        break;
                                                   
                                                 } 
                                                 
                                break;                           
                        
                           default:   
                            Clear_DataWords();
                            return_value[0] = InvalidNbr;
                                break;
                        }     
           break; 
                    
      default:    
            //Clear_DataWords ();
             Display_AdditionalLiveInfo(ToggleScale());

           break;                                                                                                        
    } 

    
    OUT_SeqModeManager    = SeqModeManager;
    OUT_SeqMaster[Scale1] = SeqMaster;
    OUT_SeqMaster[Scale2] = Seq2Master;
    OUT_FaultGen          = Fault_Type[FLT_GEN];
    OUT_FaultBlock        = Fault_Type[FLT_BLK];
    OUT_FaultStopping     = Fault_Type[FLT_STOP];
    OUT_FaultWarn         = Fault_Type[FLT_WRN];
    
    OUT_LiveWeight_MSB[Scale1]  = Convert_Single2Double(NetWeight[Scale1], HighBit);
    OUT_LiveWeight_LSB[Scale1]  = Convert_Single2Double(NetWeight[Scale1], LowBit);
    OUT_LiveWeight_MSB[Scale2]  = Convert_Single2Double(NetWeight[Scale2], HighBit);
    OUT_LiveWeight_LSB[Scale2]  = Convert_Single2Double(NetWeight[Scale2], LowBit);
  
    OUT_ScaleStatus     = Scale_Status();
    OUT_WeighProgram    = WP.No;
    OUT_WeightUnit      = (char(WP.Unit[0])<<8) | char(WP.Unit[1]);
    OUT_dp              = dp;
    OUT_Command         = IN_Command;
    OUT_Parameter       = IN_Parameter;

   for (i=OUT_PLC_StartReg; i<OUT_PLC_EndReg; i=i+2)
   {
    OUT_Value_DoubleWord[i]   = Convert_Single2Double(return_value[j], HighBit);
    OUT_Value_DoubleWord[i+1] = Convert_Single2Double(return_value[j], LowBit);
    j++;
   }
  return (err);
}

void PLC_Communication(void)
{
  
  if(FieldBusType == FB_ETX)
   SwapBytes = ON;
  else 
   SwapBytes = OFF;
   
  Read_PLC(SwapBytes);
  PLC_Monitor();
  Write_PLC(SwapBytes);
} 
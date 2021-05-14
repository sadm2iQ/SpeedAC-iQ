
#define CSV_ON_SHARED              1
#define CSV_ON_USB                 2
#define DIR_USB                    3
#define DIR_SHARED                 4
#define DBsBACKUP                  5
#define USB_PATH                   "usbstick/DataLog"
#define SHARED_PATH                "shared"
#define UNIT_RECORD                "Unit_Record_"
#define MAX_UNITRECORD_FILES       7
#define USB_FILE_REPORT            "usbstick/PrintReport.txt"
#define USB_FILE_BATCH             "usbstick/PrintBatch.txt"

#define FIFO_UNITREC_SHARED 0
#define FIFO_UNITREC_USB    1
#define FIFO_UNITREC_SIZE 12000


/* dir functions for event log and protocol log*/
#define DSORT_KEY_NAME_CS   0   // name case sensitive
#define DSORT_KEY_NAME_CI   1   // name case insensitive
#define DSORT_KEY_SIZE      2   // size
#define DSORT_KEY_TIME      3   // modification time

#define DSORT_DIR_ASC       1   // ascending
#define DSORT_DIR_DESC     -1   // descending


#define  sCodepage      "None;850;852;866;" // for write into system
#define  tCodepage      "None,850,852,866"  // only for prompt
#define  TX_PrtCodePage "Codepage{" tCodepage "}"


#if defined __IT8000E__
  #define PRINTER_PORTS  "Ethernet,COM1,COM2,COM3,COM4,USB"
  enum {PP_ETH,  pp1, pp2, pp3, pp4, PP_USB=5, PP_DUMMY};
  #define HOST_PORTS     "Ethernet,COM1,COM2,COM3,COM4"
#else
  #define PRINTER_PORTS  "Ethernet,COM1,COM2,USB"
  enum {PP_ETH, pp1, pp2, PP_USB=3, PP_DUMMY};
  #define HOST_PORTS     "Ethernet,COM1,COM2"
#endif

#define USB_PRINTER_DEVICE "/dev/usblp0"

void RefreshProdRepTexts(void) 
{
  STR_WPUnit = trim(string(WP.Unit));
  STR_ID_PRODUCTIONREPORT = lsub(TX_REPORT_PAGE);
  STR_ID_ACTUAL_PROD = lsub(TX_ID_ACTUAL_PROD);
  STR_ID_LIFETIME_PROD = lsub(TX_ID_LIFETIME_PROD);
  STR_ID_NOMINAL_WEIGHT = concat(lsub(TX_ID_NOMINAL_WEIGHT),"(",STR_WPUnit,")"); 
  STR_ID_TOTAL_WEIGHMENTS = lsub(TX_ID_TOTAL_WEIGHMENTS);  
  STR_ID_UNITS_DONE = lsub(TX_ID_UNITS_DONE);
  STR_ID_TOTAL_UNITS = lsub(TX_ID_TOTAL_UNITS);
  STR_ID_UNITS_ACCEPTED = lsub(TX_ID_UNITS_ACCEPTED);
  STR_ID_UNDERWEIGHT = lsub(TX_ID_UNDERWEIGHT);
  STR_ID_OVERWEIGHT = lsub(TX_ID_OVERWEIGHT);
  STR_ID_TOTAL_WEIGHT = lsub(TX_ID_TOTAL_WEIGHT);
  STR_ID_TOTAL_WEIGHT_W_UNIT = concat(lsub(TX_ID_TOTAL_WEIGHT),"(",STR_WPUnit,")");
  RefreshProdRepText = ON;
}

void RefreshProdRepData(void)
{
  STR_WPName = concat("WP:",trim(string(WP.Name)));
  STR_WPUnit = trim(string(WP.Unit));
  STR_WPNominalWeight = trim(string(WP.NominalWeight));
  STR_ProdTotalWeighmentsLT = trim(string(int(ProdTotalWeighmentsLT)));
  STR_ProdTotalUnitsCnt_Scale1 = trim(string(int(ProdTotalUnitsCnt[Scale1])));
  STR_ProdTotalUnitsCnt_Scale2 = trim(string(int(ProdTotalUnitsCnt[Scale2])));
  STR_ProdTotalUnitsCnt_ScaleBoth = trim(string(int(ProdTotalUnitsCnt[Scale1]+ProdTotalUnitsCnt[Scale2])));
  STR_ProdTotalUnitsLT = trim(string(int(ProdTotalUnitsLT)));
  STR_ProdAcceptUnitCnt_Scale1 = trim(string(int(ProdAcceptUnitCnt[Scale1])));
  STR_ProdAcceptUnitCnt_Scale2 = trim(string(int(ProdAcceptUnitCnt[Scale2])));
  STR_ProdAcceptUnitCnt_ScaleBoth = trim(string(int(ProdAcceptUnitCnt[Scale1]+ProdAcceptUnitCnt[Scale2])));
  STR_ProdTotalWeightLT = concat(trim(adj(ProdTotalWeightLT,14,2))," ",STR_WPUnit);
  STR_ProdUnderWeightCnt_Scale1 = trim(string(int(ProdUnderWeightCnt[Scale1])));
  STR_ProdUnderWeightCnt_Scale2 = trim(string(int(ProdUnderWeightCnt[Scale2])));
  STR_ProdUnderWeightCnt_ScaleBoth = trim(string(int(ProdUnderWeightCnt[Scale1]+ProdUnderWeightCnt[Scale2])));
  STR_ProdOverWeightCnt_Scale1 = trim(string(int(ProdOverWeightCnt[Scale1])));
  STR_ProdOverWeightCnt_Scale2 = trim(string(int(ProdOverWeightCnt[Scale2])));
  STR_ProdOverWeightCnt_ScaleBoth = trim(string(int(ProdOverWeightCnt[Scale1]+ProdOverWeightCnt[Scale2])));
  STR_ProdTotalWeight_Scale1 = trim(adj(ProdTotalWeight1,14,2));
  STR_ProdTotalWeight_Scale2 = trim(adj(ProdTotalWeight2,14,2));
  STR_ProdTotalWeight_ScaleBoth = trim(adj(ProdTotalWeight1+ProdTotalWeight2,14,2));
  STR_Date = trim(string(date));
  STR_Time = trim(string(time));
}

void RefreshBatchRepTexts(void) 
{
  STR_BATCH_CURRENT_PROD = lsub(TX_BATCH_PAGE);
  STR_BATCH_NAME = lsub(TX_BATCH_NAME);
  STR_ID_TOTAL_WEIGHT = lsub(TX_ID_TOTAL_WEIGHT);
  STR_BATCH_PRESET = lsub(TX_BATCH_PRESET);
  STR_BATCH_MIN_ACCEPTED = lsub(TX_BATCH_MIN_ACCEPTED);
  STR_ID_UNITS_DONE = lsub(TX_ID_UNITS_DONE);
  STR_BATCH_MAX_ACCEPTED = lsub(TX_BATCH_MAX_ACCEPTED);
  STR_ID_UNITS_ACCEPTED = lsub(TX_ID_UNITS_ACCEPTED);
  STR_BATCH_RESIDUE = lsub(TX_BATCH_RESIDUE);
  STR_ID_UNDERWEIGHT = lsub(TX_ID_UNDERWEIGHT);
  STR_STD_DEV = lsub(TX_STD_DEV);
  STR_ID_OVERWEIGHT = lsub(TX_ID_OVERWEIGHT);
  STR_AVERAGE = lsub(TX_AVERAGE);
  STR_BATCH_DETAILS = lsub(TX_BATCH_DETAILS);
  STR_BATCH_COUNTALL = lsub(TX_BATCH_COUNTALL);
  RefreshBatchRepText = ON;
}

void RefreshBatchRepData(void)
{
  STR_BatchTotalWeight = trim(string(Batch.TotalWeight));
  STR_BatchPreset      = trim(string(Batch.Preset));
  STR_BatchMinAccepted = trim(string(Batch.MinAccepted));
  STR_BatchUnitsDone   = trim(string(Batch.UnitsDone));
  STR_BatchMaxAccepted = trim(string(Batch.MaxAccepted));
  STR_BatchUnitsAccepted = trim(string(Batch.UnitsAccepted));
  STR_BatchResidue       = trim(string(Batch.Residue));
  STR_BatchUnderWeightCnt = trim(string(Batch.UnderWeightCnt));
  STR_BatchStdDev = trim(string(Batch.StdDev));
  STR_BatchOverWeightCnt = trim(string(Batch.OverWeightCnt));
  STR_BatchAvg = trim(string(Batch.Avg));
  STR_WPName = concat("WP:",trim(string(WP.Name)));
  STR_BatchName = trim(string(Batch.Name));
  STR_WPUnit = trim(string(WP.Unit));
  STR_BatchDetails = trim(string(Batch.Details));
  STR_Date = trim(string(date));
  STR_Time = trim(string(time));
}

//#define EPSON_SUPPORT
#ifdef EPSON_SUPPORT
  #define PRINT_BOLD  bold
#else
  #define PRINT_BOLD // = empty
#endif

form ProdRepTicket
{
    1   1 STR_ID_PRODUCTIONREPORT 
    1  22 STR_WPName
    1  75 STR_Date
    2  75 STR_Time
    3   1 STR_ID_ACTUAL_PROD   
    3  50 STR_ID_LIFETIME_PROD 
    4   1 STR_ID_NOMINAL_WEIGHT 
    4  32 STR_WPNominalWeight 
    //4  50 STR_WPUnit 
    4  50 STR_ID_TOTAL_WEIGHMENTS 
    4  75 STR_ProdTotalWeighmentsLT 
    5  22 "#1"
    5  32 "#2"
    5  42 "#1+#2"
    5  50 STR_ID_TOTAL_UNITS 
    5  75 STR_ProdTotalUnitsLT
    6   1 STR_ID_UNITS_DONE 
    6  22 STR_ProdTotalUnitsCnt_Scale1
    6  32 STR_ProdTotalUnitsCnt_Scale2
    6  42 STR_ProdTotalUnitsCnt_ScaleBoth
    6  50 STR_ID_TOTAL_WEIGHT 
    6  75 STR_ProdTotalWeightLT  
    7   1 STR_ID_UNITS_ACCEPTED 
    7  22 STR_ProdAcceptUnitCnt_Scale1 
    7  32 STR_ProdAcceptUnitCnt_Scale2 
    7  42 STR_ProdAcceptUnitCnt_ScaleBoth 
    8   1 STR_ID_UNDERWEIGHT 
    8  22 STR_ProdUnderWeightCnt_Scale1
    8  32 STR_ProdUnderWeightCnt_Scale2
    8  42 STR_ProdUnderWeightCnt_ScaleBoth 
    9   1 STR_ID_OVERWEIGHT 
    9  22 STR_ProdOverWeightCnt_Scale1 
    9  32 STR_ProdOverWeightCnt_Scale2 
    9  42 STR_ProdOverWeightCnt_ScaleBoth 
   10   1 STR_ID_TOTAL_WEIGHT_W_UNIT
   10  22 STR_ProdTotalWeight_Scale1 
   10  32 STR_ProdTotalWeight_Scale2 
   10  42 STR_ProdTotalWeight_ScaleBoth
   //10  50 STR_WPUnit 
   11   1 <13,10,12>  
}



form BatchRepTicket
{
    1   1 STR_BATCH_CURRENT_PROD 
    1  22 STR_WPName 
    2   1 STR_BATCH_NAME 
    2  22 STR_BatchName 
    4  38 STR_ID_TOTAL_WEIGHT 
    4  59 STR_BatchTotalWeight 
    4  71 STR_WPUnit 
    4   1 STR_BATCH_PRESET 
    4  22 STR_BatchPreset 
    5  38 STR_BATCH_MIN_ACCEPTED 
    5  59 STR_BatchMinAccepted 
    5   1 STR_ID_UNITS_DONE 
    5  22 STR_BatchUnitsDone 
    6  38 STR_BATCH_MAX_ACCEPTED 
    6  59 STR_BatchMaxAccepted 
    6  71 STR_WPUnit 
    6   1 STR_ID_UNITS_ACCEPTED 
    6  22 STR_BatchUnitsAccepted 
    7  38 STR_BATCH_RESIDUE 
    7  59 STR_BatchResidue 
    7  71 STR_WPUnit 
    7   1 STR_ID_UNDERWEIGHT 
    7  22 STR_BatchUnderWeightCnt 
    8  38 STR_STD_DEV 
    8  59 STR_BatchStdDev 
    8  71 STR_WPUnit 
    8   1 STR_ID_OVERWEIGHT 
    8  22 STR_BatchOverWeightCnt 
    9  38 STR_AVERAGE 
    9  59 STR_BatchAvg 
    9  71 STR_WPUnit 
   10   1 STR_BATCH_DETAILS 
   10  22 STR_BatchDetails 
    9   1 STR_BATCH_COUNTALL 
    9  22 STR_BatchCount 
   11   1 <13,10,12>  
    5  71 STR_WPUnit 
    1  63 STR_Date 
    2  63 STR_Time 
}




/* ************************************************************** */
/*   Get and set printer port parameters                          */
/* ************************************************************** */
int GetPrtPort(int PrtPort)      
{
  if ( PrtPort==ETHERNET_PRINTER_CHANNEL )
    return(PP_ETH);
  else if ( PrtPort == USB_PRINTER_CHANNEL )
    return(PP_USB);
  else
    return(PrtPort);
}

int SetPrtPort(int PrtPort, string PrinterIP ,string *pPrtPortPara)   // np+ V1.05
{
  if ( PrtPort==PP_ETH )
  {
    PrtPort      = ETHERNET_PRINTER_CHANNEL;
    pPrtPortPara = concat (PrinterIP, ETHERNET_PRINTER_PORT);
  }
  else
  {
    if ( PrtPort==PP_USB )
    {
      PrtPort = USB_PRINTER_CHANNEL;
      pPrtPortPara = USB_PRINTER_DEVICE;
    }
  }
  return(PrtPort);
}

void ClosePrtPort(int prtport)
{
  if (prtport == ETHERNET_PRINTER_CHANNEL || prtport == USB_PRINTER_CHANNEL)
    pclose (prtport);
}

bool OpenPrtPort (int prtport, string prtportpara)
{
int err;

  if(prtport <=7)         return (ON);
  if(pconnected(prtport)) return (ON);
  
  err = popen(prtport, prtportpara);
  if (err != 0)
   {
    pclose (prtport);
    return (OFF);
   }
              
  if (!ptxready(prtport))
    return(OFF);

 return (ON);
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ReadLogFiles
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/04
--  
--  Purpose           : Read available log-files into a string array. 
--                    ; returns number of available files.                  
--                                
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
int ReadLogFiles(string dir, int criteria, int direction, string ext)
{
string fname[40];
int    i,j=0, Temp_len, err;

  for(i=0;i<MAX_LOG_FILES;i++) 
  LogFiles[i]="";
  
  if (dopen (0,dir))
  {
    dsort(0,criteria,direction);  // search for oldest log file...
    while (dread(0,fname) && j<MAX_LOG_FILES)
    {
      for (i=length(fname)-1;i>0;i--) 
      {
        if (fname[i]=='.') break;
      }  
      Temp_len = length(concat(UNIT_RECORD,"123456"));
      if (sub(fname,0,Temp_len-6)==UNIT_RECORD && sub(fname,Temp_len+1,9)==ext || ext=="*") LogFiles[j++]=fname;
      else err = fremove(concat(dir,"/",fname));
    }  
    dclose (0);
    return(j);
  }
  return(-1);
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : DeleteLogFiles
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/04
--  
--  Purpose           : Used to delete oldest log file on USB Stick 
--                    ;                  
--                                
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void DeleteLogFiles(string dir, int criteria, int direction)
{
string fname[40] = "";
int err;


  if (dopen(0,dir))
  {
    dsort(0,criteria,direction); // Sort names by date/time, oldest first
    if (dread(0,fname)) 
    err = fremove(concat(dir,"/",fname));
    dclose(0);  
  }
}


/*------------------------------------------------------------------------------- 
--  Procedure Name    : SendPageToPrinter
--  Created by        : Steve Santerre
--  Last modified on  : 2017/09
--  
--  Purpose           : Used to Send Report Page on desired Printer 
--                    ;                  
--                                
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------------*/ 
void SendPageToPrinter(int Scrn_No,int PrtPortTest,string PrtPortPara,string PortName,bool Printer)
{

                           /* Other commands available */
                           //print2string( WeighingTicket,StringName, "example.lab"); //.lab can be dummy
                           //print2file (Test, "path/FileName.txt", "example.lab");   //.lab can be dummy

string ShowErrorMsg[40] ="";
bool PortOpened=OFF,USBFile=OFF;
  
  if(PrtPortTest != USBFILE_PRINTREPORT_CHANNEL)
    PortOpened = OpenPrtPort(PrtPortTest, PrtPortPara);
  else
    USBFile = ON;
      
  if ( PortOpened || USBFile )
      {
        switch (Scrn_No) 
        {
    
           case SCREEN_REPORT:  
                                if (!RefreshProdRepText) RefreshProdRepTexts();
                                RefreshProdRepData();
                                if(USBFile)
                                  {
                                   print2file (ProdRepTicket, USB_FILE_REPORT, "dummy1.lab");
                                  } 
                                else
                                  print(PrtPortTest, ProdRepTicket);
                             
                             break;
           
           case SCREEN_BATCH:  
                                if (Batch.CountAll) STR_BatchCount = "ON"; else STR_BatchCount = "OFF";
                                if (!RefreshBatchRepText) RefreshBatchRepTexts();
                                RefreshBatchRepData();
                                if(USBFile)
                                 {
                                  print2file (BatchRepTicket, USB_FILE_BATCH, "dummy2.lab");
                                 } 
                                else
                                  print(PrtPortTest, BatchRepTicket);
                        break;
        }
         
        if(!USBFile)
        {
         if(!ptxready(PrtPortTest))
          ShowErrorMsg = concat("511 ",PortName," Printer connection lost");

        
         if( PrtPortTest > 7 && Printer) // Port 1 à 7 réservé à série. Port 8 = USB et Port 9 = Ethernet
          pclose(PrtPortTest);
        }  
      }
      else 
      ShowErrorMsg = concat("511 ",PortName," Printer connection lost");
    
    if ( ShowErrorMsg != "")
     {
       SystemWarningCode =  ShowErrorMsg;    
     }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : PrintPage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/02/24
--  
--  Purpose           : Print selected Page using formatted form 
--                    ;                      
--                                
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : none
--------------------------------------------------------------------------------*/ 
void PrintPage (int Scrn_No)
{
int err, PrtPortTest;
   
         if(MC.PortCOM2Cfg == COM2FctReportToPrinter)     
          {
           PrtPortTest = COM2_PRINTER_CHANNEL;
           SendPageToPrinter(Scrn_No,PrtPortTest,PrtPortPara,TX_PortCom2,ON);
          }
          
          if(MC.PortUSBCfg == USBFctReportToPrinter)     
          {
           PrtPortTest = USB_PRINTER_CHANNEL; PrtPortPara = USB_PRINTER_DEVICE;
           SendPageToPrinter(Scrn_No,PrtPortTest,PrtPortPara,TX_PortUSB,ON);
          }
          
          if(MC.PortETHCfg == ETHFctReportToPrinter)     
          {
           PrtPortTest = ETHERNET_PRINTER_CHANNEL; PrtPortPara = concat (MC.PrinterIP, ETHERNET_PRINTER_PORT);
           SendPageToPrinter(Scrn_No,PrtPortTest,PrtPortPara,TX_PortEthernet,ON);
          }
          
           PrtPortTest = ETHERNET_PRINTREPORT_CHANNEL; PrtPortPara = ETHERNET_PRINTREPORT_PORT;
           SendPageToPrinter(Scrn_No,PrtPortTest,PrtPortPara,TX_PortEthernet,OFF);
           
           PrtPortTest = USBFILE_PRINTREPORT_CHANNEL;
           SendPageToPrinter(Scrn_No,PrtPortTest,PrtPortPara,TX_PortUSB,OFF);
           
}  

/*------------------------------------------------------------------------------- 
--  Procedure Name    : SendUnitRecToFile
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/02/24
--  
--  Purpose           : Print selected Page using formatted form 
--                    ;                      
--                                
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : none
--------------------------------------------------------------------------------*/ 
void SendUnitRecToFile(string ticket,int Destination)
{
string  FileName[64],Path[20],ticket_temp[256];
string ShowErrorMsg[40] ="",DestName[20],FileNameMem[64];
int Dir,NumberOfFiles,FifoNbr,ticket_len;
bool InvalidDest;
        
        switch(Destination)
        {
         case CSV_ON_USB:
          Path = USB_PATH;
          Dir = DIR_USB;
          DestName = concat(TX_PortUSB,"memory");
          NumberOfFiles = 7;
          FileNameMem = USBFileNameMem;
          FifoNbr = FIFO_UNITREC_USB;
          break;
          
         case CSV_ON_SHARED:
          Path = SHARED_PATH;
          Dir = DIR_SHARED;
          DestName = concat(SHARED_PATH,"memory");
          NumberOfFiles = 3;
          FileNameMem = SHAREDFileNameMem;
          FifoNbr = FIFO_UNITREC_SHARED;
          break;
          
         default:
          InvalidDest = ON;
          break;
        }   
        
       if(!InvalidDest)
       { 
        CurLogFiles = ReadLogFiles(Path,DSORT_KEY_TIME,DSORT_DIR_DESC,"txt");
        
        if (dopen (Dir,Path)) 
        { 

          FileName = concat(Path,"/",UNIT_RECORD, FileName_Date,".txt");           
          
          if (FileName != FileNameMem)
          {
            if(fexists(FileName)) fremove(FileName);

             switch(Destination)
             {
              case CSV_ON_USB:
               USBFileNameMem = FileName;
               break;
          
              case CSV_ON_SHARED:
               SHAREDFileNameMem = FileName;
               break;
             }
               
          }

           err = fopen (Destination,FileName );
           if (err!=0) 
           {
            ShowErrorMsg = concat("501 ",DestName,":cannot open file");
           }
           
           else
           {  
             for(;;)
             {
              ticket_temp = "";
              fifo_read (FifoNbr, ticket_temp, ticket_len);
              if(ticket_len == 0)
                break;
              if (fwrite (Destination, ticket_temp,ticket_len) != ticket_len) 
               {
                ShowErrorMsg = concat("503 ",DestName," full");
                break;
               }
             }
           }    

             err=fclose (Destination);
             dclose (Dir);
             
             /* Delete files  */
             if (CurLogFiles > NumberOfFiles || DeleteLogBypass )
             {
               do  
               {
                 DeleteLogFiles(Path,DSORT_KEY_NAME_CS,DSORT_DIR_ASC);
                 CurLogFiles = ReadLogFiles(Path,DSORT_KEY_TIME,DSORT_DIR_DESC,"*");
               }
               while (CurLogFiles > NumberOfFiles);  
             }
             
         }  
        else  ShowErrorMsg = concat("504 ",DestName,":cannot open dir.");
       } 
        if ( ShowErrorMsg != "")
        {
         SystemWarningCode =  ShowErrorMsg;    
        } 
}

void SendUnitRecToPort(int PrtPort,string PrtPortPara,string ticket)
{
string ShowErrorMsg[40] ="",PortName[10];

    switch(PrtPort)
     {
       case USB_PRINTER_CHANNEL:
        PortName = TX_PortUSB;
        break;
       
       case COM2_PRINTER_CHANNEL:
        PortName = TX_PortCom2;
        break;
      
      case ETHERNET_UNITRECORD_CHANNEL:
        PortName = TX_PortEthernet;
        break;
         
       default:
        PortName = "Invalid Port";
        break;
        
        
     }
             
 if (OpenPrtPort(PrtPort, PrtPortPara))
    {
     writestring (PrtPort, ticket);
    }
 else 
    ShowErrorMsg = concat("510 ", PortName," connection lost"); 
      
    if ( ShowErrorMsg != "")
     {
       SystemWarningCode =  ShowErrorMsg;    
     }
}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : PrintUnitRecord
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/04
--  
--  Purpose           : Print selected Page using formatted form 
--                    ;                      
--                                
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : none
--------------------------------------------------------------------------------*/ 
void PrintUnitRecord (int ScaleNo)
{
//int err, Ftell, CurLogFiles;
string ShowErrorMsg[40] ="";

              
          SendUnitRecToFile(TicketInfo,CSV_ON_SHARED);                 
       switch(MC.PortUSBCfg)
       {
         case USBFctUnitRecString:  
           PrtPort = USB_PRINTER_CHANNEL; PrtPortPara = USB_PRINTER_DEVICE; 
           SendUnitRecToPort( PrtPort,PrtPortPara,TicketInfo);
           break;
       
         case USBFctUnitRecFile:    
          SendUnitRecToFile(TicketInfo,CSV_ON_USB);
          break;
       
         default:                   break;
       }
       
       if(MC.PortCOM2Cfg == COM2FctUnitRecString)
        {
         PrtPort = COM2_PRINTER_CHANNEL; PrtPortPara = "";
         SendUnitRecToPort( PrtPort,PrtPortPara,TicketInfo);
        } 
        
         PrtPort = ETHERNET_UNITRECORD_CHANNEL; PrtPortPara = concat ("",ETHERNET_UNITRECORD_PORT);
         SendUnitRecToPort(PrtPort,PrtPortPara,TicketInfo);
         
}


/*********************************************************/
/******              Print Task                      *****/
/*********************************************************/

void PrintTask(void)
{

 for(;;)
 {
 
 if (PrintRequest)
   {
     PrintBegin = systemtimer_ms();
     PrintPage (Current_Screen);
     PrintEnd = systemtimer_ms();
     printTime = PrintEnd - PrintBegin;
     PrintRequest = OFF;
   }
   
 delay(0.5);

 }
} 


/* ************************ */
/*  Continuous Output Task  */
/* ************************ */
void ContOutTask(void)
{
 bool ContOutActive,portopened[2];
 int starttime,scaleno,PortNbr[2];
 float taskduration;
 string PortParam[2][25],weight[8],PortName[10];
 string ShowErrorMsg[40] ="";
 char zero,unsettled,stableindicator;
 
 unsettled = '~';
 zero   = '¯';
 
 for(;;)
 {
  starttime = systemtimer_ms();
  
  if(MC.ContPort != ContPortMem)
  {
    ContPortMem = MC.ContPort;
    switch(MC.ContPort)
    {
     case CONTPortNone:   
                        ContOutActive = OFF;
                        break;
     
     case CONTPortSIM:    
                        ContOutActive = ON;
                        PortName = TX_ContOutSIM3_4;
                        PortNbr[Scale1]   = COM3_CONTOUT_CHANNEL;
                        PortNbr[Scale2]   = COM4_CONTOUT_CHANNEL;
                        PortParam[Scale1] = "";
                        PortParam[Scale2] = "";
                        break;
     
     case CONTPortETH:  
                        ContOutActive = ON;
                        PortName = TX_PortEthernet; 
                        PortNbr[Scale1]   = ETHERNET_CONTOUT1_CHANNEL;
                        PortNbr[Scale2]   = ETHERNET_CONTOUT2_CHANNEL;
                        PortParam[Scale1] = ETHERNET_CONTOUT1_PORT;
                        PortParam[Scale2] = ETHERNET_CONTOUT2_PORT; 
                        break;
     
     default:           
                        ContOutActive = OFF;
                        break;
    }
  }
  
   if(ContOutActive)
   {
    for(scaleno=1;scaleno<=2;scaleno++)
    {
     portopened[scaleno-1] = OpenPrtPort(PortNbr[scaleno-1], PortParam[scaleno-1]);
     if(portopened[scaleno-1])
      {
       weight = adj(NetWeight[scaleno-1],8,DP[scaleno-1]);
       weight = concat(space(8-length(weight)),weight);
       if(!IsSettled[scaleno-1]) stableindicator = unsettled;
       else if(IsZero[scaleno-1]) stableindicator = zero;
       else stableindicator = ' ';
       writestring (PortNbr[scaleno-1], concat(space(1),stableindicator,weight,space(1),WP.Unit,"N",CRLF));
      }
     else 
      ShowErrorMsg = concat("510 ", PortName," connection lost"); 
      
    if ( ShowErrorMsg != "")
     {
       SystemWarningCode =  ShowErrorMsg;    
     }  
    }
   } 
     
  taskduration = (systemtimer_ms()-starttime)/1000;
  delay(ContOutIntervalTime-taskduration);
 }   

}
     
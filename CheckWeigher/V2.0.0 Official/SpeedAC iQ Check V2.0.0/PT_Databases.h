

/**************************************************************************** 
  Databases  
*****************************************************************************/




/**************************************************************************** 
  IO Table  
*****************************************************************************/
dbase TX_IO_CONFIG  IOdb[MAX_IO]
{  
  TX_NO                  int     No;             selectmode=input; //No%2.0;
  TX_NAME                string  Name[24];
  TX_ADDRESS             decimal Address%2.0;
  TX_ENABLE              bool    Enable;
  TX_INPUT               bool    Input;

}



/**************************************************************************** 
  Languages 
*****************************************************************************/


dbase TX_LANGUAGE  Language[MAX_LANG]
{  
  TX_NO                decimal No%2.0;            selectmode=input;
  TX_LANGUAGE          string  Name[24];
                       bool    Translated;
}

/**************************************************************************** 
  Flexible IOs
*****************************************************************************/


dbase TX_FLEXIONAME  FlexIO[MAX_FLEXIO]
{  
  TX_FLEXOUTPUT        int      No;                selectmode=input;
  TX_FLEXIOTYPE        int      TypeOn;
  TX_FLEXIOTYPE        int      TypeOff;
  TX_FLEXSPSIGN        bool     SPSignOn;
  TX_FLEXSPSIGN        bool     SPSignOff;
  TX_FLEXSETPOINT      int      SPOn;
  TX_FLEXSETPOINT      int      SPOff;
  TX_FLEXIO            int      IoOn;
  TX_FLEXIO            int      IoOff;
  TX_FLEXTIMER         int      TOn; 
  TX_FLEXTIMER         int      TOff;          
  TX_FLEXSWITCH        bool     IoSwOff;
  TX_FLEXSWITCH        bool     IoSwOn;
  TX_FLEXIOVALID       bool     IoOnOk;
  TX_FLEXIOVALID       bool     IoOffOk;
  TX_FLEXCNTMODE       int      CntMode; 
  TX_FLEXPRESOURCE     int      CntPreSource;
  TX_FLEXINITDELAY     decimal  InitDelay%4.2;
  TX_FLEXONTIME        decimal  OnTime%4.2;     
  TX_FLEXOFFTIME       decimal  OffTime%4.2;
                       int      IoEnumOn;
                       int      IoEnumOff; 
                       string   IoNameOn[24];  
                       string   IoNameOff[24];                    
  
}
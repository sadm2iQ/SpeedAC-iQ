/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateAnalogTestPage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/09
--  
--  Purpose           : Create Analog OUTPUT Test page
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateAnalogTestPage(void) 
{
  begindraw();
  createpage(PAGE_IO_ANALOGTEST);  
  page_background (PAGE_IO_ANALOGTEST, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); //HBOX #4    
        
        // WE CARE     Page Info:       MODE         FAULT
         beginlayout(LAYOUT_TYPE_HBOX, MIN_EDGE_DISTANCE, FCT_BUTTON_DISTANCE); // HBOX #5
              CreatePTLogoHeader();
              CreateHeader (IO_SEARCH_ID, 400, 50, "", align_hcenter, concat (space(1), lsub(TX_ANALOGTEST_PAGE), space(1)), FT_MEDIUM_SIZE);
              createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
         endlayout(); // End of HBOX #5 

        //Fault and Mode display
        CreateModeFltDisplay();

       endlayout();  // End of HBOX #4


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6


CreatePromptField (IO_SPACE_1,    CL_PT_BLUE, false,                       "", FT_STANDARD_SIZE, 1, HT_IO_HEADER, 0, true);         
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER_LEFT,   CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_ANALOG_INPUT), FT_MEDIUM_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false  );
            endrow();
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_IO_NAME), FT_STANDARD_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, true, WD_IO_ADDRESS, HT_IO_HEADER, true );
              CreateIOField (IO_VALUE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_IO_VALUE), FT_STANDARD_SIZE, true, WD_IO_ANALOG_VALUE, HT_IO_HEADER, true );              
            endrow();

            beginrow(); // First row 
              CreateIOField         (IO_ID_ROW1,    CL_PT_BLUE, CL_PT_WHITE, false, "AIN1", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW1, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateOutputDataField (IO_STATE_ROW1, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE, HT_IO_HEADER, true);   
            endrow();
              
            beginrow(); // Second row 
              CreateIOField         (IO_ID_ROW2,    CL_PT_BLUE, CL_PT_WHITE, false, "AIN2", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateOutputDataField (IO_STATE_ROW2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, true);      
            endrow();
            
            beginrow(); // Third row 
              CreateIOField         (IO_ID_ROW3,    CL_PT_BLUE, CL_PT_WHITE, false, "", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW3, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateOutputDataField (IO_STATE_ROW3, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, true);      
            endrow();
            
            beginrow(); // Fourth row 
              CreateIOField         (IO_ID_ROW4,    CL_PT_BLUE, CL_PT_WHITE, false, "", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW4, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateOutputDataField (IO_STATE_ROW4, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, true);
            endrow();
                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, true, "", FT_IO_HEADER, false, WD_ANALOGTEST_SPACE, HT_IO_HEADER, true  ); 

        // Layout of second column on the right 
           
          
          beginlayout(LAYOUT_TYPE_GRID, 0); // 

            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER_RIGHT,  CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_ANALOG_OUTPUT), FT_MEDIUM_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false  );
            endrow(); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_IO_NAME), FT_STANDARD_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, false, WD_IO_ADDRESS, HT_IO_HEADER, true );
              CreateIOField (IO_VALUE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_IO_VALUE), FT_STANDARD_SIZE, false, WD_IO_HEADER, HT_IO_HEADER, false );
              CreateIOField (IO_UNIT_HEADER2,     CL_PT_BLUE, CL_PT_WHITE, true, "", FT_STANDARD_SIZE, false, WD_IO_PERCENT, HT_IO_HEADER, true );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, true, lsub(TX_IO_TEST), FT_STANDARD_SIZE, false, WD_IO_HEADER, HT_IO_HEADER, false );
            endrow();
            
            beginrow(); // First row 
              CreateIOField         (IO_ID_ROW7,    CL_PT_BLUE, CL_PT_WHITE, false, "AOUT1", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW7, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateInputIO         (IO_STATE_ROW7, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 3, 0, lsub(TX_IO_ENTER_ANALOG), WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, true); 
              CreateIOField         (IO_UNIT_ROW7,  CL_PT_BLUE, CL_PT_WHITE, true, "%", FT_IOPAGES_SIZE, false, WD_IO_PERCENT, HT_IO_HEADER, false );
              CreateOnOffBoxField   (IO_CHECK_ROW7, 25, WIDGET_TEXT_ALIGN_CENTER, true, BTN_TESTON, BTN_TESTOFF);
              widget_attribute      (IO_CHECK_ROW7, WIDGET_ATTRIBUTE_AUTO_CHANGE_STATE, "0");      
            endrow();
            
            beginrow(); // Second row 
              CreateIOField         (IO_ID_ROW8,    CL_PT_BLUE, CL_PT_WHITE, false, "AOUT2", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW8, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateInputIO         (IO_STATE_ROW8, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 3, 0, lsub(TX_IO_ENTER_ANALOG), WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, true);
              CreateIOField         (IO_UNIT_ROW8,  CL_PT_BLUE, CL_PT_WHITE, true, "%", FT_IOPAGES_SIZE, false, WD_IO_PERCENT, HT_IO_HEADER, false ); 
              CreateOnOffBoxField   (IO_CHECK_ROW8, 25, WIDGET_TEXT_ALIGN_CENTER, true, BTN_TESTON, BTN_TESTOFF); 
              widget_attribute      (IO_CHECK_ROW8, WIDGET_ATTRIBUTE_AUTO_CHANGE_STATE, "0");     
            endrow();
            
            beginrow(); // Third row 
              CreateIOField         (IO_ID_ROW9,    CL_PT_BLUE, CL_PT_WHITE, false, "", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW9, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateIOField         (IO_STATE_ROW9, CL_PT_BLUE, CL_PT_WHITE, true, "", FT_IOPAGES_SIZE, false, WD_IO_HEADER, HT_IO_HEADER, true );      
            endrow();
            
            beginrow(); // Fourth row 
              CreateIOField         (IO_ID_ROW10,    CL_PT_BLUE, CL_PT_WHITE, false, "", FT_IOPAGES_SIZE, false, WD_IO_ANALOG_NAME, HT_IO_HEADER, false );
              CreateOutputDataField (IO_INPUT_ROW10, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, true);
              CreateIOField         (IO_STATE_ROW10, CL_PT_BLUE, CL_PT_WHITE, true, "", FT_IOPAGES_SIZE, false, WD_IO_HEADER, HT_IO_HEADER, true );      
            endrow();
                   
          endlayout(); // End of Grid Layout

//CreatePromptField (IO_SPACE_2,    CL_PT_BLUE, false,                       "", FT_STANDARD_SIZE, 1, HT_IO_HEADER, 0, true);         
                 
        endlayout(); // End of HBOX #6  
       
       createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, false);
     DrawNavButtons (SCREEN_ANALOGTEST, true, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshAnalogTestScreen
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/03/02
--  
--  Purpose           : Refresh Analog Test screen display 
--                      
--  Value Parameters  :
--  Variable Params   : Scrn_No = screen number of the page to refresh 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshAnalogTestScreen(int Scrn_No)
{
int i;


 begindraw(); 
                                                        
                widget_text (IO_SEARCH_ID, lsub(TX_ANALOGTEST_PAGE)); 
                // Analog Input 

                  widget_text   (IO_INPUT_ROW1, "1");
                  widget_enable (IO_INPUT_ROW1, false);
                  widget_text   (IO_STATE_ROW1, "0");
                  widget_enable (IO_STATE_ROW1, false);
                  
                  widget_text   (IO_INPUT_ROW2, "2");
                  widget_enable (IO_INPUT_ROW2, false);
                  widget_text   (IO_STATE_ROW2, "0");
                  widget_enable (IO_STATE_ROW2, false);

   
                // Analog Output                               
                  
                  widget_text (IO_INPUT_ROW7, "1");
                  widget_enable (IO_INPUT_ROW7,  DAM_Active);
                  widget_text (IO_STATE_ROW7, trim(AOUT1_Preset));
                  widget_enable (IO_STATE_ROW7,  DAM_Active);
                  widget_text (IO_CHECK_ROW7, IO_Force_AOUT1); 
                  widget_enable (IO_CHECK_ROW7,  DAM_Active);
                  
                  widget_text   (IO_INPUT_ROW8, "2");
                  widget_enable (IO_INPUT_ROW8,  false);
                  widget_text (IO_STATE_ROW8, "0");
                  widget_enable (IO_STATE_ROW8,  false);
                  widget_text (IO_CHECK_ROW8, IO_Force_AOUT2);
                  widget_enable (IO_CHECK_ROW8,  false);
                 
 enddraw();           
}

void StopAnalogOut(void)
{     
   FeedingStop();
   IO_Force_AOUT1_MEM = OFF;
   IO_Force_AOUT1 = OFF;
}

void Set_Analog_Position(void)
{
bool RefreshAout;
int test, test2;
float Analog_OutputNew;

  Analog_OutputNew  = (AOUT1_Preset*0.01);
  if (Analog_Output != Analog_OutputNew)
    {
     Analog_Output = Analog_OutputNew;
     RefreshAout = ON;
    } 

  if (IO_Force_AOUT1 && (!IO_Force_AOUT1_MEM || RefreshAout) && DAM_Active)
  {
     if(!IO_Force_AOUT1_MEM) 
      if (iQOpenConnection (SCALE_CHANNEL, "127.0.0.1"))
        {
           SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_SMART); 
            SetAnalogOutputVal (0, 100);
            iQSetEnableSignalOutput (SCALE_CHANNEL, SCALE_NUMBER, IO_Address[O_DribbleFeed]); 
            SetTargetValue(TargetWeight[Scale1]*UnitIQtoADM); 
        }

    Analog_Output = (AOUT1_Preset*0.01);
    iQFeedingDebugOutput (SCALE_CHANNEL, SCALE_NUMBER, Analog_Output, IO_Address[O_DribbleFeed], ON);
    test = bit((IO_Address[O_DribbleFeed]),test2);
    IO_Force_AOUT1_MEM = ON;
  }
  if (!IO_Force_AOUT1 && IO_Force_AOUT1_MEM && DAM_Active || LT_GEN)
    { 
      StopAnalogOut();
    }

}
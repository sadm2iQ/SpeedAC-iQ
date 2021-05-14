﻿/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateMPPage1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/24
--  
--  Purpose           : Creation of Machine Parameters page #1   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateMPPage1(void) 
{
  begindraw();
  createpage(PAGE_MP_1);  
  page_background (PAGE_MP_1, BackgroundColor);//"white");
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (MP_SEARCH_ID,WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_MACHINEPARAMETERS_PAGE)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header
 

       // Left display with weighing in-/outputs without infoline
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // Grid Layout #1
            beginrow(); // First row with three columns 
              CreatePromptField (MP_ROW1_ID,    CL_PT_BLUE, false,                        lsub(TX_MPSAMPLEFREQUENCY), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked );
              CreateInputField  (MP_ROW1_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 7, 0, false, lsub(TX_MPSAMPLEFREQUENCY), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW1_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Second row with three columns
              CreatePromptField (MP_ROW2_ID,    CL_PT_BLUE, false,                        lsub(TX_MPSAMPLESIZE), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW2_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 0, false, lsub(TX_MPSAMPLESIZE), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW2_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Thirth row with three columns
              CreatePromptField (MP_ROW3_ID,     CL_PT_BLUE, false,                      lsub(TX_MPZEROFREQUENCY), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW3_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 7, 0, false, lsub(TX_MPZEROFREQUENCY), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW3_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();   
                     
            beginrow(); // Fourth row with three columns
              CreatePromptField (MP_ROW4_ID,    CL_PT_BLUE, false,                       lsub(TX_MPZEROLIMIT), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW4_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 4, 2, false, lsub(TX_MPZEROLIMIT), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW4_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();

            beginrow(); // Fifth row with three columns
              CreatePromptField   (MP_ROW5_ID,     CL_PT_BLUE, false,                    lsub(TX_MPAUTOZEROOFF), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateComboBoxField (MP_ROW5_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_OFF), lsub(TX_ON), "", "", "", WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField     (MP_ROW5_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "" , WD_UNIT, HT_MP_BOX, widget_locked);
            endrow();

            beginrow(); // Sixth row with three columns
              CreatePromptField     (MP_ROW6_ID,     CL_PT_BLUE, false,                  lsub(TX_MPSCREENSAVERTIME), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField      (MP_ROW6_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 2, 0, false, lsub(TX_MPSCREENSAVERTIME), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField       (MP_ROW6_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         lsub(TX_MINUTE_UNIT) , WD_UNIT, HT_MP_BOX, widget_locked);
            endrow();
                   
          endlayout();  //End of Grid Layout #1
          
        // Spacing between columns
          CreatePromptField (MP_SPACE1,    CL_PT_BLUE, false,                       "", FT_STANDARD_SIZE, WD_MP_SPACE, HT_MP_DESCRIPTION, No_Margin, widget_locked);
        
        // Second Column of recipe page  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // Grid Layout #2
            beginrow(); // First row with three columns 
              CreatePromptField (MP_ROW7_ID,    CL_PT_BLUE, false,                        lsub(TX_MPDISCHDOORMAXTIME) , FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW7_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, false, lsub(TX_MPDISCHDOORMAXTIME), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW7_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked);
            endrow();     
            
            beginrow(); // Second row with three columns
              CreatePromptField (MP_ROW8_ID,    CL_PT_BLUE, false,                        lsub(TX_MPSLOWCYCLETIME), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW8_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, false, lsub(TX_MPSLOWCYCLETIME), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW8_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();    
            
            beginrow(); // Third row with three columns 
              CreatePromptField (MP_ROW9_ID,    CL_PT_BLUE, false,                        lsub(TX_MPFEEDGATEMAXTIME) , FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW9_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, false, lsub(TX_MPFEEDGATEMAXTIME), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW9_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();                              
          
            beginrow(); // Fourth row with three columns  
              CreatePromptField (MP_ROW10_ID,    CL_PT_BLUE, false,                       lsub(TX_MPOUTOFTOLTIME) , FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW10_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 7, 2, false, lsub(TX_MPOUTOFTOLTIME), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW10_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();            

            beginrow(); // Fifth row with three columns 
              CreatePromptField (MP_ROW12_ID,    CL_PT_BLUE, false,                        lsub(TX_MPSTABTIMELIMIT), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW12_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, false, lsub(TX_MPSTABTIMELIMIT), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW12_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow(); 
            
            beginrow(); // Sixth row with three columns
              CreatePromptField (MP_ROW11_ID,    CL_PT_BLUE, false,                       lsub(TX_MPFEEDRATEFILTERRATIO) , FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW11_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL,4, 3, false, lsub(TX_MPFEEDRATEFILTERRATIO), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW11_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();  

            
                    
          endlayout(); // End of Grid Layout #2
          
       
        endlayout(); // End of HBOX #6  // End of left display in-/outputs without infoline HBOX
       
       createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, false);
   DrawNavButtons (SCREEN_MP1, true, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_TIMEDATE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateMPPage2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/24
--  
--  Purpose           : Creation of Machine Parameters page #2   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateMPPage2(void) 
{
  begindraw();
  createpage(PAGE_MP_2);  
  page_background (PAGE_MP_2, BackgroundColor);//"white");
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // Split left screen in in-/outputs and infoline

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (MP_SEARCH_ID,WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_MACHINEPARAMETERS_PAGE)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Left display with weighing in-/outputs without infoline
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            beginrow(); // First row with three columns 
              CreatePromptField   (MP_ROW13_ID,     CL_PT_BLUE, false,                    lsub(TX_MPCORRECTIONONAVERAGE), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateComboBoxField (MP_ROW13_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_OFF), lsub(TX_ON), "", "", "", WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField     (MP_ROW13_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Second row with three columns
              CreatePromptField (MP_ROW14_ID,    CL_PT_BLUE, false,                       lsub(TX_MPCUTOFFCORRECTIONLIMIT), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW14_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 4, 2, false, lsub(TX_MPCUTOFFCORRECTIONLIMIT), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW14_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Thirth row with three columns
              CreatePromptField (MP_ROW15_ID,    CL_PT_BLUE, false,                        lsub(TX_MPDFWEIGHTCORRECTION), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW15_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 3, 1, false, lsub(TX_MPDFWEIGHTCORRECTION), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW15_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(TX_PERC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();   
                     
            beginrow(); // Fourth row with three columns
              CreatePromptField (MP_ROW16_ID,    CL_PT_BLUE, false,                        lsub(TX_MPCUTOFFCORRECTION), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW16_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 2, false, lsub(TX_MPCUTOFFCORRECTION), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW16_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(TX_PERC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked ); 
            endrow();

            beginrow(); // Fifth row with three columns
              CreatePromptField (MP_ROW17_ID,    CL_PT_BLUE, false,                        lsub(TX_MPMAXFEEDRATE), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW17_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 10, 2, false, lsub(TX_MPMAXFEEDRATE), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW17_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(WP.Unit+TX_PER_HOUR), WD_UNIT, HT_MP_BOX, widget_locked ); 
            endrow();

            beginrow(); // Sixth row with three columns
              CreatePromptField (MP_ROW18_ID,    CL_PT_BLUE, false,                        lsub(TX_MPLOWFEEDINGTIME), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW18_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 4, 2, false, lsub(TX_MPLOWFEEDINGTIME), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW18_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked ); 
            endrow();
                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreatePromptField (MP_SPACE1,    CL_PT_BLUE, false,                       "", FT_STANDARD_SIZE, WD_MP_SPACE, HT_MP_DESCRIPTION, No_Margin, widget_locked);
        
        // Second Column of recipe page  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 

            beginrow(); // Fourth row with three columns  
              CreatePromptField  (MP_ROW22_ID,     CL_PT_BLUE, false,                  lsub(TX_MPSTDFILTER), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField   (MP_ROW22_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 2, 0, false, lsub(TX_MPSTDFILTER), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField    (MP_ROW22_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                            "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Sixth row with three columns
              //CreatePromptField     (MP_ROW24_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              //CreateOutputTextField (MP_ROW24_INPUT,                                      "", WD_MP_BOX, HT_MP_BOX, widget_locked);
              //CreateUnitField       (MP_ROW24_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,       "", WD_UNIT, HT_MP_BOX, widget_locked );
              CreatePromptField (MP_ROW24_ID,    CL_PT_BLUE, false,                        lsub(TX_MPMAINTCYCCLE), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (MP_ROW24_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 0, false, lsub(TX_MPMAINTCYCCLE), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW24_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              "", WD_UNIT, HT_MP_BOX, widget_locked ); 
            endrow(); 
                                         
            beginrow(); // First row with three columns 
              CreatePromptField (MP_ROW19_ID,     CL_PT_BLUE, false,                      lsub(TX_MPENDOFSHIFT1), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW19_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_TIME, 5, 0, WIDGET_TEXT_ALIGN_RIGHT, lsub(TX_MPENDOFSHIFT1), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW19_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                            "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();     
            
            beginrow(); // Second row with three columns  
              CreatePromptField (MP_ROW20_ID,    CL_PT_BLUE, false,                       lsub(TX_MPENDOFSHIFT2), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW20_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_TIME, 5, 0, WIDGET_TEXT_ALIGN_RIGHT, lsub(TX_MPENDOFSHIFT2), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW20_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();    
            
            beginrow(); // Third row with three columns 
              CreatePromptField (MP_ROW21_ID,     CL_PT_BLUE, false,                      lsub(TX_MPENDOFSHIFT3), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (MP_ROW21_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_TIME, 5, 0, WIDGET_TEXT_ALIGN_RIGHT, lsub(TX_MPENDOFSHIFT3), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField   (MP_ROW21_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                            "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();                              
          
            beginrow(); // Fifth row with three columns 
              CreatePromptField  (MP_ROW23_ID,     CL_PT_BLUE, false,                  lsub(TX_MPENDOFSHIFT4), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField   (MP_ROW23_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_TIME, 5, 0, WIDGET_TEXT_ALIGN_RIGHT, lsub(TX_MPENDOFSHIFT4), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField    (MP_ROW23_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                            "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();  

          endlayout(); // End of Grid Layout
 
//        createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline          
       
        endlayout(); // End of HBOX #6  // End of left display in-/outputs without infoline HBOX
       
       createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, false);
   DrawNavButtons (SCREEN_MP2, true, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateMPPage3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/03
--  
--  Purpose           : Creation of Machine Parameters page #3   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateMPPage3(void) 
{
  begindraw();
  createpage(PAGE_MP_3);  
  page_background (PAGE_MP_3, BackgroundColor);//"white");
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // Split left screen in in-/outputs and infoline

      beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (MP_SEARCH_ID,WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_MACHINEPARAMETERS_PAGE)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Left display with weighing in-/outputs without infoline
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
           beginrow(); // First row with three columns 
              CreatePromptField     (MP_ROW25_ID,     CL_PT_BLUE, false,                  lsub(TX_MPT1), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField      (MP_ROW25_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 3, false, lsub(TX_MPT1), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField       (MP_ROW25_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                        lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();     
            
            beginrow(); // Second row with three columns  
              CreatePromptField     (MP_ROW26_ID,     CL_PT_BLUE, false,                  lsub(TX_MPT2), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField      (MP_ROW26_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 3, false, lsub(TX_MPT2), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField       (MP_ROW26_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                        lsub(TX_SEC_UNIT), WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();    
            
            beginrow(); // Third row with three columns 
              CreatePromptField     (MP_ROW27_ID,    CL_PT_BLUE, false,                        lsub(TX_FLEXCOUNTER) , FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField      (MP_ROW27_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, false, lsub(TX_FLEXCOUNTER), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField       (MP_ROW27_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                              "#", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();                              
          
            beginrow(); // Fourth row with three columns  
              beginrow(); // Third row with three columns 
              CreatePromptField   (MP_ROW28_ID,     CL_PT_BLUE, false,                    lsub(TX_MPINVERTFEEDANDDISCHOUTPUTS), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateComboBoxField (MP_ROW28_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_OFF), lsub(TX_ON), "", "", "", WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField     (MP_ROW28_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();            

            beginrow(); // Fifth row with three columns 
              CreatePromptField     (MP_ROW29_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputTextField (MP_ROW29_INPUT,                                      "", WD_MP_BOX, HT_MP_BOX, widget_locked);
              CreateUnitField       (MP_ROW29_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,       "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();

            beginrow(); // Sixth row with three columns
              CreatePromptField     (MP_ROW30_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputTextField (MP_ROW30_INPUT,                                      "", WD_MP_BOX, HT_MP_BOX, widget_locked);
              CreateUnitField       (MP_ROW30_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,       "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();
                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreatePromptField (MP_SPACE1,    CL_PT_BLUE, false,                       "", FT_STANDARD_SIZE, WD_MP_SPACE, HT_MP_DESCRIPTION, No_Margin, widget_locked);
        
        // Second Column of recipe page  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 

            beginrow(); // First row with three columns 
              CreatePromptField     (MP_ROW31_ID,    CL_PT_BLUE, false,                   lsub(TX_MPSP1) , FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField      (MP_ROW31_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, false, lsub(TX_MPSP1), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField       (MP_ROW31_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         WP.Unit, WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();     
            
            beginrow(); // Second row with three columns  
              CreatePromptField     (MP_ROW32_ID,    CL_PT_BLUE, false,                   lsub(TX_MPSP2) , FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField      (MP_ROW32_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, false, lsub(TX_MPSP2), WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField       (MP_ROW32_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         WP.Unit, WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();    
            
            beginrow(); // Third row with three columns 
              CreatePromptField   (MP_ROW33_ID,     CL_PT_BLUE, false,                    lsub(TX_MPFAILSAFE), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateComboBoxField (MP_ROW33_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_OFF), lsub(TX_ON), "", "", "", WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField     (MP_ROW33_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();                              
          
            beginrow(); // Fourth row with three columns  
              CreatePromptField   (MP_ROW34_ID,     CL_PT_BLUE, false,                    lsub(TX_STOPWITHGATESANDDISCHOPEN), FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, Left_Margin, widget_locked);
              CreateComboBoxField (MP_ROW34_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_OFF), lsub(TX_ON), "", "", "", WD_MP_BOX, HT_MP_BOX, widget_locked );
              CreateUnitField     (MP_ROW34_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();            

            beginrow(); // Fifth row with three columns 
              CreatePromptField     (MP_ROW35_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputTextField (MP_ROW35_INPUT,                                      "", WD_MP_BOX, HT_MP_BOX, widget_locked);
              CreateUnitField       (MP_ROW35_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,       "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow();  

            beginrow(); // Sixth row with three columns
              CreatePromptField     (MP_ROW36_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_DESCRIPTION, HT_MP_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputTextField (MP_ROW36_INPUT,                                      "", WD_MP_BOX, HT_MP_BOX, widget_locked);
              CreateUnitField       (MP_ROW36_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,       "", WD_UNIT, HT_MP_BOX, widget_locked );
            endrow(); 
                  
          endlayout(); // End of Grid Layout
 
//        createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline          
       
        endlayout(); // End of HBOX #6  // End of left display in-/outputs without infoline HBOX
       
       createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, false);
   DrawNavButtons (SCREEN_MP3, true, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateMPPage4
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/29
--  
--  Purpose           : Creation of Machine Parameters page #4   Save to default
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/

void CreateMPPage4(void) 
{
  begindraw();
  createpage(PAGE_MP_4);  
  page_background (PAGE_MP_4, BackgroundColor);//"white");
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // Split left screen in in-/outputs and infoline

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (MP_SEARCH_ID,WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_MACHINEPARAMETERS_PAGE)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Left display with weighing in-/outputs without infoline
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  First column on the left
         createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
          beginlayout(LAYOUT_TYPE_GRID, 0); 
            beginrow(); // First row with three columns 
              CreatePromptField     (MP_ROW37_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, Left_Margin, widget_locked);
            endrow();
            beginrow(); // Second row with three columns  
              CreatePromptField     (MP_ROW38_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, HT_MP_BOX, Left_Margin, widget_locked);
            endrow();
            beginrow(); // Third row with three columns  
              createwidget (MP_SAVE2DEFAULT, WIDGET_TYPE_TEXT_OUTPUT);
              widget_text_alignment (MP_SAVE2DEFAULT,  WIDGET_TEXT_ALIGN_CENTER);
            endrow(); 
            beginrow(); // Fourth row with three columns 
              CreatePromptField   (MP_ROW39_ID,     CL_PT_BLUE, false,                      lsub(TX_SaveMP2Def), FT_STANDARD_SIZE, WD_MP_PAGE4, HT_MP_BOX, Left_Margin, widget_locked);
              widget_text_alignment (MP_ROW39_ID,  WIDGET_TEXT_ALIGN_CENTER);
            endrow();           
            beginrow(); // Fifth row with three columns  
              CreatePromptField     (MP_ROW40_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, Left_Margin, widget_locked);
            endrow();
            beginrow(); // Sixth row with three columns  
              CreatePromptField     (MP_ROW41_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, Left_Margin, widget_locked);
            endrow();
            beginrow(); // Seventh row with three columns  
              CreatePromptField     (MP_ROW42_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, Left_Margin, widget_locked);
            endrow();
                               
          endlayout();  //End of Grid Layout
          
        // Second Column of recipe page  
         createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
          beginlayout(LAYOUT_TYPE_GRID, 0); // 
            beginrow(); // First row with three columns 
              CreatePromptField     (MP_ROW43_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, No_Margin, widget_locked);
            endrow();
            beginrow(); // Second row with three columns 
              CreatePromptField     (MP_ROW44_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, HT_MP_BOX, No_Margin, widget_locked);
            endrow();
            beginrow(); // Third row with three columns 
              createwidget (MP_RESTOREDEFAULT, WIDGET_TYPE_TEXT_OUTPUT);
              widget_text_alignment (MP_RESTOREDEFAULT,  WIDGET_TEXT_ALIGN_CENTER);
            endrow();
            beginrow(); // Fourth row with three columns 
              CreatePromptField   (MP_ROW45_ID,     CL_PT_BLUE, false,                      lsub(TX_RestDef2MP), FT_STANDARD_SIZE, WD_MP_PAGE4, HT_MP_BOX, No_Margin, widget_locked);
              widget_text_alignment (MP_ROW45_ID,  WIDGET_TEXT_ALIGN_CENTER);
            endrow();
            beginrow(); // Fifth row with three columns 
              CreatePromptField     (MP_ROW46_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, No_Margin, widget_locked);
            endrow();
            beginrow(); // Sixth row with three columns 
              CreatePromptField     (MP_ROW47_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, No_Margin, widget_locked);
            endrow();
            beginrow(); // Seventh row with three columns 
              CreatePromptField     (MP_ROW48_ID,     CL_PT_BLUE, false,                  "", FT_STANDARD_SIZE, WD_MP_PAGE4, 20, No_Margin, widget_locked);
            endrow();     
               
          endlayout(); // End of Grid Layout
          
       

        createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
        endlayout(); // End of HBOX #6  // End of left display in-/outputs without infoline HBOX
       
       createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   
   endlayout();  // End layout of HBOX #2

   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, false);
   DrawNavButtons (SCREEN_MP4, true, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : MPFillDb_Init
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Fill MP Database at startup to avoid empty Db
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void MPFillDb_Init (void)
{
int   i, err, MaxArrayMPTemp;

   MaxArrayMPTemp= records(MPdb);

// Fill MC missing Tables
   for (i=(MaxArrayMPTemp+1); i<=MAX_MP; i++)
   {
      DbDamaged.MPs = ON;
      MPdb.No = i;
      if (i==1) MPdb.Name = "Active";  
      else MPdb.Name = "Default";
      err=insert(MPdb); 
   }   

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshMPGrayOut
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/24
--  
--  Purpose           : Gray out management while refreshing page
--                      
--  Value Parameters  :
--  Variable Params   : Scrn_No = Active screen, MaxRows = # of rows to update,
--                    : pointer =  starting IO # (0 to 72)
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshMPGrayOut(int Scrn_No, int page_no, int MaxRows, int pointer)
{
int i, j ;
TEST_ID[0]     = string(MP_ROW1_ID);
TEST_VALUE[0]  = string(MP_ROW1_INPUT);
TEST_SELECT[0] = string(MP_ROW1_SELECT);
TEST_UNITS[0]   = string(MP_ROW1_UNIT);
j=pointer;

//MP_Grayout[5]=0;
//MP_Grayout[14]=0;
//MP_Grayout[15]=0;

 for (i=pointer; i<page_no; i++)
     {
 
      TEST_POINTER[i] = pointer+i;
      TEST_ID[i]      = TEST_ID[0]+i;
      TEST_VALUE[i]   = TEST_VALUE[0]+i;
      TEST_SELECT[i]  = TEST_SELECT[0]+i;
      TEST_UNITS[i]    = TEST_UNITS[0]+i;

     }

 for (i=pointer; i<pointer+MaxRows; i++)
     {
      widget_enable     (TEST_ID[j],     !MP_Grayout[i+1]);
      widget_enable     (TEST_VALUE[j],  !MP_Grayout[i+1]);
      widget_enable     (TEST_SELECT[j], !MP_Grayout[i+1]);
//      widget_enable     (TEST_UNITS[j],   !MP_Grayout[i+1]);
                 
      j = j+1;
     }

} 



/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshMPScreen
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/24
--  
--  Purpose           : Refresh Recipe screen at first screen access or after 
--                    : keyboard input entry to update Lim function
--  Value Parameters  :
--  Variable Params   : Scrn_No = Active screen number
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshMPScreen(int Scrn_No)
{
 begindraw(); 
 


  switch ( Scrn_No )
  {
    case SCREEN_MP1 :  
                    widget_text (MP_SEARCH_ID, concat(space(1), lsub(TX_MACHINEPARAMETERS_PAGE),space(5), "1" , space(1), TX_FSLASH, space(1), "3") );
                  // First Column                                
                    widget_text (MP_ROW1_INPUT, MP.SampleFreq);
                    widget_text (MP_ROW2_INPUT, MP.SampleSize);
                    widget_text (MP_ROW3_INPUT, MP.ZeroFreq);
                    widget_text (MP_ROW4_INPUT,  MP.ZeroLimit);
                    widget_set_index (MP_ROW5_SELECT, MP.AutoZeroOff,0);
                    widget_text      (MP_ROW6_INPUT, MP.ScreenSaverTime);
  
                  // Second Column                               
                    widget_text (MP_ROW7_INPUT, MP.DischDoorMaxTime);
                    widget_text (MP_ROW8_INPUT, MP.SlowCycleTime);
                    widget_text (MP_ROW9_INPUT, MP.FeedGateMaxTime);
                    widget_text (MP_ROW10_INPUT, MP.OutOfTolTime);
                    widget_text (MP_ROW11_INPUT, MP.FeedRateFilterRatio);
                    widget_text (MP_ROW12_INPUT, MP.StabTimeLimit); 
                    
                    RefreshMPGrayOut(SCREEN_MP1, MX_PAGE1, 12, 0);                                                                                                                                    
                  break;
                         
                         
    case SCREEN_MP2 :    
                    widget_text (MP_SEARCH_ID, concat(space(1), lsub(TX_MACHINEPARAMETERS_PAGE),space(5), "2" , space(1), TX_FSLASH, space(1), "3") );
                  // First Column
                    widget_set_index (MP_ROW13_SELECT, MP.CorrOnAverage,0);
                    widget_text      (MP_ROW14_INPUT,  MP.CutoffCorrLimit);
                    widget_text      (MP_ROW15_INPUT,  MP.DFWeightCorr);
                    widget_text      (MP_ROW16_INPUT,  MP.CutoffCorr);
                    widget_text      (MP_ROW17_INPUT,  MP.MaxFeedRate);   
                    widget_text      (MP_ROW18_INPUT,  MP.LowFeedingTime);

                   // Second Column                               
                    widget_text      (MP_ROW19_INPUT,  MP.EndOfShift1);
                    widget_text      (MP_ROW20_INPUT,  MP.EndOfShift2);
                    widget_text      (MP_ROW21_INPUT,  MP.EndOfShift3);
                    widget_text      (MP_ROW22_INPUT,  MP.StdFilterSize); 
                    widget_text      (MP_ROW23_INPUT,  MP.EndOfShift4);  
                    widget_text      (MP_ROW24_INPUT,  MP.MaintCycle);               
                    
                    
                    RefreshMPGrayOut(SCREEN_MP2, MX_PAGE2, 12, 12);                    
                     
                   break;

    case SCREEN_MP3 :    
                    widget_text (MP_SEARCH_ID, concat(space(1), lsub(TX_MACHINEPARAMETERS_PAGE),space(5),"3" , space(1), TX_FSLASH, space(1), "3") );
                  // First Column                              
                    widget_text      (MP_ROW25_INPUT,  MP.FlexT1);
                    widget_text      (MP_ROW26_INPUT,  MP.FlexT2);
                    widget_text      (MP_ROW27_INPUT,  MP.FlexCounter);                    

                   // Second Column                                                     
                    widget_text      (MP_ROW31_INPUT,  MP.FlexSP1);
                    widget_text      (MP_ROW31_UNIT,   WP.Unit);                    
                    widget_text      (MP_ROW32_INPUT,  MP.FlexSP2);
                    widget_text      (MP_ROW32_UNIT,   WP.Unit);
                    widget_set_index (MP_ROW28_SELECT, MP.InvertFeedAndDischOutputs,0);
                    widget_set_index (MP_ROW33_SELECT, MP.FailSafe,0); 
                    widget_set_index (MP_ROW34_SELECT, MP.StopWithGatesAndDischDoorOpen,0);
                    RefreshMPGrayOut(SCREEN_MP3, MX_PAGE3, 12, 24);                    
                     
                   break;

    case SCREEN_MP4 :
    
                    widget_text (MP_SEARCH_ID, concat (space(1), lsub(TX_MACHINEPARAMETERS_PAGE), space(1)));
                   // First Column                                
                    widget_image (MP_SAVE2DEFAULT,BTN_SAVE2DFLT);
                    
                  // Second Column
                    widget_image (MP_RESTOREDEFAULT,BTN_RESTOREDFLT);
                    
                   break;
                                      
  }

 enddraw();           
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshMPInputEntry
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/22
--  
--  Purpose           : Refresh Input box entry to recipe buffer
--                      
--  Value Parameters  :
--  Variable Params   : value = readevent entered value, Argument = Argument value from readevent 
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshMPInputEntry(int Scrn_No, int value, string Argument) 
{
 begindraw();
 
  switch (Scrn_No)
  {  
    case SCREEN_MP1 :  
                   switch (value)
                   {      
                   // Page 1 of 2
                      case MP_ROW1_INPUT :  MP.SampleFreq = int (Lim(1,9999999,Argument));
                                            MP.SampleSize = int (Lim(1,MP.SampleFreq,MP.SampleSize));
                                            break;
    
                      case MP_ROW2_INPUT :  MP.SampleSize = int (Lim(1,MP.SampleFreq,Argument)); 
                                            break;
                                              
                      case MP_ROW3_INPUT : MP.ZeroFreq = decimal (Lim(1,(9999999/MP.SampleFreq),Argument));
                                            break;
                                                
                      case MP_ROW4_INPUT : MP.ZeroLimit = decimal (Lim(0.1,100,Argument));
                                            break; 
                                            
                      case MP_ROW6_INPUT : MP.ScreenSaverTime = decimal (Lim(0,99,Argument));
                                            break;                                            
                                                    
                      case MP_ROW7_INPUT :  MP.DischDoorMaxTime = decimal (Lim(0,99,Argument));
                                            break;
                                                    
                      case MP_ROW8_INPUT :  MP.SlowCycleTime = decimal (Lim(0,1800,Argument));
                                            break;    
                      
                      case MP_ROW9_INPUT :  MP.FeedGateMaxTime = decimal (Lim(0,5,Argument));
                                            break;
                                     
                      case MP_ROW10_INPUT : MP.OutOfTolTime = decimal (Lim(0,1200,Argument));
                                            break; 
                                     
                      case MP_ROW11_INPUT : MP.FeedRateFilterRatio = decimal (Lim(0.001,1,Argument));
                                            break;
                      
                      case MP_ROW12_INPUT :  MP.StabTimeLimit = decimal (Lim(0.01,20,Argument));
                                            break;               
                        
                   }
                 break;  

    case SCREEN_MP2 :  
                   switch (value)
                   {
                   // Page 2 of 2                          
                             
                      case MP_ROW14_INPUT : MP.CutoffCorrLimit = decimal (Lim(0,100,Argument));
                                            break;
                                            
                      case MP_ROW15_INPUT :  MP.DFWeightCorr   = decimal (Lim(0,50,Argument)); 
                                            break; 
                                                                   
                      case MP_ROW16_INPUT :  MP.CutoffCorr = decimal (Lim(0,100,Argument));    // np+ ADJUSTED - 21.12.2015  
                                            break;
                      
                      case MP_ROW17_INPUT :  MP.MaxFeedRate = decimal (Lim(0,80000,Argument));   
                                            break;
                      
                      case MP_ROW18_INPUT :  MP.LowFeedingTime = decimal (Lim(0,60,Argument));    
                                            break;
                      
                      
                                                    
                      case MP_ROW19_INPUT : MP.EndOfShift1 = FormatTime(Argument); 
                                            break;                      
                       
                      case MP_ROW20_INPUT : 
                                            MP.EndOfShift2 = FormatTime(Argument); 
                                            break;
                                            
                      case MP_ROW21_INPUT : MP.EndOfShift3 = FormatTime(Argument); 
                                            break;
                                            
                      case MP_ROW22_INPUT : MP.StdFilterSize = decimal (Lim((SMFilterSize-5),(SMFilterSize+5),Argument));
                                            break;
                                            
                      case MP_ROW23_INPUT : MP.EndOfShift4 = FormatTime(Argument); 
                                            break;
                      
                      case MP_ROW24_INPUT : MP.MaintCycle = decimal (Lim(0,200000,Argument));    
                                            break;                     
                                            
 
                                                            
                      
                                                                                
                   }                                                                                                                                     
                 break;

    case SCREEN_MP3 :  
                   switch (value)
                   {
                   // Page 3 of 3                          
                                            
                      case MP_ROW25_INPUT : MP.FlexT1 = decimal (Lim(0, 60, Argument));
                                            FlexIO_SetTPresetsFlag = Execute;
                                            break;
                                            
                      case MP_ROW26_INPUT : MP.FlexT2 = decimal (Lim(0, 60, Argument));
                                            FlexIO_SetTPresetsFlag = Execute;
                                            break;
                                            
                      case MP_ROW27_INPUT : MP.FlexCounter= decimal (Lim(0,999999,Argument));
                                            FlexIO_SetTPresetsFlag = Execute;
                                            break;
  
                                            
                      case MP_ROW31_INPUT : MP.FlexSP1 = decimal (Lim(0, 100,Argument));
                                            FlexIO_SetTPresetsFlag = Execute;
                                            break;
                                            
                      case MP_ROW32_INPUT : MP.FlexSP2 = decimal (Lim(0, 100,Argument));
                                            FlexIO_SetTPresetsFlag = Execute;
                                            break;      
                      
                   }                                                                                                                                     
                 break;

  }
 enddraw();
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshMPComboBoxEntry
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/24
--  
--  Purpose           : Refresh ComboBox box entry to recipe buffer
--                      
--  Value Parameters  :
--  Variable Params   : value = readevent entered value, Argument = Argument value from readevent 
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshMPComboBoxEntry(int Scrn_No, int value, string Argument)
{
 begindraw();

  switch (Scrn_No)
  {  
    case SCREEN_MP1 :  
                   switch (value)
                   {      
                      case MP_ROW5_SELECT :  MP.AutoZeroOff = int (Argument);
                                              break;                      
                   }      
                 break;
                   
    case SCREEN_MP2 :  
                   switch (value)
                   {      
                      case MP_ROW13_SELECT :  MP.CorrOnAverage = int (Argument);
                                              break;
                   }
                 break;
                 
//    case SCREEN_MP3 :  
//                   switch (value)
//                   {      
//                      case MP_ROW13_SELECT :  MP.CorrOnAverage = int (Argument);
//                                              break;
//                   }
//                 break;

   case SCREEN_MP3 :  
                   switch (value)
                   {      
                      case MP_ROW28_SELECT :  MP.InvertFeedAndDischOutputs = int (Argument);
                                              break;    
                      case MP_ROW33_SELECT :  MP.FailSafe = int (Argument);
                                              break;
                      case MP_ROW34_SELECT :  MP.StopWithGatesAndDischDoorOpen = int (Argument);
                                              break;                        
                   }
                 break;
                 
  }
 enddraw();
} 

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateMachineParamPages
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create Machine Parameters Pages Manager 
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateMPPages(void) 
{
    CreateMPPage1();
    CreateMPPage2();
    CreateMPPage3();
    CreateMPPage4();
}

/* *********************************************** */
/*   Create Input field                            */                                                            
/* *********************************************** */

void CreateInputFieldTD (int id, int font_size, int font_face, int format, int len, int decs, int height, string text )
{
  createwidget(id, WIDGET_TYPE_TEXT_INPUT);
    widget_style           (id, WPMANAGEBOX_STYLE);
    widget_size_policy     (id,  SIZE_POLICY_MINIMUM, SIZE_POLICY_FIXED);
    widget_fontsize        (id,  font_size); 
    widget_fontface        (id,  font_face);
    widget_foreground      (id,   CL_PT_BLUE);
    widget_format          (id,  format, len, decs);
    widget_label           (id,  text);
    widget_text_alignment  (id,   WIDGET_TEXT_ALIGN_CENTER );
    widget_text            (id,   "" );
    widget_dimensions      (id,  WD_TD_BOX, height);
    widget_maximum_size    (id,  WD_TD_BOX, height);
//    widget_content_margins (id,  0,0,0,0);   
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateTimeDateManagePage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/26
--  
--  Purpose           : Create Time and date management page
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateTimeDateManagePage(void) 
{
  begindraw();
  createpage(PAGE_TDMANAGE);  
  page_background (PAGE_TDMANAGE, BackgroundColor);
   
beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1  VBOX = Alignement des Rangées

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (TDMANAGE_ID,WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_TDMANAGE_MENU)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
        
        endlayout(); // Header 

       

       // Current date & time       User Level display
         beginlayout(LAYOUT_TYPE_HBOX, 0);         
            CreateHeader (AUTO_SPACE_1, WD_TIMEUSERLEVEL, HT_TIMEUSERLEVEL, "", align_hcenter, "", 25, widget_unlocked );
            CreateHeader (TDMANAGE_TIME_DISPLAY, WD_TIMEHEADER, HT_TIMEHEADER, "", align_hcenter, concat (space(1),lsub(TX_TDMANAGE_DATE),space(1), date, space(2),lsub(TX_TDMANAGE_TIME), space(1), time , space(1), widget_unlocked), 25, widget_unlocked );
            CreateHeader (ACCESS_LEVEL, WD_TIMEUSERLEVEL, HT_TIMEUSERLEVEL, "", align_vcenter, concat (space(1), lsub(TX_ACCESS_USER),":", space(1) , CurrentUser), 20, widget_unlocked);
         endlayout(); // 

CreateSpacingField (TDMANAGE_SPACE_5, CL_PT_BLUE, FT_STANDARD_SIZE, space(100));
beginlayout(LAYOUT_TYPE_HBOX, 0); 
        

        //  Source WP and Dest. WP ID & boxes
        beginlayout(LAYOUT_TYPE_HBOX, 0); //HBOX #2

          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);          

          // First Column "DAY"
          beginlayout(LAYOUT_TYPE_GRID, 0); // GRID #1
            
              beginrow(); // First row "Blank" with 2 columns             
                CreatePromptField   (TDMANAGE_DAY_ID,     CL_PT_BLUE, false, lsub(TX_TDMANAGE_DAY_ID), FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked); 
                widget_text_alignment (TDMANAGE_DAY_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
                widget_content_margins (TDMANAGE_DAY_ID, 0,0,WD_MARGIN,0);
                CreateInputFieldTD  (TDMANAGE_DAY_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 2, 0, HT_TDBOX_SIZE, lsub(TX_TDMANAGE_DAY_ID) );   
              endrow();
              
              beginrow(); // Second row with two columns
                CreatePromptField   (TDMANAGE_HOUR_ID,     CL_PT_BLUE, false, lsub(TX_TDMANAGE_HOUR_ID), FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked);  
                widget_text_alignment (TDMANAGE_HOUR_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
                widget_content_margins (TDMANAGE_HOUR_ID, 0,0,WD_MARGIN,0);
                CreateInputFieldTD  (TDMANAGE_HOUR_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 2, 0, HT_TDBOX_SIZE, lsub(TX_TDMANAGE_HOUR_ID) );                           
              endrow();
         
              beginrow(); // Third row with two columns         
                CreatePromptField     (TDMANAGE_ROW3_ID,     CL_PT_BLUE, false, "", FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked);
                CreateOutputTextField (TDMANAGE_ROW3_INPUT,"", WD_TDBOX_SIZE, HT_TDBOX_SIZE, widget_locked);
              endrow();

          endlayout();  // End GRID #1

        // Spacing between columns
          CreatePromptField (TD_SPACE1,    CL_PT_BLUE, false,                       "", FT_STANDARD_SIZE, WD_TD_SPACE, HT_MP_DESCRIPTION, No_Margin, widget_locked);          
          
          // Second Column "MONTH"
          beginlayout(LAYOUT_TYPE_GRID, 0);
            beginrow(); // First row with three columns         
              CreatePromptField   (TDMANAGE_MONTH_ID,     CL_PT_BLUE, false, lsub(TX_TDMANAGE_MONTH_ID), FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked);
              widget_text_alignment (TDMANAGE_MONTH_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
              widget_content_margins (TDMANAGE_MONTH_ID, 0,0,WD_MARGIN,0);
              CreateInputFieldTD  (TDMANAGE_MONTH_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 2, 0, HT_TDBOX_SIZE, lsub(TX_TDMANAGE_MONTH_ID) );                   
            endrow();


            beginrow(); // Second row with three columns               
              CreatePromptField   (TDMANAGE_MINUTE_ID,     CL_PT_BLUE, false, lsub(TX_TDMANAGE_MINUTE_ID), FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked);              
              widget_text_alignment (TDMANAGE_MINUTE_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
              widget_content_margins (TDMANAGE_MINUTE_ID, 0,0,WD_MARGIN,0);
              CreateInputFieldTD  (TDMANAGE_MINUTE_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 2, 0, HT_TDBOX_SIZE, lsub(TX_TDMANAGE_MINUTE_ID) );              
            endrow();


            beginrow(); // Second row with three columns 
              CreatePromptField (TDMANAGE_ROW13_ID,     CL_PT_BLUE, false, "", FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked);
              CreateOutputTextField (TDMANAGE_ROW13_INPUT,"", WD_TDBOX_SIZE, HT_TDBOX_SIZE, widget_locked);  
            endrow();
//
          endlayout();

        // Spacing between columns
          CreatePromptField (TD_SPACE2,    CL_PT_BLUE, false,                       "", FT_STANDARD_SIZE, WD_TD_SPACE, HT_MP_DESCRIPTION, No_Margin, widget_locked);   
          
          //  Third column "YEAR"
          beginlayout(LAYOUT_TYPE_GRID, 0);
            beginrow(); // First row with three columns       
              CreatePromptField   (TDMANAGE_YEAR_ID,     CL_PT_BLUE, false, lsub(TX_TDMANAGE_YEAR_ID), FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked); 
              widget_text_alignment (TDMANAGE_YEAR_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
              widget_content_margins (TDMANAGE_YEAR_ID, 0,0,WD_MARGIN,0);
              CreateInputFieldTD  (TDMANAGE_YEAR_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 4, 0, HT_TDBOX_SIZE, lsub(TX_TDMANAGE_YEAR_ID) );  
            endrow();


            beginrow(); // Second row with three columns 
              CreatePromptField     (TDMANAGE_ROW22_ID,     CL_PT_BLUE, false, "", FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_locked);
              CreateOutputTextField (TDMANAGE_ROW22_INPUT,"", WD_TDBOX_SIZE, HT_TDBOX_SIZE, widget_locked); 
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField     (TDMANAGE_ROW23_ID,     CL_PT_BLUE, false, "", FT_AUTOPAGE2_SIZE, WD_TDHEADER_SIZE, HT_TDBOX_SIZE, No_Margin, widget_unlocked);
              CreateOutputTextField (TDMANAGE_ROW23_INPUT,"", WD_TDBOX_SIZE, HT_TDBOX_SIZE, widget_unlocked);  
            endrow();


          endlayout();
          
          
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);      

        endlayout(); // End HBOX #2

endlayout(); 

   createwidget (0, WIDGET_TYPE_STRETCH);  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, false);
   DrawNavButtons (SCREEN_TDMANAGE, true, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_SAVE, BTN_NIL_BLUE); 
    
endlayout();  // End of VBOX #1
enddraw();

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshTDManageScreen
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/02
--  
--  Purpose           : Refresh Time and Date Screen
--                      
--  Value Parameters  :
--  Variable Params   : bypass =  Used to bypass RefreshTDManageCnt Logic
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/

void RefreshTDManageScreen(bool bypass)
{
int RefreshTDManageCnt,commapos,dateformatlen,dateformat2len,yearpos;

if (RefreshTDManageCnt<= 0 || RefreshTDManageCnt > 10 || bypass)
{

RefreshTDManageCnt = 0;
dateformat = readparameter("General","Dateformat");
dateformatlen = length(dateformat);
commapos = pos(dateformat,',');
dateformat2 = sub(dateformat,commapos+1,dateformatlen-commapos);
dateformat2len = length(dateformat2);
if(dateformat2len == 10)
 {
  TD_YearDigits = 4;
  yearpos = pos(dateformat2,'Y');
  yearprefix = sub(date,yearpos,2);
 }
 
else 
 {
  TD_YearDigits = 2; 
  yearprefix = "";
 }   

stddate = getstddate();
stdtime = getstdtime();

 begindraw(); 
 
  widget_text   (TDMANAGE_ID, concat(space(1), lsub(TX_TDMANAGE_MENU)));
  widget_text   (TDMANAGE_TIME_DISPLAY, concat (space(1),lsub(TX_TDMANAGE_DATE),space(1), date, space(2),lsub(TX_TDMANAGE_TIME), space(1), time , space(1)));
  RefreshCurrentUser();
 
  if (bypass)
  {
    TD_Day    = int (sub (stddate, 4, 2));
    widget_text (TDMANAGE_DAY_INPUT,sub(stddate, 4, 2));
    TD_Month  = int (sub (stddate, 2, 2));
    widget_text (TDMANAGE_MONTH_INPUT,sub (stddate, 2, 2));
    TD_Year   = int (sub (stddate, 0, 2)); 
    widget_text (TDMANAGE_YEAR_INPUT,concat (yearprefix,sub (stddate, 0, 2)));

    TD_Hour   = int (sub(stdtime, 0, 2));
    widget_text (TDMANAGE_HOUR_INPUT,sub(stdtime, 0, 2));
    TD_Minute = int (sub (stdtime, 2, 2));    
    widget_text (TDMANAGE_MINUTE_INPUT,sub (stdtime, 2, 2));
    
  }  
  
 enddraw();
}

RefreshTDManageCnt = RefreshTDManageCnt+1;         
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshTDManageInputEntry
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/02/11
--  
--  Purpose           : Refresh Input box entry to Time and Date
--                      
--  Value Parameters  :
--  Variable Params   : value = readevent entered value, Argument = Argument value from readevent 
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshTDManageInputEntry(int value, string Argument)
{
 begindraw();

   switch(value)
   { 
    case TDMANAGE_DAY_INPUT :  
                                TD_Day    = int (Lim(1,31,Argument)); 
                                widget_text (TDMANAGE_DAY_INPUT, trim(string(TD_Day)));

                              break;
    
    case TDMANAGE_MONTH_INPUT : 

                                TD_Month  = int (Lim(1,12,Argument));
                                widget_text (TDMANAGE_MONTH_INPUT, trim(string(TD_Month))); 
  
                              break;  
    
    case TDMANAGE_YEAR_INPUT :  
                                if(TD_YearDigits == 2) TD_Year   = int (Lim(00,99,Argument));
                                if(TD_YearDigits == 4) TD_Year   = int (Lim(1000,9999,Argument));
                                widget_text (TDMANAGE_YEAR_INPUT, trim(string(TD_Year)));  

                              break;
                                    
    case TDMANAGE_HOUR_INPUT :  

                                TD_Hour   = int (Lim(0,24,Argument));
                                widget_text (TDMANAGE_HOUR_INPUT, trim(string(TD_Hour)));

                              break; 
                                  
    case TDMANAGE_MINUTE_INPUT : 

                                TD_Minute = int (Lim(0,59,Argument));
                                widget_text (TDMANAGE_MINUTE_INPUT, trim(string(TD_Minute)));

                              break;
  
   }
 enddraw();  
}
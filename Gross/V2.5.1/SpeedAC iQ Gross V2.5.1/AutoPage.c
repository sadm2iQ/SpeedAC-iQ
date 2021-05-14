void CreateAutoRecipeButton (int id, int font_size, int font_face, string fg_color, string bg_color, string text)
{
  createwidget (id, WIDGET_TYPE_BUTTON);
//    widget_dimensions      (id,  435,45);   
    widget_size_policy     (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);     
    widget_fontsize        (id,  font_size); 
    widget_fontface        (id,  font_face);
    widget_foreground      (id,  fg_color);
    widget_background      (id,  bg_color);
    widget_text_alignment  (id,  WIDGET_TEXT_ALIGN_CENTER );
    widget_text            (id,  text );
    widget_style           (id,  AUTOWPBOX_STYLE);
    widget_content_margins (id,  0,0,0,10); 
    widget_maximum_size    (id,  450, 45);  
    widget_attribute       (id,  WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_BLACK_WHITE); 
}

/* *********************************************************************** */
/*                                                                         */
/*   Create AUTO page                                                      */
/*                                                                         */
/* *********************************************************************** */
void CreateAutoScreen(void) 
{
begindraw();
  createpage(PAGE_AUTO);  
  page_background (PAGE_AUTO, BackgroundColor);                                       
                                                                                   
// Border control   
  beginlayout(LAYOUT_TYPE_VBOX, 0); //VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #2 

     beginlayout(LAYOUT_TYPE_VBOX, 0); //VBOX #3
          
        beginlayout(LAYOUT_TYPE_HBOX, 0); //search recipe button
          CreatePTLogoHeader();
          CreateAutoRecipeButton (ACTIVE_RECIPE_ID, FT_MEDIUM_SIZE, FT_RTC_BOLD, CL_PT_BLUE, CL_PT_WHITE, concat (space(1), lsub(WP.Name), space(1)));
         
          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
           //Fault and Mode display
           CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,2,0,0"); //"left,top,right,bottom"
        endlayout(); // End of search recipe button
    
 
       beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #6

//beginlayout(LAYOUT_TYPE_GRID, 0);        
//setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,0,0"); //"left,top,right,bottom"

       // First Column
       
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // Grid #1
//setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,0,0"); //"left,top,right,bottom" 
            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW1_ID,     CL_PT_BLUE, OFF, lsub(TX_TARGET_WEIGHT_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW1_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW1_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked);              
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField (AUTO_ROW2_ID,     CL_PT_BLUE, OFF, lsub(TX_AVERAGE_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW2_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW2_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked); 
  
            endrow();

            beginrow(); // Third row with three columns 
              CreatePromptField (AUTO_ROW3_ID,     CL_PT_BLUE, OFF, lsub(TX_STD_DEV_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW3_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW3_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked);  
            endrow();

            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW4_ID,     CL_PT_BLUE, OFF, lsub(TX_LAST_CHECKED_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW4_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked); 
              CreateUnitField   (AUTO_ROW4_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked); 
            endrow();

          endlayout();  // End Grid layout #1


        // Spacing between columns
          CreatePromptField (AUTO_SPACE_3,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_AUTO_SPACE, HT_AUTO_DESCRIPTION, No_Margin, widget_locked);

       // Second Column

          //  First column on the Right
          beginlayout(LAYOUT_TYPE_GRID, 0,3); //Grid #2
          
            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW11_ID,     CL_PT_BLUE, OFF, lsub(TX_UNITS_ACCEPTED_ID), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION-20), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW11_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, (WD_AUTOPAGE_BOX+45), HT_AUTOPAGE_BOX, widget_locked); 
              CreateUnitField   (AUTO_ROW11_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , (WD_AUTO_UNIT-18), HT_AUTOPAGE_BOX, widget_locked);           
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField (AUTO_ROW12_ID,     CL_PT_BLUE, OFF, lsub(TX_UNITS_DONE_ID), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION-20), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW12_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, (WD_AUTOPAGE_BOX+45), HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW12_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , (WD_AUTO_UNIT-18), HT_AUTOPAGE_BOX, widget_locked);  
            endrow();

            beginrow(); // Third row with three columns 
              CreatePromptField (AUTO_ROW13_ID,     CL_PT_BLUE, OFF, lsub(TX_PRESETS_PER_UNIT_ID), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION-20), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW13_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, (WD_AUTOPAGE_BOX+45), HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW13_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , (WD_AUTO_UNIT-18), HT_AUTOPAGE_BOX, widget_locked);
            endrow();
            
            
            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW14_ID,     CL_PT_BLUE, OFF, "", FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION-20), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW14_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, (WD_AUTOPAGE_BOX+45), HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW14_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , (WD_AUTO_UNIT-18), HT_AUTOPAGE_BOX, widget_locked); 
            endrow();


          endlayout();  //Grid #2 
  
  
       // Third Column          

          //  First column on the Right
          beginlayout(LAYOUT_TYPE_GRID, 0,3); //Grid #3
//setlayoutoption (LAYOUT_OPTION_SPACING, "0"); //"left,top,right,bottom" 
//setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,0,0"); //"left,top,right,bottom" 

            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW21_ID,     CL_PT_BLUE, OFF, lsub(TX_UNITSPERMIN_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW21_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW21_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);             
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField (AUTO_ROW22_ID,     CL_PT_BLUE, OFF, lsub(TX_BULK_TIME_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW22_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW22_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          lsub(TX_SEC_UNIT) , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);
            endrow();

            beginrow(); // Third row with three columns 
              CreatePromptField (AUTO_ROW23_ID,     CL_PT_BLUE, OFF, lsub(TX_DRIBBLE_TIME_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW23_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW23_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          lsub(TX_SEC_UNIT) , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked); 
            endrow();

            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW24_ID,     CL_PT_BLUE, OFF, lsub(TX_CYCLE_TIME_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW24_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW24_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          lsub(TX_SEC_UNIT) , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);
            endrow();
           setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,2,0"); //"left,top,right,bottom"
          endlayout();  //Grid #3                 

//setlayoutoption (LAYOUT_OPTION_COLUMN_MINIMUM_WIDTH, "0,0,0");
//endlayout();  // End Grid layout of all 3 columns

//setlayoutoption (LAYOUT_OPTION_COLUMN_MINIMUM_WIDTH, "266,266,266"); //"left,top,right,bottom" 
        endlayout(); // End of HBOX #6
        
      endlayout();  // End layout of VBOX #3


    endlayout();  // End layout of HBOX #2 


endlayout();  // End layout of Test Layout #1 

    createwidget (0, WIDGET_TYPE_STRETCH);
 
    beginlayout(LAYOUT_TYPE_GRID, 0,2);
     beginrow();
    /*Display message line*/
      createwidget (MESSAGE_DISPLAY, WIDGET_TYPE_TEXT_OUTPUT);
        widget_foreground      (MESSAGE_DISPLAY,   CL_PT_BLUE);
        widget_text_alignment  (MESSAGE_DISPLAY,   WIDGET_TEXT_ALIGN_HCENTER);
        widget_fontsize        (MESSAGE_DISPLAY,   PT_INFO_LINE);
        widget_size_policy     (MESSAGE_DISPLAY,   SIZE_POLICY_FIXED, SIZE_POLICY_MINIMUM);
        widget_maximum_size    (MESSAGE_DISPLAY,  850, 0);
        widget_text            (MESSAGE_DISPLAY,   "");
        widget_text_alignment  (MESSAGE_DISPLAY,   WIDGET_TEXT_ALIGN_LEFT);
        widget_content_margins (MESSAGE_DISPLAY, Left_Margin,0,0,0);
             
    /*Display High resolution Weight*/   
      createwidget (HIRESWEIGHT, WIDGET_TYPE_TEXT_OUTPUT);
        widget_foreground      (HIRESWEIGHT,   CL_PT_BLUE);
        widget_text_alignment  (HIRESWEIGHT,   WIDGET_TEXT_ALIGN_HCENTER);
        widget_fontsize        (HIRESWEIGHT,   PT_INFO_LINE);
        widget_size_policy     (HIRESWEIGHT,   SIZE_POLICY_FIXED, SIZE_POLICY_MINIMUM);
        widget_maximum_size    (HIRESWEIGHT,  150, 0);
        widget_text            (HIRESWEIGHT,   concat(NetWeightHiRes[Scale1],space(1),WP.Unit,space(1)));
        widget_text_alignment  (HIRESWEIGHT,   WIDGET_TEXT_ALIGN_RIGHT);
        widget_content_margins (HIRESWEIGHT, 0,2,0,0);    

     endrow();   
    endlayout();
     
      CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
      DrawNavButtons (SCREEN_AUTOMATIC, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_DISCH_OFF, BTN_OFF, HOPPER_FILL, BTN_START, BTN_STOP);   
    
  endlayout(); // End layout of VBOX #1 
  
enddraw();

}


/* *********************************************************************** */
/*                                                                         */
/*       Refresh Auto screen display                                       */
/*                                                                         */
/* *********************************************************************** */

void RefreshAutoScreen(bool RefreshAll)
{
   bool FirstPassDone;
   decimal TargetWeightMem%6.2[2],ProdAvgWeightMem%6.2[2],ProdStdDevMem%6.4[2],ProdLastCheckedMem%7.2[2];
   decimal ProdAcceptUnitCntMem%6.0[2],ProdTotalUnitsCntMem%10.0[2],ProdCycleUnitsPerMinMem%6.2[2];
   decimal ProdBulkDurationMem%6.2[2],ProdDribbleDurationMem%6.2[2],ProdCycleDurationMem%6.2[2];
   int BatchCountMem, BatchPresetMem%6.0;
   
   if(RefreshAll)
   {
      FirstPassDone = OFF;
   }
   
   begindraw();
      if(SeqModeManager == stp_OFF_MODE || !FirstPassDone)
      {
         RefreshRecipeInAutoScreen();
         widget_text (AUTO_ROW1_UNIT, WP.Unit);
         widget_text (AUTO_ROW2_UNIT, WP.Unit);
         widget_text (AUTO_ROW3_UNIT, WP.Unit);
         widget_text (AUTO_ROW4_UNIT, WP.Unit);
      }

      // First Column                                         
      // First Row Info 
      if(TargetWeight[Scale1] != TargetWeightMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW1_OUTPUT, TargetWeight[Scale1]);
         TargetWeightMem[Scale1] = TargetWeight[Scale1];
      }
      
      // 2nd Row Info 
      if(ProdAvgWeight[Scale1] != ProdAvgWeightMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW2_OUTPUT, ProdAvgWeight[Scale1]);
         ProdAvgWeightMem[Scale1] = ProdAvgWeight[Scale1];
      } 
                             
      // Third Row Info 
      if(ProdStdDev[Scale1] != ProdStdDevMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW3_OUTPUT, ProdStdDev[Scale1]);
         ProdStdDevMem[Scale1] = ProdStdDev[Scale1];
      } 
                            
      // Fourth Row Info
      if(ProdLastChecked[Scale1] != ProdLastCheckedMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW4_OUTPUT, ProdLastChecked[Scale1]);
         ProdLastCheckedMem[Scale1] = ProdLastChecked[Scale1];
      }
      
      // Second Column                                                     
      // First Row Info 
      if(ProdAcceptUnitCnt[Scale1] != ProdAcceptUnitCntMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW11_OUTPUT, ProdAcceptUnitCnt[Scale1]);                             
         ProdAcceptUnitCntMem[Scale1] = ProdAcceptUnitCnt[Scale1];
      }
      
      // Third Row Info 
      if(ProdTotalUnitsCnt[Scale1] != ProdTotalUnitsCntMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW12_OUTPUT,  ProdTotalUnitsCnt[Scale1]);
         ProdTotalUnitsCntMem[Scale1] = ProdTotalUnitsCnt[Scale1];
      }
      
      // Fourth Row Info 
      if(Batch.Count != BatchCountMem || Batch.Preset != BatchPresetMem || !FirstPassDone)
      {
         widget_text (AUTO_ROW13_OUTPUT, concat(Batch.Count,"/",Batch.Preset));
         BatchCountMem = Batch.Count;
         BatchPresetMem = Batch.Preset;
      }
      
      // Third Column                                      
      // First Row Info 
      if(ProdCycleUnitsPerMin[Scale1] != ProdCycleUnitsPerMinMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW21_OUTPUT, ProdCycleUnitsPerMin[Scale1]);
         ProdCycleUnitsPerMinMem[Scale1] = ProdCycleUnitsPerMin[Scale1];
      }
      
      // 2nd Row Info 
      if(ProdBulkDuration[Scale1] != ProdBulkDurationMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW22_OUTPUT, ProdBulkDuration[Scale1]);
         ProdBulkDurationMem[Scale1] = ProdBulkDuration[Scale1];
      }
                             
      // Third Row Info 
      if(ProdDribbleDuration[Scale1] != ProdDribbleDurationMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW23_OUTPUT, ProdDribbleDuration[Scale1]);
         ProdDribbleDurationMem[Scale1] = ProdDribbleDuration[Scale1];
      }
                           
      // Fourth Row Info 
      if(ProdCycleDuration[Scale1] != ProdCycleDurationMem[Scale1] || !FirstPassDone)
      {
         widget_text (AUTO_ROW24_OUTPUT, ProdCycleDuration[Scale1]);
         ProdCycleDurationMem[Scale1] = ProdCycleDuration[Scale1];
      }
      
      if(MessageText != MessageTextMem || !FirstPassDone)
      {
         widget_background     (MESSAGE_DISPLAY, MessageColor);
         widget_text           (MESSAGE_DISPLAY, MessageText);  
         MessageTextMem = MessageText;  
      }
   enddraw();
   
   if(!FirstPassDone)
   {
      FirstPassDone = ON;
   } 
}

/* *********************************************** */
/*          CreateProdDataWidget                   */                                                                 
/* *********************************************** */
void CreateProdDataWidget (int id, int width, int height, int alignment, string text, int font_size )
{
   createwidget (id, WIDGET_TYPE_TEXT_OUTPUT);
   widget_dimensions     (id,  width, height); //FCT_BUTTON_WIDTH, FCT_BUTTON_HEIGHT);      
   widget_fontsize       (id,  font_size); 
   widget_size_policy    (id,  SIZE_POLICY_FIXED,SIZE_POLICY_FIXED);     //SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_MINIMUM      
   widget_foreground     (id,  CL_PT_WHITE);
   if (alignment == align_hcenter)
   { 
      widget_text_alignment (id,  WIDGET_TEXT_ALIGN_HCENTER );
   }
   else if(alignment == align_left)
   {
      widget_text_alignment (id,  WIDGET_TEXT_ALIGN_LEFT);
   }
   else
   {
      widget_text_alignment (id,  WIDGET_TEXT_ALIGN_VCENTER );
   }
   widget_text           (id,  text );
   
   #if defined LAYOUT_TEST
      widget_background(id, "red" );
   #else
      widget_background(id, CL_PT_BLUE );
   #endif  
   
   widget_fontface(id,  FT_RTC_BOLD); 
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateProdDataPopupBox
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/03/17
--  
--  Purpose           : Prod Data Popup window creation    
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateProdDataPopupBox (void)         
{
  begindraw();
    createwindow (PRODDATA_POPUP_WINDOW, WINDOW_TYPE_POPUP, "Popup Window");
    windowstyle (PRODDATA_POPUP_WINDOW, POPUP_OUTBOX_STYLE2);      
      
      beginlayout (LAYOUT_TYPE_VBOX,0);
      
        beginlayout (LAYOUT_TYPE_VBOX,0);
         //Info Text
          createwidget (PRODDATA_POPUP, WIDGET_TYPE_TEXT_OUTPUT);
            widget_size_policy    (PRODDATA_POPUP,  SIZE_POLICY_MINIMUM, SIZE_POLICY_MINIMUM);
            widget_style          (PRODDATA_POPUP,  ST_BOXTEXT_STYLE); // ST_BOXTEXT_STYLE
            widget_fontsize       (PRODDATA_POPUP,  30); 
            widget_foreground     (PRODDATA_POPUP, CL_PT_BLUE );                               
            widget_text_alignment (PRODDATA_POPUP,  WIDGET_TEXT_ALIGN_HCENTER);
            widget_text           (PRODDATA_POPUP, concat(space(25),"Algorithm Statistical Data",space(25)));

        endlayout();


        beginlayout(LAYOUT_TYPE_VBOX, STD_EDGE_DISTANCE_NAVIG, FCT_BUTTON_DISTANCE_NAVIG);
 
         beginlayout(LAYOUT_TYPE_GRID, 0); // Grid Layout #1
            beginrow(); 
              CreateProdDataWidget (PRODDATA_STRING1, -1, -1, align_hcenter, "", 20);
              CreateProdDataWidget (PRODDATA_STRING2, -1, -1, align_hcenter, "", 20);
              CreateProdDataWidget (PRODDATA_STRING3, -1, -1, align_hcenter, "", 20);
            endrow(); 
            
            beginrow(); 
              CreateProdDataWidget (PRODDATA_STRING4, -1, -1, align_hcenter, "", 20);
              CreateProdDataWidget (PRODDATA_STRING5, -1, -1, align_hcenter, "               Cycle Machine for New Data                ", 20);
              CreateProdDataWidget (PRODDATA_STRING6, -1, -1, align_hcenter, "", 20);
            endrow(); 
            
            beginrow(); 
              CreateProdDataWidget (PRODDATA_STRING7, -1, -1, align_hcenter, "", 20);
              CreateProdDataWidget (PRODDATA_STRING8, -1, -1, align_hcenter, "", 20);
              CreateProdDataWidget (PRODDATA_STRING9, -1, -1, align_hcenter, "", 20);
            endrow();

        endlayout();       

            
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
        endlayout();
      
      endlayout();
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateWeighingDataPopupBox
--  Created by        : Jean-Pierre DorÃ©
--  Last modified on  : 2016/03/17
--  
--  Purpose           : Prod Data Popup window creation    
--                      
--  Value Parameters  :
--  Variable Params   : 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateWeighingDataPopupBox (void)         
{
 int width = 300,heigth = 27,font_wd = 16,i,j,between;
  begindraw();
    createwindow (WEIGHINGDATA_POPUP_WINDOW, WINDOW_TYPE_POPUP, "Popup Window");
    windowstyle (WEIGHINGDATA_POPUP_WINDOW, POPUP_OUTBOX_STYLE3);      
    
      beginlayout (LAYOUT_TYPE_VBOX,0);
      
        beginlayout (LAYOUT_TYPE_VBOX,0);
         //Info Text
         beginlayout(LAYOUT_TYPE_GRID, 0); // Grid Layout #1
            beginrow(); 
             createwidget (WEIGHINGDATA_POPUP, WIDGET_TYPE_TEXT_OUTPUT);
              widget_size_policy    (WEIGHINGDATA_POPUP,  SIZE_POLICY_MINIMUM, SIZE_POLICY_MINIMUM);
              widget_style          (WEIGHINGDATA_POPUP,  WEIGHINGDATA_STYLE); 
              widget_fontsize       (WEIGHINGDATA_POPUP,  20); 
              widget_foreground     (WEIGHINGDATA_POPUP, CL_PT_BLUE ); 
              widget_text_alignment (WEIGHINGDATA_POPUP,  WIDGET_TEXT_ALIGN_HCENTER);
              widget_text           (WEIGHINGDATA_POPUP, lsub(TX_WEIGHING_DATA));
            endrow();  
                             
        endlayout();


        beginlayout(LAYOUT_TYPE_HBOX, STD_EDGE_DISTANCE_NAVIG, FCT_BUTTON_DISTANCE_NAVIG);
 
         beginlayout(LAYOUT_TYPE_GRID, 0,0); // Grid Layout #1
            beginrow();
              CreateProdDataWidget (WEIGHINGDATA_TITLE_1+j, width, heigth, align_left, concat(lsub(TX_BULK),space(tab-1),lsub(TX_DRIBBLE),space(tab-2),lsub(TX_WEIGHT),space(tab+2),lsub(TX_TIME)),font_wd);
            endrow();  
            
            for(i=0;i<10;i++)
            {
             beginrow();
               CreateProdDataWidget(WEIGHINGDATA_STRING1_1+i, width, heigth, align_left, concat("0.00s",space(tab),"0.00s",space(tab),"0.00kg",space(tab),"00:00:00"), font_wd);
             endrow();
            }  
            
        endlayout();       

            
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
        endlayout();
      
      endlayout();
  enddraw();
}

  
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
/*   Create Weight Display                                                 */
/*                                                                         */
/* *********************************************************************** */
void CreateWeightDisplayX2(void) 
{
    CreateOutputDataField (DUPLEX_WEIGHT, FT_RTCMONO_BOLD, 19/*FT_STANDARD_SIZE*/, WIDGET_TEXT_ALIGN_CENTER, 125, 45, widget_locked);
    widget_size_policy  (DUPLEX_WEIGHT,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
    widget_style(DUPLEX_WEIGHT,WEIGHTBOX_STYLE);
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
          //CreatePTLogoHeader();
          CreateWeightDisplayX2();
          CreateAutoRecipeButton (ACTIVE_RECIPE_ID, FT_MEDIUM_SIZE, FT_RTC_BOLD, CL_PT_BLUE, CL_PT_WHITE, concat (space(1), lsub(WP.Name), space(1)));
         
          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
           //Fault and Mode display
           CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "2,2,0,0"); //"left,top,right,bottom"
        endlayout(); // End of search recipe button
    
 
       beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #6

//beginlayout(LAYOUT_TYPE_GRID, 0);        
//setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,0,0"); //"left,top,right,bottom"

       // First Column
       
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // Grid #1
//setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,0,0"); //"left,top,right,bottom" 
            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW1_ID,     CL_PT_BLUE, OFF, lsub(TX_TARGET_WEIGHT_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); //ON
              CreateOutputDataField (AUTO_ROW1_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW1_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW1_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked);              
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField (AUTO_ROW2_ID,     CL_PT_BLUE, OFF, lsub(TX_AVERAGE_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); //ON
              CreateOutputDataField (AUTO_ROW2_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW2_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW2_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked); 
  
            endrow();

            beginrow(); // Third row with three columns 
              CreatePromptField (AUTO_ROW3_ID,     CL_PT_BLUE, OFF, lsub(TX_STD_DEV_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); //ON
              CreateOutputDataField (AUTO_ROW3_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW3_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW3_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked);  
            endrow();

            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW4_ID,     CL_PT_BLUE, OFF, lsub(TX_LAST_CHECKED_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); //ON
              CreateOutputDataField (AUTO_ROW4_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW4_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked); 
              CreateUnitField   (AUTO_ROW4_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked); 
            endrow();

          endlayout();  // End Grid layout #1


        // Spacing between columns
          CreatePromptField (AUTO_SPACE_2,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_AUTO_SPACE2, HT_AUTO_DESCRIPTION, No_Margin, widget_locked);

       // Second Column

          //  First column on the Right
          beginlayout(LAYOUT_TYPE_GRID, 0,3); //Grid #2
//setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,0,0"); //"left,top,right,bottom" 
          
            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW11_ID,     CL_PT_BLUE, OFF, lsub(TX_UNITS_ACCEPTED_ID), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW11_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_LEFT, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW11_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_CENTER, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW11_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);           
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField (AUTO_ROW12_ID,     CL_PT_BLUE, OFF, lsub(TX_WEIGHS_PER_UNIT_ID), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW12_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW12_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_LEFT, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW12_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked); 
            endrow();

            beginrow(); // Third row with three columns 
              CreatePromptField (AUTO_ROW13_ID,     CL_PT_BLUE, OFF, lsub(TX_UNITS_DONE_ID), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW13_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_LEFT, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW13_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_CENTER, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW13_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);  
            endrow();

            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW14_ID,     CL_PT_BLUE, OFF, lsub(TX_PRESETS_PER_UNIT_ID), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW14_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW14_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_LEFT, (WD_AUTOPAGE_BOX2), HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW14_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);
            endrow();

          endlayout();  //Grid #2 
  
  
       // Third Column          
       // Spacing between columns
          CreatePromptField (AUTO_SPACE_3,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_AUTO_SPACE3, HT_AUTO_DESCRIPTION, No_Margin, widget_locked);
          
          //  First column on the Right
          beginlayout(LAYOUT_TYPE_GRID, 0,3); //Grid #3

            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW21_ID,     CL_PT_BLUE, OFF, lsub(TX_UNITSPERMIN_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW21_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW21_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_LEFT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW21_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          "" , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);             
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField (AUTO_ROW22_ID,     CL_PT_BLUE, OFF, lsub(TX_BULK_TIME_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW22_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW22_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW22_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          lsub(TX_SEC_UNIT) , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);
            endrow();

            beginrow(); // Third row with three columns 
              CreatePromptField (AUTO_ROW23_ID,     CL_PT_BLUE, OFF, lsub(TX_DRIBBLE_TIME_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW23_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW23_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW23_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          lsub(TX_SEC_UNIT) , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked); 
            endrow();

            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW24_ID,     CL_PT_BLUE, OFF, lsub(TX_CYCLE_TIME_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW24_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateOutputDataField (AUTO_ROW24_OUTPUT2, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX2, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW24_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          lsub(TX_SEC_UNIT) , WD_AUTO_SEC, HT_AUTOPAGE_BOX, widget_locked);
            endrow();
           setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,2,0"); //"left,top,right,bottom"
          endlayout();  //Grid #3                 


        endlayout(); // End of HBOX #6
        
      endlayout();  // End layout of VBOX #3


    endlayout();  // End layout of HBOX #2 


endlayout();  // End layout of Test Layout #1 

    createwidget (0, WIDGET_TYPE_STRETCH);
 
    beginlayout(LAYOUT_TYPE_GRID, 0,2);
     beginrow();
    /*Display message line*/
      createwidget (MESSAGE_DISPLAY1, WIDGET_TYPE_TEXT_OUTPUT);
        widget_foreground      (MESSAGE_DISPLAY1,   CL_PT_BLUE);
        widget_text_alignment  (MESSAGE_DISPLAY1,   WIDGET_TEXT_ALIGN_HCENTER);
        widget_fontsize        (MESSAGE_DISPLAY1,   PT_INFO_LINE);
        widget_size_policy     (MESSAGE_DISPLAY1,   SIZE_POLICY_FIXED, SIZE_POLICY_MINIMUM);
        widget_maximum_size    (MESSAGE_DISPLAY1,  500, 0);
        widget_text            (MESSAGE_DISPLAY1,   "");
        widget_text_alignment  (MESSAGE_DISPLAY1,   WIDGET_TEXT_ALIGN_LEFT);
        widget_content_margins (MESSAGE_DISPLAY1, Left_Margin,0,0,0);
        
    /*Display message line - Scale #2*/
      createwidget (MESSAGE_DISPLAY2, WIDGET_TYPE_TEXT_OUTPUT);
        widget_foreground      (MESSAGE_DISPLAY2,   CL_PT_BLUE);
        widget_text_alignment  (MESSAGE_DISPLAY2,   WIDGET_TEXT_ALIGN_HCENTER);
        widget_fontsize        (MESSAGE_DISPLAY2,   PT_INFO_LINE);
        widget_size_policy     (MESSAGE_DISPLAY2,   SIZE_POLICY_FIXED, SIZE_POLICY_MINIMUM);
        widget_maximum_size    (MESSAGE_DISPLAY2,  325, 0);
        widget_text            (MESSAGE_DISPLAY2,   "");
        widget_text_alignment  (MESSAGE_DISPLAY2,   WIDGET_TEXT_ALIGN_LEFT);
        widget_content_margins (MESSAGE_DISPLAY2, Left_Margin,0,0,0);    
     
         /*Display High resolution Weight*/   
      createwidget (HIRESWEIGHT, WIDGET_TYPE_TEXT_OUTPUT);
        widget_foreground      (HIRESWEIGHT,   CL_PT_BLUE);
        widget_text_alignment  (HIRESWEIGHT,   WIDGET_TEXT_ALIGN_HCENTER);
        widget_fontsize        (HIRESWEIGHT,   PT_INFO_LINE);
        widget_size_policy     (HIRESWEIGHT,   SIZE_POLICY_FIXED, SIZE_POLICY_MINIMUM);
        widget_maximum_size    (HIRESWEIGHT,  175, 0);
        widget_text            (HIRESWEIGHT,   concat(NetWeightHiRes[Scale1],space(1),WP.Unit,space(1)));
        widget_text_alignment  (HIRESWEIGHT,   WIDGET_TEXT_ALIGN_RIGHT);
        widget_content_margins (HIRESWEIGHT, 0,2,0,0);    

     
    endlayout();
     
      CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
      DrawNavButtons (SCREEN_AUTOMATIC, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_DISCH_PAN_OFF, BTN_OFF, HOPPER_FILL, BTN_START, BTN_STOP);   
    
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
 bool    FirstPassDone;
 decimal TargetWeightTemp%6.2[2],ProdAvgWeightTemp%6.2[2],ProdStdDevTemp%6.4[2],ProdLastCheckedTemp%7.3[2];
 decimal ProdAcceptUnitCntTemp%6.0[2],WeighPerUnitAccTemp%5.0,ProdTotalUnitsCntTemp%10.0[2];
 decimal ProdCycleUnitsPerMinTemp%6.2,ProdBulkDurationTemp%6.2[2],ProdDribbleDurationTemp%6.2[2],ProdCycleDurationTemp%6.2[2];
 int     Batch_CountTemp;

 if(RefreshAll)
 {
  FirstPassDone = OFF;
 } 
         
         
  begindraw();
        if(SeqModeManager == stp_OFF_MODE)RefreshRecipeInAutoScreen();
        //RefreshCurrentUser();

  // First Column                                
                                        
        // First Row Info 
        if(TargetWeightTemp[Scale1] != TargetWeight[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW1_OUTPUT, adj(TargetWeight[Scale1],6,DP[Scale1]));
         TargetWeightTemp[Scale1] = TargetWeight[Scale1];
        } 
        
        if(TargetWeightTemp[Scale2] != TargetWeight[Scale2] || !FirstPassDone)
        {
         widget_text (AUTO_ROW1_OUTPUT2, adj(TargetWeight[Scale2],6,DP[Scale2]));
         TargetWeightTemp[Scale2] = TargetWeight[Scale2];
        } 
        if(SeqModeManager == stp_OFF_MODE) widget_text (AUTO_ROW1_UNIT, WP.Unit);
  
        // 2nd Row Info 
        if(ProdAvgWeightTemp[Scale1] != ProdAvgWeight[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW2_OUTPUT, adj(ProdAvgWeight[Scale1],6,DP[Scale1]));
         ProdAvgWeightTemp[Scale1] = ProdAvgWeight[Scale1];
        }
        
        if(ProdAvgWeightTemp[Scale2] != ProdAvgWeight[Scale2] || !FirstPassDone)
        { 
         widget_text (AUTO_ROW2_OUTPUT2, adj(ProdAvgWeight[Scale2],6,DP[Scale2]));
         ProdAvgWeightTemp[Scale2] = ProdAvgWeight[Scale2];
        }
        if(SeqModeManager == stp_OFF_MODE) widget_text (AUTO_ROW2_UNIT, WP.Unit); 
                                         
        // Third Row Info 
        if(ProdStdDevTemp[Scale1] != ProdStdDev[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW3_OUTPUT, adj(ProdStdDev[Scale1],6,DP[Scale1]+2));
         ProdStdDevTemp[Scale1] = ProdStdDev[Scale1];
        } 
         
        if(ProdStdDevTemp[Scale2] != ProdStdDev[Scale2] || !FirstPassDone)
        {
         widget_text (AUTO_ROW3_OUTPUT2, adj(ProdStdDev[Scale2],6,DP[Scale2]+2));
         ProdStdDevTemp[Scale2] = ProdStdDev[Scale2];
        } 
        if(SeqModeManager == stp_OFF_MODE) widget_text (AUTO_ROW3_UNIT, WP.Unit); 
                                        
        // Fourth Row Info 
        if(ProdLastCheckedTemp[Scale1] != ProdLastChecked[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW4_OUTPUT, adj(ProdLastChecked[Scale1],7,DP[Scale1]));
         ProdLastCheckedTemp[Scale1] = ProdLastChecked[Scale1];
        }
        
        if(ProdLastCheckedTemp[Scale2] != ProdLastChecked[Scale2] || !FirstPassDone)
        { 
         widget_text (AUTO_ROW4_OUTPUT2, adj(ProdLastChecked[Scale2],7,DP[Scale2]));
         ProdLastCheckedTemp[Scale2] = ProdLastChecked[Scale2];
        }
        if(SeqModeManager == stp_OFF_MODE) widget_text (AUTO_ROW4_UNIT, WP.Unit);

        
  // Second Column                               
                                        
        // First Row Info 
        if(ProdAcceptUnitCntTemp[Scale1] != ProdAcceptUnitCnt[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW11_OUTPUT, trim(string(int(ProdAcceptUnitCnt[Scale1]))));
         ProdAcceptUnitCntTemp[Scale1] = ProdAcceptUnitCnt[Scale1];
        } 
        
        if(ProdAcceptUnitCntTemp[Scale2] != ProdAcceptUnitCnt[Scale2] || !FirstPassDone)
        {
         widget_text (AUTO_ROW11_OUTPUT2, trim(string(int(ProdAcceptUnitCnt[Scale2]))));
         ProdAcceptUnitCntTemp[Scale2] = ProdAcceptUnitCnt[Scale2];
        } 
  
        // 2nd Row Info 
        if(WeighPerUnitAccTemp != WeighPerUnitAcc || !FirstPassDone)
        {
         widget_text (AUTO_ROW12_OUTPUT, concat(trim(string(WeighPerUnitAcc))," / "));
         WeighPerUnitAccTemp = WeighPerUnitAcc;
        }
        if(SeqModeManager == stp_OFF_MODE) widget_text (AUTO_ROW12_OUTPUT2, trim(string(WP.WeighmentsPerUnit)));                                

        // Third Row Info 
        if(ProdTotalUnitsCntTemp[Scale1] != ProdTotalUnitsCnt[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW13_OUTPUT,  trim(string(int(ProdTotalUnitsCnt[Scale1]))));
         ProdTotalUnitsCntTemp[Scale1] = ProdTotalUnitsCnt[Scale1];
        }
        
        if(ProdTotalUnitsCntTemp[Scale2] != ProdTotalUnitsCnt[Scale2] || !FirstPassDone)
        {
         widget_text (AUTO_ROW13_OUTPUT2,  trim(string(int(ProdTotalUnitsCnt[Scale2]))));
         ProdTotalUnitsCntTemp[Scale2] = ProdTotalUnitsCnt[Scale2];
        }
                                        
        // Fourth Row Info 
        if(Batch_CountTemp != Batch.Count || !FirstPassDone)
        {
         widget_text (AUTO_ROW14_OUTPUT, concat(trim(string(Batch.Count))," / "));
         Batch_CountTemp = Batch.Count;
        } 
        if(SeqModeManager == stp_OFF_MODE || SeqModeManager == stp_STOP_MODE) widget_text (AUTO_ROW14_OUTPUT2,trim(string(Batch.Preset)));



  // Third Column                               
                                        
        // First Row Info 
        if(ProdCycleUnitsPerMinTemp != ProdCycleUnitsPerMin || !FirstPassDone)
        {
         widget_text (AUTO_ROW21_OUTPUT2, ProdCycleUnitsPerMin);
         ProdCycleUnitsPerMinTemp = ProdCycleUnitsPerMin;
        }
         
        // 2nd Row Info
        if(ProdBulkDurationTemp[Scale1] != ProdBulkDuration[Scale1] || !FirstPassDone)
        { 
         widget_text (AUTO_ROW22_OUTPUT, ProdBulkDuration[Scale1]);
         ProdBulkDurationTemp[Scale1] = ProdBulkDuration[Scale1];
        } 
        
        if(ProdBulkDurationTemp[Scale2] != ProdBulkDuration[Scale2] || !FirstPassDone)
        {
         widget_text (AUTO_ROW22_OUTPUT2, ProdBulkDuration[Scale2]);
         ProdBulkDurationTemp[Scale2] = ProdBulkDuration[Scale2];
        } 
                                         
        // Third Row Info 
        if(ProdDribbleDurationTemp[Scale1] != ProdDribbleDuration[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW23_OUTPUT, ProdDribbleDuration[Scale1]);
         ProdDribbleDurationTemp[Scale1] = ProdDribbleDuration[Scale1];
        }
        
        if(ProdDribbleDurationTemp[Scale2] != ProdDribbleDuration[Scale2] || !FirstPassDone)
        { 
         widget_text (AUTO_ROW23_OUTPUT2, ProdDribbleDuration[Scale2]);
         ProdDribbleDurationTemp[Scale2] = ProdDribbleDuration[Scale2];
        }
                                       
        // Fourth Row Info 
        if(ProdCycleDurationTemp[Scale1] != ProdCycleDuration[Scale1] || !FirstPassDone)
        {
         widget_text (AUTO_ROW24_OUTPUT, ProdCycleDuration[Scale1]);
         ProdCycleDurationTemp[Scale1] = ProdCycleDuration[Scale1];
        }
        
        if(ProdCycleDurationTemp[Scale2] != ProdCycleDuration[Scale2] || !FirstPassDone)
        {
         widget_text (AUTO_ROW24_OUTPUT2, ProdCycleDuration[Scale2]);
         ProdCycleDurationTemp[Scale2] = ProdCycleDuration[Scale2];
        }
        
        //Messages display - both
        if(MessageTextTemp[Scale1] != MessageText[Scale1] || !FirstPassDone)
        {
         widget_background     (MESSAGE_DISPLAY1, MessageColor[Scale1]);
         widget_text           (MESSAGE_DISPLAY1, MessageText[Scale1]);

         MessageTextTemp[Scale1] = MessageText[Scale1];
        }
         
        if(MessageTextTemp[Scale2] != MessageText[Scale2] || !FirstPassDone)
        {
         widget_background     (MESSAGE_DISPLAY2, MessageColor[Scale2]);
         widget_text           (MESSAGE_DISPLAY2, MessageText[Scale2]);
         widget_background     (HIRESWEIGHT, MessageColor[Scale2]);
         MessageTextTemp[Scale2] = MessageText[Scale2];
        }

  enddraw(); 
  
  FirstPassDone = ON;                                       
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
    widget_fontface       (id,  FT_RTC_BOLD); 
}




/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateWeighingDataPopupBox
--  Created by        : Steve Santerre
--  Last modified on  : 2018/02/02
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
              widget_text           (WEIGHINGDATA_POPUP, concat("#1",space(30),"Weighing Data",space(30),"#2"));
            endrow();  
                             
        endlayout();


        beginlayout(LAYOUT_TYPE_HBOX, STD_EDGE_DISTANCE_NAVIG, FCT_BUTTON_DISTANCE_NAVIG);
 
         beginlayout(LAYOUT_TYPE_GRID, 0,0); // Grid Layout #1
            beginrow();
            for(j=0;j<2;j++)
            {
              CreateProdDataWidget (WEIGHINGDATA_TITLE_1+j, width, heigth, align_left, concat("Bulk",space(tab-1),"Dribble",space(tab-2),"Weight",space(tab+2),"Time"),font_wd);
              if(j==0)CreateProdDataWidget(WEIGHINGDATA_TITLE_SPACE+i, 25, heigth, align_left, "", font_wd);
            }
            endrow();  
            
            for(i=0;i<10;i++)
            {
             beginrow();
              for(j=0;j<2;j++)
              {
               CreateProdDataWidget(WEIGHINGDATA_STRING1_1+j+(2*i), width, heigth, align_left, concat("0.00s",space(tab),"0.00s",space(tab),"0.00kg",space(tab),"00:00:00"), font_wd);
               if(j==0)CreateProdDataWidget(WEIGHINGDATA_STRING1_SPACE+i, 25, heigth, align_left, "", font_wd);
              }
             endrow();
            }  
            
        endlayout();       

            
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
        endlayout();
      
      endlayout();
  enddraw();
}
 
  
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
       // First Column
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // Grid #1
            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW1_ID,     CL_PT_BLUE, OFF, lsub(TX_TARGET_WEIGHT_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW1_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW1_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked);              
            endrow();

            beginrow(); // Second row with three columns 
              CreatePromptField (AUTO_ROW2_ID,     CL_PT_BLUE, OFF, lsub(TX_AVERAGE), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW2_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW2_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked); 
  
            endrow();

          endlayout();  // End Grid layout #1


        // Spacing between columns
          CreatePromptField (AUTO_SPACE_3,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_AUTO_SPACE, HT_AUTO_DESCRIPTION, No_Margin, widget_locked);

       // Second Column
          //  First column on the Right
          beginlayout(LAYOUT_TYPE_GRID, 0,3); //Grid #2
            
            beginrow(); // Third row with three columns 
              CreatePromptField (AUTO_ROW11_ID,     CL_PT_BLUE, OFF, lsub(TX_STD_DEV), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW11_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked);
              CreateUnitField   (AUTO_ROW11_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked);  
            endrow();

            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW12_ID,     CL_PT_BLUE, OFF, lsub(TX_LAST_CHECKED_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION, HT_AUTO_DESCRIPTION, Left_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW12_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX, HT_AUTOPAGE_BOX, widget_locked); 
              CreateUnitField   (AUTO_ROW12_UNIT,  FT_RTC_BOLD, FT_AUTOPAGE2_SIZE,          WP.Unit , WD_AUTO_UNIT, HT_AUTOPAGE_BOX, widget_locked); 
            endrow();
          
          endlayout();  //Grid #2 
  
          // Spacing between columns
          CreatePromptField (AUTO_SPACE_4,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_AUTO_SPACE, HT_AUTO_DESCRIPTION, No_Margin, widget_locked);
          
       // Third Column          
          //  First column on the Right
          beginlayout(LAYOUT_TYPE_GRID, 0,3); //Grid #3

            beginrow(); // First row with three columns
              CreatePromptField (AUTO_ROW21_ID,     CL_PT_BLUE, OFF, lsub(TX_UNITSPERMIN_ID), FT_AUTOPAGE2_SIZE, WD_AUTO_DESCRIPTION-50, HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW21_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, WD_AUTOPAGE_BOX+50, HT_AUTOPAGE_BOX, widget_locked);
            endrow();
            
            beginrow(); // Fourth row with three columns 
              CreatePromptField (AUTO_ROW22_ID,     CL_PT_BLUE, OFF, lsub(TX_BATCH), FT_AUTOPAGE2_SIZE, (WD_AUTO_DESCRIPTION-50), HT_AUTO_DESCRIPTION, No_Margin, widget_locked); 
              CreateOutputDataField (AUTO_ROW22_OUTPUT, FT_RTC_BOLD, FT_AUTOPAGE2_SIZE, WIDGET_TEXT_ALIGN_RIGHT, (WD_AUTOPAGE_BOX+50), HT_AUTOPAGE_BOX, widget_locked);
            endrow();
                        
          endlayout();  //Grid #3                 

        endlayout(); // End of HBOX #6
      
       
        beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #7
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,0,0,0"); //"left,top,right,bottom"  
          beginlayout(LAYOUT_TYPE_VBOX);     
           CreateTolImage(AUTO_ROW111_ID,TOL_UNDER_REJ);
           CreatePromptField (AUTO_ROW111_OUTPUT,CL_PT_BLUE, OFF, "COUNT", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin, widget_locked);
           widget_text_alignment(AUTO_ROW111_OUTPUT,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
           CreatePromptField (AUTO_ROW111_OUTPUT2,CL_PT_BLUE, ON, "1234567", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin, widget_locked);
           widget_text_alignment(AUTO_ROW111_OUTPUT2,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
         endlayout();
         
         beginlayout(LAYOUT_TYPE_VBOX);
           CreateTolImage(AUTO_ROW112_ID,TOL_UNDER_ACC);
           CreatePromptField (AUTO_ROW112_OUTPUT,CL_PT_BLUE, OFF, "COUNT", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin, widget_locked);
           widget_text_alignment(AUTO_ROW112_OUTPUT,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
           CreatePromptField (AUTO_ROW112_OUTPUT2,CL_PT_BLUE, ON, "1234567", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW112_OUTPUT2,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
        endlayout();
        
        beginlayout(LAYOUT_TYPE_VBOX); 
           CreateTolImage(AUTO_ROW113_ID,TOL_GOOD);
           CreatePromptField (AUTO_ROW113_OUTPUT,CL_PT_BLUE, OFF, "COUNT", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW113_OUTPUT,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
           CreatePromptField (AUTO_ROW113_OUTPUT2,CL_PT_BLUE, ON, "1234567", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW113_OUTPUT2,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
        endlayout();
        
        beginlayout(LAYOUT_TYPE_VBOX); 
           CreateTolImage(AUTO_ROW114_ID,TOL_OVER_ACC);
           CreatePromptField (AUTO_ROW114_OUTPUT,CL_PT_BLUE, OFF, "COUNT", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW114_OUTPUT,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
           CreatePromptField (AUTO_ROW114_OUTPUT2,CL_PT_BLUE, ON, "1234567", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW114_OUTPUT2,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
        endlayout();
        
        beginlayout(LAYOUT_TYPE_VBOX); 
           CreateTolImage(AUTO_ROW115_ID,TOL_OVER_REJ);
           CreatePromptField (AUTO_ROW115_OUTPUT,CL_PT_BLUE, OFF, "COUNT", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW115_OUTPUT,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
           CreatePromptField (AUTO_ROW115_OUTPUT2,CL_PT_BLUE, ON, "1234567", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW115_OUTPUT2,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
        endlayout(); 
         
         beginlayout(LAYOUT_TYPE_VBOX); 
           CreateTolImage(AUTO_ROW116_ID,TOL_INVALID);
           CreatePromptField (AUTO_ROW116_OUTPUT,CL_PT_BLUE, OFF, lsub(TX_INVALID), FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW116_OUTPUT,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
           CreatePromptField (AUTO_ROW116_OUTPUT2,CL_PT_BLUE, ON, "1234567", FT_AUTOPAGE_SIZE_TOL, WD_AUTO_DESCRIPTION_TOL, HT_AUTO_DESCRIPTION_TOL, Left_Margin,widget_locked);
           widget_text_alignment(AUTO_ROW116_OUTPUT2,(WIDGET_TEXT_ALIGN_HCENTER | WIDGET_TEXT_ALIGN_VCENTER));
        endlayout();
        
        endlayout();  // End layout of HBOX #7
         
      endlayout();  // End layout of VBOX #3


    endlayout();  // End layout of HBOX #2 


endlayout();  // End layout of Test Layout #1 

    createwidget (0, WIDGET_TYPE_STRETCH);
 
    beginlayout(LAYOUT_TYPE_GRID, 0,0);
    setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "2,2,2,0"); //"left,top,right,bottom"
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
        widget_text            (HIRESWEIGHT,   concat(NetWeightHiRes,space(1),WP.Unit,space(1)));
        widget_text_alignment  (HIRESWEIGHT,   WIDGET_TEXT_ALIGN_RIGHT);
        widget_content_margins (HIRESWEIGHT, 0,2,0,0);    
     endrow();   
    endlayout();
     
      CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
      DrawNavButtons (SCREEN_AUTOMATIC, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_BATCH, BTN_OFF, BTN_NIL_GRAYOUT, BTN_START, BTN_STOP);   
    
  endlayout(); // End layout of VBOX #1 
  
enddraw();

}

void RefreshTol(int prev,int actual)
{

  //Put Previous back to Normal
 if(prev>= TolURej && prev<= TolInvalid)
 { 
  widget_text(AUTO_ROWTOL_ID+prev,OFF);
  widget_foreground   (AUTO_ROWTOL_OUTPUT+prev,  CL_PT_BLUE); 
  widget_background   (AUTO_ROWTOL_OUTPUT+prev,  CL_WHITE);
  widget_foreground   (AUTO_ROWTOL_OUTPUT2+prev, CL_PT_BLUE); 
  widget_background   (AUTO_ROWTOL_OUTPUT2+prev, CL_WHITE);
 }
  
  //Put Actual to Inverted colors
 if(actual>= TolURej && actual<= TolInvalid)
 {  
  widget_text(AUTO_ROWTOL_ID+actual,ON);
  widget_foreground   (AUTO_ROWTOL_OUTPUT+actual,  CL_WHITE); 
  widget_background   (AUTO_ROWTOL_OUTPUT+actual,  CL_PT_BLUE);
  widget_foreground   (AUTO_ROWTOL_OUTPUT2+actual, CL_WHITE); 
  widget_background   (AUTO_ROWTOL_OUTPUT2+actual, CL_PT_BLUE);
 } 
 
}           

/* *********************************************************************** */
/*                                                                         */
/*       Refresh Auto screen display                                       */
/*                                                                         */
/* *********************************************************************** */

void RefreshAutoScreen(bool RefreshAll)
{
 bool    FirstPassDone;
 decimal NominalWeightTemp%6.2,NominalWeight113Temp%6.2,ProdAvgWeightTemp%6.2,ProdStdDevTemp%6.4,ProdLastCheckedTemp%7.3;
 int     BatchPresetTemp%6.0;
 decimal TolUnderRejWeightTemp%6.2,TolUnderAccWeightTemp%6.2,TolOverRejWeightTemp%6.2,TolOverAccWeightTemp%6.2;
 
 decimal ProdCycleUnitsPerMinTemp%6.2;
 int     TotalCountTemp;
  
  if(RefreshAll)
  {
   FirstPassDone = OFF;
  }

  begindraw();
        if(SeqModeManager == stp_OFF_MODE)RefreshRecipeInAutoScreen();

  // First Column                                
        // First Row Info 
        if(NominalWeightTemp != WP.NominalWeight || !FirstPassDone)
        {
         widget_text (AUTO_ROW1_OUTPUT, adj(WP.NominalWeight,6,dp));
         NominalWeightTemp = WP.NominalWeight;
        } 
        if(SeqModeManager == stp_OFF_MODE)widget_text (AUTO_ROW1_UNIT, WP.Unit);
  
        // 2nd Row Info 
        if(ProdAvgWeightTemp != ProdAvgWeight || !FirstPassDone) //
        {
         widget_text (AUTO_ROW2_OUTPUT, adj(ProdAvgWeight,6,dp));
         ProdAvgWeightTemp = ProdAvgWeight;
        } 
        if(SeqModeManager == stp_OFF_MODE)widget_text (AUTO_ROW2_UNIT, WP.Unit); 
    
    // Second Column                                      
        // First Row Info
        if(ProdStdDevTemp != ProdStdDev || !FirstPassDone)
        {
         widget_text (AUTO_ROW11_OUTPUT, adj(ProdStdDev,6,dp+2));
         ProdStdDevTemp = ProdStdDev;
        } 
        if(SeqModeManager == stp_OFF_MODE)widget_text (AUTO_ROW11_UNIT, WP.Unit); 
                                        
        // 2nd Row Info 
        if(ProdLastCheckedTemp != ProdLastChecked || !FirstPassDone)
        {
         widget_text (AUTO_ROW12_OUTPUT, adj(ProdLastChecked,6,dp));
         ProdLastCheckedTemp = ProdLastChecked;
        } 
        if(SeqModeManager == stp_OFF_MODE)widget_text (AUTO_ROW12_UNIT, WP.Unit);


  // Third Column                               
        // First Row Info 
        if(ProdCycleUnitsPerMinTemp != ProdCycleUnitsPerMin || !FirstPassDone)
        {
         widget_text (AUTO_ROW21_OUTPUT, ProdCycleUnitsPerMin);
         ProdCycleUnitsPerMinTemp = ProdCycleUnitsPerMin;
        }
    
    
    //Total units    
    if(Batch.Preset > 0)
      {  
        if(BatchPresetTemp != Batch.Preset)
        { 
         widget_text       (AUTO_ROW22_ID,   lsub(TX_BATCH));
         BatchPresetTemp = Batch.Preset;
        }
        // 2nd Row Info 
        if(TotalCountTemp != Batch.Count || !FirstPassDone || SeqModeManager == stp_OFF_MODE)
        { 
         widget_text (AUTO_ROW22_OUTPUT, concat(Batch.Count,"/",Batch.Preset));
         TotalCountTemp = Batch.Count;
        } 
      }
     else
      {  
        if(BatchPresetTemp != Batch.Preset)
        { 
         widget_text       (AUTO_ROW22_ID,   lsub(TX_ID_UNITS_DONE));
         BatchPresetTemp = Batch.Preset;
        }
        // 2nd Row Info 
        if(TotalCountTemp != WP.TolTotalCnt || !FirstPassDone || SeqModeManager == stp_OFF_MODE)
        { 
         widget_text (AUTO_ROW22_OUTPUT, trim(WP.TolTotalCnt));
         TotalCountTemp = WP.TolTotalCnt;
        } 
      }
        
    //Under Reject
     if(TolUnderRejWeightTemp != WP.TolUnderRejWeight || !FirstPassDone)
        { 
         widget_text (AUTO_ROW111_OUTPUT, concat("<= ",adj(WP.TolUnderRejWeight,6,dp),WP.Unit));
         TolUnderRejWeightTemp = WP.TolUnderRejWeight;
        } 
        
    if(Batch.Preset > 0)
      { 
        
        if(TolUnderRejCntTemp != Batch.TolUnderRejCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW111_OUTPUT2, trim(Batch.TolUnderRejCnt));
         TolUnderRejCntTemp = Batch.TolUnderRejCnt;
        }
      }
    else
      { 
        if(TolUnderRejCntTemp != WP.TolUnderRejCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW111_OUTPUT2, trim(WP.TolUnderRejCnt));
         TolUnderRejCntTemp = WP.TolUnderRejCnt;
        }
      }        
        
    //Under Accept
     if(TolUnderAccWeightTemp != WP.TolUnderAccWeight || !FirstPassDone)
        { 
         widget_text (AUTO_ROW112_OUTPUT, concat("<= ",adj(WP.TolUnderAccWeight,6,dp),WP.Unit));
         TolUnderAccWeightTemp = WP.TolUnderAccWeight;
        } 
        
    if(Batch.Preset > 0)
      { 
        if(TolUnderAccCntTemp != Batch.TolUnderAccCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW112_OUTPUT2, trim(Batch.TolUnderAccCnt));
         TolUnderAccCntTemp = Batch.TolUnderAccCnt;
        } 
      }
     else
      { 
        if(TolUnderAccCntTemp != WP.TolUnderAccCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW112_OUTPUT2, trim(WP.TolUnderAccCnt));
         TolUnderAccCntTemp = WP.TolUnderAccCnt;
        } 
      } 
        
    //Good
     if(NominalWeight113Temp != WP.NominalWeight || !FirstPassDone)
        { 
         widget_text (AUTO_ROW113_OUTPUT, concat(adj(WP.NominalWeight,6,dp),WP.Unit));
         NominalWeight113Temp = WP.NominalWeight;
        } 
        
    if(Batch.Preset > 0)
      {
        if(TolGoodCntTemp != Batch.TolGoodCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW113_OUTPUT2, trim(Batch.TolGoodCnt));
         TolGoodCntTemp = Batch.TolGoodCnt;
        } 
      }
    else
      {
        if(TolGoodCntTemp != WP.TolGoodCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW113_OUTPUT2, trim(WP.TolGoodCnt));
         TolGoodCntTemp = WP.TolGoodCnt;
        } 
      }  
        
    //Over Accept
      if(TolOverAccWeightTemp != WP.TolOverAccWeight || !FirstPassDone)
        { 
         widget_text (AUTO_ROW114_OUTPUT, concat(">= ",adj(WP.TolOverAccWeight,6,dp),WP.Unit));
         TolOverAccWeightTemp = WP.TolOverAccWeight;
        } 
       
     if(Batch.Preset > 0)
      { 
        if(TolOverAccCntTemp != Batch.TolOverAccCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW114_OUTPUT2, trim(Batch.TolOverAccCnt));
         TolOverAccCntTemp = Batch.TolOverAccCnt;
        } 
      }
     else
      { 
        if(TolOverAccCntTemp != WP.TolOverAccCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW114_OUTPUT2, trim(WP.TolOverAccCnt));
         TolOverAccCntTemp = WP.TolOverAccCnt;
        } 
      } 
        
    //Over Reject
      if(TolOverRejWeightTemp != WP.TolOverRejWeight || !FirstPassDone)
        { 
         widget_text (AUTO_ROW115_OUTPUT, concat(">= ",adj(WP.TolOverRejWeight,6,dp),WP.Unit));
         TolOverRejWeightTemp = WP.TolOverRejWeight;
        } 
     
     if(Batch.Preset > 0)
      {   
        if(TolOverRejCntTemp != Batch.TolOverRejCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW115_OUTPUT2, trim(Batch.TolOverRejCnt));
         TolOverRejCntTemp = Batch.TolOverRejCnt;
        } 
      }
     else
      {   
        if(TolOverRejCntTemp != WP.TolOverRejCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW115_OUTPUT2, trim(WP.TolOverRejCnt));
         TolOverRejCntTemp = WP.TolOverRejCnt;
        } 
      } 
        
    //Invalid
     if(Batch.Preset > 0)
      {           
        if(TolInvalidCntTemp != Batch.TolInvalidCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW116_OUTPUT2, trim(Batch.TolInvalidCnt));
         TolInvalidCntTemp = Batch.TolInvalidCnt;
        } 
      }
     else
      {           
        if(TolInvalidCntTemp != WP.TolInvalidCnt || !FirstPassDone)
        { 
         widget_text (AUTO_ROW116_OUTPUT2, trim(WP.TolInvalidCnt));
         TolInvalidCntTemp = WP.TolInvalidCnt;
        } 
      } 
        
        if(TolTypeMem != TolType)
        {
         RefreshTol(TolTypeMem,TolType); 
         TolTypeMem = TolType;
        }  
               
        if(MessageTextTemp != MessageText || !FirstPassDone)
        {
         widget_background     (MESSAGE_DISPLAY, MessageColor);
         widget_text           (MESSAGE_DISPLAY, MessageText);
         widget_background     (HIRESWEIGHT, HiResColor);
         MessageTextTemp = MessageText;
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
 int width = 370,heigth = 27,font_wd = 16,i,j,between;
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
              widget_text           (WEIGHINGDATA_POPUP, "Weighing Data");
            endrow();  
                             
        endlayout();


        beginlayout(LAYOUT_TYPE_HBOX, STD_EDGE_DISTANCE_NAVIG, FCT_BUTTON_DISTANCE_NAVIG);
 
         beginlayout(LAYOUT_TYPE_GRID, 0,0); // Grid Layout #1
            beginrow();
              CreateProdDataWidget (WEIGHINGDATA_TITLE_1+j, width, heigth, align_left, 
                  concat("Weight",space(tab-1),"Tol",space(tab+1),"Limit",space(tab),"Evaluation",space(tab),"Time"),font_wd);
            endrow();  
            
            for(i=0;i<10;i++)
            {
             beginrow();
               CreateProdDataWidget(WEIGHINGDATA_STRING1_1+i, width, heigth, align_left, 
                   concat("00.00",WP.Unit,space(tab),"= ",space(tab),"00.00",WP.Unit,space(tab),"0.00sec",space(tab),"00:00:00"), font_wd);
             endrow();
            }  
            
        endlayout();       

            
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH); 
        endlayout();
      
      endlayout();
  enddraw();
}
  
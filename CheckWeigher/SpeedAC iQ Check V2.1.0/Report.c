/* *********************************************************************** */
/*                                                                         */
/*   Create REPORT page #1                                                 */
/*                                                                         */
/* *********************************************************************** */

void CreateReportPage(void) 
{
  begindraw();
  createpage(PAGE_REPORT);  
  page_background (PAGE_REPORT, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // 
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // 

        // ##### Header #####
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
          CreatePTLogoHeader();
          CreateHeader (REPORT_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_REPORT_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #6   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #6
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // End of HBOX #5 //End of Header       

      

        beginlayout(LAYOUT_TYPE_GRID, 0,3); // HBOX #8
        setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "50,0,50,0"); //"left,top,right,bottom" 
          CreatePromptField (REPORT_ROW7_ID,    CL_PT_BLUE, ON, concat(lsub(TX_ID_ACTUAL_PROD)), FT_STANDARD_SIZE, WD_REPORT_DESCRIPTION1, HT_REPORT_DESCRIPTION, Left_Margin, widget_locked);
          CreatePromptField (REPORT_ROW7_INPUT,    CL_PT_BLUE, OFF, concat("(",lsub(WP.Name),")"), FT_STANDARD_SIZE, WD_REPORT_DESCRIPTION2, HT_REPORT_DESCRIPTION, No_Margin, widget_locked);
          widget_text_alignment (REPORT_ROW7_INPUT,  WIDGET_TEXT_ALIGN_CENTER );           
          CreatePromptField (REPORT_ROW7_ID2,    CL_PT_BLUE, ON, concat(lsub(TX_ID_ACTUAL_PROD)), FT_STANDARD_SIZE, WD_REPORT_DESCRIPTION1, HT_REPORT_DESCRIPTION, Left_Margin, widget_locked);
        endlayout(); //HBOX #8

       beginlayout(LAYOUT_TYPE_VBOX); 
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #7
       
        //First column on the left
         beginlayout(LAYOUT_TYPE_VBOX);
            
          beginlayout(LAYOUT_TYPE_HBOX, 0);
              CreatePromptField (REPORT_ROW1_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_NOMINAL_WEIGHT), FT_STANDARD_SIZE, WD_REPORT_COLUMN1, HT_REPORT_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW1_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_REPORT_COLUMN2, HT_REPORT_BOX, widget_locked);
              CreateUnitField   (REPORT_ROW1_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          WP.Unit , WD_UNIT, HT_REPORT_BOX, widget_locked);            
          endlayout();
            
          beginlayout(LAYOUT_TYPE_HBOX, 0);
              CreatePromptField (REPORT_ROW2_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_UNITS_DONE), FT_STANDARD_SIZE, WD_REPORT_COLUMN1, HT_REPORT_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW2_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_REPORT_COLUMN2, HT_REPORT_BOX, widget_locked);
              CreateUnitField   (REPORT_ROW2_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          "", WD_UNIT, HT_REPORT_BOX, widget_locked );   
          endlayout();
            
          beginlayout(LAYOUT_TYPE_HBOX, 0);
              CreatePromptField (REPORT_ROW3_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_TOTAL_WEIGHT), FT_STANDARD_SIZE, WD_REPORT_COLUMN1, HT_REPORT_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW3_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_REPORT_COLUMN2, HT_REPORT_BOX, widget_locked);
              CreateUnitField   (REPORT_ROW3_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          WP.Unit, WD_UNIT, HT_REPORT_BOX, widget_locked );  
          endlayout();
        
         beginlayout(LAYOUT_TYPE_HBOX, 0);     
              CreatePromptField (REPORT_ROW4_ID,    CL_PT_BLUE, ON, lsub(TX_ID_LIFETIME_PROD), FT_STANDARD_SIZE, WD_REPORT_COLUMN1, HT_REPORT_DESCRIPTION, No_Margin, widget_unlocked);
         endlayout();
         
         beginlayout(LAYOUT_TYPE_HBOX, 0);
              CreatePromptField (REPORT_ROW5_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_TOTAL_UNITS), FT_STANDARD_SIZE, WD_REPORT_COLUMN1, HT_REPORT_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW5_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_REPORT_COLUMN2, HT_REPORT_BOX, widget_locked);
              CreateUnitField   (REPORT_ROW5_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          "", WD_UNIT, HT_REPORT_BOX, widget_locked ); 
         endlayout();
            
         beginlayout(LAYOUT_TYPE_HBOX, 0);
              CreatePromptField (REPORT_ROW6_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_TOTAL_WEIGHT), FT_STANDARD_SIZE, WD_REPORT_COLUMN1, HT_REPORT_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW6_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_REPORT_COLUMN2, HT_REPORT_BOX, widget_locked);
              CreateUnitField   (REPORT_ROW6_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          WP.Unit, WD_UNIT, HT_REPORT_BOX, widget_locked );
         endlayout();
            
        endlayout();  //End of Grid Layout

        // Spacing between columns
        CreatePromptField (REPORT_SPACE_1,    CL_PT_BLUE, OFF,"", FT_STANDARD_SIZE, 2, HT_IO_HEADER, 0, widget_locked);    
          
        // Second Column of REPORT page  

          beginlayout(LAYOUT_TYPE_GRID, 0,1); // 
            beginrow(); // First row with three colons 
              CreatePromptField (REPORT_ROW8_ID,    CL_PT_BLUE, OFF, lsub(TX_IDUNDERREJECT), FT_STANDARD_SIZE, WD_REPORT_COLUMN3, HT_REPORT_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW8_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER,WD_REPORT_COLUMN4, HT_REPORT_BOX, widget_locked);
              CreateOutputDataField (REPORT_ROW8_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R,WD_REPORT_COLUMN5, HT_REPORT_BOX, widget_locked);
            endrow();
            
            beginrow(); // Second row with three colons
              CreatePromptField (REPORT_ROW9_ID,    CL_PT_BLUE, OFF, lsub(TX_IDUNDERACCEPT), FT_STANDARD_SIZE, WD_REPORT_COLUMN3, HT_REPORT_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW9_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_REPORT_COLUMN4, HT_REPORT_BOX, widget_locked);
              CreateOutputDataField (REPORT_ROW9_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R,WD_REPORT_COLUMN5, HT_REPORT_BOX, widget_locked);
            endrow();
      
            beginrow(); // Third row with three colons
              CreatePromptField (REPORT_ROW10_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_UNITS_ACCEPTED), FT_STANDARD_SIZE, WD_REPORT_COLUMN3, HT_REPORT_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW10_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_REPORT_COLUMN4, HT_REPORT_BOX, widget_locked);
              CreateOutputDataField (REPORT_ROW10_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_REPORT_COLUMN5, HT_REPORT_BOX, widget_locked);
            endrow();
            
            beginrow(); // Fourth row with three colons
              CreatePromptField (REPORT_ROW11_ID,    CL_PT_BLUE, OFF, lsub(TX_IDOVERACCEPT), FT_STANDARD_SIZE, WD_REPORT_COLUMN3, HT_REPORT_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW11_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_REPORT_COLUMN4, HT_REPORT_BOX, widget_locked);
              CreateOutputDataField (REPORT_ROW11_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_REPORT_COLUMN5, HT_REPORT_BOX, widget_locked);
            endrow();
            
            beginrow(); // Fifth row with three colons
              CreatePromptField (REPORT_ROW12_ID,    CL_PT_BLUE, OFF, lsub(TX_IDOVERREJECT), FT_STANDARD_SIZE, WD_REPORT_COLUMN3, HT_REPORT_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW12_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_REPORT_COLUMN4, HT_REPORT_BOX, widget_locked);
              CreateOutputDataField (REPORT_ROW12_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R,WD_REPORT_COLUMN5, HT_REPORT_BOX, widget_locked);
            endrow();
            
            beginrow(); // sixth row with three colons
              CreatePromptField (REPORT_ROW13_ID,    CL_PT_BLUE, OFF, lsub(TX_IDINVALIDWEIGHMENT), FT_STANDARD_SIZE,WD_REPORT_COLUMN3, HT_REPORT_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (REPORT_ROW13_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_REPORT_COLUMN4, HT_REPORT_BOX, widget_locked);
              CreateOutputDataField (REPORT_ROW13_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R,WD_REPORT_COLUMN5, HT_REPORT_BOX, widget_locked);
            endrow();

          endlayout(); // End of Grid Layout
          
        endlayout(); // End of HBOX #7  // 
       
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1 

   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
    DrawNavButtons (SCREEN_REPORT, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_WEIGHING_DATA, BTN_NIL_BLUE, BTN_REPORTRESET);  

  endlayout();  // End of VBOX #1
  enddraw();

}




/* *********************************************************************** */
/*                                                                         */
/*       Refresh REPORT screen display                                     */
/*                                                                         */
/* *********************************************************************** */

void RefreshReportScreen (int Scrn_No) 
{
  begindraw();

    switch ( Scrn_No )
    {
      case SCREEN_REPORT:
      
          // First Column                                
                
               widget_text         (REPORT_ROW7_INPUT,  concat("(",lsub(WP.Name),")"));
                                                
                // First Row Info 
                widget_text       (REPORT_ROW1_INPUT, WP.NominalWeight);
                widget_text       (REPORT_ROW1_UNIT,  WP.Unit);
          
                // 2nd Row Info 
                widget_text       (REPORT_ROW2_INPUT, WP.TolTotalCnt);
                                                 
                // Third Row Info 
                widget_text       (REPORT_ROW3_INPUT, trim(adj(WP.TotalWeight,14,2)));
                widget_text       (REPORT_ROW3_UNIT,  WP.Unit);                                
                                                                 
                // Fifth Row Info 
                widget_text       (REPORT_ROW5_INPUT, ProdTotalUnitsLT);
                                                
                // Sixth Row Info 
                ProdTotalWeightLT = ProdTotalWeightLTkg / WP_UnitToKG;
                widget_text       (REPORT_ROW6_INPUT, trim(adj(ProdTotalWeightLT,14,2)));
                widget_text       (REPORT_ROW6_UNIT,  WP.Unit);
                
          // Second Column                               
                                                
                // First Row Info  
                widget_text       (REPORT_ROW8_INPUT, trim(WP.TolUnderRejCnt));
                widget_text       (REPORT_ROW8_INPUT2, concat(WP.TolUnderRejPct,"%"));
          
                // 2nd Row Info 
                widget_text       (REPORT_ROW9_INPUT, trim(WP.TolUnderAccCnt));
                widget_text       (REPORT_ROW9_INPUT2, concat(WP.TolUnderAccPct,"%"));
                                                 
                // Third Row Info 
                widget_text       (REPORT_ROW10_INPUT, trim(WP.TolGoodCnt));
                widget_text       (REPORT_ROW10_INPUT2, concat(WP.TolGoodPct,"%"));
                                                
                // Fourth Row Info 
                widget_text       (REPORT_ROW11_INPUT, trim(WP.TolOverAccCnt));
                widget_text       (REPORT_ROW11_INPUT2, concat(WP.TolOverAccPct,"%"));
                                                 
                // Fifth Row Info 
                widget_text       (REPORT_ROW12_INPUT, trim(WP.TolOverRejCnt));
                widget_text       (REPORT_ROW12_INPUT2, concat(WP.TolOverRejPct,"%"));
                                                
                // Sixth Row Info 
                widget_text       (REPORT_ROW13_INPUT, trim(WP.TolInvalidCnt));
                widget_text       (REPORT_ROW13_INPUT2, concat(WP.TolInvalidPct,"%"));
                
                // Reset Lifetime production data button display
                if (CurrentLevel == Level_PT) widget_image (NAV_FCT_BUTTON_9, BTN_RESETLIFETIME);
                else widget_image (NAV_FCT_BUTTON_9, BTN_NIL_BLUE);
          
          break;

      case SCREEN_BATCH:
          // Header
               
               widget_text         (BATCH_ROW1_INPUT,  concat("(",lsub(WP.Name),")"));
                                                
                // First Row Info 
                widget_text       (BATCH_NAME_INPUT, Batch.Name);
          
                // 2nd Row Info
                widget_text       (BATCH_DETAILS_INPUT, Batch.Details); 
                
                                                 
                // Third Row Info
                widget_text       (BATCH_PRESET_INPUT, Batch.Preset);  
                 
                 // Fourth Row Info 
                widget_text       (BATCH_ROW4_INPUT, Batch.NominalWeight);
                widget_text       (BATCH_ROW4_UNIT,  WP.Unit);
                                               
                // 5 Row Info 
                widget_text       (BATCH_ROW5_INPUT, Batch.Avg);
                widget_text       (BATCH_ROW5_UNIT,  WP.Unit);
                                                 
                // 6 Row Info 
                widget_text       (BATCH_ROW6_INPUT, Batch.StdDev);
                widget_text       (BATCH_ROW6_UNIT,  WP.Unit);
                                                
                // 7 Row Info 
                widget_text       (BATCH_ROW7_INPUT, trim(adj(Batch_TotalWeight,14,2)));
                widget_text       (BATCH_ROW7_UNIT,  WP.Unit);
                
                // Seventh Row Info 
                
                
                
          // Second Column                               
                                                
                // First Row Info  
                widget_text       (BATCH_ROW8_INPUT, trim(Batch.TolUnderRejCnt));
                widget_text       (BATCH_ROW8_INPUT2, concat(Batch.TolUnderRejPct,"%"));
          
                // 2nd Row Info 
                widget_text       (BATCH_ROW9_INPUT, trim(Batch.TolUnderAccCnt));
                widget_text       (BATCH_ROW9_INPUT2, concat(Batch.TolUnderAccPct,"%"));
                                                 
                // Third Row Info 
                widget_text       (BATCH_ROW10_INPUT, trim(Batch.TolGoodCnt));
                widget_text       (BATCH_ROW10_INPUT2, concat(Batch.TolGoodPct,"%"));
                                                
                // Fourth Row Info 
                widget_text       (BATCH_ROW11_INPUT, trim(Batch.TolOverAccCnt));
                widget_text       (BATCH_ROW11_INPUT2, concat(Batch.TolOverAccPct,"%"));
                                                 
                // Fifth Row Info 
                widget_text       (BATCH_ROW12_INPUT, trim(Batch.TolOverRejCnt));
                widget_text       (BATCH_ROW12_INPUT2, concat(Batch.TolOverRejPct,"%"));
                                                
                // Sixth Row Info 
                widget_text       (BATCH_ROW13_INPUT, trim(Batch.TolInvalidCnt));
                widget_text       (BATCH_ROW13_INPUT2, concat(Batch.TolInvalidPct,"%"));
                
                // Seventh Row Info
                widget_text       (BATCH_ROW14_INPUT, trim(Batch.TolTotalCnt));
                widget_text       (BATCH_ROW14_INPUT2, concat(Batch.TolTotalPct,"%"));
                
     
          break;

    }
  enddraw();
}  

/* *********************************************** */
/*   Create Input field                            */                                                            
/* *********************************************** */

void CreateInputFieldBatch (int id, int font_size, int font_face, int format, int len, int decs, int width, int height, string text )
{
  createwidget (id, WIDGET_TYPE_TEXT_INPUT);
    widget_style           (id,  WPMANAGEBOX_STYLE); 
    widget_size_policy     (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED); 
    widget_fontsize        (id,  font_size); 
//    widget_fontface      (id,  font_face);
    widget_foreground      (id,  CL_PT_BLUE);
    widget_format          (id,  format, len, decs);
    widget_label           (id,  text); 
    widget_text            (id,  "" );
    widget_dimensions      (id,  width, height);
    widget_text_alignment  (id,  WIDGET_TEXT_ALIGN_CENTER );
    widget_maximum_size    (id,  width, height);
    widget_content_margins (id,  0,0,0,0); 
}


/* *********************************************************************** */
/*                                                                         */
/*   Create BATCH Report page                                              */
/*                                                                         */
/* *********************************************************************** */

void CreateBatchReportPage(void) 
{
  begindraw();
  createpage(PAGE_BATCH);  
  page_background (PAGE_BATCH, BackgroundColor);

  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // 
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // 

        // ##### Header #####
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
          CreatePTLogoHeader();
          CreateHeader (BATCH_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_BATCH_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);
        
          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #6   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #6
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // End of HBOX #5 //End of Header

        beginlayout(LAYOUT_TYPE_HBOX, 0,3); // HBOX #8
          CreatePromptField (BATCH_ROW1_ID,    CL_PT_BLUE, ON, concat(lsub (TX_BATCH_CURRENT_PROD),":"), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION1, HT_BATCH_DESCRIPTION, Left_Margin, widget_locked);
          CreatePromptField (BATCH_ROW1_INPUT,    CL_PT_BLUE, OFF, concat("(",lsub(WP.Name),")"), FT_STANDARD_SIZE, WD_REPORT_DESCRIPTION2, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
          widget_text_alignment (BATCH_ROW1_INPUT,  WIDGET_TEXT_ALIGN_CENTER );
          CreatePromptField (BATCH_ROW2_ID,    CL_PT_BLUE, ON, "", FT_STANDARD_SIZE, WD_BATCH_DESCR_SPACE, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
        endlayout(); //HBOX #8

       // ##### Left display with weighing in-/outputs without infoline #####
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #7
       
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // First row with three colons 
              CreatePromptField (BATCH_NAME_ID,    CL_PT_BLUE, OFF, lsub(TX_BATCH_NAME), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputFieldBatch  (BATCH_NAME_INPUT, FT_STANDARD_SIZE, FT_RTC, INPUT_FORMAT_STRING, 24, 0, WD_BATCH_BOX, HT_BATCH_BOX, lsub(TX_BATCH_NAME) );
              CreateUnitField   (BATCH_NAME_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          "", WD_BATCH_UNIT, HT_BATCH_BOX, widget_locked );            
            endrow();
            
            beginrow(); // Second row with three colons
              CreatePromptField (BATCH_DETAILS_ID,    CL_PT_BLUE, OFF, lsub(TX_BATCH_DETAILS), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, Left_Margin, widget_locked); 
              CreateInputFieldBatch  (BATCH_DETAILS_INPUT, FT_STANDARD_SIZE, FT_RTC, INPUT_FORMAT_STRING, 48, 0, WD_BATCH_BOX, HT_BATCH_BOX, "Details" );
              CreateUnitField   (BATCH_DETAILS_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          "", WD_BATCH_UNIT, HT_BATCH_BOX, widget_locked );
            endrow();
            
            beginrow(); // third row with three colons
              CreatePromptField (BATCH_PRESET_ID,    CL_PT_BLUE, OFF, lsub(TX_BATCH_PRESET), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputFieldBatch  (BATCH_PRESET_INPUT, FT_STANDARD_SIZE, FT_RTC, INPUT_FORMAT_DECIMAL, 6, 0, WD_BATCH_BOX, HT_BATCH_BOX, lsub(TX_BATCH_PRESET) );
              CreateUnitField   (BATCH_PRESET_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          "", WD_BATCH_UNIT, HT_BATCH_BOX, widget_locked );   
            endrow();
            
            beginrow(); // Fourth row with three colons
              CreatePromptField (BATCH_ROW4_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_NOMINAL_WEIGHT), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW4_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX, HT_BATCH_BOX, widget_locked);
              CreateUnitField   (BATCH_ROW4_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          WP.Unit, WD_UNIT, HT_BATCH_BOX, widget_locked);
            endrow();
            
            beginrow(); // Fifth row with three colons
              CreatePromptField (BATCH_ROW5_ID,    CL_PT_BLUE, OFF, lsub(TX_AVERAGE), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW5_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX, HT_BATCH_BOX, widget_locked);
              CreateUnitField   (BATCH_ROW5_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          WP.Unit, WD_UNIT, HT_BATCH_BOX, widget_locked);
            endrow();
            
            beginrow(); // sixth row with three colons
              CreatePromptField (BATCH_ROW6_ID,    CL_PT_BLUE, OFF, lsub(TX_STD_DEV), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW6_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX, HT_BATCH_BOX, widget_locked);
              CreateUnitField   (BATCH_ROW6_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          WP.Unit, WD_UNIT, HT_BATCH_BOX, widget_locked);
            endrow(); 
            
            beginrow(); // seventh row with three colons
              CreatePromptField (BATCH_ROW7_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_TOTAL_WEIGHT), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW7_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX, HT_BATCH_BOX, widget_locked);
              CreateUnitField   (BATCH_ROW7_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,          WP.Unit, WD_UNIT, HT_BATCH_BOX, widget_locked );
            endrow();
            
          endlayout();  //End of Grid Layout
          
          
        // Second Column of REPORT page  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            
            beginrow(); // First row with three colons 
              CreatePromptField (BATCH_ROW8_ID,    CL_PT_BLUE, OFF, lsub(TX_IDUNDERREJECT), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW8_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_BATCH_BOX3, HT_BATCH_BOX, widget_locked);
              CreateOutputDataField (BATCH_ROW8_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX2, HT_BATCH_BOX, widget_locked);
            endrow();
            
            beginrow(); // Second row with three colons
              CreatePromptField (BATCH_ROW9_ID,    CL_PT_BLUE, OFF, lsub(TX_IDUNDERACCEPT), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW9_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_BATCH_BOX3, HT_BATCH_BOX, widget_locked);
              CreateOutputDataField (BATCH_ROW9_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX2, HT_BATCH_BOX, widget_locked);
            endrow();
      
            beginrow(); // Third row with three colons
              CreatePromptField (BATCH_ROW10_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_UNITS_ACCEPTED), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW10_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_BATCH_BOX3, HT_BATCH_BOX, widget_locked);
              CreateOutputDataField (BATCH_ROW10_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX2, HT_BATCH_BOX, widget_locked);
            endrow();
            
            beginrow(); // Fourth row with three colons
              CreatePromptField (BATCH_ROW11_ID,    CL_PT_BLUE, OFF, lsub(TX_IDOVERACCEPT), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW11_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_BATCH_BOX3, HT_BATCH_BOX, widget_locked);
              CreateOutputDataField (BATCH_ROW11_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX2, HT_BATCH_BOX, widget_locked);
            endrow();
            
            beginrow(); // Fifth row with three colons
              CreatePromptField (BATCH_ROW12_ID,    CL_PT_BLUE, OFF, lsub(TX_IDOVERREJECT), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW12_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_BATCH_BOX3, HT_BATCH_BOX, widget_locked);
              CreateOutputDataField (BATCH_ROW12_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX2, HT_BATCH_BOX, widget_locked);
            endrow();
            
            beginrow(); // sixth row with three colons
              CreatePromptField (BATCH_ROW13_ID,    CL_PT_BLUE, OFF, lsub(TX_IDINVALIDWEIGHMENT), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW13_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_BATCH_BOX3, HT_BATCH_BOX, widget_locked);
              CreateOutputDataField (BATCH_ROW13_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX2, HT_BATCH_BOX, widget_locked);
            endrow();
            
            beginrow(); // seventh row with three colons
              CreatePromptField (BATCH_ROW14_ID,    CL_PT_BLUE, OFF, lsub(TX_ID_UNITS_DONE), FT_STANDARD_SIZE, WD_BATCH_DESCRIPTION, HT_BATCH_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputDataField (BATCH_ROW14_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_BATCH_BOX3, HT_BATCH_BOX, widget_locked);
              CreateOutputDataField (BATCH_ROW14_INPUT2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_R, WD_BATCH_BOX2, HT_BATCH_BOX, widget_locked);
            endrow();            
                   
          endlayout(); // End of Grid Layout
          
        endlayout(); // End of HBOX #7  // End of left display in-/outputs without infoline HBOX
        
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   endlayout();  // End layout of HBOX #2
   
endlayout(); //Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);

  
    CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
    DrawNavButtons (SCREEN_BATCH, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_WEIGHING_DATA, BTN_NIL_BLUE, BTN_REPORTRESET);  
//   endlayout(); // End layout of VBOX #8
    
  endlayout();  // End of VBOX #1
  enddraw();

}

/* *********************************************************************** */
/*                                                                         */
/*   Create Registration page                                              */
/*                                                                         */
/* *********************************************************************** */

void CreateRegistrationPage(void) 
{
  
  begindraw();
  createpage(PAGE_REGISTRATION);  
  page_background (PAGE_REGISTRATION, "white");
  
  
    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // Split left screen in in-/outputs and infoline

       beginlayout(LAYOUT_TYPE_HBOX, 0);  // HBOX #4   

        // ##### Search REPORT button #####
        beginlayout(LAYOUT_TYPE_HBOX, MIN_EDGE_DISTANCE, FCT_BUTTON_DISTANCE); // HBOX #5
          CreatePTLogoHeader();
          CreateHeader (REPORT_SEARCH_ID, 400, 50, "", align_hcenter, concat (space(3), lsub("Registration Page"), space(1)), FT_MEDIUM_SIZE, widget_unlocked);
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
          CreateHeader (LOGO_BOX2, 155, 50, BTN_LOGO_iQ, WIDGET_TEXT_ALIGN_VCENTER_R, "" , FT_MEDIUM_SIZE, widget_unlocked);
          widget_image          (LOGO_BOX2,   BTN_LOGO_iQ); 
        endlayout(); // End of HBOX #5 //End of search REPORT button


      endlayout(); //End layout of HBOX #4


       // ##### Left display with weighing in-/outputs without infoline #####
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #7
              
          //  First column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0); 
            
            beginrow();
              CreatePromptField (REGISTRATION_ROW0_ID,    CL_PT_BLUE, OFF, lsub(""), FT_STANDARD_SIZE, 50, 32, 195,widget_unlocked);
              widget_text (REGISTRATION_ROW0_ID,"");
            endrow();
            
            beginrow(); // First row with three colons 
              CreatePromptField (REGISTRATION_ROW1_ID,    CL_PT_BLUE, OFF, lsub("Mac Address:"), FT_STANDARD_SIZE, 50, 32, 195,widget_unlocked);
              CreateOutputDataField (REGISTRATION_ROW1_INPUT, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_VCENTER_L, WD_PTBOX_SIZE, HT_PTBOX_SIZE, widget_unlocked);
            endrow();
            
            beginrow(); // Second row with three colons
              CreatePromptField (REGISTRATION_ROW2_ID,    CL_PT_BLUE, OFF, lsub("Registration Key:"), FT_STANDARD_SIZE, 50, 32, 195, widget_unlocked);
              CreateInputField  (REGISTRATION_ROW2_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_STRING, 14, 0,OFF, lsub("Registration Key:"),200,PT_6BOX_SIZE, widget_locked );
              
            endrow();
            
            beginrow();
            CreateSpacingField (REGISTRATION_SPACE_1, CL_PT_BLUE, FT_STANDARD_SIZE, space(6)); 
            CreateNavigButtons (1, REGISTRATION_BUTTON_1, ON);                                     
            DrawGenericButtons (SCREEN_REGISTRATION, ON, 1, REGISTRATION_BUTTON_1, BTN_CHECK, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, 
                                                                    BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE );
            
            endrow();
            
          endlayout();  //End of Grid Layout
          
          
        
        endlayout(); // End of HBOX #7  // End of left display in-/outputs without infoline HBOX
       
       createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   endlayout();  // End layout of HBOX #2
   


   
  enddraw();

}

                                             
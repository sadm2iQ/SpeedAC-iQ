


/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateSearchRecipeButton
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Creation of the search recipe button  
--                    : 
--  Value Parameters  :
--  Variable Params   : id = entity enum number ex: RECIPE_SEARCH_ID
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateSearchRecipeButton(int id)
{
  createwidget (id, WIDGET_TYPE_BUTTON);
    widget_dimensions     (id, 598, 48);      
    widget_fontsize       (id, FT_RECIPE_SIZE); 
    widget_size_policy    (id, SIZE_POLICY_FIXED, SIZE_POLICY_FIXED); 
    widget_foreground     (id, CL_PT_WHITE );
    widget_background     (id, CL_PT_BLUE );
    widget_text_alignment (id, WIDGET_TEXT_ALIGN_HCENTER );
    widget_maximum_size   (id,  598, 49);
}






/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateRecipePage1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Creation of Recipe page #1   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateRecipePage1(void) 
{
  begindraw();
  createpage(PAGE_RECIPE_1);  
  page_background (PAGE_RECIPE_1, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3              

         // Search recipe button
         beginlayout(LAYOUT_TYPE_HBOX, 0); // search recipe
           CreateSearchRecipeButton (RECIPE_SEARCH_ID);     

         beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
         //Fault and Mode display
         CreateModeFltDisplay();
         endlayout(); // End of HBOX #5
        setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
       endlayout(); // End of search recipe

createwidget (0, WIDGET_TYPE_STRETCH);

       // Layout of both recipe columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // Grid Layout #1
            beginrow(); // First row with three columns 
              CreatePromptField (RECIPE_ROW1_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPNOMINALWEIGHT), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked ); 
              CreateInputField  (RECIPE_ROW1_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 7, 3, OFF, lsub(TX_WPNOMINALWEIGHT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW1_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Second row with three columns
              CreatePromptField (RECIPE_ROW2_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPOVERFILL), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW2_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPOVERFILL), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW2_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Thirth row with three columns
              CreatePromptField (RECIPE_ROW3_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPCUTOFFWEIGHT), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW3_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPCUTOFFWEIGHT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW3_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();   
                     
            beginrow(); // Fourth row with three columns
              CreatePromptField (RECIPE_ROW4_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPDRIBBLEFEEDWEIGHT), FT_STANDARD_SIZE, WD_WP_DESCRIPTION,HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW4_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPDRIBBLEFEEDWEIGHT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW4_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();

            beginrow(); // Fifth row with three columns
              CreatePromptField (RECIPE_ROW5_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPDRIBBLEFEEDTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW5_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPDRIBBLEFEEDTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW5_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();

            beginrow(); // Sixth row with three columns
              CreatePromptField (RECIPE_ROW6_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPBULKFEEDTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW6_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPBULKFEEDTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW6_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
                   
          endlayout();  //End of Grid Layout #1


        // Spacing between columns
          CreatePromptField (RECIPE_SPACE1,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_WP_SPACE, HT_WP_DESCRIPTION, No_Margin, widget_locked);
        
        // Layout of second column of recipe page on the right
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // Grid Layout #2
            beginrow(); // First row with three columns 
              CreatePromptField (RECIPE_ROW7_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPUNDERWEIGHT) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW7_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPUNDERWEIGHT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW7_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow();     
            
            beginrow(); // Second row with three columns  
              CreatePromptField (RECIPE_ROW8_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPOVERWEIGHT) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW8_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPOVERWEIGHT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW8_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();    
            
            beginrow(); // Third row with three columns 
              CreatePromptField (RECIPE_ROW9_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPINTERMFEEDWEIGHT) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW9_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPINTERMFEEDWEIGHT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW9_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();                              
          
            beginrow(); // Fourth row with three columns  
              CreatePromptField (RECIPE_ROW10_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPDISCHARGEWEIGHT) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW10_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 7, 3, OFF, lsub(TX_WPDISCHARGEWEIGHT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW10_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             WP.Unit, WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();            

            beginrow(); // Fifth row with three columns 
              CreatePromptField (RECIPE_ROW11_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPDISCHARGETIME) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW11_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPDISCHARGETIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW11_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();  

            beginrow(); // Sixth row with three columns
              CreatePromptField (RECIPE_ROW12_ID,     CL_PT_BLUE, OFF,                      lsub(TX_WPFALLINGTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_BOX, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW12_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPFALLINGTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW12_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow(); 
                    
          endlayout(); // End of Grid Layout #2
          
       
        endlayout(); // End of HBOX #6  
           
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_RECIPE1, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_COPY, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateRecipePage2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Creation of Recipe page #2   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateRecipePage2(void) 
{
  begindraw();
  createpage(PAGE_RECIPE_2);  
  page_background (PAGE_RECIPE_2, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); //Header   
         // Search recipe button
         beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
           CreateSearchRecipeButton (RECIPE_SEARCH_ID);
           endlayout(); // End of HBOX #5 //End of search recipe button

          //Fault and Mode display
          CreateModeFltDisplay();
        setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
       endlayout();  // End of Header


       //  Layout of both recipe columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            beginrow(); // First row with three columns 
              CreatePromptField (RECIPE_ROW13_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPMINFEEDING), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked );
              CreateInputField  (RECIPE_ROW13_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 2, OFF, lsub(TX_WPMINFEEDING), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW13_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Second row with three columns
              CreatePromptField (RECIPE_ROW14_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPMAXFEEDING), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW14_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 2, OFF, lsub(TX_WPMAXFEEDING), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW14_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Thirth row with three columns
              CreatePromptField (RECIPE_ROW15_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPREGMINFEEDING), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW15_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 2, OFF, lsub(TX_WPREGMINFEEDING), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW15_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();   
                     
            beginrow(); // Fourth row with three columns
              CreatePromptField (RECIPE_ROW16_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPREGMAXFEEDING), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW16_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 2, OFF, lsub(TX_WPREGMAXFEEDING), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW16_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();

            beginrow(); // Fifth row with three columns
              CreatePromptField   (RECIPE_ROW17_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPSTREAMREG), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW17_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD, lsub(TX_WPSTREAMREGLOW), lsub(TX_WPSTREAMREGHIGH), concat(lsub(TX_WPSTREAMREGAUTO),"-",lsub(TX_RAISEATEND)), concat(lsub(TX_WPSTREAMREGAUTO),"-",lsub(TX_RAISEATRUN)), "", WD_WP_BOX, HT_WP_BOX, widget_locked);
              CreateUnitField     (RECIPE_ROW17_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();

            beginrow(); // Sixth row with three columns
              CreatePromptField (RECIPE_ROW18_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPACTUATORPOS), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW18_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 2, OFF, lsub(TX_WPACTUATORPOS), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW18_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreatePromptField (RECIPE_SPACE1,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_WP_SPACE, HT_WP_DESCRIPTION, No_Margin, widget_locked);
        
        // Layout of second column of recipe page on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // First row with three columns 
              CreatePromptField (RECIPE_ROW19_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPWEIGHMENTSPERUNIT) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW19_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 0, OFF, lsub(TX_WPWEIGHMENTSPERUNIT), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW19_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             "" , WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow();     
            
            beginrow(); // Second row with three columns  
              CreatePromptField (RECIPE_ROW20_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPFEEDDELAYTIME) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW20_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPFEEDDELAYTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW20_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();    
            
            beginrow(); // Third row with three columns 
              CreatePromptField   (RECIPE_ROW21_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPVIBRATORYDISCHDOOR), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW21_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_OFF), lsub(TX_ON), "", "", "", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField     (RECIPE_ROW21_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "" , WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow();                              
          
            beginrow(); // Fourth row with three columns  
              CreatePromptField   (RECIPE_ROW22_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPZEROINGOPEN), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW22_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_WPDOOR_CLOSED), lsub(TX_WPDOOR_OPEN), "",  "", "", WD_WP_BOX,  HT_WP_BOX, widget_locked);
              CreateUnitField     (RECIPE_ROW22_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();            

            beginrow(); // Fifth row with three columns 
              CreatePromptField   (RECIPE_ROW23_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPSLOWCYCLEEND), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW23_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_WPHOLD_CYCLE), lsub(TX_WPEND_CYCLE),lsub(TX_WPDRIBBLEEND),  "", "", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField     (RECIPE_ROW23_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();  

            beginrow(); // Sixth row with three columns
              CreatePromptField   (RECIPE_ROW24_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPENABLEDSCALE), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW24_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        "#1","#2","#1 & #2",  "", "", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField     (RECIPE_ROW24_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                           "" , WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow(); 
                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
       
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_RECIPE2, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateRecipePage3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Creation of Recipe page #3   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateRecipePage3(void) 
{
  begindraw();
  createpage(PAGE_RECIPE_3);  
  page_background (PAGE_RECIPE_3, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); //Header  
         // Search recipe button
         beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
           CreateSearchRecipeButton (RECIPE_SEARCH_ID);
           endlayout(); // End of HBOX #5 //End of search recipe button

          //Fault and Mode display
          CreateModeFltDisplay();
        setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
       endlayout();  // End of Header


       // Layout of both recipe columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            beginrow(); // First row (Operator) with three columns 
              CreatePromptField (RECIPE_ROW25_ID,    CL_PT_BLUE, OFF,                              lsub(TX_WPTOPUPOFFTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked );
              CreateInputField  (RECIPE_ROW25_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPTOPUPOFFTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW25_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked);
            endrow();
            
            beginrow(); // Second row (Article no) with three columns
              CreatePromptField (RECIPE_ROW26_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPTOPUPONTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW26_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPTOPUPONTIME) , WD_WP_BOX, HT_WP_BOX, widget_locked);
              CreateUnitField   (RECIPE_ROW26_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Thirth row (Article no) with three columns
              CreatePromptField (RECIPE_ROW27_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPKNOCKINGTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW27_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPKNOCKINGTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW27_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();   
                     
            beginrow(); // Fourth row (Article no) with three columns
              CreatePromptField (RECIPE_ROW28_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPBAGINFLATIONTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW28_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPBAGINFLATIONTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW28_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // 5th row (Article no) with three columns
              CreatePromptField (RECIPE_ROW29_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPKICKERCENTERTIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW29_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPKICKERCENTERTIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW29_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // 6th row (Article no) with three columns
              CreatePromptField (RECIPE_ROW30_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPKICKERACTIVATETIME), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW30_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPKICKERACTIVATETIME), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW30_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();

            
                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreatePromptField (RECIPE_SPACE1,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_WP_SPACE, HT_WP_DESCRIPTION, No_Margin, widget_locked); 
        
        // LAyout of second column of recipe page on the right  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // First row (Operator) with three columns 
              CreatePromptField     (RECIPE_ROW31_ID,    CL_PT_BLUE, OFF,                   lsub(TX_WPUNITSELECTION) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField   (RECIPE_ROW31_SELECT,FT_STANDARD_SIZE, FT_RTC_BOLD,       lsub(TX_WPUNITKG), lsub(TX_WPUNITLB), "", "", "", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField       (RECIPE_ROW31_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                           "", WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow();     
            
            beginrow(); // 2nd row (Article no) with three columns
              CreatePromptField   (RECIPE_ROW32_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPFEEDALGOTYPE), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW32_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_WPALGOSTD),  lsub(TX_WPALGOSMARTIQ), lsub(TX_WPALGOFLASHIQ),lsub(TX_WPALGOSIMIQ),"", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField     (RECIPE_ROW32_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT_LEFT, HT_WP_BOX, widget_locked ); 
            endrow();

            beginrow(); // 3rd row (Article no) with three columns
              CreatePromptField     (RECIPE_ROW33_ID,    CL_PT_BLUE, OFF,                   lsub(TX_WPSLOWFILLFACTOR) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField   (RECIPE_ROW33_SELECT,FT_STANDARD_SIZE, FT_RTC_BOLD,       lsub(TX_WPSFF0), lsub(TX_WPSFF1), lsub(TX_WPSFF2),  lsub(TX_WPSFF3), lsub(TX_WPSFF4), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField       (RECIPE_ROW33_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "", WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Fourth row (Operator) with three columns  
              CreatePromptField   (RECIPE_ROW34_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPTUNEIQFEED), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW34_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_OFF), lsub(TX_ON), "", "", "", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField     (RECIPE_ROW34_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "" , WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow();            

            beginrow(); // Fifth row (Operator) with three columns 
              CreatePromptField   (RECIPE_ROW35_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPBULKMODE), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW35_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_BYWEIGHT), lsub(TX_BYTIME), "", "", "", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField     (RECIPE_ROW35_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "" , WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow();  

            beginrow(); // Sixth row with three columns
              CreatePromptField (RECIPE_ROW36_ID,    CL_PT_BLUE, OFF,                       lsub(TX_WPCATCHGATEDELAY), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW36_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 2, OFF, lsub(TX_WPCATCHGATEDELAY), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW36_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow(); 
                   
          endlayout(); // End of Grid Layout
                
        
        endlayout(); // End of HBOX #6   
        
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_RECIPE3, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateRecipePage4
--  Created by        : Steve Santerre
--  Last modified on  : 2017/03
--  
--  Purpose           : Creation of Recipe page #4   
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateRecipePage4(void) 
{
  begindraw();
  createpage(PAGE_RECIPE_4);  
  page_background (PAGE_RECIPE_4, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); //Header        
         // Search recipe button
         beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
          CreateSearchRecipeButton (RECIPE_SEARCH_ID);
          endlayout(); // End of HBOX #5 //End of search recipe button

          //Fault and Mode display
          CreateModeFltDisplay();
        setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
       endlayout();  // End of Header


       // Layout of both recipe columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            beginrow(); // First row (Operator) with three columns 
              CreatePromptField     (RECIPE_ROW37_ID,    CL_PT_BLUE, OFF,                   lsub(TX_WPT1) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField      (RECIPE_ROW37_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 3, OFF, lsub(TX_WPT1), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField       (RECIPE_ROW37_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                        lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Second row (Article no) with three columns
              CreatePromptField     (RECIPE_ROW38_ID,    CL_PT_BLUE, OFF,                   lsub(TX_WPT2) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField      (RECIPE_ROW38_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 3, OFF, lsub(TX_WPT2), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField       (RECIPE_ROW38_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
            
            beginrow(); // Thirth row (Article no) with three columns
              CreatePromptField (RECIPE_ROW39_ID,    CL_PT_BLUE, OFF,                       lsub(TX_FLEXCOUNTER), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateInputField  (RECIPE_ROW39_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 6, 0, OFF, lsub(TX_FLEXCOUNTER), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW39_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             "#", WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();   
                     
            beginrow(); // Fourth row (Article no) with three columns
              CreatePromptField   (RECIPE_ROW40_ID,     CL_PT_BLUE, OFF,                    lsub(TX_WPDISCHDOORMODE), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateComboBoxField (RECIPE_ROW40_SELECT, FT_STANDARD_SIZE, FT_RTC_BOLD,        lsub(TX_DDSMALL), lsub(TX_DDMEDIUM), lsub(TX_DDLARGE), "", "", WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField     (RECIPE_ROW40_UNIT,   FT_RTC_BOLD, FT_STANDARD_SIZE,                          "" , WD_UNIT_LEFT, HT_WP_BOX, widget_locked);
            endrow();

            beginrow(); // Fifth row (Article no) with three columns
              CreatePromptField   (RECIPE_ROW41_ID,     CL_PT_BLUE, OFF,                  "", FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputTextField (RECIPE_ROW41_INPUT,                                      "", WD_WP_BOX, HT_WP_BOX, widget_locked);
              CreateUnitField       (RECIPE_ROW41_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         "", WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();

            beginrow(); // Sixth row (Article no) with three columns
              CreatePromptField     (RECIPE_ROW42_ID,     CL_PT_BLUE, OFF,                  "", FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked);
              CreateOutputTextField (RECIPE_ROW42_INPUT,                                      "", WD_WP_BOX, HT_WP_BOX, widget_locked);
              CreateUnitField       (RECIPE_ROW42_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         "", WD_UNIT, HT_WP_BOX, widget_locked );
            endrow();
                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreatePromptField (RECIPE_SPACE1,    CL_PT_BLUE, OFF,                       "", FT_STANDARD_SIZE, WD_WP_SPACE, HT_WP_DESCRIPTION, No_Margin, widget_locked);
        
        // LAyout of second column of recipe page on the right  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // First row (Operator) with three columns 
              CreatePromptField     (RECIPE_ROW43_ID,    CL_PT_BLUE, OFF,                   lsub(TX_WPSP1) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField      (RECIPE_ROW43_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPSP1), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField       (RECIPE_ROW43_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         WP.Unit, WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();     
            
            beginrow(); // Second row (Operator) with three columns  
              CreatePromptField     (RECIPE_ROW44_ID,    CL_PT_BLUE, OFF,                   lsub(TX_WPSP2) , FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateInputField      (RECIPE_ROW44_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 8, 3, OFF, lsub(TX_WPSP2), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField       (RECIPE_ROW44_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         WP.Unit, WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();    
            
            beginrow(); // Third row with three columns  
              CreatePromptField (RECIPE_ROW45_ID,    CL_PT_BLUE, false,                              lsub(TX_WPVIBRATIONAMPLITUDE), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked );
              CreateInputField  (RECIPE_ROW45_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 4, 2, false, lsub(TX_WPVIBRATIONAMPLITUDE), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW45_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_PERC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked);
            endrow();    
            
            beginrow(); //  Fourth row with three columns 
              CreatePromptField (RECIPE_ROW46_ID,    CL_PT_BLUE, false,                              lsub(TX_WPVIBRATIONPERIOD), FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, Left_Margin, widget_locked );
              CreateInputField  (RECIPE_ROW46_INPUT, FT_STANDARD_SIZE, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 4, 2, false, lsub(TX_WPVIBRATIONPERIOD), WD_WP_BOX, HT_WP_BOX, widget_locked );
              CreateUnitField   (RECIPE_ROW46_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                             lsub(TX_SEC_UNIT), WD_UNIT, HT_WP_BOX, widget_locked);
            endrow();            

            beginrow(); // Fifth row (Operator) with three columns 
              CreatePromptField     (RECIPE_ROW47_ID,     CL_PT_BLUE, OFF,                  "", FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputTextField (RECIPE_ROW47_INPUT,                                      "", WD_WP_BOX, HT_WP_BOX, widget_locked);
              CreateUnitField       (RECIPE_ROW47_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         "", WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow();  

            beginrow(); // Sixth row (Article no) with three columns
              CreatePromptField     (RECIPE_ROW48_ID,     CL_PT_BLUE, OFF,                  "", FT_STANDARD_SIZE, WD_WP_DESCRIPTION, HT_WP_DESCRIPTION, No_Margin, widget_locked);
              CreateOutputTextField (RECIPE_ROW48_INPUT,                                      "", WD_WP_BOX, HT_WP_BOX, widget_locked);
              CreateUnitField       (RECIPE_ROW48_UNIT,  FT_RTC_BOLD, FT_STANDARD_SIZE,                         "", WD_UNIT_LEFT, HT_WP_BOX, widget_locked );
            endrow(); 
                   
          endlayout(); // End of Grid Layout
                
        
        endlayout(); // End of HBOX #6   
        
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   


   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_RECIPE4, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateRecipeListPage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/02/10
--  
--  Purpose           : Recipe page database creation 
--                    : 
--  Value Parameters  :
--  Variable Params   : none
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateRecipeListPage(void) // Added by DORJ2 *** Lists the product types
{
  begindraw();
    createpage(PAGE_RECIPE_DBASE_LIST);  
    beginlayout(LAYOUT_TYPE_VBOX, 0);  // VBox 1 separated in 3 parts: headline, simple weighing and button line
          
      createwidget (ID_HEADLINE, WIDGET_TYPE_TEXT_OUTPUT);
        widget_background     (ID_HEADLINE,   CL_PT_GRAY );
        widget_foreground     (ID_HEADLINE,   CL_PT_WHITE);
        widget_fontsize       (ID_HEADLINE,   FT_RECIPE_SIZE);
        widget_size_policy    (ID_HEADLINE,   SIZE_POLICY_MINIMUMEXPANDING, SIZE_POLICY_MINIMUM);
        widget_text_alignment (ID_HEADLINE,   WIDGET_TEXT_ALIGN_LEFT );
        widget_text           (ID_HEADLINE,   concat(space(1), lsub(TX_RECIPE_ID), space(5), lsub(TX_PRESSHERE)) );
  
      createwidget (ID_RECIPE_DBASE_LIST, WIDGET_TYPE_LIST);
        widget_fontsize    (ID_RECIPE_DBASE_LIST, FT_RECIPE_SIZE);  
        
    endlayout(); // End VBox 1 layout
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : WPFillDb_Init
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/26
--  
--  Purpose           : Fill WP Database If less than MaxArrayWPDbase
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void WPFillDb_Init (void)
{
int   i,j,k, err, MaxArrayWPTemp,test,test2;
bool WPsActive;


   MaxArrayWPDbase = MAX_WP;
   MaxArrayWPTemp= records(WPdb);
   WPsActive = OFF;

WPdb.No = 0;
if(find(WPdb)==0)
 { 
  delete(WPdb);
  DbDamaged.WPs = ON;
 } 
 
while(findnext(WPdb)==0)
 {
 test++;
 }

do
 {
 if (WPdb.No <1 || WPdb.No > MAX_WP)
  { 
   delete(WPdb);
   DbDamaged.WPs = ON;
  } 
 test++;
  if(WPdb.NominalWeight > 0) WPsActive = ON;
 }
while(findprev(WPdb)==0); 

 if(!WPsActive)
  DbDamaged.WPs = ON;

i=1; 
while(i<=MAX_WP)
 {
  WPdb.No=i;
  while(find(WPdb)==0)
  {
      
      WPdb.No = i + 1000;
      if(WPdb.Name == "" || left(WPdb.Name,4) == "Free")
      {
      WPdb.Name = concat("Free", space(1), trim(string(i)));
      WPdb.Unit = ("kg");
      }
      err=insert(WPdb);
      WPdb.No=i;
      while(find(WPdb)==0)
       {
        delete(WPdb);
       } 
      WPdb.No = i + 1000;
      find(WPdb);
      WPdb.No = i;
      err=insert(WPdb);
      WPdb.No = i + 1000;
      find(WPdb);
      delete(WPdb);
      i++;
    WPdb.No=i;  
  }     
     if(i<=MAX_WP)
     { 
      DbDamaged.WPs = ON;
      WPdb.No=i;
      WPdb.Name = concat("Free", space(1), trim(string(i)));
      WPdb.Unit = ("kg");
      err=insert(WPdb);
      i++;
     } 
 }      

}


/*------------------------------------------------------------------------- 
--  Procedure Name    : WPManagePageClear
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/26
--  
--  Purpose           : Clears data in Pattern Manager page
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void WPManagePageClear (void)
{
  WP_Rename_No = 0;
  WP_CopySrce_No = 0;
  WP_CopyDest_No = 0;
  WP_Delete_No = 0;
  widget_text (WPMANAGE_RENSRCE_SEARCH_ID, "");
  widget_text (WPMANAGE_RENNEW_SEARCH_ID, "");
  widget_text (WPMANAGE_COPYSRCE_SEARCH_ID, "");
  widget_text (WPMANAGE_COPYDEST_SEARCH_ID, ""); 
  widget_text (WPMANAGE_DELETE_SEARCH_ID, "");
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshWPGrayOut
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/22
--  
--  Purpose           : Gray out management while refreshing page
--                      
--  Value Parameters  :
--  Variable Params   : Scrn_No = Active screen, MaxRows = # of rows to update,
--                    : pointer =  starting IO # (0 to 72)
--  Side Effects      : 
--------------------------------------------------------------------------*/

void RefreshWPGrayOut(int Scrn_No, int page_no, int MaxRows, int pointer)
{
int i, j ;
TEST_ID[0]     = string(RECIPE_ROW1_ID);
TEST_VALUE[0]  = string(RECIPE_ROW1_INPUT);
TEST_SELECT[0] = string(RECIPE_ROW1_SELECT);
TEST_UNITS[0]  = string(RECIPE_ROW1_UNIT);
j=pointer;

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
      widget_enable     (TEST_ID[j],      !Recipe_Grayout[i+1]);
      widget_enable     (TEST_VALUE[j],   !Recipe_Grayout[i+1]);
      widget_enable     (TEST_SELECT[j],  !Recipe_Grayout[i+1]);
//      widget_enable     (TEST_UNITS[j],   !Recipe_Grayout[i+1]);
                 
      j = j+1;
     }
} 


/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshWPScreen
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/22
--  
--  Purpose           : Refresh Recipe screen at first screen access or after 
--                    : keyboard input entry to update Lim function
--  Value Parameters  :
--  Variable Params   : Scrn_No = Active screen number
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshWPScreen(int Scrn_No)
{

 if (Scrn_No==SCREEN_RECIPE1 || Scrn_No==SCREEN_RECIPE2 || Scrn_No==SCREEN_RECIPE3 || Scrn_No==SCREEN_RECIPE4) 
 {
   begindraw(); 
   
 
    switch ( Scrn_No )
    {
      case SCREEN_RECIPE1 : 
      
                      widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(RECIPECHARSPACE), "1" , space(1), TX_FSLASH, space(1),"4", space(1)));
                         
                    // First Column                                
                      widget_text      (RECIPE_ROW1_INPUT,  WP.NominalWeight);
                      widget_text      (RECIPE_ROW1_UNIT,   WP.Unit);
                      
                      widget_text      (RECIPE_ROW2_INPUT,  WP.Overfill);
                      widget_text      (RECIPE_ROW2_UNIT,   WP.Unit);
                      
                      widget_text      (RECIPE_ROW3_INPUT,  adj((WP.Cutoff-CutoffCorrOffset[Scale1]),6,2));
                      widget_text      (RECIPE_ROW3_UNIT,   WP.Unit);
                    
                      widget_text      (RECIPE_ROW4_INPUT,  WP.BulkCutoff);
                      widget_text      (RECIPE_ROW4_UNIT,   WP.Unit);
                      
                      widget_text      (RECIPE_ROW5_INPUT,  WP.DFTime);
                      widget_text      (RECIPE_ROW6_INPUT,  WP.BFTime);
    
                    // Second Column                               
                      widget_text      (RECIPE_ROW7_INPUT,  WP.UnderWeight);
                      widget_text      (RECIPE_ROW7_UNIT,   WP.Unit);
                      
                      widget_text      (RECIPE_ROW8_INPUT,  WP.OverWeight);
                      widget_text      (RECIPE_ROW8_UNIT,   WP.Unit);
                      
                      widget_text      (RECIPE_ROW9_INPUT,  WP.IntermCutoff);
                      widget_text      (RECIPE_ROW9_UNIT,   WP.Unit);
                    
                      widget_text      (RECIPE_ROW10_INPUT, WP.DischargeWeight);
                      widget_text      (RECIPE_ROW10_UNIT,  WP.Unit);
                      
                      widget_text      (RECIPE_ROW11_INPUT, WP.DischargeTime);
                      widget_text      (RECIPE_ROW12_INPUT, WP.FallingTime); 
                      
                      RefreshWPGrayOut (SCREEN_RECIPE1, MX_PAGE1, 12, 0);                                                                                                                                    
                    break;
                           
                           
      case SCREEN_RECIPE2 :   
        
                      widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(RECIPECHARSPACE), "2" , space(1), TX_FSLASH, space(1),"4", space(1))); 
        
                    // First Column                                 
                      widget_text      (RECIPE_ROW13_INPUT,  WP.MinFeeding);
                      widget_text      (RECIPE_ROW14_INPUT,  WP.MaxFeeding);
                      widget_text      (RECIPE_ROW15_INPUT,  WP.RegMinFeeding);
                      
                      widget_text      (RECIPE_ROW16_INPUT,  WP.RegMaxFeeding);
                      widget_set_index (RECIPE_ROW17_SELECT, WP.StreamRegConfig,0);
                      WP.ActuatorPos = LimActuator(5,95,WP.ActuatorPos);
                      widget_text      (RECIPE_ROW18_INPUT,  WP.ActuatorPos);
  
                     // Second Column                               
                      widget_text      (RECIPE_ROW19_INPUT,  WP.WeighmentsPerUnit);
                      widget_text      (RECIPE_ROW20_INPUT,  WP.FeedDelayTime);                 
                      widget_set_index (RECIPE_ROW21_SELECT, WP.VibratoryDischDoors,0);
                     
                      widget_set_index (RECIPE_ROW22_SELECT, WP.ZeroingOpen,0);                     
                      widget_set_index (RECIPE_ROW23_SELECT, WP.SlowCycleEnd,0);                        
                      widget_set_index (RECIPE_ROW24_SELECT, WP.EnabledScale,0);  
                      
                      RefreshWPGrayOut (SCREEN_RECIPE2, MX_PAGE2, 12, 12);                    
                       
                     break;
  
      case SCREEN_RECIPE3 :
      
                      widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(RECIPECHARSPACE), "3" , space(1), TX_FSLASH, space(1),"4", space(1)));
      
                     // First Column 
                      if(WP.FeedAlgoType == FeediQSim) 
                      {
                        widget_text       (RECIPE_ROW25_ID,    concat("iQSim ",lsub(TX_BULK_TIME_ID)));
                        widget_label      (RECIPE_ROW25_INPUT, concat("iQSim ",lsub(TX_BULK_TIME_ID)));
                      }  
                      else 
                      { 
                        widget_text       (RECIPE_ROW25_ID,    lsub(TX_WPTOPUPOFFTIME));   
                        widget_label      (RECIPE_ROW25_INPUT, lsub(TX_WPTOPUPOFFTIME));
                      }                              
                      widget_text      (RECIPE_ROW25_INPUT,  WP.TopUpOFFTime);
                      widget_text      (RECIPE_ROW26_INPUT,  WP.TopUpONTime);
                      widget_text      (RECIPE_ROW27_INPUT,  WP.KnockningTime);
                      
                      widget_text      (RECIPE_ROW28_INPUT,  WP.BagInflationTime);
                      widget_text      (RECIPE_ROW29_INPUT,  WP.KickerCenterTime);
                      widget_text      (RECIPE_ROW30_INPUT,  WP.KickerActivateTime);
                      
                      
                    // Second Column
                      if(WP.FeedAlgoType == FeediQSim) widget_text       (RECIPE_ROW26_ID, concat("iQSim ",lsub(TX_DRIBBLE_TIME_ID)));
                      else                             widget_text       (RECIPE_ROW26_ID, lsub(TX_WPTOPUPONTIME)); 
                      widget_set_index (RECIPE_ROW31_SELECT, (WP.Unit==TX_WPUNITLB),0);
                      widget_set_index (RECIPE_ROW32_SELECT, WP.FeedAlgoType,0);
                      widget_set_index (RECIPE_ROW33_SELECT, WP.SlowFillFactor,0);
                      widget_set_index (RECIPE_ROW34_SELECT, WP.TuneiQFeed,0);
                      widget_set_index (RECIPE_ROW35_SELECT, WP.BulkMode,0);
                      widget_text      (RECIPE_ROW36_INPUT,  WP.CatchGateDelay);
                      
                      RefreshWPGrayOut (SCREEN_RECIPE3, MX_PAGE3, 12, 24);
                      
                     break; 
                     
      case SCREEN_RECIPE4 :
      
                      widget_text (RECIPE_SEARCH_ID, concat(space(1),lsub(WP.Name),space(RECIPECHARSPACE), "4" , space(1), TX_FSLASH, space(1),"4", space(1)));
      
                     // First Column 
                      
                      widget_text      (RECIPE_ROW37_INPUT,  WP.FlexT1);
                      widget_text      (RECIPE_ROW38_INPUT,  WP.FlexT2);
                      widget_text      (RECIPE_ROW39_INPUT,  WP.FlexCounter);
                      widget_set_index (RECIPE_ROW40_SELECT, WP.DischDoorMode,0);
                      
                    // Second Column
                      widget_text      (RECIPE_ROW43_INPUT,  WP.FlexSP1);
                      widget_text      (RECIPE_ROW43_UNIT,   WP.Unit);
                      
                      widget_text      (RECIPE_ROW44_INPUT,  WP.FlexSP2);
                      widget_text      (RECIPE_ROW44_UNIT,   WP.Unit);
                      
                      widget_text      (RECIPE_ROW45_INPUT,  WP.VibrationAmplitude);
                      widget_text      (RECIPE_ROW46_INPUT,  WP.VibrationPeriod);
                      
                      RefreshWPGrayOut (SCREEN_RECIPE4, MX_PAGE4, 12, 36);
                      
                     break;                                   
    }
   enddraw();           
 }
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : SaveRecipeInputEntry
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
void RefreshRecipeInputEntry(int Scrn_No, int value, string Argument)
{

decimal NominalWeightPrev%6.2,NominalWeightOffset%6.2,OverfillPrev%6.2,OverfillOffset%6.2;
 begindraw();
  switch (Scrn_No)
  {
    case SCREEN_RECIPE1 :
                      switch (value)
                      {      
                        // Page 1 of 4
                        
                        case RECIPE_ROW1_INPUT :   
                                                  NominalWeightPrev =  WP.NominalWeight;
                                                  WP.NominalWeight = decimal (Lim(MaxWeight[Scale1]*0.05,MaxWeight[Scale1],Argument));
                                                  NominalWeightOffset =  NominalWeightPrev - WP.NominalWeight;
                                                                                                    
                                                //Autotracking feature 
                                                  WP.UnderWeight = Lim((WP.NominalWeight - (MaxWeight[Scale1]*0.08)),WP.NominalWeight, (WP.UnderWeight - NominalWeightOffset) );
                                                  WP.OverWeight  = Lim(WP.NominalWeight,(WP.NominalWeight + (MaxWeight[Scale1]*0.08)), (WP.OverWeight - NominalWeightOffset));
                                                  WP.Cutoff      = Lim(((WP.NominalWeight+WP.Overfill)- (0.5*MaxWeight[Scale1])),((WP.NominalWeight+WP.Overfill)+ (0.5*MaxWeight[Scale1])),(WP.Cutoff - NominalWeightOffset));
                                                  WP.BulkCutoff  = Lim(0,(WP.Cutoff-CutoffCorrOffset[Scale1]),(WP.BulkCutoff - NominalWeightOffset));
                                                  WP.IntermCutoff    = Lim(WP.BulkCutoff,WP.Cutoff,(WP.IntermCutoff - NominalWeightOffset));
                                                  WP.DischargeWeight = Lim(0,WP.NominalWeight,(WP.DischargeWeight - NominalWeightOffset));
                                                  break;
                        
                        case RECIPE_ROW2_INPUT :  
                                                  OverfillPrev = WP.Overfill;
                                                  WP.Overfill = Lim(0,MaxWeight[Scale1]*0.02,Argument); 
                                                  OverfillOffset = OverfillPrev - WP.Overfill;
                                                  
                                                //Autotracking feature 
                                                  WP.Cutoff      = Lim(((WP.NominalWeight+WP.Overfill)- (0.5*MaxWeight[Scale1])),((WP.NominalWeight+WP.Overfill)+ (0.5*MaxWeight[Scale1])),(WP.Cutoff - OverfillOffset));
                                                  WP.BulkCutoff  = Lim(0,(WP.Cutoff-CutoffCorrOffset[Scale1]),(WP.BulkCutoff - OverfillOffset));
                                                  WP.IntermCutoff    = Lim(WP.BulkCutoff,WP.Cutoff,(WP.IntermCutoff - OverfillOffset));   
                                                  break;  
                        
                        case RECIPE_ROW3_INPUT :  WP.Cutoff   = Lim(((WP.NominalWeight+WP.Overfill)- (0.5*MaxWeight[Scale1])),((WP.NominalWeight+WP.Overfill)+ (0.5*MaxWeight[Scale1])),Argument);
                                                  CutoffCorrOffset[Scale1] = 0;
                                                  WP.BulkCutoff  = Lim(0,(WP.Cutoff-CutoffCorrOffset[Scale1]),WP.BulkCutoff);
                                                  break;
                                                        
                        case RECIPE_ROW4_INPUT :  WP.BulkCutoff = Lim(0,(WP.Cutoff-CutoffCorrOffset[Scale1]),Argument); // g_arDribbleFeedQuantity in NXT 
                                                  break; 
                                                       
                        case RECIPE_ROW5_INPUT :  WP.DFTime   = Lim(0,1800,Argument);
                                                  break;
                                                         
                        case RECIPE_ROW6_INPUT :  WP.BFTime   = Lim(0,1800,Argument);
                                                  break;    
                                                  
                        case RECIPE_ROW7_INPUT :  WP.UnderWeight = Lim((WP.NominalWeight - (MaxWeight[Scale1]*0.08)),WP.NominalWeight,Argument);
                                                  break;
                                                         
                        case RECIPE_ROW8_INPUT :  WP.OverWeight = Lim(WP.NominalWeight,(WP.NominalWeight + (MaxWeight[Scale1]*0.08)),Argument);
                                                  break;  
                                                          
                        case RECIPE_ROW9_INPUT :  WP.IntermCutoff = Lim(WP.BulkCutoff,WP.Cutoff,Argument);
                                                  break;
                                                         
                        case RECIPE_ROW10_INPUT : WP.DischargeWeight = Lim(0,WP.NominalWeight,Argument);
                                                  break; 
                                                         
                        case RECIPE_ROW11_INPUT : WP.DischargeTime = Lim(0,60,Argument);
                                                  break;
                                                         
                        case RECIPE_ROW12_INPUT : WP.FallingTime = Lim(0.01,50,Argument);
                                                  break;  
                      }
                    break;  
                      
    case SCREEN_RECIPE2 :
                     switch (value)
                     {                    
                        // Page 2 of 4                          
                        case RECIPE_ROW13_INPUT : WP.MinFeeding = Lim(0,WP.MaxFeeding-1,Argument);
                                                  break; 
                                                  
                        case RECIPE_ROW14_INPUT : WP.MaxFeeding = Lim(WP.MinFeeding+1,100,Argument);
                                                  break; 
                                                  
                        case RECIPE_ROW15_INPUT : WP.RegMinFeeding = Lim(0,WP.RegMaxFeeding-1,Argument);
                                                  break; 
                                                  
                        case RECIPE_ROW16_INPUT : WP.RegMaxFeeding = Lim(WP.RegMinFeeding+1,100,Argument);
                                                  break; 
                                                  
                    /*    case RECIPE_ROW17_INPUT : WP.StreamRegConfig = int (Argument);
                                                  break; 
                    */                              
                        case RECIPE_ROW18_INPUT : WP.ActuatorPos = LimActuator(5,95,Argument);
                                                  break; 
                                                  
                        case RECIPE_ROW19_INPUT : WP.WeighmentsPerUnit = int (Lim(1,99999,Argument));
                                                  break; 
                                                  
                        case RECIPE_ROW20_INPUT : WP.FeedDelayTime = Lim(0,60,Argument);
                                                  break; 
                                                  
                    /*    case RECIPE_ROW21_INPUT : WP.VibratoryDischDoors = int (Argument);
                                                  break; 
                    */                              
                    /*    case RECIPE_ROW22_INPUT : WP.ZeroingOpen = int (Argument);
                                                  break; 
                    */                              
                    /*    case RECIPE_ROW23_INPUT : WP.SlowCycleEnd = int (Argument);
                                                  break; 
                    */                              
                    /*    case RECIPE_ROW24_INPUT : WP.EnabledScale = int (Argument);
                                                  break; 
                    */
                     }
                   break;  
                     
    case SCREEN_RECIPE3 :
                     switch (value) 
                     {                    
                        // Page 3 of 4                          
                        case RECIPE_ROW25_INPUT : WP.TopUpOFFTime = Lim(0,10,Argument);
                                                  break; 
                                                  
                        case RECIPE_ROW26_INPUT : WP.TopUpONTime = Lim(0,10,Argument); 
                                                  break; 
                                                  
                        case RECIPE_ROW27_INPUT : WP.KnockningTime = Lim(0,120,Argument);
                                                  break; 
                                                  
                        case RECIPE_ROW28_INPUT : WP.BagInflationTime = Lim(0,60,Argument);
                                                  break; 
                        
                        case RECIPE_ROW29_INPUT : WP.KickerCenterTime = Lim(0,60,Argument);
                                                  break;
                                                  
                        case RECIPE_ROW30_INPUT : WP.KickerActivateTime = Lim(0,60,Argument);
                                                  break;                                                    
                                                  
                        case RECIPE_ROW31_INPUT : 
                                                  break; 
                                                  
                        
                                                  
                        case RECIPE_ROW36_INPUT : WP.CatchGateDelay = Lim(0,CATCHGATEDELAYMAX,Argument);
                                                  break;  
                     } 
                   break;
                   
     case SCREEN_RECIPE4 :
                     switch (value) 
                     {                    
                        // Page 4 of 4                          
                        
                        case RECIPE_ROW37_INPUT : WP.FlexT1 = Lim(0,60,Argument);
                                                  FlexIO_SetTPresetsFlag = Execute;
                                                  break; 
                                                  
                        case RECIPE_ROW38_INPUT : WP.FlexT2 = Lim(0,60,Argument);
                                                  FlexIO_SetTPresetsFlag = Execute;
                                                  break;
                                                  
                        case RECIPE_ROW39_INPUT : WP.FlexCounter = Lim(0,999999,Argument);
                                                  FlexIO_SetTPresetsFlag = Execute;
                                                  break;                          
                        
                        case RECIPE_ROW43_INPUT : WP.FlexSP1 = Lim(0,WP.NominalWeight,Argument);
                                                  FlexIO_SetTPresetsFlag = Execute;
                                                  break; 
                                                  
                        case RECIPE_ROW44_INPUT : WP.FlexSP2 = Lim(0,WP.NominalWeight,Argument);
                                                  FlexIO_SetTPresetsFlag = Execute;
                                                  break;
                       
                        case RECIPE_ROW45_INPUT : WP.VibrationAmplitude = Lim(0,40,Argument);
                                                  break;  
                                                  
                        case RECIPE_ROW46_INPUT : WP.VibrationPeriod = Lim(0.05,1,Argument);
                                                  break;                            
                         
                     } 
                   break;                                                                                                                                                                        
  
  }
 enddraw();
}



/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshRecipeComboBoxEntry
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/22
--  
--  Purpose           : Refresh ComboBox box entry to recipe buffer
--                      
--  Value Parameters  :
--  Variable Params   : value = readevent entered value, Argument = Argument value from readevent 
                      :  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshRecipeComboBoxEntry(int Scrn_No, int value, int Arg_int, string Arg_str )
{
 begindraw();
  switch (Scrn_No)
  {  
    case SCREEN_RECIPE2 :  
                   switch (value)
                   {
                     case RECIPE_ROW17_SELECT :  WP.StreamRegConfig = Arg_int;
                                                 break;
                     case RECIPE_ROW21_SELECT :  WP.VibratoryDischDoors = Arg_int;
                                                 break;   
                     case RECIPE_ROW22_SELECT :  WP.ZeroingOpen = Arg_int;
                                                 break; 
                     case RECIPE_ROW23_SELECT :  WP.SlowCycleEnd = Arg_int;
                                                 break;
                     case RECIPE_ROW24_SELECT :  WP.EnabledScale = Arg_int;
                                                 break;
                   }
                 break;  

    case SCREEN_RECIPE3 :  
                   switch (value)
                   {
                     case RECIPE_ROW31_SELECT :  WP.Unit = Arg_str;
                                                 break;
                                                 
                     case RECIPE_ROW32_SELECT :  
                                                 WP.FeedAlgoType = ValidateAlgoType(MC.FeederType,Arg_int,WP.FeedAlgoType); 
                                                 if(WP.FeedAlgoType != Arg_int)
                                                 {
                                                  widget_set_index (RECIPE_ROW32_SELECT, WP.FeedAlgoType,0);
                                                 }
                                                 RefreshGrayout();
                                                 break;
                
                                               break;
                     case RECIPE_ROW33_SELECT :  WP.SlowFillFactor = Arg_int;
                                                 break;
                                                 
                     case RECIPE_ROW34_SELECT :  WP.TuneiQFeed = Arg_int;
                                                 break;
                     case RECIPE_ROW35_SELECT :  WP.BulkMode   = Arg_int;
                                                 break;                                                        
                                                                                                                      
                   }
                 break; 
       
       case SCREEN_RECIPE4 :  
                   switch (value)
                   {
                     case RECIPE_ROW40_SELECT :  WP.DischDoorMode = Arg_int;
                                                 break;          
                   }
                  break;                               
  }
   
 enddraw();
} 
/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateRecipePages
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/24
--  
--  Purpose           : Create Recipe Pages Manager 
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateRecipePages(void) 
{
    CreateRecipeListPage();
    CreateRecipePage1();
    CreateRecipePage2();
    CreateRecipePage3();
    CreateRecipePage4();
}





















void CreateWPListButton (int id, int font_size, int font_face, string bg_color, int width, int height, string text)
{
  createwidget (id, WIDGET_TYPE_BUTTON);
    widget_style           (id,  WPMANAGEBOX_STYLE);
    widget_dimensions      (id,  width, height);  
    widget_size_policy     (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);    
    widget_fontsize        (id,  font_size); 
    widget_foreground      (id,  CL_PT_BLUE);
    widget_background      (id,  bg_color);
    widget_text_alignment  (id,  WIDGET_TEXT_ALIGN_CENTER );
    widget_text            (id,  text );
    widget_maximum_size    (id,  WD_WPMANAGE_DESCR, WD_WP_BOX);
    widget_content_margins (id,  0,0,0,0);
}


/* *********************************************** */
/*   Create Input field                            */                                                            
/* *********************************************** */

void CreateInputField2 (int id, int font_size, int font_face, int format, int len, int decs, int width, int height, string text )
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
    widget_maximum_size    (id,  WD_WPMANAGE_DESCR, WD_WP_BOX);
    widget_content_margins (id,  0,0,0,0); 
}

void CreateStatusField (int id, int type, int al, string font_size, int font_face, string text, string w_style)
{
  createwidget(id, type);
    widget_text_alignment  (id,  al);
    widget_fontsize        (id,  font_size);  
    widget_fontface        (id,  font_face);         
    widget_style           (id,  w_style);    
    widget_text            (id,  text);
}




/* *********************************************************************** */
/*                                                                         */
/*       Refresh Recipe management screen display                          */
/*                                                                         */
/* *********************************************************************** */

void RefreshWPManageScreen(int Scrn_No)
{
 begindraw(); 
  RefreshCurrentUser();
  widget_text   (WPMANAGE_RECIPE_ID, concat(space(1),lsub(WP.Name),space(1)));

  switch ( Scrn_No )
  {
    case SCREEN_WPMANAGECOPY :                                   
                                widget_text (WPMANAGE_COPYSRCE_SEARCH_ID, "");
                                widget_text (WPMANAGE_COPYDEST_SEARCH_ID, "");
                               break; 
    case SCREEN_WPMANAGERENAME:                                   
                                widget_text (WPMANAGE_RENSRCE_SEARCH_ID, "");
                                widget_text (WPMANAGE_RENNEW_SEARCH_ID, "");
                               break;
    case SCREEN_WPMANAGEDELETE :                                   
                                widget_text (WPMANAGE_DELETE_SEARCH_ID, "");
                               break;                               
  }
 enddraw();
          
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateWPManageCopyPage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/26
--  
--  Purpose           : Create Recipe Manager page
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateWPManageCopyPage(void) 
{
  begindraw();
  createpage(PAGE_WPMANAGECOPY);  
  page_background (PAGE_WPMANAGECOPY, BackgroundColor);
  
   
beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1  VBOX = Alignement des Rangées


       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (WPMANAGE_RECIPE_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(WP.Name), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // WP Copy header       User Level display
       beginlayout(LAYOUT_TYPE_HBOX, 0,3);     
          CreateHeader (AUTO_SPACE_1, WD_USERLEVEL, HT_USERLEVEL, "", align_hcenter, "", FT_STANDARD_SIZE, widget_locked );
          CreateHeader (WPMANAGE_PAGE_HEADER, WD_HEADER, HT_HEADER, "", align_hcenter, concat (space(1), lsub(TX_WPMANAGECOPY_PAGE), space(1)), FT_STANDARD_SIZE, widget_locked );
          CreateHeader (ACCESS_LEVEL, WD_USERLEVEL, HT_USERLEVEL, "", align_vcenter, concat (space(1), lsub(TX_ACCESS_USER),":", space(1) , CurrentUser), FT_SMALL_SIZE, widget_locked);
       endlayout(); 



     beginlayout(LAYOUT_TYPE_VBOX, 0); // Centering Source WP/ Dest. WP with Copy button
        
        //  Source WP and Dest. WP ID & boxes
        beginlayout(LAYOUT_TYPE_HBOX, 0); //HBOX #2

//          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);          

          beginlayout(LAYOUT_TYPE_GRID, 0); // GRID #1
            
              beginrow(); // First row "Blank" with 2 columns             
                CreatePromptField     (WPMANAGE_ROW13_ID,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_WPMANAGE_BOX, 12, No_Margin, widget_unlocked);
                CreateOutputTextField (WPMANAGE_ROW13_INPUT,"", WD_WPMANAGE_DESCR, 12, widget_locked);   
              endrow();
              
              beginrow(); // Second row with two columns
                CreatePromptField (WPMANAGE_COPYSRCE_ID,     CL_PT_BLUE, OFF, lsub(TX_WPMANAGE_CPY_SRCE), FT_STANDARD_SIZE, WD_WPMANAGE_BOX, HT_WP_BOX, No_Margin, widget_unlocked);
                widget_text_alignment (WPMANAGE_COPYSRCE_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
                widget_content_margins (WPMANAGE_COPYSRCE_ID, 0,0,WD_MARGIN,0);
                CreateWPListButton (WPMANAGE_COPYSRCE_SEARCH_ID, FT_STANDARD_SIZE, FT_RTC_BOLD, CL_PT_WHITE, WD_WPMANAGE_DESCR, HT_WP_BOX, "" );                            
              endrow();
         
              beginrow(); // Third row with two columns         
                CreatePromptField (WPMANAGE_COPYDEST_ID,     CL_PT_BLUE, OFF, lsub(TX_WPMANAGE_CPY_DEST), FT_STANDARD_SIZE, WD_WPMANAGE_BOX, HT_WP_BOX, No_Margin, widget_unlocked);              
                widget_text_alignment (WPMANAGE_COPYDEST_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
                widget_content_margins (WPMANAGE_COPYDEST_ID, 0,0,WD_MARGIN,0);
                CreateWPListButton (WPMANAGE_COPYDEST_SEARCH_ID, FT_STANDARD_SIZE, FT_RTC_BOLD, CL_PT_WHITE, WD_WPMANAGE_DESCR, HT_WP_BOX, "" );
              endrow();
              
              beginrow(); // Fourth row "Blank" with 2 columns             
                CreatePromptField     (WPMANAGE_ROW14_ID,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_WPMANAGE_BOX, 10, No_Margin, widget_unlocked);
                CreateOutputTextField (WPMANAGE_ROW14_INPUT,"", WD_WPMANAGE_DESCR, 10, widget_locked);   
              endrow();

          endlayout();  // End GRID #1
          
//          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);      

        endlayout(); // End HBOX #2

        //  Copy button
        beginlayout(LAYOUT_TYPE_HBOX, 0);
        
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
          CreateSpacingField (WPMANAGE_SPACE_6, CL_PT_BLUE, FT_STANDARD_SIZE, space(30));
          createwidget (WPMANAGE_COPY_BUTTON, WIDGET_TYPE_TEXT_OUTPUT);
          widget_image (WPMANAGE_COPY_BUTTON,BTN_COPY);
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
        
        endlayout();  
     
     endlayout(); // End of Centering Source WP/ Dest. WP with Copy button


   createwidget (0, WIDGET_TYPE_STRETCH);  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_WPMANAGECOPY, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_COPY, BTN_RENAME, BTN_DEL, BTN_NIL_BLUE, BTN_NIL_BLUE);  
    
endlayout();  // End of VBOX #1
enddraw();

}




/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateWPManageRenamePage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/26
--  
--  Purpose           : Create Recipe Manager page
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateWPManageRenamePage(void) 
{
  begindraw();
  createpage(PAGE_WPMANAGERENAME);  
  page_background (PAGE_WPMANAGERENAME, BackgroundColor);
  
   
beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1  VBOX = Alignement des Rangées

        beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (WPMANAGE_RECIPE_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(WP.Name), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // WP Rename header       User Level display
       beginlayout(LAYOUT_TYPE_HBOX, 0,3);     
          CreateHeader (AUTO_SPACE_1, WD_USERLEVEL, HT_USERLEVEL, "", align_hcenter, "", FT_STANDARD_SIZE, widget_locked );
          CreateHeader (WPMANAGE_PAGE_HEADER, WD_HEADER, HT_HEADER, "", align_hcenter, concat (space(1), lsub(TX_WPMANAGERENAME_PAGE), space(1)), FT_STANDARD_SIZE, widget_locked );
          CreateHeader (ACCESS_LEVEL, WD_USERLEVEL, HT_USERLEVEL, "", align_vcenter, concat (space(1), lsub(TX_ACCESS_USER),":", space(1) , CurrentUser), FT_SMALL_SIZE, widget_locked);
       endlayout(); 



     beginlayout(LAYOUT_TYPE_VBOX, 0); // Centering Source Name/ New Name with Rename button
        
        //  Source Name and New Name ID & boxes
        beginlayout(LAYOUT_TYPE_HBOX, 0); //HBOX #2

//          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);          

          beginlayout(LAYOUT_TYPE_GRID, 0); // GRID #1
            
              beginrow(); // First row "Blank" with 2 columns             
                CreatePromptField     (WPMANAGE_ROW21_ID,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_WPMANAGE_BOX, 12, No_Margin, widget_unlocked);
                CreateOutputTextField (WPMANAGE_ROW21_INPUT,"", WD_WPMANAGE_DESCR, 12, widget_locked);   
              endrow();
              
              beginrow(); // Second row with two columns
                CreatePromptField   (WPMANAGE_RENSRCE_ID,     CL_PT_BLUE, OFF, lsub(TX_WPMANAGE_REN_STR_SRCE), FT_STANDARD_SIZE, WD_WPMANAGE_BOX, HT_WP_BOX, No_Margin, widget_unlocked); 
                widget_text_alignment (WPMANAGE_RENSRCE_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
                widget_content_margins (WPMANAGE_RENSRCE_ID, 0,0,WD_MARGIN,0);
                CreateWPListButton (WPMANAGE_RENSRCE_SEARCH_ID, FT_STANDARD_SIZE, FT_RTC_BOLD, CL_PT_WHITE, WD_WPMANAGE_DESCR, HT_WP_BOX, "" );                             
              endrow();
         
              beginrow(); // Third row with two columns         
                CreatePromptField (WPMANAGE_RENNEW_ID,     CL_PT_BLUE, OFF, lsub(TX_WPMANAGE_REN_STR_NEW), FT_STANDARD_SIZE, WD_WPMANAGE_BOX, HT_WP_BOX, No_Margin, widget_unlocked);
                widget_text_alignment (WPMANAGE_RENNEW_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
                widget_content_margins (WPMANAGE_RENNEW_ID, 0,0,WD_MARGIN,0);
                CreateInputField2  (WPMANAGE_RENNEW_SEARCH_ID, FT_STANDARD_SIZE, FT_RTC, INPUT_FORMAT_STRING, WP_NAME_LENGTH, 0, WD_WPMANAGE_DESCR, HT_WP_BOX, lsub(TX_WPMANAGE_REN_STR_NEW) );
              endrow();
              
              beginrow(); // Fourth row "Blank" with 2 columns             
                CreatePromptField     (WPMANAGE_ROW24_ID,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_WPMANAGE_BOX, 10, No_Margin, widget_unlocked);
                CreateOutputTextField (WPMANAGE_ROW24_INPUT,"", WD_WPMANAGE_DESCR, 10, widget_locked);   
              endrow();

          endlayout();  // End GRID #1
          
//          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);      

        endlayout(); // End HBOX #2

        //  Rename button
        beginlayout(LAYOUT_TYPE_HBOX, 0);
        
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
          CreateSpacingField (WPMANAGE_SPACE_5, CL_PT_BLUE, FT_STANDARD_SIZE, space(30));
          createwidget (WPMANAGE_RENAME_BUTTON, WIDGET_TYPE_TEXT_OUTPUT);
          widget_image (WPMANAGE_RENAME_BUTTON,BTN_RENAME);
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
        
        endlayout();  
     
     endlayout(); // End of Centering Source Name/ New Name with Rename button


   createwidget (0, WIDGET_TYPE_STRETCH);  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_WPMANAGERENAME, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_COPY, BTN_RENAME, BTN_DEL, BTN_NIL_BLUE, BTN_NIL_BLUE);  
    
endlayout();  // End of VBOX #1
enddraw();

}




/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateWPManageDeletePage
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/10/26
--  
--  Purpose           : Create Recipe Manager page
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateWPManageDeletePage(void) 
{
  begindraw();
  createpage(PAGE_WPMANAGEDELETE);  
  page_background (PAGE_WPMANAGEDELETE, BackgroundColor);
  
   
beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1  VBOX = Alignement des Rangées

        beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (WPMANAGE_RECIPE_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(WP.Name), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // WP Delete header       User Level display
       beginlayout(LAYOUT_TYPE_HBOX, 0,3);     
          CreateHeader (AUTO_SPACE_1, WD_USERLEVEL, HT_USERLEVEL, "", align_hcenter, "", FT_STANDARD_SIZE, widget_locked );
          CreateHeader (WPMANAGE_PAGE_HEADER, WD_HEADER, HT_HEADER, "", align_hcenter, concat (space(1), lsub(TX_WPMANAGEDELETE_PAGE), space(1)), FT_STANDARD_SIZE, widget_locked );
          CreateHeader (ACCESS_LEVEL, WD_USERLEVEL, HT_USERLEVEL, "", align_vcenter, concat (space(1), lsub(TX_ACCESS_USER),":", space(1) , CurrentUser), FT_SMALL_SIZE, widget_locked);
       endlayout(); 



     beginlayout(LAYOUT_TYPE_VBOX, 0); // Centering WP to Del: with Delete button
        
        //  WP to Del: ID & boxe
        beginlayout(LAYOUT_TYPE_HBOX, 0); //HBOX #2

//          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);          

          beginlayout(LAYOUT_TYPE_GRID, 0); // GRID #1
            
              beginrow(); // First row "Blank" with 2 columns             
                CreatePromptField     (WPMANAGE_ROW31_ID,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_WPMANAGE_BOX, 12, No_Margin, widget_unlocked);
                CreateOutputTextField (WPMANAGE_ROW31_INPUT,"", WD_WPMANAGE_DESCR, 12, widget_locked);   
              endrow();
              
              beginrow(); // Second row with two columns             
                CreatePromptField   (WPMANAGE_DELETE_ID,     CL_PT_BLUE, OFF, lsub(TX_WPMANAGE_DEL_SRCE), FT_STANDARD_SIZE, WD_WPMANAGE_BOX, HT_WP_BOX, No_Margin, widget_unlocked);
                widget_text_alignment (WPMANAGE_DELETE_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
                widget_content_margins (WPMANAGE_DELETE_ID, 0,0,WD_MARGIN,0);
                CreateWPListButton (WPMANAGE_DELETE_SEARCH_ID, FT_STANDARD_SIZE, FT_RTC_BOLD, CL_PT_WHITE, WD_WPMANAGE_DESCR, HT_WP_BOX, "");  
              endrow();
         
              beginrow(); // Third row with two columns         
                CreatePromptField     (WPMANAGE_ROW33_ID,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_WPMANAGE_BOX, HT_WP_BOX, No_Margin, widget_unlocked);
                CreateOutputTextField (WPMANAGE_ROW33_INPUT,"", WD_WPMANAGE_DESCR, HT_WP_BOX, widget_locked);
              endrow();
              
              beginrow(); // Fourth row "Blank" with 2 columns             
                CreatePromptField     (WPMANAGE_ROW34_ID,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_WPMANAGE_BOX, 10, No_Margin, widget_unlocked);
                CreateOutputTextField (WPMANAGE_ROW34_INPUT,"", WD_WPMANAGE_DESCR, 10, widget_locked);   
              endrow();

          endlayout();  // End GRID #1
          
//          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);      

        endlayout(); // End HBOX #2

        //  Rename button
        beginlayout(LAYOUT_TYPE_HBOX, 0);
        
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
          CreateSpacingField (WPMANAGE_SPACE_4, CL_PT_BLUE, FT_STANDARD_SIZE, space(30));
          createwidget (WPMANAGE_DELETE_BUTTON, WIDGET_TYPE_TEXT_OUTPUT);
          widget_image (WPMANAGE_DELETE_BUTTON,BTN_DEL);
          createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);
        
        endlayout();  
     
     endlayout(); // End of Centering WP to Del: with Delete button


   createwidget (0, WIDGET_TYPE_STRETCH);  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_WPMANAGEDELETE, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_COPY, BTN_RENAME, BTN_DEL, BTN_NIL_BLUE, BTN_NIL_BLUE);  
    
endlayout();  // End of VBOX #1
enddraw();

}
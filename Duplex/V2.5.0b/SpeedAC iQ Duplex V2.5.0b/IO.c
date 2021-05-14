/*------------------------------------------------------------------------------------
-- File Name: IO_Config.c 
--
-- Copyright 2015 PremierTech as an unpublished work. 
-- All Rights Reserved.
--
-- The information contained herein is confidential property of 
-- Premier Tech.  The use, copying, transfer or disclosure of such
-- information is prohibited except by express written agreement with
-- Premier Tech.
--
-- First written in August, 2015 by Jean-Pierre Doré.
--
-- Module Description:
-- This file is dedicated to the creation, display and refresh of the I/O Config page. 
-------------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateIOField
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create IO field
--                      
--  Value Parameters  :
--  Variable Params   : id = , fg_color = Foreground color, bold; bold = ON , text = String text, font_size = Font size, width = width of the field, height = height of the field ; 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateIOField(int id, string fg_color, string bg_color, bool bold, string text, int font_size, bool align_center, int width, int height, int margin, bool widget_lock)
{
  createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);     
    widget_size_policy    (id,  SIZE_POLICY_MINIMUM, SIZE_POLICY_FIXED);
    widget_foreground     (id,  fg_color); 
    widget_background     (id,   bg_color);
    widget_fontsize       (id,  font_size); 
  if (align_center)  widget_text_alignment (id,  WIDGET_TEXT_ALIGN_CENTER);
    widget_dimensions     (id,  width, height);
  if (widget_lock) widget_maximum_size (id,  width, height);
    widget_text           (id,  text);
    
  if (bold) widget_fontface  (id,  FT_RTC_BOLD);
  else widget_fontface  (id,  FT_RTC);
    
    widget_content_margins (id, margin,0,0,0);   
}    

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateInputIO
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create Input field
--                      
--  Value Parameters  :
--  Variable Params   : id = , font_face = Font face, format = input format , len = , 
                      : decs = , string = string text, width = width of the field, height = height of the field ; 
--  Side Effects      : widget_lock = if the box size needs to be forced to a smaller value than the default dimension
--------------------------------------------------------------------------*/
void CreateInputIO (int id, int font_face, int format, int len, int decs, string text, int width, int height, bool widget_lock )
{
  createwidget(id, WIDGET_TYPE_TEXT_INPUT); 
    widget_size_policy    (id,  SIZE_POLICY_MINIMUM, SIZE_POLICY_FIXED);
    widget_fontsize       (id,  FT_STANDARD_SIZE); 
    widget_fontface       (id,  font_face);
    widget_format         (id,  format, len, decs);
    widget_label          (id,  text); 
    widget_text_alignment (id,  WIDGET_TEXT_ALIGN_CENTER);
    widget_dimensions     (id,  width, height);
  if (widget_lock) widget_maximum_size (id,  width, height); 
    widget_content_margins (id, 0,0,0,0);    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateIODisplayLoop
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O Display Loop
--                      
--  Value Parameters  :
--  Variable Params   : MaxRows = # of rows, id = , io_num = , check = , state = , pointer = # of the first of the column 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateIODisplayLoop (int MaxButtons, int id, int io_num, int check, int pointer, int margin, bool output  )
{
int i;
TEST_ID[0] = string(id);
TEST_VALUE[0] = string(io_num);
TEST_CHECK[0] = string(check);

 for (i=0; i<MaxButtons; i++)
     {
 
     TEST_ID[i] = TEST_ID[0]+i;
     TEST_POINTER[i] = pointer+i;
     TEST_VALUE[i] = TEST_VALUE[0]+i;
     TEST_CHECK[i] = TEST_CHECK[0]+i;

     }

 for (i=0; i<MaxButtons; i++)
     {
      beginrow(); // single row 
       CreateIOField (TEST_ID[i],    CL_PT_BLUE, CL_PT_WHITE, OFF, IO_Name[TEST_POINTER[i]], FT_IOPAGES_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, margin, widget_locked ); 
       CreateInputIO  (TEST_VALUE[i], FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 2, 0, lsub(TX_IO_ENTER_ADDRESS), WD_IO_INPUT, HT_IO_ADDRESS, widget_locked);
       CreateOnOffBoxField (TEST_CHECK[i], 25, WIDGET_TEXT_ALIGN_CENTER, ON, BTN_CHECKON, BTN_CHECKOFF);
      endrow();
       
     }
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateInputConfigPage1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O INPUT Config page #1
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateInputConfigPage1(void) 
{
 int i; 
 
  begindraw();
  createpage(PAGE_IO_INPUT_1);  
  page_background (PAGE_IO_INPUT_1, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2  
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_INPUTCONFIG_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns 
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 

            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked  ); 
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked ); 
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked ); 
            endrow();          

           CreateIODisplayLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_CHECK_ROW1,1, Left_Margin, Input_Page);
                  
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_1,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOCFG_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked ); 
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

           CreateIODisplayLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_CHECK_ROW7,7, No_Margin, Input_Page);  
                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  // 
       
            
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);

   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_IOCFG_IN1, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateInputConfigPage2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O INPUT Config page #2
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateInputConfigPage2(void) 
{
  begindraw();
  createpage(PAGE_IO_INPUT_2);  
  page_background (PAGE_IO_INPUT_2, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3   

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_INPUTCONFIG_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns 
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER , Left_Margin, widget_locked ); 
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

          CreateIODisplayLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_CHECK_ROW1,13, Left_Margin, Input_Page);

                   
          endlayout();  //End of Grid Layout

        // Spacing between columns
          CreateIOField (IO_SPACE_1,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOCFG_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
          
        // Layout of second column on the right
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked ); 
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

           CreateIODisplayLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_CHECK_ROW7,19, No_Margin, Input_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
       
      
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);

   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_IOCFG_IN2, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateInputConfigPage3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O INPUT Config page #3
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateInputConfigPage3(void) 
{
  begindraw();
  createpage(PAGE_IO_INPUT_3);  
  page_background (PAGE_IO_INPUT_3, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_INPUTCONFIG_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


        // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked  ); 
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_CHECK_ROW1,25, Left_Margin, Input_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_1,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOCFG_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked ); 
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked);
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_CHECK_ROW7,31, No_Margin, Input_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
       
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);

   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_IOCFG_IN3, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputConfigPage1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O OUTPUT Config page #1
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputConfigPage1(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUT_1);  
  page_background (PAGE_IO_OUTPUT_1, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // Split left screen in in-/outputs and infoline

      beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTCONFIG_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


        // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked  );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_CHECK_ROW1,37, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_1,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOCFG_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_CHECK_ROW7,43, No_Margin, Output_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
       
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_IOCFG_OUT1, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputConfigPage2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O OUTPUT Config page #2
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputConfigPage2(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUT_2);  
  page_background (PAGE_IO_OUTPUT_2, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
     beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  
     
      beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTCONFIG_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_CHECK_ROW1,49, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_1,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOCFG_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_CHECK_ROW7,55, No_Margin, Output_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
       
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_IOCFG_OUT2, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputConfigPage3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O OUTPUT Config page #3
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputConfigPage3(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUT_3);  
  page_background (PAGE_IO_OUTPUT_3, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  
      
      beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTCONFIG_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_CHECK_ROW1,61, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_1,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOCFG_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_CHECK_ROW7,67, No_Margin, Output_Page);


                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
       
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_IOCFG_OUT3, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputConfigPage4
--  Created by        : Steve Santerre
--  Last modified on  : 2018/01/10
--  
--  Purpose           : Create I/O OUTPUT Config page #4
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputConfigPage4(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUT_4);  
  page_background (PAGE_IO_OUTPUT_4, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  
      
      beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTCONFIG_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_CHECK_ROW1,73, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_1,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOCFG_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_IO_HEADER, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_IO_HEADER, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ENABLE), FT_IO_HEADER, OFF, WD_IO_ENABLE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIODisplayLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_CHECK_ROW7,79, No_Margin, Output_Page);


                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
       
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_IOCFG_OUT4, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}










/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshIOGrayOut
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/09/16
--  
--  Purpose           : Gray out management while refreshing page
--                      
--  Value Parameters  :
--  Variable Params   : Scrn_No = Active screen, MaxRows = # of rows to update,
--                    : pointer =  starting IO # (0 to 72)
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshIOGrayOut(int Scrn_No, int MaxRows, int pointer)
{


int i, j;
TEST_ID[0]    = string(IO_ID_ROW1);
TEST_VALUE[0] = string(IO_INPUT_ROW1);
TEST_CHECK[0] = string(IO_CHECK_ROW1);
TEST_STATE[0] = string(IO_STATE_ROW1);
j=0;

 for (i=pointer; i<MaxRows; i++)
     {
 
     TEST_ID[i]      = TEST_ID[0]+i;
     TEST_VALUE[i]   = TEST_VALUE[0]+i;
     TEST_CHECK[i]   = TEST_CHECK[0]+i;

     }
     
 for (i=pointer; i<pointer+MaxRows; i++)
     {
        
      widget_enable     (TEST_ID[j],       IO_Enable[i+1]);
      widget_enable     (TEST_VALUE[j],    IO_Enable[i+1]);
      widget_enable     (TEST_STATE[j],    IO_Enable[i+1]);
     
      if (Scrn_No == SCREEN_IOTEST_OUT1 || Scrn_No == SCREEN_IOTEST_OUT2 || Scrn_No == SCREEN_IOTEST_OUT3 || Scrn_No == SCREEN_IOTEST_OUT4) 
         {
           widget_enable     (TEST_CHECK[j], IO_Enable[i+1]);
         }
         else
            {
              widget_enable     (TEST_CHECK[j], ON);
            }
      j = j+1;
     }    
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshIOConfigScreen
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Refresh I/O Config screen display 
--                      
--  Value Parameters  :
--  Variable Params   : Scrn_No = screen number of the page to refresh 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshIOConfigScreen(int Scrn_No)
{

scrn_index = 20;

 begindraw(); 
   
  widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5),  space(1), TX_FSLASH, space(1), "3"));

  switch (Scrn_No)
  {
    case SCREEN_IOCFG_IN1 :    
                // First Column       
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "1", space(1), TX_FSLASH, space(1), "3"));                       
                  if (!IO_Address[1] && !IO_Enable[1]) widget_text (IO_INPUT_ROW1, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW1, trim(IO_Address[1]));
                  widget_text (IO_CHECK_ROW1, IO_Enable[1]);
                  if (!IO_Address[2] && !IO_Enable[2]) widget_text (IO_INPUT_ROW2, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW2, trim(IO_Address[2]));
                  widget_text (IO_CHECK_ROW2, IO_Enable[2]);
                  if (!IO_Address[3] && !IO_Enable[3]) widget_text (IO_INPUT_ROW3, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW3, trim(IO_Address[3]));
                  widget_text (IO_CHECK_ROW3, IO_Enable[3]);
                  if (!IO_Address[4] && !IO_Enable[4]) widget_text (IO_INPUT_ROW4, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW4, trim(IO_Address[4]));
                  widget_text (IO_CHECK_ROW4, IO_Enable[4]);
                  if (!IO_Address[5] && !IO_Enable[5]) widget_text (IO_INPUT_ROW5, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW5, trim(IO_Address[5]));
                  widget_text (IO_CHECK_ROW5, IO_Enable[5]);
                  if (!IO_Address[6] && !IO_Enable[6]) widget_text (IO_INPUT_ROW6, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW6, trim(IO_Address[6]));
                  widget_text (IO_CHECK_ROW6, IO_Enable[6]);
   
                // Second Column                               
                  if (!IO_Address[7] && !IO_Enable[7]) widget_text (IO_INPUT_ROW7, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW7, trim(IO_Address[7]));
                  widget_text (IO_CHECK_ROW7, IO_Enable[7]);
                  if (!IO_Address[8] && !IO_Enable[8]) widget_text (IO_INPUT_ROW8, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW8, trim(IO_Address[8]));
                  widget_text (IO_CHECK_ROW8, IO_Enable[8]);
                  if (!IO_Address[9] && !IO_Enable[9]) widget_text (IO_INPUT_ROW9, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW9, trim(IO_Address[9]));
                  widget_text (IO_CHECK_ROW9, IO_Enable[9]);
                  if (!IO_Address[10] && !IO_Enable[10]) widget_text (IO_INPUT_ROW10, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW10, trim(IO_Address[10]));
                  widget_text (IO_CHECK_ROW10, IO_Enable[10]);
                  if (!IO_Address[11] && !IO_Enable[11]) widget_text (IO_INPUT_ROW11, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW11, trim(IO_Address[11]));
                  widget_text (IO_CHECK_ROW11, IO_Enable[11]);
                  if (!IO_Address[12] && !IO_Enable[12]) widget_text (IO_INPUT_ROW12, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW12, trim(IO_Address[12]));
                  widget_text (IO_CHECK_ROW12, IO_Enable[12]);  
                  
                  RefreshIOGrayOut(SCREEN_IOCFG_IN1,12,0);
                                                                                                                                                        
                break;
    
    case SCREEN_IOCFG_IN2 :    
                // First Column     
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "2", space(1), TX_FSLASH, space(1), "3"));                      
                  if (!IO_Address[13] && !IO_Enable[13]) widget_text (IO_INPUT_ROW1, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW1, trim(IO_Address[13]));
                  widget_text (IO_CHECK_ROW1, IO_Enable[13]);
                  if (!IO_Address[14] && !IO_Enable[14]) widget_text (IO_INPUT_ROW2, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW2, trim(IO_Address[14]));
                  widget_text (IO_CHECK_ROW2, IO_Enable[14]);
                  if (!IO_Address[15] && !IO_Enable[15]) widget_text (IO_INPUT_ROW3, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW3, trim(IO_Address[15]));
                  widget_text (IO_CHECK_ROW3, IO_Enable[15]);
                  if (!IO_Address[16] && !IO_Enable[16]) widget_text (IO_INPUT_ROW4, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW4, trim(IO_Address[16]));
                  widget_text (IO_CHECK_ROW4, IO_Enable[16]);
                  if (!IO_Address[17] && !IO_Enable[17]) widget_text (IO_INPUT_ROW5, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW5, trim(IO_Address[17]));
                  widget_text (IO_CHECK_ROW5, IO_Enable[17]);
                  if (!IO_Address[18] && !IO_Enable[18]) widget_text (IO_INPUT_ROW6, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW6, trim(IO_Address[18]));
                  widget_text (IO_CHECK_ROW6, IO_Enable[18]);
   
                // Second Column                               
                  if (!IO_Address[19] && !IO_Enable[19]) widget_text (IO_INPUT_ROW7, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW7, trim(IO_Address[19]));
                  widget_text (IO_CHECK_ROW7, IO_Enable[19]);
                  if (!IO_Address[20] && !IO_Enable[20]) widget_text (IO_INPUT_ROW8, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW8, trim(IO_Address[20]));
                  widget_text (IO_CHECK_ROW8, IO_Enable[20]);
                  if (!IO_Address[21] && !IO_Enable[21]) widget_text (IO_INPUT_ROW9, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW9, trim(IO_Address[21]));
                  widget_text (IO_CHECK_ROW9, IO_Enable[21]);
                  if (!IO_Address[22] && !IO_Enable[22]) widget_text (IO_INPUT_ROW10, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW10, trim(IO_Address[22]));
                  widget_text (IO_CHECK_ROW10, IO_Enable[22]);
                  if (!IO_Address[23] && !IO_Enable[23]) widget_text (IO_INPUT_ROW11, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW11, trim(IO_Address[23]));
                  widget_text (IO_CHECK_ROW11, IO_Enable[23]);
                  if (!IO_Address[24] && !IO_Enable[24]) widget_text (IO_INPUT_ROW12, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW12, trim(IO_Address[24]));
                  widget_text (IO_CHECK_ROW12, IO_Enable[24]); 
                  
                  RefreshIOGrayOut(SCREEN_IOCFG_IN2, 12,12);
                                                                                                                                                         
                break;
                
    case SCREEN_IOCFG_IN3 :    
                // First Column        
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTCONFIG_PAGE),space(5), "3", space(1), TX_FSLASH, space(1), "3"));                     
                  if (!IO_Address[25] && !IO_Enable[25]) widget_text (IO_INPUT_ROW1, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW1, trim(IO_Address[25]));
                  widget_text (IO_CHECK_ROW1, IO_Enable[25]);
                  if (!IO_Address[26] && !IO_Enable[26]) widget_text (IO_INPUT_ROW2, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW2, trim(IO_Address[26]));
                  widget_text (IO_CHECK_ROW2, IO_Enable[26]);
                  if (!IO_Address[27] && !IO_Enable[27]) widget_text (IO_INPUT_ROW3, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW3, trim(IO_Address[27]));
                  widget_text (IO_CHECK_ROW3, IO_Enable[27]);
                  if (!IO_Address[28] && !IO_Enable[28]) widget_text (IO_INPUT_ROW4, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW4, trim(IO_Address[28]));
                  widget_text (IO_CHECK_ROW4, IO_Enable[28]);
                  if (!IO_Address[29] && !IO_Enable[29]) widget_text (IO_INPUT_ROW5, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW5, trim(IO_Address[29]));
                  widget_text (IO_CHECK_ROW5, IO_Enable[29]);
                  if (!IO_Address[30] && !IO_Enable[30]) widget_text (IO_INPUT_ROW6, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW6, trim(IO_Address[30]));
                  widget_text (IO_CHECK_ROW6, IO_Enable[30]);
   
                // Second Column                               
                  if (!IO_Address[31] && !IO_Enable[31]) widget_text (IO_INPUT_ROW7, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW7, trim(IO_Address[31]));
                  widget_text (IO_CHECK_ROW7, IO_Enable[31]);
                  if (!IO_Address[32] && !IO_Enable[32]) widget_text (IO_INPUT_ROW8, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW8, trim(IO_Address[32]));
                  widget_text (IO_CHECK_ROW8, IO_Enable[32]);
                  if (!IO_Address[33] && !IO_Enable[33]) widget_text (IO_INPUT_ROW9, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW9, trim(IO_Address[33]));
                  widget_text (IO_CHECK_ROW9, IO_Enable[33]);
                  if (!IO_Address[34] && !IO_Enable[34]) widget_text (IO_INPUT_ROW10, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW10, trim(IO_Address[34]));
                  widget_text (IO_CHECK_ROW10, IO_Enable[34]);
                  if (!IO_Address[35] && !IO_Enable[35]) widget_text (IO_INPUT_ROW11, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW11, trim(IO_Address[35]));
                  widget_text (IO_CHECK_ROW11, IO_Enable[35]);
                  if (!IO_Address[36] && !IO_Enable[36]) widget_text (IO_INPUT_ROW12, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW12, trim(IO_Address[36]));
                  widget_text (IO_CHECK_ROW12, IO_Enable[36]);   
                  
                  RefreshIOGrayOut(SCREEN_IOCFG_IN3, 12,24);
                                                                                                                                                      
                break;        
                                                 
    case SCREEN_IOCFG_OUT1 :    
                // First Column   
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "1", space(1), TX_FSLASH, space(1), "4"));                           
                  if (!IO_Address[37] && !IO_Enable[37]) widget_text (IO_INPUT_ROW1, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW1, trim(IO_Address[37]));
                  widget_text (IO_CHECK_ROW1, IO_Enable[37]);
                  if (!IO_Address[38] && !IO_Enable[38]) widget_text (IO_INPUT_ROW2, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW2, trim(IO_Address[38]));
                  widget_text (IO_CHECK_ROW2, IO_Enable[38]);
                  if (!IO_Address[39] && !IO_Enable[39]) widget_text (IO_INPUT_ROW3, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW3, trim(IO_Address[39]));
                  widget_text (IO_CHECK_ROW3, IO_Enable[39]);
                  if (!IO_Address[40] && !IO_Enable[40]) widget_text (IO_INPUT_ROW4, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW4, trim(IO_Address[40]));
                  widget_text (IO_CHECK_ROW4, IO_Enable[40]);
                  if (!IO_Address[41] && !IO_Enable[41]) widget_text (IO_INPUT_ROW5, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW5, trim(IO_Address[41]));
                  widget_text (IO_CHECK_ROW5, IO_Enable[41]);
                  if (!IO_Address[42] && !IO_Enable[42]) widget_text (IO_INPUT_ROW6, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW6, trim(IO_Address[42]));
                  widget_text (IO_CHECK_ROW6, IO_Enable[42]);
   
                // Second Column                               
                  if (!IO_Address[43] && !IO_Enable[43]) widget_text (IO_INPUT_ROW7, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW7, trim(IO_Address[43]));
                  widget_text (IO_CHECK_ROW7, IO_Enable[43]);
                  if (!IO_Address[44] && !IO_Enable[44]) widget_text (IO_INPUT_ROW8, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW8, trim(IO_Address[44]));
                  widget_text (IO_CHECK_ROW8, IO_Enable[44]);
                  if (!IO_Address[45] && !IO_Enable[45]) widget_text (IO_INPUT_ROW9, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW9, trim(IO_Address[45]));
                  widget_text (IO_CHECK_ROW9, IO_Enable[45]);
                  if (!IO_Address[46] && !IO_Enable[46]) widget_text (IO_INPUT_ROW10, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW10, trim(IO_Address[46]));
                  widget_text (IO_CHECK_ROW10, IO_Enable[46]);
                  if (!IO_Address[47] && !IO_Enable[47]) widget_text (IO_INPUT_ROW11, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW11, trim(IO_Address[47]));
                  widget_text (IO_CHECK_ROW11, IO_Enable[47]);
                  if (!IO_Address[48] && !IO_Enable[48]) widget_text (IO_INPUT_ROW12, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW12, trim(IO_Address[48]));
                  widget_text (IO_CHECK_ROW12, IO_Enable[48]);   
                  
                  RefreshIOGrayOut(SCREEN_IOCFG_OUT1, 12,36);
                                                                                                                                                       
                break;
     
     case SCREEN_IOCFG_OUT2 :    
                // First Column         
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "2", space(1), TX_FSLASH, space(1), "4"));                      
                  if (!IO_Address[49] && !IO_Enable[49]) widget_text (IO_INPUT_ROW1, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW1, trim(IO_Address[49]));
                  widget_text (IO_CHECK_ROW1, IO_Enable[49]);
                  if (!IO_Address[50] && !IO_Enable[50]) widget_text (IO_INPUT_ROW2, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW2, trim(IO_Address[50]));
                  widget_text (IO_CHECK_ROW2, IO_Enable[50]);
                  if (!IO_Address[51] && !IO_Enable[51]) widget_text (IO_INPUT_ROW3, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW3, trim(IO_Address[51]));
                  widget_text (IO_CHECK_ROW3, IO_Enable[51]);
                  if (!IO_Address[52] && !IO_Enable[52]) widget_text (IO_INPUT_ROW4, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW4, trim(IO_Address[52]));
                  widget_text (IO_CHECK_ROW4, IO_Enable[52]);
                  if (!IO_Address[53] && !IO_Enable[53]) widget_text (IO_INPUT_ROW5, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW5, trim(IO_Address[53]));
                  widget_text (IO_CHECK_ROW5, IO_Enable[53]);
                  if (!IO_Address[54] && !IO_Enable[54]) widget_text (IO_INPUT_ROW6, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW6, trim(IO_Address[54]));
                  widget_text (IO_CHECK_ROW6, IO_Enable[54]);
   
                // Second Column                               
                  if (!IO_Address[55] && !IO_Enable[55]) widget_text (IO_INPUT_ROW7, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW7, trim(IO_Address[55]));
                  widget_text (IO_CHECK_ROW7, IO_Enable[55]);
                  if (!IO_Address[56] && !IO_Enable[56]) widget_text (IO_INPUT_ROW8, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW8, trim(IO_Address[56]));
                  widget_text (IO_CHECK_ROW8, IO_Enable[56]);
                  if (!IO_Address[57] && !IO_Enable[57]) widget_text (IO_INPUT_ROW9, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW9, trim(IO_Address[57]));
                  widget_text (IO_CHECK_ROW9, IO_Enable[57]);
                  if (!IO_Address[58] && !IO_Enable[58]) widget_text (IO_INPUT_ROW10, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW10, trim(IO_Address[58]));
                  widget_text (IO_CHECK_ROW10, IO_Enable[58]);
                  if (!IO_Address[59] && !IO_Enable[59]) widget_text (IO_INPUT_ROW11, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW11, trim(IO_Address[59]));
                  widget_text (IO_CHECK_ROW11, IO_Enable[59]);
                  if (!IO_Address[60] && !IO_Enable[60]) widget_text (IO_INPUT_ROW12, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW12, trim(IO_Address[60]));
                  widget_text (IO_CHECK_ROW12, IO_Enable[60]);   
                  
                  RefreshIOGrayOut(SCREEN_IOCFG_OUT2, 12,48);
                                                                                                                                                       
                break;
     
     case SCREEN_IOCFG_OUT3 :    
                // First Column   
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "3", space(1), TX_FSLASH, space(1), "4"));                            
                  if (!IO_Address[61] && !IO_Enable[61]) widget_text (IO_INPUT_ROW1, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW1, trim(IO_Address[61]));
                  widget_text (IO_CHECK_ROW1, IO_Enable[61]);
                  if (!IO_Address[62] && !IO_Enable[62]) widget_text (IO_INPUT_ROW2, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW2, trim(IO_Address[62]));
                  widget_text (IO_CHECK_ROW2, IO_Enable[62]);
                  if (!IO_Address[63] && !IO_Enable[63]) widget_text (IO_INPUT_ROW3, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW3, trim(IO_Address[63]));
                  widget_text (IO_CHECK_ROW3, IO_Enable[63]);
                  if (!IO_Address[64] && !IO_Enable[64]) widget_text (IO_INPUT_ROW4, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW4, trim(IO_Address[64]));
                  widget_text (IO_CHECK_ROW4, IO_Enable[64]);
                  if (!IO_Address[65] && !IO_Enable[65]) widget_text (IO_INPUT_ROW5, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW5, trim(IO_Address[65]));
                  widget_text (IO_CHECK_ROW5, IO_Enable[65]);
                  if (!IO_Address[66] && !IO_Enable[66]) widget_text (IO_INPUT_ROW6, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW6, trim(IO_Address[66]));
                  widget_text (IO_CHECK_ROW6, IO_Enable[66]);
   
                // Second Column                               
                  if (!IO_Address[67] && !IO_Enable[67]) widget_text (IO_INPUT_ROW7, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW7, trim(IO_Address[67]));
                  widget_text (IO_CHECK_ROW7, IO_Enable[67]);
                  if (!IO_Address[68] && !IO_Enable[68]) widget_text (IO_INPUT_ROW8, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW8, trim(IO_Address[68]));
                  widget_text (IO_CHECK_ROW8, IO_Enable[68]);
                  if (!IO_Address[69] && !IO_Enable[69]) widget_text (IO_INPUT_ROW9, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW9, trim(IO_Address[69]));
                  widget_text (IO_CHECK_ROW9, IO_Enable[69]);
                  if (!IO_Address[70] && !IO_Enable[70]) widget_text (IO_INPUT_ROW10, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW10, trim(IO_Address[70]));
                  widget_text (IO_CHECK_ROW10, IO_Enable[70]);
                  if (!IO_Address[71] && !IO_Enable[71]) widget_text (IO_INPUT_ROW11, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW11, trim(IO_Address[71]));
                  widget_text (IO_CHECK_ROW11, IO_Enable[71]);
                  if (!IO_Address[72] && !IO_Enable[72]) widget_text (IO_INPUT_ROW12, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW12, trim(IO_Address[72]));
                  widget_text (IO_CHECK_ROW12, IO_Enable[72]);  
                  
                                  
                  RefreshIOGrayOut(SCREEN_IOCFG_OUT3, 12,60);
                                                                                                                                                        
                break;
      
      case SCREEN_IOCFG_OUT4 :    
                // First Column   
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTCONFIG_PAGE),space(5), "4", space(1), TX_FSLASH, space(1), "4"));
                                             
                  if (!IO_Address[73] && !IO_Enable[73]) widget_text (IO_INPUT_ROW1, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW1, trim(IO_Address[73]));
                  widget_text (IO_CHECK_ROW1, IO_Enable[73]);
                  
                  if (!IO_Address[74] && !IO_Enable[74]) widget_text (IO_INPUT_ROW2, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW2, trim(IO_Address[74]));
                  widget_text (IO_CHECK_ROW2, IO_Enable[74]);
                  
                  if (!IO_Address[75] && !IO_Enable[75]) widget_text (IO_INPUT_ROW3, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW3, trim(IO_Address[75]));
                  widget_text (IO_CHECK_ROW3, IO_Enable[75]);
                  
                  if (!IO_Address[76] && !IO_Enable[76]) widget_text (IO_INPUT_ROW4, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW4, trim(IO_Address[76]));
                  widget_text (IO_CHECK_ROW4, IO_Enable[76]);
                  
                  if (!IO_Address[77] && !IO_Enable[77]) widget_text (IO_INPUT_ROW5, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW5, trim(IO_Address[77]));
                  widget_text (IO_CHECK_ROW5, IO_Enable[77]);
                  
                  if (!IO_Address[78] && !IO_Enable[78]) widget_text (IO_INPUT_ROW6, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW6, trim(IO_Address[78]));
                  widget_text (IO_CHECK_ROW6, IO_Enable[78]);
   
                // Second Column                               
                  if (!IO_Address[79] && !IO_Enable[79]) widget_text (IO_INPUT_ROW7, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW7, trim(IO_Address[79]));
                  widget_text (IO_CHECK_ROW7, IO_Enable[79]);
                  
                  if (!IO_Address[80] && !IO_Enable[80]) widget_text (IO_INPUT_ROW8, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW8, trim(IO_Address[80]));
                  widget_text (IO_CHECK_ROW8, IO_Enable[80]);
                  
                  if (!IO_Address[81] && !IO_Enable[81]) widget_text (IO_INPUT_ROW9, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW9, trim(IO_Address[81]));
                  widget_text (IO_CHECK_ROW9, IO_Enable[81]);
                  
                  if (!IO_Address[82] && !IO_Enable[82]) widget_text (IO_INPUT_ROW10, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW10, trim(IO_Address[82]));
                  widget_text (IO_CHECK_ROW10, IO_Enable[82]);
                  
                  if (!IO_Address[83] && !IO_Enable[83]) widget_text (IO_INPUT_ROW11, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW11, trim(IO_Address[83]));
                  widget_text (IO_CHECK_ROW11, IO_Enable[83]);
                  
                  if (!IO_Address[84] && !IO_Enable[84]) widget_text (IO_INPUT_ROW12, lsub(TX_IO_NULL));
                  else widget_text (IO_INPUT_ROW12, trim(IO_Address[84]));
                  widget_text (IO_CHECK_ROW12, IO_Enable[84]);  
                  
                  // Force a widget enable scan for Flexible IO button in GoTo page
                  ButtonDisplayRefreshed[SCREEN_GOTO] = OFF;
                  
                  RefreshIOGrayOut(SCREEN_IOCFG_OUT4, 12,72);
                                                                                                                                                        
                break;          
                             
  }

 enddraw();           
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : WriteIOTableDB
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2017/04
--  
--  Purpose           : Copy the entire database
--                    ; 
--                      
--  Value Parameters  :
--  Variable Params   : none  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void WriteIOTableDB (void)           
{
int   i, err;

    for (i=0; i<MAX_IO; i++)
    {
      IOdb.No  = IO_No[i+1];
      IOdb.Name = IO_NameEn[i+1];
      IOdb.Input = IO_Input[i+1];
      IOdb.Enable = IO_Enable[i+1];
      IOdb.Address = IO_Address[i+1];
      err=insert(IOdb);
    }
} 

/*------------------------------------------------------------------------- 
--  Procedure Name    : LoadIOTableDB
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Load IO table from DBase
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void LoadIOTableDB (void) 
{
int   i, err;
bool Updatedb;


   

// Clear IO Tables
   for (i=0; i<=MAX_IO; i++)
   {
      IO_No[i] = 0;
      IO_Address[i] = 0;
      IO_Enable[i] = 0;
      IO_Input[i] = 0;
   }   

   
   
   IOdb.No=0;
   for (i=0; i<=MAX_IO; i++)
   {
 
 
//     err = (findnext(IOdb));

     if (findnext(IOdb)==0)
     {
      IO_No[i+1] = IOdb.No;
      IO_Address[i+1] = IOdb.Address;
      IO_Enable[i+1] = IOdb.Enable;
      IO_Input[i+1] = IOdb.Input;
      if(IOdb.Name != IO_NameEn[i+1])
       {
        IOdb.Address = IO_Address[i+1];
        IOdb.Enable = IO_Enable[i+1];
        IOdb.Input = IO_Input[i+1];
        IOdb.Name = IO_NameEn[i+1];
        err = insert(IOdb);
       }
            
      
      
        /* Verify and disable I/O if address # is over Maximum IOs configured */
        if (IO_Address[i+1] > MaxNumbOfIO)
        {
          IO_Address[i+1] = 0;
          IO_Enable[i+1]  = OFF;
          Updatedb = ON;
        }
      
      
     }
     IO_No[i] = IO_No[0]+i; 
   }    

   if (Updatedb) WriteIOTableDB();

}

/*------------------------------------------------------------------------- 
--  Procedure Name    : WriteIOSingleEntryDB
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Write into a single entry of the database
--                      
--  Value Parameters  :
--  Variable Params   : pointer = IOdb.No, value = value to input, db =  
--  Side Effects      : 
--------------------------------------------------------------------------*/
void WriteIOSingleEntryDB (int pointer, string value, int type, bool db)
{
int     Temp_Enable, err;
decimal Temp_Address %2.0;

//        IOdb.No = (value)-IO_CHECKBOX_MARKER;
        IOdb.Name = IO_NameEn[pointer];
        IOdb.Input= IO_Input[pointer];
        Temp_Enable = IO_Enable[pointer];
        Temp_Address = IO_Address[pointer];
        if (Temp_Enable != decimal (value) && type==CheckBox) 
         {
          IOdb.Enable = int (value);
         }
        else
         {
          IOdb.Enable = IO_Enable[pointer];
         } 
        if (Temp_Address != decimal (value) && type==InputBox) 
         {
          IOdb.Address = decimal (value);
         }
        else
         {
          if (IOdb.Enable == 0)
          {
            IOdb.Address = 0;
          }
          else IOdb.Address = IO_Address[pointer];
         }   
        if (db) err=insert(IOdb); else IO_Change = ON;
        LoadIOTableDB ();    
} 


/*------------------------------------------------------------------------- 
--  Procedure Name    : IOFillDb_Init
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/11
--  
--  Purpose           : Fill IO Database at startup to avoid empty Db
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void IOFillDb_Init (void)
{
int   i, err, MaxArrayIOTemp;
bool  rebuildIOdb,IOsActive;

   MaxArrayIOTemp= records(IOdb);
   IOsActive = OFF;


// Fill IO missing Tables
   if(MaxArrayIOTemp != MAX_IO) 
    {
     rebuildIOdb = ON;
    }
   else
    { 
     for (i=1; i<=MAX_IO; i++)
     {
      IOdb.No = i;
      if(!find(IOdb))
      {
        if(IOdb.Enable) IOsActive = ON;
        if((i<=NUMBEROFINPUTS && IOdb.Input ==ON) || (i>NUMBEROFINPUTS && IOdb.Input ==OFF))
        {
         rebuildIOdb = OFF;
        }
        else 
        {  
         rebuildIOdb = ON;
         break;
        }
      } 
      else 
      {  
      rebuildIOdb = ON;
      break;
      }
     }
    }
     
   if(rebuildIOdb || !IOsActive)
   {
    DbDamaged.IO = ON;
    clear(IOdb);
    for (i=1; i<=MAX_IO; i++)
     {
      IOdb.No = i;
      IOdb.Name = IO_NameEn[i];
      if (i<=NUMBEROFINPUTS) IOdb.Input = ON;
      else IOdb.Input = OFF;  
      IOdb.Enable = OFF;
      IOdb.Address = 0;
      err=insert(IOdb); 
     }
   }  
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateIOConfigPages
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O Config Pages Manager 
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateIOConfigPages(void) 
{
    CreateInputConfigPage1();
    CreateInputConfigPage2();
    CreateInputConfigPage3();
    CreateOutputConfigPage1();
    CreateOutputConfigPage2();
    CreateOutputConfigPage3();
    CreateOutputConfigPage4();
}

//Flex IO Timer Preset setting
void FlexIO_SetTPresets(void)
{
int i,j;
/* Flex IO Timer Presets */
    for (i=0; i<MAX_FLEXIO; i++)  
    {
      for (j=0; j<Flex_Out3; j++) 
      {  
       
       if(i<Flex_Out3)
       {  
        switch (FlexIO_Timer[i][j])
        {
          case WP_Flex1_TPre: if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_ON] ) T_PRE[T_FlexOut1On]=  WP.FlexT1; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_OFF]) T_PRE[T_FlexOut1Off]= WP.FlexT1; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_ON])  T_PRE[T_FlexOut2On]=  WP.FlexT1; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_OFF]) T_PRE[T_FlexOut2Off]= WP.FlexT1;                      
                break;
          case WP_Flex2_TPre: if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_ON])  T_PRE[T_FlexOut1On]=  WP.FlexT2; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_OFF]) T_PRE[T_FlexOut1Off]= WP.FlexT2; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_ON])  T_PRE[T_FlexOut2On]=  WP.FlexT2; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_OFF]) T_PRE[T_FlexOut2Off]= WP.FlexT2;                      
                break;
          case MP_Flex1_TPre: if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_ON])  T_PRE[T_FlexOut1On]=  MP.FlexT1; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_OFF]) T_PRE[T_FlexOut1Off]= MP.FlexT1; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_ON])  T_PRE[T_FlexOut2On]=  MP.FlexT1; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_OFF]) T_PRE[T_FlexOut2Off]= MP.FlexT1;                      
                break;
          case MP_Flex2_TPre: if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_ON])  T_PRE[T_FlexOut1On]=  MP.FlexT2; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_OFF]) T_PRE[T_FlexOut1Off]= MP.FlexT2; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_ON])  T_PRE[T_FlexOut2On]=  MP.FlexT2; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_OFF]) T_PRE[T_FlexOut2Off]= MP.FlexT2;                      
                break; 
          default:            if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_ON])  T_PRE[T_FlexOut1On]=  0; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out1][FlexOutput_OFF]) T_PRE[T_FlexOut1Off]= 0; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_ON])  T_PRE[T_FlexOut2On]=  0; 
                              if (FlexIO_Timer[i][j] == FlexIO_Timer[Flex_Out2][FlexOutput_OFF]) T_PRE[T_FlexOut2Off]= 0;                      
                break;                 
        }
        
        /* Flex IO Setpoints */
        switch (FlexIO_SP[i][j])
        {
          case WP_Flex1_SP: if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = WP.FlexSP1; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = WP.FlexSP1;  
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = WP.FlexSP1;
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = WP.FlexSP1;                      
                break;
          case WP_Flex2_SP: if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = WP.FlexSP2; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = WP.FlexSP2; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = WP.FlexSP2; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = WP.FlexSP2;                      
                break;
          case MP_Flex1_SP: if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = MP.FlexSP1; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = MP.FlexSP1; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = MP.FlexSP1; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = MP.FlexSP1;                     
                break;
          case MP_Flex2_SP: if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = MP.FlexSP2; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out1][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = MP.FlexSP2; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_ON])  
                               FlexIO_SP_Pre[i][j] = MP.FlexSP2; 
                            if (FlexIO_SP[i][j] == FlexIO_SP[Flex_Out2][FlexOutput_OFF]) 
                               FlexIO_SP_Pre[i][j] = MP.FlexSP2;                      
                break;                            
        }
       }
        
        if (i == Flex_Out3 && j == FlexOutput_ON)
        {

            T_PRE[T_FlexOut3OnTime]=     FlexIO_OnTime[i][FlexOutput_ON];
            T_PRE[T_FlexOut3InitOn]=     FlexIO_InitDelay[i][FlexOutput_ON];
            T_PRE[T_FlexOut3OffTime]=    FlexIO_OffTime[i][FlexOutput_ON]; 
           
          switch (FlexIO_CntPreSource[Flex_Out3][FlexOutput_ON])
          {           
            case WP_Flex_Counter:  FlexCNT_PRE =  WP.FlexCounter;                     
                break;         
            case MP_Flex_Counter:  FlexCNT_PRE =  MP.FlexCounter;                     
                break;
          
          }
          
        } 
        
//        FlexIO_CntMode[i][ON]   = FlexIO.CntMode; 
//        FlexIO_CntPreSource[i][ON] = FlexIO.CntPreSource;
        
      }
    }
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : FlexFillDb_Init
--  Created by        : Steve Santerre
--  Last modified on  : 2018/12
--  
--  Purpose           : Fill Flex Database at startup to avoid empty Db
--                      & Invalid .No
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void FlexFillDb_Init(void)
{
  int   i;
  bool  FlexRecordExist[4];
   
   do
    if(FlexIO.No < 1 || FlexIO.No > 3)
     {
      delete(FlexIO);
      if(FlexIO.No != 0) 
       DbDamaged.Flex = ON;
     }
    else
     {  
      FlexRecordExist[FlexIO.No] = ON;
     }
   while(!findnext(FlexIO));
  
  for(i=1;i<=3;i++)
   {
    if(!FlexRecordExist[i])
     {
      FlexIO.No = i;
      insert(FlexIO);
      DbDamaged.Flex = ON;
     }
   }
}       


/*------------------------------------------------------------------------- 
--  Procedure Name    : MoveFlexIoDbs2Vars
--  Created by        : Jean-Pierre DorÃ©
--  Last modified on  : 2016/05
--  
--  Purpose           : Move Flex IO database to global variables for simpler                        
--                      internal processing
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void MoveFlexIoDbs2Vars (void)
{
int   i, err, FlexIO_No_Mem;

   FlexIO_No_Mem = FlexIO.No;
   MaxArrayFlexIODbase= records(FlexIO);

   for (i=0; i<MaxArrayFlexIODbase; i++)
   { 
      FlexIO.No = i+1;
      find_db (FlexIO_Db);
       
      // Output ON
      FlexIO_Type[i][FlexOutput_ON]         = FlexIO.TypeOn;
      FlexIO_SPSign[i][FlexOutput_ON]       = FlexIO.SPSignOn;  
      FlexIO_SP[i][FlexOutput_ON]           = FlexIO.SPOn;                  
      FlexIO_IO[i][FlexOutput_ON]           = FlexIO.IoOn;
      FlexIO_IOEnum[i][FlexOutput_ON]       = FlexIO.IoEnumOn;
      FlexIO_Valid[i][FlexOutput_ON]        = FlexIO.IoOnOk;
      FlexIO_IoSwitch[i][FlexOutput_ON]     = FlexIO.IoSwOn; 
      FlexIO_Timer[i][FlexOutput_ON]        = FlexIO.TOn;                              
      FlexIO_Output[i][FlexOutput_ON]       = OFF;
      FlexIO_CntMode[i][FlexOutput_ON]      = FlexIO.CntMode; 
      FlexIO_CntPreSource[i][FlexOutput_ON] = FlexIO.CntPreSource;
      
      if (i == Flex_Out3)
      { 
        FlexIO_InitDelay[i][FlexOutput_ON] = FlexIO.InitDelay; 
        FlexIO_OnTime[i][FlexOutput_ON]    = FlexIO.OnTime;
        FlexIO_OffTime[i][FlexOutput_ON]   = FlexIO.OffTime;
      }  


      switch (i)
      {
       case 0: FlexIO_IONameON[i] = FlexIO.IoNameOn;
              break;
       case 1: FlexIO_IONameON[i] = FlexIO.IoNameOn;  
              break;  
      }  
                         
      // Output OFF
      FlexIO_Type[i][FlexOutput_OFF]      = FlexIO.TypeOff;
      FlexIO_SPSign[i][FlexOutput_OFF]    = FlexIO.SPSignOff; 
      FlexIO_SP[i][FlexOutput_OFF]        = FlexIO.SPOff;     
      FlexIO_IO[i][FlexOutput_OFF]        = FlexIO.IoOff;
      FlexIO_IOEnum[i][FlexOutput_OFF]    = FlexIO.IoEnumOff; 
      FlexIO_Valid[i][FlexOutput_OFF]     = FlexIO.IoOffOk;  
      FlexIO_IoSwitch[i][FlexOutput_OFF]  = FlexIO.IoSwOff;
      FlexIO_Timer[i][FlexOutput_OFF]     = FlexIO.TOff;
      FlexIO_Output[i][FlexOutput_OFF]    = OFF;

      switch (i)
      {
       case 0: FlexIO_IONameOFF[i] = FlexIO.IoNameOff; 
              break;
       case 1: FlexIO_IONameOFF[i] = FlexIO.IoNameOff;
              break;
      }  
   }
   FlexIO.No = FlexIO_No_Mem; 
   FlexIO_SetTPresets();  

}

/* *********************************************************************** */
/*                                                                         */
/*   IO_Test.c section placed here for testing                             */
/*                                                                         */
/* *********************************************************************** */



/*----------------------------------------------------------------------------------
-- File Name: IO_Test.c 
--
-- Copyright 2015 PremierTech as an unpublished work. 
-- All Rights Reserved.
--
-- The information contained herein is confidential property of 
-- Premier Tech.  The use, copying, transfer or disclosure of such
-- information is prohibited except by express written agreement with
-- Premier Tech.
--
-- First written in August, 2015 by Jean-Pierre Doré.
--
-- Module Description:
-- This file is dedicated to the creation, display and refresh of the I/O test page. 
-----------------------------------------------------------------------------------*/



/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateIOTestLoop
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Creates the I/O display loop of 6 I/Os per column
--                      
--  Value Parameters  :
--  Variable Params   : MaxRows = # of rows, id = , io_num = , check = , state = , pointer = # of the first of the column, output; True = OUTPUTS, OFF = INPUTS ; 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateIOTestLoop (int MaxButtons, int id, int io_num, int state, int check, int pointer, int margin, bool output )
{
int i;
TEST_ID[0] = string(id);
TEST_VALUE[0] = string(io_num);
TEST_CHECK[0] = string(check);
TEST_STATE[0] = string(state);


 for (i=0; i<MaxButtons; i++)
     {
 
     TEST_ID[i] = TEST_ID[0]+i;
     TEST_POINTER[i] = pointer+i;
     TEST_VALUE[i] = TEST_VALUE[0]+i;
     TEST_CHECK[i] = TEST_CHECK[0]+i;
     TEST_STATE[i] = TEST_STATE[0]+i;

     }

 for (i=0; i<MaxButtons; i++)
     {
      
      beginrow(); // First row 
       if (!output) CreateIOField (TEST_ID[i],    CL_PT_BLUE, CL_PT_WHITE, OFF, IO_Name[TEST_POINTER[i]], FT_IOPAGES_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, margin, widget_unlocked );
       else CreateIOField (TEST_ID[i],    CL_PT_BLUE, CL_PT_WHITE, OFF, IO_Name[TEST_POINTER[i]], FT_IOPAGES_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, margin, widget_unlocked );
       CreateOutputDataField (TEST_VALUE[i], FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, widget_locked);
       CreateIOField (TEST_STATE[i],    CL_PT_BLUE, CL_PT_WHITE, ON, IO_State[TEST_POINTER[i]], FT_IOPAGES_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, margin, widget_unlocked );
       if (output)
       {
         CreateOnOffBoxField (TEST_CHECK[i], 25, WIDGET_TEXT_ALIGN_CENTER, ON, BTN_TESTON, BTN_TESTOFF);
        /* "DORJ2 Toggle IO Test button change on state vs auto toggle On/Off TEST "*/
         widget_attribute (TEST_CHECK[i], WIDGET_ATTRIBUTE_AUTO_CHANGE_STATE, "0");
       }
             
      endrow();
    
     }
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshIOTestLoop
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Refresh I/O test Display Loop
--                      
--  Value Parameters  :
--  Variable Params   : MaxRows = # of rows, id = , io_num = , check = , pointer = Row # where to start, IOpointer = I/O # where to start the loop ; 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshIOTestLoop (int MaxButtons, int id, int io_num, int state, int pointer, int IOpointer )
{
int i;
TEST_ID[0] = string(id);
TEST_VALUE[0] = string(io_num);
TEST_STATE[0] = string(state);

 for (i=pointer; i<(MaxButtons+pointer); i++)
     {
 
     TEST_ID[i] = TEST_ID[0]+i;
     TEST_VALUE[i] = TEST_VALUE[0]+i;
     TEST_STATE[i] = TEST_STATE[0]+i;
     TEST_CHECK[i] = TEST_CHECK[0]+i;

     }

 for (i=pointer; i<(MaxButtons + pointer); i++)
     {
      beginrow(); // First row 
             if (!IO_Address[IOpointer+1] && !IO_Enable[IOpointer+1]) widget_text (TEST_VALUE[i], lsub(TX_IO_NULL));
             else widget_text (TEST_VALUE[i], trim(IO_Address[IOpointer+1])); 

             if ( IO_TestState[IOpointer+1]  ) widget_text (TEST_STATE[i], lsub(TX_IO_ON)); else  widget_text (TEST_STATE[i], lsub(TX_IO_OFF)); 
             if ( IO_Force[IOpointer+1]  ) widget_text (TEST_CHECK[i], ON); else  widget_text (TEST_CHECK[i], OFF); 

           IOpointer = IOpointer + 1;
      endrow();
       
     }
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateInputTestPage1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O INPUT Test page #1
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateInputTestPage1(void) 
{
 int i; 
 
  begindraw();
  createpage(PAGE_IO_INPUTTEST_1);  
  page_background (PAGE_IO_INPUTTEST_1, BackgroundColor);//"white");
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

        beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_INPUTTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
       
          // Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 


            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked ); 
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();          

       CreateIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1, IO_CHECK_ROW1, 1, Left_Margin, Input_Page);
                  
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOTESTINPUT_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked ); 
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();


        CreateIOTestLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_STATE_ROW7,IO_CHECK_ROW7, 7, No_Margin, Input_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #5  // 
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_IOTEST_IN1, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}


/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateInputTestPage2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O INPUT Test page #2
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateInputTestPage2(void) 
{
  begindraw();
  createpage(PAGE_IO_INPUTTEST_2);  
  page_background (PAGE_IO_INPUTTEST_2, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // 
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // 

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_INPUTTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns 
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

      CreateIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,IO_CHECK_ROW1, 13, Left_Margin, Input_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOTESTINPUT_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

       CreateIOTestLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_STATE_ROW7,IO_CHECK_ROW7, 19, No_Margin, Input_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #5  
        
     endlayout(); // End of VBOX #3 // End of left screen VBOX

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);
  
   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_IOTEST_IN2, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateInputTestPage3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O INPUT Test page #3
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateInputTestPage3(void) 
{
  begindraw();
  createpage(PAGE_IO_INPUTTEST_3);  
  page_background (PAGE_IO_INPUTTEST_3, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    // Split screen in weighing in-/outputs and sketch field
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  // Split left screen in in-/outputs and infoline

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_INPUTTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom" 
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

        CreateIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,IO_CHECK_ROW1, 25, Left_Margin, Input_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOTESTINPUT_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

        CreateIOTestLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_STATE_ROW7,IO_CHECK_ROW7, 31, No_Margin, Input_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #5  

        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);

   CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
   DrawNavButtons (SCREEN_IOTEST_IN3, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NEXT, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputTestPage1
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O OUTPUT Test page #1
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputTestPage1(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUTTEST_1);  
  page_background (PAGE_IO_OUTPUTTEST_1, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,IO_CHECK_ROW1, 37, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOTESTOUTPUT_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

            CreateIOTestLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_STATE_ROW7,IO_CHECK_ROW7, 43, No_Margin, Output_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #6  
        
     endlayout(); // End of VBOX #3 
   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_IOTEST_OUT1, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputTestPage2
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O OUTPUT Test page #2
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputTestPage2(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUTTEST_2);  
  page_background (PAGE_IO_OUTPUTTEST_2, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

          CreateIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,IO_CHECK_ROW1, 49, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOTESTOUTPUT_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right 
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

         CreateIOTestLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_STATE_ROW7,IO_CHECK_ROW7, 55, No_Margin, Output_Page);

                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #5  
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1 

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_IOTEST_OUT2, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputTestPage3
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O OUTPUT Test page #3
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputTestPage3(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUTTEST_3);  
  page_background (PAGE_IO_OUTPUTTEST_3, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3 

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

         CreateIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,IO_CHECK_ROW1, 61, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOTESTOUTPUT_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

       CreateIOTestLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_STATE_ROW7,IO_CHECK_ROW7, 67, No_Margin, Output_Page);


                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #5  
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1 

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_IOTEST_OUT3, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateOutputTestPage4
--  Created by        : Steve Santerre
--  Last modified on  : 2018/01/10
--  
--  Purpose           : Create I/O OUTPUT Test page #4
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateOutputTestPage4(void) 
{
  begindraw();
  createpage(PAGE_IO_OUTPUTTEST_4);  
  page_background (PAGE_IO_OUTPUTTEST_4, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3 

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_OUTPUTTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #5
       
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

         CreateIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,IO_CHECK_ROW1, 73, Left_Margin, Output_Page);

                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_IOTESTOUTPUT_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 
        
        // Layout of second column on the right  
           
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IOOUTPUT_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_STATE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_STATE), FT_STANDARD_SIZE, ON, WD_IO_STATE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_CHECK_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_TEST), FT_STANDARD_SIZE, ON, WD_IO_TEST, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();

       CreateIOTestLoop (6, IO_ID_ROW7, IO_INPUT_ROW7, IO_STATE_ROW7,IO_CHECK_ROW7, 79, No_Margin, Output_Page);


                   
          endlayout(); // End of Grid Layout
          
       
        endlayout(); // End of HBOX #5  
        
     endlayout(); // End of VBOX #3 

   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1 

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_IOTEST_OUT4, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

  endlayout();  // End of VBOX #1
  enddraw();
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : RefreshIOTestScreen
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Refresh I/O Test screen display 
--                      
--  Value Parameters  :
--  Variable Params   : Scrn_No = screen number of the page to refresh 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void RefreshIOTestScreen(int Scrn_No)
{
int i;
string liveweight[40];

   scrn_index = 40;
   liveweight = concat(" - ",adj(NetWeight[Scale1],6,DP[Scale1]),WP.Unit," / ",adj(NetWeight[Scale2],6,DP[Scale2]),WP.Unit);
   
 begindraw(); 

  switch (Scrn_No)
  {
    case SCREEN_IOTEST_IN1 :    
                // First Column   
                  widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(2), "1",  TX_FSLASH,  "3",liveweight));
                   RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,0, 0);
  
                // Second Column                                              
                   RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,6, 6);  
                                                                                                                                 
                break;
    
    case SCREEN_IOTEST_IN2 :    
                // First Column    
                  widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(2), "2",  TX_FSLASH,  "3",liveweight));
                   RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,0, 12);
   
                // Second Column                               
                   RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,6, 18); 
                                                                                                                                                  
                break;
                
    case SCREEN_IOTEST_IN3 :    
                // First Column  
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_INPUTTEST_PAGE),space(2), "3",  TX_FSLASH, "3",liveweight));                            
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,0, 24);
   
                // Second Column                               
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,6, 30);
                                                                                                                                      
                break;        
                                                 
    case SCREEN_IOTEST_OUT1 :    
                // First Column  
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(2), "1",  TX_FSLASH,  "4",liveweight));                             
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,0, 36);

                // Second Column                               
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,6, 42); 
                                                                                                                                     
                break;
     
     case SCREEN_IOTEST_OUT2 :    
                // First Column  
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(2), "2",  TX_FSLASH,  "4",liveweight));                             
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,0, 48);
   
                // Second Column                               
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,6, 54); 
                                                                                                                                     
                break;
     
     case SCREEN_IOTEST_OUT3 :    
                // First Column   
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(2), "3",  TX_FSLASH,  "4",liveweight));                           
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,0, 60);
   
                // Second Column                               
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,6, 66); 
                                                                                                                                     
                break;
     
     case SCREEN_IOTEST_OUT4 :    
                // First Column   
                 widget_text (IO_SEARCH_ID, concat(space(1), lsub(TX_OUTPUTTEST_PAGE),space(2), "4",  TX_FSLASH,  "4",liveweight));                           
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,0, 72);
   
                // Second Column                               
                  RefreshIOTestLoop (6, IO_ID_ROW1, IO_INPUT_ROW1, IO_STATE_ROW1,6, 78); 
                                                                                                                                     
                break;           
                             
  }

 enddraw();           
}

/*------------------------------------------------------------------------- 
--  Procedure Name    : CreateIOTestPages
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2015/08/14
--  
--  Purpose           : Create I/O Test Pages Manager 
--                      
--  Value Parameters  :
--  Variable Params   : none 
--  Side Effects      : 
--------------------------------------------------------------------------*/
void CreateIOTestPages(void) 
{
    CreateInputTestPage1();
    CreateInputTestPage2();
    CreateInputTestPage3();
    CreateOutputTestPage1();
    CreateOutputTestPage2();
    CreateOutputTestPage3();
    CreateOutputTestPage4();
}


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

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
   
      beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #3  

       beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (IO_SEARCH_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_ANALOGTEST_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
        setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
       endlayout(); // Header


       // Layout of both IO columns
        beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #6

     
          //  Layout of first column on the left
          beginlayout(LAYOUT_TYPE_GRID, 0,3); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER_LEFT,   CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_ANALOG_INPUT), FT_MEDIUM_SIZE, OFF, WD_IO_ANALOG_NAME2, HT_IO_HEADER, Left_Margin, widget_locked  );
            endrow();
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER1,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_ANALOG_NAME2, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS2, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_VALUE_HEADER1,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_VALUE), FT_STANDARD_SIZE, ON, WD_IO_ANALOG_VALUE2, HT_IO_HEADER, No_Margin, widget_locked );              
            endrow();

            beginrow(); // First row 
              CreateIOField         (IO_ID_ROW1,    CL_PT_BLUE, CL_PT_WHITE, OFF, "AIN1", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME2, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW1, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS2, HT_IO_ADDRESS, widget_locked);
              CreateOutputDataField (IO_STATE_ROW1, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE2, HT_IO_HEADER, widget_locked);
              CreateIOField         (IO_UNIT_ROW1,  CL_PT_BLUE, CL_PT_WHITE, ON, "%", FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT2, HT_IO_HEADER, No_Margin, widget_locked );   
            endrow();
              
            beginrow(); // Second row 
              CreateIOField         (IO_ID_ROW2,    CL_PT_BLUE, CL_PT_WHITE, OFF, "AIN2", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME2, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS2, HT_IO_ADDRESS, widget_locked);
              CreateOutputDataField (IO_STATE_ROW2, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE2, HT_IO_ADDRESS, widget_locked);
              CreateIOField         (IO_UNIT_ROW2,  CL_PT_BLUE, CL_PT_WHITE, ON, "%", FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT2, HT_IO_HEADER, No_Margin, widget_locked );      
            endrow();
            
     
            beginrow(); // Third row 
              CreateIOField         (IO_ID_ROW3,    CL_PT_BLUE, CL_PT_WHITE, OFF, "High resolution", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME2, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW3, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS2, HT_IO_ADDRESS, widget_locked);
              CreateOutputDataField (IO_STATE_ROW3, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE2, HT_IO_ADDRESS, widget_locked);
              CreateIOField         (IO_UNIT_ROW3,  CL_PT_BLUE, CL_PT_WHITE, ON, WP.Unit, FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT2, HT_IO_HEADER, No_Margin, widget_locked );      
            endrow();
            
            beginrow(); // Fourth row 
              CreateIOField         (IO_ID_ROW4,    CL_PT_BLUE, CL_PT_WHITE, OFF, "Loadcell voltage", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME2, HT_IO_HEADER, Left_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW4, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS2, HT_IO_ADDRESS, widget_locked);
              CreateOutputDataField (IO_STATE_ROW4, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ANALOG_VALUE2, HT_IO_ADDRESS, widget_locked);
              CreateIOField         (IO_UNIT_ROW4,  CL_PT_BLUE, CL_PT_WHITE, ON, "mV/V", FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT2, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();
                   
          endlayout();  //End of Grid Layout
          
        // Spacing between columns
          CreateIOField (IO_SPACE_2,       CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_IO_HEADER, OFF, WD_ANALOGTEST_SPACE, HT_IO_HEADER, No_Margin, widget_locked  ); 

        // Layout of second column on the right 
           
          
          beginlayout(LAYOUT_TYPE_GRID, 0,3); // 

            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER_RIGHT,  CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_ANALOG_OUTPUT), FT_MEDIUM_SIZE, OFF, WD_IO_ANALOG_NAME, HT_IO_HEADER, No_Margin, widget_locked  );
            endrow(); 
            
            beginrow(); // Headers
              CreateIOField (IO_ID_HEADER2,       CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_NAME), FT_STANDARD_SIZE, OFF, WD_IO_ANALOG_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_INPUT_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_ADDRESS), FT_STANDARD_SIZE, ON, WD_IO_ADDRESS, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_VALUE_HEADER2,    CL_PT_BLUE, CL_PT_WHITE, ON, lsub(TX_IO_VALUE), FT_STANDARD_SIZE, OFF, WD_IO_ANALOG_VALUE, HT_IO_HEADER, No_Margin, widget_locked );
              CreateIOField (IO_UNIT_HEADER2,     CL_PT_BLUE, CL_PT_WHITE, ON, "", FT_STANDARD_SIZE, OFF, WD_IO_PERCENT, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();
            
            beginrow(); // First row 
              CreateIOField         (IO_ID_ROW7,    CL_PT_BLUE, CL_PT_WHITE, OFF, "AOUT1", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW7, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, widget_locked);
              CreateInputIO         (IO_STATE_ROW7, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 1, lsub(TX_IO_ENTER_ANALOG), WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, widget_locked); 
              CreateIOField         (IO_UNIT_ROW7,  CL_PT_BLUE, CL_PT_WHITE, ON, "%", FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT, HT_IO_HEADER, No_Margin, widget_locked );
            endrow();
            
            beginrow(); // Second row 
              CreateIOField         (IO_ID_ROW8,    CL_PT_BLUE, CL_PT_WHITE, OFF, "AOUT2", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW8, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, widget_locked);
              CreateInputIO         (IO_STATE_ROW8, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 1, lsub(TX_IO_ENTER_ANALOG), WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, widget_locked);
              CreateIOField         (IO_UNIT_ROW8,  CL_PT_BLUE, CL_PT_WHITE, ON, "%", FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT, HT_IO_HEADER, No_Margin, widget_locked ); 
            endrow();
            
            beginrow(); // Third row 
              CreateIOField         (IO_ID_ROW9,    CL_PT_BLUE, CL_PT_WHITE, OFF, "AOUT3", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW9, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, widget_locked);
              CreateInputIO         (IO_STATE_ROW9, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 1, lsub(TX_IO_ENTER_ANALOG), WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, widget_locked);
              CreateIOField         (IO_UNIT_ROW9,  CL_PT_BLUE, CL_PT_WHITE, ON, "%", FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT, HT_IO_HEADER, No_Margin, widget_locked );     
            endrow();
            
            beginrow(); // Fourth row 
              CreateIOField         (IO_ID_ROW10,    CL_PT_BLUE, CL_PT_WHITE, OFF, "AOUT4", FT_IOPAGES_SIZE, OFF, WD_IO_ANALOG_NAME, HT_IO_HEADER, No_Margin, widget_locked );
              CreateOutputDataField (IO_INPUT_ROW10, FT_RTC_BOLD, FT_STANDARD_SIZE, WIDGET_TEXT_ALIGN_CENTER, WD_IO_ADDRESS, HT_IO_ADDRESS, widget_locked);
              CreateInputIO         (IO_STATE_ROW10, FT_RTC_BOLD, INPUT_FORMAT_DECIMAL, 5, 1, lsub(TX_IO_ENTER_ANALOG), WD_IO_ANALOG_VALUE, HT_IO_ADDRESS, widget_locked);
              CreateIOField         (IO_UNIT_ROW10,  CL_PT_BLUE, CL_PT_WHITE, ON, "%", FT_IOPAGES_SIZE, OFF, WD_IO_PERCENT, HT_IO_HEADER, No_Margin, widget_locked );    
            endrow();
                   
          endlayout(); // End of Grid Layout       
                 
        endlayout(); // End of HBOX #6  
       
       createwidget (ID_STRETCH, WIDGET_TYPE_STRETCH);  // Set max distance between entries and infoline
        
     endlayout(); // End of VBOX #3 
   
   endlayout();  // End layout of HBOX #2
   
endlayout();  // End layout of Test Layout #1 

   createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_ANALOGTEST, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_PREV, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);     

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
 bool result[2];
 int i;
 string liveweight[40];
 float voltage_mv[2];

   
   if(iQFeedAlgorithmName[Scale1] != IQ_FEEDING_ALGORITHM_NONE) SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_NONE,1);
   if(iQFeedAlgorithmName[Scale2] != IQ_FEEDING_ALGORITHM_NONE) SetiQFeedAlgorithm (IQ_FEEDING_ALGORITHM_NONE,2);
   result[Scale1] = iQGetCurrentVoltage(SCALE_CHANNEL1,SCALE_NUMBER1,voltage_mv[Scale1]);
   result[Scale2] = iQGetCurrentVoltage(SCALE_CHANNEL2,SCALE_NUMBER2,voltage_mv[Scale2]);
   
   liveweight = concat(" - ",adj(NetWeight[Scale1],6,DP[Scale1]),WP.Unit," / ",adj(NetWeight[Scale2],6,DP[Scale2]),WP.Unit);
   
 begindraw(); 
                                                        
                widget_text (IO_SEARCH_ID, concat(lsub(TX_ANALOGTEST_PAGE),liveweight));
                
                // Analog Input 
                  // Analog Input 
                  if(AINActive[AIO1]) AINValue[AIO1] = ActuatorPosition[Scale1]; //ain(AIO1);
                  else                AINValue[AIO1] = 0.0;
                  
                  if(AINActive[AIO2]) AINValue[AIO2] = ActuatorPosition[Scale2]; //ain(AIO2);
                  else                AINValue[AIO2] = 0.0; 
                   
                  widget_text   (IO_INPUT_ROW1, "1");
                  widget_enable (IO_INPUT_ROW1, OFF);
                  widget_text   (IO_STATE_ROW1, trim(AINValue[AIO1]));
                  widget_enable (IO_STATE_ROW1, OFF);
                  
                  widget_text   (IO_INPUT_ROW2, "2");
                  widget_enable (IO_INPUT_ROW2, OFF);
                  widget_text   (IO_STATE_ROW2, trim(AINValue[AIO2]));
                  widget_enable (IO_STATE_ROW2, OFF);

                  widget_text   (IO_INPUT_ROW3, adj(NetWeightHiRes[Scale1],6,DP[Scale1]+1));
                  widget_enable (IO_INPUT_ROW3, OFF);
                  widget_text   (IO_STATE_ROW3, adj(NetWeightHiRes[Scale2],6,DP[Scale2]+1));
                  widget_enable (IO_STATE_ROW3, OFF);
                  widget_text   (IO_UNIT_ROW3,  WP.Unit);
                  widget_enable (IO_UNIT_ROW3,  OFF);
                  
                  widget_text   (IO_INPUT_ROW4, adj(voltage_mv[Scale1],7,5));
                  widget_enable (IO_INPUT_ROW4, OFF);
                  widget_text   (IO_STATE_ROW4, adj(voltage_mv[Scale2],7,5));
                  widget_enable (IO_STATE_ROW4, OFF);
                  
                // Analog Output                               
                  
                  widget_text (IO_INPUT_ROW7, "1");
                  widget_enable (IO_INPUT_ROW7,  AOUTActive[AIO1]);
                  widget_text (IO_STATE_ROW7, trim(AOUTPreset[AIO1]));
                  widget_enable (IO_STATE_ROW7,  AOUTActive[AIO1]);
                  
                  widget_text   (IO_INPUT_ROW8, "2");
                  widget_enable (IO_INPUT_ROW8,  AOUTActive[AIO2]);
                  widget_text (IO_STATE_ROW8, trim(AOUTPreset[AIO2]));
                  widget_enable (IO_STATE_ROW8,  AOUTActive[AIO2]);
                  
                  widget_text   (IO_INPUT_ROW9, "3");
                  widget_enable (IO_INPUT_ROW9,  AOUTActive[AIO3]);
                  widget_text (IO_STATE_ROW9, trim(AOUTPreset[AIO3]));
                  widget_enable (IO_STATE_ROW9,  AOUTActive[AIO3]);
                  
                  widget_text   (IO_INPUT_ROW10, "4");
                  widget_enable (IO_INPUT_ROW10,  AOUTActive[AIO4]);
                  widget_text (IO_STATE_ROW10, trim(AOUTPreset[AIO4]));
                  widget_enable (IO_STATE_ROW10,  AOUTActive[AIO4]);
                  
                  if(AOUTActive[AIO1]) aout(AIO1,AOUTPreset[AIO1]);
                  if(AOUTActive[AIO2]) aout(AIO2,AOUTPreset[AIO2]);
                  if(AOUTActive[AIO3]) aout(AIO3,AOUTPreset[AIO3]);
                  if(AOUTActive[AIO4]) aout(AIO4,AOUTPreset[AIO4]);
                 
 enddraw();           
}

void StopAnalogOut(void)
{     
   AOUTPreset[AIO1] = 0.0;
   AOUTPreset[AIO2] = 0.0;
   AOUTPreset[AIO3] = 0.0;
   AOUTPreset[AIO4] = 0.0;
   if(AOUTActive[AIO1]) aout(AIO1,AOUTPreset[AIO1]);
   if(AOUTActive[AIO2]) aout(AIO2,AOUTPreset[AIO2]);
   if(AOUTActive[AIO3]) aout(AIO3,AOUTPreset[AIO3]);
   if(AOUTActive[AIO4]) aout(AIO4,AOUTPreset[AIO4]);
}



/* *********************************************************************** */
/*                                                                         */
/*   Create Fault page                                                     */
/*                                                                         */
/* *********************************************************************** */

void CreateFaultPage(void) 
{
int i;
begindraw();
  createpage(PAGE_FAULT);  
  page_background (PAGE_FAULT, BackgroundColor);

  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

beginlayout(LAYOUT_TYPE_VBOX, 0); //Test Layout #1 

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    
    

        beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (FAULT_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_FAULT_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked);  

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
         setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
        endlayout(); // Header
  
  
    endlayout(); // End of HBOX #2    
      


      beginlayout(LAYOUT_TYPE_HBOX, 0);
    
    
        beginlayout(LAYOUT_TYPE_VBOX, 0); 
            
            CreateHeader          (FAULT_LINE_HEADER, WD_FAULTLINE_HEADER, HT_FAULT_HEADER, "", align_vcenter, concat (space(FAULT_DETAIL_SPACE), lsub(TX_FAULT_DETAILS)) , HT_FAULT_TEXT, widget_locked);
            widget_content_margins (FAULT_LINE_HEADER, 2,0,0,0);  
            widget_background     (FAULT_LINE_HEADER,  CL_PT_BLUE );
            widget_foreground     (FAULT_LINE_HEADER,  CL_PT_WHITE);
            widget_size_policy    (FAULT_LINE_HEADER,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
            
            for (i=FAULT_LINE1; i<(FAULT_LINE1+FltDispLines); i++)
            {            
              CreateHeader        (i, WD_FAULTLINE_HEADER, HT_FAULT_MESSAGE, "", align_vcenter, "" , HT_FAULT_MESSAGETEXT, widget_locked);
              widget_content_margins (i, 2,0,0,0);
              widget_size_policy  (i,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
            }
    
        endlayout(); 
          
          
        beginlayout(LAYOUT_TYPE_VBOX, 0); 
          
            CreateHeader          (FAULT_TIME_HEADER,  WD_FAULTTIME_HEADER, HT_FAULT_HEADER, "", align_vcenter, concat (space(FAULT_TIME_SPACE),lsub(TX_FAULT_DATE)) , HT_FAULT_TEXT, widget_locked);  
            widget_background     (FAULT_TIME_HEADER,  CL_PT_BLUE );
            widget_foreground     (FAULT_TIME_HEADER,  CL_PT_WHITE);
            widget_size_policy    (FAULT_TIME_HEADER,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
    
            for (i=FAULT_TIME1; i<(FAULT_TIME1+FltDispLines); i++)
            {       
              CreateHeader        (i, WD_FAULTTIME_HEADER, HT_FAULT_MESSAGE, "", align_vcenter, "" , HT_FAULT_MESSAGETEXT, widget_locked);
              widget_size_policy  (i,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);    
            }
    
        endlayout(); 
      
      endlayout();       

endlayout();  // End layout of Test Layout #1

    createwidget (0, WIDGET_TYPE_STRETCH);
  
    CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
    DrawNavButtons (SCREEN_FAULT, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_FIRST_PAGE, BTN_PAGE_UP, BTN_PAGE_DOWN, BTN_LAST_PAGE);

  endlayout();  // End of VBOX #1
enddraw();

}




/* *********************************************************************** */
/*                                                                         */
/*       Refresh FAULT screen display                                     */
/*                                                                         */
/* *********************************************************************** */

void RefreshFaultScreenReq(void)
{
   RefreshFaultScreenFlag = Execute;
}


/* *********************************************************************** */
/*                                                                         */
/*       Refresh FAULT screen display                                     */
/*                                                                         */
/* *********************************************************************** */
void RefreshFaultScreen(void)
{
int i,j,Line_Pos, spacenbr, prespacenbr, tempo;
begindraw();                                
   
            
   j = 0;
   
          if (Fault_Pointer > 99) Fault_Pointer = 0;
          else
          if (Fault_Pointer < 0) Fault_Pointer = FltArrayMax-2;
          else
          
          
          Line_Pos = Fault_Pointer+1;
        
        if (FltLine_Pointer == 0)
        { 
          Line_Pos = Line_Pos+FltLine_Pointer;
        }  
        else
            {
              if ((Fault_Pointer+1)+FltLine_Pointer > 99)
              {
                tempo = ((Fault_Pointer+1)+FltLine_Pointer);
                Line_Pos = tempo - 100;
              }
              else
                  {
                    Line_Pos = Line_Pos+FltLine_Pointer; 
                  }           
            }


  if (FaultMsgTime[Line_Pos] != FaultMsgTimeMem || FS_Flt)
  {
   for (i=FAULT_LINE1; i<(FAULT_LINE1+FltDispLines); i++) 
    {   
    
        if (Line_Pos > 99) Line_Pos = 0;  
        
        prespacenbr = 4;
        spacenbr = 2;
        if (FltLine_Pointer == 0 && j>8 || FltLine_Pointer > 9)  prespacenbr = prespacenbr - 2;
        if (FltLine_Pointer == 90 && j>8)                        prespacenbr = prespacenbr - 2;


        widget_text  (i,  concat (space(prespacenbr),trim(FltLine_Pointer + (j+1)),"." ,space(spacenbr), (FaultMessage[Line_Pos])));     

        widget_text  (i+10,  concat (space(1), (FaultMsgTime[Line_Pos]))); 
        if (j == 0) FaultMsgTimeMem = FaultMsgTime[Line_Pos]; 
        
        if (FaultClrMsg[Line_Pos])       
        { 
          widget_foreground (i,     CL_BLUE);
          widget_foreground (i+10,  CL_BLUE);
        }
        else 
        {
          widget_foreground (i,     CL_PT_BLUE);
          widget_foreground (i+10,  CL_PT_BLUE);
        }  
        j++;
        Line_Pos++;
        FS_Flt = OFF;
    }
  }

enddraw();
}    
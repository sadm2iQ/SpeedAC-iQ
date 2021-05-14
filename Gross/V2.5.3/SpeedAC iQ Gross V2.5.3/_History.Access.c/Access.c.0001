


/* *********************************************** */
/*   Create Combobox selection field               */                                                            
/* *********************************************** */
void CreateSelectPWField (int id, int font_size,int font_face, int width, int height,int sel_1, string text_1, int sel_2, string text_2, int sel_3, string text_3, int sel_4, string text_4)
{
  createwidget(id, WIDGET_TYPE_COMBOBOX);
    widget_size_policy     (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);
    widget_fontsize        (id,  font_size); 
    widget_fontface        (id,  font_face);
    widget_maximum_size    (id,  width, height);
    widget_content_margins (id,  0,0,0,0); 
    
    if ( text_1!="" )
    widget_text         (id,  text_1, sel_1);
    widget_text         (id,  text_2, sel_2);
    widget_text         (id,  text_3, sel_3); 
    widget_text         (id,  text_4, sel_4); 
}

/* *********************************************** */
/*   Create Prompt field                           */                                                            
/* *********************************************** */
void CreatePromptFieldPW(int id, string fg_color, bool bold, string text, int font_size, int width, int height, int margin, int widget_lock )
{
  createwidget(id, WIDGET_TYPE_TEXT_OUTPUT);     
    widget_size_policy  (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);//
    widget_foreground   (id,  fg_color); 
    widget_background   (id,  CL_WHITE);
    widget_fontsize     (id,  font_size); 
    widget_dimensions   (id,  width, height);
  if (widget_lock) widget_maximum_size (id,  width, height);  
    widget_text         (id,  text);
    
  if (bold) widget_fontface  (id,  FT_RTC_BOLD);
  else widget_fontface  (id,  FT_RTC);
  
    widget_content_margins (id, margin,0,0,0);     
}

/* *********************************************** */
/*   Create Input field                            */                                                            
/* *********************************************** */
void CreateInputPWField (int id, int font_size, int font_face, int format, int len, int decs, int width, int height, string text )
{
  createwidget(id, WIDGET_TYPE_TEXT_INPUT);
    widget_fontsize        (id,  font_size); 
    widget_fontface        (id,  font_face);
    widget_format          (id,  format, len, decs);
    widget_label           (id,  text);
    widget_maximum_size    (id,  width, height);
    widget_content_margins (id,  0,0,0,0); 
    widget_size_policy     (id,  SIZE_POLICY_FIXED, SIZE_POLICY_FIXED);

}
/* *********************************************************************** */
/*                                                                         */
/*       Refresh Access screen display                                     */
/*                                                                         */
/* *********************************************************************** */

void RefreshAccessScreen(bool refreshtimeonly)
{
string min[2],hour[2];
       if(date[HH] < 10) hour = concat("0",trim(date[HH]));
       else              hour = trim(date[HH]);
       if(date[MM] < 10) min  = concat("0",trim(date[MM]));
       else              min  = trim(date[MM]);
       
 begindraw();
     
    widget_text   (TDMANAGE_TIME_DISPLAY, concat (space(1),lsub(TX_TDMANAGE_TIME), space(1),hour,":",min) , space(1));
    MinuteInAccess = date[MM];
    
    if(!refreshtimeonly)
    { 
     RefreshCurrentUser();

     if (CurrentLevel < Level_OP)
     {
       widget_set_index  (ACCESS_USER_SELECT, 0,1);
       widget_text       (ACCESS_PW, "");
       AccessButtonSwitch(ON);
       widget_enable     (ACCESS_USER_SELECT, ON);
       widget_enable     (ACCESS_PW, ON);
     } 
    } 
     
 enddraw();  
}

/* *********************************************************************** */
/*                                                                         */
/*   Create Access page                                                     */
/*                                                                         */
/* *********************************************************************** */

void CreateAccessPage(void) 
{
 begindraw();
 createpage(PAGE_ACCESS);  
 page_background (PAGE_ACCESS, BackgroundColor);
  
  beginlayout(LAYOUT_TYPE_VBOX, 0); // VBOX #1

    beginlayout(LAYOUT_TYPE_HBOX, 0); // HBOX #2    

           beginlayout(LAYOUT_TYPE_HBOX, 0); // Header
          CreatePTLogoHeader();
          CreateHeader (ACCESS_ID, WD_PAGE_HEADER, HT_PAGE_HEADER, "", align_hcenter, concat (space(1), lsub(TX_ACCESS_PAGE), space(1)), FT_MEDIUM_SIZE, widget_locked); 

          beginlayout(LAYOUT_TYPE_HBOX, 0);  //HBOX #5   
            CreateModeFltDisplay();
          endlayout();  // End layout of HBOX #5
        setlayoutoption (LAYOUT_OPTION_CONTENT_MARGINS, "0,1,0,0"); //"left,top,right,bottom"
       endlayout(); // Header
     
    endlayout(); // End of HBOX #2
        
    beginlayout(LAYOUT_TYPE_HBOX, 0,3); // HBOX #6
       CreateHeader (BLANK_SPACE,  WD_USERLEVEL, HT_USERLEVEL, "", align_vcenter, "" , FT_MEDIUM_SIZE, widget_locked);
       CreateHeader (TDMANAGE_TIME_DISPLAY, WD_HEADER, HT_HEADER, "", align_hcenter, concat (space(1),/*lsub(TX_TDMANAGE_DATE),space(1), date, space(2),*/lsub(TX_TDMANAGE_TIME),
                     space(1), time , space(1), widget_unlocked), 25, widget_locked );
       CreateHeader (ACCESS_LEVEL, WD_USERLEVEL, HT_USERLEVEL, "", align_vcenter, concat (space(1), lsub(TX_ACCESS_USER),":", space(1) , CurrentUser), FT_SMALL_SIZE, widget_locked);
    endlayout(); //End layout of HBOX #6
 

   beginlayout(LAYOUT_TYPE_HBOX, 0);// VBOX #10
    
    // User combobox line 
    beginlayout(LAYOUT_TYPE_GRID, 0); // HBOX #7
     beginrow(); // First row "Blank" with 2 columns             
      CreatePromptField     (ACCESS_SPACE_3,     CL_PT_BLUE, OFF, "", FT_STANDARD_SIZE, WD_ACCESS_BOX, 12, No_Margin, widget_unlocked);
      CreateOutputTextField (ACCESS_SPACE_4,"", WD_ACCESS_BOX, 12, widget_locked);   
     endrow();
    
     beginrow();
       CreatePromptFieldPW   (ACCESS_USER_ID,    CL_PT_BLUE, ON,                    lsub(TX_USER) , FT_ACCESSPAGE_SIZE, WD_ACCESS_BOX, HT_ACCESS_HEADER, No_Margin, widget_locked);
       widget_text_alignment (ACCESS_USER_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
       widget_content_margins (ACCESS_USER_ID, 0,0,WD_MARGIN,0);
       CreateSelectPWField   (ACCESS_USER_SELECT, FT_ACCESSPAGE_SIZE, FT_RTC_BOLD, WD_ACCESS_BOX, HT_ACCESS_BOX, 0, "", 1, lsub(TX_USER3), 2, lsub(TX_USER2), 3, lsub(TX_USER1) );     
     endrow();

     beginrow();
       CreatePromptFieldPW   (ACCESS_PW_ID,    CL_PT_BLUE, ON,                    lsub(TX_PW) , FT_ACCESSPAGE_SIZE, WD_ACCESS_BOX, HT_ACCESS_HEADER, No_Margin, widget_locked);
       widget_text_alignment (ACCESS_PW_ID,  WIDGET_TEXT_ALIGN_VCENTER_R );
       widget_content_margins (ACCESS_PW_ID, 0,0,WD_MARGIN,0);
       CreateInputPWField    (ACCESS_PW, FT_ACCESSPAGE_SIZE, FT_RTC_BOLD, INPUT_FORMAT_NUMERIC_PASSWORD, 8, 0, WD_ACCESS_BOX, HT_ACCESS_BOX, lsub(TX_PW) ); 
     endrow();
    endlayout();  //End layout of HBOX #8

   endlayout();  //End Layout VBOX #10
         
    beginlayout(LAYOUT_TYPE_HBOX, 0);  // HBOX #9
       CreateSpacingField (ACCESS_SPACE_1, CL_PT_BLUE, FT_STANDARD_SIZE, space(73)); 
       CreateNavigButtons (1, ACCESS_BUTTON_1, ON);                                     
       DrawGenericButtons (SCREEN_ACCESS, ON, 2, ACCESS_BUTTON_1, BTN_NOACCESS ,BTN_ACCESS_OK, BTN_INFO, BTN_NIL_BLUE, BTN_NIL_BLUE, 
                                                                    BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE );
       if (fscan)
       {
         AccessOK = OFF;
         AccessButtonSwitch(ON);
       }
     CreateSpacingField (ACCESS_SPACE_2, CL_PT_BLUE, FT_STANDARD_SIZE, space(73));
     endlayout(); //End layout of HBOX #9

     createwidget (0, WIDGET_TYPE_STRETCH);
  
     CreateNavigButtons (10, NAV_FCT_BUTTON_1, OFF);
     DrawNavButtons (SCREEN_ACCESS, ON, BTN_AUTO, BTN_RECIPE, BTN_REPORT, BTN_NAVIG, BTN_ALARM, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE, BTN_NIL_BLUE);

  endlayout();  // End of VBOX #1
 enddraw();

}

/*------------------------------------------------------------------------------- 
--  Procedure Name    : ButtonDisplayControl
--  Created by        : Jean-Pierre Doré
--  Last modified on  : 2016/02/10
--  
--  Purpose           : Enable/disable widgets for button display purposes 
--                      
--                                
--  Value Parameters  :
--  Variable Params   : Scrn_No: Screen page number to to execute
--  Side Effects      : If not set correctly, some widgets might not display correctly
--------------------------------------------------------------------------------*/  

void ButtonDisplayControl (int Scrn_No)  
{
int Scrn_No_Temp = Scrn_No;
bool BatchEditAllowed;

if (Scrn_No==SCREEN_INFO || Scrn_No==SCREEN_ACCESS || Scrn_No==SCREEN_FAULT) 
    Scrn_No_Temp=SCREEN_MULTIPLE;    
if (Scrn_No==SCREEN_MC3 || Scrn_No==SCREEN_MP3 )
    Scrn_No_Temp=SCREEN_CONFIG;
if (Scrn_No==SCREEN_RECIPE1 || Scrn_No==SCREEN_RECIPE2 || Scrn_No==SCREEN_RECIPE3 || Scrn_No==SCREEN_RECIPE4) 
    Scrn_No_Temp=SCREEN_RECIPES;            

 begindraw();
    switch (Scrn_No_Temp)
    {
      
      case SCREEN_AUTOMATIC :

        if ( CurrentLevel < Level_OP)
        { 
           RecipeButtonSwitch(NAV_FCT_BUTTON_2,   OFF);
           widget_enable(ACTIVE_RECIPE_ID,   OFF);
           ActiveRecipeAllowed = OFF;
           
        }
        else
        {
           RecipeButtonSwitch(NAV_FCT_BUTTON_2,   ON);  
           widget_enable(ACTIVE_RECIPE_ID,   (mode_step == stp_OFF_MODE));
           ActiveRecipeAllowed = (mode_step == stp_OFF_MODE);        
        }
        widget_enable(NAV_FCT_BUTTON_8, (mode_step != stp_OFF_MODE && SeqModeManager != stp_STOP_MODE) && (IO_Enable[O_HopFillReq] || !Input_State(I_LowLevelSensor)));
        
        RefreshRecipeInAutoScreen();
        break;
 
 
        
      case SCREEN_GOTO :
      
        if ( CurrentLevel < Level_PT)
        {
           PageButtonSwitch     (GOTO_PAGE_BUTTON_1, OFF);        
           PageButtonSwitch     (GOTO_PAGE_BUTTON_9, OFF);
        }
        else
        {
           PageButtonSwitch     (GOTO_PAGE_BUTTON_1,  (mode_step == stp_OFF_MODE));        
           PageButtonSwitch     (GOTO_PAGE_BUTTON_9,  (IO_Enable[O_FlexIO_1] || IO_Enable[O_FlexIO_2] || IO_Enable[O_FlexIO_3]));
        }
        
        if ( CurrentLevel < Level_SUP)
        {  
           PageButtonSwitch     (GOTO_PAGE_BUTTON_5, OFF);
           PageButtonSwitch     (GOTO_PAGE_BUTTON_6, OFF);
           PageButtonSwitch     (GOTO_PAGE_BUTTON_10, OFF);
           widget_enable     (GOTO_FCT_BUTTON_10,  OFF);          
        }
        else
        {
           PageButtonSwitch     (GOTO_PAGE_BUTTON_5,  (mode_step == stp_OFF_MODE));
           PageButtonSwitch     (GOTO_PAGE_BUTTON_6, (mode_step == stp_OFF_MODE || mode_step == stp_STOP_MODE));
           PageButtonSwitch     (GOTO_PAGE_BUTTON_10, (mode_step == stp_OFF_MODE));
           widget_enable     (GOTO_FCT_BUTTON_10,  (mode_step == stp_OFF_MODE));

        }
        
        if ( CurrentLevel < Level_OP)
        {
           RecipeButtonSwitch     (NAV_FCT_BUTTON_2,   OFF);
           PageButtonSwitch     (GOTO_PAGE_BUTTON_4, OFF);
           widget_enable     (GOTO_FCT_BUTTON_4,  OFF);  
        }
        else
        {
           RecipeButtonSwitch     (NAV_FCT_BUTTON_2,   ON);
           PageButtonSwitch     (GOTO_PAGE_BUTTON_4, (mode_step == stp_OFF_MODE));
           widget_enable     (GOTO_FCT_BUTTON_4,  WP.FeedAlgoType != FeedStd && WP.FeedAlgoType != FeediQSim );
        }
        
        widget_enable     (GOTO_FCT_BUTTON_6,  (mode_step == stp_OFF_MODE));
        if(!LowLevelManReset)
        {
         widget_image (GOTO_FCT_BUTTON_8, BTN_LOWLEVEL_AUTORESET);
        }
        else 
        {
         widget_image (GOTO_FCT_BUTTON_8, BTN_LOWLEVEL_MANRESET);
        }
        break;
         
        
        
      case SCREEN_MULTIPLE : // SCREEN_MULTIPLE used to combine if Scrn_No==SCREEN_INFO, SCREEN_ACCESS, SCREEN_FAULT or SCREEN_REPORT
           
        if ( CurrentLevel < Level_OP) 
        {
           RecipeButtonSwitch     (NAV_FCT_BUTTON_2, OFF);
        }
        else
        {
           RecipeButtonSwitch     (NAV_FCT_BUTTON_2, ON);
        }
                       
       break;


      case SCREEN_MP1 : //
           
        if ( CurrentLevel < Level_SUP) 
        {
           widget_enable     (NAV_FCT_BUTTON_6, OFF);
        }
        else
        {
           widget_enable     (NAV_FCT_BUTTON_6, (mode_step == stp_OFF_MODE));
        }
                       
       break;        

      case SCREEN_REPORT :

        
        if ( CurrentLevel < Level_OP)
        { 
           RecipeButtonSwitch     (NAV_FCT_BUTTON_2,   OFF);
           
        }
        else
        {
           RecipeButtonSwitch     (NAV_FCT_BUTTON_2,   ON);
          
        }

        widget_enable     (NAV_FCT_BUTTON_6, ON);
              
        break;

      case SCREEN_BATCH : //
           
           BatchEditAllowed = (mode_step == stp_OFF_MODE || mode_step == stp_STOP_MODE);

           widget_enable     (REPORT_BATCHNAME_INPUT,     BatchEditAllowed);
           widget_enable     (REPORT_BATCHPRESET_INPUT,   BatchEditAllowed);
           widget_enable     (REPORT_BATCHDETAILS_INPUT,  BatchEditAllowed);
           widget_enable     (REPORT_BATCHCOUNTALL_INPUT, BatchEditAllowed);
           
           if(BatchEditAllowed)
            {
              widget_style(REPORT_BATCHNAME_INPUT,WPMANAGEBOX_STYLE);
              widget_style(REPORT_BATCHPRESET_INPUT,WPMANAGEBOX_STYLE);
              widget_style(REPORT_BATCHDETAILS_INPUT,WPMANAGEBOX_STYLE);
            }
           
           else
            {
              widget_style(REPORT_BATCHNAME_INPUT,WPMANAGEBOX_STYLE_GRAY);
              widget_style(REPORT_BATCHPRESET_INPUT,WPMANAGEBOX_STYLE_GRAY);
              widget_style(REPORT_BATCHDETAILS_INPUT,WPMANAGEBOX_STYLE_GRAY);
              
            }  
           
           if ( CurrentLevel < Level_OP)
             { 
              RecipeButtonSwitch(NAV_FCT_BUTTON_2,   OFF);
             }
            else
             {
              RecipeButtonSwitch(NAV_FCT_BUTTON_2,   ON);
             }
             
           widget_enable     (NAV_FCT_BUTTON_7, ON);
       break;
  
      case SCREEN_CONFIG :
             
        if ( CurrentLevel < Level_PT)
        {
           widget_enable     (NAV_FCT_BUTTON_10, OFF);
        }
        else
        {
           widget_enable     (NAV_FCT_BUTTON_10, ON);
        }
        
        switch (Scrn_No)
        {
          case SCREEN_MC3:
                                 Access_MCPage3 = Scrn_No;
                               break;
          case SCREEN_MP3: 
                                 Access_MPPage3 = Scrn_No;
                               break;
        }
       break;



      case SCREEN_RECIPES : 
         
   
            widget_enable     (RECIPE_SEARCH_ID,(mode_step == stp_OFF_MODE));
            if((mode_step == stp_OFF_MODE)) widget_background     (RECIPE_SEARCH_ID, CL_PT_BLUE );
            else widget_background(RECIPE_SEARCH_ID, CL_PT_SYSTEC_GRAYOUT ); 
       break;                                           

    }
    
     
 ButtonDisplayRefreshed[Scrn_No] = ON;
 enddraw();
} 

void Logout (int Scrn_No) 
{
     
 begindraw();
     CurrentUser = lsub(TX_NONE);
     CurrentLevel = Level_None;
     Test_PW = 9999999;
     UserForced = OFF;
     widget_set_index       (ACCESS_USER_SELECT, 0,1);
     widget_text       (ACCESS_PW, "");
     AccessButtonSwitch(ON);
     widget_enable     (ACCESS_USER_SELECT, ON);
     widget_enable     (ACCESS_PW, ON);
     KeyLockPTSZI(LAST,LAST,ON,LAST,ON);
     ButtonDisplayControl(SCREEN_ACCESS);
     
     Access_MCPage3 = -1;
     Access_MPPage3 = -1;
     
     Clear_ButtonControlRefreshed();
     
     if (Scrn_No != SCREEN_ACCESS)
     {
      Force_Screen_Req (SCREEN_AUTOMATIC, LARGE) ;
     } 
 enddraw();
}

void ResetTouchScreenTimeout (void ) 
{

 if (AccessTimer_ON)
 { 
  T_EnOff(T_AccessTimeout);
  AccessTimer_ON = OFF;
 }
  
}

//User Login Timeout in Minutes
void StartTimerUser (int UserTimeoutDelay ) 
{
  T_PRE[T_AccessTimeout]= UserTimeoutDelay*60;
  T_EnOn(T_AccessTimeout);
  AccessTimer_ON = ON;
}


void TimeoutUser (void) 
{  

 if (TouchScreenTimerEnable)
 {
  if (TouchScreenTimerEnable && !AccessTimer_ON)
  {
   StartTimerUser(CurrentTimeout);
  } 
   
  if(T_Dn(T_AccessTimeout)) 
  { 
    T_EnOff(T_AccessTimeout);
    AccessTimer_ON = OFF;
    TouchScreenTimerEnable = OFF;
    Logout(Current_Screen);
    RefreshAccessScreen(OFF);
  }
 
 } 
}
 
void Login (void) 
{
int Test_PWmem, PwdPTmem;
// begindraw(); 
         
        Access_PW[2] = iQ_PT_Access ();      
         
         if(Test_No >=0 && Test_No <=2)
         {
          if (Test_No == 2 && Access_PW[Test_No] != Test_PW)
          {
           Test_PWmem = Test_PW;
           PwdPTmem   = Access_PW[Test_No];
          }
         } 
         
         if(Test_No >=0 && Test_No <=2)   
          if (Access_PW[Test_No] == Test_PW) 
          {
            CurrentLevel      = Access_Level[Test_No];
            CurrentTimeout    = Access_Timeout[Test_No];
            if(CurrentTimeout < 1) CurrentTimeout = 1;
            if (Test_No     == 0) CurrentUser  = lsub(TX_USER3);
            if (Test_No     == 1) CurrentUser  = lsub(TX_USER2);
            if (Test_No     == 2) CurrentUser  = lsub(TX_USER1);
            
            if (CurrentLevel > Level_OP) KeyLockPTSZI(LAST,LAST,ON,LAST,OFF);
            
            AccessButtonSwitch(OFF);

            widget_enable     (ACCESS_USER_SELECT, OFF);
            widget_enable     (ACCESS_PW, OFF);
            TouchScreenTimerEnable   = ON;
            StartTimerUser(CurrentTimeout);
            
            Access_MCPage3 = -1;
            Access_MPPage3 = -1;
            
            Clear_ButtonControlRefreshed();
            UserForced = OFF; 
          }             
          else
          {
           AccessButtonSwitch(ON);
           widget_enable     (ACCESS_PW, ON);
           widget_set_index  (ACCESS_USER_SELECT, 0,1);
          }
            Test_PW           = 9999999;
            Test_No           = 0;
            widget_text       (ACCESS_PW, "");
            ButtonDisplayControl(SCREEN_ACCESS);
// enddraw();
}



void ResetUserLogin (void) 
{
 begindraw();
     
     CurrentUser = lsub(TX_NONE);    
     CurrentLevel = Level_None;
     Test_PW = 9999999;
     UserForced = OFF;
     widget_set_index       (ACCESS_USER_SELECT, 0,1);
     widget_text       (ACCESS_PW, "");
     AccessButtonSwitch(ON);
     KeyLockPTSZI(LAST,LAST,ON,LAST,ON);
 enddraw();
}                           
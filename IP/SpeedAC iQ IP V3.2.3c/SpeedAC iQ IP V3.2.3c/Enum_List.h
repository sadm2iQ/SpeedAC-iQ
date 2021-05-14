﻿/*-----------------------------------------------------------------------------
-- File Name: Enum_List.h 
--
-- Copyright 2015 PremierTech as an unpublished work. 
-- All Rights Reserved.
--
-- The information contained herein is confidential property of 
-- Premier Tech.  The use, copying, transfer or disclosure of such
-- information is prohibited except by express written agreement with
-- Premier Tech.
--
-- First written in Febuary, 2015 by Jean-Pierre Doré.
--
-- Module Description:
-- With the enum type specifier. The user can define
-- a fixed set of words that a variable of type enum can take as its value. 
-- The words are assigned integer values by the compiler so that code can 
-- compare enum variables.
------------------------------------------------------------------------------*/

// Create pages
enum
{
   ///////////////////////////////////////////
 //  CALL selectpage and createpage Only  //
///////////////////////////////////////////
  PAGE_DUMMYFIRST=1,
  PAGE_RECIPE_DBASE_LIST,
  PAGE_RECIPE_1,
  PAGE_RECIPE_2,
  PAGE_RECIPE_3,
  PAGE_RECIPE_4,
  PAGE_AUTO,
  PAGE_REPORT,
  PAGE_BATCH,
  PAGE_GOTO,
  PAGE_WPMANAGECOPY,
  PAGE_WPMANAGERENAME,
  PAGE_WPMANAGEDELETE,
  PAGE_INFO,
  PAGE_FAULT,
  PAGE_ACCESS,
  PAGE_IO_INPUT_1,
  PAGE_IO_INPUT_2,
  PAGE_IO_INPUT_3,
  PAGE_IO_OUTPUT_1,
  PAGE_IO_OUTPUT_2,
  PAGE_IO_OUTPUT_3,
  PAGE_IO_INPUTTEST_1,
  PAGE_IO_INPUTTEST_2,
  PAGE_IO_INPUTTEST_3,
  PAGE_IO_OUTPUTTEST_1,
  PAGE_IO_OUTPUTTEST_2,
  PAGE_IO_OUTPUTTEST_3,
  PAGE_MP_1,
  PAGE_MP_2,
  PAGE_MP_3,
  PAGE_MP_4,
  PAGE_MC_1,
  PAGE_MC_2,
  PAGE_MC_3,
  PAGE_MC_4,
  PAGE_FLEXIO_1,
  PAGE_FLEXIO_2,
  PAGE_FLEXIO_3,
  PAGE_FLEXIO_DBASE_LIST,
  PAGE_TDMANAGE,
  YESNO_POPUP_WINDOW,
  CONFIRM_POPUP_WINDOW,
  PRODDATA_POPUP_WINDOW,
  WEIGHINGDATA_POPUP_WINDOW,
  PAGE_LANGUAGE_DBASE_LIST,
  PAGE_REGISTRATION,
  PAGE_DUMMYLAST,
  PAGE_SELECTWRONG,
  PAGE_SELECTTIMEOUT,
  PAGE_GRAPH
  
}

// Widget ID´s for Pages
enum
{
  ID_HEADLINE, 
  ID_STRETCH,
  UNAPPROVED_HEADER,  
  
// Recipe (WP) 
  NAV_FCT_BUTTON_1,
  NAV_FCT_BUTTON_2,
  NAV_FCT_BUTTON_3,
  NAV_FCT_BUTTON_4,
  NAV_FCT_BUTTON_5,
  NAV_FCT_BUTTON_6,
  NAV_FCT_BUTTON_7,
  NAV_FCT_BUTTON_8,
  NAV_FCT_BUTTON_9,
  NAV_FCT_BUTTON_10,

  RECIPE_SEARCH_ID,

// Page 1
  RECIPE_ROW1_ID,
  RECIPE_ROW2_ID,
  RECIPE_ROW3_ID,
  RECIPE_ROW4_ID,
  RECIPE_ROW5_ID,
  RECIPE_ROW6_ID,
  RECIPE_ROW7_ID,
  RECIPE_ROW8_ID,
  RECIPE_ROW9_ID,
  RECIPE_ROW10_ID,
  RECIPE_ROW11_ID,
  RECIPE_ROW12_ID,
// Page 2  
  RECIPE_ROW13_ID,
  RECIPE_ROW14_ID,
  RECIPE_ROW15_ID,
  RECIPE_ROW16_ID,
  RECIPE_ROW17_ID,
  RECIPE_ROW18_ID,
  RECIPE_ROW19_ID,
  RECIPE_ROW20_ID,
  RECIPE_ROW21_ID,
  RECIPE_ROW22_ID,
  RECIPE_ROW23_ID,
  RECIPE_ROW24_ID,
// Page 3  
  RECIPE_ROW25_ID,
  RECIPE_ROW26_ID,
  RECIPE_ROW27_ID,
  RECIPE_ROW28_ID,
  RECIPE_ROW29_ID,
  RECIPE_ROW30_ID,
  RECIPE_ROW31_ID,
  RECIPE_ROW32_ID,
  RECIPE_ROW33_ID,
  RECIPE_ROW34_ID,
  RECIPE_ROW35_ID,
  RECIPE_ROW36_ID,
// Page 4  
  RECIPE_ROW37_ID,
  RECIPE_ROW38_ID,
  RECIPE_ROW39_ID,
  RECIPE_ROW40_ID,
  RECIPE_ROW41_ID,
  RECIPE_ROW42_ID,
  RECIPE_ROW43_ID,
  RECIPE_ROW44_ID,
  RECIPE_ROW45_ID,
  RECIPE_ROW46_ID,
  RECIPE_ROW47_ID,
  RECIPE_ROW48_ID,   

// Page 1  
  RECIPE_ROW1_INPUT,
  RECIPE_ROW2_INPUT,
  RECIPE_ROW3_INPUT,
  RECIPE_ROW4_INPUT,
  RECIPE_ROW5_INPUT,
  RECIPE_ROW6_INPUT,
  RECIPE_ROW7_INPUT,
  RECIPE_ROW8_INPUT,
  RECIPE_ROW9_INPUT,
  RECIPE_ROW10_INPUT,
  RECIPE_ROW11_INPUT,
  RECIPE_ROW12_INPUT,
// Page 2  
  RECIPE_ROW13_INPUT,
  RECIPE_ROW14_INPUT,
  RECIPE_ROW15_INPUT,
  RECIPE_ROW16_INPUT,
  RECIPE_ROW17_INPUT,
  RECIPE_ROW18_INPUT,
  RECIPE_ROW19_INPUT,
  RECIPE_ROW20_INPUT,
  RECIPE_ROW21_INPUT,
  RECIPE_ROW22_INPUT,
  RECIPE_ROW23_INPUT,
  RECIPE_ROW24_INPUT,
// Page 3  
  RECIPE_ROW25_INPUT,
  RECIPE_ROW26_INPUT,
  RECIPE_ROW27_INPUT,
  RECIPE_ROW28_INPUT,
  RECIPE_ROW29_INPUT,
  RECIPE_ROW30_INPUT,
  RECIPE_ROW31_INPUT,
  RECIPE_ROW32_INPUT,
  RECIPE_ROW33_INPUT,
  RECIPE_ROW34_INPUT,
  RECIPE_ROW35_INPUT,
  RECIPE_ROW36_INPUT,
  // Page 4  
  RECIPE_ROW37_INPUT,
  RECIPE_ROW38_INPUT,
  RECIPE_ROW39_INPUT,
  RECIPE_ROW40_INPUT,
  RECIPE_ROW41_INPUT,
  RECIPE_ROW42_INPUT,
  RECIPE_ROW43_INPUT,
  RECIPE_ROW44_INPUT,
  RECIPE_ROW45_INPUT,
  RECIPE_ROW46_INPUT,
  RECIPE_ROW47_INPUT,
  RECIPE_ROW48_INPUT,
  

// Page 1  
  RECIPE_ROW1_SELECT,
  RECIPE_ROW2_SELECT,
  RECIPE_ROW3_SELECT,
  RECIPE_ROW4_SELECT,
  RECIPE_ROW5_SELECT,
  RECIPE_ROW6_SELECT,
  RECIPE_ROW7_SELECT,
  RECIPE_ROW8_SELECT,
  RECIPE_ROW9_SELECT,
  RECIPE_ROW10_SELECT,
  RECIPE_ROW11_SELECT,
  RECIPE_ROW12_SELECT,
// Page 2  
  RECIPE_ROW13_SELECT,
  RECIPE_ROW14_SELECT,
  RECIPE_ROW15_SELECT,
  RECIPE_ROW16_SELECT,
  RECIPE_ROW17_SELECT,
  RECIPE_ROW18_SELECT,
  RECIPE_ROW19_SELECT,
  RECIPE_ROW20_SELECT,
  RECIPE_ROW21_SELECT,
  RECIPE_ROW22_SELECT,
  RECIPE_ROW23_SELECT,
  RECIPE_ROW24_SELECT,
// Page 3  
  RECIPE_ROW25_SELECT,
  RECIPE_ROW26_SELECT,
  RECIPE_ROW27_SELECT,
  RECIPE_ROW28_SELECT,
  RECIPE_ROW29_SELECT,
  RECIPE_ROW30_SELECT,
  RECIPE_ROW31_SELECT,
  RECIPE_ROW32_SELECT,
  RECIPE_ROW33_SELECT,
  RECIPE_ROW34_SELECT,
  RECIPE_ROW35_SELECT,
  RECIPE_ROW36_SELECT,
// Page 4  
  RECIPE_ROW37_SELECT,
  RECIPE_ROW38_SELECT,
  RECIPE_ROW39_SELECT,
  RECIPE_ROW40_SELECT,
  RECIPE_ROW41_SELECT,
  RECIPE_ROW42_SELECT,
  RECIPE_ROW43_SELECT,
  RECIPE_ROW44_SELECT,
  RECIPE_ROW45_SELECT,
  RECIPE_ROW46_SELECT,
  RECIPE_ROW47_SELECT,
  RECIPE_ROW48_SELECT,
  
// Page 1
  RECIPE_ROW1_UNIT,
  RECIPE_ROW2_UNIT,
  RECIPE_ROW3_UNIT,
  RECIPE_ROW4_UNIT,
  RECIPE_ROW5_UNIT,
  RECIPE_ROW6_UNIT,
  RECIPE_ROW7_UNIT,
  RECIPE_ROW8_UNIT,
  RECIPE_ROW9_UNIT,
  RECIPE_ROW10_UNIT,
  RECIPE_ROW11_UNIT,
  RECIPE_ROW12_UNIT,
// Page 2  
  RECIPE_ROW13_UNIT,
  RECIPE_ROW14_UNIT,
  RECIPE_ROW15_UNIT,
  RECIPE_ROW16_UNIT,
  RECIPE_ROW17_UNIT,
  RECIPE_ROW18_UNIT,
  RECIPE_ROW19_UNIT,
  RECIPE_ROW20_UNIT,
  RECIPE_ROW21_UNIT,
  RECIPE_ROW22_UNIT,
  RECIPE_ROW23_UNIT,
  RECIPE_ROW24_UNIT,
// Page 3  
  RECIPE_ROW25_UNIT,
  RECIPE_ROW26_UNIT,
  RECIPE_ROW27_UNIT,
  RECIPE_ROW28_UNIT,
  RECIPE_ROW29_UNIT,
  RECIPE_ROW30_UNIT,
  RECIPE_ROW31_UNIT,
  RECIPE_ROW32_UNIT,
  RECIPE_ROW33_UNIT,
  RECIPE_ROW34_UNIT,
  RECIPE_ROW35_UNIT,
  RECIPE_ROW36_UNIT,
// Page 4  
  RECIPE_ROW37_UNIT,
  RECIPE_ROW38_UNIT,
  RECIPE_ROW39_UNIT,
  RECIPE_ROW40_UNIT,
  RECIPE_ROW41_UNIT,
  RECIPE_ROW42_UNIT,
  RECIPE_ROW43_UNIT,
  RECIPE_ROW44_UNIT,
  RECIPE_ROW45_UNIT,
  RECIPE_ROW46_UNIT,
  RECIPE_ROW47_UNIT,
  RECIPE_ROW48_UNIT,  

  RECIPE_SPACE1,
  ID_RECIPE_DBASE_LIST,


// Test to simplify all enums to a single list  
  SEARCH_ID,
  SPACE_1,
  SPACE_2,
  SPACE_3,
  ROW1_ID,
  ROW1_INPUT,
  ROW1_OUTPUT,
  ROW1_SELECT,
  ROW1_UNIT,
  ROW2_ID,
  ROW2_INPUT,
  ROW2_OUTPUT,
  ROW2_SELECT,
  ROW2_UNIT,
  ROW3_ID,
  ROW3_INPUT,
  ROW3_OUTPUT,
  ROW3_SELECT,
  ROW3_UNIT,
  ROW4_ID,
  ROW4_INPUT,
  ROW4_OUTPUT,
  ROW4_SELECT,
  ROW4_UNIT,
  ROW5_ID,
  ROW5_INPUT,
  ROW5_OUTPUT,
  ROW5_SELECT,
  ROW5_UNIT,
  ROW6_ID,
  ROW6_INPUT,
  ROW6_OUTPUT, 
  ROW6_SELECT, 
  ROW6_UNIT,
  ROW7_ID,
  ROW7_INPUT,
  ROW7_OUTPUT,
  ROW7_SELECT,
  ROW7_UNIT,
  ROW8_ID,
  ROW8_INPUT,
  ROW8_OUTPUT,
  ROW8_SELECT,
  ROW8_UNIT,
  ROW9_ID,
  ROW9_INPUT,
  ROW9_OUTPUT,
  ROW9_SELECT,
  ROW9_UNIT,
  ROW10_ID,
  ROW10_INPUT,
  ROW10_OUTPUT,
  ROW10_SELECT,
  ROW10_UNIT,
  ROW11_ID,
  ROW11_INPUT,
  ROW11_OUTPUT,
  ROW11_SELECT,
  ROW11_UNIT,
  ROW12_ID,
  ROW12_INPUT,
  ROW12_OUTPUT,
  ROW12_SELECT,
  ROW12_UNIT,
   
  ID_STRETCH_1, 
  YESNO_POPUP,
  CONFIRM_POPUP,
  INPUT_POPUP,
  PRODDATA_POPUP,
  PRODDATA_STRING1,
  PRODDATA_STRING2,
  PRODDATA_STRING3,
  PRODDATA_STRING4,
  PRODDATA_STRING5,
  PRODDATA_STRING6,
  PRODDATA_STRING7,
  PRODDATA_STRING8,
  PRODDATA_STRING9,
  WEIGHINGDATA_POPUP,
  WEIGHINGDATA_TITLE_1,
  WEIGHINGDATA_TITLE_SPACE,
  WEIGHINGDATA_STRING1_1,
  WEIGHINGDATA_STRING2_1,
  WEIGHINGDATA_STRING3_1,
  WEIGHINGDATA_STRING4_1,
  WEIGHINGDATA_STRING5_1,
  WEIGHINGDATA_STRING6_1,
  WEIGHINGDATA_STRING7_1,
  WEIGHINGDATA_STRING8_1,
  WEIGHINGDATA_STRING9_1,
  WEIGHINGDATA_STRING10_1,
  YES_BOX,
  NO_BOX,
  EXECUTE_BOX,
  CANCEL_BOX, 
  MODE_BOX,
  LOGO_BOX,
  LOGO_BOX2,
  WECARE_IMAGE,
  FAULT_BOX,
  MESSAGE_DISPLAY,
  HIRESWEIGHT,
  ACTIVE_RECIPE_ID,
  MC_LANGUAGE1_LIST,
  AUTO_ROW1_ID,
  AUTO_ROW1_OUTPUT,
  AUTO_ROW1_UNIT,
  AUTO_ROW2_ID,
  AUTO_ROW2_OUTPUT,
  AUTO_ROW2_UNIT,
  AUTO_ROW3_ID,
  AUTO_ROW3_OUTPUT,
  AUTO_ROW3_UNIT,
  AUTO_ROW4_ID,
  AUTO_ROW4_OUTPUT,
  AUTO_ROW4_UNIT,
  AUTO_ROW5_ID,
  AUTO_ROW5_OUTPUT,
  AUTO_ROW5_UNIT,
  AUTO_ROW11_ID,
  AUTO_ROW11_OUTPUT,
  AUTO_ROW11_UNIT,
  AUTO_ROW12_ID,
  AUTO_ROW12_OUTPUT,
  AUTO_ROW12_UNIT,
  AUTO_ROW13_ID,
  AUTO_ROW13_OUTPUT,
  AUTO_ROW13_UNIT,
  AUTO_ROW14_ID,
  AUTO_ROW14_OUTPUT,
  AUTO_ROW14_UNIT,
  AUTO_ROW15_ID,
  AUTO_ROW15_OUTPUT,
  AUTO_ROW15_UNIT,
  AUTO_ROW21_ID,
  AUTO_ROW21_OUTPUT,
  AUTO_ROW21_UNIT,
  AUTO_ROW22_ID,
  AUTO_ROW22_OUTPUT,
  AUTO_ROW22_UNIT,
  AUTO_ROW23_ID,
  AUTO_ROW23_OUTPUT,
  AUTO_ROW23_UNIT,
  AUTO_ROW24_ID,
  AUTO_ROW24_OUTPUT,
  AUTO_ROW24_UNIT,
  AUTO_ROW25_ID,
  AUTO_ROW25_OUTPUT,
  AUTO_ROW25_UNIT,  
  
  AUTO_ROW75_ID,
  AUTO_ROW76_ID,
  AUTO_ROW77_ID,
  AUTO_ROW78_ID,
  AUTO_SPACE_1,
  AUTO_SPACE_2,
  AUTO_SPACE_3,
  
  REPORT_SPACE_1,
  REPORT_SEARCH_ID,
  REPORT_ROW1_ID,
  REPORT_ROW1_INPUT,
  REPORT_ROW1_UNIT,
  REPORT_ROW2_ID,
  REPORT_ROW2_INPUT,
  REPORT_ROW2_UNIT,
  REPORT_ROW3_ID,
  REPORT_ROW3_INPUT,
  REPORT_ROW3_UNIT,
  REPORT_ROW4_ID,
  REPORT_ROW4_INPUT,
  REPORT_ROW4_UNIT,
  REPORT_ROW5_ID,
  REPORT_ROW5_INPUT,
  REPORT_ROW5_UNIT,
  REPORT_ROW6_ID,
  REPORT_ROW6_INPUT,
  REPORT_ROW6_UNIT,
  REPORT_ROW7_ID,
  REPORT_ROW7_INPUT,
  REPORT_ROW7_UNIT,
  REPORT_ROW8_ID,
  REPORT_ROW8_INPUT,
  REPORT_ROW8_UNIT,
  REPORT_ROW9_ID,
  REPORT_ROW9_INPUT,
  REPORT_ROW9_UNIT,
  REPORT_ROW10_ID,
  REPORT_ROW10_INPUT,
  REPORT_ROW10_UNIT,
  REPORT_ROW11_ID,
  REPORT_ROW11_INPUT,
  REPORT_ROW11_UNIT,
  REPORT_ROW12_ID,
  REPORT_ROW12_INPUT,
  REPORT_ROW12_UNIT,
  REPORT_ROW13_ID,
  REPORT_ROW13_INPUT,
  REPORT_ROW13_UNIT,
  REPORT_ROW14_ID,
  REPORT_ROW14_INPUT,
  REPORT_ROW14_UNIT,
  REPORT_ROW15_ID,
  REPORT_ROW15_INPUT,
  REPORT_ROW15_UNIT,
  REPORT_ROW16_ID,
  REPORT_ROW16_INPUT,
  REPORT_ROW16_UNIT,
  REPORT_BATCHNAME_ID,
  REPORT_BATCHNAME_INPUT,
  REPORT_BATCHNAME_UNIT,
  REPORT_BATCHPRESET_ID,
  REPORT_BATCHPRESET_INPUT,
  REPORT_BATCHPRESET_UNIT,
  REPORT_BATCHDETAILS_ID,
  REPORT_BATCHDETAILS_INPUT,
  REPORT_BATCHDETAILS_UNIT,
  REPORT_BATCHCOUNTALL_ID,
  REPORT_BATCHCOUNTALL_INPUT,
  REPORT_BATCHCOUNTALL_UNIT,
  
  //Registration Page
  REGISTRATION_ROW0_ID,
  REGISTRATION_ROW1_ID,
  REGISTRATION_ROW1_INPUT,
  REGISTRATION_ROW2_ID,
  REGISTRATION_ROW2_INPUT,
  REGISTRATION_BUTTON_1,
  REGISTRATION_SPACE_1,
  
// Access Page  
  ACCESS_ID,
  ACCESS_USER_SELECT,
  ACCESS_USER_ID,
  ACCESS_PW,
  ACCESS_PW_ID,
  ACCESS_LEVEL,
  ACCESS_BUTTON_1,
  ACCESS_BUTTON_2,
  ACCESS_SPACE_1,
  ACCESS_SPACE_2,
  ACCESS_SPACE_3,
  ACCESS_SPACE_4,
  ID_LANGUAGE_DBASE_LIST,
  
  BLANK_SPACE,
  BLANK_SPACE2,
  LANGUAGE_BUTTON1,
  LANGUAGE_BUTTON2,
  LANGUAGE_BUTTON3,
  INFO_ID,
  INFO_USER_ID,
  INFO_USER,
  INFO_PW_ID,
  INFO_PW,
  INFO_SPACE_1,
  INFO_SPACE_2,
  INFO_SPACE_3,
  INFO_BUTTON_1,
  INFO_VERSION,
  INFO_ROW1_ID,
  INFO_ROW1_OUTPUT,
  INFO_ROW1B_ID,
  INFO_ROW2_ID,
  INFO_ROW2_OUTPUT,
  INFO_ROW3_ID,
  INFO_ROW3_OUTPUT,
  INFO_ROW4_ID,
  INFO_ROW4_OUTPUT,
  INFO_ROW5_ID,
  INFO_ROW5_OUTPUT,
  INFO_ROW6_ID,
  INFO_ROW6_OUTPUT,
  INFO_ROW7_ID,
  INFO_ROW7_OUTPUT,
  INFO_ROW8_ID,
  INFO_ROW8_OUTPUT,
  INFO_ROW9_ID,
  INFO_ROW9_OUTPUT,
  INFO_ROW10_ID,
  INFO_ROW10_OUTPUT,
  INFO_ROW11_ID,
  INFO_ROW11_OUTPUT,
  INFO_ROW12_ID,
  INFO_ROW12_OUTPUT,
  INFO_ROW13_ID,
  INFO_ROW13_OUTPUT,
  INFO_ROW14_ID,
  INFO_ROW14_OUTPUT,
  INFO_ROW15_ID,
  INFO_ROW15_OUTPUT,
  INFO_ROW16_ID,
  INFO_ROW16_OUTPUT,
  FAULT_ID,
  FAULT_LINE_HEADER, 
  FAULT_TIME_HEADER,       
  FAULT_LINE1,
  FAULT_LINE2,
  FAULT_LINE3,
  FAULT_LINE4,
  FAULT_LINE5,
  FAULT_LINE6,
  FAULT_LINE7,
  FAULT_LINE8,
  FAULT_LINE9,
  FAULT_LINE10, 
  FAULT_TIME1,
  FAULT_TIME2,
  FAULT_TIME3,
  FAULT_TIME4,
  FAULT_TIME5,
  FAULT_TIME6,
  FAULT_TIME7,
  FAULT_TIME8,
  FAULT_TIME9,
  FAULT_TIME10,
  FAULT_ROW1_ID,

  GOTO_PAGE_BUTTON_1,
  GOTO_PAGE_BUTTON_2,
  GOTO_PAGE_BUTTON_3,
  GOTO_PAGE_BUTTON_4,
  GOTO_PAGE_BUTTON_5,
  GOTO_PAGE_BUTTON_6,
  GOTO_PAGE_BUTTON_7,
  GOTO_PAGE_BUTTON_8,
  GOTO_PAGE_BUTTON_9,
  GOTO_PAGE_BUTTON_10,
  GOTO_FCT_BUTTON_1,
  GOTO_FCT_BUTTON_2,
  GOTO_FCT_BUTTON_3,
  GOTO_FCT_BUTTON_4,
  GOTO_FCT_BUTTON_5,
  GOTO_FCT_BUTTON_6,
  GOTO_FCT_BUTTON_7,
  GOTO_FCT_BUTTON_8,
  GOTO_FCT_BUTTON_9,
  GOTO_FCT_BUTTON_10,
  GOTO_PAGE_HEADER,
  GOTO_FNCT_HEADER,
  GOTO_RECIPE_ID,

  TDMANAGE_TIME_DISPLAY,
  TD_SPACE1,
  TD_SPACE2,
  TDMANAGE_ID,
  TDMANAGE_SPACE_1,
  TDMANAGE_SPACE_2,
  TDMANAGE_SPACE_3,
  TDMANAGE_SPACE_4,
  TDMANAGE_SPACE_5,
  TDMANAGE_YEAR_ID,
  TDMANAGE_YEAR_INPUT,
  TDMANAGE_MONTH_ID,
  TDMANAGE_MONTH_INPUT,
  TDMANAGE_DAY_ID,
  TDMANAGE_DAY_INPUT,
  TDMANAGE_HOUR_ID,
  TDMANAGE_HOUR_INPUT,
  TDMANAGE_MINUTE_ID,
  TDMANAGE_MINUTE_INPUT,
  TDMANAGE_ROW3_ID,
  TDMANAGE_ROW3_INPUT,
  TDMANAGE_ROW13_ID,
  TDMANAGE_ROW13_INPUT,
  TDMANAGE_ROW22_ID,
  TDMANAGE_ROW22_INPUT,
  TDMANAGE_ROW23_ID,
  TDMANAGE_ROW23_INPUT,
  
  WPMANAGE_RECIPE_ID,
  WPMANAGE_RENAME_BUTTON,
  WPMANAGE_COPY_BUTTON,
  WPMANAGE_DELETE_BUTTON,
  WPMANAGE_PAGE_BUTTON_4,
  WPMANAGE_PAGE_HEADER,
  WPMANAGE_SPACE_HEADER,
  WPMANAGE_SPACE_1,
  WPMANAGE_SPACE_2,
  WPMANAGE_SPACE_3,
  WPMANAGE_SPACE_4,
  WPMANAGE_SPACE_5,
  WPMANAGE_SPACE_6,
  WPMANAGE_SPACE_7,
  WPMANAGE_RENSRCE_ID,
  WPMANAGE_RENNEW_ID,
  WPMANAGE_COPYSRCE_ID,
  WPMANAGE_COPYDEST_ID,
  WPMANAGE_DELETE_ID,
  WPMANAGE_RENNEW_SEARCH_ID,
  WPMANAGE_COPYSRCE_SEARCH_ID,
  WPMANAGE_COPYDEST_SEARCH_ID,
  WPMANAGE_ROW13_ID,
  WPMANAGE_ROW13_INPUT,
  WPMANAGE_ROW14_ID,
  WPMANAGE_ROW14_INPUT,
  WPMANAGE_ROW21_ID,
  WPMANAGE_ROW21_INPUT,
  WPMANAGE_ROW24_ID,
  WPMANAGE_ROW24_INPUT,
  WPMANAGE_ROW31_ID,
  WPMANAGE_ROW31_INPUT,
  WPMANAGE_ROW33_ID,
  WPMANAGE_ROW33_INPUT,
  WPMANAGE_ROW34_ID,
  WPMANAGE_ROW34_INPUT,
  WPMANAGE_RENSRCE_SEARCH_ID,
  WPMANAGE_ROW2_SEARCH_ID,
  WPMANAGE_ROW3_SEARCH_ID,
  WPMANAGE_ROW11_SEARCH_ID,
  WPMANAGE_ROW12_SEARCH_ID,
  WPMANAGE_ROW13_SEARCH_ID,
  WPMANAGE_DELETE_SEARCH_ID,
  WPMANAGE_ROW22_SEARCH_ID,
  WPMANAGE_ROW23_SEARCH_ID,
   
  ID_IO_DBASE_LIST,
  IO_SEARCH_ID,
  IO_SPACE_1,
  IO_SPACE_2,
  IO_SPACE_3,
  IO_ID_HEADER1,
  IO_ID_HEADER2,
  IO_ID_HEADER_LEFT,
  IO_ID_HEADER_RIGHT,
  IO_CHECK_HEADER1,
  IO_CHECK_HEADER2,
  IO_STATE_HEADER1,
  IO_STATE_HEADER2,
  IO_VALUE_HEADER1,
  IO_VALUE_HEADER2,
  IO_INPUT_HEADER1,
  IO_INPUT_HEADER2,
  IO_UNIT_HEADER1,
  IO_UNIT_HEADER2,
       
  IO_ROW_MARKER           = 1000,
  IO_ID_ROW1              = 1001,
  IO_ID_ROW2,
  IO_ID_ROW3,
  IO_ID_ROW4,
  IO_ID_ROW5,
  IO_ID_ROW6,
  IO_ID_ROW7,
  IO_ID_ROW8,
  IO_ID_ROW9,
  IO_ID_ROW10,
  IO_ID_ROW11,
  IO_ID_ROW12, 

  IO_INPUTBOX_MARKER       = 1100,
  IO_INPUT_ROW1            = 1101,
  IO_INPUT_ROW2,
  IO_INPUT_ROW3,
  IO_INPUT_ROW4,
  IO_INPUT_ROW5,
  IO_INPUT_ROW6,
  IO_INPUT_ROW7,
  IO_INPUT_ROW8,
  IO_INPUT_ROW9,
  IO_INPUT_ROW10,
  IO_INPUT_ROW11,
  IO_INPUT_ROW12,

  IO_CHECKBOX_MARKER       = 1200,
  IO_CHECK_ROW1            = 1201,
  IO_CHECK_ROW2,
  IO_CHECK_ROW3,
  IO_CHECK_ROW4,
  IO_CHECK_ROW5,
  IO_CHECK_ROW6,
  IO_CHECK_ROW7,
  IO_CHECK_ROW8,
  IO_CHECK_ROW9,
  IO_CHECK_ROW10,
  IO_CHECK_ROW11,
  IO_CHECK_ROW12,
  
  IO_STATE_MARKER           = 1300,
  IO_STATE_ROW1             = 1301,
  IO_STATE_ROW2,
  IO_STATE_ROW3,
  IO_STATE_ROW4,
  IO_STATE_ROW5,
  IO_STATE_ROW6,
  IO_STATE_ROW7,
  IO_STATE_ROW8,
  IO_STATE_ROW9,
  IO_STATE_ROW10,
  IO_STATE_ROW11,
  IO_STATE_ROW12,
 
  IO_UNIT_MARKER             = 1400,
  IO_UNIT_ROW1               = 1401,
  IO_UNIT_ROW2,
  IO_UNIT_ROW3,
  IO_UNIT_ROW4,
  IO_UNIT_ROW5,
  IO_UNIT_ROW6,
  IO_UNIT_ROW7,
  IO_UNIT_ROW8,
  IO_UNIT_ROW9,
  IO_UNIT_ROW10,
  IO_UNIT_ROW11,
  IO_UNIT_ROW12,
 
  MC_HEADLINE_ID,
  MC_SEARCH_ID,
  MC_SPACE1,
  MC_SPACE2,
  MC_SPACE3,
// Page 1
  MC_ROW1_ID,
  MC_ROW2_ID,
  MC_ROW3_ID,
  MC_ROW4_ID,
  MC_ROW5_ID,
  MC_ROW6_ID,
  MC_ROW7_ID,
  MC_ROW8_ID,
  MC_ROW9_ID,
  MC_ROW10_ID,
  MC_ROW11_ID,
  MC_ROW12_ID,
// Page 2  
  MC_ROW13_ID,
  MC_ROW14_ID,
  MC_ROW15_ID,
  MC_ROW16_ID,
  MC_ROW17_ID,
  MC_ROW18_ID,
  MC_ROW19_ID,
  MC_ROW20_ID,
  MC_ROW21_ID,
  MC_ROW22_ID,
  MC_ROW23_ID,
  MC_ROW24_ID,
// Page 3  
  MC_ROW25_ID,
  MC_ROW26_ID,
  MC_ROW27_ID,
  MC_ROW28_ID,
  MC_ROW29_ID,
  MC_ROW30_ID,
  MC_ROW31_ID,
  MC_ROW32_ID,
  MC_ROW33_ID,
  MC_ROW34_ID,
  MC_ROW35_ID,
  MC_ROW36_ID,
// Page 4
  MC_ROW37_ID,
  MC_ROW38_ID,
  MC_ROW39_ID,
  MC_ROW40_ID,
  MC_ROW41_ID,
  MC_ROW42_ID,
  MC_ROW43_ID,
  MC_ROW44_ID,
  MC_ROW45_ID,
  MC_ROW46_ID,
  MC_ROW47_ID,
  MC_ROW48_ID,
  MC_ROW49_ID,
  
// Page 1  
  MC_ROW1_INPUT,
  MC_ROW2_INPUT,
  MC_ROW3_INPUT,
  MC_ROW4_INPUT,
  MC_ROW5_INPUT,
  MC_ROW6_INPUT,
  MC_ROW7_INPUT,
  MC_ROW8_INPUT,
  MC_ROW9_INPUT,
  MC_ROW10_INPUT,
  MC_ROW11_INPUT,
  MC_ROW12_INPUT,
// page 2  
  MC_ROW13_INPUT,
  MC_ROW14_INPUT,
  MC_ROW15_INPUT,
  MC_ROW16_INPUT,
  MC_ROW17_INPUT,
  MC_ROW18_INPUT,
  MC_ROW19_INPUT,
  MC_ROW20_INPUT,
  MC_ROW21_INPUT,
  MC_ROW22_INPUT,
  MC_ROW23_INPUT,
  MC_ROW24_INPUT,
// page 3  
  MC_ROW25_INPUT,
  MC_ROW26_INPUT,
  MC_ROW27_INPUT,
  MC_ROW28_INPUT,
  MC_ROW29_INPUT,
  MC_ROW30_INPUT,
  MC_ROW31_INPUT,
  MC_ROW32_INPUT,
  MC_ROW33_INPUT,
  MC_ROW34_INPUT,
  MC_ROW35_INPUT,
  MC_ROW36_INPUT,  

// Page 1  
  MC_ROW1_SELECT,
  MC_ROW2_SELECT,
  MC_ROW3_SELECT,
  MC_ROW4_SELECT,
  MC_ROW5_SELECT,
  MC_ROW6_SELECT,
  MC_ROW7_SELECT,
  MC_ROW8_SELECT,
  MC_ROW9_SELECT,
  MC_ROW10_SELECT,
  MC_ROW11_SELECT,
  MC_ROW12_SELECT,
// Page 2  
  MC_ROW13_SELECT,
  MC_ROW14_SELECT,
  MC_ROW15_SELECT,
  MC_ROW16_SELECT,
  MC_ROW17_SELECT,
  MC_ROW18_SELECT,
  MC_ROW19_SELECT,
  MC_ROW20_SELECT,
  MC_ROW21_SELECT,
  MC_ROW22_SELECT,
  MC_ROW23_SELECT,
  MC_ROW24_SELECT,
// Page 3  
  MC_ROW25_SELECT,
  MC_ROW26_SELECT,
  MC_ROW27_SELECT,
  MC_ROW28_SELECT,
  MC_ROW29_SELECT,
  MC_ROW30_SELECT,
  MC_ROW31_SELECT,
  MC_ROW32_SELECT,
  MC_ROW33_SELECT,
  MC_ROW34_SELECT,
  MC_ROW35_SELECT,
  MC_ROW36_SELECT,
  
// Page 1
  MC_ROW1_UNIT,
  MC_ROW2_UNIT,
  MC_ROW3_UNIT,
  MC_ROW4_UNIT,
  MC_ROW5_UNIT,
  MC_ROW6_UNIT,
  MC_ROW7_UNIT,
  MC_ROW8_UNIT,
  MC_ROW9_UNIT,
  MC_ROW10_UNIT,
  MC_ROW11_UNIT,
  MC_ROW12_UNIT,
// Page 2  
  MC_ROW13_UNIT,
  MC_ROW14_UNIT,
  MC_ROW15_UNIT,
  MC_ROW16_UNIT,
  MC_ROW17_UNIT,
  MC_ROW18_UNIT,
  MC_ROW19_UNIT,
  MC_ROW20_UNIT,
  MC_ROW21_UNIT,
  MC_ROW22_UNIT,
  MC_ROW23_UNIT,
  MC_ROW24_UNIT, 
// Page 3  
  MC_ROW25_UNIT,
  MC_ROW26_UNIT,
  MC_ROW27_UNIT,
  MC_ROW28_UNIT,
  MC_ROW29_UNIT,
  MC_ROW30_UNIT,
  MC_ROW31_UNIT,
  MC_ROW32_UNIT,
  MC_ROW33_UNIT,
  MC_ROW34_UNIT,
  MC_ROW35_UNIT,
  MC_ROW36_UNIT,   
// Page 4  
  MC_ROW39_OUTPUT,
  MC_ROW40_OUTPUT,


  MP_HEADLINE_ID,
  MP_SEARCH_ID,
  MP_SPACE1,
  MP_SPACE2,
  MP_SPACE3,
// Page 1
  MP_ROW1_ID,
  MP_ROW2_ID,
  MP_ROW3_ID,
  MP_ROW4_ID,
  MP_ROW5_ID,
  MP_ROW6_ID,
  MP_ROW7_ID,
  MP_ROW8_ID,
  MP_ROW9_ID,
  MP_ROW10_ID,
  MP_ROW11_ID,
  MP_ROW12_ID,
// Page 2  
  MP_ROW13_ID,
  MP_ROW14_ID,
  MP_ROW15_ID,
  MP_ROW16_ID,
  MP_ROW17_ID,
  MP_ROW18_ID,
  MP_ROW19_ID,
  MP_ROW20_ID,
  MP_ROW21_ID,
  MP_ROW22_ID,
  MP_ROW23_ID,
  MP_ROW24_ID,
// Page 3  
  MP_ROW25_ID,
  MP_ROW26_ID,
  MP_ROW27_ID,
  MP_ROW28_ID,
  MP_ROW29_ID,
  MP_ROW30_ID,
  MP_ROW31_ID,
  MP_ROW32_ID,
  MP_ROW33_ID,
  MP_ROW34_ID,
  MP_ROW35_ID,
  MP_ROW36_ID,  
// Page 4
  MP_ROW37_ID,
  MP_ROW38_ID,
  MP_ROW39_ID,
  MP_ROW40_ID,
  MP_ROW41_ID,
  MP_ROW42_ID,
  MP_ROW43_ID,
  MP_ROW44_ID,
  MP_ROW45_ID,
  MP_ROW46_ID,
  MP_ROW47_ID,
  MP_ROW48_ID,

// Page 1  
  MP_ROW1_INPUT,
  MP_ROW2_INPUT,
  MP_ROW3_INPUT,
  MP_ROW4_INPUT,
  MP_ROW5_INPUT,
  MP_ROW6_INPUT,
  MP_ROW7_INPUT,
  MP_ROW8_INPUT,
  MP_ROW9_INPUT,
  MP_ROW10_INPUT,
  MP_ROW11_INPUT,
  MP_ROW12_INPUT,
// Page 2  
  MP_ROW13_INPUT,
  MP_ROW14_INPUT,
  MP_ROW15_INPUT,
  MP_ROW16_INPUT,
  MP_ROW17_INPUT,
  MP_ROW18_INPUT,
  MP_ROW19_INPUT,
  MP_ROW20_INPUT,
  MP_ROW21_INPUT,
  MP_ROW22_INPUT,
  MP_ROW23_INPUT,
  MP_ROW24_INPUT,
// Page 3  
  MP_ROW25_INPUT,
  MP_ROW26_INPUT,
  MP_ROW27_INPUT,
  MP_ROW28_INPUT,
  MP_ROW29_INPUT,
  MP_ROW30_INPUT,
  MP_ROW31_INPUT,
  MP_ROW32_INPUT,
  MP_ROW33_INPUT,
  MP_ROW34_INPUT,
  MP_ROW35_INPUT,
  MP_ROW36_INPUT,

// Page 1  
  MP_ROW1_SELECT,
  MP_ROW2_SELECT,
  MP_ROW3_SELECT,
  MP_ROW4_SELECT,
  MP_ROW5_SELECT,
  MP_ROW6_SELECT,
  MP_ROW7_SELECT,
  MP_ROW8_SELECT,
  MP_ROW9_SELECT,
  MP_ROW10_SELECT,
  MP_ROW11_SELECT,
  MP_ROW12_SELECT,
// Page 2  
  MP_ROW13_SELECT,
  MP_ROW14_SELECT,
  MP_ROW15_SELECT,
  MP_ROW16_SELECT,
  MP_ROW17_SELECT,
  MP_ROW18_SELECT,
  MP_ROW19_SELECT,
  MP_ROW20_SELECT,
  MP_ROW21_SELECT,
  MP_ROW22_SELECT,
  MP_ROW23_SELECT,
  MP_ROW24_SELECT,
// Page 3  
  MP_ROW25_SELECT,
  MP_ROW26_SELECT,
  MP_ROW27_SELECT,
  MP_ROW28_SELECT,
  MP_ROW29_SELECT,
  MP_ROW30_SELECT,
  MP_ROW31_SELECT,
  MP_ROW32_SELECT,
  MP_ROW33_SELECT,
  MP_ROW34_SELECT,
  MP_ROW35_SELECT,
  MP_ROW36_SELECT,
  
// Page 1
  MP_ROW1_UNIT,
  MP_ROW2_UNIT,
  MP_ROW3_UNIT,
  MP_ROW4_UNIT,
  MP_ROW5_UNIT,
  MP_ROW6_UNIT,
  MP_ROW7_UNIT,
  MP_ROW8_UNIT,
  MP_ROW9_UNIT,
  MP_ROW10_UNIT,
  MP_ROW11_UNIT,
  MP_ROW12_UNIT,
// Page 2  
  MP_ROW13_UNIT,
  MP_ROW14_UNIT,
  MP_ROW15_UNIT,
  MP_ROW16_UNIT,
  MP_ROW17_UNIT,
  MP_ROW18_UNIT,
  MP_ROW19_UNIT,
  MP_ROW20_UNIT,
  MP_ROW21_UNIT,
  MP_ROW22_UNIT,
  MP_ROW23_UNIT,
  MP_ROW24_UNIT,
// Page 3  
  MP_ROW25_UNIT,
  MP_ROW26_UNIT,
  MP_ROW27_UNIT,
  MP_ROW28_UNIT,
  MP_ROW29_UNIT,
  MP_ROW30_UNIT,
  MP_ROW31_UNIT,
  MP_ROW32_UNIT,
  MP_ROW33_UNIT,
  MP_ROW34_UNIT,
  MP_ROW35_UNIT,
  MP_ROW36_UNIT,  
// Page 4  
  MP_ROW39_OUTPUT,
  MP_ROW40_OUTPUT,

  FLEX_HEADLINE_ID,
  FLEX_SEARCH_ID,
  FLEX_SPACE_1,
  FLEX_SPACE_2,
  FLEX_SPACE_3,
// Page 1
  FLEX_ROW1_ID,
  FLEX_ROW2_ID,
  FLEX_ROW3_ID,
  FLEX_ROW4_ID,
  FLEX_ROW5_ID,
  FLEX_ROW6_ID,
  FLEX_ROW7_ID,
  FLEX_ROW8_ID,
  FLEX_ROW9_ID,
  FLEX_ROW10_ID,
  FLEX_ROW11_ID,
  FLEX_ROW12_ID,
// Page 2  
  FLEX_ROW13_ID,
  FLEX_ROW14_ID,
  FLEX_ROW15_ID,
  FLEX_ROW16_ID,
  FLEX_ROW17_ID,
  FLEX_ROW18_ID,
  FLEX_ROW19_ID,
  FLEX_ROW20_ID,
  FLEX_ROW21_ID,
  FLEX_ROW22_ID,
  FLEX_ROW23_ID,
  FLEX_ROW24_ID,
// Page 3  
  FLEX_ROW25_ID,
  FLEX_ROW26_ID,
  FLEX_ROW27_ID,
  FLEX_ROW28_ID,
  FLEX_ROW29_ID,
  FLEX_ROW30_ID,
  FLEX_ROW31_ID,
  FLEX_ROW32_ID,
  FLEX_ROW33_ID,
  FLEX_ROW34_ID,
  FLEX_ROW35_ID,
  FLEX_ROW36_ID,  

// Page 1  
  FLEX_ROW1_INPUT,
  FLEX_ROW2_INPUT,
  FLEX_ROW3_INPUT,
  FLEX_ROW4_INPUT,
  FLEX_ROW5_INPUT,
  FLEX_ROW6_INPUT,
  FLEX_ROW7_INPUT,
  FLEX_ROW8_INPUT,
  FLEX_ROW9_INPUT,
  FLEX_ROW10_INPUT,
  FLEX_ROW11_INPUT,
  FLEX_ROW12_INPUT,
// Page 2  
  FLEX_ROW13_INPUT,
  FLEX_ROW14_INPUT,
  FLEX_ROW15_INPUT,
  FLEX_ROW16_INPUT,
  FLEX_ROW17_INPUT,
  FLEX_ROW18_INPUT,
  FLEX_ROW19_INPUT,
  FLEX_ROW20_INPUT,
  FLEX_ROW21_INPUT,
  FLEX_ROW22_INPUT,
  FLEX_ROW23_INPUT,
  FLEX_ROW24_INPUT,
// Page 3  
  FLEX_ROW25_INPUT,
  FLEX_ROW26_INPUT,
  FLEX_ROW27_INPUT,
  FLEX_ROW28_INPUT,
  FLEX_ROW29_INPUT,
  FLEX_ROW30_INPUT,
  FLEX_ROW31_INPUT,
  FLEX_ROW32_INPUT,
  FLEX_ROW33_INPUT,
  FLEX_ROW34_INPUT,
  FLEX_ROW35_INPUT,
  FLEX_ROW36_INPUT,  

// Page 1  
  FLEX_ROW1_SELECT,
  FLEX_ROW2_SELECT,
  FLEX_ROW3_SELECT,
  FLEX_ROW4_SELECT,
  FLEX_ROW5_SELECT,
  FLEX_ROW6_SELECT,
  FLEX_ROW7_SELECT,
  FLEX_ROW8_SELECT,
  FLEX_ROW9_SELECT,
  FLEX_ROW10_SELECT,
  FLEX_ROW11_SELECT,
  FLEX_ROW12_SELECT,
// Page 2  
  FLEX_ROW13_SELECT,
  FLEX_ROW14_SELECT,
  FLEX_ROW15_SELECT,
  FLEX_ROW16_SELECT,
  FLEX_ROW17_SELECT,
  FLEX_ROW18_SELECT,
  FLEX_ROW19_SELECT,
  FLEX_ROW20_SELECT,
  FLEX_ROW21_SELECT,
  FLEX_ROW22_SELECT,
  FLEX_ROW23_SELECT,
  FLEX_ROW24_SELECT,
// Page 3  
  FLEX_ROW25_SELECT,
  FLEX_ROW26_SELECT,
  FLEX_ROW27_SELECT,
  FLEX_ROW28_SELECT,
  FLEX_ROW29_SELECT,
  FLEX_ROW30_SELECT,
  FLEX_ROW31_SELECT,
  FLEX_ROW32_SELECT,
  FLEX_ROW33_SELECT,
  FLEX_ROW34_SELECT,
  FLEX_ROW35_SELECT,
  FLEX_ROW36_SELECT,
    
// Page 1
  FLEX_ROW1_UNIT,
  FLEX_ROW2_UNIT,
  FLEX_ROW3_UNIT,
  FLEX_ROW4_UNIT,
  FLEX_ROW5_UNIT,
  FLEX_ROW6_UNIT,
  FLEX_ROW7_UNIT,
  FLEX_ROW8_UNIT,
  FLEX_ROW9_UNIT,
  FLEX_ROW10_UNIT,
  FLEX_ROW11_UNIT,
  FLEX_ROW12_UNIT,
// Page 2  
  FLEX_ROW13_UNIT,
  FLEX_ROW14_UNIT,
  FLEX_ROW15_UNIT,
  FLEX_ROW16_UNIT,
  FLEX_ROW17_UNIT,
  FLEX_ROW18_UNIT,
  FLEX_ROW19_UNIT,
  FLEX_ROW20_UNIT,
  FLEX_ROW21_UNIT,
  FLEX_ROW22_UNIT,
  FLEX_ROW23_UNIT,
  FLEX_ROW24_UNIT,
// Page 3  
  FLEX_ROW25_UNIT,
  FLEX_ROW26_UNIT,
  FLEX_ROW27_UNIT,
  FLEX_ROW28_UNIT,
  FLEX_ROW29_UNIT,
  FLEX_ROW30_UNIT,
  FLEX_ROW31_UNIT,
  FLEX_ROW32_UNIT,
  FLEX_ROW33_UNIT,
  FLEX_ROW34_UNIT,
  FLEX_ROW35_UNIT,
  FLEX_ROW36_UNIT, 
  
  FLEX_ENABLED_IO_DBASE_LIST,
  FLEX_DBASE_ID,
  
  // Auto page space added by namk
  AUTO_SPACE1, 
  AUTO_SPACE2,
  AUTO_SPACE3,
  AUTO_SPACE4,
  AUTO_SPACE5,
  
  REPORT_ROW11_ADJUSTSTOCK,
  REPORT_ROW12_SILOSTOCK,
  REPORT_ROW13_SILONO,
  
  //Graph
  GRAPH_ROW1,
  GRAPH_ROW2,
  GRAPH_ROW3,
  GRAPH_ROW4,
  GRAPH_ROW5,
  GRAPH_ROW6,
  GRAPH_ROW7,
  GRAPH_ROW8,
  GRAPH_ROW9,
  GRAPH_ROW10,
  GRAPH_ROW11,
  GRAPH_ROW12,
  
}

// Screen calling control
// Screen #s
enum
{
  NIL,
  SCREEN_RECIPE1    = 1,
  SCREEN_RECIPE2,
  SCREEN_RECIPE3,
  SCREEN_RECIPE4,
  SCREEN_RECIPES,
  SCREEN_AUTOMATIC,
  SCREEN_REPORT,
  SCREEN_BATCH,
  SCREEN_GOTO,
  SCREEN_WPMANAGECOPY,
  SCREEN_WPMANAGERENAME,
  SCREEN_WPMANAGEDELETE,
  SCREEN_ACCESS,
  SCREEN_INFO,
  SCREEN_FAULT,
  SCREEN_TDMANAGE,
  SCREEN_IOCFG_IN1   = 21,
  SCREEN_IOCFG_IN2,
  SCREEN_IOCFG_IN3,
  SCREEN_IOCFG_OUT1  = 25,
  SCREEN_IOCFG_OUT2,
  SCREEN_IOCFG_OUT3,
  SCREEN_IOTEST_IN1  = 31,
  SCREEN_IOTEST_IN2,
  SCREEN_IOTEST_IN3,
  SCREEN_IOTEST_OUT1 = 35,
  SCREEN_IOTEST_OUT2,
  SCREEN_IOTEST_OUT3,
  SCREEN_MP1         = 41,
  SCREEN_MP2,
  SCREEN_MP3,
  SCREEN_MP4,
  SCREEN_MC1         = 45,
  SCREEN_MC2,
  SCREEN_MC3,
  SCREEN_MC4,
  SCREEN_FLEXIO_1    = 50,
  SCREEN_FLEXIO_2,
  SCREEN_FLEXIO_3,
  SCREEN_REGISTRATION,
  SCREEN_WP_LIST_POPUP,
  SCREEN_LANG_LIST_POPUP,
  SCREEN_FLEXIO_LIST_POPUP,
  SCREEN_GRAPH,
  SCREEN_UPLOAD_DBS,
  LAST_SCREEN,

  SCREEN_CONFIG,
  SCREEN_MULTIPLE,
  SCREEN_INPUT_PAGE1, 
  SCREEN_INPUT_PAGE2,
  SCREEN_INPUT_PAGE3,
  SCREEN_INPUT_PAGES,
  SCREEN_OUTPUT_PAGE1,
  SCREEN_OUTPUT_PAGE2,
  SCREEN_OUTPUT_PAGE3,
  SCREEN_OUTPUT_PAGES,
  SCREEN_IOTEST_PAGES,
  SCREEN_WPMANAGE,
  MP_SAVE2DEFAULT,
  MP_RESTOREDEFAULT,
  MC_SAVE2DEFAULT,
  MC_RESTOREDEFAULT,
  MC_SETMASTERPASS,
  SCREEN_FORBIDDEN,
  SAVE_PAGES,
  CONFIG_PAGES,
  WPMANAGE_PAGES,
  NIL_SCREEN,
  SCREEN_HOURLY,
  SCREEN_SHIFT,
  SCREEN_INDIVIDUAL,
  SCREEN_FULLEMPTY  
}

   ////////////////////////////////////
 //   Specific Screen creation ID  //
///////////////////////////////////
enum
{
  WPMANAGECOPY_PAGE,
  WPMANAGERENAME_PAGE,
  WPMANAGEDELETE_PAGE,
}

   ///////////////////////////
 //   Mode Step control   //
//////////////////////////
enum
{
  stp_OFF_MODE = 100,
  stp_STOP_MODE =200,
  stp_STOPPING_MODE =300,
  stp_MANUAL_MODE =400,
  stp_PREP_MODE =500,
  stp_AUTO_MODE =600,
  stp_WAIT_MODE = 700
} 

   ///////////////////////////////
 //   Fault display control   //
//////////////////////////////
enum
{
  stp_NO_FLT,
  stp_GEN_FLT,
  stp_WARN_FLT,
  stp_BLOCK_FLT,
  
}


// for WriteIOSingleEntryDB routine
enum
{
CheckBox,
InputBox
}

enum
{
Int,
Dec,
Float,
}

// Database list for YES/NO Popup
enum
{
NO_Db,
WP_Db,
MP_Db,
MC_Db,
FlexIO_Db
}

// Beeper config
enum
{
BEEP_OFF,
BEEP_ON = 1200,
}

// for RefreshMCGrayOut and RefreshMPGrayOut routine
enum
{
MX_PAGE1 = 12,
MX_PAGE2 = 24,
MX_PAGE3 = 36,
MX_PAGE4 = 48,
}


// Fault Priority List
enum
{
FLT_GEN,
FLT_BLK,
FLT_STOP,
FLT_WRN
}

// Weight display size
enum
{
LARGE,
SMALL
}

// Max Array test
enum
{
MaxFlts= 4
}

// User Level
enum 
{
Level_None = 0,
Level_OP   = 3,
Level_SUP  = 5,
Level_PT   = 8
}

enum
{
WgtDisplFull,
WgtDisplSmall,
WgtDisplInfo,
WgtDisplOff
}

enum
{
align_vcenter,
align_hcenter,
align_left
}


enum //Flex IOs Type of contact
{
//Flex_None,
Flex_Input,
Flex_Output,
Flex_Setpoint
}

enum //Flex IOs 
{
Flex_Out1,
Flex_Out2,
Flex_Out3
}

enum //Flex IOs Timer presets 
{
Flex_None_TPre,
WP_Flex1_TPre,
WP_Flex2_TPre,
MP_Flex1_TPre,
MP_Flex2_TPre,
MP_Flex3_TPre,
WP_Flex3_TPre
}

enum //Flex IOs Setpoints 
{
WP_Flex1_SP,
WP_Flex2_SP,
MP_Flex1_SP,
MP_Flex2_SP
}
enum //Flex IOs T_EN and T_Done test
{
Flex_T_EN,
Flex_T_Dn
}

enum //Flex IOs Count Mode
{
Flex_Preset,
Flex_Pulsing
}

enum //Flex Counter Source
{
WP_Flex_Counter,
MP_Flex_Counter
}

enum //Flex Output
{
FlexOutput_OFF,
FlexOutput_ON
}

enum
{
Flex_On_Time,
Flex_Init_Delay,
Flex_Off_Time
}

enum //Scale Type configured
{
No_Scale,
iQ_Feeding,
Lbs,
iQ_Sim,
A_D_M
}

enum //Force weight display when remote display connected
{
No_Forcing,
Force_Display
}

enum //Remove pointer in WP List when in WP Management page
{
WP_List,
WPManage_List
}

enum //Select WP Selection method
{
List_Page,
Numeric_Keyboard
}

enum
{
Act_Ext = 1,
Act_ExtPulsed,
Act_Positioned,
Act_Ret,
Act_RetPulsed
}

enum
{
widget_unlocked,
widget_locked
}

enum
{
No_Margin,
Left_Margin = 2
}

enum
{
Input_Page,
Output_Page
}

enum
{
Local,
Remote
}

enum //Printing & Reporting Functions
{
COM2FctNone=0,
COM2FctContinuousOut,
COM2FctUnitRecString,
COM2FctReportToPrinter,
}


enum //Printing & Reporting Functions
{
USBFctNone=0,
USBFctUnitRecString,
USBFctUnitRecFile,
USBFctReportToPrinter,
USBFctReportToFile
}

enum //Printing & Reporting Functions
{
ETHFctNone=0,
ETHFctContinuousOut,
ETHFctReportToPrinter,
}

enum
{
BARGRAPH_ID1 = 10000,
BARGRAPH_ID2,
BARGRAPH_ID3,
BARGRAPH_ID4,
BARGRAPH_ID5,
BARGRAPH_ID6,
BARGRAPH_ID7,
BARGRAPH_ID8,
BARGRAPH_ID9,
BARGRAPH_ID10,
BARGRAPH_ID11,
BARGRAPH_ID12,
BARGRAPH_ID13,
BARGRAPH_ID14,
BARGRAPH_ID15,
BARGRAPH_MAX = 10030,
BARGRAPH_ID31 = 10050,
}
/* ****************************************************************** */
/* ****************************************************************** */
/* *                                                                * */
/* *                                                                * */
/* *                                                                * */
/* *                        RTC-Program                             * */
/* *                                                                * */
/* *                 Copyright by SysTec GmbH                       * */
/* *                                                                * */
/* ****************************************************************** */
/* ****************************************************************** */

/*
 Project:                general RTC constants such as fonts, colors,...

 Creation date:          May-2010

 Author:                 SysTec

 List of modifications:

   Name:       Date:    Vers. Modification:
 
*/
/* screen fonts */
#define  FT_RTC          24    // RTC proportional
#define  FT_RTC_BOLD     25    // RTC proportional, bold
#define  FT_RTCMONO      28    // RTC monospaced
#define  FT_RTCMONO_BOLD 29    // RTC monospaced, bold
/* weight template */
#define  FT_RTC_WEIGHT              8  // font used in weight screen
#define  RTC_JUMBO_WEIGHT_SIZE     86  // 38*86 >> fontsize(38) font(FT_RTC)
#define  RTC_WEIGHT_SIZE           44  // 28*44 >  fontsize(38) font(FT_RTC)
#define  RTC_UNIT_SIZE             18  // 11*22 =  fontsize(18) font(FT_RTC)
/* Screen colors */
#define  CL_BLACK         0
#define  CL_WHITE       255
#define  CL_RED          88
#define  CL_GREEN_BG     63
#define  CL_YELLOW       94
#define  CL_ORANGE       93
#define  CL_BLUE        216
#define  CL_SILVER       50
#define  CL_GREY         31    // disabled text
#define  CL_LT_GREEN    102    // background of positive operator feedback
#define  CL_LT_BLUE     229    // background for operator prompting
#define  CL_LT_GREY      238    // background of message boxes original = 29
#define  CL_BACKGROUND   20    // standard screen background original = 20
#define  CL_BACK_BLUE   238    // background for data entry


// Touch screen colors 
#define  CL_TITLE_BACKGROUND  "#9EACBA" //Original = "#5a7cf9"     
#define  CL_TOUCH_LIGHT_BLUE  "#9EACBA"//PT color RGB:0,33,71 = #002147     // Info line operator prompting //Original = "#5a7cf9"
#define  CL_TEXT_FOREGROUND   "white"
#define  CL_BUTTON            "#002147" //Original = darkblue
#define  CL_BACKGROUND_TOUCH  "white" //Original = #d0e0ff
#define  CL_TOUCH_RED         "#ff0000"
#define  CL_SKETCH_WHITE      "white"
#define  CL_PROMPT_FOREGROUND "#002147"

// Premier Tech defined colours
#define  CL_PT_BLUE              "#002147"
#define  CL_PT_ROLLOVER          "#83a8c0" //dégradé pâle
#define  CL_PT_ROLLOVER2         "#597688" //dégradé fonçé
#define  CL_PT_RED               "#b32024"
#define  CL_PT_WHITE             "white"
#define  CL_PT_YELLOW            "#f3bc34"
#define  CL_PT_GREEN             "#0a7d3f"
#define  CL_PT_GRAY              "#9EACBA"
#define  CL_PT_GRAYROLLOVER      "#xxxxx"
#define  CL_PT_SYSTEC_GRAYOUT    "#c0c0c0" //"#6B6B6B"

// Touch 
#define  FCT_BUTTON_HEIGHT     55
#define  FCT_BUTTON_WIDTH     100 
#define  FCT_BUTTON_FONTSIZE   24
#define  FCT_BUTTON_DISTANCE    0  // no distance
#define  STD_EDGE_DISTANCE      2
#define  MIN_EDGE_DISTANCE      0
#define  STD_FONTSIZE          24

//Premier Tech Buttons section
#define  FCT_BUTTON_EXT_GAP           2  // External gap around button
#define  FCT_BUTTON_DISTANCE_NAVIG    0  // no distance 
#define  STD_EDGE_DISTANCE_NAVIG      2
#define  PT_INFO_LINE                24 //28

//Premier Tech font size
#define FT_SMALL_SIZE      19
#define FT_STANDARD_SIZE   24 //old 23?
#define FT_STANDARD_SMALL  22
#define FT_MEDIUM_SIZE     30
#define FT_LARGE_SIZE      40
#define FT_ACCESSPAGE_SIZE 26
#define FT_RECIPE_SIZE     34
#define FT_FLEX_OVERSIZE   19

//Premier Tech Input Box Size
#define PT_6BOX_SIZE        47
#define PT_7BOX_SIZE        40

//Premier Tech Output Box Size
#define WD_PTBOX_SIZE         1
#define HT_PTBOX_SIZE        32

/* special functions */
#define SET_COLUMN_POS(p)      writeparameter("SYSTEM","X2",     #p)  // set input position of inputbox
#define SET_PRINTER_PORT(Port) writeparameter("System","Printer",adj(Port,1,0))
#define SELECT_MODE(p)         writeparameter("SYSTEM","SELECTBOXMODE",#p) // "0"=delete all fct key texts in 1st level, "1"=write fct keys in 1st level
#define SET_F6_BUTTON(s)       writeparameter("SYSTEM","TX07_FINISH",s) // set fct key text for return key in rtc functions for user input
#define SAVE_SCREEN            showtext(0,0,"\0277")  // Save all contents, attributes and cursor position of application screen 
#define RESTORE_SCREEN         showtext(0,0,"\0278")  // Restore saved application screen and cursor position 
#define RESTOREATTRIBUTES      showtext(0,0,"\0279")  // Only restore attributes and cursor position of application screen 

// Simple weighing page
#define SW_OUTPUT_FONTZISE      30
#define SW_FONTSIZE_NETHIRES    45

#define SW_STRETCH_OUTPUT_X    120
#define SW_STRETCH_OUTPUT_Y     20

#define WD_PTLOGO              140   
#define HT_PTLOGO               45

// GENERAL
#define WD_UNIT                22
#define WD_UNIT_LEFT           24
#define HT_UNIT                40
#define WD_BOX                 80
#define HT_BOX                 20
#define WD_USERLEVEL          280
#define HT_USERLEVEL           35
#define WD_HEADER             234
#define HT_HEADER              35
#define WD_MARGIN               4
#define TOPBARCHARMAX         128  /*** 128 characters available in TopBar Info with Clock included */

// General Page Header 
#define WD_PAGE_HEADER        450
#define HT_PAGE_HEADER         48

// Fault Page
#define WD_FAULTLINE_HEADER   620
#define HT_FAULT_HEADER        26
#define HT_FAULT_MESSAGE       24
#define WD_FAULTTIME_HEADER   175
#define HT_FAULT_TEXT          22
#define HT_FAULT_MESSAGETEXT   20
#define FAULT_DETAIL_SPACE      2
#define FAULT_TIME_SPACE        2

// IO Page
#define FT_IOPAGES_SIZE        21
#define FT_IO_HEADER           24
#define HT_IO_HEADER           44 //39
#define WD_IO_NAME            230 //224
#define WD_IOOUTPUT_NAME      220 //224
#define WD_IO_ADDRESS          80 
#define HT_IO_ADDRESS          44
#define WD_IO_INPUT            80 
#define WD_IO_ENABLE           67
#define WD_IO_STATE            47
#define WD_IO_TEST             53
#define WD_IOCFG_SPACE         30 //50
#define WD_IOTESTINPUT_SPACE   40
#define WD_IOTESTOUTPUT_SPACE  5
#define WD_ANALOGTEST_SPACE    25
#define WD_IO_PERCENT          15
#define WD_IO_ANALOG_NAME     170
#define WD_IO_ANALOG_VALUE     60 

//IO test Analog input column
#define WD_IO_PERCENT2          45
#define WD_IO_ANALOG_NAME2     200
#define WD_IO_ANALOG_VALUE2     87
#define WD_IO_ADDRESS2          87  
// Auto Page
#define FT_AUTOPAGE_SIZE       26
#define FT_AUTOPAGE2_SIZE      22
#define WD_AUTO_DESCRIPTION   160 // 155 
#define HT_AUTO_DESCRIPTION    32
#define WD_AUTOPAGE_BOX        75
#define HT_AUTOPAGE_BOX        32
#define WD_AUTO_SPACE          3 //5
#define WD_AUTO_UNIT           20
#define WD_AUTO_SEC            10

// Recipe Page
#define WD_WP_DESCRIPTION     198 //192
#define HT_WP_DESCRIPTION      50
#define WD_WP_BOX             167
#define HT_WP_BOX              50 //45
#define WD_WP_SPACE             1
#define WD_WPMANAGE_DESCR     350
#define WD_WPMANAGE_BOX       200
#define HT_WPMANAGEPT_BOX      50
#define RECIPECHARSPACE         6


// MC Page
#define WD_MC_DESCRIPTION     210 //240
#define HT_MC_DESCRIPTION      50
#define WD_MC_BOX             167 //137 //158
#define HT_MC_BOX              50 //45
#define WD_MC_UNIT             12
#define WD_MC_UNIT_LEFT        18
#define WD_MC_SPACE             1
#define WD_MC_PAGE4           375

// MP Page
#define WD_MP_DESCRIPTION     240
#define HT_MP_DESCRIPTION      50
#define WD_MP_BOX             100
#define HT_MP_BOX              49 //45
#define WD_MP_SPACE            10
#define WD_MP_PAGE4           375

// Info Page
#define WD_INFO_DESCRIPTION     175
#define WD_INFO_DESCRIPTION2    150
#define WD_INFO_DESCRIPTION4    3
#define HT_INFO_DESCRIPTION      35
#define WD_INFO_BOX             210
#define WD_INFO_BOX2            235
#define HT_INFO_BOX              35
#define WD_INFO_SPACE             1
#define WD_INFO_DESCRIPTION3    WD_INFO_DESCRIPTION2 + WD_INFO_BOX2 + 6

// Report Page
#define WD_REPORT_DESCRIPTION1  140
#define WD_REPORT_DESCRIPTION2  285
#define WD_REPORT_DESCRIPTION3  375
#define WD_REPORT_COLUMN1       190
#define WD_REPORT_COLUMN2       150
#define WD_REPORT_COLUMN3       210
#define WD_REPORT_COLUMN4       150
#define HT_REPORT_DESCRIPTION    36
#define WD_REPORT_BOX           205
#define HT_REPORT_BOX            36
#define WD_REPORT_SPACE           5

#define WD_BATCH_DESCRIPTION1   275
#define WD_BATCH_DESCRIPTION    190
#define HT_BATCH_DESCRIPTION     37
#define WD_BATCH_BOX            175
#define HT_BATCH_BOX             37
#define WD_BATCH_UNIT            15
#define WD_BATCH_DESCR_SPACE    225

// Time & Date Management Page
#define WD_TD_BOX               120
#define WD_TIMEHEADER           280
#define HT_TIMEHEADER            35
#define WD_TIMEUSERLEVEL        235
#define HT_TIMEUSERLEVEL         35
#define WD_TDHEADER_SIZE         75
#define HT_TDBOX_SIZE            50
#define WD_TDBOX_SIZE            50
#define WD_TD_SPACE               5

// Access Page
#define WD_ACCESS_HEADER        175
#define HT_ACCESS_HEADER         55
#define WD_ACCESS_BOX           200
#define HT_ACCESS_BOX            55

// Flex IOs
#define WD_FLEXIO_BOX           211
#define HT_FLEXIO_BOX            50
#define WD_FLEXIO_DESCRIPTION    178
#define HT_FLEXIO_DESCRIPTION    50
#define WD_FLEX_SPACE            25
#define WD_FLEXIO_SIGNBOX        73
#define WD_FLEXIO_SIGNBOX2      135
#define WD_FLEX_SECONDS          13
#define WD_FLEXIOCNT_BOX        193
#define LISTTEXTLENGTH           21

//Border Style: none   | dashed | dot-dash | dot-dot-dash | dotted | double | 
//              groove | inset  | outset   | ridge        | solid  
//              

// Possible boarder foreground and background colors 
// #000000 - #ffffff 
// also possible white, black, red, green, blue, light-blue,...

// Draw Window
#define ST_BOX_STYLE       "background:"   CL_BACKGROUND_TOUCH ";" \
                           "border-style:  outset;"                \ 
                           "border-width:  0.1px;"                 

// Ouput of the window
#define ST_BOXTEXT_STYLE   "background:"   "White" ";"       \  //CL_TOUCH_LIGHT_BLUE ";"
                           "foreground:"   CL_PT_WHITE ";"        \
                           "padding:       0.3em;"                       \
                           "border-color:  white white white white;"     \
                           "padding-left:  0.5em; padding-right: 0.5em;" \
                           "padding-top:   10px; padding-bottom: 10px;"  \
                           "border-style:  solid;"                       \
                           "border-radius: 5px"

#define WEIGHINGDATA_STYLE    "background:"   "White" ";"       \  
                              "foreground:"   CL_PT_WHITE ";"        \
                              "border-style: solid     ;"     \
                              "border-width:  2px       ;"     \ 
                              "border-color: grey white white grey;" \ 
                              "padding-left:  0.1em; padding-right: 0.1em;" \
                              "padding-top:   0px; padding-bottom: 0px;"  \
                              "border-radius: 0px"                              
                           

// Popup Box                            
#define POPUP_BOXTEXT_STYLE   "background:"   "White" ";"               \
                              "foreground:"   CL_PT_WHITE ";"        \
                              "padding:       0.3em;"                       \
                              "border-color:  white red red white;"     \
                              "padding-left:  0.5em; padding-right: 0.5em;" \
                              "padding-top:   10px; padding-bottom: 10px;"  \
                              "border-style:  double;"                       \
                              "border-radius: 0px"                          
                              
// Outside of Popup Box
#define POPUP_OUTBOX_STYLE    "background:"   CL_PT_GRAY ";"       \  //CL_TOUCH_LIGHT_BLUE ";"
                              "foreground:"   CL_PT_WHITE ";"        \
                              "padding:       0.3em;"                       \
                              "border-color:  white white white white;"     \
                              "padding-left:  0.5em; padding-right: 0.5em;" \
                              "padding-top:   10px; padding-bottom: 10px;"  \
                              "border-style:  solid;"                       \
                              "border-radius: 5px"           

#define WPMANAGEBOX_STYLE     "background:" CL_PT_WHITE ";"     \
                              "border-style: solid     ;"     \
                              "border-width:  2px       ;"     \ 
                              "border-color: #002147 #002147 #002147 #002147 ;" \ 
                              "padding-left:  0.1em; padding-right: 0.1em;" \
                              "padding-top:   0px; padding-bottom: 0px;"  \
                              "border-radius: 5px"
                              
#define WPMANAGEBOX_STYLE_GRAY"background:" CL_PT_SYSTEC_GRAYOUT ";"     \
                              "border-style: solid     ;"     \
                              "border-width:  2px       ;"     \ 
                              "border-color: #002147 #002147 #002147 #002147 ;" \ 
                              "padding-left:  0.1em; padding-right: 0.1em;" \
                              "padding-top:   0px; padding-bottom: 0px;"  \
                              "border-radius: 5px"                              
                             
#define AUTOWPBOX_STYLE       "background:" CL_PT_WHITE ";"     \
                              "border-style: solid     ;"     \
                              "border-width:  3px       ;"     \ 
                              "border-color: #002147 #002147 #002147 #002147 ;" \ 
                              "padding-left:  0.1em; padding-right: 0.1em;" \
                              "padding-top:   0px; padding-bottom: 0px;"  \
                              "border-radius: 5px"
                              
#define AUTOWPBOX_STYLE_GRAY  "background:" CL_PT_SYSTEC_GRAYOUT ";"     \
                              "border-style: solid     ;"     \
                              "border-width:  3px       ;"     \ 
                              "border-color: #002147 #002147 #002147 #002147 ;" \ 
                              "padding-left:  0.1em; padding-right: 0.1em;" \
                              "padding-top:   0px; padding-bottom: 0px;"  \
                              "border-radius: 5px"
                              
#define AUTOWPBOX_STYLE_RED  "background:" CL_PT_RED ";"     \
                              "border-style: solid     ;"     \
                              "border-width:  3px       ;"     \ 
                              "border-color: #002147 #002147 #002147 #002147 ;" \ 
                              "padding-left:  0.1em; padding-right: 0.1em;" \
                              "padding-top:   0px; padding-bottom: 0px;"  \
                              "border-radius: 5px"                                                               
                              
#define POPUP_OUTBOX_STYLE2   "background:"   CL_PT_BLUE ";"       \ 
                              "foreground:"   CL_PT_WHITE ";"        \
                              "padding:       0.3em;"                       \
                              "border-color:  white white white white;"     \
                              "padding-left:  0.5em; padding-right: 0.5em;" \
                              "padding-top:   10px; padding-bottom: 10px;"  \
                              "border-style:  solid;"                       \
                              "border-radius: 5px"        
                              
#define POPUP_OUTBOX_STYLE3   "background:"   CL_PT_BLUE ";"       \ 
                              "foreground:"   CL_PT_WHITE ";"        \
                              "padding:       0.3em;"                       \
                              "border-color:  white white white white;"     \
                              "padding-left:  0.5em; padding-right: 0.5em;" \
                              "padding-top:   1px; padding-bottom: 1px;"  \
                              "border-style:  solid;"                       \
                              "border-radius: 2px"                                                                                                                             

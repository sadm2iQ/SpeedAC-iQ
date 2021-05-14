V.1.0.6 DORJ2
----------------------------------------------------------------------------------
1)  Added Text alignment to every list page
2)  Delay of 0.1s after iQShowStartupMessage() to force display before filling QTMonitor queue during bootup;
3)  Spanish Mode and fault images added as condition 
4)  RefreshFaultScreenFlag and CurModeSetFlag in Display Handling task manage Spanish in a dynamic way
5)  Default MC and MP is now saved to flash
6)  string iQ_Version[1023]=__FILE__; Used to display the iQ software version
7)  Integrated things from Steve`s version SpeedAC iQ Net V1.0.5 20161115 EXCEPT FLASHSAVE flash int       MemRecipe, MemLanguage, MemLanguage_Cnt;
8)  Added Service Mode access control (Need QtMonitor.0.5.3.20161115.PT.update)
    Need to validate "TX_SM_INFOBOX" message to translation.ini infobox("The cycle must be OFF to access\n the Service Mode"); 
9)  Added SpeedAc iQ version check. If not matching, program not statrted and popup diplayed "Please update firmware"
10) Added Systec firmware compatibility check
11) Translation.ini file scans \\Shared folder for different version and applies these changes. If \\Shared empty or file identical, compiler uses original file in \\Appdata
    Note: Translation.ini file in\\Appdata always compiled at startup then checks for newer file in \\Shared subsequently
12) Limiting certain actions from Remote display unless in PremierTech UserLevel
13) Removed "dropevents()" for page change purposes and replaced with WaitPageActive function
14) Removed possibility of requesting page change to the actual page ie. can't call Auto page in Auto page
15) integrated widget_attribute (id, WIDGET_ATTRIBUTE_CLICK_EFFECT, CLICK_EFFECT_NONE); No more animation on unusable buttons
16) writeparameter("System","Stoponstringtoolong","0"); // Used to disable the String too long Watcher. For test purposes only
17) Fault Message Log written with Fault_Pointer. 
18) EVENT_TYPE_CONNECTION_ESTABLISHED reloads all important refresh data to synchronize with the controller.
19) writeparameter ("general","LightOffTime") to force screensaver. could be added to MP,MC?
20) "Scale_Switch" Added for multiple scale switching. Selects matching scales per unit type
21) Added "Check_Scale_Cfg()" to validate the correct Feed driver configuration before starting the cycle.
22) Removed Accessdb. Now in flash memory
23) Removed Access portion from MCdb. now ready flash memory directly
24) Removed Spanish Mode and Fault icons
25) Added WP direct entry in top left corner of Auto page
26) ***Removed*** See older versions for code: WPFillDb_Init(): temporay WPdbTemp database used to rebuild the WPdb and removes invalid entries or adds entries to complete the database 
27) Added Page 3 FlexIO Counter
28) Fixed Fault Page display for longuer text and moved Date column to the right
29) Need to fix CreateHeader function to integrate all new changes to the 58 already existing CreateHeaders in the project
30) Added Reset_FlexIOFlag = Execute to reset the logic loop every Automatic Mode start in VarInitCycle() instead of VarInitOff()
31) Autopage Layout Modification possibility:
    - beginlayout(LAYOUT_TYPE_HBOX, 0): Content spacing is at 6 pixels by default. Change to (LAYOUT_TYPE_HBOX, 0,3,0) for 3 pixels spacing
    - change WD_AUTO_DESCRIPTION to 155 and WD_AUTO_SPACE to 5
    It would be great if we could "Lock" A BeginLayout at a certain box dimension to let the info inside the box to change size dynamically within 
    this box size 
 


32) Added FlexIO Counter page and functionality. 
33)
34)
35)
36)
37)
38)
39)
40)
41)
42)
43)
44)
45)
46)
47)
48)
49)
50)



To Do:
1) widget_content_margins (int id, int left, int right, int top, int bottom). On all widgets to limit spacing between them
2) Adjust size of slider for count all in Batch page
3) Try to position grid sizes locked in space 
4) Try to use spacing in beginlayout to tighten the grid.
5) setlayoutoption (LAYOUT_OPTION_COLUMN_MINIMUM_WIDTH, "266,266,266"); //"left,top,right,bottom" 
6)
7)
8)
9)
10)
11)
12)
13)
14)
15)



Corriger MC defini dans flash. Modifier pour sauvegarder le default et ensuite comparer le db vs ?? pour loader le default dans le db vide
Quoi faire avec la memorisation des outputs FLEXIO? on devrait tester si le IO selectionné est toujours enabled avant de le mettre en marche et sinon le désactiver.
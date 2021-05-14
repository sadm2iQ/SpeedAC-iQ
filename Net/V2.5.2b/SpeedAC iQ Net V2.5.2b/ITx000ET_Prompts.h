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

 Project:                Project prompts  

 Creation date:          

 Author:                 
 
 List of modifications:

 Name        Date     Version     Modification:

*/

// available Languages:    German|English|Francais
#pragma(languages,"German,15,DE;English,15,[US,GB];French,15,FR")

           
/* ****************************************************************** */
/*     DORJ2 test Report.c                                            */
/* ****************************************************************** */

#define TX_SEC_UNIT               "s"
                                  
#define TX_PERC_UNIT              "%"  
                                   
#define TX_BATCH_NAME             "Batch Name|"\
                                  "Batch Name|"\
                                  "Nom de la batch"                                                                   

#define TX_BATCH_DETAILS          "Details|"\
                                  "Details|"\
                                  "Details"

#define TX_BATCH_COUNTALL         "Count All|"\
                                  "Count All|"\
                                  "Count All" 

#define TX_BATCH_PRESET           "Preset|"\
                                  "Preset|"\
                                  "Preset" 

#define TX_ID_ACTUAL_PROD         "SINCE RESET|"\
                                  "SINCE RESET|"\
                                  "SINCE RESET"

#define TX_BATCH_CURRENT_PROD     "CURRENT PRODUCTION:|"\
                                  "CURRENT PRODUCTION:|"\
                                  "PRODUCTION ACTUELLE:"

#define TX_BATCH_MIN_ACCEPTED     "Minimum Accepted|"\
                                  "Minimum Accepted|"\
                                  "Minimum Accepted"

#define TX_BATCH_RESIDUE          "Residue Weight|"\
                                  "Residue Weight|"\
                                  "Residue Weight"

#define TX_BATCH_MAX_ACCEPTED     "Maximum Accepted|"\
                                  "Maximum Accepted|"\
                                  "Maximum Accepted"
                                  
#define TX_ID_LIFETIME_PROD       "CUMULATED PRODUCTION|"\
                                  "CUMULATED PRODUCTION|"\
                                  "CUMULATED PRODUCTION"                                  

#define TX_ID_NOMINAL_WEIGHT      "Nominal weight|"\
                                  "Nominal weight|"\
                                  "Poid nominale"

#define TX_ID_WEIGHTMENTS_DONE    "Weighments Done|"\
                                  "Weighments Done|"\
                                  "Weighments Done"

#define TX_ID_ACCEPT_WEIGHS       "Accepted Weighments|"\
                                  "Accepted Weighments|"\
                                  "Accepted Weighments"

#define TX_ID_UNDERWEIGHT         "Underweight|"\
                                  "Underweight|"\
                                  "Underweight"

#define TX_ID_OVERWEIGHT          "Overweight|"\
                                  "Overweight|"\
                                  "Surpoid"                                  

#define TX_ID_TOTAL_WEIGHMENTS    "Total Weighments|"\
                                  "Total Weighments|"\
                                  "Total Weighments"

#define TX_ID_TOT_ACCEPT_WEIGHS   "Accepted Weighments|"\
                                  "Accepted Weighments|"\
                                  "Accepted Weighments"
                                        
#define TX_ID_TOTAL_WEIGHT        "Total Weight|"\
                                  "Total Weight|"\
                                  "Total Weight"
                                  
#define TX_LABEL_INFLATION        "Bag inflation"


                                   
#define TX_LABEL_NOMINAL_WEIGHT    "Nominal weight"

#define TX_DRIBBLE_FEED_TIME       "Dribble feed time|"\
                                   "Dribble feed time|"\
                                   "Temp petite ouv."
                                   
#define TX_LABEL_DRIBBLE_FEED_TIME "Dribble feed time"

#define TX_ID_OVER_WEIGHT          "Over weight|"\
                                   "Over weight|"\
                                   "Surpoid"
                                       
#define TX_LABEL_OVER_WEIGHT       "Over weight"

#define TX_MIN_FEEDING_OPENING     "Min. feeding Opening|"\
                                   "Min. feeding Opening|"\
                                   "Ouverture min. de remplis."
                                           
#define TX_LABEL_MIN_FEEDING_OPEN  "Minimum feeding opening"

#define TX_MAX_FEEDING_OPENING     "Max. feeding Opening|"\
                                   "Max. feeding Opening|"\
                                   "Ouverture max. de remplis."
                                           
#define TX_LABEL_MAX_FEEDING_OPEN  "Maximum feeding opening"

#define TX_SLOW_CYCLE_END          "Slow cycle end|"\
                                   "Slow cycle end|"\
                                   "Fin de cycle lente"
                                         
#define TX_SLOW_CYCLE_END_UNIT     ""





#define TX_CONFIRM_SAVERECIPE           "Do you really want to save\nall settings to recipe?|" \ 
                                        "Do you really want to save\nall settings to recipe?|" \
                                        "Voulez-vous vraiment sauvegarder\nles paramètres de la recette?" 
                                        
#define TX_CONFIRM_DELRECIPE            "Do you really want to remove\nthis recipe?|" \ 
                                        "Do you really want to remove\nthis recipe?|" \
                                        "Voulez-vous vraiment supprimer\ncette recette?"                                         
                                        
#define TX_CONFIRM_SAVEMP               "Do you really want to save\nall settings to Machine Params?|" \ 
                                        "Do you really want to save\nall settings to Machine Params?|" \
                                        "Voulez-vous vraiment sauvegarder\nles paramètres de Machine Params?"                                        
                                        
#define TX_CONFIRM_SAVEMC               "Do you really want to save\nall settings to Machine Config?|" \ 
                                        "Do you really want to save\nall settings to Machine Config?|" \
                                        "Voulez-vous vraiment sauvegarder\nles paramètres de Machine Config?"                                        

#define TX_CONFIRM_SAVEREPORT           "Do you really want to save\nall settings to REPORT?|" \
                                        "Do you really want to save\nall settings to REPORT?|" \
                                         "Voulez-vous vraiment sauvegarder\nles paramètres du rapport?"
                                         
#define TX_CONFIRM_SAVE2DEFAULT         "Do you really want to overwrite\nall settings to default?|" \ 
                                        "Do you really want to overwrite\nall settings to default?|" \
                                        "Voulez-vous vraiment écraser\nles paramètres par défaut?"

#define TX_CONFIRM_RESTOREDEFAULT       "Do you really want to restore all\n settings from default?|" \ 
                                        "Do you really want to restore all\n settings from default?|" \
                                        "Voulez-vous vraiment restaurer\nles paramètres par défaut?"

/* ****************************************************************** */
/*     DORJ2 test Recipe.h                                            */
/* ****************************************************************** */

#define TX_WEIGHTPERUNIT                  "Weight/Unit|"\
                                          "Weight/Unit|"\
                                          "PoidPar/Unite"
                                          
#define TX_RECIPES                  "Recipe|"\
                                    "Recipe|"\
                                    "Recette"

#define TX_DISCHARGETIME                  "Discharge time|"\
                                          "Discharge time|"\
                                          "Temp de décharge"
                                          
#define TX_ZERO                     "Zero|"\
                                    "Zero|"\
                                    "Zéro"
                                    
#define TX_TOPUPOffTIME                  "Top-up OFF time|"\
                                         "Top-up OFF time|"\
                                         "Temp OFF Top-up"
                                         
#define TX_TOPUPONTIME                  "Top-up ON time|"\
                                        "Top-up ON time|"\
                                        "Temp ON Top-up"
                                        
#define TX_BAGINFLATION                  "Bag inflation time|"\
                                         "Bag inflation time|"\
                                         "Temp inflation vessie"
                                         
#define TX_NOMINALWEIGHT                  "Nominal weight|"\
                                          "Nominal weight|"\
                                          "Poid nominale"
                                          
#define TX_DRIBBLETIME                  "Dribble feed time|"\
                                        "Dribble feed time|"\
                                        "Temp dribble feed"
                                        
#define TX_BULKTIME                  "Bulk feed time|"\
                                     "Bulk feed time|"\
                                     "Délai bulk feed"
                                     
#define TX_OVERWEIGHT                  "Over weight|"\
                                       "Over weight|"\
                                       "Surpoid"
                                       
#define TX_MINFEEDINGOPEN                  "Min. feeding Opening|"\
                                           "Min. feeding Opening|"\
                                           "Ouverture min. de remplis."
                                           
#define TX_MAXFEEDINGOPEN                  "Max. feeding Opening|"\
                                           "Max. feeding Opening|"\
                                           "Ouverture max. de remplis."
                                           
#define TX_SLOWCYCLEEND                  "Slow cycle end|"\
                                         "Slow cycle end|"\
                                         "Fin de cycle lent"
                                         
#define TX_STD_DEV                  "Std. Deviation|"\
                                    "Std. Deviation|"\
                                    "Déviation std"

#define TX_AVERAGE                  "Average|"\
                                    "Average|"\
                                    "Moyenne"
                                    
#define TX_ACC_UNITS                "Accepted Units|"\
                                    "Accepted Units|"\
                                    "Unités acceptées"
                                    
#define TX_WEIGHS_PER_UNIT          "Weighments/Unit|"\
                                    "Weighments/Unit|"\
                                    "Mesures/Unités"
                                    
#define TX_WEIGHS_DONE              "Weighments Done|"\
                                    "Weighments Done|"\
                                    "Mesures terminés"

/* ****************************************************************** */
/*     DORJ2 test ACCESS                                              */
/* ****************************************************************** */

#define  TX_LOGON                    "User access|"\
                                    "User access|"\
                                    "Acces utilisateur"  
#define  TX_USER                    "User name|"\
                                    "User name|"\
                                    "Nom d'utilisateur"      
#define  TX_PW                      "Password|"\
                                    "Password|"\
                                    "Mot de passe"
#define  TX_USER1                   "Premier Tech|"\
                                    "Premier Tech|"\
                                    "Premier Tech" //"Installation" User and password comparison is language sensitive. Must be the same in all languages
#define  TX_USER2                   "Supervisor|"\
                                    "Supervisor|"\
                                    "Supervisor" //"Superviseur|"
#define  TX_USER3                   "Operator|"\
                                    "Operator|"\
                                    "Operateur" // "Maintenance|"
#define  TX_USER4                   "Maintenance|"\
                                    "Maintenance|"\
                                    "Maintenance" //"Opérateur|"
#define  TX_LEVEL                   "User level|"\
                                    "User level|"\
                                    "Niveau d'accès" 
#define  TX_TIMEOUT                 "Timeout|"\
                                    "Timeout|"\
                                    "Délai"
#define  TX_NONE                    "None|"\
                                    "None|"\
                                    "Aucun"                                    
 
/* ****************************************************************** */
/*     DORJ2 test AutoPage.c                                          */
/* ****************************************************************** */                                    
                                    
#define TX_AUTOROW1_ID                "Target Weight:|"\
                                      "Target Weight:|"\
                                      "Poid cible:" 
                                                                           
#define TX_AUTOROW2_ID                "Average:|"\
                                      "Average:|"\
                                      "Moyenne:"

#define TX_AUTOROW3_ID                "Std Deviation:|"\
                                      "Std Deviation:|"\
                                      "Écart type:|"
 
#define TX_AUTOROW4_ID                "Last checked:|"\
                                      "Last checked:|"\
                                      "Dernier vérifié:"
                                                                                                                 
#define TX_AUTOROW11_ID               "Accepted Units:|"\
                                      "Accepted Units:|"\
                                      "Unités acceptés:"

#define TX_AUTOROW12_ID               "Weighments/Unit:|"\
                                      "Weighments/Unit:|"\
                                      "Mesures/Unités:"

#define TX_AUTOROW13_ID               "Weighments Done:|"\
                                      "Weighments Done:|"\
                                      "Mesures completées:"

#define TX_AUTOROW14_ID               "Presets/Unit:|"\
                                      "Presets/Unit:|"\
                                      "Presets/Unités:"


#define TX_AUTOROW22_ID                "Bulk Time:|"\
                                       "Bulk Time:|"\
                                       "Délai grande:"

#define TX_AUTOROW23_ID                "Dribble Time:|"\
                                       "Dribble Time:|"\
                                       "Délai petite:"

#define TX_AUTOROW24_ID                "Cycle Time:|"\
                                       "Cycle Time:|"\
                                       "Temp de cycle:"


/* ****************************************************************** */
/*          WP Management                                             */
/* ****************************************************************** */ 

#define TX_WPMANAGE_REN_STR_SRCE       "Source Name:|"\
                                       "Source Name:|"\
                                       "Nom source:"

#define TX_WPMANAGE_REN_STR_NEW        "New Name:|"\
                                       "New Name:|"\
                                       "Nouveau nom:"
                                       
#define TX_WPMANAGE_CPY_SRCE           "Source WP:|"\
                                       "Source WP:|"\
                                       "WP source:"

#define TX_WPMANAGE_CPY_DEST           "Dest. WP:|"\
                                       "Dest. WP:|"\
                                       "WP dest."  
                                       
#define TX_WPMANAGE_DEL_SRCE           "WP to Del:|"\
                                       "WP to Del:|"\
                                       "WP à suppr."                                                                            

#define TX_DELETE_WPMANAGE             "Do you really want to delete\nthis recipe?|"\  
                                       "Do you really want to delete\nthis recipe?|"\
                                       "Voulez-vous vraiment \neffacer la recette?"

#define TX_RENAME_WPMANAGE             "Do you really want to rename\nthis recipe?|"\  
                                       "Do you really want to rename\nthis recipe?|"\
                                       "Voulez-vous vraiment \nrenommer la recette?"
                                       
#define TX_COPY_WPMANAGE               "Do you really want to copy\nto this location?|"\  
                                       "Do you really want to copy\nto this location|"\
                                       "Voulez-vous vraiment \ncopier cette recette?"  
                                       
#define TX_WPMANAGECOPY_PAGE           "WP Copy|"\
                                       "WP Copy|"\
                                       "Copie de recette" 
                                       
#define TX_WPMANAGERENAME_PAGE         "WP Rename|"\
                                       "WP Rename|"\
                                       "Renommer la recette" 
                                       
#define TX_WPMANAGEDELETE_PAGE         "WP Delete|"\
                                       "WP Delete|"\
                                       "Supprimer la recette"   
                                       
/* ****************************************************************** */
/*          TD Management                                             */
/* ****************************************************************** */ 

#define TX_TDMANAGE_YEAR_ID            "Year:|"\
                                       "Year:|"\
                                       "Année:"

#define TX_TDMANAGE_MONTH_ID           "Month:|"\
                                       "Month:|"\
                                       "Mois:"                                       

#define TX_TDMANAGE_DAY_ID             "Day:|"\
                                       "Day:|"\
                                       "Jour:"
                                       
#define TX_TDMANAGE_HOUR_ID            "Hour:|"\
                                       "Hour:|"\
                                       "Heure:"
                                       
#define TX_TDMANAGE_MINUTE_ID          "Minute:|"\
                                       "Minute:|"\
                                       "Minute:"                                                                                                                 

#define TX_TDMANAGE_MENU               "Time & Date Management|"\
                                       "Time & Date Management|"\
                                       "Gestion heure et date" 
                                       
/* ****************************************************************** */
/*     DORJ2 I/O Database                                             */
/* ****************************************************************** */  

#define TX_IO                          "I/O Variable|"\
                                       "I/O Variable|"\
                                       "I/O Variable"
#define TX_ADDRESS                     "I/O adress|"\
                                       "I/O adress|"\
                                       "I/O adress" 
#define TX_ENABLE                      "I/O enabled|"\
                                       "I/O enabled|"\
                                       "I/O enabled" 
#define TX_SECTION                     "Section|"\
                                       "Section|"\
                                       "Section"  
#define TX_INPUT                       "Input?"\
                                       "Input?|"\
                                       "Input?" 

#define TX_IO_ON                          "On|"\
                                       "On|"\
                                       "On"
#define TX_IO_OFF                         "Off|"\
                                       "Off|"\
                                       "Off"                                       
#define TX_IO_NAME                     "Name|"\
                                       "Name|"\
                                       "Nom" 
#define TX_IO_ADDRESS                  "Address|"\
                                       "Address|"\
                                       "Adresse"                                       
#define TX_IO_ENABLE                   "Enable  |"\
                                       "Enable  |"\
                                       "Activé  " 
#define TX_IO_ENTER_ADDRESS            "Input Address here|"\
                                       "Input Address here|"\
                                       "Entrez l'adresse ici"
#define TX_IO_ENTER_ANALOG             "Input Analog Preset|"\
                                       "Input Analog Preset|"\
                                       "Entrez la consigne analogue"                                       
#define  TX_IO_CONFIG                  "I/O Config|"\
                                       "I/O Config|"\
                                       "Configuration I/Os|"
#define  TX_IO_STATE                   "State|"\
                                       "State|"\
                                       "État"
#define  TX_IO_VALUE                   "Value|"\
                                       "Value|"\
                                       "Valeur"                                                                              
#define  TX_IO_TEST                    "Test|"\
                                       "Test|"\
                                       "Test"
#define  TX_IO_NULL                    "X"             
#define  TX_ANALOG_INPUT               "Input|"\
                                       "Input|"\
                                       "Entrée"
#define  TX_ANALOG_OUTPUT              "Output|"\
                                       "Output|"\
                                       "Sortie"
                                                                                                                                                                                                                                  
#define TX_DRIBBLEFEED_ONLY            "Dribble feed only|"\
                                       "Dribble feed only|"\
                                       "Dribble feed only" 
#define TX_OK_BULKFEED                 "Ok for Bulk feed|"\
                                       "Ok for Bulk feed|"\
                                       "Ok for Bulk feed"
#define TX_OK_INTERM_FEED              "Ok for Interm feed|"\
                                       "Ok for Interm feed|"\
                                       "Ok for Interm feed"
#define TX_OK_FRO_DRIBBLEFEED          "Ok for Dribble feed|"\
                                       "Ok for Dribble feed|"\
                                       "Ok for Dribble feed"
#define TX_CATCH_GATE_OPEN             "Catch gate open|"\
                                       "Ok for Dribble feed|"\
                                       "Ok for Dribble feed"
#define TX_BULK_FEED                   "Bulk feed|"\
                                       "Bulk feed|"\
                                       "Bulk feed"
#define TX_INTERM_FEED                 "Intermediate feed|"\
                                       "Intermediate feed|"\
                                       "Intermediate feed"
#define TX_DRIBBLE_FEED                "Dribble feed|"\
                                       "Dribble feed|"\
                                       "Dribble feed"
#define TX_STREAM_REG                  "Steam regulator|"\
                                       "Steam regulator|"\
                                       "Steam regulator"
#define TX_CATCH_GATE                  "Catch gate|"\
                                       "Catch gate|"\
                                       "Catch gate"
#define TX_CATCH_GATE_DRIB             "Catch gate dribble|"\
                                       "Catch gate dribble|"\
                                       "Catch gate dribble"
#define TX_LOW_LEVEL_IN                "Low level sensor|"\
                                       "Low level sensor|"\
                                       "Low level sensor"
#define TX_HIGH_LEVEL_IN               "High level sensor|"\
                                       "High level sensor|"\
                                       "High level sensor"
#define TX_EMPTY_HOPPER                "Empty hopper|"\
                                       "Empty hopper|"\
                                       "Empty hopper"
#define TX_HOPPER_REFILL               "Hopper refilling|"\
                                       "Hopper refilling|"\
                                       "Hopper refilling"
#define TX_LOW_LEVEL_OUT               "Low level|"\
                                       "Low level|"\
                                       "Low level"


                                    
/* ****************************************************************** */
/*     DORJ2 test Others etc                                          */
/* ****************************************************************** */  

#define TX_CONFIRM_START               "Do you really want to start\nthe cycle?|"\
                                       "Do you really want to start\nthe cycle?|"\
                                       "Voulez-vous vraiment démarrer\nle cycle?"  
                                       
#define TX_CONFIRM_OFF                 "Do you really want to reset\nthe machine?|"\  
                                       "Do you really want to reset\nthe machine?|"\
                                       "Voulez-vous réinitialiser\nla machine?"
                                       
#define TX_CONFIRM_MANUAL              "You are about to reset the cycle\nand go to manual mode.\nDo you want to continue?|"

#define TX_ACCESS_PAGE                 "Access|"\
                                       "Access|"\
                                       "Page d'accès" 
                                       
#define TX_ACCESS_USER                 "User Level:|"\
                                       "User Level:|"\
                                       "Niveau d'accès:"
                                                                              
#define TX_INFO_PAGE                   "Information|"\
                                       "Information|"\
                                       "Information" 
                                                                             
#define TX_FAULT_PAGE                  "Faults|"\
                                       "Faults|"\
                                       "Fautes"

#define TX_FLT_HIST_PAGE               "Fault History Page|"\
                                       "Fault History Page|"\
                                       "Page d'historique de faute" 
                                                                              
#define TX_REPORT_PAGE                 "Production Report|"\
                                       "Production Report|"\
                                       "Rapport de Production"  

#define TX_BATCH_PAGE                  "Batch Report|"\
                                       "Batch Report|"\
                                       "Rapport de la batch" 
                                       
#define TX_RECIPE_ID                   "Select Recipe:|"\
                                       "Select Recipe:|"\
                                       "Sélectionnez une recette:"                                        
                                       
#define TX_RECIPE_MENU                 "Selected WP:|"\
                                       "Selected WP:|"\
                                       "WP sélect.:"   

#define TX_PAGE                        "page|"\
                                       "page|"\
                                       "page"   
                                       
#define TX_OF                          "of|"\
                                       "of|"\
                                       "de"   
                                       
#define TX_INPUTCONFIG_PAGE            "Input Configuration|"\
                                       "Input Configuration|"\
                                       "Configuration des entrées" 
                                       
#define TX_OUTPUTCONFIG_PAGE           "Output Configuration|"\
                                       "Output Configuration|"\
                                       "Configuration des sorties"  
                                                                                                                   
#define TX_INPUTTEST_PAGE              "Input Test|"\
                                       "Input Test|"\
                                       "Test des entrées" 
                                       
#define TX_OUTPUTTEST_PAGE             "Output Test|"\
                                       "Output Test|"\
                                       "Test des sorties" 

#define TX_ANALOGTEST_PAGE             "Analog Test|"\
                                       "Analog Test|"\
                                       "Test analog" 

#define TX_MACHINEPARAMETERS_PAGE      "Machine Parameters|"\
                                       "Machine Parameters|"\
                                       "Paramètres Machine" 

#define TX_MACHINECONFIG_PAGE          "Machine Config.|"\
                                       "Machine Config.|"\
                                       "Config. Machine" 

#define TX_GOTO_PAGE                   "Other Pages|"\
                                       "Other Pages|"\
                                       "Autres Pages" 
                                       
#define TX_WPMANAGE_PAGE               "WP Management|"\
                                       "WP Management|"\
                                       "Gestion de recette"                                                                               
                                       
#define TX_GOTO_FNCT                   "Other Functions|"\
                                       "Other Functions|"\
                                       "Autres Fonctions"                                       
                                       
#define TX_AUTO_RECIPE                 "WP Name:|"\
                                       "WP Name:|"\
                                       "Nom du WP:"
                                       
#define TX_HOLD_CYCLE                  "Hold Cycle|"\
                                       "Hold Cycle|"\
                                       "Pause le cycle"
                                       
#define TX_END_CYCLE                   "End Cycle|"\
                                       "End Cycle|"\
                                       "Fin de cycle"  
       
/* ****************************************************************** */
/*     Software Information                                           */
/* ****************************************************************** */ 
                                       
#define TX_CONTROLLER_ID               "SpeedAc IQ"

#define TX_PT_CONTROLLER_ID            "SpeedAc IQ Version:|"\
                                       "SpeedAc IQ Version:|"\
                                       "Version du SpeedAc IQ:"

#define TX_PT_SERIAL_ID                "Serial number:|"\
                                       "Serial number:|"\
                                       "Numéro de série:"
                                       
#define TX_PT_COMPANY_ID               "Premier Tech|"\
                                       "Premier Tech|"\
                                       "Premier Tech"

#define TX_PT_SERIAL_NB                 "123 456 789"

#define TX_PT_CONTROL_SW_VERS          "V.1.0.2"

#define TX_SCALE_TYPE_ID               "Scale Type:|"\
                                       "Scale Type:|"\
                                       "Type de balance:" 
                                       
#define TX_SCALE_TYPE                  "Net Weigher"  
 
#define TX_RTC_VERSION                "RTC Version:|"\
                                      "RTC Version:|"\
                                      "Version RTC:"  
                                        
#define TX_DEVICE_MODE                "Device:|"\
                                      "Device:|"\
                                      "Module:"       
                                      
#define TX_LANGUAGE_MODE              "Device:|"\
                                      "Device:|"\
                                      "Module:"     
                                      

#define TX_FAULT_RESET             "RESET|"\
                                   "RESET|"\
                                   "AQUITTÉ" 
                                   
#define TX_NO                       "Nr.|"\
                                    "No.|"\
                                    ""    
                                                                     
#define TX_NAME                     "Name|"\
                                    "Name|"\
                                    ""                                                                                                                                                                                                      
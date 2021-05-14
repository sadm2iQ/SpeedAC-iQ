/* ****************************************************************** */
/* ****************************************************************** */
/* *                                                                * */
/* *                                                                * */
/* *                                                                * */
/* *                 CHECK E Driver Header File                     * */
/* *                                                                * */
/* *                 Copyright by SysTec GmbH                       * */
/* *                                                                * */
/* ****************************************************************** */
/* ****************************************************************** */

/*

 Project:                Check_e_driver.h   

 Creation date:          August    2014

 Author:                 Michael Neuendorf 
                         Joachim Pauel

   Modifications:
   -------------
   Name        Date     Version  Description
   -----------------------------------------
 J.Pauel      14.10.16  1.5.3   1. Header implemented
                                2. Function check_set_acknowledge_weights and check_acknowledge_weight included.
                                3. New parameter in the function init_zero_check_control
                                4. New parameter in the function check_weight_msg

 J.Pauel      08.11.16  1.5.4   1. implemented datatype struct
 
 J.Pauel     14.06.16   1.5.5   1. The function CheckAnyValidEval is inserted. This can be used to 
                                   check whether a valid evaluation parameter exists at all.

M.Neuendorf  14.08.17  1.5.6   1. The check_set_pusher function is extended by the Pusher on Error.
J.Pauel      25.08.17          2. Added the pass parameters to the CheckAnyValidEvalParameter function.

 J.Pauel     15.06.18   1.5.7   1. Bug in function test_zero_control and init_zero_check_control fixed

*/

#define  CHECK_E_DRIVER_MAJOR         "1"
#define  CHECK_E_DRIVER_MINOR         "5"
#define  CHECK_E_DRIVER_PATCH         "7"
#define  CHECK_E_DRIVER_VERSION_NO    CHECK_E_DRIVER_MAJOR "." CHECK_E_DRIVER_MINOR "." CHECK_E_DRIVER_PATCH



struct DynGenPar
{
bool         ApprovalFlag;             // approved_weighing,
bool         CatchWeigherFlag;         // catchweigher,
bool         CheckDynFlag;             // dynamic_mode,
int          SampleRate;
float        MinZeroSettingTime;
int          AutomaticZeroMode;
int          AutomaticZeroPeriod;
int          MinimumOffBeltDistance;
int          MaximumMeasuringTime;
int          MeasurementStartMode;
int          MeasurementStopMode;
int          LightBarrierDebounceTime;
int          WarmUpTime;              
int          MinimumLoad;             
int          TranspControlMode;           
int          SpeedControlMode;   
int          SpeedControlPlusTol;         
int          SpeedControlMinusTol;         
int          SpeedControlDistance;
int          ClassificationEnable;
int          EvaluationControlMode;               
}
DynGenPar  GeneralCheckParameter;

struct DynEvaPar
{
// evaluation paramtert
int           EvaluationParameters;
int           PrimaryFilterTime;
int           EvaluationFilterSize;
float         BeltSpeed;
string        CorrectingPolynomial [100];  
int           StartOffset;                  // ms
int           StopOffset;                   // ms
float         ManualThreshold;
int           MeasuringTime;                //ms
float         MinimumWeight;
float         MaximumWeight;
}
DynEvaPar EvaluationCheckParameter;


struct WgtRes
{
bool          WeightValid;
int           WeightError;
float         Price;
string        Zone [3];
float         WeightAvg;     
float         WeightStdDev;  
float         DevAvg;
float         DevStddev;
float         Speed;
int           StatisticValues;  
int           PieceMissed;       
}
WgtRes WeighingResult;

// return string from the scale driver!
#define zTU2                 "TU2"
#define zTU1                 "TU1"
#define zTO1                 "TO1"
#define zTO2                 "TO2"
#define zOK                  "OK"



/******************************************************************************/
/* types used by the check driver                                             */
/******************************************************************************/
// check statusses as returned by check_status_msg
enum
{
/*  0 */  CHECK_STATUS_UNSET,
/*  1 */  CHECK_STATUS_OK,
/*  2 */  CHECK_STATUS_ADM_THREAD_NOT_RUNNING,
/*  3 */  CHECK_STATUS_ZERO_SETTING_RECOMMENDED,
/*  4 */  CHECK_STATUS_ZERO_SETTING_REQUIRED,
/*  5 */  CHECK_STATUS_ZERO_SETTING_ACTIVE,
/*  6 */  CHECK_STATUS_UNUSED,
/*  7 */  CHECK_STATUS_TRANSPORT_ERROR,              
/*  8 */  CHECK_STATUS_POWER_UP_ZERO,                 
/*  9 */  CHECK_STATUS_AUTOMATIC_TARE,
/* 10 */  CHECK_STATUS_SERVICE_MODE,
/* 11 */  CHECK_STATUS_NOT_INITIALIZED,
/* 12 */  CHECK_STATUS_CALIBRATION_ERROR,
/* 13 */  CHECK_STATUS_CALCULATION_SCHEDULING_ERROR,
/* 14 */  CHECK_STATUS_ADM_READ_ERROR,
/* 15 */  CHECK_STATUS_ZERO_SETTING_SUCCEEDED,
/* 16 */  CHECK_STATUS_SPEED_ERROR,                   
/* 17 */  CHECK_STATUS_INITIALIZATION_DONE,
/* 18 */  CHECK_STATUS_EVALUATION_ERROR,
/* 19 */  CHECK_STATUS_ZERO_SETTING_SKIPPED,
/* 20 */  __CHECK_STATUS_MAX
};

// check errors as returned by check_weight_msg
enum   // Error=
{
/*  0 */  CHECK_ERROR_NO_ERROR,
/*  1 */  CHECK_ERROR_NO_WEIGHT,
/*  2 */  CHECK_ERROR_NO_DATA,
/*  3 */  CHECK_ERROR_NO_MAXIMUM,
/*  4 */  CHECK_ERROR_CALCULATE_VALUE,
/*  5 */  CHECK_ERROR_TRANSPORT,                      // this message would not be come
/*  6 */  CHECK_ERROR_PEAK_TOO_SHORT,
/*  7 */  CHECK_ERROR_PEAK_TOO_LONG,
/*  8 */  CHECK_ERROR_CALCULATE_DERIVATIVE,
/*  9 */  CHECK_ERROR_NO_PEAK_PLATEAU,
/* 10 */  CHECK_ERROR_FILTER_CALCULATION,
/* 11 */  CHECK_ERROR_SCHEDULING_CALCULATION,
/* 12 */  CHECK_ERROR_WEIGHT_BELOW_MINIMUM_LOAD,
/* 13 */  CHECK_ERROR_SPEED_OUTSIDE_RANGE,           // this message will not come
/* 14 */  CHECK_ERROR_WEIGHT_ABOVE_MAXIMUM_LOAD,
/* 15 */  CHECK_ERROR_ADM_READ,
/* 16 */  CHECK_ERROR_OBJECT_IGNORED,                    
/* 17 */  CHECK_ERROR_PLATEAU_INCORRECTLY_DETECTED,      
/* 18 */  __CHECK_ERROR_MAX
};


#ifndef SYSTEM_EVENT_ENUM
  #define SYSTEM_EVENT_ENUM
  enum
  {
/*  0 */  SYSTEM_EVENT_NONE,
/*  1 */  SYSTEM_EVENT_SERVICE_MODE_ENTERED,
/*  2 */  SYSTEM_EVENT_SERVICE_MODE_LEFT,
/*  3 */  SYSTEM_EVENT_WSS_CONNECTED,
/*  4 */  SYSTEM_EVENT_WSS_DISCONNECTED,
/*  5 */  SYSTEM_EVENT_WSS_DATA_PENDING,
/*  6 */  SYSTEM_EVENT_SCALE_DRIVER_WEIGHT,
/*  7 */  SYSTEM_EVENT_SCALE_DRIVER_ERROR,
/*  8 */  SYSTEM_EVENT_SCALE_DRIVER_STATUS,
/*  9 */  SYSTEM_EVENT_APPLICATION_CONFIGURATION,
/* 10 */  SYSTEM_EVENT_APPLICATION_SETTINGS,
/* 11 */  SYSTEM_EVENT_APPLICATION_JSON,
/* 12 */  SYSTEM_EVENT_ERROR_MESSAGE,
/* 13 */  SYSTEM_EVENT_SCALE_DRIVER_DEBUG,
/* 14 */  SYSTEM_EVENT_APPLICATION_CONTROL,
/* 15 */  SYSTEM_EVENT_SCALE_DRIVER_MESSAGE,
/* 16 */  SYSTEM_EVENT_SCALE_SETTINGS,
/* 17 */  SYSTEM_EVENT_APPLICATION_SAVE_REQUEST,
/* 18 */  SYSTEM_EVENT_APPLICATION_SAVE_ENABLED,
/*    */  // define a maximum element for the system event
/* 19 */  __SYSTEM_EVENT_MAX
  };
#endif  // SYSTEM_EVENT_ENUM

// scale driver message types
enum
{
  CHECK_SCALE_MESSAGE_TYPE_NONE,
  CHECK_SCALE_MESSAGE_TYPE_PUSHER,
  __CHECK_SCALE_MESSAGE_TYPE_MAX
};


// check measurement modes as returned by check_config_parameters
enum
{
  CHECK_MEASUREMENT_START_MODE_OFF,
  CHECK_MEASUREMENT_START_MODE_AUTO,
  CHECK_MEASUREMENT_START_MODE_MANUAL,
  CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_OPEN,
  CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_CLOSED,
  CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_OPEN_WL,
  CHECK_MEASUREMENT_START_MODE_LIGHTBARRIER_NORMALLY_CLOSED_WL,
};

enum
{
  CHECK_MEASUREMENT_STOP_MODE_OFF,
  CHECK_MEASUREMENT_STOP_MODE_AUTO,
  CHECK_MEASUREMENT_STOP_MODE_MANUAL,
  CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_OPEN,
  CHECK_MEASUREMENT_STOP_MODE_MEASURING_TIME,
  CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_CLOSED,
  CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_OPEN_WL,
  CHECK_MEASUREMENT_STOP_MODE_LIGHTBARRIER_NORMALLY_CLOSED_WL,
    
};

// check zero modes as returned by check_config_parameters
enum
{
  CHECK_ZERO_MODE_OFF,
  CHECK_ZERO_MODE_AUTOMATIC,
};

// check pusher trigger points for check_set_pusher
enum
{
  PUSHER_TRIGGER_CONTROL_OFF,
  PUSHER_TRIGGER_CONTROL_START,
  PUSHER_TRIGGER_CONTROL_STOP,
  PUSHER_TRIGGER_CONTROL_SEPARATE,
};

// transport control mode
enum
{
  TRANSPORT_CONTROL_MODE_OFF,
  TRANSPORT_CONTROL_MODE_PUSH,
  TRANSPORT_CONTROL_MODE_STOP
};

// speed control mode
enum
{
  SPEED_CONTROL_MODE_OFF,
  SPEED_CONTROL_MODE_PUSH,
  SPEED_CONTROL_MODE_STOP
};

// evaluation control mode
enum
{
  EVALUATION_CONTROL_MODE_OFF,
  EVALUATION_CONTROL_MODE_PUSH,
  EVALUATION_CONTROL_MODE_STOP,
};

// price unit for price calculation
enum
{
  PRICE_UNIT_PER_KG,
  PRICE_UNIT_PER_100_GRAM,
  PRICE_UNIT_PER_POUND,
  __PRICE_UNIT_MAX
};

/*######################################################################*/
/* interface description                                                */
/*######################################################################*/

/*

#########################################################################
#  changes the operating mode to static weighing                        #
#########################################################################
bool check_static_mode (int handle,
                        int scaleno);

#########################################################################
#  changes the operating mode to check weighing                         #
#########################################################################
bool check_dynamic_mode (int handle,
                         int scaleno);

#########################################################################
#  set the rating parameters                                            # 
#########################################################################
bool check_set_period  (int handle,
                        int scaleno,
                        float seconds)

#########################################################################
#  set the rating parameters                                            # 
#########################################################################
bool check_set_rating_parameters (int    handle,
                                  int    scaleno,
                                  float  basic_price,
                                  int    price_unit,
                                  string currency,
                                  float  target_weight,
                                  float  weight_tu2,
                                  float  weight_tu1,
                                  float  weight_to1,
                                  float  weight_to2);

#########################################################################
#  reset the statistics                                                 # 
#########################################################################
bool check_reset_statistics (int handle,
                             int scaleno);

#########################################################################
#  reset a transport error                                              #
#########################################################################
bool check_reset_transport_error (int handle,
                                  int scaleno);


##################################################################################
#  lets the driver calculate a correcting polynomial                             #
#  reference_weights: solidus-separated string of double values                  #
#  actual_weights:    solidus-separated string of double values                  #
#  *correction:       solidus-separated string containing the correction values  #
##################################################################################
bool check_calculate_correction (int    handle,
                                 int    scaleno,
                                 string reference_weights,
                                 string actual_weights,
                                 string *correction);

#########################################################################
#  evaluates a weight message from the driver                           #
#########################################################################
bool check_weight_msg (int    scaleno,
                       WgtRes  *WeighingReult);
            

#########################################################################
#  evaluates a status message from the driver                           #
#########################################################################
bool check_status_msg (int scaleno,
                       int *status);

###############################################################################
#  evaluates the type of a scale message from the driver                      #
#  scale messages may have different types, so use this function to determine #
#  the contained type and call the corresponding evaluation function then     #
###############################################################################
bool check_scale_msg_type (int  scaleno,
                           int  *type);        

#########################################################################
#  evaluates the pusher information of a scale message from the driver  #
#########################################################################
bool check_scale_msg_pusher (int   scaleno,
                             float *threshold_weight,
                             int   *output_number,
                             int   *trigger_time_ms,
                             int   *on_time_ms);

#########################################################################
#  returns an appropriately formatted string for a pusher control       #
#########################################################################
string check_pusher_control (float threshold_weight,
                             int    output_number,
                             int    trigger_time_ms,
                             int    on_time_ms);

#########################################################################
#  applies the pusher parameters to the CheckE driver                   #
#########################################################################
bool check_set_pusher (int    handle,
                       int    scaleno,
                       int    pusher_trigger_control,
                       string pusher_lower,
                       string pusher_higher,
                       string pusher_on_error);

#########################################################################
#  enable classification                                                #
#########################################################################
bool check_enable_classification (int  handle,
                                  int  scaleno,
                                  bool enable);



#########################################################################
#  check the actual status of dynamic mode                              #
#########################################################################
bool check_classification_enabled (int    handle,
                                   int    scaleno,
                                   string *enabled);

#########################################################################
#  reads the check configuration parameters                             #
#########################################################################     
bool check_config_parameters (int       handle,
                              int       scaleno,
                              DynGenPar *GeneralParameter);

#########################################################################
#  reads the currently selected evaluation parameters                   #
#########################################################################     
bool check_selected_parameters  (int handle,
                                 int scaleno,
                                 int *parameterno);

#########################################################################
#  selects the evaluation parameters                                    #
#########################################################################     
bool check_select_parameters (int    handle,
                              int    scaleno,
                              int    parameterno,
                              string product_id);

#########################################################################
#  reads the evaluation parameter details of the given parameter set    #
#########################################################################     
bool check_parameter_details (int        handle,
                              int        scaleno,
                              int        parameterno,  // -1 because the driver works zero based
                              DynEvaPar *EvaluationCheckParameter
                              bool      *valid);

#########################################################################
#  reads the current zero weight values                                 #                     
#########################################################################      
bool check_zero_weight (int   handle,
                        int   scaleno,
                        float *power_up_zero,
                        float *current_zero);

#########################################################################
#  reads the current tare weight                                        #                     
#########################################################################      
bool check_tare_weight (int   handle,
                        int   scaleno,
                        float *tare_weight);


#########################################################################
#  reads the current static weight on the scale                         #                     
#########################################################################      
bool check_static_weight (int    handle,
                          int   scaleno,
                          float *static_gross,
                          float *static_tare,
                          float *static_net,
                          float *static_net_hires);

#########################################################################
#  remove a weight from the statistics                                  #
#########################################################################      
bool check_remove_weight (int   handle,
                          int   scaleno,
                          float weight);

##############################################################################
#  tell the driver to ignore an object at the given position (=object count) #
#    the command must be send before product into the start light            #
#    barrier commes.                                                         #
#    positon = 0 mean the next object                                        #
#    push = 0 object not pushed (only if a pusher configured)                #
#           1 object pushed (only if a pusher configured)                    #
##############################################################################      
bool check_ignore_object (int handle,
                          int scaleno,
                          int position
                          bool push);

#########################################################################
#   query the remaining time until the next zero setting requirement    #
#########################################################################      
bool check_remaining_uptime (int    handle,
                             int    scaleno,
                             int    *minutes,
                             int    *seconds,
                             string *remaining_time);


#########################################################################
#   query the evaluation statistics                                     #
#########################################################################      
bool check_evaluation_statistics (int handle,
                                  int scaleno,
                                  int *piece_total,
                                  int *piece_evaluable,
                                  int *piece_unevaluable,
                                  int *piece_pushed,
                                  int *piece_accepted
                                  int *piece_missed);


#########################################################################
#  query the rating statistics                                          #
#########################################################################      
bool check_rating_statistics (int handle,
                              int scaleno,
                              int *piece_tu2,
                              int *piece_tu1,
                              int *piece_ok,
                              int *piece_to1,
                              int *piece_to2);
                              
#########################################################################
#  checks whether the check driver is configured for the given scale    #
#########################################################################      
bool check_driver_installed (int  handle,
                             int   scaleno);



#########################################################################
#  Open the pors to the check dyn driver and test the default           #
#  check_config_parameters and Checks the IO configuration              #
#########################################################################      
bool start_check_driver (int    handle_I,    // conection from the main-task
                         int    handle_II,   // conection from the CheckweighingTask
                         int    scaleno, 
                         int    *io_offset, 
                         bool   *fOnly_Pim_Configured, 
                         string no_driver_msg, 
                         string no_pim_msg);   



#########################################################################
#  returns the calculated price                                         # 
#########################################################################      
decimal check_calculate_price (decimal   valuta);


#########################################################################
#   Check the status of the light barrier                               # 
#########################################################################      
bool chk_scl_free_and_no_lgt_br  (int    measurement_start_mode, 
                                  int    measurement_stop_mode); 


#########################################################################
#   read all old message                                                # 
#########################################################################      
void  READ_ALL_OLD_MSG();


#########################################################################
#  returns the staus of dynamic mode                                    #
#########################################################################      
bool IsDynamicModeActive (void)      // Returns true if the dynamic mode is started




      
*********************************************************************************
//   only for static mode                                                         
*********************************************************************************
void init_zero_check_control (int Outputs, 
                              int O_SET_ZERO0,
                              int AutomaticZeroPeriod);


bool test_zero_control (int ProcessState, 
                        int ProcessState_II,   // last process step bevor error steps  
                        int Outputs, 
                        int O_SET_ZERO,
                        int AutomaticZeroPeriod);


string  get_zone_static (decimal lnet, 
                         decimal ProductWgt_TU2, 
                         decimal ProductWgt_TU1, 
                         decimal ProductWgt_TO1, 
                         decimal ProductWgt_TO2);

*********************************************************************************
// End of only for static mode
*********************************************************************************


*********************************************************************************
new for driver ADM_CHECK_468E.1.5.12.r7250.update
*********************************************************************************

#########################################################################
#  Enable Disable the function check_acknowledge_weight                 #
#########################################################################  
bool check_set_acknowledge_weights (int handle,
                                    int scaleno,
                                    bool enabled);
  
#########################################################################
#  confirm a weight                                                     #
#########################################################################
bool check_acknowledge_weight (int handle,
                               int scaleno);


#########################################################################
#  Function to check that there is any valid evaluation parameter       #
#########################################################################
bool CheckAnyValidEvalParameter (); 
 
*/




/******************************************************************************/
/* include the object file                                                    */
/******************************************************************************/
#ifdef CHECK_E_DRIVER_DEBUG
  #include "check_e_driver.ccf"
#else
  //#binary "check_e_driver.obj"
  #binary "check_e_driver_pt_V1.5.7.obj"
#endif

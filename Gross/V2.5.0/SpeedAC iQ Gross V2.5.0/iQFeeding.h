#ifndef IQ_FEEDING_H
#define IQ_FEEDING_H

//#define IQ_FEEDING_DEBUG
#define IQ_FEEDING_WITH_PROTOTYPES

/****************************************************************************/
// names of available feeding algorithms
/****************************************************************************/
#define IQ_FEEDING_ALGORITHM_SMART    "iqsmartfeed"
#define IQ_FEEDING_ALGORITHM_FLASH    "iqflashfeed"
#define IQ_FEEDING_ALGORITHM_VALVE    "iqvalvebagger"
#define IQ_FEEDING_ALGORITHM_PLOOP    "iqploop"
#define IQ_FEEDING_ALGORITHM_HELPER   "iqhelper"
#define IQ_FEEDING_ALGORITHM_SCALE    "iqscale"
#define IQ_FEEDING_ALGORITHM_LIGHT    "iqlightfeed"
#define IQ_FEEDING_ALGORITHM_DEFAULT  IQ_FEEDING_ALGORITHM_SCALE

/****************************************************************************/
// names of available analog output modules
/****************************************************************************/
#define IQ_FEEDING_ANALOG_MODULE_DAM  "dam"
#define IQ_FEEDING_ANALOG_MODULE_DAU  "dau"

enum
{
  ANALOG_OUTPUT_MODE_0_10V,
  ANALOG_OUTPUT_MODE_2_10V,
  ANALOG_OUTPUT_MODE_0_20mA,
  ANALOG_OUTPUT_MODE_4_20mA,
};

/****************************************************************************/
// names of available interpolation algorithms
/****************************************************************************/
#define IQ_FEEDING_INTERPOLATION_LINEAR_INTERPOLATION   "linear_interpolation"
#define IQ_FEEDING_INTERPOLATION_ARITHMETIC_MEAN        "arithmetic_mean"
#define IQ_FEEDING_INTERPOLATION_BEST_MEAN              "best_mean"

#ifdef IQ_FEEDING_WITH_PROTOTYPES

/****************************************************************************/
// name of available hires resolutions
/****************************************************************************/
enum
{
  HIRES_X10,
  HIRES_X100,
}

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/*** REQUIRED COMMON FUNCTIONS                                            ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

/****************************************************************************/
// open a connection to the scale host at the
// IP address or host name
/****************************************************************************/
bool iQOpenConnection
    (int channel,
    string host);

/****************************************************************************/
// close any open connection on the channel
/****************************************************************************/
void iQCloseConnection
    (int channel);

/****************************************************************************/
// registers for receiving events from within the calling task
/****************************************************************************/
void iQRegisterEventReception
    (void);

/****************************************************************************/
// waits for an event from an iQFeeding driver and returns its content
/****************************************************************************/
bool iQReadEvent
    (int *scaleno,
    float *filled_weight,
    string *status,
    float *fast_slow_switch_weight,
    float *slow_cutoff_weight,
    float *slow_filling_duration,
    float *fast_filling_duration,
    float *filling_duration,
    float *overall_duration);

bool iQReadEventStats
    (int *scaleno,
    float *controlled_fast_time,
    float *controlled_slow_time,
    float *stable_fast_flow,
    float *stable_slow_flow,
    float *fast_flow_fluctuation,
    float *slow_flow_fluctuation);

/****************************************************************************/
// load the feeding algorithm for the scale
/****************************************************************************/
bool iQSetAlgorithm
    (int channel,
    int scaleno,
    string algorithm);

/****************************************************************************/
// set the valve output signal which is active during each feeding
/****************************************************************************/
bool iQSetEnableSignalOutput
    (int channel,
    int scaleno,
    int output,
    int preserve_in_learning);

/****************************************************************************/
// set the target weight for the feeding
/****************************************************************************/
bool iQSetTargetWeight
    (int channel,
    int scaleno,
    float target_weight);

/****************************************************************************/
// clear the control parameters, i.e. start a new learning
// phase for the current product
/****************************************************************************/
bool iQClearControlParameters
    (int channel,
    int scaleno);

/****************************************************************************/
// starts the next feeding and begins a new cycle
/****************************************************************************/
bool iQFeedingStart
    (int channel,
    int scaleno,
    bool check_target_weight);

/****************************************************************************/
// starts debugging the outputs
/****************************************************************************/
bool iQFeedingDebugOutput
    (int channel,
    int scaleno,
    float analog_output,
    int digital_speed,
    bool enable_signal);

/****************************************************************************/
// stops any ongoing feeding
/****************************************************************************/
bool iQFeedingStop
    (int channel,
    int scaleno);

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/*** REQUIRED ALGORITHM-SPECIFIC FUNCTIONS                                ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

/****************************************************************************/
// reads the calibrated filter size
/****************************************************************************/
bool iQReadCalFilterSize
    (int channel,
    int scaleno,
    int *cal_filter_size);

/****************************************************************************/
// set the control parameters for the current product
/****************************************************************************/
bool iQSmSetControlParameters
    (int channel,
    int scaleno,
    string fast_avg_points,
    string slow_avg_points,
    string slow_itp_points,
    float switch_time);

/****************************************************************************/
// fetch the control parameters of the current product,
// i.e. the parameters that were gathered during the learning
// phase of the driver
/****************************************************************************/
bool iQSmGetControlParameters
    (int channel,
    int scaleno,
    string *fast_avg_points,
    string *slow_avg_points,
    string *slow_itp_points,
    float *switch_time,
    bool *learning_completed);

/****************************************************************************/
// set analog output mode using the specified module
/****************************************************************************/
bool iQSmSetAnalogOutput
    (int channel,
    int scaleno,
    int output_index,
    string module_name,
    int module_number,
    int output_mode,
    float slow_percentage,
    float fast_percentage);

/****************************************************************************/
// set digital output mode using the specified output signals
/****************************************************************************/
bool iQSmSetDigitalOutput
    (int channel,
    int scaleno,
    int fast_output,
    int slow_output,
    bool fast_enables_slow);

/****************************************************************************/
// setup the analog output using the specified module
/****************************************************************************/
bool iQFlSetAnalogOutput
    (int channel,
    int scaleno,
    string module_name,
    int module_number,
    int output_mode,
    float minimum_opening_percentage,
    float maximum_opening_percentage);

/****************************************************************************/
// set the closing function
/****************************************************************************/
bool iQFlSetFeedingLimits
    (int channel,
    int scaleno,
    float start_percentage,
    float control_percentage);

/****************************************************************************/
// set the control parameters for the current product
/****************************************************************************/
bool iQFlSetControlParameters
    (int channel,
    int scaleno,
    string fast_points,
    string deviation_points);

/****************************************************************************/
// fetch the control parameters of the current product
/****************************************************************************/
bool iQFlGetControlParameters
    (int channel,
    int scaleno,
    string *fast_points,
    string *deviation_points,
    bool *learning_completed);

/****************************************************************************/
// set the switch weight from bulk feeding to reducing the output
/****************************************************************************/
bool iQFlSetSwitchWeight
    (int channel,
    int scaleno,
    float switch_weight);

/****************************************************************************/
// set the requested control time, i.e. the duration of closing the gate
/****************************************************************************/
bool iQFlSetControlTime
    (int channel,
    int scaleno,
    float control_time);

/****************************************************************************/
// sets the output level at which the active control loop starts
/****************************************************************************/
bool iQFlSetReduceOutput
    (int channel,
    int scaleno,
    float output_reduce);

/****************************************************************************/
// sets the setpoints for the feeding
/****************************************************************************/
bool iQVbSetPoints
    (int channel,
    int scaleno,
    float fast_setpoint,
    float slow_setpoint,
    float switch_time);

/****************************************************************************/
// sets the outputs for the feeding process
// outputs are given in a colon-separated list of bits, for instance 0:2:3
/****************************************************************************/
bool iQVbSetOutputs
    (int channel,
    int scaleno,
    string claimed_outputs,
    string fast_outputs,
    string slow_outputs);
    
/****************************************************************************/
// sets the number of values after which the correction starts
/****************************************************************************/
bool iQVbSetCorrStartSize
    (int channel,
    int scaleno,
    int corr_start_size);

/****************************************************************************/
// set the parameters of the helper algorithm
/****************************************************************************/
string iQHlpGenerateProgramPart
    (float duration,
    string function);

bool iQHlpSetParameters
    (int channel,
    int scaleno,
    float emergency_stop_weight,
    string program);

/****************************************************************************/
// set analog output mode using the specified module
/****************************************************************************/
bool iQPLoopSetAnalogOutput
    (int channel,
    int scaleno,
    int output_index,
    string module_name,
    int module_number,
    int output_mode);

bool iQPLoopSetParameters
    (int channel,
    int scaleno,
    int loop_index,
    float slow_percentage,
    float fast_percentage,
    float cut_off_weight,
    float kp);

/****************************************************************************/
// set the control parameters for the current product
/****************************************************************************/
bool iQLightSetControlParameters
    (int channel,
    int scaleno,
    string slow_avg_points,
    string slow_itp_points,
    float switch_time);

/****************************************************************************/
// fetch the control parameters of the current product,
// i.e. the parameters that were gathered during the learning
// phase of the driver
/****************************************************************************/
bool iQLightGetControlParameters
    (int channel,
    int scaleno,
    string *slow_avg_points,
    string *slow_itp_points,
    float *switch_time,
    bool *learning_completed);

/****************************************************************************/
// set analog output mode using the specified module
/****************************************************************************/
bool iQLightSetAnalogOutput
    (int channel,
    int scaleno,
    int output_index,
    string module_name,
    int module_number,
    int output_mode,
    float slow_percentage,
    float fast_percentage);

/****************************************************************************/
// set digital output mode using the specified output signals
/****************************************************************************/
bool iQLightSetDigitalOutput
    (int channel,
    int scaleno,
    int fast_output,
    int slow_output,
    bool fast_enables_slow);
    
bool iQLightSetRequestedFastFillDuration
    (int channel,
    int scaleno,
    float duration);
    
bool iQLightSetRequestedSlowFillDuration
    (int channel,
    int scaleno,
    float duration);
    
bool iQLightSetMinimumSlowFillDuration
    (int channel,
    int scaleno,
    float duration);

bool iQLightSetSlowCutoffWeight
    (int channel,
    int scaleno,
    float weight);

bool iQLightSetSlowStatsPercentage
    (int channel,
    int scaleno,
    float percentage);

bool iQLightReadEvent
    (int *scaleno,
    float *filled_weight,
    string *status,
    float *fast_slow_switch_weight,
    float *slow_cutoff_weight,
    float *slow_filling_duration,
    float *filling_duration,
    float *overall_duration,
    float *controlled_slow_time,
    float *fast_weight_maximum,
    float *fast_weight_minimum,
    float *slow_flow_average,
    float *slow_flow_stddev);

/****************************************************************************/
/***                                                                      ***/
/***                                                                      ***/
/*** OPTIONAL FUNCTIONS                                                   ***/
/***                                                                      ***/
/***                                                                      ***/
/****************************************************************************/

/****************************************************************************/
// set the emergency stop weight during the fast feeding
/****************************************************************************/
bool iQSetEmergencyStopFast
    (int channel,
    int scaleno,
    float emergency_stop_weight);

/****************************************************************************/
// set the threshold value for load detection
/****************************************************************************/
bool iQSetThreshold
    (int channel,
    int scaleno,
    float threshold_weight,
    float attack_time);

/****************************************************************************/
// set the timing requirements for the slow feeding
/****************************************************************************/
bool iQSetSlowFillTimes
    (int channel,
    int scaleno,
    float minimum_slow_fill_time,
    float requested_slow_fill_time);

/****************************************************************************/
// set the interpolation mode for the prediction
/****************************************************************************/
bool iQSetInterpolationMode
    (int channel,
    int scaleno,
    string interpolation_mode_name);

/****************************************************************************/
// set the size of the filter during fast feeding
/****************************************************************************/
bool iQSetFastFilterSize
    (int channel,
    int scaleno,
    int size);

/****************************************************************************/
// set the size of the filter during slow feeding
/****************************************************************************/
bool iQSetSlowFilterSize
    (int channel,
    int scaleno,
    int size);

/****************************************************************************/
// fetch the current update rate
/****************************************************************************/
bool iQGetUpdateRate
    (int channel,
    int scaleno,
    int *update_rate);

/****************************************************************************/
// fetch the current voltage in mV of the load cell
/****************************************************************************/
bool iQGetCurrentVoltage
  (int channel,
  int scaleno,
  float *voltage_mv);

/****************************************************************************/
// set optional parameters for the learning of the smart feed
/****************************************************************************/
bool iQSmSetLearnDelay1
    (int channel,
    int scaleno,
    float learn_delay1);

bool iQSmSetLearnSuspendPercentage1
    (int channel,
    int scaleno,
    float learn_suspend_percentage1);
    
bool iQSmSetFillSuspendPercentage
    (int channel,
    int scaleno,
    float fill_suspend_percentage);
    
bool iQSmSetFastSlowZeroPercentage
    (int channel,
    int scaleno,
    float fast_slow_zero_percentage);

bool iQSmSetDeadTime
    (int channel,
    int scaleno,
    float dead_time);

bool iQSmGetDeadTime
    (int channel,
    int scaleno,
    float *dead_time);

/****************************************************************************/
// set nethires resolution factor
/****************************************************************************/
bool SetHiResolutionFactor 
    (int channel,
     int scaleno,
     int high_resolution_factor);

#endif // #ifdef IQ_FEEDING_WITH_PROTOTYPES

/****************************************************************************/
// include the sources
/****************************************************************************/
#ifdef IQ_FEEDING_DEBUG
  #include "iQFeeding.ccf"
#else
  #binary "iQFeeding.obj"
#endif

#endif

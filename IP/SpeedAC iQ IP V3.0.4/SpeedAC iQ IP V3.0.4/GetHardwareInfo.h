
/* ****************************************************************** */
/* ****************************************************************** */
/* *                                                                * */
/* *                Get Harware Info                                * */
/* *                                                                * */
/* *  Routines for checking hardware configuration                  * */
/* *                                                                * */
/* *                                                                * */
/* *                 Copyright by SysTec GmbH                       * */
/* *                                                                * */
/* ****************************************************************** */
/* ****************************************************************** */


//#include "GetHardwareInfo.ccf"
#binary "GetHardwareInfo.obj"
/*
  General notes and warnings:
  ====================================================================================
  The following pre-processor definitions contains the actual version number:
  GET_HARDWARE_INFO_VERSION

  Public get harware info variables
  ====================================================================================
  bool HasSPU;
  bool HasPIO;
  bool HasNWU;
  bool HasProfibus;
  bool HasProfinet;
  bool HasEthernetIP;


  Available functions:
  ====================================================================================
  int GetHardwareInfo (bool *HasSPU, bool *HasPIO, bool *HasNWU, bool *HasProfibus, bool *HasProfinet, bool *HasEthernetIP)  

  parameters: HasSPU          
              HasPIO
              HasNWU
              HasProfibus
              HasProfinet
              HasEthernetIP      
              
  returns:    number of hardware type 
  ------------------------------------------------------------------------------------
  
  bool SetFieldbusProtocol (void)  
  parameters: ---
              
  returns:    false = no card detected
  ------------------------------------------------------------------------------------
  
  void RebootTerminal (void)
  parameters: ---
              
  returns:    --- 
  ------------------------------------------------------------------------------------
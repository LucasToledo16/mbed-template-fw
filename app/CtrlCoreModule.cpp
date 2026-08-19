/*
 * Copyright (C) 2023 CNPEM (cnpem.br)
 * Author: Guilherme Ricioli <guilherme.ricioli@lnls.br>
 */

#include "CtrlCoreModule.hpp"
#include <cstdlib>
#include "mbed.h"

#define SET_COMMAND_ID "@SET"
#define INC_COMMAND_ID "@INC"
#define DEC_COMMAND_ID "@DEC"
#define ZER_COMMAND_ID "@ZER"

DigitalOut led_inc(LED1);
DigitalOut led_dec(LED2);
DigitalOut led_zer(LED3);
DigitalOut led_set(LED4);

CtrlCoreModule::CtrlCoreModule(
    mbed::Callback<bool(Kernel::Clock::duration_u32, CtrlIntfModuleMessage**)>
    try_get_for_cb,
    /* Module params */
    osPriority priority, uint32_t stack_size, unsigned char *stack_mem,
    const char *name) :
  Module(priority, stack_size, stack_mem, name), _try_get_for_cb(try_get_for_cb) {
    _count = 0;
  }

CtrlCoreModule::~CtrlCoreModule() {}

void CtrlCoreModule::_task() {
  while(true) {
    bool status;
    CtrlIntfModuleMessage *p_ctrl_intf_mod_msg;
    char *set_value = nullptr;
    char *saveptr = nullptr;
    char *endptr = nullptr;

    /* Reads messages */
    status = _try_get_for_cb(rtos::Kernel::wait_for_u32_forever,
        &p_ctrl_intf_mod_msg);
    assert(status);

    /* Process command */
    if (strstr(p_ctrl_intf_mod_msg->buff, INC_COMMAND_ID) != nullptr){
      led_inc = 1;
      ThisThread::sleep_for(500ms);
      ++_count;
      led_inc = 0;
    } else if (strstr(p_ctrl_intf_mod_msg->buff, DEC_COMMAND_ID) != nullptr){
          led_dec = 1;
          ThisThread::sleep_for(500ms);
          if(_count > 0){
            --_count;
          }
          led_dec = 0;
    } else if (strstr(p_ctrl_intf_mod_msg->buff, ZER_COMMAND_ID) != nullptr){
          led_zer = 1;
          ThisThread::sleep_for(500ms);
          _count = 0;
          led_zer = 0;


    } else if (strstr(p_ctrl_intf_mod_msg->buff, SET_COMMAND_ID) != nullptr){
          set_value = strtok_r(p_ctrl_intf_mod_msg->buff, " \n", &saveptr);
          set_value = strtok_r(NULL, " \n", &saveptr);
          int value = strtol(set_value,&endptr,10);
          led_set = 1;
          ThisThread::sleep_for(500ms);
          if(set_value != endptr && *endptr == '\0' && value >= 0){
            _count =  value;
          }
          led_set = 0;
    }

    /* Writes message response */
    memset(p_ctrl_intf_mod_msg->buff, 0, sizeof(p_ctrl_intf_mod_msg->buff));
    snprintf(p_ctrl_intf_mod_msg->buff, sizeof(p_ctrl_intf_mod_msg->buff),
        "%lu", _count);

    /* Signalizes that response is ready */
    p_ctrl_intf_mod_msg->p_ready->release();
  }
}
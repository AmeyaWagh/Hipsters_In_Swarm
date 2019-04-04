#ifndef BUZZ_UTILS_H
#define BUZZ_UTILS_H

#include <buzz/argos/buzz_controller.h>

buzzvm_state FetchInt(buzzvm_t &t_vm, const std::string& str_sym, SInt32& n_value);
buzzvm_state FetchFloat(buzzvm_t &t_vm, const std::string& str_sym, Real& f_value);
void RegisterInt(buzzvm_t &t_vm, const std::string& str_sym, SInt32 n_value);
void RegisterFloat(buzzvm_t &t_vm, const std::string& str_sym, Real f_value);
void RegisterFunction(buzzvm_t &t_vm, const std::string& str_sym, const std::string& str_fun);

#endif
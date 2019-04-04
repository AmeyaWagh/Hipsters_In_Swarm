#include "buzz_utils.h"

buzzvm_state FetchInt(buzzvm_t t_vm,
                      const std::string& str_sym,
                      SInt32& n_value) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 0));
   buzzvm_gload(t_vm);
   buzzvm_type_assert(t_vm, 1, BUZZTYPE_INT);
   n_value = buzzvm_stack_at(t_vm, 1)->i.value;
   return BUZZVM_STATE_READY;
}

buzzvm_state FetchFloat(buzzvm_t t_vm,
                        const std::string& str_sym,
                        Real& f_value) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 0));
   buzzvm_gload(t_vm);
   buzzvm_type_assert(t_vm, 1, BUZZTYPE_FLOAT);
   f_value = buzzvm_stack_at(t_vm, 1)->f.value;
   return BUZZVM_STATE_READY;
}

void RegisterInt(buzzvm_t t_vm,
                        const std::string& str_sym,
                        SInt32 n_value) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 1));
   buzzvm_pushi(t_vm, n_value);
   buzzvm_gstore(t_vm);
}

void RegisterFloat(buzzvm_t t_vm,
                          const std::string& str_sym,
                          Real f_value) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 1));
   buzzvm_pushf(t_vm, f_value);
   buzzvm_gstore(t_vm);
}

void RegisterFunction(buzzvm_t t_vm,
                             const std::string& str_sym,
                             const std::string& str_fun) {
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_sym.c_str(), 1));
   buzzvm_pushs(t_vm, buzzvm_string_register(t_vm, str_fun.c_str(), 0));
   buzzvm_gload(t_vm);
   if(buzzvm_stack_at(t_vm, 1)->o.type != BUZZTYPE_CLOSURE) {
      THROW_ARGOSEXCEPTION("Buzz script does not contain function '" << str_fun << "'");
   }
   buzzvm_gstore(t_vm);
}
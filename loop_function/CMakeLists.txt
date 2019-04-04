set(custom_loop_function_SOURCE custom_loop_function.cpp buzz_utils.cpp buzz_utils.h)

add_library(custom_loop_function MODULE ${custom_loop_function_SOURCE})
target_link_libraries(custom_loop_function
  ${BUZZ_LIBRARY}
  argos3core_simulator
  argos3plugin_simulator_entities
  argos3plugin_simulator_kheperaiv
  argos3plugin_simulator_buzz
  argos3plugin_simulator_dynamics2d
  argos3plugin_simulator_genericrobot
  argos3plugin_simulator_media)

set(custom_loop_function_SOURCE custom_loop_function.cpp buzz_utils.cpp)

#if(ARGOS_COMPILE_QTOPENGL)
#  set(foraging_loop_functions_SOURCES
#    ${foraging_loop_functions_SOURCES}
#    foraging_qt_user_functions.cpp)
#endif(ARGOS_COMPILE_QTOPENGL)

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

#if(ARGOS_COMPILE_QTOPENGL)
#  target_link_libraries(foraging_loop_functions argos3plugin_simulator_qtopengl)
#endif(ARGOS_COMPILE_QTOPENGL)
set(BUZZ_BZZ_INCLUDE_DIR "${BUZZ_BZZ_INCLUDE_DIR}:${CMAKE_CURRENT_SOURCE_DIR}")

buzz_make(hipsters_in_network.bzz INCLUDES obstacle_avoidance_controller.bzz  opinion_propagation.bzz  utils.bzz)
set(BUZZ_BZZ_INCLUDE_DIR "${BUZZ_BZZ_INCLUDE_DIR}:${CMAKE_CURRENT_SOURCE_DIR}")

buzz_make(hipsters_in_network.bzz INCLUDES lib/obstacle_avoidance_controller.bzz  lib/opinion_propagation.bzz  lib/utils.bzz)
get_filename_component(SUBMODULE_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
file(GLOB_RECURSE SUBMODULE_SOURCE_FILES "*.cpp")
add_library(${SUBMODULE_NAME} ${SUBMODULE_SOURCE_FILES})
target_include_directories(${SUBMODULE_NAME} PUBLIC "include")
target_link_libraries(${SUBMODULE_NAME} PUBLIC
    bksram
    sml
)
target_link_libraries(${SUBMODULE_NAME} PRIVATE
    stm32cubef2
    trielo
    actu::fan_broiler
    actu::fan_ctl
    actu::peltier
    actu::pump
    actu::buzzer
    panel::sevseg_white
)
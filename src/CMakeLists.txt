

ADD_LIBRARY(DRACO_GPIO_MOD DRACO_GPIO_mod)
ADD_LIBRARY(NRF24L01 nRF24L01)
ADD_LIBRARY(MIRF mirf)
ADD_LIBRARY(AISOYAPI AISoyAPI)
ADD_LIBRARY(AISOYGLOBAL AISoyGlobal)
SET_TARGET_PROPERTIES(MIRF PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(AISOYAPI  PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(AISOYGLOBAL  PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(NRF24L01  PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(DRACO_GPIO_MOD  PROPERTIES LINKER_LANGUAGE C)
add_executable(main main.cpp)
target_link_libraries(main aisoy1)
target_link_libraries(main MIRF)
target_link_libraries(main AISOYAPI)
target_link_libraries(main NRF24L01)
target_link_libraries(main DRACO_GPIO_MOD)
target_link_libraries(main pthread)


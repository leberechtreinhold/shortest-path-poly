install(
    TARGETS shortest-path-poly_exe
    RUNTIME COMPONENT shortest-path-poly_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()

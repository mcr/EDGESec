if (USE_ZYMKEY4_HSM)
  add_compile_definitions(WITH_ZYMKEY4_HSM)
  find_library(LIBZYMKEY4_LIB NAMES zk_app_utils libzk_app_utils)
  if (LIBZYMKEY4_LIB)
    message("Found libzk_app_utils library: ${LIBZYMKEY4_LIB}")
  else ()
    message(FATAL_ERROR "Could not find libzk_app_utils library.")
  endif ()
endif ()
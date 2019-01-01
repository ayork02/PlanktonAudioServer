if (PLANKAUDIO_LIBRARIES AND PLANKAUDIO_INCLUDE_DIRS)
  # in cache already
  set(PLANKAUDIO_FOUND TRUE)
else (PLANKAUDIO_LIBRARIES AND PLANKAUDIO_INCLUDE_DIRS)

  if (PLANKAUDIO_FOUND)
    set(PLANKAUDIO_INCLUDE_DIRS
      ${PLANKAUDIO_INCLUDE_DIRS}
    )
  else (PLANKAUDIO_FOUND)
    find_path(PLANKAUDIO_INCLUDE_DIR
      NAMES
        plankaudio.h
      PATHS
        /usr/include
        /usr/local/include
        /opt/local/include
        /sw/include
    )
   
    find_library(PLANKAUDIO_LIBRARY
      NAMES
        plankaudio
      PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
        /sw/lib
        ${PLANKAUDIO_LIBRARY_DIR}
    )
   
    set(PLANKAUDIO_INCLUDE_DIRS
      ${PLANKAUDIO_INCLUDE_DIR}
    )
    set(PLANKAUDIO_LIBRARIES
      ${PLANKAUDIO_LIBRARY}
    )
   
    set(PLANKAUDIO_LIBRARY_DIRS
      ${PLANKAUDIO_LIBRARY_DIR}
    )
   
    if (PLANKAUDIO_INCLUDE_DIRS AND PLANKAUDIO_LIBRARIES)
       set(PLANKAUDIO_FOUND TRUE)
    endif (PLANKAUDIO_INCLUDE_DIRS AND PLANKAUDIO_LIBRARIES)
   
    if (PLANKAUDIO_FOUND)
      if (NOT plankaudio_FIND_QUIETLY)
        message(STATUS "Found plankaudio: ${PLANKAUDIO_LIBRARIES}")
      endif (NOT plankaudio_FIND_QUIETLY)
    else (PLANKAUDIO_FOUND)
      if (plankaudio_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find plankaudio")
      endif (plankaudio_FIND_REQUIRED)
    endif (PLANKAUDIO_FOUND)
  endif (PLANKAUDIO_FOUND)

  # show the PLANKAUDIO_INCLUDE_DIRS and PLANKAUDIO_LIBRARIES variables only in the advanced view
  mark_as_advanced(PLANKAUDIO_INCLUDE_DIRS PLANKAUDIO_LIBRARIES)

endif (PLANKAUDIO_LIBRARIES AND PLANKAUDIO_INCLUDE_DIRS)

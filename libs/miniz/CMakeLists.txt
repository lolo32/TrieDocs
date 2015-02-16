SET( ENV{miniz_ROOT} ${PROJECT_SOURCE_DIR}/3party/miniz-r63 } )
SET( ENV{miniz_ROOT_libs} ${CMAKE_CURRENT_SOURCE_DIR} )

SET(miniz_SOURCES
    $ENV{miniz_ROOT}/miniz.c
    $ENV{miniz_ROOT_libs}/zlib.h
)

INCLUDE_DIRECTORIES( $ENV{miniz_ROOT} )
ADD_LIBRARY( miniz STATIC ${miniz_SOURCES} )

SET_TARGET_PROPERTIES(miniz
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

ADD_EXECUTABLE( check_miniz EXCLUDE_FROM_ALL
    $ENV{miniz_ROOT}/miniz_tester.cpp
    $ENV{miniz_ROOT}/timer.cpp
    $ENV{miniz_ROOT}/timer.h
)
TARGET_LINK_LIBRARIES( check_miniz miniz )
SET_TARGET_PROPERTIES( check_miniz
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)


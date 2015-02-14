SET( ENV{miniz_root} ${PROJECT_SOURCE_DIR}/3party/miniz-r63 } )

SET(miniz_SOURCES
    $ENV{miniz_root}/miniz.c
)

INCLUDE_DIRECTORIES( $ENV{miniz_root} )
ADD_LIBRARY( miniz STATIC ${miniz_SOURCES} )

ADD_EXECUTABLE( check_miniz EXCLUDE_FROM_ALL
    $ENV{miniz_root}/miniz_tester.cpp
    $ENV{miniz_root}/timer.cpp
    $ENV{miniz_root}/timer.h
)
TARGET_LINK_LIBRARIES( check_miniz miniz )

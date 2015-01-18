SET(myminiz_SOURCES libmyminiz.h libmyminiz.c)

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3party/miniz-r63 )

ADD_LIBRARY( myminiz STATIC ${myminiz_SOURCES} )

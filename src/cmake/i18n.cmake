# Liste des langues à générer
# Une langue par ligne
SET(GEN_TRADUCTIONS
    en
)

FIND_PACKAGE(Qt5LinguistTools REQUIRED)

# Fonction réécrite pour appeler la version modifiée de la compression des .qm
function(myQT5_CREATE_TRANSLATION _qm_files)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs OPTIONS)

    cmake_parse_arguments(_LUPDATE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(_lupdate_files ${_LUPDATE_UNPARSED_ARGUMENTS})
    set(_lupdate_options ${_LUPDATE_OPTIONS})

    set(_my_sources)
    set(_my_tsfiles)
    foreach(_file ${_lupdate_files})
        get_filename_component(_ext ${_file} EXT)
        get_filename_component(_abs_FILE ${_file} ABSOLUTE)
        if(_ext MATCHES "ts")
            list(APPEND _my_tsfiles ${_abs_FILE})
        else()
            list(APPEND _my_sources ${_abs_FILE})
        endif()
    endforeach()
    foreach(_ts_file ${_my_tsfiles})
        if(_my_sources)
          get_filename_component( _ts_lang ${_ts_file} NAME_WE )
          # make a list file to call lupdate on, so we don't make our commands too
          # long for some systems
          get_filename_component(_ts_name ${_ts_file} NAME_WE)
          set(_ts_lst_file "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${_ts_name}_lst_file")
          set(_lst_file_srcs)
          foreach(_lst_file_src ${_my_sources})
              set(_lst_file_srcs "${_lst_file_src}\n${_lst_file_srcs}")
          endforeach()

          get_directory_property(_inc_DIRS INCLUDE_DIRECTORIES)
          foreach(_pro_include ${_inc_DIRS})
              get_filename_component(_abs_include "${_pro_include}" ABSOLUTE)
              set(_lst_file_srcs "-I${_pro_include}\n${_lst_file_srcs}")
          endforeach()

          file(WRITE ${_ts_lst_file} "${_lst_file_srcs}")
        endif()
        add_custom_command(OUTPUT ${_ts_file}
            COMMAND ${Qt5_LUPDATE_EXECUTABLE}
            ARGS ${_lupdate_options} -target-language ${_ts_lang} "@${_ts_lst_file}" -ts ${_ts_file}
            DEPENDS ${_my_sources} ${_ts_lst_file} VERBATIM)
    endforeach()
    myqt5_add_translation(${_qm_files} ${_my_tsfiles})
    set(${_qm_files} ${${_qm_files}} PARENT_SCOPE)
endfunction()

# Fonction réécrite pour compresser les fichier,
# et pour compiler les .qm dans les sources
function(myQT5_ADD_TRANSLATION _qm_files)
    foreach(_current_FILE ${ARGN})
        get_filename_component(_abs_FILE ${_current_FILE} ABSOLUTE)
        get_filename_component(_abs_DIR ${_abs_FILE} DIRECTORY)
        get_filename_component(qm ${_abs_FILE} NAME_WE)
        set(qm "${_abs_DIR}/${qm}.qm")

        add_custom_command(OUTPUT ${qm}
            PRE_BUILD
            COMMAND ${Qt5_LRELEASE_EXECUTABLE}
            ARGS  -markuntranslated ! -removeidentical ${_abs_FILE} -qm ${qm}
            DEPENDS ${_abs_FILE} VERBATIM
        )
        list(APPEND ${_qm_files} ${qm})
    endforeach()
    set(${_qm_files} ${${_qm_files}} PARENT_SCOPE)
endfunction()

set(TRANSLATIONS_FILES)
foreach( _trad ${GEN_TRADUCTIONS} )
    list( APPEND TRANSLATIONS_FILES "i18n/${_trad}.ts" )
endforeach()

OPTION (UPDATE_TRANSLATIONS "Update source translation i18n/*.ts")
IF (UPDATE_TRANSLATIONS)
  FILE(GLOB TrieDocs_SOURCES   *.cpp )
  FILE(GLOB TrieDocs_HEADERS   *.h   )
  FILE(GLOB TrieDocs_FENETRES  *.ui  )
  myQT5_CREATE_TRANSLATION(QM_FILES ${TrieDocs_SOURCES} ${TrieDocs_HEADERS} ${TrieDocs_FENETRES} ${TRANSLATIONS_FILES} OPTIONS -source-language fr )
  # prevent the generated files from being deleted during make clean
  set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM true)
ELSE (UPDATE_TRANSLATIONS)
  myQT5_ADD_TRANSLATION(QM_FILES ${TRANSLATIONS_FILES})
ENDIF (UPDATE_TRANSLATIONS)

ADD_CUSTOM_TARGET (i18n_target DEPENDS ${QM_FILES} ${TRANSLATIONS_FILES} VERBATIM SOURCES ${TRANSLATIONS_FILES})

SET_PROPERTY(TARGET i18n_target
   APPEND PROPERTY AUTOGEN_TARGET_DEPENDS TrieDocs_automoc
 )

SET_SOURCE_FILES_PROPERTIES( qrc_resources.cpp PROPERTIES OBJECT_DEPENDS "${QM_FILES}" )

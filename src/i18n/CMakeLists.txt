FIND_PACKAGE(Qt5LinguistTools REQUIRED)

function(myQT5_ADD_TRANSLATION _qm_files)
    foreach(_current_FILE ${ARGN})
        get_filename_component(_abs_FILE ${_current_FILE} ABSOLUTE)
        get_filename_component(_abs_DIR ${_abs_FILE} DIRECTORY)
        get_filename_component(qm ${_abs_FILE} NAME_WE)
        set(qm "${_abs_DIR}/${qm}.qm")

        add_custom_command(OUTPUT ${qm}
            PRE_BUILD
            COMMAND ${Qt5_LRELEASE_EXECUTABLE}
            ARGS ${_abs_FILE} -qm ${qm} -compress -removeidentical
            DEPENDS ${_abs_FILE} VERBATIM
        )
        list(APPEND ${_qm_files} ${qm})
    endforeach()
    set(${_qm_files} ${${_qm_files}} PARENT_SCOPE)
endfunction()

FILE (GLOB TRANSLATIONS_FILES *.ts)

OPTION (UPDATE_TRANSLATIONS "Update source translation i18n/*.ts")
IF (UPDATE_TRANSLATIONS)
  QT5_CREATE_TRANSLATION(QM_FILES ${FILES_TO_TRANSLATE} ${TRANSLATIONS_FILES})
ELSE (UPDATE_TRANSLATIONS)
  myQT5_ADD_TRANSLATION(QM_FILES ${TRANSLATIONS_FILES})
ENDIF (UPDATE_TRANSLATIONS)

ADD_CUSTOM_TARGET (i18n_target ALL DEPENDS ${QM_FILES} VERBATIM SOURCES ${TRANSLATIONS_FILES})

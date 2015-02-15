# Liste des langues à générer
# Une langue par ligne
SET(GEN_TRADUCTIONS
    en      # Anglais
)

FIND_PACKAGE(Qt5LinguistTools REQUIRED)

# Fonction réécrite pour appeler la version modifiée de la compression des .qm
# et spécifier la langue source lors de la création des fichiers de traduction
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

LIST( SORT GEN_TRADUCTIONS )
# Génère la liste des fichiers traductions à traiter
set(TRANSLATIONS_FILES)
foreach( _trad ${GEN_TRADUCTIONS} )
    list( APPEND TRANSLATIONS_FILES "i18n/${_trad}.ts" )
endforeach()

#######################
# Modifie le fichier de ressources pour intégrer TOUTES les langues définies au début du fichier

# Lit le fichier de ressources
FILE( READ resources.qrc RESSOURCES_XML )
SET( RESSOURCES_ORIGINE ${RESSOURCES_XML} )
# Supprime la liste des traductions
# Les lignes sont du style `<file alias="triedocs_en.qm">i18n/en.qm</file>`
STRING( REGEX REPLACE "        <file alias=\"triedocs_[a-zA-Z_]+\\.qm\">i18n/[a-zA-Z_]+\\.qm</file>\n" "" RESSOURCES_XML ${RESSOURCES_XML} )
# Génère les lignes à rajouter pour les traductions
SET(_lang_ajouter)
FOREACH(_lang ${GEN_TRADUCTIONS})
    SET( _lang_ajouter "${_lang_ajouter}        <file alias=\"triedocs_${_lang}.qm\">i18n/${_lang}.qm</file>\n" )
ENDFOREACH()
# On les ajoute
STRING( REGEX REPLACE "<qresource prefix=\"/i18n\">\n" "<qresource prefix=\"/i18n\">\n${_lang_ajouter}" RESSOURCES_XML ${RESSOURCES_XML} )
# On écrit le nouveau fichier de ressource si il y a modification
IF( NOT ${RESSOURCES_XML} STREQUAL ${RESSOURCES_ORIGINE} )
    FILE( WRITE resources.qrc "${RESSOURCES_XML}" )
ENDIF()

#######################
# Commandes pour lancer la régénération/compilation des traductions

OPTION (UPDATE_TRANSLATIONS "Update source translation i18n/*.ts")
IF (UPDATE_TRANSLATIONS)
    myQT5_CREATE_TRANSLATION(QM_FILES ${TrieDocs_SOURCES} ${TrieDocs_HEADERS} ${TrieDocs_FENETRES} ${TRANSLATIONS_FILES} OPTIONS -source-language fr )
    # prevent the generated files from being deleted during make clean
    set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM true)
ELSE (UPDATE_TRANSLATIONS)
    myQT5_ADD_TRANSLATION(QM_FILES ${TRANSLATIONS_FILES})
ENDIF (UPDATE_TRANSLATIONS)

# Cible pour compiler les traductions
ADD_CUSTOM_TARGET (i18n_target DEPENDS ${QM_FILES} ${TRANSLATIONS_FILES} VERBATIM SOURCES ${TRANSLATIONS_FILES})

# Ajout d’une règle pour recompiler les ressources si une traduction a été mise à jour
SET_PROPERTY(TARGET i18n_target
    APPEND PROPERTY AUTOGEN_TARGET_DEPENDS TrieDocs_automoc
)

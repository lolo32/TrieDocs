#ifndef COMMUN_H
#define COMMUN_H

// Désactive l’autocast QString depuis/vers char*
// Permet de vérifier que les convertion Latin/Utf8 sont bien respecté,
// car elles doivent être explicites
#define QT_NO_CAST_FROM_ASCII 1
#define QT_NO_CAST_TO_ASCII   1

// On n’inclut que l’en-tête de miniz, le reste étant compilé en bibliothèque
#define MINIZ_HEADER_FILE_ONLY 1

// Numéro de la révision Git
extern const char g_GIT_SHA1[];

// Numéro de version du programme
extern const char g_TRIEDOCS_VERSION_STR[];

#endif // COMMUN_H

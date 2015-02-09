# Comment ajouter une traduction

## Créer le fichier de la nouvelle traduction

Il faut éditer le fichier `src/cmake/i18n.cmake`, et rajouter la ou les
langue(s) à la liste `SET(GEN_TRADUCTIONS` se trouvant au début du fichier.

Par exemple, si la langue à créer est l’anglais, il faut ajouter une ligne
ayant pour nom `en`, car le code ISO 639-1 de l’anglais est `en`. Un autre
exemple avec le brésilien qui a pour code `pt_BR`.

Vous pouvez vous repporter à la page sur [Lingoes](http://www.lingoes.net/en/translator/langcode.htm)
donnant un tableau des différents codes.

## Activer la régénération des traductions sous CMake

Il faut activer l’extraction des textes sources dans CMake.

    cmake -DUPDATE_TRANSLATIONS=1

Ensuite, on lance la compilation des traductions

    make i18n_target

## Traduction du nouveau fichier de traduction

Ouvrez la nouvelle traduction se trouvant dans le répertoire `src/i18n`, avec
le programme QLinguist par exemple, ou un simple éditeur de texte.

La balise `<extracomment>` contient la traduction du texte en anglais, et
`<extra-Context>` des informations additionnelles sur le contexte d’utilisation
du texte.

### Remarque

*Attention, n’oubliez pas de traduire la chaîne indiquant le nom de la langue
dans la langue native*

    <source>Français</source>
    <extracomment>This is the language name of the file</extracomment>
    <translation></translation>

`<translation></translation>` doit en effet contenir le nom de la langue, par
exemple :

| Code de la langue |   Nom de la langue  | Description              |
| :---------------: | :-----------------: | ------------------------ |
| `fr_CA`           | `Français (Canada)` | pour le français d’origine canadienne |
| `es`              | `Español`           | pour l’espagnol général  |
| `pt_BR`           | `Brasileño`         | pour le brésilien = portugais parlé au brésil |

## Tester

Il est possible de tester la nouvelle traduction, ou modifiée, en plaçant
simplement le fichier `triedocs_<code_langue>.qm` dans le répertoire courant,
l’application va le charger en plus de la version déjà incluse dans les
ressources, et c’est la version externe (non incluse) qui a le privilège.

Il est maintenant possible de tester des nouvelles traductions sans avoir à
recompiler toute l’application, il suffit juste de publier la traduction à
partir de Qt Lignuist par exemple.

## Ajouter la traduction dans les ressources

Il ne reste plus qu’à tester la nouvelle traduction en lançant une nouvelle
compilation de TrieDocs.

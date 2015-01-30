# Comment ajouter une traduction

## Créer le fichier de la nouvelle traduction

Il faut créer le fichier qui va contenir la nouvelle traduction, en créant un
fichier vide dont le nom est le code de la langue terminé par l’extension `.ts`
dans le répertoire `src/i18n`.

Par exemple, si la langue à créer est l’anglais, il faut créer un fichier
ayant pour nom `en.ts`, car le code ISO 639-1 de l’anglais est `en`. Un autre
exemple avec l’allemand qui a pour code `de`.

Vous pouvez vous repporter à la page sur [Wikipedia](http://fr.wikipedia.org/wiki/Liste_des_codes_ISO_639-1)
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

## Ajouter la traduction au programme

Il faut éditer le fichier des ressources `src/resources.qrc` en rajoutant la
référence au nouveau fichier de traduction.

Par exemple, dans le morceau ci-dessous, il n’y a que l’anglais.

    <qresource prefix="/i18n">
        <file alias="en.qm">i18n/en.qm</file>
    </qresource>

On rajoute l’espagnol :

    <qresource prefix="/i18n">
        <file alias="en.qm">i18n/en.qm</file>
        <file alias="es.qm">i18n/es.qm</file>
    </qresource>

## Tester

Il ne reste plus qu’à tester la nouvelle traduction en lançant une nouvelle
compilation de TrieDocs.

### En cas d’erreur de traduction pour retester

Comme les traductions sont incluses en tant que ressources dans l’application,
il faut s’assurer que la traduction, une fois modifiée, est de nouveau incluse.

Il suffit de supprimer le fichier généré `src/qrc_resources.cpp` se trouvant
dans l’arborescence de compilation.

/*
 * Table des données des documents
 */

/** Données générale d'un document */
CREATE TABLE IF NOT EXISTS documents (
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    titre TEXT NOT NULL,
    fichier TEXT NOT NULL
) WITHOUT ROWID;

/** Données dans les pages */
CREATE TABLE IF NOT EXISTS privdoc_pages (
    doc_id INTEGER REFERENCES documents(id) ON DELETE CASCADE ON UPDATE CASCADE,
    page INTEGER,
    UNIQUE(doc_id, page)
);

CREATE VIRTUAL TABLE IF NOT EXISTS privdoc_contenu USING fts4(
    tokenize=porter, compress=zip, uncompress=unzip
);

  /* required when ref. integrity deletes rows in FilePages as
     a result of delete row(s) operation in Document */
CREATE TRIGGER IF NOT EXISTS privdoc_pages_DELETE AFTER DELETE ON privdoc_pages FOR EACH ROW
BEGIN
    DELETE FROM privdoc_contenu WHERE rowid = OLD.rowid;
END;

CREATE VIEW IF NOT EXISTS contenu AS
    SELECT
        privdoc_pages.rowid AS rowid,
        privdoc_pages.doc_id,
        privdoc_pages.page,
        privdoc_contenu.content
    FROM privdoc_pages JOIN privdoc_contenu ON privdoc_pages.rowid = privdoc_contenu.rowid;

CREATE TRIGGER IF NOT EXISTS contenu_INSERT INSTEAD OF INSERT ON contenu
BEGIN
    INSERT INTO privdoc_pages(doc_id, page) VALUES (NEW.doc_id, NEW.page);
    INSERT INTO privdoc_contenu(rowid, content) VALUES (last_insert_rowid(), NEW.content);
END;

CREATE TRIGGER IF NOT EXISTS contenu_DELETE INSTEAD OF DELETE ON contenu
BEGIN
    DELETE FROM privdoc_pages WHERE rowid = OLD.rowid;
    DELETE FROM privdoc_contenu WHERE rowid = OLD.rowid;
END;

/*
 * Liste des étiquettes
 */
CREATE TABLE IF NOT EXISTS tags(
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL UNIQUE
);

CREATE TABLE IF NOT EXISTS docs_tags(
    tag_id INTEGER NOT NULL REFERENCES tags(id) ON DELETE CASCADE,
    doc_id INTEGER NOT NULL REFERENCES documents(id) ON DELETE CASCADE,
    PRIMARY KEY (tag_id, doc_id)
) WITHOUT ROWID;
CREATE INDEX IF NOT EXISTS idx_docs_tags_doc_id ON docs_tags(doc_id);

/*
 * Table des paramètres de configuration
 */
CREATE TABLE IF NOT EXISTS conf(
    parametre TEXT NOT NULL PRIMARY KEY,
    valeur TEXT NOT NULL
) WITHOUT ROWID;
/** Version de la base de données */
INSERT INTO conf(parametre, valeur) VALUES ('version', 1);

/*
 * Tables pour la gestion des utilisateurs
 */
CREATE TABLE IF NOT EXISTS groupes(
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL UNIQUE,
    expire TIMESTAMP NOT NULL
);
CREATE TABLE IF NOT EXISTS utilisateurs(
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL UNIQUE,
    mdp TEXT NOT NULL,
    expire TIMESTAMP NOT NULL
);
CREATE TABLE IF NOT EXISTS utilisateur_groupe(
    utilisateur_id INTEGER REFERENCES utilisateurs(id) ON DELETE CASCADE,
    groupe_id INTEGER REFERENCES groupes(id) ON DELETE CASCADE
) WITHOUT ROWID;

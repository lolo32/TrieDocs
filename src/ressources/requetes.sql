CREATE VIRTUAL TABLE documents USING fts4 (
    titre TEXT,
    page INTEGER,
    texte TEXT,
    tokenize=porter, compress=zip, uncompress=unzip, no tindexed=page
);

CREATE TABLE tags(
    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL
);
CREATE INDEX idx_tags_nom ON tags(nom);

CREATE TABLE docs_tags(
    tag_id INTEGER NOT NULL REFERENCES tags(id) ON DELETE CASCADE,
    doc_id INTEGER NOT NULL REFERENCES docs(docid) ON DELETE CASCADE,
    PRIMARY KEY (tag_id, doc_id)
);
CREATE INDEX idx_docs_tags_doc_id ON docs_tags(doc_id);

CREATE TABLE conf(
    parametre TEXT NOT NULL PRIMARY KEY,
    valeur TEXT NOT NULL
);

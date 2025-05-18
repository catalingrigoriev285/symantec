CREATE TABLE IF NOT EXISTS "signatures" (
	"id"	INTEGER UNIQUE,
	"name"	TEXT,
	"description"	TEXT,
	"value"	TEXT,
	"algorithm"	TEXT,
	"hash"	TEXT,
	"created_at"	TEXT,
	"updated_at"	TEXT,
	PRIMARY KEY("id" AUTOINCREMENT)
);
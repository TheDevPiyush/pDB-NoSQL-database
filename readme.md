# pDB — A `NoSQL Database` in C

pDB is a lightweight **NoSQL document database** written entirely in **C**, built to explore low-level systems programming, storage engines, and database internals.

The project implements a custom database engine with collections, documents, persistence, and a command-line query interface — inspired by databases like MongoDB and SQLite.

---

## ✨ Current Features

- 📦 **Document-based storage** (schema-less data model)
- 🗂 **Multiple collections**
- 🆔 Auto-generated document IDs
- 💾 Binary disk persistence (`.pdb` database file)
- 🔎 Query support:
  - `select` (all documents)
  - `select <id>` (single document)
  - `Update <id>` documents by ID
  - `Delete <id>` documents by ID
- 🖥 Interactive database shell

---

## 🧱 Architecture

The project follows a layered database design:

```text
main (REPL shell)
       ↓
parser (command detection)
       ↓
executor (command execution)
       ↓
database / collection layer
       ↓
storage engine (binary persistence)
```

## Core Components

| Module | Responsibility |
|---|---|
| `main.c` | Interactive CLI loop |
| `parser.c` | Command parsing |
| `executor.c` | Command execution |
| `collection.c` | Document operations |
| `storage.c` | Disk serialization |
| `document.h` | Data structures |

## 📄 Data Model

Documents are stored as key–value pairs:

```json
{
  "_id": 1,
  "name": "Piyush",
  "age": "21"
}
```

## Build
```./build.sh```

## Run
```./db```

## Example Session

```
pdb >> create users
pdb >> use users

pdb_users >> insert name="Piyush" age=22
Document inserted

pdb_users >> select
{ "_id": 1, "name": "Piyush", "age": "22" }
{ "_id": 2, "name": "Rahul", "age": "20" }

pdb_users >> select 1
{ "_id": 1, "name": "Piyush", "age": "21" }
```
# Release notes

November 15, 2018

The SQLite3 shell applications are now compatible with the official
SQLite3 shell in respect to the compile time options
`SQLITE_ENABLE_DBSTAT_VTAB`, SQLITE_ENABLE_STMTVTAB`, and
`SQLITE_ENABLE_UNKNOWN_SQL_FUNCTION`.

This archive with precompiled Windows DLLs for SQLite3 contains
experimental versions with enabled ICU support, in addition to the
versions without ICU support.

The required ICU DLLs are not included in this archive; they have
to be downloaded from

https://www.npcglib.org/~stathis/blog/precompiled-icu

ICU support for SQLite3 is based on the pre-built ICU Libraries v59.1.
These are compiled for 32/64-bit Windows, using Visual Studio 2015.

When using the ICU DLLs you may need to specify an environment variable
ICU_DATA pointing to the data folder, where the icudtXXl.dat file lives
(e.g. set ICU_DATA=F:\icu\data).

## Archive content

Archive name: `wxsqlite3-sqlite3-multicipher.zip`

32 Bit   | 64 Bit       | Description
:------- | :----------- | :--------
*.a      | *_x64.a      | Import libraries for GCC
*.lib    | *_x64.lib    | Import libraries for MSVC
*.pdb    | *_x64.pdb    | Program Database files for MSVC
*.dll    | *_x64.dll    | Shared release DLLs
*.exe    | *_x64.exe    | SQLite3 shell tool
*icu.a   | *icu_x64.a   | Import libraries for GCC, with ICU support
*icu.lib | *icu_x64.lib | Import libraries for MSVC, with ICU support
*icu.dll | *icu_x64.dll | Shared release DLLs, with ICU support
*icu.exe | *icu_x64.exe | SQLite3 shell tool, with ICU support

## Support

If you have any comments or problems open an issue on the wxSQLite3 github page:
https://github.com/utelle/wxsqlite3/issues

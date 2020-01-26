# Release notes

January 26, 2020

The SQLite3 shell applications are now compatible with the official
SQLite3 shell in respect to the compile time options
`SQLITE_ENABLE_DBSTAT_VTAB`, `SQLITE_ENABLE_STMTVTAB`, and
`SQLITE_ENABLE_UNKNOWN_SQL_FUNCTION`.

Starting from October 2019 separate archives are provided with resp.
without enabled ICU support for 32-bit and 64-bit Windows.

ICU support for SQLite3 is currently based on the pre-built ICU
Libraries v65.1, which were compiled with Visual Studio 2017.
The required ICU DLLs are now included in the archives in folder `bin`.
They were downloaded from

https://github.com/unicode-org/icu/releases/latest

In addition, the Visual C++ 2017 runtime is required to be installed,
because the ICU DLLs depend on it.

## Archive content

Archive names:

1) `wxsqlite3-sqlite3-x.y.z-win32.zip` - 32-bit Windows without ICU support
2) `wxsqlite3-sqlite3-x.y.z-win64.zip` - 64-bit Windows without ICU support
3) `wxsqlite3-sqlite3-x.y.z-icu-win32.zip` - 32-bit Windows with ICU support
4) `wxsqlite3-sqlite3-x.y.z-icu-win64.zip` - 64-bit Windows with ICU support

where `x.y.z` designates the version of the SQLite3 library.

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

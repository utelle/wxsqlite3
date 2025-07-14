# wxSQLite3 - a lightweight wrapper for SQLite

**wxSQLite3** is a C++ wrapper around the public domain SQLite 3.x database
and is specifically designed for use in programs based on the wxWidgets
library.

**wxSQLite3** does not try to hide the underlying database, in contrary
almost all special features of the current SQLite3 version are
supported, like for example the creation of user defined scalar or
aggregate functions.

Since SQLite stores strings in UTF-8 encoding, the wxSQLite3 methods
provide automatic conversion between wxStrings and UTF-8 strings. This
works best for the Unicode builds of wxWidgets. In ANSI builds the
current locale conversion object (wxConvCurrent) is used for conversion
to/from UTF-8. Special care has to be taken if external administration
tools are used to modify the database contents, since not all of these
tools operate in Unicode or UTF-8 mode.

Since version 1.7.0 **wxSQLite3** includes a key-based SQLite3 encryption
extension using AES encryption. The decision whether to use 128 bit or
256 bit AES encryption had to be made at compile time. Starting with version
4.0.0 the encryption extension allows to select the cipher scheme at runtime.

Currently the following encryption schemes are supported:

- AES 128 Bit CBC - No HMAC ([wxSQLite3](https://github.com/utelle/wxsqlite3))
- AES 256 Bit CBC - No HMAC ([wxSQLite3](https://github.com/utelle/wxsqlite3))
- ChaCha20 - Poly1305 HMAC ([sqleet](https://github.com/resilar/sqleet)) (**default**)
- AES 256 Bit CBC - SHA1/SHA256/SHA512 HMAC ([SQLCipher](https://www.zetetic.net/sqlcipher/) versions 1 - 4) 
- RC4 - No HMAC ([System.Data.SQLite](https://system.data.sqlite.org/))
- Ascon 128 - Ascon Tag ([Ascon](https://ascon.iaik.tugraz.at/)) (since version 4.9.8)
- AEGIS - AEGIS Tag ([AEGIS](https://cfrg.github.io/draft-irtf-cfrg-aegis-aead/draft-irtf-cfrg-aegis-aead.html)) (since version 4.10.0)

## Important Notes

With the release of SQLite version 3.32.0 on May 22, 2020 critical changes to the public SQLite code finally took officially effect, although they weren't officially announced. They were introduced on Feb 7, 2020: ["Simplify the code by removing the unsupported and undocumented SQLITE_HAS_CODEC compile-time option"](https://www.sqlite.org/src/timeline?c=5a877221ce90e752). As a consequence, updating the _wxSQLite3 encryption extension_ to support SQLite version 3.32.0 and later was no longer possible.

Since August 2020 a new implementation of an encryption extension, capable of supporting SQLite version 3.32.0 and later, is available as a separate project, [SQLite3 Multiple Ciphers](https://github.com/utelle/SQLite3MultipleCiphers). Starting with the release of **wxSQLite3 4.6.0** this new implementation is used.

Currently the _CMake_ support is experimental and limited to Windows platforms (and may or may not work). 

## Table of Contents

- [Version history](#history)
- [Installation](#install)
- [Optional features](#optional)
- [Key based database encryption support](#encryption)
- [Static SQLite library](#sqlite-static)
- [License](#license)
- [Acknowledgements](#acknowledge)

## <a name="history"></a>Version history

* 4.10.10 - *July 2025*

  - Upgrade to SQLite3 Multiple Ciphers version 2.2.2 (SQLite version 3.50.2) to fix issue #126

For further version information please consult the [CHANGELOG](CHANGELOG.md).

## <a name="install" />Installation

The build files for Windows platforms are now generated with
[Premake 5](https://premake.github.io/) (version Premake 5.0 beta 5).

Ready to use project files are provided for Visual C++ 2010, 2012, 2013,
2015, 2017, 2019, and 2022. Additionally, GNU Makefiles are provided supporting for
example MinGW-w64.

For Visual Studio 2010+ solutions it is possible to customize the build
by creating a `wx_local.props` file in the build directory which is used,
if it exists, by the projects. The settings in that file override the
default values for the properties. The typical way to make the file is
to copy `wx_setup.props` to `wx_local.props` and then edit locally.

For GNU Makefiles the file `config.gcc` serves the same purpose as the
file wx_setup.props for Visual C++ projects.

The customization files `wx_setup.props` resp. `config.gcc` allow to
customize certain settings like for example the version number and the
root directory of the wxWidgets library.

### wxMSW

When building on Win32 or Win64, you can use the makefiles or one of the
Microsoft Visual Studio solution files in the `build` folder.

The Visual Studio solution files reference the property file `wx_setup.props`
in the build subdirectory. This file is configured in a way to allow running
AppVeyor CI without any modifications. Especially, specific library directories
are used for different compiler versions (as it is used by the pre-built
wxWidgets libraries) by adding the toolkit version (i.e., 141 for VS 2015,
142 for VS 2019) to the library path name.

To get library path names without toolkit version (as you usually get when
compiling wxWidgets yourself) please adjust the 2 parameters `wxCompilerPrefix`
and `wxMsvcVersionAuto` in file `wx_setup.props` as follows:

```
<wxCompilerPrefix>vc</wxCompilerPrefix>
<wxMsvcVersionAuto></wxMsvcVersionAuto>
```

Additionally, the property file assumes that the environment variable `WXWIN`
is defined and points to the root directory of the wxWidgets installation.
Make sure that `WXWIN` is set up properly, or replace it by a environment
variable of your choice or by an absolute path specification.

For Visual C++ the debugging properties are set up in such a way that
debugging the sample applications should work right out of the box. For
release builds you may need to copy the wxSQLite3 DLL or add the
`lib` folder path to the Windows search path (PATH environment variable).

The SQLite3 library is now compiled as an integrated part of wxSQLite3.
The advantage is that SQLite3 and wxSQLite3 are always compiled with
matching configuration options. Additionally, the SQLite3 encryption
extension is automatically enabled, too.

A precompiled SQLite shell program supporting encrypted
databases is provided as a separate download. Use
```
PRAGMA KEY="encryption key";
```
to create or open an encrypted database. Use
```
ATTACH DATABASE x AS y KEY z;
```
to attach an encrypted database.

### wxGTK

When building on an autoconf-based system (like Linux/GNU-based
systems), the first setup is to recreate the configure script doing:

```
  autoreconf
```

Thereafter you should create a build directory

```
  mkdir build-gtk [or any other suitable name]
  cd build-gtk
  ../configure [here you should use the same flags you used to configure wxWidgets]
  make
```
 
Type `../configure --help` for more info.

The autoconf-based system also supports a `make install` target which
builds the library and then copies the headers of the component to
`/usr/local/include` and the lib to `/usr/local/lib`.

## <a name="optional" />Optional features

SQLite has many optional features and offers a number of optional extensions.
The below table lists the features that are enabled for **wxSQLite3** as
default. For details, please see [SQLite Compile Time Options](https://www.sqlite.org/compile.html).

In case of memory constraints it is of course possible to disable unneeded features.
However, this will usually require to modify the build files.

| Symbol | Description|
| :--- | :--- |
| SQLITE_DQS | Setting for the double-quoted string literal misfeature (default: disabled) |
| SQLITE_ENABLE_CARRAY | C array extension |
| SQLITE_ENABLE_COLUMN_METADATA | Access to meta-data about tables and queries |
| SQLITE_ENABLE_CSV | CSV extension |
| SQLITE_ENABLE_DEBUG | Enable additional debug features (default: off) |
| SQLITE_ENABLE_DESERIALIZE | Option to enable the serialization interface |
| SQLITE_ENABLE_EXPLAIN_COMMENTS | Enable additional comments in EXPLAIN output |
| SQLITE_ENABLE_FTS3 | Version 3 of the full-text search engine |
| SQLITE_ENABLE_FTS3_PARENTHESIS | Additional operators for query pattern parser |
| SQLITE_ENABLE_FTS4 | Version 4 of the full-text search engine |
| SQLITE_ENABLE_FTS5 | Version 5 of the full-text search engine |
| SQLITE_ENABLE_GEOPOLY | Geopoly extension |
| SQLITE_ENABLE_JSON1 | JSON SQL functions |
| SQLITE_ENABLE_REGEXP | Regular expression extension |
| SQLITE_ENABLE_RTREE | R*Tree index extension |
| SQLITE_ENABLE_EXTFUNC | Extension with mathematical and string functions |
| SQLITE_ENABLE_FILEIO | Extension with file I/O SQL functions |
| SQLITE_ENABLE_SERIES | Series extension |
| SQLITE_ENABLE_SHA3 | SHA3 extension |
| SQLITE_ENABLE_UUID | Extension for handling handling RFC-4122 UUIDs |
| SQLITE_MAX_ATTACHED=10 | Maximum Number Of Attached Databases (max. 125) |
| SQLITE_SECURE_DELETE | Overwrite deleted content with zeros |
| SQLITE_SOUNDEX | Enable soundex SQL function |
| SQLITE_THREADSAFE | Setting the multithreading mode (default: serialized)  |
| SQLITE_USE_URI | Enable URI file names |
| SQLITE_USER_AUTHENTICATION | User authentication extension |

## <a name="encryption" />Key based database encryption support

The public release of SQLite contains hooks for key based database
encryption, but the code for implementing this feature is not freely
available. D. Richard Hipp offers a commercial solution
(see [http://www.hwaci.com/sw/sqlite/prosupport.html#crypto](http://www.hwaci.com/sw/sqlite/prosupport.html#crypto)).

There exist other closed-source commercial solutions, among them:

- [http://www.sqlcrypt.com](http://www.sqlcrypt.com)
- [http://www.sqlite-crypt.com](http://www.sqlite-crypt.com)

Both use a slightly different encryption API, which is currently _NOT_
supported by wxSQLite3.

For Windows based systems there exists an open source solution:
[System.Data.SQLite](http://System.Data.SQLite.org). For SQLite version 3.32.0 or higher encryption support has been dropped.
However, the new encryption extension _SQLite3 Multiple Ciphers_ allows to use this encryption scheme on all supported platforms.

**wxSQLite3** uses now the new encryption extension [SQLite3 Multiple Ciphers](https://github.com/utelle/SQLite3MultipleCiphers).
Precompiled binaries of the SQLite3 DLL and the SQLite3 shell  for Windows are now provided by this new separate project.

## <a name="sqlite-static"></a>Using statically linked SQLite library on Windows

Starting with wxSQLite3 version 3.5.0 the SQLite3 library is compiled as an
integrated part of wxSQLite3. A separate SQLite3 DLL is not required any longer.

## <a name="license" />License

**wxSQLite3** is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License version 3
or later as published by the Free Software Foundation,
with the wxWindows 3.1 exception.

## <a name="acknowledge" />Acknowledgements

The following people have contributed to **wxSQLite3**:

- Vadim Zeitlin (revision of the build system)
- Francesco Montorsi (enhancement of the build system)
- Neville Dastur (enhancement of the method TableExists)
- Tobias Langner (RAII class for managing transactions)

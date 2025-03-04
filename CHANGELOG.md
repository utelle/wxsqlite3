# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [4.10.5] - 2025-03-04

  - Upgrade to SQLite3 Multiple Ciphers version 2.1.0 (SQLite version 3.49.1)
  - Disable AEGIS cipher scheme when compiling with MSVC 2015 or below

## [4.10.4] - 2025-02-21

  - Upgrade to SQLite3 Multiple Ciphers version 2.0.4 (SQLite version 3.49.1)

## [4.10.3] - 2025-02-10

  - Upgrade to SQLite3 Multiple Ciphers version 2.0.3 (SQLite version 3.49.0)

## [4.10.2] - 2025-01-16

  - Upgrade to SQLite3 Multiple Ciphers version 2.0.2 (SQLite version 3.48.0)

## [4.10.1] - 2025-01-06

  - Upgrade to SQLite3 Multiple Ciphers version 2.0.1 (SQLite version 3.47.2)
  - Fixed issue #120 - crashes on some Linux systems due to _illegal instruction_ exceptions related to the code of the new cipher scheme _AEGIS_

## [4.10.0] - 2024-12-31

- Upgrade to SQLite3 Multiple Ciphers version 2.0.0 (SQLite version 3.47.2)
- Removed support for User Authentication extension
- Added new cipher scheme AEGIS

## [4.9.12] - 2024-10-22

- Upgrade to SQLite3 Multiple Ciphers version 1.9.0 (SQLite version 3.47.0)

## [4.9.11] - 2024-06-14

- Upgrade to SQLite3 Multiple Ciphers version 1.8.6 (SQLite version 3.46.0)

## [4.9.10] - 2024-03-27

- Upgrade to SQLite3 Multiple Ciphers version 1.8.4 (SQLite version 3.45.2)
- Disable user authentication extension in build files by default

## [4.9.9] - 2024-01-18

- Upgrade to SQLite3 Multiple Ciphers version 1.8.2 (SQLite version 3.45.0)

## [4.9.8] - 2023-11-23

- Upgrade to SQLite3 Multiple Ciphers version 1.8.0 (SQLite version 3.44.1)
- Added new cipher scheme Ascon-128 (Lightweight Authenticated Encryption)

## [4.9.7] - 2023-11-09

- Upgrade to SQLite3 Multiple Ciphers version 1.7.4 (SQLite version 3.44.0)
- Prevent crashes due to uninitialized cipher tables (issue #113)

## [4.9.6] - 2023-10-04

- Upgrade to SQLite3 Multiple Ciphers version 1.7.0 (SQLite version 3.43.1)

## [4.9.5] - 2023-09-15

- Upgrade to SQLite3 Multiple Ciphers version 1.6.5 (SQLite version 3.43.1)

## [4.9.4] - 2023-05-29

- Upgrade to SQLite3 Multiple Ciphers version 1.6.3 (SQLite version 3.42.0)

## [4.9.3] - 2023-03-15

- Upgrade to SQLite3 Multiple Ciphers version 1.6.1 (SQLite version 3.41.1)

## [4.9.2] - 2023-02-24

- Upgrade to SQLite3 Multiple Ciphers version 1.6.0 (SQLite version 3.41.0)
- Enhanced method wxSQLite3Database::Open allowing to set the VFS to be used
- Added method wxSQLite3Database::IsInterrupted

## [4.9.1] - 2022-11-19

- Upgrade to SQLite3 Multiple Ciphers version 1.5.4 (SQLite version 3.40.0)

## [4.9.0] - 2022-09-08

- Upgrade to SQLite3 Multiple Ciphers version 1.5.3 (SQLite version 3.39.3)

## [4.8.2] - 2022-07-17

- Upgrade to SQLite3 Multiple Ciphers version 1.4.6 (SQLite version 3.39.1)

## [4.8.1] - 2022-05-07

- Upgrade to SQLite3 Multiple Ciphers version 1.4.3 (SQLite version 3.38.5)

## [4.8.0] - 2022-04-27

- Upgrade to SQLite3 Multiple Ciphers version 1.4.2 (SQLite version 3.38.3)

## [4.7.9] - 2022-04-01

- Upgrade to SQLite3 Multiple Ciphers version 1.3.10 (SQLite version 3.38.2)

## [4.7.8] - 2022-03-16

- Upgrade to SQLite3 Multiple Ciphers version 1.3.9 (SQLite version 3.38.1)

## [4.7.7] - 2022-02-26

- Upgrade to SQLite3 Multiple Ciphers version 1.3.8 (SQLite version 3.38.0)

## [4.7.6] - 2022-01-10

- Upgrade to SQLite3 Multiple Ciphers version 1.3.7 (SQLite version 3.37.2)

## [4.7.5] - 2021-11-29

- Upgrade to SQLite3 Multiple Ciphers version 1.3.5 (SQLite version 3.37.0)
- Added build support for Visual C++ 2022

## [4.7.4] - 2021-07-24

- Upgrade to SQLite3 Multiple Ciphers version 1.3.4 (SQLite version 3.36.0)

## [4.7.3] - 2021-06-19

- Upgrade to SQLite3 Multiple Ciphers version 1.3.3 (SQLite version 3.36.0)

## [4.7.2] - 2021-05-14

- Upgrade to SQLite3 Multiple Ciphers version 1.3.2 (SQLite version 3.35.5)

## [4.7.1] - 2021-04-28

- Upgrade to SQLite3 Multiple Ciphers version 1.3.1 (SQLite version 3.35.5)

## [4.7.0] - 2021-04-24

- Upgrade to SQLite3 Multiple Ciphers version 1.3.0 (SQLite version 3.35.5)

## [4.6.10] - 2021-04-20

- Upgrade to SQLite3 Multiple Ciphers version 1.2.5 (SQLite version 3.35.5)

## [4.6.9] - 2021-04-05

- Upgrade to SQLite3 Multiple Ciphers version 1.2.4 (SQLite version 3.35.4)

## [4.6.8] - 2021-03-27

- Upgrade to SQLite3 Multiple Ciphers version 1.2.3 (SQLite version 3.35.3)

## [4.6.7] - 2021-03-22

- Upgrade to SQLite3 Multiple Ciphers version 1.2.2 (SQLite version 3.35.2)

## [4.6.6] - 2021-03-16

- Upgrade to SQLite3 Multiple Ciphers version 1.2.1 (SQLite version 3.35.1)

## [4.6.5] - 2021-03-14

- Upgrade to SQLite3 Multiple Ciphers version 1.2.0 (SQLite version 3.35.0)
- Enabled new SQLite Math Extension
- Fixed a memory leak in method wxSQLite3Database::GetTable
- Adjusted build files (DLL builds with MinGW/GCC used wrong DLL file extension)

## [4.6.4] - 2020-12-30

- Upgrade to SQLite3 Multiple Ciphers version 1.1.3
- Adjusted autotool build files to enable AES hardware support if available

## [4.6.3] - 2020-12-12

- Upgrade to SQLite3 Multiple Ciphers version 1.1.2
- Adjusted build files for MinGW

## [4.6.2] - 2020-12-07

- Upgrade to SQLite3 Multiple Ciphers version 1.1.1
- Upgrade to SQLite version 3.34.0
- Added method `wxSQLite3Database::QueryTransactionState`

## [4.6.1] - 2020-10-04

- Added SQLite VSV extension (Variably Separated Values)

## [4.6.0] - 2020-08-16

- Use SQLite encryption extension _SQLite3 Multiple Ciphers_
- Upgrade to SQLite version 3.33.0
- Added support for System.Data.SQLite's RC4 encryption

## [4.5.1] - 2020-01-28

- Upgrade to SQLite version 3.31.1

## [4.5.0] - 2020-01-26

- Upgrade to SQLite version 3.31.0
- Modified API for wxSQLite3Database::CreateFunction methods

## [4.4.8] - 2019-10-13

- Upgrade to SQLite version 3.30.1
- Adjusted encryption extension to support SQLite's shared cache mode

## [4.4.7] - 2019-10-06

- Upgrade to SQLite version 3.30.0

## [4.4.6] - 2019-09-02

- Fixed missing cipher application in method wxSQLite3Database::ReKey

## [4.4.5] - 2019-08-08

- Fixed broken compatibility with wxWidgets 2.8.12

## [4.4.4] - 2019-08-08

- Upgrade to SQLite version 3.29.0
- Added SQLite logging support
- Added build support for VS2019
- Added CMake support (PR #63)
- Updated build files to overcome problems with static builds (issue #73)
- Eliminated duplication of error messages for different wxWidgets builds (PR #64)
- Fixed missing call to progress callback in wxSQLite3Database::Restore (PR #66)
- Fixed issue #58 with silently failing wxSQLite3Transaction::Commit method
- Fixed issue with named collections which could result in crashes (PR #59)

## [4.4.3] - 2019-05-18

- Upgrade to SQLite version 3.28.0

## [4.4.2] - 2019-02-28

- Upgrade to SQLite version 3.27.2

## [4.4.1] - 2019-02-10

- Upgrade to SQLite version 3.27.1

## [4.4.0] - 2018-12-14

- Upgrade to SQLite version 3.26.0
- Added support for the SQLCipher 4 database format

## [4.3.0] - 2018-11-15

- Upgrade to SQLite version 3.25.3
- Adjusted encryption extension to support cipher configuration via database URI

## [4.2.0] - 2018-10-29

- Added method wxSQLite3Database::GetKeySalt to access the key salt of encrypted databases
- Fixed memory leaks in methods wxSQLite3ResultSet::GetExpandedSQL and wxSQLite3Statement::GetExpandedSQL
- Adjusted encryption extension to support raw key (and salt) for the **ChaCha20 (sqleet)** encryption scheme

## [4.1.1] - 2018-10-02

- Upgrade to SQLite version 3.25.2

## [4.1.0] - 2018-09-21

- Upgrade to SQLite version 3.25.1
- Added support for SQL window functions
- Adjusted encryption extension to check for matching page sizes on rekeying a database

## [4.0.4] - 2018-06-09

- Upgrade to SQLite version 3.24.0

## [4.0.3] - 2018-04-23

- Adjusted encryption extension to better support the SQLite backup API

## [4.0.2] - 2018-04-13

- Upgrade to SQLite version 3.23.1

## [4.0.1] - 2018-04-11

- Fixed a bug in the rekeying function of the encryption extension

## [4.0.0] - 2018-04-10

- Added multi-cipher support
- Added methods for attaching/detaching databases
- Cleaned up code using statement buffers

## [3.5.9] - 2018-01-24

- Upgrade to SQLite version 3.22.0

## [3.5.8] - 2017-11-02

- Upgrade to SQLite version 3.21.0

## [3.5.7] - 2017-09-07

- Upgrade to SQLite version 3.20.1

## [3.5.6] - 2017-08-03

- Upgrade to SQLite version 3.20.0
- Added support for persistent prepared statements
- Added support for binding pointers (new SQLite pointer-binding interface)
- Added several SQLite extensions (csv, sha3, carray, fileio, series) for the included SQLite library
- Modified build files to expose the parameter SQLITE_MAX_ATTACHED to allow easier adjustment of the maximum number of attached databases

## [3.5.5] - 2017-06-09

- Upgrade to SQLite version 3.19.3

## [3.5.4] - 2017-06-05

- Upgrade to SQLite version 3.19.2

## [3.5.3] - 2017-03-31

- Upgrade to SQLite version 3.18.0
- Minor modification to wxsqlite3.pc.in to fix issue with pkgconfig tool

## [3.5.2] - 2017-03-19

- Upgrade to SQLite version 3.17.0
- Fixed minor issue in SQLite encryption extension related to symbol `SQLITE_DEBUG`
- Modified build system for GNU make (support monolithic wxWidgets build)

## [3.5.1] - 2017-02-01

- Added version information as Windows resource for DLL builds on Windows
- Cleaned up premake5 build files for Visual C++ (corrected debug environment settings)
- Resolved wxWidgets library dependencies for Visual C++ using wxWidgets' special setup.h for MSVC

## [3.5.0] - 2017-01-30

- Upgrade to SQLite version 3.16.2
- SQLite3 library now integrated part of wxSQLite3
- Overhaul of build system

## [3.4.1] - 2016-10-19

- Upgrade to SQLite version 3.15.0

## [3.4.0] - 2016-08-13

- Upgrade to SQLite version 3.14.1
- Added method `wxSQLite3Statement::GetExpandedSQL`
- Added method `wxSQLite3ResultSet::GetExpandedSQL`
- Started to modify the build system to compile and statically link the SQLite3 library together with wxSQLite3
- Added the CSV extension module as part of the SQLite3 library with encryption extension

## [3.3.1] - 2016-04-10

- Upgrade to SQLite version 3.12.1
- Added method `wxSQLite3Database::GetSystemErrorCode`

## [3.3.0] - 2015-12-16

- Upgrade to SQLite version 3.9.2 (including adjusted SQLite amalgamation source to fix problem with the user authentication module)
- Transition from SourceForge to GitHub

## [3.2.1] - 2015-03-04

- Upgrade to SQLite version 3.8.8.3
- Fixed a bug in method GetParamName

## [3.2.0] - 2014-12-25

- Upgrade to SQLite version 3.8.7.4
- Added support for the SQLite user authentication module

## [3.1.1] - 2014-06-28

- Upgrade to SQLite version 3.8.5

## [3.1.0] - 2014-05-26

- Upgrade to SQLite version 3.8.4.3
- Added flag `isDeterministic` to method `wxSQLite3Database::CreateFunction`
- Added new GUI sample
- Changed implementation of encryption extension (see readme file in sqlite3 subfolder)

## [3.0.6] - 2013-12-08

- Upgrade to SQLite version 3.8.2

## [3.0.5] - 2013-10-19

- Upgrade to SQLite version 3.8.0.2
- Added support for setting the temporary directory for SQLite on Windows

## [3.0.4] - 2013-08-29

- Upgrade to SQLite version 3.8.0
- Added support for querying performance characteristics of prepared statements

## [3.0.3] - 2013-03-19

- Upgrade to SQLite version 3.7.16

## [3.0.2] - 2012-12-22

- Upgrade to SQLite version 3.7.15.1
- Corrected an internal SQLite data structure to avoid compile time warnings
- Changed method `wxSQLite3Exception::ErrorCodeAsString` to return the error messages provided by SQLite

## [3.0.1] - 2012-11-24

- Upgrade to SQLite version 3.7.14.1
- Cleaned up and optimized Finalize methods
- Modified `wxSQLite3Database::Close` to avoid potential memory leaks
- Added method `wxSQLite3Database::GetWrapperVersion`
- Added method `wxSQLite3Database::IsReadOnly`
- Added method `wxSQLite3Statement::BindUnixDateTime`
- Added method `wxSQLite3ResultSet::GetUnixDateTime`
- Added method `wxSQLite3ResultSet::GetAutomaticDateTime`
- Fixed a potential memory leak in method `wxSQLite3Database::ExecuteUpdate`
- Added a `wxsqlite3.pc` file on request of the Fedora Project developers
- Replaced assert by `wxASSERT` in `wxSQLite3Transaction` constructor

## [3.0.0] - 2012-01-19

- Upgrade to SQLite version 3.7.10
- Added method `wxSQLite3Database::Vacuum`
- Added method `wxSQLite3Database::GetDatabaseFilename`
- Added method `wxSQLite3Database::ReleaseMemory`
- Added method `wxSQLite3ResultSet::CursorMoved`
- Added method `wxSQLite3Statement::IsBusy`
- Fixed a bug in method `operator=` of `wxSQLite3StringCollection` causing an endless recursion on assignment
- Dropped the concept of SQLite3 pointer ownership in favor of reference counted pointers allowing much more flexible use of wxSQLite3 classes
- Modified SQLite3 encryption extension (defining int64 datatype for SHA2 algorithm)
- Dropped dbadmin sample from build files
- Added Premake support for SQLite3 library with encryption support and for wxSQLite3 (experimental)

## [2.1.3] - 2011-08-16

- Corrected default behaviour for attached databases in case of an encrypted main database. (Now the attached database uses the same encryption key as the main database if no explicit key is given. Previously the attached database remained unencrypted.)
- Added an optional progress callback for metheods Backup & Restore
- Added method `SetBackupRestorePageCount` to set the number of pages to be copied in one cycle of the backup/restore process

## [2.1.2] - 2011-07-06

- Upgrade to SQLite version 3.7.7.1
- Modified `wxSQLite3Transaction` class to make it exception safe

## [2.1.1] - 2011-04-17

- Upgrade to SQLite version 3.7.6.1
- Added convenience method `wxSQLite3Statement::ExecuteScalar`
- Changed write-ahead log checkpoint method to new version (v2)

## [2.1.0] - 2011-03-13

- Upgrade to SQLite version 3.7.5
- Added wxSQLite+, a database administration application written by Fred Cailleau-Lepetit, as a GUI sample for wxSQLite3. Minor adjustments were applied to make wxSQLite+ compatible with wxWidgets 2.9.x. To compile and link wxSQLite+ successfully using wxWidgets 2.8.x it is required to build the "stc" library (scintilla) in the "contrib" folder of wxWidgets. Please note that wxSQLite+ is under GPL license.

## [2.0.2] - 2010-12-11

- Upgrade to SQLite version 3.7.4

## [2.0.1] - 2010-10-14

- Upgrade to SQLite version 3.7.3
- Added parameter `transferStatementOwnership` to method `wxSQLite3Statement::ExecuteQuery` to allow using the returned result set beyond the life time of the `wxSQLite3Statement` instance

## [2.0.0.1] - 2010-08-05

- Upgrade to SQLite version 3.7.0.1
- Added missing function interfaces in `wxsqlite3dyn.h`
- Adjusted code to eliminate a reference to `sqlite3_mprintf`

## [2.0.0] - 2010-07-23

- Upgrade to SQLite version 3.7.0
- Fixed a bug in class `wxSQLite3ResultSet`
- Added support for SQLite's write-ahead log journal mode
- Added support for named collections (see class `wxSQLite3NamedCollection`)
- Changed UTF-8 string handling to use methods To/FromUTF8 of the wxString class (requires wxWidgets 2.8.4 or higher)
- Compatible with wxWidgets 2.9.1

## [1.9.9] - 2010-03-21

- Upgrade to SQLite version 3.6.23
- Fixed a bug when compiling for dynamic loading of SQLite
- Added static methods to class `wxSQLite3Database` for accessing the run-time library compilation options diagnostics
- Added mathod FormatV to class `wxSQLite3StatementBuffer`

## [1.9.8] - 2010-02-06

- Upgrade to SQLite version 3.6.22
- Fixed a bug when compiling without precompiled header support (by including wx/arrstr.h)
- Added experimental support for 256 bit AES encryption to the optional key based encryption extension

## [1.9.7] - 2009-11-10

- Upgrade to SQLite version 3.6.20
- Added methods to query, enable or disable foreign key support

## [1.9.6] - 2009-09-13

- Upgrade to SQLite version 3.6.18
- Added method to get the SQLite library source id
- Added `flags` parameter to `wxSQLite3Database::Open` to allow additional control over the database connection (see [http://www.sqlite.org/c3ref/open.html](http://www.sqlite.org/c3ref/open.html) for further information)
- Fixed a potential memory leak in `wxSQLite3Statement` class
- Converted encryption extension from C++ to pure C to make it compatible with the SQLite amalgamation.

## [1.9.5] - 2009-02-22

- Upgrade to SQLite version 3.6.11
- Added user defined function class for REGEXP operator
- Added support for SQLite backup/restore API, introduced with SQLite 3.6.11

## [1.9.4] - 2009-01-23

- Upgrade to SQLite version 3.6.10
- Added support for SQLite savepoints, introduced with SQLite 3.6.8
- Added IsOk methods to several classes

## [1.9.3] - 2008-12-18

- Upgrade to SQLite version 3.6.7
- Fixed a bug in method `wxSQLite3Table::GetDouble` (conversion from string to double failed in non-US locales)
- Build system upgraded using Bakefile 0.2.5

## [1.9.2] - 2008-11-22

- Upgrade to SQLite version 3.6.6
- Added RAII transaction class (see docs for details)

## [1.9.1] - 2008-09-06

- Upgrade to SQLite version 3.6.2
- Introduced own step counting for aggregate user functions since the `sqlite3_aggregate_count` function is now deprecated.
- Enhanced `wxSQLite3Database::TableExists` method to query an attached database for existence of a table or to query all open databases.

## [1.9.0] - 2008-07-20

- Upgrade to SQLite version 3.6.0
- The optional key based encryption support has been adapted to support SQLite version 3.6.0.
- Added static methods to initialize and shutdown the SQLite library.
- Changed build system to support static library build against shared wxWidgets build on Linux.
- Changed behaviour of `Close` method of class `wxSQLite3Database` to finalize all unfinalized prepared statements.

## [1.8.5] - 2008-06-28

- Upgrade to SQLite version 3.5.9
- Integration of the optional key based encryption support into SQLite has been made easier. Changes to original SQLite source files are no longer necessary.

## [1.8.4] - 2008-05-01

- Upgrade to SQLite version 3.5.8
- Added support for accessing database limits
- Changed method `TableExists` to check a table name case insensitive
- Fixed several minor issues in the build files.

## [1.8.3] - January 2008

- Added support for shared cache mode
- Added support for access to original SQL statement for prepared statements (requires SQLite 3.5.3 or above)
- Fixed broken SQLite DLLs

## [1.8.2] - Dezember 2007

- Upgrade to SQLite version 3.5.4
- Fixed a bug in in `wxSQLite3Database::Begin` (wrong transaction type)

## [1.8.1] - November 2007

- Fixed a bug in in `wxSQLite3Database::Close` (resetting flag `m_isEncrypted`)
- Eliminated several compile time warnings (regarding unused parameters)
- Fixed a compile time bug in `wxSQLite3Database::GetBlob` (missing explicit type cast)

## [1.8.0] - November 2007

- Upgrade to SQLite version 3.5.2
- Support for SQLite incremental BLOBs
- Changed source code in the SQLite3 encryption extension to eliminate several warnings
- Changed default wxWidgets version to 2.8.x
- Adjusted sources for SQLite encryption support are included for all SQLite version from 3.3.1 up to 3.5.2
- SQLite link libraries for MinGW on Windows are included
- Added `WXMAKINGLIB_WXSQLITE3` compile time option to support building wxSQLite3 as a static library while using the shared libraries of wxWidgets.

## [1.7.3] - May 2007

- Upgrade to SQLite version 3.3.17
- Fixed a bug in the SQLite3 encryption extension (MD5 algorithm was not aware of endianess on big-endian platforms, resulting in non-portable database files)

## [1.7.2] - February 2007

- Upgrade to SQLite version 3.3.11
- Support for loadable extensions is now optional
- Check for optional wxSQLite3 features at runtime
- wxSQLite3 API independent of optional features

## [1.7.1] - January 2007

- Fixed a bug in the key based database encryption feature (The call to `sqlite3_rekey` in `wxSQLite3Database::ReKey` could cause a program crash, when used to encrypt a previously unencrypted database.)

## [1.7.0] - January 2007

- Upgrade to SQLite version 3.3.10
- Added support for BLOBs as wxMemoryBuffer objects
- Added support for loadable extensions
- Optional support for key based database encryption

## [1.6.0] - July 2006

- Added support for user-defined collation sequences

## [1.5.3] - June 2006

- Upgrade to SQLite version 3.3.6
- Added support for optional SQLite meta data methods

## [1.5.2] - March 2006

- Fixed a bug in wxSQLite3Database::Prepare
- Added `wxSQLite3Database::IsOpen` for convenience

## [1.5.1] - February 2006

- SQLite DLL upgraded to version 3.3.4

## [1.5] - February 2006

- Upgrade to SQLite version 3.3.3
- Added support for commit, rollback and update callbacks

## [1.4.2] - November 2005

- Optimized code for wxString arguments

## [1.4.1] - November 2005

- Fixed a bug in `TableExists`, eliminated some compiler warnings
- Changed handling of Unicode string conversion
- Added support for different transaction types

## [1.4] - November 2005

- Optionally load SQLite library dynamically at run time

## [1.3.1] - November 2005

- Corrected `wxSQLite3ResultSet::GetInt64`,
- Added `wxSQLite3Table::GetInt64`

## [1.3] - October 2005

- Added wxGTK build support

## [1.2] - October 2005

- Corrected error in `wxSQLite3Table::FindColumnIndex`

## [1.1] - October 2005

- Upgrade to SQLite version 3.2.7

## [1.0] - July 2005

- First public release

[Unreleased]: ../../compare/v4.10.5...HEAD
[4.10.5]: ../../compare/v4.10.4...v4.10.5
[4.10.4]: ../../compare/v4.10.3...v4.10.4
[4.10.3]: ../../compare/v4.10.2...v4.10.3
[4.10.2]: ../../compare/v4.10.1...v4.10.2
[4.10.1]: ../../compare/v4.10.0...v4.10.1
[4.10.0]: ../../compare/v4.9.12...v4.10.0
[4.9.12]: ../../compare/v4.9.11...v4.9.12
[4.9.11]: ../../compare/v4.9.10...v4.9.11
[4.9.10]: ../../compare/v4.9.9...v4.9.10
[4.9.9]: ../../compare/v4.9.8...v4.9.9
[4.9.8]: ../../compare/v4.9.7...v4.9.8
[4.9.7]: ../../compare/v4.9.6...v4.9.7
[4.9.6]: ../../compare/v4.9.5...v4.9.6
[4.9.5]: ../../compare/v4.9.4...v4.9.5
[4.9.4]: ../../compare/v4.9.3...v4.9.4
[4.9.3]: ../../compare/v4.9.2...v4.9.3
[4.9.2]: ../../compare/v4.9.1...v4.9.2
[4.9.1]: ../../compare/v4.9.0...v4.9.1
[4.9.0]: ../../compare/v4.8.2...v4.9.0
[4.8.2]: ../../compare/v4.8.1...v4.8.2
[4.8.1]: ../../compare/v4.8.0...v4.8.1
[4.8.0]: ../../compare/v4.7.9...v4.8.0
[4.7.9]: ../../compare/v4.7.8...v4.7.9
[4.7.8]: ../../compare/v4.7.7...v4.7.8
[4.7.7]: ../../compare/v4.7.6...v4.7.7
[4.7.6]: ../../compare/v4.7.5...v4.7.6
[4.7.5]: ../../compare/v4.7.4...v4.7.5
[4.7.4]: ../../compare/v4.7.3...v4.7.4
[4.7.3]: ../../compare/v4.7.2...v4.7.3
[4.7.2]: ../../compare/v4.7.1...v4.7.2
[4.7.1]: ../../compare/v4.7.0...v4.7.1
[4.7.0]: ../../compare/v4.6.10...v4.7.0
[4.6.10]: ../../compare/v4.6.9...v4.6.10
[4.6.9]: ../../compare/v4.6.8...v4.6.9
[4.6.8]: ../../compare/v4.6.7...v4.6.8
[4.6.7]: ../../compare/v4.6.6...v4.6.7
[4.6.6]: ../../compare/v4.6.5...v4.6.6
[4.6.5]: ../../compare/v4.6.4...v4.6.5
[4.6.4]: ../../compare/v4.6.3...v4.6.4
[4.6.3]: ../../compare/v4.6.2...v4.6.3
[4.6.2]: ../../compare/v4.6.1...v4.6.2
[4.6.1]: ../../compare/v4.6.0...v4.6.1
[4.6.0]: ../../compare/v4.5.1...v4.6.0
[4.5.1]: ../../compare/v4.5.0...v4.5.1
[4.5.0]: ../../compare/v4.4.8...v4.5.0
[4.4.8]: ../../compare/v4.4.7...v4.4.8
[4.4.7]: ../../compare/v4.4.6...v4.4.7
[4.4.6]: ../../compare/v4.4.5...v4.4.6
[4.4.5]: ../../compare/v4.4.4...v4.4.5
[4.4.4]: ../../compare/v4.4.3...v4.4.4
[4.4.3]: ../../compare/v4.4.2...v4.4.3
[4.4.2]: ../../compare/v4.4.1...v4.4.2
[4.4.1]: ../../compare/v4.4.0...v4.4.1
[4.4.0]: ../../compare/v4.3.0...v4.4.0
[4.3.0]: ../../compare/v4.2.0...v4.3.0
[4.2.0]: ../../compare/v4.1.1...v4.2.0
[4.1.1]: ../../compare/v4.1.0...v4.1.1
[4.1.0]: ../../compare/v4.0.4...v4.1.0
[4.0.4]: ../../compare/v4.0.3...v4.0.4
[4.0.3]: ../../compare/v4.0.2...v4.0.3
[4.0.2]: ../../compare/v4.0.1...v4.0.2
[4.0.1]: ../../compare/v4.0.0...v4.0.1
[4.0.0]: ../../compare/v3.5.9...v4.0.0
[3.5.9]: ../../compare/v3.5.8...v3.5.9
[3.5.8]: ../../compare/v3.5.7...v3.5.8
[3.5.7]: ../../compare/v3.5.6...v3.5.7
[3.5.6]: ../../compare/v3.5.5...v3.5.6
[3.5.5]: ../../compare/v3.5.4...v3.5.5
[3.5.4]: ../../compare/v3.5.3...v3.5.4
[3.5.3]: ../../compare/v3.5.2...v3.5.3
[3.5.2]: ../../compare/v3.5.1...v3.5.2
[3.5.1]: ../../compare/v3.5.0...v3.5.1
[3.5.0]: ../../compare/v3.4.1...v3.5.0
[3.4.1]: ../../compare/v3.4.0...v3.4.1
[3.4.0]: ../../compare/v3.3.1...v3.4.0
[3.3.1]: ../../compare/v3.3.0...v3.3.1
[3.3.0]:

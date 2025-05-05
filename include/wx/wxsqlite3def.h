  /*
** Name:        wxsqlite3def.h
** Purpose:     wxWidgets wrapper around the SQLite3 embedded database library.
** Author:      Ulrich Telle
** Created:     2005-07-14
** Copyright:   (c) 2005-2025 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

/// \file wxsqlite3def.h Compile time switches for the wxSQLite3 class

/** \mainpage wxSQLite3

\section intro What is wxSQLite3?

  \b wxSQLite3 is a C++ wrapper around the public domain <a href="http://www.sqlite.org">SQLite 3.x</a> database
  and is specifically designed for use in programs based on the \b wxWidgets library.

  Several solutions already exist to access SQLite databases. To name just a few:

  - <a href="http://sourceforge.net/projects/wxsqlite">wxSQLite</a> :
    This is a wxWidgets wrapper for version 2.8.x of SQLite.
    SQLite version 3.x has a lot more features - which are not supported by this wrapper.

  - <a href="http://www.codeproject.com/database/CppSQLite.asp">CppSQLite</a> :
    Not wxWidgets specific, but with (partial) support for the newer version 3.x of SQLite.

  - <a href="http://wxcode.sf.net">DatabaseLayer</a> :
    This is a database abstraction providing a JDBC-like interface to database I/O.
    In the current version SQLite3, PostgreSQL, MySQL, Firebird, and ODBC database backends
    are supported.

  The component \b wxSQLite3 was inspired by all three mentioned SQLite wrappers.
  \b wxSQLite3 does not try to hide the underlying database, in contrary almost all special features
  of the SQLite3 version 3.x are supported, like for example the creation of user defined
  scalar or aggregate functions.

  Since SQLite stores strings in UTF-8 encoding, the wxSQLite3 methods provide automatic conversion
  between wxStrings and UTF-8 strings. The methods ToUTF8 and FromUTF8 of the wxString class (available
  since wxWidgets 2.8.4) are used for the conversion. Special care has to be taken if external administration
  tools are used to modify the database contents, since not all of these tools operate in Unicode or UTF-8 mode.

\note With the release of SQLite version 3.32.0 on May 22, 2020 critical changes to the public SQLite code finally took officially effect, although they weren't officially announced. They were introduced on Feb 7, 2020: ["Simplify the code by removing the unsupported and undocumented SQLITE_HAS_CODEC compile-time option"](https://www.sqlite.org/src/timeline?c=5a877221ce90e752). Since August 2020 a new implementation of an encryption extension, capable of supporting SQLite version 3.32.0 and later, is available as a separate project, [**SQLite3 Multiple Ciphers**](https://github.com/utelle/SQLite3MultipleCiphers). Starting with the release of **wxSQLite3 4.6.0** this new implementation will be used.

\section version Version history

<dl>

<dt><b>4.10.6</b> - <i>May 2025</i></dt>
<dd>
Add method wxSQLite3Database::Configure()<br>
Add missing wxSQLite3Database::Restore() method variant<br>
Fix mapping between cipher ids and cipher names

</dd>

<dt><b>4.10.5</b> - <i>March 2025</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 2.1.0 (SQLite version 3.49.1)</i><br>
Disable AEGIS cipher scheme when compiling with MSVC 2015 or below

</dd>

<dt><b>4.10.4</b> - <i>February 2025</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 2.0.4 (SQLite version 3.49.1)</i>

</dd>

<dt><b>4.10.3</b> - <i>February 2025</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 2.0.3 (SQLite version 3.49.0)</i>

</dd>

<dt><b>4.10.2</b> - <i>January 2025</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 2.0.2 (SQLite version 3.48.0)</i>

</dd>

<dt><b>4.10.1</b> - <i>January 2025</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 2.0.1 (SQLite version 3.47.2)</i><br>
Fixed issue #120 - crashes on some Linux systems due to <i>illegal instruction</i> exceptions related to the code of the new cipher scheme <i>AEGIS</i>

</dd>

<dt><b>4.10.0</b> - <i>December 2024</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 2.0.0 (SQLite version 3.47.2)</i><br>
Removed <i>User Authentication</i> extension<br>
Added new cipher scheme AEGIS

</dd>

<dt><b>4.9.12</b> - <i>October 2024</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.9.0 (SQLite version 3.47.0)</i>

</dd>

<dt><b>4.9.11</b> - <i>June 2024</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.8.6 (SQLite version 3.46.0)</i>

</dd>

<dt><b>4.9.10</b> - <i>March 2024</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.8.4 (SQLite version 3.45.2)</i><br>
Disable user authentication extension in build files by default

</dd>

<dt><b>4.9.9</b> - <i>January 2024</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.8.2 (SQLite version 3.45.0)</i>

</dd>

<dt><b>4.9.8</b> - <i>November 2023</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.8.0 (SQLite version 3.44.1)</i><br>
Added new cipher scheme Ascon-128 (Lightweight Authenticated Encryption)

</dd>

<dt><b>4.9.7</b> - <i>November 2023</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.7.4 (SQLite version 3.44.0)</i><br>
Prevent crashes due to uninitialized cipher tables (issue #113)

</dd>

<dt><b>4.9.6</b> - <i>October 2023</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.7.0 (SQLite version 3.43.1)</i><br>

</dd>

<dt><b>4.9.5</b> - <i>September 2023</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.6.5 (SQLite version 3.43.1)</i><br>

</dd>

<dt><b>4.9.4</b> - <i>May 2023</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.6.3 (SQLite version 3.42.0)</i><br>

</dd>

<dt><b>4.9.3</b> - <i>March 2023</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.6.1 (SQLite version 3.41.1)</i><br>

</dd>

<dt><b>4.9.2</b> - <i>February 2023</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.6.0 (SQLite version 3.41.0)</i><br>
Enhanced method wxSQLite3Database::Open allowing to set the VFS to be used<br>
Added method wxSQLite3Database::IsInterrupted<br>

</dd>

<dt><b>4.9.1</b> - <i>November 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.5.4 (SQLite version 3.40.0)</i><br>

</dd>

<dt><b>4.9.0</b> - <i>September 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.5.3 (SQLite version 3.39.3)</i><br>

</dd>

<dt><b>4.8.2</b> - <i>July 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.4.6 (SQLite version 3.39.1)</i><br>

</dd>

<dt><b>4.8.1</b> - <i>May 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.4.3 (SQLite version 3.38.5)</i><br>

</dd>

<dt><b>4.8.0</b> - <i>April 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.4.2 (SQLite version 3.38.3)</i><br>

</dd>

<dt><b>4.7.9</b> - <i>April 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.10 (SQLite version 3.38.2)</i><br>

</dd>
<dt><b>4.7.8</b> - <i>March 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.9 (SQLite version 3.38.1)</i><br>

</dd>
<dt><b>4.7.7</b> - <i>February 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.8 (SQLite version 3.38.0)</i><br>

</dd>
<dt><b>4.7.6</b> - <i>January 2022</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.7 (SQLite version 3.37.2)</i><br>

</dd>
<dt><b>4.7.5</b> - <i>November 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.5 (SQLite version 3.37.0)</i><br>

</dd>
<dt><b>4.7.4</b> - <i>July 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.4 (SQLite version 3.36.0)</i><br>

</dd>
<dt><b>4.7.3</b> - <i>June 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.3 (SQLite version 3.36.0)</i><br>

</dd>
<dt><b>4.7.2</b> - <i>May 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.2 (SQLite version 3.35.5)</i><br>

</dd>
<dt><b>4.7.1</b> - <i>April 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.1 (SQLite version 3.35.5)</i><br>

</dd>
<dt><b>4.7.0</b> - <i>April 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.3.0 (SQLite version 3.35.5)</i><br>

</dd>
<dt><b>4.6.10</b> - <i>April 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.2.5 (SQLite version 3.35.5)</i><br>

</dd>
<dt><b>4.6.9</b> - <i>April 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.2.4 (SQLite version 3.35.4)</i><br>

</dd>
<dt><b>4.6.8</b> - <i>March 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.2.3 (SQLite version 3.35.3)</i><br>

</dd>
<dt><b>4.6.7</b> - <i>March 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.2.2 (SQLite version 3.35.2)</i><br>

</dd>
<dt><b>4.6.6</b> - <i>March 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.2.1 (SQLite version 3.35.1)</i><br>

</dd>
<dt><b>4.6.5</b> - <i>March 2021</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.2.0 (SQLite version 3.35.0)</i><br>
Enabled new SQLite Math Extension<br>
Fixed a memory leak in method wxSQLite3Database::GetTable<br>
Adjusted build files (DLL builds with MinGW/GCC used wrong DLL file extension)<br>

</dd>
<dt><b>4.6.4</b> - <i>December 2020</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.1.3</i><br>
Adjusted autotool build files to enable AES hardware support if available<br>

</dd>
<dt><b>4.6.3</b> - <i>December 2020</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.1.2</i><br>
Adjusted build files for MinGW<br>

</dd>
<dt><b>4.6.2</b> - <i>December 2020</i></dt>
<dd>
Upgrade to <i>SQLite3 Multiple Ciphers version 1.1.1</i><br>
Upgrade to <i>SQLite version 3.34.0</i><br>
Added method wxSQLite3Database::QueryTransactionState<br>

</dd>
<dt><b>4.6.1</b> - <i>October 2020</i></dt>
<dd>
Added SQLite VSV extension (Variably Separated Values)<br>

</dd>
<dt><b>4.6.0</b> - <i>August 2020</i></dt>
<dd>
Use SQLite encryption extension "SQLite3 Multiple Ciphers"<br>
Upgrade to SQLite version 3.33.0<br>
Added support for System.Data.SQLite's RC4 encryption<br>

</dd>
<dt><b>4.5.1</b> - <i>January 2020</i></dt>
<dd>
Upgrade to SQLite version 3.31.1<br>

</dd>
<dt><b>4.5.0</b> - <i>January 2020</i></dt>
<dd>
Upgrade to SQLite version 3.31.0<br>
Modified API for wxSQLite3Database::CreateFunction methods<br>

</dd>
<dt><b>4.4.8</b> - <i>October 2019</i></dt>
<dd>
Upgrade to SQLite version 3.30.1<br>
Adjusted encryption extension to support SQLite's shared cache mode<br>

</dd>
<dt><b>4.4.7</b> - <i>October 2019</i></dt>
<dd>
Upgrade to SQLite version 3.30.0<br>

</dd>
<dt><b>4.4.6</b> - <i>September 2019</i></dt>
<dd>
Fixed missing cipher application in method wxSQLite3Database::ReKey<br>

</dd>
<dt><b>4.4.5</b> - <i>August 2019</i></dt>
<dd>
Fixed broken compatibility with wxWidgets 2.8.12<br>

</dd>
<dt><b>4.4.4</b> - <i>August 2019</i></dt>
<dd>
Upgrade to SQLite version 3.29.0<br>
Added SQLite logging support<br>
Added build support for VS2019<br>
Added CMake support (PR #63)<br>
Updated build files to overcome problems with static builds (issue #73)<br>
Eliminated duplication of error messages for different wxWidgets builds (PR #64)<br>
Fixed missing call to progress callback in wxSQLite3Database::Restore (PR #66)<br>
Fixed issue #58 with silently failing wxSQLite3Transaction::Commit method<br>
Fixed issue with named collections which could result in crashes (PR #59)<br>

</dd>
<dt><b>4.4.3</b> - <i>May 2019</i></dt>
<dd>
Upgrade to SQLite version 3.28.0<br>

</dd>
<dt><b>4.4.2</b> - <i>February 2019</i></dt>
<dd>
Upgrade to SQLite version 3.27.2<br>

</dd>
<dt><b>4.4.1</b> - <i>February 2019</i></dt>
<dd>
Upgrade to SQLite version 3.27.1<br>

</dd>
<dt><b>4.4.0</b> - <i>December 2018</i></dt>
<dd>
Upgrade to SQLite version 3.26.0<br>
Added support for the SQLCipher 4 database format<br>

</dd>
<dt><b>4.3.0</b> - <i>November 2018</i></dt>
<dd>
Upgrade to SQLite version 3.25.3<br>
Adjusted encryption extension to support cipher configuration via database URI<br>

</dd>
<dt><b>4.2.0</b> - <i>October 2018</i></dt>
<dd>
Added method wxSQLite3Database::GetKeySalt to access the key salt of encrypted databases<br>
Fixed memory leaks in methods wxSQLite3ResultSet::GetExpandedSQL and wxSQLite3Statement::GetExpandedSQL<br>
Adjusted encryption extension to support raw key (and salt) for the <b>ChaCha20 (sqleet)</b> encryption scheme<br>

</dd>
<dt><b>4.1.1</b> - <i>October 2018</i></dt>
<dd>
Upgrade to SQLite version 3.25.2<br>

</dd>
<dt><b>4.1.0</b> - <i>September 2018</i></dt>
<dd>
Upgrade to SQLite version 3.25.1<br>
Added support for SQL window functions<br>
Adjusted encryption extension to check for matching page sizes on rekeying a database<br>

</dd>
<dt><b>4.0.4</b> - <i>June 2018</i></dt>
<dd>
Upgrade to SQLite version 3.24.0<br>

</dd>
<dt><b>4.0.3</b> - <i>April 2018</i></dt>
<dd>
Adjusted encryption extension to better support the SQLite backup API<br>

</dd>
<dt><b>4.0.2</b> - <i>April 2018</i></dt>
<dd>
Upgrade to SQLite version 3.23.1<br>

</dd>
<dt><b>4.0.1</b> - <i>April 2018</i></dt>
<dd>
Fixed a bug in the rekeying function of the encryption extension<br>

</dd>
<dt><b>4.0.0</b> - <i>April 2018</i></dt>
<dd>
Introduced multi-cipher support at runtime<br>
Added methods for attaching/detaching databases<br>
Cleaned up code using statement buffers<br>
Improved constness of methods<br>
Upgrade to SQLite version 3.23.0<br>

</dd>
<dt><b>3.5.9</b> - <i>January 2018</i></dt>
<dd>
Upgrade to SQLite version 3.22.0<br>

</dd>
<dt><b>3.5.8</b> - <i>November 2017</i></dt>
<dd>
Upgrade to SQLite version 3.21.0<br>

</dd>
<dt><b>3.5.7</b> - <i>September 2017</i></dt>
<dd>
Upgrade to SQLite version 3.20.1<br>

</dd>
<dt><b>3.5.6</b> - <i>August 2017</i></dt>
<dd>
Upgrade to SQLite version 3.20.0<br>
Added support for persistent prepared statements<br>
Added support for binding pointers (new SQLite pointer-binding interface)<br>
Added several SQLite extensions (csv, sha3, carray, fileio, series) for the included SQLite library<br>
Modified build files to expose the parameter SQLITE_MAX_ATTACHED to allow easier adjustment of the maximum number of attached databases<br>

</dd>
<dt><b>3.5.5</b> - <i>June 2017</i></dt>
<dd>
Upgrade to SQLite version 3.19.3<br>

</dd>
<dt><b>3.5.4</b> - <i>June 2017</i></dt>
<dd>
Upgrade to SQLite version 3.19.2<br>

</dd>
<dt><b>3.5.3</b> - <i>March 2017</i></dt>
<dd>
Upgrade to SQLite version 3.18.0<br>
Minor modification to wxsqlite3.pc.in to fix issue with pkgconfig tool<br>

</dd>
<dt><b>3.5.2</b> - <i>March 2017</i></dt>
<dd>
Upgrade to SQLite version 3.17.0<br>
Fixed minor issue in SQLite encryption extension related to symbol SQLITE_DEBUG<br>
Modified build system for GNU make (support monolithic wxWidgets build)<br>

</dd>
<dt><b>3.5.1</b> - <i>February 2017</i></dt>
<dd>
Added version information as Windows resource for DLL builds on Windows<br>
Cleaned up premake5 build files for Visual C++ (corrected debug environment settings)<br>
Resolved wxWidgets library dependencies for Visual C++ using wxWidgets' special setup.h for MSVC<br>

</dd>
<dt><b>3.5.0</b> - <i>January 2017</i></dt>
<dd>
Upgrade to SQLite version 3.16.2<br>
SQLite3 library now integrated part of wxSQLite3<br>
Build system overhauled<br>
Added Travis Continuous Integration<br>

</dd>
<dt><b>3.4.1</b> - <i>October 2016</i></dt>
<dd>
Upgrade to SQLite version 3.15.0<br>

</dd>
<dt><b>3.4.0</b> - <i>August 2016</i></dt>
<dd>
Upgrade to SQLite version 3.14.1<br>
Added method wxSQLite3Statement::GetExpandedSQL<br>
Added method wxSQLite3ResultSet::GetExpandedSQL<br>
Started to modify the build system to compile and statically link the SQLite3 library together with wxSQLite3<br>
Added the CSV extension module as part of the SQLite3 library with encryption extension<br>

</dd>
<dt><b>3.3.1</b> - <i>April 2016</i></dt>
<dd>
Upgrade to SQLite version 3.12.1<br>
Added method wxSQLite3Database::GetSystemErrorCode<br>

</dd>
<dt><b>3.3.0</b> - <i>December 2015</i></dt>
<dd>
Upgrade to SQLite version 3.9.2<br>
(SQLite amalgamation source adjusted to fix problem with user authentication module)<br>

</dd>
<dt><b>3.2.1</b> - <i>March 2015</i></dt>
<dd>
Upgrade to SQLite version 3.8.8.3<br>
Fixed a bug in method GetParamName<br>

</dd>
<dt><b>3.2.0</b> - <i>December 2014</i></dt>
<dd>
Upgrade to SQLite version 3.8.7.4<br>
Added support for the SQLite user authentication module<br>

</dd>
<dt><b>3.1.1</b> - <i>June 2014</i></dt>
<dd>
Upgrade to SQLite version 3.8.5<br>

</dd>
<dt><b>3.1.0</b> - <i>May 2014</i></dt>
<dd>
Upgrade to SQLite version 3.8.4.3<br>
Added flag <i>isDeterministic</i> to method wxSQLite3Database::CreateFunction<br>
Added new GUI sample<br>
Changed implementation of encryption extension (see Readme file in sqlite3 subfolder)<br>

</dd>
<dt><b>3.0.6</b> - <i>December 2013</i></dt>
<dd>
Upgrade to SQLite version 3.8.2<br>

</dd>
<dt><b>3.0.5</b> - <i>September 2013</i></dt>
<dd>
Upgrade to SQLite version 3.8.0.2<br>
Added support for setting the temporary directory for SQLite on Windows<br>

</dd>
<dt><b>3.0.4</b> - <i>August 2013</i></dt>
<dd>
Upgrade to SQLite version 3.8.0<br>
Added support for querying performance characteristics of prepared statements<br>


</dd>
<dt><b>3.0.3</b> - <i>March 2013</i></dt>
<dd>
Upgrade to SQLite version 3.7.16<br>


</dd>
<dt><b>3.0.2</b> - <i>December 2012</i></dt>
<dd>
Upgrade to SQLite version 3.7.15.1<br>
Corrected an internal SQLite data structure to avoid compile time warnings<br>
Changed method wxSQLite3Exception::ErrorCodeAsString to return the error messages provided by SQLite<br>


</dd>
<dt><b>3.0.1</b> - <i>November 2012</i></dt>
<dd>
Upgrade to SQLite version 3.7.14.1<br>
Cleaned up and optimized Finalize methods<br>
Modified wxSQLite3Database::Close to avoid potential memory leaks<br>
Added method wxSQLite3Database::GetWrapperVersion<br>
Added method wxSQLite3Database::IsReadOnly<br>
Added method wxSQLite3Statement::BindUnixDateTime<br>
Added method wxSQLite3ResultSet::GetUnixDateTime<br>
Added method wxSQLite3ResultSet::GetAutomaticDateTime<br>
Fixed a potential memory leak in method wxSQLite3Database::ExecuteUpdate<br>
Added a wxsqlite3.pc file on request of the Fedora Project developers<br>
Replaced assert by wxASSERT in wxSQLite3Transaction constructor<br>


</dd>
<dt><b>3.0.0</b> - <i>January 2012</i></dt>
<dd>
Upgrade to SQLite version 3.7.10<br>
Added method wxSQLite3Database::Vacuum<br>
Added method wxSQLite3Database::GetDatabaseFilename<br>
Added method wxSQLite3Database::ReleaseMemory<br>
Added method wxSQLite3ResultSet::CursorMoved<br>
Added method wxSQLite3Statement::IsBusy<br>
Fixed a bug in method operator= of wxSQLite3StringCollection
causing an endless recursion on assignment<br>
Dropped the concept of SQLite3 pointer ownership in favor of reference
counted pointers allowing much more flexible use of wxSQLite3 classes<br>
Modified SQLite3 encryption extension (defining int64 datatype
for SHA2 algorithm)<br>
Dropped dbadmin sample from build files<br>
Added Premake support for SQLite3 library with encryption support
and for wxSQLite3 (experimental)<br>

</dd>
<dt><b>2.1.3</b> - <i>August 2011</i></dt>
<dd>
Corrected default behavior for attached databases in case of
an encrypted main database. (Now the attached database uses the same
encryption key as the main database if no explicit key is given.
Previously the attached database remained unencrypted.)<br>
Added an optional progress callback for methods Backup and Restore<br>
Added method SetBackupRestorePageCount to set the number of pages
to be copied in one cycle of the backup/restore process<br>

</dd>
<dt><b>2.1.2</b> - <i>July 2011</i></dt>
<dd>
Upgrade to SQLite version 3.7.7.1<br>
Modified wxSQLite3Transaction to make it exception safe<br>

</dd>
<dt><b>2.1.1</b> - <i>April 2011</i></dt>
<dd>
Upgrade to SQLite version 3.7.6.1<br>
Added convenience method wxSQLite3Statement::ExecuteScalar<br>
Changed write-ahead log checkpoint method to new version (v2)<br>

</dd>
<dt><b>2.1.0</b> - <i>March 2011</i></dt>
<dd>
Upgrade to SQLite version 3.7.5<br>
Added wxSQLite+, a database administration application written by Fred Cailleau-Lepetit,
as a GUI sample for wxSQLite3. Minor adjustments were applied to make wxSQLite+
compatible with wxWidgets 2.9.x. Please note that wxSQLite+ is under GPL license.<br>

</dd>
<dt><b>2.0.2</b> - <i>December 2010</i></dt>
<dd>
Upgrade to SQLite version 3.7.4<br>
Added support for rebinding a BLOB object to a new row<br>
Added support for determining if an SQL statement writes the database<br>

</dd>
<dt><b>2.0.1</b> - <i>October 2010</i></dt>
<dd>
Upgrade to SQLite version 3.7.3<br>
Added parameter transferStatementOwnership to method wxSQLite3Statement::ExecuteQuery
to allow using the returned result set beyond the life time of the wxSQLite3Statement instance<br>
Eliminated the use of sqlite3_mprintf which caused linker problems when loading SQLite dynamically<br>

</dd>
<dt><b>2.0.0</b> - <i>July 2010</i></dt>
<dd>
Upgrade to SQLite version 3.7.0<br>
Fixed a bug in class wxSQLite3ResultSet<br>
Added support for SQLite's write-ahead log journal mode<br>
Added support for named collections (see class wxSQLite3NamedCollection)<br>
Changed UTF-8 string handling to use methods To/FromUTF8 of the wxString class (requires wxWidgets 2.8.4 or higher)<br>
Compatible with wxWidgets 2.9.1<br>

</dd>
<dt><b>1.9.9</b> - <i>March 2010</i></dt>
<dd>
Upgrade to SQLite version 3.6.23<br>
Fixed a bug when compiling for dynamic loading of SQLite<br>
Added static methods for accessing the run-time library compilation options diagnostics<br>
Added mathod FormatV to class wxSQLite3StatementBuffer<br>

</dd>
<dt><b>1.9.8</b> - <i>February 2010</i></dt>
<dd>
Upgrade to SQLite version 3.6.22<br>
Fixed a bug when compiling without pre-compiled header support
(by including wx/arrstr.h)<br>

</dd>
<dt><b>1.9.7</b> - <i>November 2009</i></dt>
<dd>
Upgrade to SQLite version 3.6.20<br>
Added methods to query, enable or disable foreign key support<br>

</dd>
<dt><b>1.9.6</b> - <i>September 2009</i></dt>
<dd>
Upgrade to SQLite version 3.6.18<br>
Added method to get the SQLite library source id<br>
Added flags parameter to wxSQLite3Database::Open to allow additional control over the database
connection (see http://www.sqlite.org/c3ref/open.html for further information)<br>
Fixed a potential memory leak in wxSQLite3Statement class<br>
Converted encryption extension from C++ to pure C to make it
compatible with the SQLite amalgamation.<br>

</dd>
<dt><b>1.9.5</b> - <i>February 2009</i></dt>
<dd>
Upgrade to SQLite version 3.6.11<br>
Added user defined function class for REGEXP operator.<br>
Added support for SQLite backup/restore API, introduced with SQLite 3.6.11<br>

</dd>
<dt><b>1.9.4</b> - <i>January 2009</i></dt>
<dd>
Upgrade to SQLite version 3.6.10<br>
Added support for savepoints, introduced with SQLite 3.6.8<br>
Added method IsOk to the classes wxSQLite3Statement, wxSQLite3Table and wxSQLite3ResultSet,
thus instances of these classes can be checked whether the associated SQLite database or
statement are valid without throwing an exception.<br>

</dd>
<dt><b>1.9.3</b> - <i>December 2008</i></dt>
<dd>
Upgrade to SQLite version 3.6.7<br>
Fixed a bug in method wxSQLite3Table::GetDouble
(conversion from string to double failed in non-US locales)<br>
Build system upgraded using Bakefile 0.2.5<br>

</dd>
<dt><b>1.9.2</b> - <i>November 2008</i></dt>
<dd>
Upgrade to SQLite version 3.6.6<br>
Added RAII transaction class (see docs for details)<br>

</dd>
<dt><b>1.9.1</b> - <i>September 2008</i></dt>
<dd>
Upgrade to SQLite version 3.6.2<br>
Introduced own step counting for aggregate user functions
since the sqlite3_aggregate_count function is now deprecated<br>
Enhanced wxSQLite3Database::TableExists method to query an attached database
for existence of a table or to query the main database and all attached databases<br>

</dd>
<dt><b>1.9.0</b> - <i>July 2008</i></dt>
<dd>
Upgrade to SQLite version 3.6.0<br>
The optional key based encryption support has been adapted to
support SQLite version 3.6.0.<br>
Added static methods to initialize and shutdown the SQLite library.<br>
Changed build system to support static library build against shared
wxWidgets build on Linux.<br>
Changed behaviour of wxSQLite3Database::Close method to finalize
all not-finalized prepared statements.

</dd>
<dt><b>1.8.5</b> - <i>June 2008</i></dt>
<dd>
Upgrade to SQLite version 3.5.9<br>
Integration of the optional key based encryption support into SQLite
has been made easier. Changes to original SQLite source files
are no longer necessary.

</dd>
<dt><b>1.8.4</b> - <i>April 2008</i></dt>
<dd>
Upgrade to SQLite version 3.5.8<br>
Added support for accessing database limits<br>
Changed method TableExists to check a table name case insensitive<br>
Fixed several minor issues in the build files.

</dd>
<dt><b>1.8.3</b> - <i>January 2008</i></dt>
<dd>
Added support for shared cache mode<br>
Added support for access to original SQL statement
for prepared statements (requires SQLite 3.5.3 or above)

</dd>
<dt><b>1.8.2</b> - <i>December 2007</i></dt>
<dd>
Upgrade to SQLite version 3.5.4<br>
Fixed a bug in wxSQLite3Database::Begin (wrong transaction type)

</dd>
<dt><b>1.8.1</b> - <i>November 2007</i></dt>
<dd>
Fixed a bug in in wxSQLite3Database::Close (resetting flag m_isEncrypted)<br>
Eliminated several compile time warnings (regarding unused parameters)<br>
Fixed a compile time bug in wxSQLite3Database::GetBlob (missing explicit type cast)

</dd>
<dt><b>1.8.0</b> - <i>November 2007</i></dt>
<dd>
Upgrade to SQLite version 3.5.2<br>
Support for SQLite incremental BLOBs<br>
 Changed source code in the SQLite3 encryption extension to eliminate several warnings<br>
Changed default wxWidgets version to 2.8.x<br>
Adjusted sources for SQLite encryption support are included for all SQLite version from 3.3.1 up to 3.5.2<br>
SQLite link libraries for MinGW on Windows are included<br>
Added <code>WXMAKINGLIB_WXSQLITE3</code> compile time option
to support building wxSQLite3 as a static library while
using the shared libraries of wxWidgets.

</dd>
<dt><b>1.7.3</b> - <i>May 2007</i></dt>
<dd>
Upgrade to SQLite version 3.3.17<br>

Fixed a bug in the SQLite3 encryption extension
(MD5 algorithm was not aware of endianess on
big-endian platforms, resulting in non-portable
database files)

</dd>
<dt><b>1.7.2</b> - <i>February 2007</i></dt>
<dd>
Upgrade to SQLite version 3.3.12<br>
Support for loadable extensions is now optional
Check for optional wxSQLite3 features at runtime
wxSQLite3 API independent of optional features

</dd>
<dt><b>1.7.1</b> - <i>January 2007</i></dt>
<dd>
Fixed a bug in the key based database encryption feature
(The call to <b>sqlite3_rekey</b> in wxSQLite3Database::ReKey
could cause a program crash, when used to encrypt a previously
unencrypted database.)<br>

</dd>
<dt><b>1.7.0</b> - <i>January 2007</i></dt>
<dd>
Upgrade to SQLite version 3.3.10 (<b>Attention</b>: at least SQLite version 3.3.9 is required)<br>
Added support for BLOBs as wxMemoryBuffer objects<br>
Added support for loadable extensions<br>
Optional support for key based database encryption

</dd>
<dt><b>1.6.0</b> - <i>July 2006</i></dt>
<dd>
Added support for user defined collation sequences

</dd>
<dt><b>1.5.3</b> - <i>June 2006</i></dt>
<dd>
Upgrade to SQLite version 3.3.6<br>
Added support for optional SQLite meta data methods

</dd>
<dt><b>1.5.2</b> - <i>March 2006</i></dt>
<dd>
Fixed a bug in wxSQLite3Database::Prepare<br>
Added wxSQLite3Database::IsOpen for convenience

</dd>
<dt><b>1.5.1</b> - <i>February 2006</i></dt>
<dd>
Upgrade to SQLite version 3.3.4 (wxMSW only)

</dd>
<dt><b>1.5</b> - <i>February 2006</i></dt>
<dd>
Upgrade to SQLite version 3.3.3<br>
Added support for commit, rollback and update callbacks

</dd>
<dt><b>1.4.2</b> - <i>November 2005</i></dt>
<dd>
Optimized code for wxString arguments

</dd>
<dt><b>1.4.1</b> - <i>November 2005</i></dt>
<dd>
Fixed a bug in wxSQLite3Database::TableExists,<br>
Changed the handling of Unicode string conversion,<br>
Added support for different transaction types

</dd>
<dt><b>1.4</b> - <i>November 2005</i></dt>
<dd>
Optionally load the SQLite library dynamically at run time.

</dd>
<dt><b>1.3.1</b> - <i>November 2005</i></dt>
<dd>
Corrected wxSQLite3ResultSet::GetInt64.<br>
Added wxSQLite3Table::GetInt64

</dd>
<dt><b>1.3</b> - <i>October 2005</i></dt>
<dd>
Added wxGTK build support<br>

</dd>
<dt><b>1.2</b> - <i>October 2005</i></dt>
<dd>
Corrected error in wxSQLite3Table::FindColumnIndex<br>

</dd>
<dt><b>1.1</b> - <i>October 2005</i></dt>
<dd>
Upgrade to SQLite version 3.2.7 <br>

</dd>

<dt><b>1.0</b> - <i>July 2005</i></dt>
<dd>
First public release
</dd>
</dl>

\author Ulrich Telle (ulrich DOT telle AT gmx DOT de)

\section ackn Acknowledgments

Kudos to <b>Fred Cailleau-Lepetit</b> for developing <b>wxSQLite+</b> as a sample demonstrating
the wxWidgets components <b>wxAUI</b> and <b>wxSQLite3</b> and for allowing it to be included
in the wxSQLite3 distribution.

The following people have contributed to wxSQLite3:

<ul>
<li>Francesco Montorsi (enhancement of the build system)</li>
<li>Neville Dastur (enhancement of the method TableExists)</li>
<li>Tobias Langner (RAII class for managing transactions)</li>
<li>Deamhan (CMake support and various bug fixes)</li>
</ul>

 */

#ifndef WX_SQLITE3_DEF_H_
#define WX_SQLITE3_DEF_H_

#if defined(WXMAKINGLIB_WXSQLITE3)
  #define WXDLLIMPEXP_SQLITE3
#elif defined(WXMAKINGDLL_WXSQLITE3)
  #define WXDLLIMPEXP_SQLITE3 WXEXPORT
#elif defined(WXUSINGDLL_WXSQLITE3)
  #define WXDLLIMPEXP_SQLITE3 WXIMPORT
#else // not making nor using DLL
  #define WXDLLIMPEXP_SQLITE3
#endif

/*
  GCC warns about using __declspec on forward declarations
  while MSVC complains about forward declarations without
  __declspec for the classes later declared with it. To hide this
  difference a separate macro for forward declarations is defined:
 */
#if defined(HAVE_VISIBILITY) || (defined(__WINDOWS__) && defined(__GNUC__))
  #define WXDLLIMPEXP_FWD_SQLITE3
#else
  #define WXDLLIMPEXP_FWD_SQLITE3 WXDLLIMPEXP_SQLITE3
#endif

#endif // WX_SQLITE3_DEF_H_

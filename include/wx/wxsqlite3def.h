  /*
** Name:        wxsqlite3def.h
** Purpose:     wxWidgets wrapper around the SQLite3 embedded database library.
** Author:      Ulrich Telle
** Created:     2005-07-14
** Copyright:   (c) 2005-2026 Ulrich Telle
** License:     LGPL-3.0+ WITH WxWindows-exception-3.1
*/

/// \file wxsqlite3def.h Compile time switches for the wxSQLite3 class

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

/** \mainpage wxSQLite3

\section intro What is wxSQLite3?

  \b wxSQLite3 is a C++ wrapper around the public domain <a href="http://www.sqlite.org">SQLite 3.x</a> database
  and is specifically designed for use in programs based on the \b wxWidgets library.

  Several solutions exist to access SQLite databases. To name just a few:

  - <a href="https://sourceforge.net/projects/wxsqlite">wxSQLite</a> :
    This is a wxWidgets wrapper for version 2.8.x of SQLite.
    SQLite version 3.x has a lot more features - which are not supported by this wrapper.

  - <a href="https://github.com/mtangoo/wxDatabase">wxDatabase</a> :
    This is a database abstraction providing a JDBC-like interface to database I/O.
    SQLite3, PostgreSQL, MySQL, and ODBC database backends are supported.

  - <a href="https://github.com/iwongu/sqlite3pp">sqlite3pp</a> :
    Not wxWidgets specific, but based on modern C++ concepts.

  - <a href="https://github.com/SRombauts/SQLiteCpp">SQLiteC++</a> :
    Not wxWidgets specific, a smart and easy to use C++ SQLite3 wrapper.

  The component \b wxSQLite3 was inspired by various SQLite wrappers, among them the ones mentioned above.
  \b wxSQLite3 does not try to hide the underlying database, in contrary almost all special features
  of **SQLite version 3.x** are supported, like for example the creation of user defined
  scalar or aggregate functions.

  Since SQLite stores strings in UTF-8 encoding, the wxSQLite3 methods provide automatic conversion
  between wxStrings and UTF-8 strings. The methods ToUTF8 and FromUTF8 of the wxString class (available
  since wxWidgets 2.8.4) are used for the conversion. Special care has to be taken if external administration
  tools are used to modify the database contents, since not all of these tools operate in Unicode or UTF-8 mode.

\note With the release of SQLite version 3.32.0 on May 22, 2020 critical changes to the public SQLite code finally took officially effect, although they weren't officially announced. They were introduced on Feb 7, 2020: ["Simplify the code by removing the unsupported and undocumented SQLITE_HAS_CODEC compile-time option"](https://www.sqlite.org/src/timeline?c=5a877221ce90e752). Since August 2020 a new implementation of an encryption extension, capable of supporting SQLite version 3.32.0 and later, is available as a separate project, [**SQLite3 Multiple Ciphers**](https://github.com/utelle/SQLite3MultipleCiphers). Starting with the release of **wxSQLite3 4.6.0** this new implementation was and is used.

\par

\note **wxSQLite3 5.x** is a major update with a modernized C++ API. It is not fully source-compatible with **wxSQLite3 4.x**. Therefore, **wxSQLite3 4.x** will receive maintenance updates, including updates to the bundled SQLite version, for a limited period following the release of 5.0.0. No new API features will be added. The **End-of-Life** date of version **4.x** will be announced separately.

\note The section \ref migration details the steps required to migrate from prior _wxSQLite3_ versions. The section \ref features presents the new features.

\section version Current Version

<dl>

<dt><b>5.0.0</b> - <i>August 2026</i></dt>
<dd>
First release in the **5.x** series with a modernized C++ interface, based on [SQLite3 Multiple Ciphers](https://github.com/utelle/SQLite3MultipleCiphers) version 2.5.0 ([SQLite version 3.53.4](https://sqlite.org/releaselog/3_53_4.html))

</dd>
</dl>

For further version information please consult the [CHANGELOG](https://github.com/utelle/wxsqlite3/blob/main/CHANGELOG.md).

\author Ulrich Telle (github DOT telle MINUS online DOT de)

\section ackn Acknowledgments

The following people have contributed to wxSQLite3:

<ul>
<li>Francesco Montorsi (enhancement of the build system)</li>
<li>Neville Dastur (enhancement of the method TableExists)</li>
<li>Tobias Langner (RAII class for managing transactions)</li>
<li>Deamhan (CMake support and various bug fixes)</li>
</ul>

 */

/** \page history Version History

<dl>

<dt><b>5.0.0</b> - <i>August 2026</i></dt>
<dd>
First release in the **5.x** series, based on [SQLite3 Multiple Ciphers](https://github.com/utelle/SQLite3MultipleCiphers) version 2.5.0 ([SQLite version 3.53.4](https://sqlite.org/releaselog/3_53_4.html))</i>
</dd>

</dl>

*/

/** \page migration Migration Guide

This guide describes the source-level changes required when migrating existing applications from the previous wxSQLite3 API (_version 4.x_) to the modernized API.

The migration is primarily a matter of adapting class names and enumerations to the new C++ namespace and scoped-enumeration conventions. The underlying database API and its concepts remain largely unchanged.

## 1. Class names and the `wxSQLite3` namespace

All _wxSQLite3_ classes are now contained in the `wxSQLite3` namespace.

In previous versions, the namespace was effectively encoded in the class names using the `wxSQLite3` prefix. The prefix has been replaced by the namespace qualifier.

For example:

```cpp
wxSQLite3Database db;
wxSQLite3Statement stmt;
wxSQLite3ResultSet resultSet;
```

becomes:

```cpp
wxSQLite3::Database db;
wxSQLite3::Statement stmt;
wxSQLite3::ResultSet resultSet;
```

This change applies consistently to the wxSQLite3 classes.

Consequently, in most existing source code the required change is simply to replace the `wxSQLite3` class-name prefix with `wxSQLite3::`.

For applications that use many _wxSQLite3_ classes, a namespace declaration can optionally be used to reduce the amount of qualification:

```cpp
using namespace wxSQLite3;
```

or, preferably when only selected types are required:

```cpp
using wxSQLite3::Database;
using wxSQLite3::Statement;
using wxSQLite3::ResultSet;
```

Using the namespace explicitly is generally recommended in headers and in code where avoiding name ambiguity is important.

## 2. Enumerations are now scoped enumerations

The _wxSQLite3_ API now consistently uses C++11 scoped enumerations (`enum class`) instead of unscoped enumerations.

As a consequence, enumeration values must normally be qualified with the corresponding enumeration type.

For example, code using an unscoped enumeration such as:

```cpp
db.SetJournalMode(WXSQLITE_JOURNALMODE_WAL);
```

must now use the scoped enumeration value:

```cpp
db.SetJournalMode(wxSQLite3::JournalMode::JOURNALMODE_WAL);
```

The exact enumeration type and value names depend on the API being used.

### Renamed enumeration values

Enumeration values have also been renamed to make them more concise and consistent.

Prefixes that were previously required to distinguish enumeration values in the global namespace have been removed. For example, prefixes such as `WXSQLITE_` are no longer part of the enumeration value names.

Similarly, values that previously used names such as `SQLITE_...` have been adapted to the new scoped-enumeration naming convention.

Therefore, migration of enumeration values generally requires two changes:

1. Add the enumeration type as a qualifier.
2. Adapt the enumeration value name to its new, shorter form.

For example:

```cpp
old_enum_value
```

becomes conceptually:

```cpp
EnumType::NewValue
```

The API documentation lists the current enumeration types and their available values.

Because enumeration values are now scoped, they no longer implicitly convert to integers. Code that relied on such implicit conversions may therefore require an explicit conversion, for example:

```cpp
const int value = static_cast<int>(enumValue);
```

Where possible, however, it is preferable to keep values as their enumeration type rather than converting them to integers.

### Tables with renaming rules

The following table shows the renaming rules for enumeration types:

<table border="0" cellpadding="5px">
<tr bgcolor="#77aaee">
  <td style="color:#000000"><b>Type name: Old <b>&rArr;</b> New</b></td>
  <td style="color:#000000"><b>Value: Old <b>&rArr;</b> New</b></td>
</tr>
<tr bgcolor="#eeeeee">
  <td style="color:#000000">wxSQLite3CipherType<br/>&emsp;<b>&rArr;</b> wxSQLite3::CipherType</td>
  <td style="color:#000000">WXSQLITE_CIPHER_\*<br/>&emsp;<b>&rArr;</b> CipherType::\*</td>
</tr>
<tr bgcolor="#ddeeff">
  <td style="color:#000000">wxSQLite3TransactionType<br/>&emsp;<b>&rArr;</b> wxSQLite3::TransactionType</td>
  <td style="color:#000000">WXSQLITE_TRANSACTION_\*<br/>&emsp;<b>&rArr;</b> TransactionType::TRANSACTION_\*</td>
</tr>
<tr bgcolor="#eeeeee">
  <td style="color:#000000">wxSQLite3TransactionState<br/>&emsp;<b>&rArr;</b> wxSQLite3::TransactionState</td>
  <td style="color:#000000">WXSQLITE_TRANSACTION_\*<br/>&emsp;<b>&rArr;</b> TransactionState::TRANSACTION_\*</td>
</tr>
<tr bgcolor="#ddeeff">
  <td style="color:#000000">wxSQLite3LimitType<br/>&emsp;<b>&rArr;</b> wxSQLite3::LimitType</td>
  <td style="color:#000000">WXSQLITE_LIMIT_\*<br/>&emsp;<b>&rArr;</b> LimitType::LIMIT_\*</td>
</tr>
<tr bgcolor="#eeeeee">
  <td style="color:#000000">wxSQLite3JournalMode<br/>&emsp;<b>&rArr;</b> wxSQLite3::JournalMode</td>
  <td style="color:#000000">WXSQLITE_JOURNALMODE_\*<br/>&emsp;<b>&rArr;</b> JournalMode::JOURNALMODE_\*</td>
</tr>
<tr bgcolor="#ddeeff">
  <td style="color:#000000">wxSQLite3StatementStatus<br/>&emsp;<b>&rArr;</b> wxSQLite3::StatementStatus</td>
  <td style="color:#000000">WXSQLITE_STMTSTATUS_\*<br/>&emsp;<b>&rArr;</b> StatementStatus::STMTSTATUS_\*</td>
</tr>
<tr bgcolor="#eeeeee">
  <td style="color:#000000">wxSQLite3DbConfig<br/>&emsp;<b>&rArr;</b> wxSQLite3::DbConfig</td>
  <td style="color:#000000">WXSQLITE_DBCONFIG_\*<br/>&emsp;<b>&rArr;</b> DbConfig::DBCONFIG\_\*</td>
</tr>

<tr bgcolor="#ddeeff">
  <td style="color:#000000">wxSQLite3Authorizer::wxAuthorizationCode<br/>&emsp;<b>&rArr;</b> wxSQLite3::AuthorizationCode</td>
  <td style="color:#000000">SQLITE\_\*<br/>&emsp;<b>&rArr;</b> AuthorizationCode::AUTH\_\*</td>
</tr>
<tr bgcolor="#eeeeee">
  <td style="color:#000000">wxSQLite3Hook::wxUpdateType<br/>&emsp;<b>&rArr;</b> wxSQLite3::AuthorizationCode</td>
  <td style="color:#000000">SQLITE\_\*<br/>&emsp;<b>&rArr;</b> AuthorizationCode::AUTH\_\*</td>
</tr>
</table>

Many symbols were defined via preprocessor symbols using the `#define` preprocessor statements. These symbols were mostly replaced by `constexpr int` expressions. In that course symbol names were shortened by removing prefixes like `WXSQLITE` or `SQLITE`.  The following table shows the renaming rules for those symbols:

<table border="0" cellpadding="5px">
<tr bgcolor="#77aaee">
  <td style="color:#000000"><b>Description</b></td>
  <td style="color:#000000"><b>Symbol: Old</b></td>
  <td style="color:#000000"><b>&rArr; New</b></td>
</tr>
<tr bgcolor="#eeeeee">
  <td style="color:#000000">Result codes</td>
  <td style="color:#000000">SQLITE\_\*</td>
  <td style="color:#000000">&emsp;<b>&rArr;</b> wxSQLite3::RC\_\*</td>
</tr>
<tr bgcolor="#ddeeff">
  <td style="color:#000000">Data types</td>
  <td style="color:#000000">SQLITE\_REAL</td>
  <td style="color:#000000">&emsp;<b>&rArr;</b> wxSQLite3::TYPE\_REAL</td>
</tr>

<tr bgcolor="#eeeeee">
  <td style="color:#000000">Open flags</td>
  <td style="color:#000000">WXSQLITE\_OPEN\_\*</td>
  <td style="color:#000000">&emsp;<b>&rArr;</b> wxSQLite3::OPEN\_\*</td>
</tr>
<tr bgcolor="#ddeeff">
  <td style="color:#000000">Checkpoint flags</td>
  <td style="color:#000000">WXSQLITE\_CHECKPOINT\_\*</td>
  <td style="color:#000000">&emsp;<b>&rArr;</b> wxSQLite3::CHECKPOINT\_\*</td>
</tr>
<tr bgcolor="#eeeeee">
  <td style="color:#000000">Function flags</td>
  <td style="color:#000000">WXSQLITE\_\*</td>
  <td style="color:#000000">&emsp;<b>&rArr;</b> wxSQLite3::FUNC\_\*</td>
</tr>
</table>

## 3. Modern C++ features

Apart from the namespace and enumeration changes, the existing wxSQLite3 API remains largely compatible. The modernized API adds several optional ways of working with result sets and prepared statements.

These additions do not require existing code to be rewritten.

### Template-based value access

Values can be retrieved from a result set using template-based `Get<T>()` methods. These methods use `std::optional<T>` to represent SQL `NULL` values.

For example:

```cpp
const auto id = resultSet.Get<int>(0);
```

An empty `std::optional` indicates that the database value is SQL `NULL`.

### Template-based parameter binding

Prepared-statement parameters can similarly be bound using the template-based `Bind()` methods. `std::optional<T>` can be used to bind either a value or SQL `NULL`.

```cpp
auto id = std::optional<int>(4711);
auto name = std::optional<wxString>(std::nullopt);
stmt.Bind(1, id);
stmt.Bind(2, name);
```

The existing type-specific methods remain available, so this is an optional modernization rather than a required migration step.

### Tuple-based access and binding

`GetTuple()` and `BindTuple()` provide a convenient way to retrieve or bind several values as a group.

Both methods are available in two forms:

* using consecutive column or parameter indices;
* using an array of explicitly specified indices.

These methods are also optional and can be introduced incrementally into existing code.

### Iterator and range-based result-set processing

`wxSQLite3::ResultSet` can now be used with standard C++ iterators and range-based `for` loops.

Existing cursor-based code such as:

```cpp
while (resultSet.NextRow())
{
    // Process row
}
```

can therefore be written as:

```cpp
for (const auto& row : resultSet)
{
    // Process row
}
```

The traditional cursor-based interface remains available, so existing result-set processing does not have to be changed as part of the migration.

## Summary

For most applications, migration consists primarily of:

1. Replacing the old `wxSQLite3ClassName` class names with `wxSQLite3::ClassName`.
2. Qualifying enumeration values with their `enum class` type.
3. Updating enumeration value names to their new, shorter names.
4. Optionally adopting the new template-based, tuple-based, and iterator/range-based interfaces.

The first two changes are source-level compatibility changes. The modern C++ features are additions to the API and therefore do not require changes to existing code.

*/


/** \page features Modern C++ Interface

wxSQLite3 provides a number of convenience features that make working with SQLite result sets and prepared statements more natural in modern C++ code. These features complement the traditional cursor-based interface and the existing type-specific methods.

## Type-aware access to result-set values

In addition to the existing type-specific methods for retrieving values from a result set, wxSQLite3 provides a template-based `Get<T>()` method. The method returns a `std::optional<T>`, making the distinction between an SQL `NULL` value and a value of the requested C++ type explicit.

For example:

```cpp
const std::optional<int> id = resultSet.Get<int>(0);
const std::optional<wxString> name = resultSet.Get<wxString>(1);

if (id)
{
    // The column contains a non-NULL integer value.
}
```

If the corresponding SQLite value is `NULL`, the returned `std::optional` is empty. Otherwise, it contains the value converted to the requested C++ type.

The template-based interface is implemented in terms of the existing type-specific result-set methods. It therefore provides a convenient and type-oriented interface without introducing a separate value-conversion mechanism.

## Type-aware binding of statement parameters

Prepared-statement parameters can likewise be bound using the template-based `Bind<T>()` interface. The method accepts a `std::optional<T>`, allowing an SQL `NULL` value to be represented naturally by an empty `std::optional`.

For example:

```cpp
std::optional<int> id = ...;
std::optional<wxString> name = ...;

stmt.Bind(1, id);
stmt.Bind(2, name);
```

An engaged `std::optional` binds its contained value, while an empty `std::optional` binds an SQL `NULL`.

As with `Get<T>()`, the template-based binding methods use the existing type-specific binding methods internally.

This makes `std::optional` a convenient way to handle nullable database values without having to treat SQL `NULL` as a special case in application code.

## Binding and retrieving tuples of values

For situations where several values need to be bound to a prepared statement or retrieved from a result set, wxSQLite3 also provides `BindTuple()` and `GetTuple()`.

The first variant uses consecutive parameter or column indices. The values are therefore associated with indices starting at the specified first index.

For example:

```cpp
const auto values = resultSet.GetTuple<int, wxString, double>(0);
```

retrieves three values from consecutive columns.

Similarly, values can be bound to consecutive parameters:

```cpp
stmt.BindTuple(1, id, name, amount);
```

The tuple-based methods use the same type-aware conversion and `std::optional` handling as the individual `Get<T>()` and `Bind()` methods. Consequently, nullable database values can be represented directly in the resulting or supplied tuple.

A second variant of `GetTuple()` and `BindTuple()` accepts an array of indices. This allows the values to be associated with arbitrary, non-consecutive columns or parameters.

For example:

```cpp
constexpr std::array<int, 3> columns{0, 3, 7};

const auto values =
    resultSet.GetTuple<int, wxString, double>(columns);
```

This is useful when the values of interest are distributed across a result set and their positions do not form a consecutive sequence.

The corresponding binding operation can use an index array in the same way:

```cpp
constexpr std::array<int, 3> parameters{1, 4, 6};

stmt.BindTuple(parameters, id, name, amount);
```

The tuple-based interface is particularly useful when several database values correspond directly to members or values of a C++ data structure and should be handled as a group.

## Range-based result-set processing

Traditionally, a `wxSQLite3ResultSet` is processed using its cursor-oriented interface:

```cpp
while (resultSet.NextRow())
{
    const auto id = resultSet.Get<int>(0);
    const auto name = resultSet.Get<wxString>(1);

    // Process row
}
```

For applications using modern C++ features, a result set can also be processed with a range-based `for` loop:

```cpp
for (const auto& row : resultSet)
{
    const auto id = row.Get<int>(0);
    const auto name = row.Get<wxString>(1);

    // Process row
}
```

This provides a concise and familiar way to iterate over all rows of a result set.

The iterator interface can also be used directly when more control over the iteration is required:

```cpp
for (auto it = resultSet.begin(); it != resultSet.end(); ++it)
{
    const auto& row = *it;

    // Process row
}
```

The iterator and range-based interfaces are alternatives to the traditional `NextRow()` loop. They do not change the underlying SQLite result-set processing model; they provide an additional interface that integrates with the standard C++ iteration mechanisms.

## Combining the features

The individual template methods, tuple operations, and range-based result-set processing can be combined to write concise and type-oriented database code.

For example:

```cpp
for (const auto& row : resultSet)
{
    const auto values =
        row.GetTuple<int, wxString, double>({0, 2, 5});

    // Process values
}
```

The tuple returned by `GetTuple()` contains `std::optional` values, so SQL `NULL` values remain distinguishable from actual C++ values.

These additions are intended to complement rather than replace the established wxSQLite3 API. Existing applications can continue to use the traditional cursor-based and type-specific methods without modification.

*/

#endif // WX_SQLITE3_DEF_H_

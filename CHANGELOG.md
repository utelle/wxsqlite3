# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [5.0.1] - 2026-08-13

- Enhance template `Get` and `Bind` methods to handle integral types in general (like `int8_t`, `uint16`, `enum` and so on)
- Enhance template `Bind` methods to handle direct types instead of `std::optional` only
- Add `class` attribute to `enum` enumerations where it was still missing
- Adjust minimal sample

## [5.0.0] - 2026-08-12

- First release of modernized C++ interface
- Upgrade to SQLite3 Multiple Ciphers version 2.5.0 (SQLite version 3.53.4)

### Overview

wxSQLite3 5.0 is a major update with a modernized C++ API. It is not fully source-compatible with wxSQLite3 4.x.

See [Migrating from 4.x to 5.x](https://utelle.github.io/wxsqlite3/docs/5.x/migration.html) for details.

See [Modern C++ Interface](https://utelle.github.io/wxsqlite3/docs/5.x/features.html) for details.

### Breaking changes

- Requires at least a C++11 compiler
- The added modern API methods require C++17 (omitted, if the compiler does not support C++17)
- Introduces namespace `wxSQLite3` (instead of name prefix `wxSQLite3` in class names)  
  Example: `wxSQLite3Datebase` becomes `wxSQLite3::Database`.
- Replaces reference-counted reference classes for databases, prepared statements, and blobs by handle classes managed by `shared_ptr`s
- Uses `enum class` instead of just `enum`  
  Most symbol names shortened by removing prefixes like `WXSQLITE_`
- Uses `constexpr` instead of `#define` for various symbols
- Uses `using` instead of `typedef`
- Uses `nullptr` instead of `NULL` symbol
- Derives exception class from `std::runtime_error`
- Removes methods for accessing the user authentication extension. The extension was officially deprecated by the SQLite developer team.

## Prior versions

See [Change Log 4.x](https://github.com/utelle/wxsqlite3/blob/4.x/CHANGELOG.md)

[Unreleased]: ../../compare/v5.0.1...HEAD
[5.0.1]: ../../compare/v5.0.0...v5.0.1
[5.0.0]:

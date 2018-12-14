# wxSQLite3 encryption extension for SQLite3

This document describes the SQLite3 encryption extension provided by wxSQLite3. The document is work in progress and still incomplete.

## Table of contents

- [Installation](#installation)
  - [wxMSW](#wxmsw)
  - [wxGTK](#wxgtk)
- [Supported ciphers](#ciphers)
  - [wxSQLite3: AES 128 Bit CBC - No HMAC](#cipher_aes128cbc)
  - [wxSQLite3: AES 256 Bit CBC - No HMAC](#cipher_aes256cbc)
  - [sqleet: ChaCha20 - Poly1305 HMAC](#cipher_chacha20)
  - [SQLCipher: AES 256 Bit CBC - SHA1/SHA256/SHA512 HMAC](#cipher_sqlcipher)
- [Legacy cipher modes](#legacy)
- [Encryption API](#encryptionapi)
  - [Overview](#encryption_overview)
  - [`sqlite3_key()` and `sqlite3_key_v2()`](#encryption_key)
  - [`sqlite3_rekey()` and `sqlite3_rekey_v2()`](#encryption_rekey)
  - [`wxsqlite3_config()`](#encryption_config)
  - [`wxsqlite3_config_cipher()`](#encryption_config_cipher)
  - [`wxsqlite3_codec_data()`](#encryption_codec_data)
  - [SQL interface](#encryption_sql)
  - [URI parameters](#encryption_uri)
- [SQLite3 Backup API](#backupapi)

## <a name="installation" />Installation

The build system is based on [Premake5](http://premake.github.io/). Premake 5.0-alpha11 or higher is recommended.

Ready to use project files are provided for Visual C++ 2010, 2012, 2013, 2015, and 2017. Additionally, GNU Makefiles are provided supporting for example TDM-GCC MinGW.

For Visual Studio 2010+ solutions it is possible to customize the build by creating a `wx_local.props` file in the build directory which is used, if it exists, by the projects. The settings in that file override the default values for the properties. The typical way to make the file is to copy `wx_setup.props` to `wx_local.props` and then edit locally.

For GNU Makefiles the file `config.gcc` serves the same purpose as the file wx_setup.props for Visual C++ projects.

The customization files `wx_setup.props` resp. `config.gcc` allow to customize certain settings like for example the version number and the root directory of the wxWidgets library.

### <a name="wxmsw" />wxMSW

When building on Win32 or Win64, you can use the makefiles or one of the Microsoft Visual Studio solution files in the `build` folder.

For Visual C++ the debugging properties are set up in such a way that debugging the sample applications should work right out of the box. For release builds you may need to copy the wxSQLite3 DLL or add the `lib` folder path to the Windows search path (PATH environment variable).

The SQLite3 library is now compiled as an integrated part of wxSQLite3. The advantage is that SQLite3 and wxSQLite3 are always compiled with matching configuration options. Additionally, the SQLite3 encryption extension is automatically enabled, too.

A precompiled SQLite shell program supporting encrypted databases is provided as a separate download. Use
```
PRAGMA KEY="encryption key";
```
to create or open an encrypted database. Use
```
ATTACH DATABASE x AS y KEY z;
```
to attach an encrypted database.

### <a name="wxgtk" />wxGTK

When building on an autoconf-based system (like Linux/GNU-based systems), the first setup is to recreate the configure script doing:

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

The autoconf-based system also supports a `make install` target which builds the library and then copies the headers of the component to `/usr/local/include` and the lib to `/usr/local/lib`.

## <a name="ciphers" />Supported ciphers

The following ciphers are currently supported by **wxSQLite3**:

- [AES 128 Bit CBC - No HMAC (wxSQLite3)](#cipher_aes128cbc)
- [AES 256 Bit CBC - No HMAC (wxSQLite3)](#cipher_aes256cbc)
- [ChaCha20 - Poly1305 HMAC (sqleet)](#cipher_chacha20)
- [AES 256 Bit CBC - SHA1/SHA256/SHA512 HMAC (SQLCipher)](#cipher_sqlcipher)

Definition of abbreviations:

- AES = Advanced Encryption Standard (Rijndael algorithm)
- CBC = Cipher Block Chaining mode
- HMAC = Hash Message Authentication Code
- ChaCha20 = symmetric stream cipher developed by Daniel J. Bernstein
- Poly1305 = cryptographic message authentication code (MAC) developed by Daniel J. Bernstein
- SHA1 = Secure Hash Algorithm 1
- SHA256 = Secure Hash Algorithm 2 (256 bit hash)
- SHA512 = Secure Hash Algorithm 2 (512 bit hash)

### <a name="cipher_aes128cbc"/>wxSQLite3: AES 128 Bit CBC - No HMAC

This cipher was added to **wxSQLite3** in 2007 as the first supported encryption scheme. It is a 128 bit AES encryption in CBC mode.

The encryption key is derived from the passphrase according to the algorithm described in the PDF specification (using the MD5 hash function and the RC4 algorithm).

The initial vector for the encryption of each database page is derived from the page number.

The cipher does not use a HMAC, and requires therefore no reserved bytes per database page.

The following table lists all parameters related to this cipher that can be set before activating database encryption.

| Parameter | Default | Min | Max | Description |
| :--- | :---: | :---: | :---: | :--- |
| `legacy` | 0 | 0 | 1 | Boolean flag whether the legacy mode should be used |
| `legacy_page_size` | 0 | 0 | 65536 | Page size to use in legacy mode, 0 = default SQLite page size |

**Note**: It is not recommended to use _legacy_ mode for encrypting new databases. It is supported for compatibility reasons only, so that databases that were encrypted in _legacy_ mode can be accessed.

### <a name="cipher_aes256cbc"/>wxSQLite3: AES 256 Bit CBC - No HMAC

This cipher was added to **wxSQLite3** in 2010. It is a 256 bit AES encryption in CBC mode.

The encryption key is derived from the passphrase using an SHA256 hash function.

The initial vector for the encryption of each database page is derived from the page number.

The cipher does not use a Hash Message Authentication Code (HMAC), and requires therefore no reserved bytes per database page.

The following table lists all parameters related to this cipher that can be set before activating database encryption.

| Parameter | Default | Min | Max | Description |
| :--- | :---: | :---: | :---: | :--- |
| `kdf_iter` | 4001 | 1 | | Number of iterations for the key derivation function
| `legacy` | 0 | 0 | 1 | Boolean flag whether the legacy mode should be used |
| `legacy_page_size` | 0 | 0 | 65536 | Page size to use in legacy mode, 0 = default SQLite page size |

**Note**: It is not recommended to use _legacy_ mode for encrypting new databases. It is supported for compatibility reasons only, so that databases that were encrypted in _legacy_ mode can be accessed.

### <a name="cipher_chacha20"/>sqleet: ChaCha20 - Poly1305 HMAC

This cipher was introduced for SQLite database encryption by the project [sqleet](https://github.com/resilar/sqleet) in 2017.

The Internet Engineering Task Force (IETF) officially standardized the cipher algorithm **ChaCha20** and the message authentication code **Poly1305** in [RFC 7905](https://tools.ietf.org/html/rfc7905) for Transport Layer Security (TLS).

The new default **wxSQLite3** cipher is **ChaCha20 - Poly1305**.

The encryption key is derived from the passphrase using a random salt (stored in the first 16 bytes of the database file) and the standardized PBKDF2 algorithm with an SHA256 hash function.

One-time keys per database page are derived from the encryption key, the page number, and a 16 bytes nonce. Additionally, a 16 bytes **Poly1305** authentication tag per database page is calculated. Therefore this cipher requires 32 reserved bytes per database page.

The following table lists all parameters related to this cipher that can be set before activating database encryption.

| Parameter | Default | sqleet | Min | Max | Description |
| :--- | :---: | :---: | :---: | :---: | :--- |
| `kdf_iter` | 64007 | 12345 | 1 | | Number of iterations for the key derivation function |
| `legacy` | 0 | 1 | 0 | 1 | Boolean flag whether the legacy mode should be used |
| `legacy_page_size` | 4096 | 4096 | 0 | 65536 | Page size to use in legacy mode, 0 = default SQLite page size |

**Note**: It is not recommended to use _legacy_ mode for encrypting new databases. It is supported for compatibility reasons only, so that databases that were encrypted in _legacy_ mode can be accessed.

### <a name="cipher_sqlcipher"/> SQLCipher: AES 256 Bit CBC - SHA1/SHA256/SHA512 HMAC

SQLCipher was developed by [Zetetic LLC](http://zetetic.net) and initially released in 2008. It is a 256 bit AES encryption in CBC mode.

The encryption key is derived from the passphrase using a random salt (stored in the first 16 bytes of the database file) and the standardized PBKDF2 algorithm with an SHA1, SHA256, or SHA512 hash function.

A random 16 bytes initial vector (nonce) for the encryption of each database page is used for the AES algorithm. Additionally, an authentication tag per database page is calculated. SQLCipher version 1 used no tag; SQLCipher version 2 to 3 used a 20 bytes **SHA1** tag; SQLCipher version 4 uses a 64 bytes **SHA512** tag, allowing to optionally choose a 32 bytes **SHA256** tag instead. Therefore this cipher requires 16, 48 or 80 reserved bytes per database page (since the number of reserved bytes is rounded to the next multiple of the AES block size of 16 bytes).

The following table lists all parameters related to this cipher that can be set before activating database encryption. The columns labelled **v4**, **v3**, **v2**, and **v1** show the parameter values used in legacy SQLCipher versions **3**, **2**, and **1** respectively. To access databases encrypted with the respective SQLCipher version the listed parameters have to be set explicitly.

| Parameter               | Default | v4     | v3    | v2    | v1     | Min   | Max   | Description |
| :---                    | :---:   | :---:  | :---: | :---: | :---:  | :---: | :---: | :--- |
| `kdf_iter`              | 256000  | 256000 | 64000 | 4000  | 4000   | 1     |       | Number of iterations for key derivation |
| `fast_kdf_iter`         | 2       | 2      | 2     | 2     | 2      | 1     |       | Number of iterations for HMAC key derivation |
| `hmac_use`              | 1       | 1      | 1     | 1     | 0      | 0     | 1     | Flag whether a HMAC should be used |
| `hmac_pgno`             | 1       | 1      | 1     | 1     | n/a    | 0     | 2     | Storage type for page number in HMAC:<br/>0 = native, 1 = little endian, 2 = big endian|
| `hmac_salt_mask`        | 0x3a    | 0x3a   | 0x3a  | 0x3a  | n/a    | 0     | 255   | Mask byte for HMAC salt |
| `legacy`                | 0       | 4      | 3     | 2     | 1      | 0     | 4     | SQLCipher version to be used in legacy mode |
| `legacy_page_size`      | 4096    | 4096   | 1024  | 1024  | 1024   | 0     | 65536 | Page size to use in legacy mode, 0 = default SQLite page size |
| `kdf_algorithm`         | 2       | 2      | 0     | 0     | 0      | 0     | 2     | Hash algoritm for key derivation function<br/>0 = SHA1, 1 = SHA256, 2 = SHA512 |
| `hmac_algorithm`        | 2       | 2      | 0     | 0     | 0      | 0     | 2     | Hash algoritm for HMAC calculation<br/>0 = SHA1, 1 = SHA256, 2 = SHA512 |
| `plaintext_header_size` | 0       | 0      | n/a   | n/a   | n/a    | 0     | 100   | Size of plaintext database header<br/>must be multiple of 16, i.e. 32 |

**Note**: It is not recommended to use _legacy_ mode for encrypting new databases. It is supported for compatibility reasons only, so that databases that were encrypted in _legacy_ mode can be accessed. However, the default _legacy_ mode for the various SQLCipher versions can be easily set using just the parameter `legacy` set to the requested version number. That is, all other parameters have to be specified only, if their requested value deviates from the default value.

**Note**: Version 4 of SQLCipher introduces a new parameter `plain_text_header_size` to overcome an issue with shared encrypted databases under **iOS**. If this parameter is set to a non-zero value (like 16 or 32), the corresponding number of bytes at the beginning of the database header are not encrypted allowing **iOS** to identify the file as a SQLite database file. The drawback of this approach is that the cipher salt used for the key derivation can't be stored in the database header any longer. Therefore it is necessary to retrieve the cipher salt on creating a new database, and to specify the salt on opening an existing database. The cipher salt can be retrieved with the function `wxsqlite3_codec_data` using parameter `cipher_salt`, and has to be supplied on opening a database via the database URI parameter `cipher_salt`.

## <a name="legacy" /> Legacy cipher modes

SQLite reads bytes 16 through 23 from the [database header](https://www.sqlite.org/fileformat.html#the_database_header) before the database file is actually opened. The main purpose of this is to detect the page size and the number of reserved bytes per page. Legacy ciphers used to encrypt these header bytes as well, but this may prevent SQLite from successfully opening the database file.

The official [SQLite Encryption Extension (SEE)](https://www.sqlite.org/see) leaves these header bytes unencrypted for this reason. Since version 3.1.0, wxSQLite3 also doesn't encrypt these header bytes unless the `legacy` parameter is explicitly set.

When using the ciphers **sqleet** (ChaCha20) or **SQLCipher**, this means that the databases written by wxSQLite3 won't be compatible with the original ciphers provided by [sqleet](https://github.com/resilar/sqleet) and [SQLCipher (Zetetic LLC)](http://zetetic.net) unless the `legacy` parameter is explicitly set. This is because the original implementations fully encrypt the database header by default. (Note that **sqleet** can also be compiled in non-legacy mode, and future releases of **SQLCipher** will probably provide this option as well.)

If a database is encrypted in legacy mode, then the `legacy` parameter *must* be set to **_true_** and the `legacy_page_size` parameter *should* be set to the correct page size. If this isn't done, wxSQLite3 might fail to access the database. Use [`wxsqlite3_config_cipher()`](#encryption_config_cipher) to set these parameters.

When accessing a database encrypted with wxSQLite3 ciphers **AES-128** or **AES-256** in legacy format, then wxSQLite3 transparently converts the database into the new format unless the `legacy` parameter is explicitly set. Note that wxSQLite3 versions prior to 3.1.0 won't be able to access non-legacy database files and will report the error message "not a database file or encrypted" instead.

It's strongly recommended to use the new encryption scheme, since it provides better compatibility with SQLite. The unencrypted header bytes don't reveal any sensitive information. Note, however, that it will actually be possible to recognize encrypted SQLite database files as such. This isn't usually a problem since the purpose of a specific file can almost always be deduced from context anyway.

It's also possible to activate the legacy mode at compile time by defining the following preprocessor symbols:

| Preprocessor symbol | Description |
| :--- | :--- |
| `WXSQLITE3_USE_OLD_ENCRYPTION_SCHEME` | Enable legacy mode for wxSQLite3 ciphers **AES-128** and **AES-256** |
| `WXSQLITE3_USE_SQLEET_LEGACY` | Enable legacy mode for **sqleet** (ChaCha20) cipher |
| `WXSQLITE3_USE_SQLCIPHER_LEGACY` | Enable legacy mode for **SQLCipher** cipher |

For the **SQLCipher** support the default version can be selected at compile time by defining the following preprocessor symbol:

| Preprocessor symbol | Description |
| `SQLCIPHER_VERSION_DEFAULT` | Select default **SQLCipher** version 1, 2, 3, or 4 |

## <a name="encryptionapi" />Encryption API

### <a name="encryption_overview" />Overview

The encryption API consists of the following functions:

| Function | Description |
| :--- | :--- |
| `sqlite3_key()` and `sqlite3_key_v2()` | Set the database key to use when accessing an encrypted database |
| `sqlite3_rekey()` and `sqlite3_rekey_v2()` | Change the database encryption key |
| `wxsqlite3_config()` | Configure database encryption parameters |
| `wxsqlite3_config_cipher()` | Configure cipher encryption parameters |

In addition, there is the `wxsqlite3_config()` SQL function which serves as SQL interface for `wxsqlite3_config()` and `wxsqlite3_config_cipher()`.

### <a name="encryption_key" />`sqlite3_key()` and `sqlite3_key_v2()`

```C
SQLITE_API int sqlite3_key(
  sqlite3 *db,                   /* Database to set the key on */
  const void *pKey, int nKey     /* The key */
);

SQLITE_API int sqlite3_key_v2(
  sqlite3 *db,                   /* Database to set the key on */
  const char *zDbName,           /* Database schema name */
  const void *pKey, int nKey     /* The key */
);
```

`sqlite3_key()` and `sqlite3_key_v2()` set the database key to use when accessing an encrypted database, and should usually be called immediately after `sqlite3_open()`.

`sqlite3_key()` is used to set the key for the main database, while `sqlite3_key_v2()` sets the key for the database with the schema name specified by `zDbName`. The schema name is `main` for the main database, `temp` for the temporary database, or the schema name specified in an [`ATTACH` statement](https://www.sqlite.org/lang_attach.html) for an attached database. If `sqlite3_key()` or `sqlite3_key_v2()` is called on an empty database, then the key will be initially set. The return value is `SQLITE_OK` on success, or a non-zero SQLite3 error code on failure.

**Note:** These functions return `SQLITE_OK` even if the provided key isn't correct. This is because the key isn't actually used until a subsequent attempt to read or write the database is made. To check whether the provided key was actually correct, you must execute a simple query like e.g. `SELECT * FROM sqlite_master;` and check whether that succeeds.

**Note:** When setting a new key on an empty database (that is, a database with zero bytes length), you have to make a subsequent write access so that the database will actually be encrypted. You'd usually want to write to a new database anyway, but if not, you can execute the [`VACUUM` command](https://www.sqlite.org/lang_vacuum.html) instead to force SQLite to write to the empty database.

### <a name="encryption_rekey" />`sqlite3_rekey()` and `sqlite3_rekey_v2()`

```C
SQLITE_API int sqlite3_rekey(
  sqlite3 *db,                   /* Database to be rekeyed */
  const void *pKey, int nKey     /* The new key */
);

SQLITE_API int sqlite3_rekey_v2(
  sqlite3 *db,                   /* Database to be rekeyed */
  const char *zDbName,           /* Database schema name */
  const void *pKey, int nKey     /* The new key */
);
```

`sqlite3_rekey()` and `sqlite3_rekey_v2()` change the database encryption key.

`sqlite3_rekey()` is used to change the key for the main database, while `sqlite3_rekey_v2()` changes the key for the database with the schema name specified by `zDbName`. The schema name is `main` for the main database, `temp` for the temporary database, or the schema name specified in an [`ATTACH` statement](https://www.sqlite.org/lang_attach.html) for an attached database.

Changing the key includes encrypting the database for the first time, decrypting the database (if `pKey == NULL` or `nKey == 0`), as well as re-encrypting it with a new key. The return value is `SQLITE_OK` on success, or a non-zero SQLite3 error code on failure.

**Note:** If the number of reserved bytes per database page differs between the current and the new encryption scheme, then `sqlite3_rekey()` performs a [`VACUUM` command](https://www.sqlite.org/lang_vacuum.html) to encrypt/decrypt all pages of the database. Thus, the total disk space requirement for re-encrypting can be up to 3 times of the database size. If possible, re-encrypting is done in-place.

**Note:** On decrypting a database all reserved bytes per database page are released.

**Note**: On changing the database encryption key it is not possible to change the page size of the database at the same time. This affects mainly _legacy_ modes with a non-default page size (like legacy **SQLCipher**, which has a page size of 1024 bytes). In such cases it is necessary to adjust the legacy page size to the default page size or to adjust the page size in a separate step by executing the following SQL statements:

```SQL
PRAGMA page_size=4096;
VACUUM;
```

However, please keep in mind that this works only on plain unencrypted databases.

### <a name="encryption_config" />`wxsqlite3_config()`

```C
SQLITE_API int wxsqlite3_config(
  sqlite3*    db,                /* Database instance */
  const char* paramName,         /* Parameter name */
  int         newValue           /* New value of the parameter */
);
```

`wxsqlite3_config()` gets or sets encryption parameters which are relevant for the entire database instance. `db` is the database instance to operate on, or `NULL` to query the compile-time default value of the parameter. `paramName` is the name of the parameter which should be get or set. To set a parameter, pass the new parameter value as `newValue`. To get the current parameter value, pass **-1** as `newValue`.

Parameter names use the following prefixes:

| Prefix | Description|
| :--- | :--- |
| *no prefix* | Get or set the *transient* parameter value. Transient values are only used **once** for the next call to `sqlite3_key()` or `sqlite3_rekey()`. Afterwards, the *permanent* default values will be used again (see below). |
| `default:` | Get or set the *permanent* default parameter value. Permanent values will be used during the entire lifetime of the `db` database instance, unless explicitly overridden by a transient value. The initial values for the permanent default values are the compile-time default values. |
| `min:` | Get the lower bound of the valid parameter value range. This is read-only. |
| `max:` | Get the upper bound of the valid parameter value range. This is read-only. |

The following parameter names are supported for `paramName`:

| Parameter name | Description | Possible values |
| :--- | :--- | :--- |
| `cipher` | The cipher to be used for encrypting the database. | `CODEC_TYPE_AES128` (Cipher ID 1)<br/>`CODEC_TYPE_AES256` (Cipher ID 2)<br/>`CODEC_TYPE_CHACHA20` (Cipher ID 3)<br/>`CODEC_TYPE_SQLCIPHER` (Cipher ID 4) |
| `hmac_check` | Boolean flag whether the HMAC should be validated on read operations for encryption schemes using HMACs | `0` <br/> `1` |

The return value always is the current parameter value on success, or **-1** on failure.

**Note:** Checking the HMAC on read operations is active by default. With the parameter `hmac_check` the HMAC check can be disabled in case of trying to recover a corrupted database. It is not recommended to deactivate the HMAC check for regular database operation. Therefore the default can not be changed.

**Examples:**

```C
/* Use AES-256 cipher for the next call to sqlite3_key() or sqlite3_rekey() for the given db */
wxsqlite3_config(db, "cipher", CODEC_TYPE_AES256);
```

```C
/* Use SQLCipher during the entire lifetime of database instance */
wxsqlite3_config(db, "default:cipher", CODEC_TYPE_SQLCIPHER);
```

```C
/* Get the maximum value which can be used for the "cipher" parameter */
wxsqlite3_config(NULL, "max:cipher", -1);
```

### <a name="encryption_config_cipher" />`wxsqlite3_config_cipher()`

```C
SQLITE_API int wxsqlite3_config_cipher(
  sqlite3*    db,                /* Database instance */
  const char* cipherName,        /* Cipher name */
  const char* paramName,         /* Parameter name */
  int         newValue           /* New value of the parameter */
);
```

`wxsqlite3_config_cipher()` gets or sets encryption parameters which are relevant for a specific encryption cipher only. See the [`wxsqlite3_config()` function](#encryption_config) for details about the `db`, `paramName` and `newValue` parameters. See the related [cipher descriptions](#ciphers) for the parameter names supported for `paramName`.

The following cipher names are supported for `cipherName`:

| Cipher name | Refers to | Description |
| :--- | :--- | :--- |
| `aes128cbc` | `CODEC_TYPE_AES128` (Cipher ID 1) | [AES 128 Bit CBC - No HMAC (wxSQLite3)](#cipher_aes128cbc) |
| `aes256cbc` | `CODEC_TYPE_AES256` (Cipher ID 2) | [AES 256 Bit CBC - No HMAC (wxSQLite3)](#cipher_aes256cbc) |
| `chacha20`  | `CODEC_TYPE_CHACHA20` (Cipher ID 3) | [ChaCha20 - Poly1305 HMAC (sqleet)](#cipher_chacha20) |
| `sqlcipher` | `CODEC_TYPE_SQLCIPHER` (Cipher ID 4) | [AES 256 Bit CBC - SHA1 HMAC (SQLCipher)](#cipher_sqlcipher) |

The return value always is the current parameter value on success, or **-1** on failure.

**Example:**

```C
/* Activate SQLCipher version 1 encryption scheme for the next key or rekey operation */
wxsqlite3_config(db, "cipher", CODEC_TYPE_SQLCIPHER);
wxsqlite3_config_cipher(db, "sqlcipher", "kdf_iter", 4000);
wxsqlite3_config_cipher(db, "sqlcipher", "fast_kdf_iter", 2);
wxsqlite3_config_cipher(db, "sqlcipher", "hmac_use", 0);
wxsqlite3_config_cipher(db, "sqlcipher", "legacy", 1);
wxsqlite3_config_cipher(db, "sqlcipher", "legacy_page_size", 1024);
```

### <a name="encryption_codec_data" />`wxsqlite3_codec_data()`

```C
SQLITE_API unsigned char* wxsqlite3_codec_data(
  sqlite3*    db,                /* Database instance */
  const char* schemaName,        /* Cipher name */
  const char* paramName          /* Parameter name */
);
```

`wxsqlite3_codec_data()` retrieves the value of encryption parameters after an encrypted database has been opened. `db` is the database instance to operate on. `schemaName` optionally specifies the schema name of an attached database; for the main database the parameter can be specified as `NULL`. `paramName` specifies the parameter to be queried.

The following parameter names are currently supported for `paramName`:

| Cipher name | Description |
| :--- | :--- |
| `cipher_salt` | The random cipher salt used for key derivation and stored in the database header (as a hexadecimal encoded string, 32 bytes) |
| `raw:cipher_salt` | The random cipher salt used for key derivation and stored in the database header (as a raw binary string, 16 bytes) |

A NULL pointer is returned if the database is not encrypted or if the encryption scheme doesn't use a cipher salt. If a non-NULL pointer was returned, it is the application's responsibility to free the memory using function `sqlite3_free`.

**Note:** Some cipher schemes use a random cipher salt on database creation. If the database header gets corrupted for some reason, it is almost impossible to recover the database without knowing the cipher salt. For critical applications it is therefore recommended to retrieve the cipher salt after the initial creation of a database and keep it in a safe place.

**Note:** Please note that the parameter `cipher_salt` was renamed (the previous name was just `salt`).

### <a name="encryption_sql" />SQL interface

**wxSQLite3** additionally defines the `wxsqlite3_config()` SQL function which can be used to get or set encryption parameters by using SQL queries.

| SQL function | Description |
| :--- | :--- |
| `wxsqlite3_config(paramName TEXT)` | Get value of database encryption parameter `paramName` |
| `wxsqlite3_config(paramName TEXT, newValue)` | Set value of database encryption parameter `paramName` to `newValue` |
| `wxsqlite3_config(cipherName TEXT, paramName TEXT)` | Get value of cipher `cipherName` encryption parameter `paramName` |
| `wxsqlite3_config(cipherName TEXT, paramName TEXT, newValue)` | Set value of cipher `cipherName` encryption parameter `paramName` to `newValue` |
| `wxsqlite3_codec_data(paramName TEXT)` | Get value of parameter `paramName` |
| `wxsqlite3_codec_data(paramName TEXT, schemaName TEXT)` | Get value of parameter `paramName` from schema `schemaName` |

**Note:** See the [`wxsqlite3_config_cipher()` function](#encryption_config_cipher) for the list of supported `cipherName`s.

**Note:** Calling the configuration functions, the `paramName` can have a prefix. See the [`wxsqlite3_config()` function](#encryption_config) for details.

**Examples:**

```SQL
-- Get cipher used for the next key or rekey operation
SELECT wxsqlite3_config('cipher');
```

```SQL
-- Set cipher used by default for all key and rekey operations
SELECT wxsqlite3_config('default:cipher', 'sqlcipher');
```

```SQL
-- Get number of KDF iterations for the AES-256 cipher
SELECT wxsqlite3_config('aes256cbc', 'kdf_iter');
```

```SQL
-- Set number of KDF iterations for the AES-256 cipher to 54321
SELECT wxsqlite3_config('aes256cbc', 'kdf_iter', 54321);
```

```SQL
-- Activate SQLCipher version 1 encryption scheme for the subsequent key PRAGMA
SELECT wxsqlite3_config('cipher', 'sqlcipher');
SELECT wxsqlite3_config('sqlcipher', 'kdf_iter', 4000);
SELECT wxsqlite3_config('sqlcipher', 'fast_kdf_iter', 2);
SELECT wxsqlite3_config('sqlcipher', 'hmac_use', 0);
SELECT wxsqlite3_config('sqlcipher', 'legacy', 1);
SELECT wxsqlite3_config('sqlcipher', 'legacy_page_size', 1024);
PRAGMA key='<passphrase>';
```

```SQL
-- Get the random key salt as a hexadecimal encoded string (if database is encrypted and uses key salt)
SELECT wxsqlite3_codec_data('salt');
```

### <a name="encryption_uri" />URI parameters

SQLite3 allows to specify database file names as [SQLite Uniform Resource Identifiers](https://www.sqlite.org/uri.html) on opening or attaching databases. The advantage of using a URI file name is that query parameters on the URI can be used to control details of the newly created database connection. The **wxSQLite3** encryption extension now allows to configure the encryption cipher via URI query parameters.

| URI Parameter | Description |
| :--- | :--- |
| `cipher`=_cipher name_ | The `cipher` query parameter specifies which cipher should be used. It has to be the identifier name of one of the supported ciphers. |
| `key`=_passphrase_ | The `key` query parameter allows to specify the passphrase used to initialize the encryption extension for the database connection. If the query string does not contain a `cipher` parameter, the default cipher selected at compile time is used. |
| `hexkey`=_hex-passphrase_ | The `hexkey` query parameter allows to specify a hexadecimal encoded passphrase used to initialize the encryption extension for the database connection. If the query string does not contain a `cipher` parameter, the default cipher selected at compile time is used. |

**Note 1**: The URI query parameters `key` and `hexkey` are detected and applied by the SQLite3 library itself. If one of them is used and if it is not intended to use the default cipher, then the `cipher` query parameter and optionally further cipher configuration parameters have to be given in the URI query string as well. 

**Note 2**: The URI query parameters `key` and `hexkey` are only respected by SQLite3 on **opening** a database, but not on **attaching** a database. To specify the passphrase on attaching a database the keyword `KEY` of the SQL command `ATTACH` has to be used.

Depending on the cipher selected via the `cipher` parameter, additional query parameters can be used to configure the encryption extension. All parameters as described for each supported cipher (like `legacy`, `kdf_iter`, and so on) can be used to modify the cipher configuration. Default values are used for all cipher parameters which are not explicitly added to the URI query string. Misspelled parameters are silently ignored.

**Note 3**: The `cipher` query parameter is always required, if further query parameters should be used to configure the encryption extension. If this parameter is missing or specifies an unknown cipher, all other cipher configuration parameters are silently ignored, and the default cipher as selected at compile time will be used.

**Note 4**: On **opening** a database all cipher configuration parameters given in the URI query string are used to set the **default** cipher configuration of the database connection. On **attaching** a database the cipher configuration parameters given in the URI query string will be used for the attached database, but will not change the defaults of the database connection.

Example: URI query string to select the legacy SQLCipher Version 2 encryption scheme:  
```
file:databasefile?cipher=sqlcipher&legacy=1&kdf_iter=4000
```

## <a name="backupapi" />SQLite3 Backup API

When using the SQLite3 backup API to create a backup copy of a SQLite database, the most common case is that source and target database use the same encryption cipher, if any. However, the **wxSQLite3** multi-cipher encryption extension allows to assign different ciphers to the source and target database.

Problems can arise from the fact that different ciphers may require a different number of reserved bytes per database page. If the number of reserved bytes for the target database is greater than that for the source database, performing a backup via the SQLite3 backup API is unfortunately not possible. In such a case the backup will be aborted.

To allow as many cipher combinations as possible the **wxSQLite3** multi-cipher encryption extension implements fallback solutions for the most common case where the source database is not encrypted, but a cipher usually requiring a certain number of reserved bytes per database page was selected for the target database. In this case no reserved bytes will be used by the ciphers. The drawback is that the resulting encryption is less secure and that the resulting databases will not be compatible with the corresponding legacy ciphers.

Please find below a table describing with which encryption cipher combinations the backup API can be used.

| **Backup**&nbsp;&nbsp;**To** |  SQLite3 |  wxSQLite3 |  wxSQLite3 | wxSQLite3 | SQLCipher v1 | SQLCipher v2+ |
| --- | :---: | :---: | :---: | :---: | :---: | :---: |
<br/>**From** | Plain<br/>&nbsp; | AES-128<br/>&nbsp; | AES-256<br/>&nbsp; | ChaCha20<br/>Poly1305 | AES-256<br/>&nbsp; | AES-256<br/>SHA1 |
SQLite3<br/>Plain<br/>&nbsp; | :ok: | :ok: | :ok: | :ok: :exclamation: | :ok: :exclamation: | :ok: :exclamation:
wxSQLite3<br/> AES-128<br/>&nbsp; | :ok: | :ok: | :ok: | :ok: :exclamation: | :ok: :exclamation: | :ok: :exclamation:
wxSQLite3<br/>AES-256<br/>&nbsp; | :ok: | :ok: | :ok: | :ok: :exclamation: | :ok: :exclamation: | :ok: :exclamation:
wxSQLite3<br/>ChaCha20<br/>Poly1305 |  :ok: <sup>:small_red_triangle_down:</sup> | :ok: <sup>:small_red_triangle_down:</sup> | :ok: <sup>:small_red_triangle_down:</sup> | :ok: | :x: | :x:
SQLCipher v1<br/>AES-256<br/>&nbsp; | :ok: <sup>:small_red_triangle_down:</sup> | :ok: <sup>:small_red_triangle_down:</sup> | :ok: <sup>:small_red_triangle_down:</sup> | :x: | :ok: | :x:
SQLCipher&nbsp;v2+<br/>AES-256<br/>SHA1 | :ok: <sup>:small_red_triangle_down:</sup> | :ok: <sup>:small_red_triangle_down:</sup> | :ok: <sup>:small_red_triangle_down:</sup> | :ok: <sup>:small_red_triangle_down:</sup> | :x: | :ok:

Symbol | Description
:---: | :---
:ok:  | Works
:x: | Does **not** work
:exclamation: | Works only for non-legacy ciphers with reduced security
<sup>:small_red_triangle_down:</sup> | Keeps reserved bytes per database page

**Note**: It is strongly recommended to use the same encryption cipher for source **and** target database.

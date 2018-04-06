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
  - [SQLCipher: AES 256 Bit CBC - SHA1 HMAC](#cipher_sqlcipher)
- [Legacy cipher modes](#legacy)
- [SQLite3 / wxSQLite3 encryption API](#encryptionapi)

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
- [AES 256 Bit CBC - SHA1 HMAC (SQLCipher)](#cipher_sqlcipher)

Definition of abbreviations:

- AES = Advanced Encryption Standard (Rijndael algorithm)
- CBC = Cipher Block Chaining mode
- HMAC = Hash Message Authentication Code
- ChaCha20 = symmetric stream cipher developed by Daniel J. Bernstein
- Poly1305 = cryptographic message authentication code (MAC) developed by Daniel J. Bernstein
- SHA1 = Secure Hash Algorithm 1

### <a name="cipher_aes128cbc"/>wxSQLite3: AES 128 Bit CBC - No HMAC

This cipher was added to **wxSQLite3** in 2007 as the first supported encryption scheme. It is a 128 bit AES encryption in CBC mode.

The encryption key is derived from the passphrase according to the algorithm described in the PDF specification (using the MD5 hash function and the RC4 algorithm).

The initial vector for the encryption of each database page is derived from the page number.

The cipher does not use a HMAC, and requires therefore no reserved bytes per database page.

The following table lists all parameters related to this cipher that can be set before activating database encryption.

| Parameter | Default | Min | Max | Description |
| :--- | :---: | :---: | :---: | :--- |
| legacy | 0 | 0 | 1 | Boolean flag whether the legacy mode should be used |

**Note**: It is not recommended to use _legacy_ mode for encrypting new databases. It is supported for compatibility reasons only, so that databases that were encrypted in _legacy_ mode can be accessed.

### <a name="cipher_aes256cbc"/>wxSQLite3: AES 256 Bit CBC - No HMAC

This cipher was added to **wxSQLite3** in 2010. It is a 256 bit AES encryption in CBC mode.

The encryption key is derived from the passphrase using an SHA256 hash function.

The initial vector for the encryption of each database page is derived from the page number.

The cipher does not use a Hash Message Authentication Code (HMAC), and requires therefore no reserved bytes per database page.

The following table lists all parameters related to this cipher that can be set before activating database encryption.

| Parameter | Default | Min | Max | Description |
| :--- | :---: | :---: | :---: | :--- |
| kdf_iter | 4001 | 1 | | Number of iterations for the key derivation function
| legacy | 0 | 0 | 1 | Boolean flag whether the legacy mode should be used |

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
| kdf_iter | 64007 | 12345 | 1 | | Number of iterations for the key derivation function |
| legacy | 0 | 1 | 0 | 1 | Boolean flag whether the legacy mode should be used. |

**Note**: It is not recommended to use _legacy_ mode for encrypting new databases. It is supported for compatibility reasons only, so that databases that were encrypted in _legacy_ mode can be accessed.

### <a name="cipher_sqlcipher"/> SQLCipher: AES 256 Bit CBC - SHA1 HMAC

SQLCipher was developed by [Zetetic LLC](http://zetetic.net) and initially released in 2008. It is a 256 bit AES encryption in CBC mode.

The encryption key is derived from the passphrase using a random salt (stored in the first 16 bytes of the database file) and the standardized PBKDF2 algorithm with an SHA1 hash function.

A random 16 bytes  initial vector (nonce) for the encryption of each database page is used for the AES algorithm. Additionally, a 20 bytes **SHA1** authentication tag per database page is calculated. Therefore this cipher requires 48 reserved bytes per database page (since the number of reserved bytes is rounded to the next multiple of the AES block size of 16 bytes).

The following table lists all parameters related to this cipher that can be set before activating database encryption. The columns labelled **v3**, **v2**, and **v1** show the parameter values used in legacy SQLCipher versions **3**, **2**, and **1** respectively. To access databases encrypted with the respective SQLCipher version the listed parameters have to be set explicitly.

| Parameter | Default | v3 | v2 | v1 | Min | Max | Description |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| kdf_iter | 64000 | 64000 | 4000 | 4000 | 1 | | Number of iterations for key derivation |
| fast_kdf_iter | 2 | 2 | 2 | 2 | 1 | | Number of iterations for HMAC key derivation |
| hmac_use | 1 | 1 | 1 | 0 | 0 | 1 | Flag whether a HMAC should be used |
| hmac_pgno | 1 | 1 | 1 | n/a | 0 | 2 | Storage type for page number in HMAC:<br/>0 = native, 1 = little endian, 2 = big endian|
| hmac_salt_mask | 0x3a | 0x3a | 0x3a | n/a | 0 | 255 | Mask byte for HMAC salt |
| legacy | 0 | 1 | 1 | 1 | 0 | 1 | Boolean flag whether the legacy mode should be used |

**Note**: It is not recommended to use _legacy_ mode for encrypting new databases. It is supported for compatibility reasons only, so that databases that were encrypted in _legacy_ mode can be accessed.

## <a name="legacy" /> Legacy cipher modes

All supported encryption ciphers have a **legacy** mode. In this mode the bytes 16 through 23 of the database header are encrypted, too. This is in conflict with the description of the official  [SQLite Encryption Extension (SEE)](https://www.sqlite.org/see), stating that bytes 16 through 23 of the database file contain header information which is not encrypted. This is important, because these bytes are read and interpreted by the SQLite code before any encryption extension gets the chance to decrypt the database header.

If bytes 16 through 23 of the database header are encrypted, SQLite is usually not able to determine the page size of the database file correctly. Therefore either the encryption extension itself or the user has to explicitly set the correct page size. If this is not done, SQLite might fail to access the encrypted database.

Starting with the release of wxSQLite3 version 3.1.0 the code of the encryption extension for both wxSQLite3 ciphers (AES 128 Bit and AES 256 Bit) has been adjusted to fix potential problem resulting from encrypting bytes 16 through 23 of the database header, although chances were low that users of the prior versions of the encryption extension experienced problems, namely at most 1 out of 8192 cases.

The good news for users of prior versions of the wxSQLite3 ciphers is that the new version transparently converts existing encrypted databases to the new format. However, this is a one-way process, that is, once converted a database file can't be handled anymore by prior versions of the encryption extension. Instead, one will get the error message "not a database file or encrypted".

For the ciphers **sqleet** (ChaCha20) and **SQLCipher** the wxSQLite3 encryption extension offers variants that respect the SQLite requirements and do not encrypt the database header bytes 16 to 23. However, the resulting databases are not compatible with the original ciphers provided by [sqleet](https://github.com/resilar/sqleet) resp [SQLCipher (Zetetic LLC)](http://zetetic.net).

It is strongly recommended that the new encryption scheme is used, since it provides better compatibility with SQLite. However, if you need at all costs for some reason the old behaviour, you can activate it by defining the following preprocessor symbol:

```C
#define WXSQLITE3_USE_OLD_ENCRYPTION_SCHEME
```
This sets the default value of the **legacy** parameter of the wxSQLite3 ciphers to **_true_**. However, the values of all parameters can be temporarily or permanently overwritten.

For the **sqleet** and **SQLCipher** ciphers the situation is a bit different. Their original implementations do not offer the option to leave bytes 16 through 23 of the database header unencrypted (although this is probably about to change at least for a future release of **SQLCipher**). Therefore the implementation of these ciphers in the **wxSQLite3** encryption extension includes a mode where bytes 16 through 23 of the database header are not encrypted.

If it is required to access legacy **sqleet** or **SQLCipher** databases this is possible by setting the value of the **legacy** parameter to **_true_**. Additionally, it might be required to explicitly set the page size.

## <a name="encryptionapi" />SQLite3 / wxSQLite3 encryption API

The encryption API of SQLite3 consists of only a few functions `sqlite3_key()`, `sqlite3_key_v2()`, `sqlite3_rekey()`, and `sqlite3_rekey_v2()` for managing encryption keys.

```C
SQLITE_API int sqlite3_key(
  sqlite3 *db,                   /* Database to be rekeyed */
  const void *pKey, int nKey     /* The key */
);

SQLITE_API int sqlite3_key_v2(
  sqlite3 *db,                   /* Database to be rekeyed */
  const char *zDbName,           /* Name of the database */
  const void *pKey, int nKey     /* The key */
);
```

`sqlite3_key()` is typically called immediately after `sqlite3_open()` to specify an encryption key for the opened database. The function returns `SQLITE_OK` if the given key was correct. Otherwise a non-zero SQLite3 error code is returned and subsequent attempts to read or write the database will fail.

```C
SQLITE_API int sqlite3_rekey(
  sqlite3 *db,                   /* Database to be rekeyed */
  const void *pKey, int nKey     /* The new key */
);

SQLITE_API int sqlite3_rekey_v2(
  sqlite3 *db,                   /* Database to be rekeyed */
  const char *zDbName,           /* Name of the database */
  const void *pKey, int nKey     /* The new key */
);
```

`sqlite3_rekey()` changes the database encryption key. This includes encrypting the database the first time, decrypting the database (if `nKey == 0`), as well as re-encrypting it with a new key. Internally, `sqlite3_rekey()` performs a `VACUUM` to encrypt/decrypt all pages of the database, if the number of reserved bytes per database page differs between the current and the new encryption scheme - thus the total disk space requirement for re-encrypting can be up to 3 times the size of the database. Otherwise the re-encrypting is done in-place. On decrypting a database all possibly reserved bytes are released. The return value is `SQLITE_OK` on success.

**wxSQLite3** adds 2 further function to the interface. These functions allow to configure the encryption extension and the encryption ciphers.

```C
SQLITE_API int wxsqlite3_config(
  const char *paramName,         /* Parameter name */
  int newValue                   /* New value of the parameter */
);

SQLITE_API int wxsqlite3_config_cipher(
  const char *cipherName,        /* Cipher name */
  const char *paramName,         /* Parameter name */
  int newValue                   /* New value of the parameter */
);
```

The function `wxsqlite3_config` allows to configure global parameters. Currently the only supported parameter is `cipher` parameter:

| Parameter | Description |
| :--- | :--- |
| cipher | The cipher to be used for the next activation of database encryption.<br/>The new value has to be the **_Cipher ID_** or **_-1_** to query the current value of the parameter. |

The function `wxsqlite3_config_cipher` allows to configure the parameters of a specific cipher using the cipher name and the name of the cipher parameter in question. The cipher name is not case-sensitive. A list of valid parameters is given in the related cipher description sections.

| Cipher ID | Cipher name | Cipher description |
| :---: | :--- | :--- |
| 1 | aes128cbc | [AES 128 Bit CBC - No HMAC (wxSQLite3)](#cipher_aes128cbc) |
| 2 | aes256cbc | [AES 256 Bit CBC - No HMAC (wxSQLite3)](#cipher_aes256cbc) |
| 3 | chacha20  | [ChaCha20 - Poly1305 HMAC (sqleet)](#cipher_chacha20) |
| 4 | sqlcipher | [AES 256 Bit CBC - SHA1 HMAC (SQLCipher)](#cipher_sqlcipher) |

To query a parameter value without changing it, the new value has to be **_-1_**.

The parameter names can have the following prefixes:

| Prefix | Description|
| :--- | :--- |
| default: | Set or query the default value of a parameter |
| min: | Query the lower bound of the parameter value range.<br/>The new value is ignored. |
| max: | Query the upper bound of the parameter value range.<br/>The new value is ignored. |

For example, use parameter name **default:cipher** to set the cipher to be used for all subsequent encryption activations.

Additionally, **wxSQLite3** defines a SQL function that can be used to set or query encryption parameters from SQL statements.

| SQL function | Description |
| :--- | :--- |
| wxsqlite3_config(**_globalParameter_**) | Query global parameter |
| wxsqlite3_config(**_globalParameter_**, **_newValue_**) | Set new value for global parameter |
| wxsqlite3_config(**_cipherName_**, **_cipherParameter_**) | Query cipher parameter |
| wxsqlite3_config(**_cipherName_**, **_cipherParameter_**, **_newValue_**) | Set new value for cipher parameter |

Again, the parameter names can have prefixes as listed above.

For querying and/or setting a parameter the following SQL syntax can be used:

```SQL
SELECT wxsqlite3_config("<cipherName>", "<paramName>");           -- Query parameter
SELECT wxsqlite3_config("<cipherName>", "<paramName>", newValue); -- Set and query parameter
```

Example 1:
```SQL
SELECT wxsqlite3_config("aes256cbc", "kdf_iter", 54321); -- Set 54321 iterations for key derivation
```

The syntax is very similar to a `PRAGMA` statement, but has the advantage that no changes to the SQLite amalgamation source code are necessary.

Example 2:
```SQL
-- Activate SQLCipher version 1 encryption scheme
SELECT wxsqlite3_config("cipher", "sqlcipher");
SELECT wxsqlite3_config("sqlcipher", "kdf_iter", 4000);
SELECT wxsqlite3_config("sqlcipher", "fast_kdf_iter", 2);
SELECT wxsqlite3_config("sqlcipher", "hmac_use", 0);
SELECT wxsqlite3_config("sqlcipher", "legacy", 1);
SELECT wxsqlite3_config("sqlcipher", "legacy_page_size", 1024);
PRAGMA key="<passphrase>";
```

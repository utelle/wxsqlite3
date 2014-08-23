This directory contains all SQLite3 version 3.8.6 files needed on
Windows platforms.

For the version with encryption support (AES-128 or AES-256) the
SQLite amalgamation source code is included. The source code of the
SQLite extension function module is included, too.

*** IMPORTANT NOTICE - PLEASE READ ON ***

Starting with the release of wxSQLite3 version 3.1.0 the code of the
encryption extension has been adjusted to fix a potential problem with
creating unusable encrypted databases.

Chances were low that users of the prior versions of the encryption
extension experienced problems, namely at most 1 out of 8192 cases.
However, it was decided to eliminate this flaw.

From now on bytes 16 to 23 of the database header are saved to file
unencrypted (as for the proprietary SQLite Extensions SEE (SQLite
Encryption Extension) offered by the creators of SQLite).
This is important, because these bytes are read and interpreted by
the SQLite code before any encryption extension gets the chance to
decrypt the database header.

The good news for users of prior versions of the wxSQLite3 encryption
extension is that the new version transparently converts existing
encrypted databases to the new format. However, this is a one-way
process, that is, once converted a database file can't be handled
anymore by prior versions of the encryption extension. Instead one
will get the error message "not a database file or encrypted".

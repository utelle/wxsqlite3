-- Activate AES 256 Bit CBC (wxSQLite3 legacy) encryption scheme
SELECT wxsqlite3_config("cipher", "aes256cbc");
SELECT wxsqlite3_config("aes256cbc", "legacy", 1);
-- Unfortunately, the default page size depends on the SQLite version
-- that was used for creating the database file:
-- 1024 Bytes for SQLite versions below version 3.12.0
-- 4096 Bytes for SQLite version 3.12.0 and above
SELECT wxsqlite3_config("aes256cbc", "legacy_page_size", 0);
SELECT wxsqlite3_config("aes256cbc", "kdf_iter", 4001);

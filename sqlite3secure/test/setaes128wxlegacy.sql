-- Activate AES 128 Bit CBC (wxSQLite3 legacy) encryption scheme
SELECT wxsqlite3_config("cipher", "aes128cbc");
SELECT wxsqlite3_config("aes128cbc", "legacy", 1);
-- Unfortunately, the default page size depends on the SQLite version
-- that was used for creating the database file:
-- 1024 Bytes for SQLite versions below version 3.12.0
-- 4096 Bytes for SQLite version 3.12.0 and above
SELECT wxsqlite3_config("aes128cbc", "legacy_page_size", 0);

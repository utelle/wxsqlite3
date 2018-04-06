-- Activate AES 256 Bit CBC (wxSQLite3) encryption scheme
SELECT wxsqlite3_config("cipher", "aes256cbc");
SELECT wxsqlite3_config("aes256cbc", "legacy", 0);
SELECT wxsqlite3_config("aes256cbc", "kdf_iter", 4001);

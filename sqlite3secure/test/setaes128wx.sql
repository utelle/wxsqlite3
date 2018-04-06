-- Activate AES 128 Bit CBC (wxSQLite3) encryption scheme
SELECT wxsqlite3_config("cipher", "aes128cbc");
SELECT wxsqlite3_config("aes128cbc", "legacy", 0);

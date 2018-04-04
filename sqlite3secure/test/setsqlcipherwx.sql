-- Activate SQLCipher version (wxSQLite3) encryption scheme
SELECT wxsqlite3_config("cipher", "sqlcipher");
SELECT wxsqlite3_config("sqlcipher", "legacy", 0);
SELECT wxsqlite3_config("sqlcipher", "kdf_iter", 64000);
SELECT wxsqlite3_config("sqlcipher", "fast_kdf_iter", 2);
SELECT wxsqlite3_config("sqlcipher", "hmac_use", 1);
SELECT wxsqlite3_config("sqlcipher", "hmac_pgno", 1);
SELECT wxsqlite3_config("sqlcipher", "hmac_salt_mask", 0x3a);

-- Activate SQLCipher version 2 encryption scheme
SELECT wxsqlite3_config("cipher", "sqlcipher");
SELECT wxsqlite3_config("sqlcipher", "legacy", 1);
SELECT wxsqlite3_config("sqlcipher", "legacy_page_size", 1024);
SELECT wxsqlite3_config("sqlcipher", "kdf_iter", 4000);
SELECT wxsqlite3_config("sqlcipher", "fast_kdf_iter", 2);
SELECT wxsqlite3_config("sqlcipher", "hmac_use", 1);
SELECT wxsqlite3_config("sqlcipher", "hmac_pgno", 1);
SELECT wxsqlite3_config("sqlcipher", "hmac_salt_mask", 0x3a);

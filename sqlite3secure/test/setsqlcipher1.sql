-- Activate SQLCipher version 1 encryption scheme
SELECT wxsqlite3_config("cipher", "sqlcipher");
SELECT wxsqlite3_config("sqlcipher", "legacy", 1);
SELECT wxsqlite3_config("sqlcipher", "legacy_page_size", 1024);
SELECT wxsqlite3_config("sqlcipher", "kdf_iter", 4000);
SELECT wxsqlite3_config("sqlcipher", "fast_kdf_iter", 2);
SELECT wxsqlite3_config("sqlcipher", "hmac_use", 0);

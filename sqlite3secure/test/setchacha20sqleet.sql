-- Activate ChaCha20-Poly1305 (sqleet legacy) encryption scheme
SELECT wxsqlite3_config("cipher", "chacha20");
SELECT wxsqlite3_config("chacha20", "legacy", 1);
SELECT wxsqlite3_config("chacha20", "legacy_page_size", 1024);
SELECT wxsqlite3_config("chacha20", "kdf_iter", 12345);

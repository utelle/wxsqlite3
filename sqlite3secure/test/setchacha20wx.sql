-- Activate ChaCha20-Poly1305 (wxSQLite3) encryption scheme
SELECT wxsqlite3_config("cipher", "chacha20");
SELECT wxsqlite3_config("chacha20", "legacy", 0);
SELECT wxsqlite3_config("chacha20", "kdf_iter", 64007);

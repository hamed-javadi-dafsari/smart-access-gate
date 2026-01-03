import sqlite3
from config import DB_PATH

def init_db():
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute("""
        CREATE TABLE IF NOT EXISTS access_log (
            id INTEGER PRIMARY KEY,
            user_code TEXT,
            image_path TEXT,
            timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
        )
    """)
    conn.commit()
    conn.close()

def log_access(user_code, image_path):
    conn = sqlite3.connect(DB_PATH)
    c = conn.cursor()
    c.execute(
        "INSERT INTO access_log (user_code, image_path) VALUES (?,?)",
        (user_code, image_path)
    )
    conn.commit()
    conn.close()

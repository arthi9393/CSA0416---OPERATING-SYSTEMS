"""Sample Result Portal (Flask). Works standalone; uses PostgreSQL only if DATABASE_URL is set."""
import os, socket, time
from flask import Flask, jsonify

app = Flask(__name__)
START = time.time()
RESULTS = {"2026CSE001": {"name": "Student A", "gpa": 8.9}, "2026CSE002": {"name": "Student B", "gpa": 8.1}}

def db_connect():
    import psycopg2
    return psycopg2.connect(os.environ["DATABASE_URL"], connect_timeout=3)

@app.route("/")
def index():
    return f"<h1>University Result Portal</h1><p>Served by: {socket.gethostname()}</p>"

@app.route("/health")
def health():
    return jsonify(status="ok", uptime_s=round(time.time() - START, 1))

@app.route("/result/<regno>")
def result(regno):
    r = RESULTS.get(regno)
    return (jsonify(r), 200) if r else (jsonify(error="not found"), 404)

@app.route("/visits")
def visits():
    """Counts visits in PostgreSQL (proves the DB volume keeps data across container restarts)."""
    if "DATABASE_URL" not in os.environ:
        return jsonify(error="DATABASE_URL not set"), 503
    conn = db_connect(); cur = conn.cursor()
    cur.execute("CREATE TABLE IF NOT EXISTS visits (id SERIAL PRIMARY KEY, at TIMESTAMP DEFAULT now())")
    cur.execute("INSERT INTO visits DEFAULT VALUES")
    cur.execute("SELECT count(*) FROM visits"); n = cur.fetchone()[0]
    conn.commit(); cur.close(); conn.close()
    return jsonify(visits=n)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000)

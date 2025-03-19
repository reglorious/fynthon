import os
import subprocess
import json
import hashlib
import hmac
import sqlite3
from flask import Flask, request, render_template_string

app = Flask(__name__)

# 1. Hardcoded secret key (Embedded Secret)
SECRET_KEY = "my$ecretK3y"  # Vulnerability: Hardcoded sensitive information

# 2. Hardcoded database credentials (Embedded Secret)
DB_USERNAME = "admin"  # Vulnerability: Hardcoded username
DB_PASSWORD = "password123"  # Vulnerability: Hardcoded password

# 3. Insecure password hashing
def insecure_hash(password):
    return hashlib.md5(password.encode()).hexdigest()  # Vulnerability: MD5 is outdated and insecure

# 4. SQL Injection vulnerability
@app.route('/user/<username>')
def get_user(username):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    query = f"SELECT * FROM users WHERE username = '{username}'"  # Vulnerability: Unsanitized input in SQL query
    cursor.execute(query)
    user = cursor.fetchone()
    conn.close()
    return f"User: {user}"

# 5. Command Injection vulnerability
@app.route('/ping', methods=['POST'])
def ping():
    host = request.form['host']
    command = f"ping -c 1 {host}"  # Vulnerability: Unsanitized input in shell command
    response = subprocess.check_output(command, shell=True)
    return response

# 6. Insecure deserialization
@app.route('/load', methods=['POST'])
def load():
    data = request.data
    obj = json.loads(data)  # Safe deserialization of untrusted input
    return f"Loaded object: {obj}"

# 7. Cross-Site Scripting (XSS) vulnerability
@app.route('/greet')
def greet():
    name = request.args.get('name', 'Guest')
    template = "<h1>Hello, {}!</h1>"  # Vulnerability: Unsanitized input in HTML output
    return render_template_string(template.format(name))

# 8. Insecure HMAC comparison
def verify_signature(data, signature):
    computed_signature = hmac.new(SECRET_KEY.encode(), data.encode(), hashlib.sha256).hexdigest()
    if computed_signature == signature:  # Vulnerability: Insecure direct string comparison
        return True
    return False

# 9. Use of eval() with untrusted input
@app.route('/calc')
def calculate():
    expression = request.args.get('expression', '0')
    result = eval(expression)  # Vulnerability: Executing untrusted input
    return f"Result: {result}"

# 10. Insecure random number generation
def generate_token():
    return os.urandom(8).hex()  # Vulnerability: Insufficient length for cryptographic token

if __name__ == '__main__':
    app.run(debug=True)

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <openssl/md5.h>
#include <sqlite3.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

// 1. Hardcoded secret key (Embedded Secret)
const string SECRET_KEY = "my$ecretK3y"; // Vulnerability: Hardcoded sensitive information

// 2. Hardcoded database credentials (Embedded Secret)
const string DB_USERNAME = "admin";      // Vulnerability: Hardcoded username
const string DB_PASSWORD = "password123"; // Vulnerability: Hardcoded password

// 3. Insecure password hashing
string insecure_hash(const string& password) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)password.c_str(), password.size(), (unsigned char*)&digest);
    char mdString[33];
    for (int i = 0; i < 16; ++i)
        sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
    return string(mdString);
}

// 4. SQL Injection vulnerability
void get_user(const string& username) {
    sqlite3* db;
    sqlite3_open("users.db", &db);
    string query = "SELECT * FROM users WHERE username = '" + username + "';"; // Vulnerability: Unsanitized input in SQL query
    char* errMsg = 0;
    sqlite3_exec(db, query.c_str(), 0, 0, &errMsg);
    if (errMsg) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);
}

// 5. Command Injection vulnerability
void ping(const string& host) {
    string command = "ping -c 1 " + host; // Vulnerability: Unsanitized input in system command
    system(command.c_str());
}

// 6. Insecure deserialization
void load(const string& data) {
    FILE* file = fopen("temp.dat", "wb");
    fwrite(data.c_str(), 1, data.size(), file);
    fclose(file);
    file = fopen("temp.dat", "rb");
    char buffer[256];
    fread(buffer, 1, sizeof(buffer), file); // Vulnerability: Deserializing untrusted input
    fclose(file);
    cout << "Loaded data: " << buffer << endl;
}

// 7. Cross-Site Scripting (XSS) vulnerability
void greet(const string& name) {
    cout << "<h1>Hello, " << name << "!</h1>" << endl; // Vulnerability: Unsanitized input in HTML output
}

// 8. Insecure HMAC comparison
bool verify_signature(const string& data, const string& signature) {
    unsigned char* digest = HMAC(EVP_md5(), SECRET_KEY.c_str(), SECRET_KEY.size(),
                                 (unsigned char*)data.c_str(), data.size(), NULL, NULL);
    char mdString[33];
    for (int i = 0; i < 16; ++i)
        sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
    return signature == string(mdString); // Vulnerability: Insecure direct string comparison
}

// 9. Use of system() with untrusted input
void calculate(const string& expression) {
    string command = "echo $(( " + expression + " ))"; // Vulnerability: Executing untrusted input
    system(command.c_str());
}

// 10. Insecure random number generation
string generate_token() {
    char token[9];
    for (int i = 0; i < 8; ++i)
        token[i] = 'A' + rand() % 26; // Vulnerability: rand() is not cryptographically secure
    token[8] = '\0';
    return string(token);
}

int main() {
    // Example usage of the vulnerable functions
    string username = "user1";
    get_user(username);

    string host = "example.com";
    ping(host);

    string data = "example data";
    load(data);

    string name = "<script>alert('XSS');</script>";
    greet(name);

    string password = "password";
    cout << "Insecure hash: " << insecure_hash(password) << endl;

    string expression = "1 + 2";
    calculate(expression);

    cout << "Generated token: " << generate_token() << endl;

    string signature = "d41d8cd98f00b204e9800998ecf8427e";
    if (verify_signature(data, signature)) {
        cout << "Signature verified." << endl;
    } else {
        cout << "Invalid signature." << endl;
    }

    return 0;
}

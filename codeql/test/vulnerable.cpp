#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <openssl/md5.h>
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

    string host = "example.com";
    ping(host);

    string data = "example data";
    load(data);

    string name = "<script>alert('XSS');</script>";
    greet(name);

    string password = "password";

    string expression = "1 + 2";
    calculate(expression);

    cout << "Generated token: " << generate_token() << endl;

    string signature = "d41d8cd98f00b204e9800998ecf8427e";

    return 0;
}

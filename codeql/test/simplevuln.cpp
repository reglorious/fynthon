#include <iostream>
#include <cstring>
#include <cstdlib>

void vulnerableFunction(const char* userInput) {
    char buffer[10];

    // 1. Buffer Overflow Vulnerability
    std::strcpy(buffer, userInput); // Unsafe copying of user input to buffer
    std::cout << "Buffer content: " << buffer << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input>" << std::endl;
        return 1;
    }

    const char* userInput = argv[1];

    // 2. Command Injection Vulnerability
    char command[256];
    std::snprintf(command, sizeof(command), "echo %s", userInput);
    std::system(command); // Executes command constructed from user input

    // 3. Insecure Environment Variable Usage
    const char* secret = std::getenv("SECRET_KEY"); // Retrieves secret from environment
    if (secret) {
        std::cout << "Secret Key: " << secret << std::endl;
    } else {
        std::cerr << "SECRET_KEY not set." << std::endl;
    }

    // Call the function with the user input
    vulnerableFunction(userInput);

    return 0;
}

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include "../include/Parser.h"

void printUsage() {
    std::cout << "Usage:\n"
              << "  For evaluation:\n"
              << "    program --eval \"expression\" --with var1=val1,var2=val2,...\n"
              << "  For differentiation:\n"
              << "    program --diff \"expression\" --by variable\n"
              << "Example:\n"
              << "  program --eval \"x + 3 * y\" --with x=3,y=4\n"
              << "  program --diff \"x + 3 * y\" --by x\n";
}

std::map<std::string, double> parseVariables(const std::string& vars) {
    std::map<std::string, double> result;
    std::stringstream ss(vars);
    std::string pair;
    
    while (std::getline(ss, pair, ',')) {
        size_t pos = pair.find('=');
        if (pos == std::string::npos) {
            throw std::runtime_error("Invalid variable format. Use var=value");
        }
        
        std::string var = pair.substr(0, pos);
        std::string val = pair.substr(pos + 1);
        
        // Trim whitespace
        var.erase(0, var.find_first_not_of(" \t"));
        var.erase(var.find_last_not_of(" \t") + 1);
        val.erase(0, val.find_first_not_of(" \t"));
        val.erase(val.find_last_not_of(" \t") + 1);
        
        try {
            result[var] = std::stod(val);
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid number format for variable " + var);
        }
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printUsage();
        return 1;
    }
    
    std::string mode = argv[1];
    std::string expression = argv[2];
    std::string option = argv[3];
    
    try {
        if (mode == "--eval" && option == "--with") {
            if (argc != 5) {
                throw std::runtime_error("Missing variable values");
            }
            
            auto variables = parseVariables(argv[4]);
            auto expr = Parser::parse(expression);
            double result = expr->evaluate(variables);
            std::cout << "Result: " << result << std::endl;
            
        } else if (mode == "--diff" && option == "--by") {
            if (argc != 5) {
                throw std::runtime_error("Missing variable to differentiate by");
            }
            
            std::string diffVar = argv[4];
            auto expr = Parser::parse(expression);
            auto diff = expr->differentiate(diffVar);
            std::cout << "Derivative: " << diff->to_string() << std::endl;
            
        } else {
            throw std::runtime_error("Invalid command line arguments");
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        printUsage();
        return 1;
    }
    
    return 0;
} 
-#include <iostream>
#include <vector>
#include <string>
#include <sstream>

enum class TokenType {
    IDENTIFIER,
    OPERATOR,
    PARENTHESIS
};

struct SymbolTableEntry {
    int registro;
    std::string nombre;
    TokenType tipo;
    std::string ambito;
};

class SymbolTable {
private:
    std::vector<SymbolTableEntry> entries;
    int registroCount;

public:
    SymbolTable() : registroCount(1) {}

    void insert(const std::string& nombre, TokenType tipo, const std::string& ambito) {
        SymbolTableEntry entry;
        entry.registro = registroCount++;
        entry.nombre = nombre;
        entry.tipo = tipo;
        entry.ambito = ambito;
        entries.push_back(entry);
    }

    SymbolTableEntry* lookup(const std::string& nombre) {
        for (int i = 0; i < entries.size(); ++i) {
            if (entries[i].nombre == nombre) {
                return &entries[i];
            }
        }
        return nullptr;
    }

    std::vector<SymbolTableEntry>& getEntries() {
        return entries;
    }
};

bool isOperator(char token) {
    return token == '+' || token == '-' || token == '*' || token == '/';
}

bool isParenthesis(char token) {
    return token == '(' || token == ')';
}

int main() {
    SymbolTable table;
    std::string entrada;

    std::cout << "Ingresa una expresión algebraica: ";
    std::getline(std::cin, entrada);

    std::vector<std::string> tokens;
    std::string token;
    TokenType currentTokenType = TokenType::IDENTIFIER;

    for (char c : entrada) {
        if (c == ' ') {
            continue;
        }

        if (isOperator(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, c));
            currentTokenType = TokenType::OPERATOR;
        } else if (isParenthesis(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(std::string(1, c));
            currentTokenType = TokenType::PARENTHESIS;
        } else {
            token += c;
            currentTokenType = TokenType::IDENTIFIER;
        }
    }

    if (!token.empty()) {
        tokens.push_back(token);
    }

    for (const auto& token : tokens) {
        TokenType tipo;
        std::string ambito;

        if (isOperator(token[0])) {
            tipo = TokenType::OPERATOR;
            ambito = "Ámbito";
        } else if (isParenthesis(token[0])) {
            tipo = TokenType::PARENTHESIS;
            ambito = "Ámbito";
        } else {
            tipo = TokenType::IDENTIFIER;
            ambito = "Ámbito";
        }

        table.insert(token, tipo, ambito);
    }

    std::cout << "\nTabla de símbolos:\n";
    for (const auto& entry : table.getEntries()) {
        std::string tipoStr;
        switch (entry.tipo) {
            case TokenType::IDENTIFIER:
                tipoStr = "Identificador";
                break;
            case TokenType::OPERATOR:
                tipoStr = "Operador";
                break;
            case TokenType::PARENTHESIS:
                tipoStr = "Paréntesis";
                break;
        }
        std::cout << "Registro: " << entry.registro << ", Nombre: " << entry.nombre << ", Tipo: " << tipoStr << ", Ámbito: " << entry.ambito << "\n";
    }

    return 0;
}


#include <iostream>
#include <stack>
#include <sstream>
#include <cmath> // Untuk pow
#include <stdexcept> // Untuk std::runtime_error
using namespace std;

class Stack {
public:
    void push(int val) {
        s.push(val);
    }
    
    int pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty. Cannot pop.");
        }
        int val = s.top();
        s.pop();
        return val;
    }
    
    bool isEmpty() {
        return s.empty();
    }

private:
    stack<int> s;
};

int evaluasiPostfix(const string& ekspresi) {
    Stack stack;
    stringstream ss(ekspresi);
    string token;

    cout << "Langkah-langkah evaluasi:\n";

    while (ss >> token) {
        if (isdigit(token[0])) {
            stack.push(stoi(token));
            cout << "Push: " << token << endl;
        } else {
            if (stack.isEmpty()) {
                throw runtime_error("Invalid expression: insufficient operands.");
            }
            int b = stack.pop();
            cout << "Pop: " << b << endl;

            if (stack.isEmpty()) {
                throw runtime_error("Invalid expression: insufficient operands.");
            }
            int a = stack.pop();
            cout << "Pop: " << a << endl;

            int result;
            switch (token[0]) {
                case '+': 
                    result = a + b; 
                    cout << "Evaluate: " << a << " + " << b << " = " << result << endl;
                    break;
                case '-': 
                    result = a - b; 
                    cout << "Evaluate: " << a << " - " << b << " = " << result << endl;
                    break;
                case '*': 
                    result = a * b; 
                    cout << "Evaluate: " << a << " * " << b << " = " << result << endl;
                    break;
                case '/':
                    if (b == 0) {
                        throw runtime_error("Error: Division by zero.");
                    }
                    result = a / b; 
                    cout << "Evaluate: " << a << " / " << b << " = " << result << endl;
                    break;
                case '^': 
                    result = pow(a, b); 
                    cout << "Evaluate: " << a << " ^ " << b << " = " << result << endl;
                    break;
                default:
                    throw runtime_error("Error: Unknown operator " + token);
            }
            stack.push(result);
            cout << "Push result: " << result << endl;
        }
    }

    if (stack.isEmpty()) {
        throw runtime_error("Invalid expression: no result in stack.");
    }
    return stack.pop();
}

int main() {
    string ekspresi;
    cout << "Masukkan ekspresi postfix (misal: '3 4 + 2 * 7 /'): ";
    getline(cin, ekspresi);
    
    try {
        int hasil = evaluasiPostfix(ekspresi);
        cout << "Hasil evaluasi: " << hasil << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}

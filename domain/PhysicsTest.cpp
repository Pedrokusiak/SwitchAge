#include "Physics.h"
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <limits>

class TestSuite {
private:
    std::vector<std::pair<std::string, std::function<bool()>>> tests;
    int passedTests = 0;
    int totalTests = 0;

public:
    void addTest(const std::string& name, std::function<bool()> test) {
        tests.push_back({name, test});
    }

    void runTests() {
        for (const auto& test : tests) {
            std::cout << "Running test: " << test.first << "... ";
            if (test.second()) {
                std::cout << "PASSED" << std::endl;
                passedTests++;
            } else {
                std::cout << "FAILED" << std::endl;
            }
            totalTests++;
        }

        std::cout << "\nTest results: " << passedTests << " passed out of " << totalTests << " total tests." << std::endl;
    }
};

bool almostEqual(float a, float b, float epsilon = 0.0001f) {
    return std::fabs(a - b) < epsilon;
}

bool vectorAlmostEqual(const Vector2D& a, const Vector2D& b, float epsilon = 0.0001f) {
    return almostEqual(a.x, b.x, epsilon) && almostEqual(a.y, b.y, epsilon);
}

int main() {
    TestSuite suite;

    // Soma vetores
    suite.addTest("Vector2D Addition Test", []() {
        Vector2D v1(1, 2);
        Vector2D v2(3, 4);
        Vector2D result = v1 + v2;
        return result.x == 4 && result.y == 6;
    });

    // Multiplicação de vetor por escalar
    suite.addTest("Vector2D Scalar Multiplication Test", []() {
        Vector2D v(2, 3);
        Vector2D result = v * 2;
        return result.x == 4 && result.y == 6;
    });

    // Divisão de vetor por escalar
    suite.addTest("Vector2D Scalar Division Test", []() {
        Vector2D v(4, 6);
        Vector2D result = v / 2;
        return result.x == 2 && result.y == 3;
    });

    // Divisão de vetor por zero
    suite.addTest("Vector2D Division by Zero Test", []() {
        Vector2D v(4, 6);
        Vector2D result = v / 0;
        return std::isinf(result.x) && std::isinf(result.y);
    });
    
    // Construtor da classe Physics
    suite.addTest("Physics Constructor Test", []() {
        Physics physics(Vector2D(0, -9.8), 1.0);
        return vectorAlmostEqual(physics.getGravity(), Vector2D(0, -9.8)) &&
               almostEqual(physics.getMass(), 1.0) &&
               vectorAlmostEqual(physics.getVelocity(), Vector2D(0, 0));
    });

    // Aplicação de força em Physics
    suite.addTest("Physics Apply Force Test", []() {
        Physics physics(Vector2D(0, -9.8), 1.0);
        physics.applyForce(Vector2D(10, 0));
        physics.update(1.0);
        return vectorAlmostEqual(physics.getVelocity(), Vector2D(10, 0));
    });

    // Atualização de Physics com base no tempo
    suite.addTest("Physics Update Test", []() {
        Physics physics(Vector2D(0, -9.8), 1.0);
        physics.update(2.0);
        return vectorAlmostEqual(physics.getVelocity(), Vector2D(0, 0));
    });

    // Teste dos setters de Physics
    suite.addTest("Physics Setters Test", []() {
        Physics physics(Vector2D(0, -9.8), 1.0);
        physics.setVelocity(Vector2D(5, 5));
        physics.setGravity(Vector2D(0, -10));
        physics.setForce(Vector2D(2, 2));
        return vectorAlmostEqual(physics.getVelocity(), Vector2D(5, 5)) &&
               vectorAlmostEqual(physics.getGravity(), Vector2D(0, -10));
    });

    // Teste de exceção ao criar Physics com massa zero
    suite.addTest("Physics Zero Mass Test", []() {
        try {
            Physics physics(Vector2D(0, -9.8), 0.0);
            return false; // Não deve alcançar esta linha
        } catch (const std::invalid_argument&) {
            return true; // Exceção lançada corretamente
        }
    });

    suite.runTests();

    return 0;
}

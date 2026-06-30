#include <iostream>
#include <cmath>
#include <vector>

int main() {
    float a, b, c;
    const float eps = 1e-6f;

    std::cout << "Enter a, b, c: ";
    if (!(std::cin >> a >> b >> c)) {
        std::cerr << "Invalid input!\n";
        return 1;
    }

    // 1. Проверка: это вообще квадратное уравнение?
    if (std::fabs(a) < eps) {
        std::cout << "Not a quadratic equation (a ≈ 0).\n";
        return 0;
    }

    // --- ЛАЙФХАК 1: a + b + c == 0 → корни 1 и c/a ---
    if (std::fabs(a + b + c) < eps) {
        float x1 = 1.0f;
        float x2 = c / a;
        std::cout << "[Special] a+b+c=0: x1 = " << x1 << ", x2 = " << x2 << "\n";
        return 0;
    }

    // --- ЛАЙФХАК 2: a + c == b → корни -1 и -c/a ---
    if (std::fabs((a + c) - b) < eps) {
        float x1 = -1.0f;
        float x2 = -c / a;
        std::cout << "[Special] a+c=b: x1 = " << x1 << ", x2 = " << x2 << "\n";
        return 0;
    }

    // --- ЛАЙФХАК 3: Виет + «Переброска» (работает для целых корней при a != 1) ---
    {
        float ac = a * c;
        int b_int = static_cast<int>(std::round(b));
        int ac_int = static_cast<int>(std::round(ac));

        if (std::fabs(b - b_int) < eps && std::fabs(ac - ac_int) < eps && ac_int != 0) {
            std::vector<int> divisors;
            for (int d = 1; d <= std::abs(ac_int); ++d) {
                if (ac_int % d == 0) {
                    divisors.push_back(d);
                    divisors.push_back(-d);
                }
            }

            bool found = false;
            for (int y1 : divisors) {
                int y2 = ac_int / y1;
                if (std::fabs(static_cast<float>(y1 + y2) + b) < eps) {
                    float x1 = static_cast<float>(y1) / a;
                    float x2 = static_cast<float>(y2) / a;
                    std::cout << "[Vieta+Throw] Found integer roots via throw: x1 = " 
                              << x1 << ", x2 = " << x2 << "\n";
                    found = true;
                    break;
                }
            }
            if (found) return 0;
        } 
        else if (std::fabs(ac) < eps) {
            if (std::fabs(b) > eps) {
                float x1 = 0.0f;
                float x2 = -b / a;
                std::cout << "[Vieta+Throw] ac=0 case: x1 = " << x1 << ", x2 = " << x2 << "\n";
                return 0;
            } else {
                std::cout << "[Vieta+Throw] All zeroes case: x = 0 (double root)\n";
                return 0;
            }
        }
    }

    // --- ЛАЙФХАК 4: Чётный коэффициент b → D/4 ---
    bool use_d4 = false;
    float b_half = 0.0f;

    float b_rounded = std::round(b);
    if (std::fabs(b - b_rounded) < eps && std::fmod(b_rounded, 2.0) == 0.0) {
        use_d4 = true;
        b_half = b_rounded / 2.0f;
    }

    float discriminant = 0.0f; // Это будет либо D, либо D/4

    if (use_d4) {
        discriminant = b_half * b_half - a * c; // D/4
        std::cout << "[Method] Using D/4 because b is even. D/4 = " << discriminant << "\n";
    } else {
        discriminant = b * b - 4.0f * a * c;    // D
        std::cout << "[Method] Using standard discriminant D = " << discriminant << "\n";
    }

    // --- ОБРАБОТКА КОРНЕЙ (включая комплексные) ---
    
    if (discriminant < -eps) {
        // Комплексные корни
        float realPart = -b / (2.0f * a);
        float imagPart;
        
        if (use_d4) {
            imagPart = std::sqrt(-discriminant) / a;
        } else {
            imagPart = std::sqrt(-discriminant) / (2.0f * a);
        }

        std::cout << "Complex roots:\n";
        std::cout << "  x1 = " << realPart << " + " << imagPart << "i\n";
        std::cout << "  x2 = " << realPart << " - " << imagPart << "i\n";
    } 
    else if (std::fabs(discriminant) <= eps) {
        // Один корень (дискриминант ≈ 0)
        float x;
        if (use_d4) {
            x = -b_half / a;
        } else {
            x = -b / (2.0f * a);
        }
        std::cout << "One real root (double): x = " << x << "\n";
    } 
    else {
        // Два вещественных корня
        float sqrtVal = std::sqrt(discriminant);
        float x1, x2;

        if (use_d4) {
            x1 = (-b_half + sqrtVal) / a;
            x2 = (-b_half - sqrtVal) / a;
        } else {
            x1 = (-b + sqrtVal) / (2.0f * a);
            x2 = (-b - sqrtVal) / (2.0f * a);
        }
        std::cout << "Two real roots: x1 = " << x1 << ", x2 = " << x2 << "\n";
    }

    return 0;
}

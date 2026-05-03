#include "simple_calculation/basic_ops.h"
#include "global_constants.h"
#include <stdexcept>
#include <cmath>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <chrono>

namespace huka {
namespace math {

// ================== 自由函数 ==================
double add(double a, double b) { return a + b; }
double subtract(double a, double b) { return a - b; }
double multiply(double a, double b) { return a * b; }
double divide(double a, double b) {
    if (b == 0.0) throw std::invalid_argument("division by zero");
    return a / b;
}
int factorial(int n) {
    if (n < 0) throw std::invalid_argument("negative factorial");
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// ================== ElementaryMath ==================
double ElementaryMath::add(double a, double b) { return a + b; }
double ElementaryMath::subtract(double a, double b) { return a - b; }
double ElementaryMath::multiply(double a, double b) { return a * b; }
double ElementaryMath::divide(double a, double b) {
    if (b == 0.0) throw std::invalid_argument("division by zero");
    return a / b;
}
int ElementaryMath::factorial(int n) {
    if (n < 0) throw std::invalid_argument("negative factorial");
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
int ElementaryMath::gcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}
int ElementaryMath::lcm(int a, int b) {
    return (a == 0 || b == 0) ? 0 : (a / gcd(a, b)) * b;
}
bool ElementaryMath::isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

// ================== JuniorMath ==================
double JuniorMath::power(double base, double exp) { return std::pow(base, exp); }
double JuniorMath::sqrt(double x) {
    if (x < 0) throw std::invalid_argument("sqrt of negative number");
    return std::sqrt(x);
}
double JuniorMath::cbrt(double x) { return std::cbrt(x); }
double JuniorMath::sin(double r)  { return std::sin(r); }
double JuniorMath::cos(double r)  { return std::cos(r); }
double JuniorMath::tan(double r)  { return std::tan(r); }
double JuniorMath::asin(double x) { return std::asin(x); }
double JuniorMath::acos(double x) { return std::acos(x); }
double JuniorMath::atan(double x) { return std::atan(x); }
double JuniorMath::log(double x) {
    if (x <= 0) throw std::invalid_argument("log of non-positive");
    return std::log(x);
}
double JuniorMath::log10(double x) {
    if (x <= 0) throw std::invalid_argument("log10 of non-positive");
    return std::log10(x);
}
double JuniorMath::degToRad(double d) { return d * constants::pi() / 180.0; }
double JuniorMath::radToDeg(double r) { return r * 180.0 / constants::pi(); }

// ================== TimeCalculator ==================
long long TimeCalculator::currentTimeMillis() {
    auto now = std::chrono::system_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}
long long TimeCalculator::currentTimeSeconds() {
    return static_cast<long long>(std::time(nullptr));
}
long long TimeCalculator::parseToMillis(const std::string& s, const std::string& fmt) {
    std::tm tm = {};
    std::istringstream ss(s);
    ss >> std::get_time(&tm, fmt.c_str());
    if (ss.fail()) throw std::invalid_argument("Time format mismatch");
    std::time_t t = std::mktime(&tm);
    return static_cast<long long>(t) * 1000LL;
}
std::string TimeCalculator::formatFromMillis(long long ms, const std::string& fmt) {
    std::time_t sec = static_cast<std::time_t>(ms / 1000LL);
    std::tm* tm = std::localtime(&sec);
    if (!tm) throw std::runtime_error("localtime failed");
    std::ostringstream oss;
    oss << std::put_time(tm, fmt.c_str());
    return oss.str();
}
long long TimeCalculator::secToMillis(long long s) { return s * constants::sec_millis(); }
long long TimeCalculator::millisToSec(long long ms) { return ms / constants::sec_millis(); }

// ================== CurrencyConverter ==================
static const std::unordered_map<int, double>& rateTable() {
    static const std::unordered_map<int, double> tbl = {
        {CurrencyConverter::CNY, 1.0},
        {CurrencyConverter::USD, 7.05},
        {CurrencyConverter::EUR, 7.85},
        {CurrencyConverter::JPY, 0.052},
        {CurrencyConverter::GBP, 9.10},
        {CurrencyConverter::KRW, 0.0053},
        {CurrencyConverter::AUD, 4.70},
        {CurrencyConverter::CAD, 5.20},
        {CurrencyConverter::CHF, 7.60},
        {CurrencyConverter::HKD, 0.90}
    };
    return tbl;
}

double CurrencyConverter::rateToCNY(int country_id) {
    const auto& tbl = rateTable();
    auto it = tbl.find(country_id);
    if (it == tbl.end()) throw std::invalid_argument("Unknown country ID");
    return it->second;
}

double CurrencyConverter::convert(double amount, int from_country, int to_country) {
    double fromRate = rateToCNY(from_country);
    double toRate   = rateToCNY(to_country);
    return amount * fromRate / toRate;
}

} // namespace math
} // namespace huka

#pragma once

#include <string>

namespace huka {
namespace math {

// 原有自由函数（向后兼容）
double add(double a, double b);
double subtract(double a, double b);
double multiply(double a, double b);
double divide(double a, double b);
int factorial(int n);

// 小学计算类
class ElementaryMath {
public:
    static double add(double a, double b);
    static double subtract(double a, double b);
    static double multiply(double a, double b);
    static double divide(double a, double b);
    static int factorial(int n);
    static int gcd(int a, int b);
    static int lcm(int a, int b);
    static bool isPrime(int n);
};

// 初中计算类
class JuniorMath {
public:
    static double power(double base, double exp);
    static double sqrt(double x);
    static double cbrt(double x);
    static double sin(double radians);
    static double cos(double radians);
    static double tan(double radians);
    static double asin(double x);
    static double acos(double x);
    static double atan(double x);
    static double log(double x);
    static double log10(double x);
    static double degToRad(double degrees);
    static double radToDeg(double radians);
};

// 时间计算类
class TimeCalculator {
public:
    static long long currentTimeMillis();
    static long long currentTimeSeconds();
    static long long parseToMillis(const std::string& timeStr,
                                   const std::string& format = "%Y-%m-%d %H:%M:%S");
    static std::string formatFromMillis(long long millis,
                                        const std::string& format = "%Y-%m-%d %H:%M:%S");
    static long long secToMillis(long long sec);
    static long long millisToSec(long long millis);
};

// 货币转换类（通过国家ID）
class CurrencyConverter {
public:
    // 国家ID定义
    static const int CNY = 0;
    static const int USD = 1;
    static const int EUR = 2;
    static const int JPY = 3;
    static const int GBP = 4;
    static const int KRW = 5;
    static const int AUD = 6;
    static const int CAD = 7;
    static const int CHF = 8;
    static const int HKD = 9;

    // 将金额从 from_country 转换为 to_country 的货币
    static double convert(double amount, int from_country, int to_country);

    // 获取指定国家对人民币的汇率 (1 外币 = ? CNY)
    static double rateToCNY(int country_id);
};

} // namespace math
} // namespace huka
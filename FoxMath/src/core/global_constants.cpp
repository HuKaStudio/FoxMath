#include "global_constants.h"

namespace {

// ========== 内部数学常量 ==========
const double PI            = 3.14159265358979323846;
const double E             = 2.71828182845904523536;
const double GOLDEN_RATIO  = 1.61803398874989484820;
const double SQRT2         = 1.41421356237309504880;

// ========== 内部物理常量 ==========
const double C             = 299792458.0;               // 光速 m/s
const double JULIAN_YEAR_S = 365.25 * 24 * 3600;        // 儒略年秒数
const double LY            = C * JULIAN_YEAR_S;         // 光年 (m)
const double H             = 6.62607015e-34;            // 普朗克常数 J·s
const double NA            = 6.02214076e23;             // 阿伏伽德罗常数 mol⁻¹

// ========== 内部时间常量 ==========
const long long SEC_MS   = 1000LL;
const long long MIN_MS   = 60LL * SEC_MS;              // 60,000
const long long HOUR_MS  = 60LL * MIN_MS;              // 3,600,000
const long long DAY_MS   = 24LL * HOUR_MS;             // 86,400,000
const long long MONTH_MS = 30LL * DAY_MS;              // 2,592,000,000
const long long YEAR_MS  = 365LL * DAY_MS;             // 31,536,000,000

} // anonymous namespace

namespace huka {
namespace constants {

// 数学常量
double pi()             { return PI; }
double e()              { return E; }
double golden_ratio()   { return GOLDEN_RATIO; }
double sqrt2()          { return SQRT2; }

// 物理常量
double speed_of_light()  { return C; }
double light_year()      { return LY; }
double planck_constant() { return H; }
double avogadro_constant() { return NA; }

// 时间常量
long long sec_millis()   { return SEC_MS; }
long long min_millis()   { return MIN_MS; }
long long hour_millis()  { return HOUR_MS; }
long long day_millis()   { return DAY_MS; }
long long month_millis() { return MONTH_MS; }
long long year_millis()  { return YEAR_MS; }

} // namespace constants
} // namespace huka
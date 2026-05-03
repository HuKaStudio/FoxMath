#pragma once

namespace huka {
namespace constants {

// ========== 数学常量 ==========
double pi();                // 圆周率 π
double e();                 // 自然常数 e
double golden_ratio();      // 黄金分割率 φ ≈ 1.6180339887
double sqrt2();             // 毕达哥拉斯常数 √2

// ========== 物理常量 ==========
double speed_of_light();    // 真空光速 c，单位：m/s
double light_year();        // 光年，单位：m（1 ly = c × 一年秒数，按儒略年 365.25 天）
double planck_constant();   // 普朗克常数 h，单位：J·s
double avogadro_constant(); // 阿伏伽德罗常数 NA，单位：mol⁻¹

// ========== 时间常量（毫秒） ==========
long long sec_millis();     // 1 秒 = 1,000 毫秒
long long min_millis();     // 1 分 = 60,000 毫秒
long long hour_millis();    // 1 时 = 3,600,000 毫秒
long long day_millis();     // 1 天 = 86,400,000 毫秒
long long month_millis();   // 1 月（30天）= 2,592,000,000 毫秒
long long year_millis();    // 1 年（365天）= 31,536,000,000 毫秒

} // namespace constants
} // namespace huka
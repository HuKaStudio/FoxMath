#include <jni.h>
#include <string>
#include <algorithm>
#include <cstring>
#include <stdexcept>
#include <cmath>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "simple_calculation/basic_ops.h"
#include "global_constants.h"

using namespace huka::math;
using namespace huka::constants;

static void handleCppException(JNIEnv* env) {
    try { throw; }
    catch (const std::invalid_argument& e) { env->ThrowNew(env->FindClass("java/lang/IllegalArgumentException"), e.what()); }
    catch (const std::runtime_error& e)   { env->ThrowNew(env->FindClass("java/lang/RuntimeException"), e.what()); }
    catch (...)                           { env->ThrowNew(env->FindClass("java/lang/RuntimeException"), "Unknown native error"); }
}

// ==================== Native 函数实现 ====================

// 全局常量
static jdouble JNICALL n_pi(JNIEnv*, jclass) { return pi(); }
static jdouble JNICALL n_e(JNIEnv*, jclass) { return e(); }
static jdouble JNICALL n_golden(JNIEnv*, jclass) { return golden_ratio(); }
static jdouble JNICALL n_sqrt2(JNIEnv*, jclass) { return sqrt2(); }
static jdouble JNICALL n_c(JNIEnv*, jclass) { return speed_of_light(); }
static jdouble JNICALL n_ly(JNIEnv*, jclass) { return light_year(); }
static jdouble JNICALL n_h(JNIEnv*, jclass) { return planck_constant(); }
static jdouble JNICALL n_na(JNIEnv*, jclass) { return avogadro_constant(); }
static jlong   JNICALL n_sec(JNIEnv*, jclass) { return sec_millis(); }
static jlong   JNICALL n_min(JNIEnv*, jclass) { return min_millis(); }
static jlong   JNICALL n_hour(JNIEnv*, jclass) { return hour_millis(); }
static jlong   JNICALL n_day(JNIEnv*, jclass) { return day_millis(); }
static jlong   JNICALL n_month(JNIEnv*, jclass) { return month_millis(); }
static jlong   JNICALL n_year(JNIEnv*, jclass) { return year_millis(); }

// 小学
static jdouble JNICALL n_add(JNIEnv*, jclass, jdouble a, jdouble b) { return ElementaryMath::add(a,b); }
static jdouble JNICALL n_sub(JNIEnv*, jclass, jdouble a, jdouble b) { return ElementaryMath::subtract(a,b); }
static jdouble JNICALL n_mul(JNIEnv*, jclass, jdouble a, jdouble b) { return ElementaryMath::multiply(a,b); }
static jdouble JNICALL n_div(JNIEnv* env, jclass, jdouble a, jdouble b) {
    try { return ElementaryMath::divide(a,b); } catch(...) { handleCppException(env); return 0; }
}
static jint JNICALL n_fact(JNIEnv* env, jclass, jint n) {
    try { return ElementaryMath::factorial(n); } catch(...) { handleCppException(env); return 0; }
}
static jint JNICALL n_gcd(JNIEnv*, jclass, jint a, jint b) { return ElementaryMath::gcd(a,b); }
static jint JNICALL n_lcm(JNIEnv*, jclass, jint a, jint b) { return ElementaryMath::lcm(a,b); }
static jboolean JNICALL n_prime(JNIEnv*, jclass, jint n) { return ElementaryMath::isPrime(n); }

// 初中
static jdouble JNICALL n_pow(JNIEnv*, jclass, jdouble b, jdouble e) { return JuniorMath::power(b,e); }
static jdouble JNICALL n_sqrt(JNIEnv* env, jclass, jdouble x) {
    try { return JuniorMath::sqrt(x); } catch(...) { handleCppException(env); return 0; }
}
static jdouble JNICALL n_cbrt(JNIEnv*, jclass, jdouble x) { return JuniorMath::cbrt(x); }
static jdouble JNICALL n_sin(JNIEnv*, jclass, jdouble r) { return JuniorMath::sin(r); }
static jdouble JNICALL n_cos(JNIEnv*, jclass, jdouble r) { return JuniorMath::cos(r); }
static jdouble JNICALL n_tan(JNIEnv*, jclass, jdouble r) { return JuniorMath::tan(r); }
static jdouble JNICALL n_asin(JNIEnv*, jclass, jdouble x) { return JuniorMath::asin(x); }
static jdouble JNICALL n_acos(JNIEnv*, jclass, jdouble x) { return JuniorMath::acos(x); }
static jdouble JNICALL n_atan(JNIEnv*, jclass, jdouble x) { return JuniorMath::atan(x); }
static jdouble JNICALL n_log(JNIEnv* env, jclass, jdouble x) {
    try { return JuniorMath::log(x); } catch(...) { handleCppException(env); return 0; }
}
static jdouble JNICALL n_log10(JNIEnv* env, jclass, jdouble x) {
    try { return JuniorMath::log10(x); } catch(...) { handleCppException(env); return 0; }
}
static jdouble JNICALL n_d2r(JNIEnv*, jclass, jdouble d) { return JuniorMath::degToRad(d); }
static jdouble JNICALL n_r2d(JNIEnv*, jclass, jdouble r) { return JuniorMath::radToDeg(r); }

// 时间
static jlong JNICALL n_curMs(JNIEnv*, jclass) { return TimeCalculator::currentTimeMillis(); }
static jlong JNICALL n_curSec(JNIEnv*, jclass) { return TimeCalculator::currentTimeSeconds(); }
static jlong JNICALL n_parse(JNIEnv* env, jclass, jstring s, jstring fmt) {
    const char* str = env->GetStringUTFChars(s, nullptr);
    const char* f   = env->GetStringUTFChars(fmt, nullptr);
    try {
        jlong r = TimeCalculator::parseToMillis(str, f);
        env->ReleaseStringUTFChars(s, str);
        env->ReleaseStringUTFChars(fmt, f);
        return r;
    } catch(...) {
        env->ReleaseStringUTFChars(s, str);
        env->ReleaseStringUTFChars(fmt, f);
        handleCppException(env);
        return 0;
    }
}
static jstring JNICALL n_format(JNIEnv* env, jclass, jlong ms, jstring fmt) {
    const char* f = env->GetStringUTFChars(fmt, nullptr);
    try {
        std::string r = TimeCalculator::formatFromMillis(ms, f);
        env->ReleaseStringUTFChars(fmt, f);
        return env->NewStringUTF(r.c_str());
    } catch(...) {
        env->ReleaseStringUTFChars(fmt, f);
        handleCppException(env);
        return nullptr;
    }
}
static jlong JNICALL n_s2ms(JNIEnv*, jclass, jlong s) { return TimeCalculator::secToMillis(s); }
static jlong JNICALL n_ms2s(JNIEnv*, jclass, jlong ms) { return TimeCalculator::millisToSec(ms); }

// 货币
static jdouble JNICALL n_convert(JNIEnv* env, jclass, jdouble amount, jint from, jint to) {
    try { return CurrencyConverter::convert(amount, from, to); }
    catch(...) { handleCppException(env); return 0; }
}
static jdouble JNICALL n_rate(JNIEnv* env, jclass, jint id) {
    try { return CurrencyConverter::rateToCNY(id); }
    catch(...) { handleCppException(env); return 0; }
}

// ==================== 方法表（合并所有功能） ====================
static const JNINativeMethod gAllMethods[] = {
    // 名字与 Java 中 private native 一致
    {"native_pi",               "()D",  (void*)n_pi},
    {"native_e",                "()D",  (void*)n_e},
    {"native_goldenRatio",      "()D",  (void*)n_golden},
    {"native_sqrt2",            "()D",  (void*)n_sqrt2},
    {"native_speedOfLight",     "()D",  (void*)n_c},
    {"native_lightYear",        "()D",  (void*)n_ly},
    {"native_planckConstant",   "()D",  (void*)n_h},
    {"native_avogadroConstant", "()D",  (void*)n_na},
    {"native_secMillis",        "()J",  (void*)n_sec},
    {"native_minMillis",        "()J",  (void*)n_min},
    {"native_hourMillis",       "()J",  (void*)n_hour},
    {"native_dayMillis",        "()J",  (void*)n_day},
    {"native_monthMillis",      "()J",  (void*)n_month},
    {"native_yearMillis",       "()J",  (void*)n_year},

    {"native_add",        "(DD)D", (void*)n_add},
    {"native_subtract",   "(DD)D", (void*)n_sub},
    {"native_multiply",   "(DD)D", (void*)n_mul},
    {"native_divide",     "(DD)D", (void*)n_div},
    {"native_factorial",  "(I)I",  (void*)n_fact},
    {"native_gcd",        "(II)I", (void*)n_gcd},
    {"native_lcm",        "(II)I", (void*)n_lcm},
    {"native_isPrime",    "(I)Z",  (void*)n_prime},

    {"native_power",     "(DD)D", (void*)n_pow},
    {"native_sqrt",      "(D)D",  (void*)n_sqrt},
    {"native_cbrt",      "(D)D",  (void*)n_cbrt},
    {"native_sin",       "(D)D",  (void*)n_sin},
    {"native_cos",       "(D)D",  (void*)n_cos},
    {"native_tan",       "(D)D",  (void*)n_tan},
    {"native_asin",      "(D)D",  (void*)n_asin},
    {"native_acos",      "(D)D",  (void*)n_acos},
    {"native_atan",      "(D)D",  (void*)n_atan},
    {"native_log",       "(D)D",  (void*)n_log},
    {"native_log10",     "(D)D",  (void*)n_log10},
    {"native_degToRad",  "(D)D",  (void*)n_d2r},
    {"native_radToDeg",  "(D)D",  (void*)n_r2d},

    {"native_currentTimeMillis", "()J", (void*)n_curMs},
    {"native_currentTimeSeconds","()J", (void*)n_curSec},
    {"native_parseToMillis",     "(Ljava/lang/String;Ljava/lang/String;)J", (void*)n_parse},
    {"native_formatFromMillis",  "(JLjava/lang/String;)Ljava/lang/String;", (void*)n_format},
    {"native_secToMillis",       "(J)J", (void*)n_s2ms},
    {"native_millisToSec",       "(J)J", (void*)n_ms2s},

    {"native_convert",  "(DII)D", (void*)n_convert},
    {"native_rateToCNY","(I)D",   (void*)n_rate}
};

// ==================== JNI_OnLoad：自动发现调用者并全量注册 ====================
extern "C" jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/) {
    JNIEnv* env = nullptr;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) return JNI_ERR;

    // 1. 获取调用栈，定位到 System.loadLibrary 的调用者
    jclass threadClass = env->FindClass("java/lang/Thread");
    jmethodID curThread = env->GetStaticMethodID(threadClass, "currentThread", "()Ljava/lang/Thread;");
    jobject thread = env->CallStaticObjectMethod(threadClass, curThread);
    jmethodID getStack = env->GetMethodID(threadClass, "getStackTrace", "()[Ljava/lang/StackTraceElement;");
    jobjectArray stack = (jobjectArray)env->CallObjectMethod(thread, getStack);
    jsize len = env->GetArrayLength(stack);

    jclass steClass = env->FindClass("java/lang/StackTraceElement");
    jmethodID getClsName = env->GetMethodID(steClass, "getClassName", "()Ljava/lang/String;");

    jclass callerClass = nullptr;
    for (int i = 0; i < len; ++i) {
        jobject elem = env->GetObjectArrayElement(stack, i);
        jstring clsName = (jstring)env->CallObjectMethod(elem, getClsName);
        const char* cname = env->GetStringUTFChars(clsName, nullptr);
        if (strcmp(cname, "java.lang.System") == 0 && i + 1 < len) {
            jobject next = env->GetObjectArrayElement(stack, i + 1);
            jstring nextCls = (jstring)env->CallObjectMethod(next, getClsName);
            const char* nname = env->GetStringUTFChars(nextCls, nullptr);
            std::string internal(nname);
            std::replace(internal.begin(), internal.end(), '.', '/');
            callerClass = env->FindClass(internal.c_str());
            env->ReleaseStringUTFChars(nextCls, nname);
            env->DeleteLocalRef(nextCls);
            env->DeleteLocalRef(next);
            break;
        }
        env->ReleaseStringUTFChars(clsName, cname);
        env->DeleteLocalRef(clsName);
        env->DeleteLocalRef(elem);
    }
    env->DeleteLocalRef(stack);
    env->DeleteLocalRef(thread);

    if (callerClass == nullptr) return JNI_ERR;

    // 2. 一次性注册所有 native 方法到调用者类
    if (env->RegisterNatives(callerClass, gAllMethods,
                             sizeof(gAllMethods)/sizeof(gAllMethods[0])) != 0) {
        return JNI_ERR;
    }

    return JNI_VERSION_1_6;
}
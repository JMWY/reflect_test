/*================================================================
*   Copyright (C) meituan.com 2018-08 All rights reserved.
*   文件名称：type.h
*   创 建 者：liyangguang
*   创建日期：2018年08月09日
*   描    述：
================================================================*/

#ifndef SF_TEXT_TEMPLATE_H_
#define SF_TEXT_TEMPLATE_H_

#include <stdio.h>
#include <string.h>
#include <json/json.h>

#include <string>
#include <set>
#include <map>
#include <vector>
#include <utility>

struct BasicST {
    virtual bool setVal(Json::Value& json_val) = 0;  // NOLINT
    virtual void getValueToJson(Json::Value& dest) const = 0;  // NOLINT
    virtual int sunserial(const std::string& src) = 0;
    virtual void sserial(std::string& dest) const = 0;  // NOLINT
};

static inline void print(const int16_t id, const char* key = 0) {
    printf("%s=%d;", key, id);
}
/*
static inline void print(const int id, const char* key = 0) {
    printf("%s=%d;", key, id);
}
*/
static inline void print(const uint32_t id, const char* key = 0) {
    printf("%s=%u;", key, id);
}
static inline void print(const int32_t id, const char* key = 0) {
    printf("%s=%d;", key, id);
}
static inline void print(const uint64_t id, const char* key = 0) {
    printf("%s=%lu;", key, id);
}
static inline void print(const int64_t id, const char* key = 0) {
    printf("%s=%ld;", key, id);
}
static inline void print(const long long int id, const char* key = 0) {  // NOLINT
    printf("%s=%lld;", key, id);
}
static inline void print(const double val, const char* key = 0) {
    printf("%s=%lf;", key, val);
}
static inline void print(const float val, const char* key = 0) {
    printf("%s=%f;", key, val);
}
static inline void print(const std::string p, const char* key = 0) {
    printf("%s=%s;", key, p.c_str());
}

static inline void print(const BasicST& v, const char* key = 0) {}

template <class T>
static inline void print(const std::vector<T> p, const char* key = 0);

template <class T>
static inline void print(const std::set<T> p, const char* key = 0);

template <class T_KEY, class T_VAL>
static inline void print(const std::map<T_KEY, T_VAL> p, const char* key = 0);

template <class T_KEY, class T_VAL>
static inline void print(const std::pair<T_KEY, T_VAL> p, const char* key = 0);

static inline void sprint(std::string& dest, const int16_t id, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=%d;", key, id);
    dest.append(buff);
}
/*
static inline void sprint(std::string& dest, const int id, const char* key = 0) {
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=%d;", key, id);
    dest.append(buff);
}
*/
static inline void sprint(std::string& dest, const uint32_t id, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=%u;", key, id);
    dest.append(buff);
}
static inline void sprint(std::string& dest, const int32_t id, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=%d;", key, id);
    dest.append(buff);
}
static inline void sprint(std::string& dest, const uint64_t id, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=%lu;", key, id);
    dest.append(buff);
}
static inline void sprint(std::string& dest, const double val, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=%lf;", key, val);
    dest.append(buff);
}
static inline void sprint(std::string& dest, const float val, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=%f;", key, val);
    dest.append(buff);
}
static inline void sprint(std::string& dest, const std::string p, const char* key = 0) {  // NOLINT
    char buff[102400];
    snprintf(buff, sizeof(buff), "%s=%s;", key, p.c_str());
    dest.append(buff);
}

static inline void sprint(std::string& dest, const BasicST& p, const char* key = 0) {  // NOLINT
}

template <class T>
static inline void sprint(std::string& dest, const std::vector<T> p, const char* key = 0);  // NOLINT

template <class T>
static inline void sprint(std::string& dest, const std::set<T> p, const char* key = 0);  // NOLINT

template <class T_KEY, class T_VAL>
static inline void sprint(std::string& dest, const std::map<T_KEY, T_VAL> p, const char* key = 0);  // NOLINT

template <class T_KEY, class T_VAL>
static inline void sprint(std::string& dest, const std::pair<T_KEY, T_VAL> p, const char* key = 0);  // NOLINT

template <class T>
static inline void sprint(std::string& dest, const std::vector<T> p, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=[", key);
    dest.append(buff);
    for (typename std::vector<T>::const_iterator it = p.begin(); it != p.end();
         ++it) {
        sprint(dest, *it);
        dest.append(";");
    }
    dest.append("]");
}

template <class T>
static inline void sprint(std::string& dest, const std::set<T> p, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s=[", key);
    dest.append(buff);
    for (typename std::set<T>::const_iterator it = p.begin(); it != p.end(); ++it) {
        sprint(dest, *it);
        dest.append(";");
    }

    dest.append("];");
}

template <class T_KEY, class T_VAL>
static inline void sprint(std::string& dest, const std::map<T_KEY, T_VAL> p, const char* key = 0) {  // NOLINT
    char buff[1024];
    snprintf(buff, sizeof(buff), "%s={", key);
    dest.append(buff);
    for (typename std::map<T_KEY, T_VAL>::const_iterator it = p.begin();
         it != p.end(); ++it) {
        dest.append("(");
        sprint(dest, it->first, "key");
        sprint(dest, it->second, "val");
        dest.append(");");
    }
    dest.append("};");
}

template <class T_KEY, class T_VAL>
static inline void sprint(std::string& dest, const std::pair<T_KEY, T_VAL> p, const char* key = 0) {  // NOLINT
    char buff[1024];
    if (key) {
        snprintf(buff, sizeof(buff), "%s=<", key);
        dest.append(buff);
    } else {
        dest.append("<");
    }
    sprint(dest, p.first);
    sprint(dest, p.second);

    dest.append(">");
}

template <class T>
static inline bool serial(const std::vector<T>& src, std::string& dest);  // NOLINT

template <class T>
static inline int unserial(const std::string& src, int loc, std::vector<T>& dest);  // NOLINT

template <class T>
static inline bool serial(const std::set<T>& src, std::string& dest);  // NOLINT

template <class T>
static inline int unserial(const std::string& src, int loc, std::set<T>& dest);  // NOLINT

template <class T_KEY, class T_VAL>
static inline bool serial(const std::map<T_KEY, T_VAL>& src, std::string& dest);  // NOLINT

template <class T_KEY, class T_VAL>
static inline int unserial(const std::string& src, int loc, std::map<T_KEY, T_VAL>& dest);  // NOLINT

template <class T_KEY, class T_VAL>
static inline bool serial(const std::pair<T_KEY, T_VAL>& src, std::string& dest);  // NOLINT

template <class T_KEY, class T_VAL>
static inline int unserial(const std::string& src, int loc, std::pair<T_KEY, T_VAL>& dest);  // NOLINT

template <class T>
static inline void print(const std::vector<T> p, const char* key = 0) {
    printf("%s=[", key);
    for (typename std::vector<T>::const_iterator it = p.begin(); it != p.end();
         ++it) {
        print(*it);
        printf(";");
    }
    printf("];");
}

template <class T>
static inline void print(const std::set<T> p, const char* key = 0) {
    printf("%s=[", key);
    for (typename std::set<T>::const_iterator it = p.begin(); it != p.end(); ++it) {
        print(*it);
        printf(";");
    }
    printf("];");
}

template <class T_KEY, class T_VAL>
static inline void print(const std::map<T_KEY, T_VAL> p, const char* key = 0) {
    printf("%s={", key);
    for (typename std::map<T_KEY, T_VAL>::const_iterator it = p.begin();
         it != p.end(); ++it) {
        printf("(");
        print(it->first, "key");
        print(it->second, "val");
        printf(");");
    }
    printf("};");
}

template <class T_KEY, class T_VAL>
static inline void print(const std::pair<T_KEY, T_VAL> p, const char* key = 0) {
    if (key) {
        printf("%s=<", key);
    } else {
        printf("<");
    }
    print(p.first);
    print(p.second);
    printf(">");
}

#define process_build_in_type(build_in_type)                                                         \
static inline bool serial(const build_in_type id, std::string& dest) {                               \
    dest.append((const char*)&id, sizeof(build_in_type));                                            \
    return true;                                                                                     \
}                                                                                                    \
static inline int unserial(const std::string& src, int loc, build_in_type& dest) {                   \
    memcpy(reinterpret_cast<void*>(&dest), (const void*)(src.c_str() + loc), sizeof(build_in_type)); \
    return sizeof(build_in_type);                                                                    \
}

process_build_in_type(bool)
process_build_in_type(int8_t)
process_build_in_type(uint8_t)
process_build_in_type(int16_t)
process_build_in_type(uint16_t)
process_build_in_type(uint32_t)
process_build_in_type(int32_t)
process_build_in_type(uint64_t)
process_build_in_type(int64_t)
process_build_in_type(long long int)
process_build_in_type(float)
process_build_in_type(double)

/*
static inline bool serial(const int id, std::string& dest) {
    dest.append((const char*)&id, sizeof(int));
    return true;
}

static inline int unserial(const std::string& src, int loc, int& dest) {
    memcpy(reinterpret_cast<void*>(&dest), (const void*)(src.c_str() + loc), sizeof(int));
    return sizeof(int);
}
*/


static inline bool serial(const std::string& str, std::string& dest) {  // NOLINT
    int len = str.size();
    if (len <= 0) {
        len = 0;
        serial(len, dest);
        return true;
    }
    serial(len, dest);
    dest.append(str);
    return true;
}

static inline int unserial(const std::string& src, int loc, std::string& dest) {  // NOLINT
    int len = 0;
    int cur_loc = loc;
    cur_loc += unserial(src, loc, len);
    dest.clear();
    if (len == 0) {
        return sizeof(int);
    }
    dest.reserve(len);
    dest.append(src, cur_loc, len);
    return len + sizeof(int);
}

static inline bool serial(const BasicST& src, std::string& dest) {  // NOLINT
    std::string temp;
    src.sserial(temp);
    dest.append(temp);
    return true;
}
static inline int unserial(const std::string& src, int loc, BasicST& dest) {  // NOLINT
    int cur_loc = loc;
    std::string temp(src.begin() + loc, src.end());
    cur_loc += dest.sunserial(temp);
    return cur_loc - loc;
}

template <class T>
static inline bool serial(const std::vector<T>& src, std::string& dest) {  // NOLINT
    int len = src.size();
    serial(len, dest);
    for (typename std::vector<T>::const_iterator it = src.begin(); it != src.end();
         ++it) {
        serial(*it, dest);
    }
    return true;
}

template <class T>
static inline int unserial(const std::string& src, int loc, std::vector<T>& dest) {  // NOLINT
    dest.clear();
    T t;
    int len = 0;
    int cur_loc = loc;
    cur_loc += unserial(src, cur_loc, len);
    if (len == 0) {
        return cur_loc - loc;
    }
    dest.reserve(len);
    for (int i = 0; i < len; ++i) {
        cur_loc += unserial(src, cur_loc, t);
        dest.push_back(t);
    }
    return cur_loc - loc;
}

template <class T>
static inline bool serial(const std::set<T>& src, std::string& dest) {  // NOLINT
    int len = src.size();
    serial(len, dest);
    for (typename std::set<T>::const_iterator it = src.begin(); it != src.end();
         ++it) {
        serial(*it, dest);
    }
    return true;
}

template <class T>
static inline int unserial(const std::string& src, int loc, std::set<T>& dest) {  // NOLINT
    dest.clear();
    T t;
    int len = 0;
    int cur_loc = loc;
    cur_loc += unserial(src, cur_loc, len);
    for (int i = 0; i < len; ++i) {
        cur_loc += unserial(src, cur_loc, t);
        dest.insert(dest.end(), t);
    }
    return cur_loc - loc;
}

template <class T_KEY, class T_VAL>
static inline bool serial(const std::map<T_KEY, T_VAL>& src, std::string& dest) {  // NOLINT
    int len = src.size();
    serial(len, dest);
    for (typename std::map<T_KEY, T_VAL>::const_iterator it = src.begin();
         it != src.end(); ++it) {
        serial(it->first, dest);
        serial(it->second, dest);
    }
    return true;
}

template <class T_KEY, class T_VAL>
static inline int unserial(const std::string& src, int loc, std::map<T_KEY, T_VAL>& dest) {  // NOLINT
    dest.clear();
    T_KEY key;
    T_VAL val;

    int len = 0;
    int cur_loc = loc;
    cur_loc += unserial(src, cur_loc, len);
    for (int i = 0; i < len; ++i) {
        cur_loc += unserial(src, cur_loc, key);
        cur_loc += unserial(src, cur_loc, val);
        dest.insert(dest.end(), std::make_pair(key, val));
    }
    return cur_loc - loc;
}

template <class T_KEY, class T_VAL>
static inline bool serial(const std::pair<T_KEY, T_VAL>& src, std::string& dest) {  // NOLINT
    serial(src.first, dest);
    serial(src.second, dest);
    return true;
}

template <class T_KEY, class T_VAL>
static inline int unserial(const std::string& src, int loc, std::pair<T_KEY, T_VAL>& dest) {  // NOLINT
    int cur_loc = loc;
    cur_loc += unserial(src, cur_loc, dest.first);
    cur_loc += unserial(src, cur_loc, dest.second);
    return cur_loc - loc;
}

#endif  // SF_TEXT_TEMPLATE_H_

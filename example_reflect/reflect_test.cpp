/*================================================================
*   Copyright (C) meituan.com 2018-08 All rights reserved.
*   文件名称：type.h
*   创 建 者：liyangguang
*   创建日期：2018年08月09日
*   描    述：
================================================================*/
#include <stdint.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include "template.h"
#include <gtest/gtest.h>
using std::string;

union FieldData {
    bool    bool_value;
    int     int_value;
    int64_t int64_t_value;
    float   float_value;
    double  double_value;
    void*   ptr_value;
};

#define SET_VALUE(data, type, val)                                     \
    do {                                                               \
        data.type##_value = val;                                         \
    } while (0)

#define SET_DATA(data, type, val)           \
    do {                                    \
        memcpy(&(data), &(val), sizeof(type)); \
    } while (0)

#define SET_OBJ(data, p_obj)           \
    do {                                    \
        memcpy(&(data), &(p_obj), sizeof(void*)); \
    } while (0)


enum EnumType {
    BOOL = 0,
    INT32,
    INT64,
    DOUBLE,
    STRING,
    LIST_INT32,
    LIST_INT64,
    LIST_UINT64,
    LIST_FLOAT,
    LIST_DOUBLE,
    LIST_STRING,
    LIST_PAIR_STRING_STRING,
    LIST_PAIR_STRING_INT32,
    LIST_PAIR_INT32_INT32,
    LIST_PAIR_INT32_STRING,
    MAP_INT32_INT32,
    MAP_INT32_FLOAT,
    MAP_INT32_DOUBLE,
    MAP_INT32_STRING,
    MAP_STRING_STRING,
    TYPE_END
};

#define RELEASE(p_data)      \
      do {                   \
          std::cout << __FUNCTION__ << "\tfree memory:" << dest << std::endl; \
          if (p_data) {      \
              delete p_data;  \
              p_data = NULL;  \
          }\
      } while(0)

#define ReturnIfCheckedNull(pointer, ret_val)       \
      do {                                          \
          if (!pointer) {return ret_val;}           \
      } while(0)

//addParseType(string)
int serial_string(FieldData& data, std::string& s) {
    std::string* dest = *(string**)(&data);
    std::cout << "befor " << __FUNCTION__ << '\t' << *dest << std::endl;
    serial(*dest, s);
    std::cout << "after " << __FUNCTION__ << '\t' << s << std::endl;
    return 0;
}
int unserial_string(string& s, FieldData& data) {
    std::string* dest = *(string**)(&data);
    std::cout << "befor " << __FUNCTION__ << '\t' << *dest << std::endl;
    unserial(s, 0, *dest);
    std::cout << "after " << __FUNCTION__ << '\t' << *dest << std::endl;
    return 0;
}
void free_string(FieldData& data) {
    std::string* dest = *(string**)(&data);
    RELEASE(dest);
}

#define addParseType(type)                            \
    int serial_ ## type(FieldData& data, std::string& s) { \
      std::cout << "befor " << __FUNCTION__ << '\t' << *(type*)&data << std::endl; \
      serial(*(type*)&data, s);                        \
      std::cout << "after " << __FUNCTION__ << '\t' << s << std::endl;            \
      return 0;                                       \
    }                                                 \
    int unserial_ ## type(string& s, FieldData& data) {    \
      std::cout << "befor " << __FUNCTION__ << '\t' << *(type*)&data << std::endl; \
      unserial(s, 0, *(type*)&data);                   \
      std::cout << "after " << __FUNCTION__ << '\t' << *(type*)&data << std::endl; \
      return 0;                                       \
    } \
    void free_ ## type(FieldData& data) {\
    }

#define addParseVector(type)                                                     \
    int serial_vector_ ## type(FieldData& data, std::string& s) {                     \
      std::vector<type>* dest = *(std::vector<type>**)(&data);          \
      std::cout << "befor " << __FUNCTION__ << '\t' << dest->at(0) << std::endl;                 \
      serial(*dest, s);                                                           \
      std::cout << "after " << __FUNCTION__ << '\t' << s << std::endl;            \
      return 0;                                                                  \
    }                                                                            \
    int unserial_vector_ ## type(std::string& s, FieldData& data) {                   \
        std::vector<type>* dest = *(std::vector<type>**)(&data);          \
        std::cout << "befor " << __FUNCTION__ << '\t' << dest->size() << std::endl;             \
        dest->clear();                                                              \
        unserial(s, 0, *dest);                                                      \
        std::cout << "after " << __FUNCTION__ << '\t' << dest->size() << '\t' << dest->at(0) << std::endl;  \
        return 0;                                                                  \
    }                                                                       \
    void free_vector_ ## type(FieldData& data) {\
        std::vector<type>* dest = *(std::vector<type>**)(&data);          \
        RELEASE(dest); \
    }

#define addParseVectorPair(type1, type2)                                                                    \
    int serial_vector_ ## type1 ##_## type2(FieldData& data, std::string& s) {                                   \
        auto* dest = *(std::vector<std::pair<type1,type2>>**)(&data); \
        ReturnIfCheckedNull(dest, -1);                                                                        \
        std::cout << "befor " << __FUNCTION__ << '\t' << dest->at(0).first << '\t' << dest->at(0).second << std::endl;\
        serial(*dest, s);                                                                                      \
        std::cout << "after " << __FUNCTION__ << '\t' << s << std::endl;                                      \
        return 0;                                                                                             \
    }                                                                                                       \
    int unserial_vector_ ## type1 ##_## type2(std::string& s, FieldData& data) {                                 \
        auto* dest = *(std::vector<std::pair<type1,type2>>**)(&data); \
        ReturnIfCheckedNull(dest, -1);                                                                        \
        std::cout << "befor " << __FUNCTION__ << '\t' << dest->size() << std::endl;                            \
        dest->clear();                                                                                         \
        unserial(s, 0, *dest);                                                                                 \
        std::cout << "after " << __FUNCTION__ << '\t' << dest->at(0).first << '\t' << dest->at(0).second << std::endl;\
        return 0;                                                                                             \
    } \
    void free_vector_ ## type1 ##_## type2(FieldData& data) {  \
        auto* dest = *(std::vector<std::pair<type1,type2>>**)(&data);           \
        RELEASE(dest); \
    }

#define addParseMap(key_type, value_type)                                                             \
    int serial_map_ ## key_type ##_## value_type(FieldData& data, string& s) {                             \
      std::map<key_type, value_type>* dest = *(std::map<key_type, value_type>**)(&data);     \
      ReturnIfCheckedNull(dest, -1);                                                                        \
      std::cout << __FUNCTION__ << '\t' << dest << std::endl;                                        \
      serial(*dest, s);                                                                                \
      return 0;                                                                                       \
    }                                                                                                 \
    int unserial_map_ ## key_type ##_## value_type(string& s, FieldData& data) {                           \
      std::map<key_type, value_type>* dest = *(std::map<key_type, value_type>**)(&data);     \
      ReturnIfCheckedNull(dest, -1);                                                                    \
      std::cout << __FUNCTION__ << '\t' << dest << std::endl;                                        \
      dest->clear();                                                                                   \
      unserial(s, 0, *dest);                                                                           \
      return 0;                                                                                       \
    } \
    void free_map_ ## key_type ##_## value_type(FieldData& data) {  \
        auto* dest = *(std::map<key_type, value_type>**)(&data);           \
        RELEASE(dest); \
    }

addParseType(bool)
addParseType(int32_t)
addParseType(int64_t)
addParseType(double)

addParseVector(int32_t)
addParseVector(int64_t)
addParseVector(double)
addParseVector(string)
addParseVectorPair(int32_t, int32_t)
addParseVectorPair(string, int32_t)
addParseVectorPair(string, string)
addParseVectorPair(int32_t, string)

addParseMap(string, string)
addParseMap(int32_t, int32_t)
addParseMap(int32_t, double)

typedef int (*SerialFunc) (FieldData&, std::string&);
typedef int (*UnserialFunc) (std::string&, FieldData&);
typedef std::string (*ToString) (FieldData&);
typedef void (*ReleaseFunc) (FieldData&);
typedef struct {
   SerialFunc serial;
   UnserialFunc unserial;
   ReleaseFunc free;
   // ToString to_string;
} ParseFunctions;

class ParseFunctionsFactory {
public:
    static ParseFunctions create(EnumType type) {
        switch (type) {
            case BOOL:
                return {serial_bool, unserial_bool};
            case INT32:
                return {serial_int32_t, unserial_int32_t};
            case INT64:
                return {serial_int64_t, unserial_int64_t};
            case DOUBLE:
                return {serial_double, unserial_double};
            case STRING:
                return {serial_string, unserial_string, free_string};
            case LIST_INT32:
                return {serial_vector_int32_t, unserial_vector_int32_t, free_vector_int32_t};
            case LIST_INT64:
                return {serial_vector_int64_t, unserial_vector_int64_t, free_vector_int64_t};
            case LIST_DOUBLE:
                return {serial_vector_double, unserial_vector_double, free_vector_double};
            case LIST_STRING:
                return {serial_vector_string, unserial_vector_string, free_vector_string};
            case LIST_PAIR_STRING_STRING:
                return {serial_vector_string_string, unserial_vector_string_string, free_vector_string_string};
            case LIST_PAIR_STRING_INT32:
                return {serial_vector_string_int32_t, unserial_vector_string_int32_t, free_vector_string_int32_t};
            case LIST_PAIR_INT32_INT32:
                return {serial_vector_int32_t_int32_t, unserial_vector_int32_t_int32_t, free_vector_int32_t_int32_t};
            case LIST_PAIR_INT32_STRING:
                return {serial_vector_int32_t_string, unserial_vector_int32_t_string, free_vector_int32_t_string};
            case MAP_INT32_INT32:
                return {serial_map_int32_t_int32_t, unserial_map_int32_t_int32_t, free_map_int32_t_int32_t};
            case MAP_INT32_DOUBLE:
                return {serial_map_int32_t_double, unserial_map_int32_t_double, free_map_int32_t_double};
            case MAP_STRING_STRING:
                return {serial_map_string_string, unserial_map_string_string, free_map_string_string};
            default:
                return {NULL};
        }
    }
};

struct Field {
    EnumType type;
    FieldData data;
    Field(): type(TYPE_END) {
        memset(&data, 0, sizeof(data));
    }
};

/*******************************************************************/

class ReflectionTest: public ::testing::Test {
public:
    virtual void SetUp() {
      //***************** type reflect to parse functions *******//
      for (size_t i = 0; i < TYPE_END; ++i) {
          type2funs[i] = ParseFunctionsFactory::create(EnumType(i));
      }
     
      //  ***************** parse field type in configure *********//
      //  type_parse["i32"] = INT32;
      //  type_parse["i64"] = INT64;
      //  type_parse["double"] = DOUBLE;
      //  type_parse["string"] =  STRING;
    }
    virtual void TearDown() {}
  
    void* setDefaultValue(Field* field) {
        switch(field->type) {
            case BOOL:
            case INT32:
            case INT64:
            case DOUBLE: return memset(&field->data, 0, sizeof(field));
            case STRING:
                (*(std::string**)(&(field->data)))->clear(); return NULL;
            case LIST_INT32:
                (*(std::vector<int32_t>**)(&(field->data)))->swap(std::vector<int32_t>());
                return NULL;
            case LIST_DOUBLE:
                (*(std::vector<double>**)(&(field->data)))->swap(std::vector<double>());
                return NULL;
            case LIST_STRING:
                (*(std::vector<string>**)(&(field->data)))->swap(std::vector<string>());
                return NULL;
            case LIST_PAIR_INT32_INT32:
                (*(std::vector<std::pair<int32_t,int32_t>>**)(&(field->data)))->swap(std::vector<std::pair<int32_t,int32_t>>());
                return NULL;
            case LIST_PAIR_INT32_STRING:
                (*(std::vector<std::pair<int32_t,string>>**)(&(field->data)))->swap(std::vector<std::pair<int32_t,string>>());
                return NULL;
            case LIST_PAIR_STRING_STRING:
                (*(std::vector<std::pair<string,string>>**)(&(field->data)))->swap(std::vector<std::pair<string,string>>());
                return NULL;
            case LIST_PAIR_STRING_INT32:
                (*(std::vector<std::pair<string,int32_t>>**)(&(field->data)))->swap(std::vector<std::pair<string,int32_t>>());
                return NULL;
            default: return NULL;
        }
    }

    ParseFunctions type2funs[TYPE_END];
    //  std::map<std::string, EnumType> type_parse;
};

TEST_F(ReflectionTest, basic_type_test) {
    std::string* p_sval = new std::string("99.999这里有2600万个poi");
    std::cout << "alloc memory:" << p_sval << std::endl;
    std::vector<Field> fields(4);
    fields[0].type = INT32;
    SET_VALUE(fields[0].data, int, 99999);
    fields[1].type = DOUBLE;
    SET_VALUE(fields[1].data, double, 999.99);
    fields[2].type = STRING;
    SET_OBJ(fields[2].data, p_sval);
    ASSERT_EQ(*(string**)(&fields[2].data), p_sval);
    fields[3].type = BOOL;
    SET_VALUE(fields[3].data, bool, true);
    
    std::vector<string> code_str(4);
    for (int i = 0; i < 4; ++i) {
        type2funs[fields[i].type].serial(fields[i].data, code_str[i]);
        setDefaultValue(&fields[i]);
    }
    EXPECT_NE(fields[0].data.int_value, 99999);
    EXPECT_NE(fields[1].data.double_value, 999.99);
    EXPECT_STRNE(p_sval ->c_str(), "99.999美团点评2600万个poi");
    EXPECT_FALSE(fields[3].data.bool_value);
    
    for (int i = 0; i < 4; ++i) {
        type2funs[fields[i].type].unserial(code_str[i], fields[i].data);
    }
    EXPECT_EQ(fields[0].data.int_value, 99999);
    EXPECT_DOUBLE_EQ(fields[1].data.double_value, 999.99);
    EXPECT_STREQ(p_sval ->c_str(), "99.999美团点评2600万个poi");
    EXPECT_TRUE(fields[3].data.bool_value);

    int free_count = 0;
    for (int i = 0; i < 4; ++i) {
        if (type2funs[fields[i].type].free) {
            std::cout << __LINE__ <<  " line: free type " << fields[i].type << std::endl;
            type2funs[fields[i].type].free(fields[i].data);
            free_count++;
        }
    }
    EXPECT_EQ(free_count, 1);
}

TEST_F(ReflectionTest, vector_test) {
    auto* p_vec_int = new std::vector<int32_t>(1, 12345678);
    std::cout << "alloc memory:" << p_vec_int << std::endl;
    auto* p_vec_dbl = new std::vector<double>(1, 12345.678);
    std::cout << "alloc memory:" << p_vec_dbl << std::endl;
    auto* p_vec_str = new std::vector<std::string>(1, "123.45678");
    std::cout << "alloc memory:" << p_vec_str << std::endl;
    auto* p_vec_ii = new std::vector<std::pair<int32_t, int32_t>>(1, std::make_pair(5, 666));
    std::cout << "alloc memory:" << p_vec_ii << std::endl;
    auto* p_vec_is = new std::vector<std::pair<int32_t, std::string>>(1, std::make_pair(6, "value:<int,string>"));
    std::cout << "alloc memory:" << p_vec_is << std::endl;
    auto* p_vec_ss = new std::vector<std::pair<std::string, std::string>>(1, std::make_pair("key:<string,string>",
                                                                                            "value:<string,string>"));
    std::cout << "alloc memory:" << p_vec_ss << std::endl;
    auto* p_vec_si = new std::vector<std::pair<std::string, int32_t>>(1, std::make_pair("key:<string,int>", 9999));
    std::cout << "alloc memory:" << p_vec_si << std::endl;

    std::vector<Field> fields(7);
    fields[0].type = LIST_INT32;
    SET_OBJ(fields[0].data, p_vec_int);
    ASSERT_EQ(*(std::vector<int32_t>**)(&fields[0].data), p_vec_int);
    fields[1].type = LIST_DOUBLE;
    SET_OBJ(fields[1].data, p_vec_dbl);
    fields[2].type = LIST_STRING;
    SET_OBJ(fields[2].data, p_vec_str);
    fields[3].type = LIST_PAIR_INT32_INT32;
    SET_OBJ(fields[3].data, p_vec_ii);
    ASSERT_EQ(*(std::vector<std::pair<int32_t, int32_t>>**)(&fields[3].data), p_vec_ii);
    fields[4].type = LIST_PAIR_INT32_STRING;
    SET_OBJ(fields[4].data, p_vec_is);
    fields[5].type = LIST_PAIR_STRING_STRING;
    SET_OBJ(fields[5].data, p_vec_ss);
    fields[6].type = LIST_PAIR_STRING_INT32;
    SET_OBJ(fields[6].data, p_vec_si);

    int free_count = 0;
    for (int i = 0; i < 7; ++i) {
        std::string s;
        type2funs[fields[i].type].serial(fields[i].data, s);
        setDefaultValue(&fields[i]);
        type2funs[fields[i].type].unserial(s, fields[i].data);
        if (type2funs[fields[i].type].free) {
            std::cout << __LINE__ <<  " line: free type " << fields[i].type << std::endl;
            type2funs[fields[i].type].free(fields[i].data);
            free_count++;
        }
    }
    EXPECT_EQ(free_count, 7);
}

TEST_F(ReflectionTest, map_test) {
    auto* p_i2i = new std::map<int, int>();
    std::cout << "alloc memory:" << p_i2i << std::endl;
    auto* p_i2d = new std::map<int, double>();
    std::cout << "alloc memory:" << p_i2d << std::endl;
    auto* p_s2s = new std::map<std::string, std::string>();
    std::cout << "alloc memory:" << p_s2s << std::endl;
    
    std::vector<Field> fields(3);
    fields[0].type = MAP_INT32_INT32;
    SET_OBJ(fields[0].data, p_i2i);
    ASSERT_EQ(*(std::map<int, int>**)(&fields[0].data), p_i2i);
    fields[1].type = MAP_INT32_DOUBLE;
    SET_OBJ(fields[1].data, p_i2d);
    fields[2].type = MAP_STRING_STRING;
    SET_OBJ(fields[2].data, p_s2s);

    int free_count = 0;
    for (int i = 0; i < 3; ++i) {
        std::string s;
        type2funs[fields[i].type].serial(fields[i].data, s);
        type2funs[fields[i].type].unserial(s, fields[i].data);
        if (type2funs[fields[i].type].free) {
            std::cout << __LINE__ <<  " line: free type " << fields[i].type << std::endl;
            type2funs[fields[i].type].free(fields[i].data);
            free_count++;
        }
    }
    EXPECT_EQ(free_count, 3);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


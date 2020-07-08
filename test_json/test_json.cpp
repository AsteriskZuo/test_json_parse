//
//  test_json.cpp
//  test_json
//
//  Created by zuoyu on 2020/7/8.
//  Copyright © 2020 zuoyu. All rights reserved.
//

#include "test_json.hpp"
#include "json.h"
#include <iostream>
#include <string>

static void test1();
static void test2();
static void test3();
void test_json()
{
    test3();
}

static void parse(const Json::Value& node);
static void test1()
{
    /**
     {
         // Use IntelliSense to learn about possible attributes.
         // Hover to view descriptions of existing attributes.
         // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
         "version": "0.2.0",
         "configurations": [
             {
                 "name": "Flutter: Attach to Device",
                 "type": "dart",
                 "request": "attach",
                 "program": "dart/example/lib/main.dart"
             },
             {
                 "name": "Dart",
                 "program": "bin/main.dart",
                 "request": "launch",
                 "type": "dart"
             }
         ]
     }
     */
    // write json format
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    Json::Value root;
    std::string errs;
    const char* json_data = "{\"version\":\"0.2.0\",\"configurations\":[{\"name\":\"Flutter: Attach to Device\",\"type\":\"dart\",\"request\":\"attach\",\"program\":\"dart/example/lib/main.dart\"},{\"name\":\"Dart\",\"program\":\"bin/main.dart\",\"request\":\"launch\",\"type\":\"dart\"}]}";
    bool ret = reader->parse(json_data, json_data + strlen(json_data), &root, &errs);
    if (false == ret) {
        std::cout << "error:" << errs.c_str() << std::endl;
    }
    parse(root);
}
static void parse(const Json::Value& node)
{
    for (auto iter = node.begin(); iter != node.end(); ++iter) {
        if (iter->empty()) {
            break;
        }
        Json::ValueType vt = iter->type();
        std::string name = iter.name();
        if (Json::ValueType::nullValue == vt) {
            Json::Value v = *iter;
        } else if (Json::ValueType::intValue == vt) {
            std::cout << __func__ << ":" << "name:" << name.c_str() << ":int:" << (int)iter->asInt() << std::endl;
        } else if (Json::ValueType::uintValue == vt) {
            std::cout << __func__ << ":" << "name:" << name.c_str() << ":uint:" << (unsigned int)iter->asUInt() << std::endl;
        } else if (Json::ValueType::realValue == vt) {
            std::cout << __func__ << ":" << "name:" << name.c_str() << ":double:" << (double)iter->asDouble() << std::endl;
        } else if (Json::ValueType::stringValue == vt) {
            std::string strv = iter->asString();
            std::cout << __func__ << ":" << "name:" << name.c_str() << ":cstr:" << strv.c_str() << std::endl;
        } else if (Json::ValueType::booleanValue == vt) {
            std::cout << __func__ << ":" << "name:" << name.c_str() << ":bool:" << (bool)iter->asBool() << std::endl;
        } else if (Json::ValueType::arrayValue == vt) {
            parse(*iter);
        } else if (Json::ValueType::objectValue == vt) {
            parse(*iter);
        } else {
            std::cout << __func__ << ":" << __LINE__ << "error type" << std::endl;
        }
    }
}
static void test2()
{
    char buffer[] = "haha";
    size_t buffer_size = strlen(buffer);
    char* start = buffer;
    char* end = buffer + buffer_size;
    size_t result = (size_t)(end - start);
    if (result == buffer_size) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "not ok" << std::endl;
    }
}

static void test3()
{
    /**
     {
         // Use IntelliSense to learn about possible attributes.
         // Hover to view descriptions of existing attributes.
         // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
         "version": "0.2.0",
         "configurations": [
             {
                 "name": "Flutter: Attach to Device",
                 "type": "dart",
                 "request": "attach",
                 "program": "dart/example/lib/main.dart"
             },
             {
                 "name": "Dart",
                 "program": "bin/main.dart",
                 "request": "launch",
                 "type": "dart"
             }
         ]
     }
     */
    
    Json::Value root;
    {
        root["version"] = "0.2.0";
        Json::Value configurations(Json::ValueType::arrayValue);
        Json::Value obj1(Json::ValueType::objectValue);
        obj1["name"] = "Flutter: Attach to Device";
        obj1["type"] = "dart";
        obj1["request"] = "attach";
        obj1["program"] = "dart/example/lib/main.dart";
        configurations[configurations.size()] = std::move(obj1);
        Json::Value obj2(Json::ValueType::objectValue);
        obj2["name"] = "Dart";
        obj2["type"] = "dart";
        obj2["request"] = "launch";
        obj2["program"] = "bin/main.dart";
        configurations[configurations.size()] = std::move(obj2);
        root["configurations"] = std::move(configurations);
    }

    std::string ret = Json::writeString(Json::StreamWriterBuilder(), root);
    std::cout << __func__ << ":" << __LINE__ << ret.c_str() << std::endl;
}

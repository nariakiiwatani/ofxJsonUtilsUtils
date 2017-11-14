#pragma once

#include "ofxJsonUtils.h"

#define kv1(name) #name, name
#define kv2(name, ...) kv(name), kv1(__VA_ARGS__)
#define kv3(name, ...) kv(name), kv2(__VA_ARGS__)
#define kv4(name, ...) kv(name), kv3(__VA_ARGS__)
#define kv5(name, ...) kv(name), kv4(__VA_ARGS__)
#define kv6(name, ...) kv(name), kv5(__VA_ARGS__)
#define kv7(name, ...) kv(name), kv6(__VA_ARGS__)
#define kv8(name, ...) kv(name), kv7(__VA_ARGS__)
#define kv9(name, ...) kv(name), kv8(__VA_ARGS__)
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,NAME,...) NAME
#define KV_COMMA_SEPARATION(...) GET_MACRO(__VA_ARGS__, kv9, kv8, kv7, kv6, kv5, kv4, kv3, kv2, kv1)(__VA_ARGS__)

#define JSON_FUNCS(...) \
void loadJson(const ofJson &json) {ofxJsonUtils::load(json, KV_COMMA_SEPARATION(__VA_ARGS__));}\
ofJson toJson() const { return ofxJsonUtils::create(KV_COMMA_SEPARATION(__VA_ARGS__));}

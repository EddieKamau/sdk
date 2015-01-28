// Copyright (c) 2015, the Fletch project authors. Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE.md file.

// Generated file. Do not edit.

#include "echo_service.h"
#include "include/service_api.h"

static ServiceId _service_id;

@implementation EchoService

+ (void)Setup {
  _service_id = kNoServiceId;
  _service_id = ServiceApiLookup("EchoService");
}

+ (void)TearDown {
  ServiceApiTerminate(_service_id);
  _service_id = kNoServiceId;
}

static const MethodId _kEchoId = (MethodId)1;

+ (int)Echo:(int)n {
  static const int kSize = 36;
  char _bits[kSize];
  char* _buffer = _bits;
  *(int*)(_buffer + 32) = n;
  ServiceApiInvoke(_service_id, _kEchoId, _buffer, kSize);
  return *(int*)(_buffer + 32);
}

static void Unwrap_Int32_1(void* raw) {
  typedef void (*cbt)(int);
  char* buffer = (char*)(raw);
  int result = *(int*)(buffer + 32);
  cbt callback = *(cbt*)(buffer + 36);
  free(buffer);
  callback(result);
}

+ (void)EchoAsync:(int)n WithCallback:(void (*)(int))callback {
  static const int kSize = 36 + sizeof(void*);
  char* _buffer = (char*)(malloc(kSize));
  *(int*)(_buffer + 32) = n;
  *(void**)(_buffer + 36) = (void*)(callback);
  ServiceApiInvokeAsync(_service_id, _kEchoId, Unwrap_Int32_1, _buffer, kSize);
}

static void Unwrap_Int32_1_Block(void* raw) {
  typedef void (^cbt)(int);
  char* buffer = (char*)(raw);
  int result = *(int*)(buffer + 32);
  cbt callback = *(cbt*)(buffer + 36);
  free(buffer);
  callback(result);
}

+ (void)EchoAsync:(int)n WithBlock:(void (^)(int))callback {
  static const int kSize = 36 + sizeof(void*);
  char* _buffer = (char*)(malloc(kSize));
  *(int*)(_buffer + 32) = n;
  *(void**)(_buffer + 36) = (void*)(callback);
  ServiceApiInvokeAsync(_service_id, _kEchoId, Unwrap_Int32_1_Block, _buffer, kSize);
}

static const MethodId _kSumId = (MethodId)2;

@end

// Copyright (c) 2015, the Dartino project authors. Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE.md file.

library dartino_compiler.dartino_context;

import 'package:compiler/src/tree/tree.dart' show
    Node;

import 'package:compiler/src/common/names.dart' show
    Names;

import 'package:compiler/src/elements/elements.dart' show
    ClassElement,
    Element,
    FieldElement,
    FunctionElement,
    FunctionSignature,
    LibraryElement,
    ParameterElement,
    Name;

import 'package:compiler/src/resolution/tree_elements.dart' show
    TreeElements;

import 'package:compiler/src/universe/selector.dart' show
    Selector;

import 'package:compiler/src/constants/expressions.dart' show
    ConstantExpression;

import 'package:compiler/src/constants/values.dart' show
    ConstantValue,
    ConstructedConstantValue,
    FunctionConstantValue;

import 'dartino_compiler_implementation.dart' show
    DartinoCompilerImplementation;

export 'dartino_compiler_implementation.dart' show
    DartinoCompilerImplementation;

import 'dartino_backend.dart' show
    DartinoBackend;

export 'dartino_backend.dart' show
    DartinoBackend;

export 'bytecode_assembler.dart' show
    BytecodeAssembler,
    BytecodeLabel;

import 'dartino_native_descriptor.dart' show
    DartinoNativeDescriptor;

import 'dartino_selector.dart' show
    DartinoSelector,
    SelectorKind;

export 'dartino_native_descriptor.dart' show
    DartinoNativeDescriptor;

import 'dartino_registry.dart' show
    DartinoRegistry;

class DartinoContext {
  final DartinoCompilerImplementation compiler;

  Map<String, DartinoNativeDescriptor> nativeDescriptors;

  DartinoContext(this.compiler);

  DartinoBackend get backend => compiler.backend;

  bool get enableBigint {
    String enableBigintConstant = compiler.environment['dartino.enable-bigint'];
    return enableBigintConstant != "false";
  }

  ConstantValue getConstantValue(ConstantExpression expression) {
    return compiler.constants.getConstantValue(expression);
  }
}

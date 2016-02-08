// Copyright (c) 2016, the Dartino project authors. Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE.md file.

#include "src/shared/assert.h"
#include "src/shared/test_case.h"

#include "src/vm/double_list.h"

namespace dartino {

class Base {
 public:
  explicit Base(int arg) : base(arg) {}

  int base;
};

class Item : public Base,
             public DoubleListEntry<Item>,
             public DoubleListEntry<Item, 2> {
 public:
  explicit Item(int arg0, int arg1) : Base(arg0), item(arg1) {}

  int item;
};

TEST_CASE(DOUBLE_LIST_MULTI_ENTRY_TEST) {
  Item a1(1, 11), a2(2, 12), a3(3, 13);

  DoubleList<Item> all;
  DoubleList<Item, 2> ready;

  EXPECT(all.IsEmpty());
  EXPECT(ready.IsEmpty());

  all.Append(&a2);
  all.Append(&a3);
  all.Prepend(&a1);
  EXPECT_EQ(all.First()->item, 11);
  EXPECT_EQ(all.Last()->item, 13);

  ready.Append(&a1);
  ready.Append(&a2);
  EXPECT_EQ(ready.First()->item, 11);
  EXPECT_EQ(ready.Last()->item, 12);

  int i = 0;
  for (auto it = all.Begin(); it != all.End(); ++it) {
    i++;
    EXPECT_EQ(it->base, i);
    EXPECT_EQ((*it)->base, i);
    EXPECT_EQ(it->item, 10 + i);
    EXPECT_EQ((*it)->item, 10 + i);
  }
  EXPECT_EQ(i, 3);

  i = 0;
  for (auto it = ready.Begin(); it != ready.End(); ++it) {
    i++;
    EXPECT_EQ(it->base, i);
    EXPECT_EQ((*it)->base, i);
    EXPECT_EQ(it->item, 10 + i);
    EXPECT_EQ((*it)->item, 10 + i);
  }
  EXPECT_EQ(i, 2);

  ready.Remove(&a1);
  ready.Remove(&a2);

  all.Remove(&a1);
  all.Remove(&a2);
  all.Remove(&a3);

  EXPECT(all.IsEmpty());
  EXPECT(ready.IsEmpty());
}

TEST_CASE(DOUBLE_LIST_REMOVE_FIRST_TEST) {
  Item a1(1, 11), a2(2, 12), a3(3, 13);

  DoubleList<Item> all;

  all.Append(&a2);
  all.Append(&a3);
  all.Prepend(&a1);

  EXPECT_EQ(&a1, all.RemoveFirst());
  EXPECT_EQ(&a2, all.RemoveFirst());
  EXPECT_EQ(&a3, all.RemoveFirst());

  EXPECT(all.IsEmpty());
}

TEST_CASE(DOUBLE_LIST_REMOVE_LAST_TEST) {
  Item a1(1, 11), a2(2, 12), a3(3, 13);

  DoubleList<Item> all;

  all.Append(&a2);
  all.Append(&a3);
  all.Prepend(&a1);

  EXPECT_EQ(&a3, all.RemoveLast());
  EXPECT_EQ(&a2, all.RemoveLast());
  EXPECT_EQ(&a1, all.RemoveLast());
  EXPECT(all.IsEmpty());
}

TEST_CASE(DOUBLE_LIST_IS_IN_LIST) {
  Item a1(1, 11), a2(2, 12), a3(3, 13);

  DoubleList<Item> all;

  all.Append(&a2);
  all.Append(&a3);
  all.Prepend(&a1);

  ASSERT(all.IsInList(&a1));
  ASSERT(all.IsInList(&a2));
  ASSERT(all.IsInList(&a3));

  EXPECT_EQ(&a1, all.RemoveFirst());
  EXPECT(!all.IsInList(&a1));
  EXPECT_EQ(&a3, all.RemoveLast());
  EXPECT(!all.IsInList(&a3));
  EXPECT_EQ(&a2, all.RemoveFirst());
  EXPECT(!all.IsInList(&a2));

  EXPECT(all.IsEmpty());
}

TEST_CASE(DOUBLE_LIST_ERASE_ITERATOR) {
  Item a1(1, 11), a2(2, 12), a3(3, 13);

  DoubleList<Item> all;

  all.Append(&a2);
  all.Append(&a3);
  all.Prepend(&a1);

  auto it = all.Begin();
  it = all.Erase(++it);
  EXPECT_EQ(*it, &a3);
  EXPECT_EQ(*it, all.Last());

  it = all.Erase(all.Begin());
  EXPECT_EQ(*it, &a3);
  EXPECT_EQ(*it, all.First());
  EXPECT_EQ(*it, all.Last());

  it = all.Erase(all.Begin());
  EXPECT(it == all.End());
  EXPECT(all.IsEmpty());
}

}  // namespace dartino.

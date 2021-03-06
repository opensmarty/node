// Copyright 2019 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_HEAP_COMBINED_HEAP_H_
#define V8_HEAP_COMBINED_HEAP_H_

#include "src/heap/heap.h"
#include "src/heap/read-only-heap.h"
#include "src/objects/objects.h"

namespace v8 {
namespace internal {

// This class allows iteration over the entire heap (Heap and ReadOnlyHeap). It
// uses the HeapIterator to iterate over non-read-only objects and accepts the
// same filtering option. (Interrupting iteration while filtering unreachable
// objects is still forbidden)
class V8_EXPORT_PRIVATE CombinedHeapIterator final {
 public:
  CombinedHeapIterator(Heap* heap,
                       HeapIterator::HeapObjectsFiltering filtering =
                           HeapIterator::HeapObjectsFiltering::kNoFiltering)
      : heap_iterator_(heap, filtering),
        ro_heap_iterator_(heap->read_only_heap()) {}
  HeapObject Next();

 private:
  HeapIterator heap_iterator_;
  ReadOnlyHeapIterator ro_heap_iterator_;
};

V8_WARN_UNUSED_RESULT inline bool IsValidHeapObject(Heap* heap,
                                                    HeapObject object) {
  return ReadOnlyHeap::Contains(object) || heap->Contains(object);
}

}  // namespace internal
}  // namespace v8

#endif  // V8_HEAP_COMBINED_HEAP_H_

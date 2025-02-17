/*
    File: weakHashTable.h
*/

/*
Copyright (c) 2014, Christian E. Schafmeister
 
CLASP is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.
 
See directory 'clasp/licenses' for full details.
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
/* -^- */
#ifndef _core_WeakKeyHashTable_H
#define _core_WeakKeyHashTable_H

#include <clasp/core/object.h>
#include <clasp/gctools/gcweak.h>
#include <clasp/core/symbolTable.h>
#include <clasp/core/hashTableBase.h>
#include <clasp/core/corePackage.fwd.h>

namespace cl {
  extern core::Symbol_sp& _sym_eq;
};


template <>
struct gctools::GCInfo<core::WeakKeyHashTable_O> {
  static bool constexpr NeedsInitialization = true;
  static bool constexpr NeedsFinalization = false;
  static GCInfo_policy constexpr Policy = normal;
};

namespace core {
FORWARD(WeakKeyHashTable);
class WeakKeyHashTable_O : public HashTableBase_O {
  LISP_CLASS(core, CorePkg, WeakKeyHashTable_O, "WeakKeyHashTable",HashTableBase_O);
public: // instance variables here
  typedef typename gctools::WeakKeyHashTable::value_type value_type;
  typedef typename gctools::WeakKeyHashTable::KeyBucketsType KeyBucketsType;
  typedef typename gctools::WeakKeyHashTable::ValueBucketsType ValueBucketsType;
  typedef typename gctools::WeakKeyHashTable::KeyBucketsAllocatorType KeyBucketsAllocatorType;
  typedef typename gctools::WeakKeyHashTable::ValueBucketsAllocatorType ValueBucketsAllocatorType;
  typedef gctools::WeakKeyHashTable HashTableType;
public: // Fields
  HashTableType _HashTable;
public:
  WeakKeyHashTable_O(size_t sz, Number_sp rehashSize, double rehashThreshold ) : _HashTable(sz,rehashSize, rehashThreshold) {};
  WeakKeyHashTable_O();
  void initialize() override; 
public:
  size_t hashTableCount() const override { return this->_HashTable.tableSize();};
  cl_index size() const { return this->hashTableCount(); };
  size_t hashTableSize() const override { return this->_HashTable.length();};

  T_sp hash_table_setf_gethash(T_sp key, T_sp value) override;

  bool fullp();

  void describe(T_sp stream) override;
  virtual T_sp hashTableTest() const { return cl::_sym_eq; };
  bool keyTest(T_sp entryKey, T_sp searchKey) const;

  gc::Fixnum sxhashKey(T_sp key, gc::Fixnum bound, bool willAddKey) const;

  void maphashLowLevel(std::function<void(T_sp, T_sp)> const &fn);
  void maphash(T_sp functionDesig) override; 

  T_mv gethash(T_sp key, T_sp defaultValue= nil<T_O>()) override;
  bool remhash(T_sp key) override;
  T_sp clrhash() override;
  Number_sp rehash_size() override;
  double rehash_threshold() override;
  T_sp hash_table_test() override;

  string __repr__() const override;
};
}; /* core */






namespace core {
WeakKeyHashTable_sp core__make_weak_key_hash_table(Fixnum_sp size);
};



#endif /* _core_WeakKeyHashTable_H */

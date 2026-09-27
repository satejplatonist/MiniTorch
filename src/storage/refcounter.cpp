#include "minitorch/refcounter.h"
#include <atomic>
#include <cstddef>

RefCounter::RefCounter() { ref_counter_.store(0); }

std::size_t RefCounter::get_count() const { return ref_counter_.load(); }

void RefCounter::retain() {
  ref_counter_.fetch_add(1, std::memory_order_seq_cst);
}

void RefCounter::release() {
  if (ref_counter_.fetch_sub(1, std::memory_order_seq_cst) == 1) {
    delete this;
  }
}

RefCounter::~RefCounter() = default;

#pragma once

#include <cstddef>
#include <cstdint>

// @Brief This is seperate class for storage only, so multi-data types data can
// be stored as, it knows nothing about dtype
class Storage {
private:
  std::uint8_t* data_;
  std::size_t data_size_;

public:
  // for allocating n bytes on heap, zero initialized
  explicit Storage(const std::size_t data_size);
  ~Storage(); // for freeing memory

  // Rule of five
  Storage(const Storage &storage_obj) =
      delete; // explicitly disable copying , only move semantics
  Storage &operator=(const Storage &storage_obj) =
      delete; // explicitly disable copying, even with equal to operator

  // only move semantics
  // @Note used noexcept as we don't want exceptions to escape this function
  // as, we are using continuous blocks of storage so, if exception occurs and
  // we escape this function it will make data corrupted and it will unlock cheap moving
  // as, during resizing std:vectors and others fallback to copying instead of moving if there is no noexcept used 
  Storage(Storage &&storage_obj) noexcept;
  Storage &operator=(Storage &&storage_obj) noexcept;

  // read and write access to private data types
  std::size_t data_size() const;
  std::uint8_t* data();
  const std::uint8_t* data() const;

};

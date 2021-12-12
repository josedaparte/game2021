#pragma once
#include <cstdint>
#include <vector>

struct SlotMap
{
  using DataType = int;
  using value_type = DataType;
  using index_type = std::size_t;
  using gen_type   = index_type;
  using key_type   = struct {  index_type id;  gen_type gen; };
  static constexpr std::size_t const DefaultInitialSize {64};
  
  explicit SlotMap(index_type initialSize = DefaultInitialSize);

  key_type push_back(value_type&& data);
  key_type push_back(value_type const& data);


  constexpr std::size_t size() const { return size_; }
  constexpr std::size_t capacity() const { return data_.capacity(); } 
  constexpr void clear() { freeListInit(); generation_ = 0; }
  bool erase(key_type key);
  bool is_valid(key_type key) const noexcept;

//private:

  constexpr void freeListInit() noexcept
  {
    for (int i{0}; i < indices_.size(); i++)
      indices_[i].id = i+1;
  }
  constexpr index_type allocate();
  constexpr void free(key_type key) noexcept;


  index_type size_{0};
  index_type freeList_ {0};
  gen_type generation_ {0};
  std::vector<key_type> indices_;
  std::vector<value_type> data_;
  std::vector<index_type> erase_;
};

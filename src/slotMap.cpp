#include <slotMap.h>
#include <iostream>
#include <stdexcept>
#include <cassert>

SlotMap::SlotMap(index_type initialSize)
{
  indices_.resize(initialSize);
  data_.resize(initialSize);
  erase_.resize(initialSize);

  clear();
}

SlotMap::key_type SlotMap::push_back(value_type &&data)
{

  if (size_ > indices_.capacity())
    throw std::runtime_error("Max Capacity reached");
  assert(freeList_ < indices_.capacity());

  auto reservedId = allocate();
  auto &slot = indices_[reservedId];

  data_[slot.id] = std::move(data);
  erase_[slot.id] = reservedId;

  // user key
  auto key{slot};
  key.id = reservedId;

  return key;
}

SlotMap::key_type SlotMap::push_back(value_type const &data)
{
  return push_back(value_type{data});
}

bool SlotMap::erase(key_type key)
{
  if (!is_valid(key)) return false;

  free(key);

  return true;
}

bool SlotMap::is_valid(key_type key) const noexcept
{
  if (key.id >= indices_.capacity() ||
      indices_[key.id].gen != key.gen)
    return false;
  return true;
}

SlotMap::index_type SlotMap::allocate()
{
  // Reserve
  auto reservedId = freeList_;
  freeList_ = indices_[reservedId].id;

  // Init Slot
  auto &slot = indices_[reservedId];
  slot.id = size_;
  slot.gen = generation_;

  // Update space and generation
  ++generation_;
  ++size_;

  return reservedId;
}

void SlotMap::free(key_type key) noexcept
{
  assert(is_valid(key));
  
  auto& slot = indices_[key.id];
  auto dataId = slot.id;
  // Update Free List
  slot.id = freeList_;
  slot.gen = generation_;
  freeList_ = key.id;
  // Copy data to free slot
  if (dataId != size_ - 1)
  {
    data_[dataId] = data_[size_ - 1];
    erase_[dataId] =erase_[size_ -1];
    indices_[erase_[dataId]].id = dataId;
  }
  // Update size and generation
  --size_;
  ++generation_;
}

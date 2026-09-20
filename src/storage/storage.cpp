#include <cstddef>
#include <cstdint>

#include "minitorch/storage.h"


Storage::Storage(const std::size_t data_size){
    data_ = new std::uint8_t[data_size](); // This is zero value initialization new T[n]() 
    data_size_ = data_size;    
}

Storage::~Storage(){
    delete [] data_;
    data_size_ = 0;
}

Storage::Storage(Storage&& storage_obj) noexcept : data_(storage_obj.data_), data_size_(storage_obj.data_size_){
    storage_obj.data_ = nullptr;
    storage_obj.data_size_ = 0;
}

Storage& Storage::operator=(Storage&& storage_obj) noexcept{
    delete [] this->data_;
    this->data_ = storage_obj.data_;
    this->data_size_ = storage_obj.data_size_;
    storage_obj.data_ = nullptr;
    storage_obj.data_size_ = 0;
    return *this;
}

std::size_t Storage::data_size() const{
    return data_size_;
}

std::uint8_t* Storage::data(){
    return data_;
}

const std::uint8_t* Storage::data() const{
    return data_;
}

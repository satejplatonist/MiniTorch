#include <cassert>
#include <cstddef>
#include <cstdint>
#include <utility>
#include "minitorch/storage.h"

int main () {
    Storage s1(16);
    assert(s1.data_size()==16);
    for (std::size_t i=0; i<s1.data_size(); i++) {
        assert(s1.data()[i] == 0);
    }

    s1.data()[3] = 42;
    assert(s1.data()[3] == 42);

    Storage s2 = std::move(s1);
    assert(s1.data() == nullptr && s1.data_size() == 0);
    assert(s2.data_size()==16);
    for (std::size_t i=0; i<s2.data_size(); i++) {
        if(i==3){
            assert(s2.data()[i] == 42);
        }else{
            assert(s2.data()[i]==0);
        }
    }

    const Storage& ref = s2;
    assert(ref.data()[3]==42);

    Storage s3(8);
    s3 = std::move(s2);
    assert(s3.data()[3]==42);

    return 0;
}

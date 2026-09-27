#pragma once

#include <atomic>
#include <cstddef>

// class for keeping record of pointers accesing same memory block
class RefCounter{
    private:
        std::atomic<std::size_t> ref_counter_;

    public:
        RefCounter();
        // if it is not virtual then only RefCounter object will be deleted not the Storage one
        virtual ~RefCounter();
        
        // copy and move should not be allowed as it doesnt make sense to do so.
        // if we copy/move its value it will falsely attribute counter value when
        // it doesnt hold that much references
        RefCounter(const RefCounter& count) = delete;
        RefCounter& operator=(const RefCounter& count) = delete; 
        RefCounter(RefCounter&& count) noexcept = delete;
        RefCounter& operator=(RefCounter&& count) noexcept = delete;

        std::size_t get_count() const;

    private:
        //@Note : retain and recall classes will do atomic add and subtract . 
        //so they will be implemented by RefCounter class but will be invoked by IntrusivePtr
        //hence , declaring it as friend as forward declaration.
        template<typename U> friend class IntrusivePtr;
        void retain(); // does atomic ++
        void release(); // does atomic --
};

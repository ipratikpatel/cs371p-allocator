// ------------------------------
// projects/allocator/Allocator.h
// Copyright (C) 2013
// Glenn P. Downing
// ------------------------------

#ifndef Allocator_h
#define Allocator_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // ptrdiff_t, size_t
#include <new>     // new

// ---------
// Allocator
// ---------

template <typename T, int N>
class Allocator {
    public:
        // --------
        // typedefs
        // --------

        typedef T                 value_type;

        typedef std::size_t       size_type;
        typedef std::ptrdiff_t    difference_type;

        typedef       value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef       value_type&       reference;
        typedef const value_type& const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        friend bool operator == (const Allocator&, const Allocator&) {
            return true;}                                              // this is correct

        // -----------
        // operator !=
        // -----------

        friend bool operator != (const Allocator& lhs, const Allocator& rhs) {
            return !(lhs == rhs);}

    private:
        // ----
        // data
        // ----

        char a[N];
        
        // -----
        // valid
        // -----

        /**
         * O(1) in space
         * O(n) in time
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            const int *p = reinterpret_cast<const int*>(&a[0]);
            int sentinal_a = 0;
            int sentinal_b = 0;
            const char *temp_a = a;

            // Go through the array and check the sentinals untill we reach the end of the char a[N];
            while(temp_a < (a + N))
            {   
                sentinal_a = *p;

                if (sentinal_a < 0)
                    p = (int *) ( temp_a + ((-1 * sentinal_a) + 4) );
                else
                    p = (int *) ( temp_a +(sentinal_a + 4) );

                sentinal_b = *p;

                if (sentinal_a != sentinal_b)
                    return false;

                p += 1;
                temp_a = (char *) p;
            }

            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * O(1) in space
         * O(1) in time
         * <your documentation>
         */
        Allocator () {
            // <your code>
            int *p = reinterpret_cast<int*>(&a[0]);
            int num_free_bytes = N - 8;
            *p = num_free_bytes;
            p = (int * ) ( a + N - 4 );
            assert(p == (int *) (a + 4 + num_free_bytes)); 
            *p = num_free_bytes;
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Allocator  (const Allocator&);
        // ~Allocator ();
        // Allocator& operator = (const Allocator&);

        // --------
        // allocate
        // --------

        /**
         * O(1) in space
         * O(n) in time
         * <your documentation>
         * after allocation there must be enough space left for a valid block
         * the smallest allowable block is sizeof(T) + (2 * sizeof(int))
         * choose the first block that fits
         */
        /*pointer allocate (size_type n) {
            // <your code>
            int *sent_p = reinterpret_cast<int*>(&a[0]);
            char *temp_a = a;
            int num_bytes_allocating = n * sizeof(value_type);
            int smalllest_block = sizeof(value_type) + (2 * sizeof(int));
            int free_block_size;
            pointer alloc_p;
            //Get the pointer to the first free block
            while(temp_a < (a + N))
            {
                if (*sent_p > 0)
                {   
                    // If we have enough space, that was asked for 
                    if (*sent_p >= num_bytes_allocating)
                    {   
                        // check if left-over block is >= smallest allowable block is sizeof(T) + (2 * sizeof(int))
                        if ((*sent_p - num_bytes_allocating) >= smalllest_block ) 
                        {
                            free_block_size = *sent_p;
                            *sent_p = num_bytes_allocating * -1;
                            alloc_p = (pointer) (sent_p + 1);
                            temp_a += num_bytes_allocating + 4; 
                            sent_p = (int *) temp_a;
                            *sent_p = num_bytes_allocating * -1;

                            sent_p += 1;
                            *sent_p = free_block_size - num_bytes_allocating - 8;
                            temp_a = (char *) sent_p;
                            temp_a += *sent_p + 4;
                            sent_p = (int *) temp_a;
                            *sent_p = free_block_size - num_bytes_allocating - 8;

                            return alloc_p;
                        }
                        else
                        {
                            // check if (*sent_p - num_bytes_allocating) == 0 then give it all
                            free_block_size = *sent_p;
                            *sent_p *= -1;
                            alloc_p = (pointer) (sent_p + 1);
                            temp_a += free_block_size + 4; 
                            sent_p = (int *) temp_a;
                            *sent_p *= -1;    
                            
                            return alloc_p;                       
                        }
                    }
                    else
                    {
                        temp_a = temp_a + *sent_p + 8;
                        sent_p = (int *) temp_a;
                    }

                }
                else
                {
                    temp_a = temp_a + (*sent_p * -1) + 8;
                    sent_p = (int *) temp_a;
                }                
                
            }

            assert(valid());
            return 0;}                   // replace!*/

        // ---------
        // construct
        // ---------

        /**
         * O(1) in space
         * O(1) in time
         * <your documentation>
         */
        void construct (pointer p, const_reference v) {
            new (p) T(v);                               // this is correct and exempt
            assert(valid());}                           // from the prohibition of new

        // ----------
        // deallocate
        // ----------

        /**
         * O(1) in space
         * O(1) in time
         * <your documentation>
         * after deallocation adjacent free blocks must be coalesced
         */
        void deallocate (pointer p, size_type) {
            // <your code>
            assert(valid());}

        // -------
        // destroy
        // -------

        /**
         * O(1) in space
         * O(1) in time
         * <your documentation>
         */
        void destroy (pointer p) {
            p->~T();               // this is correct
            assert(valid());}};

#endif // Allocator_h


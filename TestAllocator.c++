// ------------------------------------
// projects/allocator/TestAllocator.c++
// Copyright (C) 2013
// Glenn P. Downing
// ------------------------------------

/*
To test the program:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

    % g++ -pedantic -std=c++0x -Wall TestAllocator.c++ -o TestAllocator -lgtest -lpthread -lgtest_main

    % valgrind TestAllocator > TestAllocator.out
*/

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// ------------------------------
// TestAllocator Our Allocator
// ------------------------------

template <typename A>
struct TestAllocator : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A                  allocator_type;
    typedef typename A::value_type      value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer         pointer;};

typedef testing::Types<
            Allocator<int, 100>,
            Allocator<double, 100>
            >
        my_types;

TYPED_TEST_CASE(TestAllocator, my_types);


TYPED_TEST(TestAllocator, Allocator_default_0) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const allocator_type& rx = x;
    ASSERT_EQ(rx.view(0), rx.view(96));
    ASSERT_EQ(rx.view(0), 92);

    }


TYPED_TEST(TestAllocator, Allocator_0) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const allocator_type& rx = x;
    ASSERT_EQ(rx.view(0), rx.view(96));
    ASSERT_EQ(rx.view(0), 92);

    const difference_type s = 1;
    const value_type      v = 2;
    const pointer         p = x.allocate(s);

    if (p != 0) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}

    ASSERT_EQ(rx.view(0), rx.view(96));
    ASSERT_EQ(rx.view(0), 92);
    }

TYPED_TEST(TestAllocator, Allocator_1) {
    typedef typename TestFixture::allocator_type  allocator_type;
    typedef typename TestFixture::value_type      value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer         pointer;

    allocator_type x;
    const allocator_type& rx = x;
    ASSERT_EQ(rx.view(0), rx.view(96));
    ASSERT_EQ(rx.view(0), 92);

    const difference_type s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != 0) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}
    ASSERT_EQ(rx.view(0), rx.view(96));
    ASSERT_EQ(rx.view(0), 92);
    
    }

    TYPED_TEST(TestAllocator, Allocator_2) {
        typedef typename TestFixture::allocator_type  allocator_type;
        typedef typename TestFixture::value_type      value_type;
        typedef typename TestFixture::difference_type difference_type;
        typedef typename TestFixture::pointer         pointer;

        allocator_type x;
        const allocator_type& rx = x;
        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

        const difference_type s = 10;
        const value_type      v = 2;
        const pointer         b = x.allocate(s);
        if (b != 0) {
            pointer e = b + s;
            pointer p = b;
            try {
                while (p != e) {
                    x.construct(p, v);
                    ++p;}}
            catch (...) {
                while (b != p) {
                    --p;
                    x.destroy(p);}
                x.deallocate(b, s);
                throw;}
            ASSERT_EQ(s, std::count(b, e, v));
            while (b != e) {
                --e;
                x.destroy(e);}
            x.deallocate(b, s);
        }

        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

        const pointer         d = x.allocate(s);
        ASSERT_EQ(d, b);
        if (d != 0) {
            pointer e = d + s;
            pointer p = d;
            try {
                while (p != e) {
                    x.construct(p, v);
                    ++p;}}
            catch (...) {
                while (d != p) {
                    --p;
                    x.destroy(p);}
                x.deallocate(d, s);
                throw;}
            ASSERT_EQ(s, std::count(d, e, v));
            while (d != e) {
                --e;
                x.destroy(e);}
            x.deallocate(d, s);
        }

        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);


    }

    TYPED_TEST(TestAllocator, TestDeallocate_0) {
        typedef typename TestFixture::allocator_type  allocator_type;
        typedef typename TestFixture::value_type      value_type;
        typedef typename TestFixture::difference_type difference_type;
        typedef typename TestFixture::pointer         pointer;

        allocator_type x;
        const allocator_type& rx = x;
        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

        const difference_type s = 10;
        const pointer         b = x.allocate(s);
        if(sizeof(value_type) == 4)
        {
            ASSERT_EQ(rx.view(0), -40);
            ASSERT_EQ(rx.view(44), -40);
            ASSERT_EQ(rx.view(48), 44);
            ASSERT_EQ(rx.view(96), 44);         
        }
        else
        {
            ASSERT_EQ(rx.view(0), -92);
            ASSERT_EQ(rx.view(96), -92);
        }
        x.deallocate(b, s);
        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

        const pointer   c = x.allocate(s);
        if(sizeof(value_type) == 4)
        {
            ASSERT_EQ(rx.view(0), -40);
            ASSERT_EQ(rx.view(44), -40);
            ASSERT_EQ(rx.view(48), 44);
            ASSERT_EQ(rx.view(96), 44);         
        }
        else
        {
            ASSERT_EQ(rx.view(0), -92);
            ASSERT_EQ(rx.view(96), -92);
        }

        x.deallocate(c, s);

        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);
    }


    TYPED_TEST(TestAllocator, TestDeallocate_1){
        typedef typename TestFixture::allocator_type  allocator_type;
        typedef typename TestFixture::value_type      value_type;
        typedef typename TestFixture::difference_type difference_type;
        typedef typename TestFixture::pointer         pointer;

        allocator_type x;
        const allocator_type& rx = x;
        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

        const pointer b = x.allocate(2);
        if(sizeof(value_type) == 4)
        {
            ASSERT_EQ(rx.view(0), -8);
            ASSERT_EQ(rx.view(12), -8);
            ASSERT_EQ(rx.view(16), 76);
            ASSERT_EQ(rx.view(96), 76);         
        }
        else
        {
            ASSERT_EQ(rx.view(0), -16);
            ASSERT_EQ(rx.view(20), -16);
            ASSERT_EQ(rx.view(24), 68);
            ASSERT_EQ(rx.view(96), 68);
        }

        const pointer c = x.allocate(3);

        if(sizeof(value_type) == 4)
        {
            ASSERT_EQ(rx.view(0), -8);
            ASSERT_EQ(rx.view(12), -8);
            ASSERT_EQ(rx.view(16), -12);
            ASSERT_EQ(rx.view(32), -12);
            ASSERT_EQ(rx.view(36), 56);
            ASSERT_EQ(rx.view(96), 56);         
        }
        else
        {
            ASSERT_EQ(rx.view(0), -16);
            ASSERT_EQ(rx.view(20), -16);
            ASSERT_EQ(rx.view(24), -24);
            ASSERT_EQ(rx.view(52), -24);
            ASSERT_EQ(rx.view(56), 36);
            ASSERT_EQ(rx.view(96), 36);
        }

        x.deallocate(c,3);
        if(sizeof(value_type) == 4)
        {
            ASSERT_EQ(rx.view(0), -8);
            ASSERT_EQ(rx.view(12), -8);
            ASSERT_EQ(rx.view(16), 76);
            ASSERT_EQ(rx.view(96), 76);         
        }
        else
        {
            ASSERT_EQ(rx.view(0), -16);
            ASSERT_EQ(rx.view(20), -16);
            ASSERT_EQ(rx.view(24), 68);
            ASSERT_EQ(rx.view(96), 68);
        }

        x.deallocate(b,2);


        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

        const pointer d = x.allocate(3);
        assert(b==d);
        x.deallocate(d,3);

        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);
    }

    TYPED_TEST(TestAllocator, deallocator_2) {
        typedef typename TestFixture::allocator_type  allocator_type;
        typedef typename TestFixture::value_type      value_type;
        typedef typename TestFixture::difference_type difference_type;
        typedef typename TestFixture::pointer         pointer;

        allocator_type x;
        const allocator_type& rx = x;
        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

        const pointer b = x.allocate(2);

        x.deallocate(b, 2);

        ASSERT_EQ(rx.view(0), rx.view(96));
        ASSERT_EQ(rx.view(0), 92);

    }


    // -------------
// TestAllocator2
// -------------

template <typename A>
struct TestAllocator2 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef A allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::difference_type difference_type;
    typedef typename A::pointer pointer;};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double> >
        my_types2;

TYPED_TEST_CASE(TestAllocator2, my_types2);

TYPED_TEST(TestAllocator2, std_One) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer pointer;

    allocator_type x;
    const difference_type s = 1;
    const value_type v = 2;
    const pointer p = x.allocate(s);
    if (p != 0) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}
}

TYPED_TEST(TestAllocator2, std_Ten) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type value_type;
    typedef typename TestFixture::difference_type difference_type;
    typedef typename TestFixture::pointer pointer;

    allocator_type x;
    const difference_type s = 10;
    const value_type v = 2;
    const pointer b = x.allocate(s);
    if (b != 0) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}
}


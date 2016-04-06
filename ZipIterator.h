#ifndef ZIP_ITERATOR
#define ZIP_ITERATOR

#include <type_traits>
#include <tuple>



namespace zip
{

namespace impl
{
    template <class F, std::size_t... Is, typename... Args>
    void forTupleImpl (F f, std::tuple<Args...>& tup, std::index_sequence<Is...>)
    {
        static auto dummie = { f(std::get<Is>(tup))... };
    }

    template <class F, typename... Args>
    void forTuple (F f, std::tuple<Args...>& tup)
    {
        forTupleImpl([&](auto&& x){ f(x); return nullptr; }, tup, std::make_index_sequence<sizeof...(Args)>());
    }



    template <typename... Args>
    struct ZipIterator
    {
        ZipIterator(Args... args) : tup(std::make_tuple(args...)) {}
        //ZipIterator(Args... args) : tup(args...) {}


        decltype(auto) operator* () { return tup; }


        template <typename Indexes = std::make_index_sequence<sizeof...(Args)>>
        decltype(auto) operator++ () { increment(Indexes()); return *this; }

        template <std::size_t... Is>
        void increment (std::index_sequence<Is...>) { [](auto&&...){}((std::get<Is>(tup)++)...); }


        bool operator == (const ZipIterator& z)
        {
            return std::get<0>(tup) == std::get<0>(z.tup);
            //return tup == z.tup;
        }

        bool operator != (const ZipIterator& z)
        {
            return !operator==(z);
        }


        std::tuple<Args...> tup;
    };


    template <class F>
    struct UnZip
    {
        UnZip (const F& f = F()) : f(f) {}

        template <typename... Args, typename Indexes = std::make_index_sequence<sizeof...(Args)>>
        void operator () (std::tuple<Args...>&& tup) { unpack(tup, Indexes()); }

        template <typename... Args, std::size_t... Is>
        void unpack (std::tuple<Args...>& tup, std::index_sequence<Is...>) { f(std::get<Is>(tup)...); }


        F f;
    };

}


    template <typename... Args>
    auto zipIterator (Args&&... args)
    {
        return impl::ZipIterator<Args...>(std::forward<Args>(args)...);
    }


    template <class F>
    auto unZip (F f)
    {
        return impl::UnZip<F>(f);
    }
}

#endif	// ZIP_ITERATOR
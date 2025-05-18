#include "traversable.hpp"
namespace lasd
{

    /* ************************************************************************** */
    /*
    FoldFun is defined in the header as:
    using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

    you can see how it would be uncomfortarble to define in everytime.
    */

    template <typename Data>
    template <typename Accumulator>
    inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> foldFun, Accumulator acc) const
    {
        /*
        Fold returns an accumulator, so the point of this function is defining the accumulator.

        Traverse takes a TraverseFun as an argument, which is given as a lambda.

        TraverseFun (the lambda) takes const Data& as an argument.

        Since we need to define the accumulator, the lambda will take the one on the scope (passed via argument) as a reference,
        and the fold function (foldFun) that will return the new Accumulator.

        foldFun takes data& (passed in the lambda), and the accumulator, which will be returned by Fold()
        */

        // inline since well, its basically a lambda

        Traverse([&acc, foldFun](const Data &data)
                 { acc = foldFun(data, acc); });

        return acc;
    }

    template <typename Data>
    inline bool TraversableContainer<Data>::Exists(const Data &data) const noexcept
    {
        bool exists = false;
        Traverse([data, &exists](const Data &currData)
                 { exists |= (data == currData); });
        return exists;
    }
    /* ************************************************************************** */

    // PreOrderTraversableContainer Methods
    template <typename Data>
    inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun func) const
    {
        PreOrderTraverse(func);
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> func, const Accumulator acc) const
    {
        PreOrderTraverse([func, &acc](const Data &data)
                         { acc = func(data, acc); });

        return acc;
    }

    /* ************************************************************************** */

    // PostOrderTraversableContainer Methods

    template <typename Data>
    void PostOrderTraversableContainer<Data>::Traverse(TraverseFun func) const
    {
        PostOrderTraverse(func);
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> func, Accumulator base) const
    {
        PostOrderTraverse(
            [&base, &func](const Data &currData)
            { base = func(currData, base); });
        return base;
    }

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;

    /* ************************************************************************** */
}
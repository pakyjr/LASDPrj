
namespace lasd
{

    /* ************************************************************************** */
    /*
    FoldFun is defined in the header as:
    using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

    you can see how it would be uncomfortarble to define in everytime.
    */
    template <typename Data, typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

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

        // inline since well, it takes a lambda

        Traverse([&acc, foldFun](const Data &data)
                 { acc = foldFun(data, acc) });

        return acc;
    }

    /* ************************************************************************** */
}
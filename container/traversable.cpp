namespace lasd
{

    template <typename Data>
    template <typename Accumulator>
    Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, const Accumulator &acc) const
    {
        Accumulator result = acc;
        Traverse([&result, &fun](const Data &data)
                 { result = fun(data, result); });
        return result;
    }

    template <typename Data>
    bool TraversableContainer<Data>::Exists(const Data &data) const noexcept
    {
        bool found = false;

        Traverse([&found, &data](const Data &current)
                 {
        if (!found && current == data) {
            found = true;
        } });

        return found;
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, const Accumulator &acc) const
    {
        Accumulator result = acc;
        PreOrderTraverse([&result, &fun](const Data &data)
                         { result = fun(data, result); });
        return result;
    }

    template <typename Data>
    void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const
    {
        PreOrderTraverse(fun);
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator PreOrderTraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, const Accumulator &acc) const
    {
        return PreOrderFold(fun, acc);
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, const Accumulator &acc) const
    {
        Accumulator result = acc;
        PostOrderTraverse([&result, &fun](const Data &data)
                          { result = fun(data, result); });
        return result;
    }

    template <typename Data>
    void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const
    {
        PostOrderTraverse(fun);
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator PostOrderTraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, const Accumulator &acc) const
    {
        return PostOrderFold(fun, acc);
    }

}
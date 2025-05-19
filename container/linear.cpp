#include "linear.hpp"
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    bool LinearContainer<Data>::operator==(const LinearContainer<Data> &other) const noexcept
    {
        if (this->Size() != other.Size())
        {
            return false;
        }

        for (ulong i = 0; i < this->Size(); i++)
        {
            if ((*this)[i] != other[i])
            {
                return false;
            }
        }
    }

    template <typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    template <typename Data>
    void LinearContainer<Data>::Traverse(TraverseFun func) const
    {
        PreOrderTraverse(func);
    }

    template <typename Data>
    void LinearContainer<Data>::PreOrderTraverse(TraverseFun tFunc) const
    {
        for (ulong i = 0; i < this->Size(); i++)
        {
            tFunc((*this)[i]);
        }
    }

    template <typename Data>
    void LinearContainer<Data>::PostOrderTraverse(TraverseFun tFunc) const
    {
        for (ulong i = this->Size(); i > 0; i--)
        {
            tFunc((*this)[i - 1]);
        }
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator LinearContainer<Data>::Fold(FoldFun<Accumulator> fFunc, const Accumulator &acc) const
    {
        return PreOrderFold(fFunc, acc);
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator LinearContainer<Data>::PreOrderFold(FoldFun<Accumulator> fFunc, const Accumulator &acc) const
    {
        Accumulator accumulator = acc;

        for (ulong i = 0; i < this->Size(); i++)
        {
            accumulator = fFunc((*this)[i], accumulator);
        }

        return accumulator;
    }

    template <typename Data>
    template <typename Accumulator>
    Accumulator LinearContainer<Data>::PostOrderFold(FoldFun<Accumulator> fFunc, const Accumulator &acc) const
    {
        Accumulator accumulator = acc;

        for (ulong i = this->Size(); i > 0; i--)
        {
            accumulator = fFunc((*this)[i - 1], accumulator);
        }

        return accumulator;
    }

    /* ************************************************************************** */

    // MutableLinearContainer

    template <typename Data>
    void MutableLinearContainer<Data>::Map(MapFun mFunc)
    {
        PreOrderMap(mFunc);
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PreOrderMap(MapFun mFunc)
    {
        for (ulong i = 0; i < this->Size(); i++)
        {
            mFunc((*this)[i]);
        }
    }

    template <typename Data>
    void MutableLinearContainer<Data>::PostOrderMap(MapFun mFunc)
    {
        for (ulong i = this->Size(); i > 0; i--)
        {
            fun((*this)[i - 1]);
        }
    }

    // SortableLinearContainer

    template <typename Data>
    void SortableLinearContainer<Data>::QuickSort(ulong left, ulong right)
    {
        if (left < right)
        {
            ulong pivot = Partition(left, right);

            if (pivot > 0)
            {
                QuickSort(left, pivot - 1);
            }

            QuickSort(pivot + 1, right);
        }
    }
}

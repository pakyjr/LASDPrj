namespace lasd
{

    /*******************************************************************************************************************************************************/

    // LinearContainer

    /**
     * Equality operator.
     * Compares two containers element by element.
     */
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

        return true;
    }

    /**
     * Inequality operator.
     */
    template <typename Data>
    bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    /**
     * Override of the Traverse method from TraversableContainer.
     */
    template <typename Data>
    void LinearContainer<Data>::Traverse(TraverseFun fun) const
    {
        PreOrderTraverse(fun);
    }

    /**
     * Specific implementation of PreOrderTraverse.
     */
    template <typename Data>
    void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const
    {
        for (ulong i = 0; i < this->Size(); i++)
        {
            fun((*this)[i]);
        }
    }

    /**
     * Specific implementation of PostOrderTraverse.
     */
    template <typename Data>
    void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun) const
    {
        for (ulong i = this->Size(); i > 0; i--)
        {
            fun((*this)[i - 1]);
        }
    }

    /**
     * Override of Fold from TraversableContainer: uses PreOrderFold as default.
     */
    template <typename Data>
    template <typename Accumulator>
    Accumulator LinearContainer<Data>::Fold(FoldFun<Accumulator> fun, const Accumulator &accum) const
    {
        return PreOrderFold(fun, accum);
    }

    /**
     * Specific implementation of PreOrderFold.
     */
    template <typename Data>
    template <typename Accumulator>
    Accumulator LinearContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, const Accumulator &accum) const
    {
        Accumulator accumulator = accum;

        for (ulong i = 0; i < this->Size(); i++)
        {
            accumulator = fun((*this)[i], accumulator);
        }

        return accumulator;
    }

    /**
     * Specific implementation of PostOrderFold.
     */
    template <typename Data>
    template <typename Accumulator>
    Accumulator LinearContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, const Accumulator &accum) const
    {
        Accumulator accumulator = accum;

        for (ulong i = this->Size(); i > 0; i--)
        {
            accumulator = fun((*this)[i - 1], accumulator);
        }

        return accumulator;
    }

    /*******************************************************************************************************************************************************/

    // MutableLinearContainer

    /**
     * Override of the Map method from MappableContainer: uses PreOrderMap as default.
     */
    template <typename Data>
    void MutableLinearContainer<Data>::Map(MapFun fun)
    {
        PreOrderMap(fun);
    }

    /**
     * Specific implementation of PreOrderMap.
     */
    template <typename Data>
    void MutableLinearContainer<Data>::PreOrderMap(MapFun fun)
    {
        for (ulong i = 0; i < this->Size(); i++)
        {
            fun((*this)[i]);
        }
    }

    /**
     * Specific implementation of PostOrderMap.
     */
    template <typename Data>
    void MutableLinearContainer<Data>::PostOrderMap(MapFun fun)
    {
        for (ulong i = this->Size(); i > 0; i--)
        {
            fun((*this)[i - 1]);
        }
    }

    /*******************************************************************************************************************************************************/

    // SortableLinearContainer

    /**
     * Protected method for quicksort.
     */
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

    /**
     * Protected method for partitioning (pivot) in the quicksort algorithm.
     */
    template <typename Data>
    ulong SortableLinearContainer<Data>::Partition(ulong left, ulong right)
    {
        ulong pivotIndex = left + (right - left) / 2;
        Data pivotValue = (*this)[pivotIndex];

        std::swap((*this)[pivotIndex], (*this)[right]); // Move the pivot to the end

        ulong storeIndex = left;

        for (ulong i = left; i < right; i++)
        {
            if ((*this)[i] <= pivotValue)
            {
                std::swap((*this)[i], (*this)[storeIndex]);
                storeIndex++;
            }
        }

        std::swap((*this)[storeIndex], (*this)[right]); // Reposition the pivot
        return storeIndex;
    }

    /*******************************************************************************************************************************************************/

}
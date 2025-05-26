#ifndef LINEAR_HPP
#define LINEAR_HPP

#include "mappable.hpp"

namespace lasd
{

  /*******************************************************************************************************************************************************/

  /**
   * Abstract template class LinearContainer that virtually extends PreOrderTraversableContainer and PostOrderTraversableContainer.
   *
   * Provides a base interface for linear containers with index access and support for traversals and folds.
   */
  template <typename Data>
  class LinearContainer : virtual public PreOrderTraversableContainer<Data>,
                          virtual public PostOrderTraversableContainer<Data>
  {

  public:
    // Destructor
    virtual ~LinearContainer() = default;

    // Disable assignment operations

    LinearContainer &operator=(const LinearContainer &) = delete;     // Copy disabled
    LinearContainer &operator=(LinearContainer &&) noexcept = delete; // Move disabled

    // Comparison operators
    virtual bool operator==(const LinearContainer &) const noexcept;
    virtual bool operator!=(const LinearContainer &) const noexcept;

    // Specific member functions

    virtual const Data &operator[](ulong) const = 0; // Read-only access (out_of_range if invalid index)
    virtual const Data &Front() const = 0;           // First element (length_error if empty)
    virtual const Data &Back() const = 0;            // Last element (length_error if empty)

    // Member function (inherited from TraversableContainer)
    using typename TraversableContainer<Data>::TraverseFun;
    void Traverse(TraverseFun) const override;

    // Member function (inherited from PreOrderTraversableContainer)
    void PreOrderTraverse(TraverseFun) const override;

    // Member function (inherited from PostOrderTraversableContainer)
    void PostOrderTraverse(TraverseFun) const override;

    // Generic fold (inherited from TraversableContainer)
    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;

    // Pre-order fold (inherited from PreOrderTraversableContainer)
    template <typename Accumulator>
    Accumulator PreOrderFold(FoldFun<Accumulator>, const Accumulator &) const;

    // Post-order fold (inherited from PostOrderTraversableContainer)
    template <typename Accumulator>
    Accumulator PostOrderFold(FoldFun<Accumulator>, const Accumulator &) const;
  };

  /*******************************************************************************************************************************************************/

  /**
   * Abstract class MutableLinearContainer that virtually extends LinearContainer and the mappable versions.
   *
   * Introduces modifiable access to the elements of the linear container.
   */
  template <typename Data>
  class MutableLinearContainer : virtual public LinearContainer<Data>,
                                 virtual public PreOrderMappableContainer<Data>,
                                 virtual public PostOrderMappableContainer<Data>
  {

  public:
    // Destructor
    virtual ~MutableLinearContainer() = default;

    // Disable assignment operations

    MutableLinearContainer &operator=(const MutableLinearContainer &) = delete;
    MutableLinearContainer &operator=(MutableLinearContainer &&) noexcept = delete;

    // Expose the const versions of the inherited functions
    using LinearContainer<Data>::operator[];
    using LinearContainer<Data>::Front;
    using LinearContainer<Data>::Back;

    // Specific member functions (modifiable versions)

    virtual Data &operator[](ulong) = 0; // Modifiable access (out_of_range if invalid index)
    virtual Data &Front() = 0;           // First element (length_error if empty)
    virtual Data &Back() = 0;            // Last element (length_error if empty)

    // Member function (inherited from MappableContainer)
    using typename MappableContainer<Data>::MapFun;
    void Map(MapFun) override;

    // Member function (inherited from PreOrderMappableContainer)
    void PreOrderMap(MapFun) override;

    // Member function (inherited from PostOrderMappableContainer)
    void PostOrderMap(MapFun) override;
  };

  /*******************************************************************************************************************************************************/

  /**
   * Abstract class SortableLinearContainer that extends MutableLinearContainer.
   *
   * Introduces sorting capabilities on modifiable linear containers.
   */
  template <typename Data>
  class SortableLinearContainer : virtual public MutableLinearContainer<Data>
  {

  private:
    // Helper functions for sorting
    virtual void QuickSort(ulong, ulong);
    virtual ulong Partition(ulong, ulong);

  public:
    // Destructor
    virtual ~SortableLinearContainer() = default;

    // Disable assignment operations

    SortableLinearContainer &operator=(const SortableLinearContainer &) = delete;
    SortableLinearContainer &operator=(SortableLinearContainer &&) noexcept = delete;

    // Specific member function

    /**
     * Public method to sort the container using quicksort.
     */
    virtual void Sort()
    {
      if (this->Size() > 1)
      {
        QuickSort(0, this->Size() - 1);
      }
    }
  };

  /*******************************************************************************************************************************************************/

}

#include "linear.cpp"

#endif
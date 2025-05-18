
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class LinearContainer : public virtual PreOrderTraversableContainer<Data>,
                          public virtual PostOrderTraversableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~LinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    LinearContainer &operator=(const LinearContainer &) = delete;

    // Move assignment
    LinearContainer &operator=(LinearContainer &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    inline bool operator==(const LinearContainer &) const noexcept;
    inline bool operator!=(const LinearContainer &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions

    virtual const Data &operator[](const unsigned long int) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)

    virtual Data &operator[](const unsigned long int) = 0;

    virtual Data &Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)

    virtual Data &Front();

    virtual Data &Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)

    virtual Data &Back();
    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)

    using typename TraversableContainer<Data>::TraverseFun;

    inline void Traverse(TraverseFun) const override; // Override TraversableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderTraversableContainer)

    inline void PreOrderTraverse(TraverseFun) const override; // Override PreOrderTraversableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderTraversableContainer)

    inline void PostOrderTraverse(TraverseFun) const override; // Override PostOrderTraversableContainer member
    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;

    template <typename Accumulator>
    Accumulator PreOrderFold(FoldFun<Accumulator>, const Accumulator &) const;

    template <typename Accumulator>
    Accumulator PostOrderFold(FoldFun<Accumulator>, const Accumulator &) const;
  };

  /* ************************************************************************** */

  template <typename Data>
  class MutableLinearContainer : virtual public LinearContainer<Data>, virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~MutableLinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    MutableLinearContainer operator=(const MutableLinearContainer &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableLinearContainer operator=(const MutableLinearContainer &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual Data &operator[](ulong) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

    virtual Data &Front() = 0; // (mutable version; concrete function must throw std::length_error when empty)

    virtual Data &Back() = 0; // (mutable version; concrete function must throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member function (inherited from MappableContainer)

    using typename MappableContainer<Data>::MapFun;

    void Map(MapFun) override; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PreOrderMappableContainer)
    void PreOrderMap(MapFun) override;  // Override PreOrderMappableContainer member
    void PostOrderMap(MapFun) override; // Override PostOrderMappableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from PostOrderMappableContainer)
  };

  template <typename Data>
  class SortableLinearContainer : virtual public MutableLinearContainer<Data>
  {
    // Must extend MutableLinearContainer<Data>

  private:
    // ...
    virtual void QuickSort(ulong, ulong);
    virtual ulong Partition(ulong, ulong);

  protected:
    // ...

  public:
    // Destructor
    ~SortableLinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    SortableLinearContainer &operator=(const SortableLinearContainer &) = delete;

    // Move assignment
    SortableLinearContainer &operator=(SortableLinearContainer &&) noexcept = delete;

    /* ************************************************************************ */

    // Specific member function

    virtual void Sort() const noexcept = 0;
  };

  /* ************************************************************************** */

}

#include "linear.cpp"

#endif

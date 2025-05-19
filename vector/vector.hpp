
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Vector : virtual public MutableLinearContainer<Data>,
                 virtual public ResizableContainer
  {
    // Must extend MutableLinearContainer<Data>,
    //             ResizableContainer

  private:
    // ...

  protected:
    using Container::size;

    Data *elements = nullptr;
    // ...

  public:
    // Default constructor
    Vector() = default;

    /* ************************************************************************ */

    // Specific constructors
    Vector(ulong);                              // A vector with a given initial dimension
    Vector(const TraversableContainer<Data> &); // A vector obtained from a TraversableContainer
    Vector(MappableContainer<Data> &&);         // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    // Copy constructor
    Vector(const Vector &);

    // Move constructor
    Vector(Vector &&);

    /* ************************************************************************ */

    // Destructor
    virtual ~Vector();

    /* ************************************************************************ */
    Vector &operator=(const Vector &);

    Vector &operator=(Vector &&) noexcept;

    using LinearContainer<Data>::operator==;
    using LinearContainer<Data>::operator!=;

    bool operator==(const Vector &) const noexcept;
    bool operator!=(const Vector &) const noexcept;
    /* ************************************************************************ */

    // Specific member functions (inherited from MutableLinearContainer)
    Data &operator[](unsigned long) override;
    Data &Front() override;
    Data &Back() override;

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)

    const Data &operator[](unsigned long) const override;
    const Data &Front() const override;
    const Data &Back() const override;

    /* ************************************************************************ */

    // Specific member function (inherited from ResizableContainer)

    void Resize(ulong) override; // Override ResizableContainer member

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override; // Override ClearableContainer member

  protected:
    void Swap(Vector &) noexcept;
  };

  /* ************************************************************************** */

  template <typename Data>
  class SortableVector : virtual public Vector<Data>, virtual public SortableLinearContainer<Data>
  {
  private:
    // ...

  protected:
    // using Container::???;

    // ...

  public:
    // Default constructor
    SortableVector() = default;

    /* ************************************************************************ */

    // Specific constructors
    explicit SortableVector(ulong newSize) : Vector<Data>(newSize) {}                           // A vector with a given initial dimension
    SortableVector(const TraversableContainer<Data> &container) : Vector<Data>(container) {}    // A vector obtained from a TraversableContainer
    SortableVector(MappableContainer<Data> &&container) : Vector<Data>(std::move(container)) {} // A vector obtained from a MappableContainer

    /* ************************************************************************ */

    SortableVector(const SortableVector &other) : Vector<Data>(other) {}

    SortableVector(SortableVector &&other) noexcept : Vector<Data>(std::move(other)) {}

    virtual ~SortableVector() = default;

    SortableVector &operator=(const SortableVector &other)
    {
      Vector<Data>::operator=(other);
      return *this;
    }

    SortableVector &operator=(SortableVector &&other) noexcept
    {
      Vector<Data>::operator=(std::move(other));
      return *this;
    }

    void Sort() override;

  protected:
    void QuickSort(unsigned long, unsigned long);
    unsigned long Partition(unsigned long, unsigned long);
    void Swap(unsigned long, unsigned long);
  };
}

#include "vector.cpp"

#endif

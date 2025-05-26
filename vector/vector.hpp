#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "../container/linear.hpp"

namespace lasd
{

  /*******************************************************************************************************************************************************/

  template <typename Data>
  class Vector : virtual public MutableLinearContainer<Data>,
                 virtual public ResizableContainer
  {

  private:
    // ...

  protected:
    using Container::size;

    Data *elements = nullptr;

  public:
    Vector() = default;

    explicit Vector(unsigned long);
    Vector(const TraversableContainer<Data> &);
    Vector(MappableContainer<Data> &&);

    Vector(const Vector &);

    Vector(Vector &&) noexcept;

    virtual ~Vector();

    Vector &operator=(const Vector &);

    Vector &operator=(Vector &&) noexcept;

    using LinearContainer<Data>::operator==;
    using LinearContainer<Data>::operator!=;

    bool operator==(const Vector &) const noexcept;
    bool operator!=(const Vector &) const noexcept;

    Data &operator[](unsigned long) override;
    Data &Front() override;
    Data &Back() override;

    const Data &operator[](unsigned long) const override;
    const Data &Front() const override;
    const Data &Back() const override;

    void Resize(unsigned long) override;

    void Clear() override;

  protected:
    void Swap(Vector &) noexcept;
  };

  /*******************************************************************************************************************************************************/

  template <typename Data>
  class SortableVector : virtual public Vector<Data>,
                         virtual public SortableLinearContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    SortableVector() = default;

    explicit SortableVector(unsigned long newSize) : Vector<Data>(newSize) {}
    SortableVector(const TraversableContainer<Data> &container) : Vector<Data>(container) {}
    SortableVector(MappableContainer<Data> &&container) : Vector<Data>(std::move(container)) {}

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
    void QuickSort(unsigned long, unsigned long) override;
    unsigned long Partition(unsigned long, unsigned long) override;
    void Swap(unsigned long, unsigned long);
  };

  /*******************************************************************************************************************************************************/

}

#include "vector.cpp"

#endif

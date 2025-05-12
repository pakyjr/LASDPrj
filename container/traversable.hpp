
#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "testable.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class TraversableContainer : virtual public TestableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~TraversableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    TraversableContainer &operator=(const TraversableContainer &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    TraversableContainer &operator=(const TraversableContainer &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    TraversableContainer &operator==(const TraversableContainer &) = delete; // Comparison of abstract types is not possible.
    TraversableContainer &operator!=(const TraversableContainer &) = delete; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member function

    using TraverseFun = std::function<void(const Data &)>;

    virtual void Traverse(TraverseFun func) const = 0;

    template <typename Accumulator>
    using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

    template <typename Accumulator>
    inline Accumulator Fold(FoldFun<Accumulator> foldFunc, Accumulator acc) const;

    /* ************************************************************************ */

    // Specific member function (inherited from TestableContainer)

    bool Exists(const Data &data) override; // Override TestableContainer member
  };

  /* ************************************************************************** */

  template <typename Data>
  class PreOrderTraversableContainer : public TraversableContainer<Data>
  {
    // Must extend TraversableContainer<Data>

  private:
    // ...

  protected:
    // ...
  public:
    // Destructor
    virtual ~PreOrderTraversableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    PreOrderTraversableContainer &operator=(const PreOrderTraversableContainer &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    PreOrderTraversableContainer &operator=(const PreOrderTraversableContainer &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    PreOrderTraversableContainer &operator==(const PreOrderTraversableContainer &) = delete; // Comparison of abstract types is not possible.
    PreOrderTraversableContainer &operator!=(const PreOrderTraversableContainer &) = delete; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member function

    using typename TraversableContainer<Data>::TraverseFun;

    void PreOrderTraverse(TraverseFun);

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator PreOrderFold(FoldFun<Accumulator>, const Accumulator) const;

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)

    void Traverse(TraverseFun) const override;

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;
  };

  /* ************************************************************************** */

  template <typename Data>
  class PostOrderTraversableContainer : TraversableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~PostOrderTraversableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    PostOrderTraversableContainer &operator=(const PostOrderTraversableContainer &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    PostOrderTraversableContainer &operator=(const PostOrderTraversableContainer &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    PostOrderTraversableContainer &operator==(const PostOrderTraversableContainer &) = delete; // Comparison of abstract types is not possible.
    PostOrderTraversableContainer &operator!=(const PostOrderTraversableContainer &) = delete; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member function

    using typename TraversableContainer<Data>::TraverseFun;

    void PostOrderTraverse(TraverseFun);

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator PostOrderFold(FoldFun<Accumulator>, Accumulator);

    /* ************************************************************************ */

    // Specific member function (inherited from TraversableContainer)

    void Traverse(TraverseFun) override;
  };

  /* ************************************************************************** */

}

#include "traversable.cpp"

#endif

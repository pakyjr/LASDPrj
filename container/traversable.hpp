#ifndef TRAVERSABLE_HPP
#define TRAVERSABLE_HPP

#include <functional>
#include "testable.hpp"

namespace lasd
{

  /*******************************************************************************************************************************************************/

  template <typename Data>
  class TraversableContainer : virtual public TestableContainer<Data>
  {

  private:
  protected:
  public:
    virtual ~TraversableContainer() = default;

    TraversableContainer &operator=(const TraversableContainer &) = delete;

    TraversableContainer &operator=(TraversableContainer &&) noexcept = delete;

    bool operator==(const TraversableContainer &) const noexcept = delete; // Uguaglianza
    bool operator!=(const TraversableContainer &) const noexcept = delete; // Disuguaglianza

    using TraverseFun = std::function<void(const Data &)>;

    virtual void Traverse(TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;

    virtual bool Exists(const Data &) const noexcept override;
  };

  /*******************************************************************************************************************************************************/

  template <typename Data>
  class PreOrderTraversableContainer : virtual public TraversableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    virtual ~PreOrderTraversableContainer() = default;

    PreOrderTraversableContainer &operator=(const PreOrderTraversableContainer &) = delete;

    PreOrderTraversableContainer &operator=(PreOrderTraversableContainer &&) noexcept = delete;

    bool operator==(const PreOrderTraversableContainer &) const noexcept = delete;
    bool operator!=(const PreOrderTraversableContainer &) const noexcept = delete;

    using typename TraversableContainer<Data>::TraverseFun;

    virtual void PreOrderTraverse(TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator PreOrderFold(FoldFun<Accumulator>, const Accumulator &) const;

    virtual void Traverse(TraverseFun) const override;

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;
  };

  /*******************************************************************************************************************************************************/
  template <typename Data>
  class PostOrderTraversableContainer : virtual public TraversableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    virtual ~PostOrderTraversableContainer() = default;

    PostOrderTraversableContainer &operator=(const PostOrderTraversableContainer &) = delete;

    PostOrderTraversableContainer &operator=(PostOrderTraversableContainer &&) noexcept = delete;

    bool operator==(const PostOrderTraversableContainer &) const noexcept = delete;
    bool operator!=(const PostOrderTraversableContainer &) const noexcept = delete;

    using typename TraversableContainer<Data>::TraverseFun;

    virtual void PostOrderTraverse(TraverseFun) const = 0;

    template <typename Accumulator>
    using FoldFun = typename TraversableContainer<Data>::template FoldFun<Accumulator>;

    template <typename Accumulator>
    Accumulator PostOrderFold(FoldFun<Accumulator>, const Accumulator &) const;

    virtual void Traverse(TraverseFun) const override;

    template <typename Accumulator>
    Accumulator Fold(FoldFun<Accumulator>, const Accumulator &) const;
  };

  /*******************************************************************************************************************************************************/

}

#include "traversable.cpp"

#endif

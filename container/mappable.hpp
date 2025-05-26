#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

#include <functional>
#include "traversable.hpp"

namespace lasd
{

  template <typename Data>
  class MappableContainer : virtual public TraversableContainer<Data>
  {

  public:
    virtual ~MappableContainer() = default;

    MappableContainer &operator=(const MappableContainer &) = delete;
    MappableContainer &operator=(MappableContainer &&) noexcept = delete;
    bool operator==(const MappableContainer &) const noexcept = delete;
    bool operator!=(const MappableContainer &) const noexcept = delete;

    using MapFun = std::function<void(Data &)>;
    virtual void Map(MapFun) = 0;
  };

  template <typename Data>
  class PreOrderMappableContainer : virtual public MappableContainer<Data>,
                                    virtual public PreOrderTraversableContainer<Data>
  {

  public:
    virtual ~PreOrderMappableContainer() = default;

    PreOrderMappableContainer &operator=(const PreOrderMappableContainer &) = delete;
    PreOrderMappableContainer &operator=(PreOrderMappableContainer &&) noexcept = delete;
    bool operator==(const PreOrderMappableContainer &) const noexcept = delete;
    bool operator!=(const PreOrderMappableContainer &) const noexcept = delete;

    using typename MappableContainer<Data>::MapFun;
    virtual void PreOrderMap(MapFun) = 0;
    void Map(MapFun) override;
  };

  template <typename Data>
  class PostOrderMappableContainer : virtual public MappableContainer<Data>,
                                     virtual public PostOrderTraversableContainer<Data>
  {

  public:
    virtual ~PostOrderMappableContainer() = default;

    PostOrderMappableContainer &operator=(const PostOrderMappableContainer &) = delete;
    PostOrderMappableContainer &operator=(PostOrderMappableContainer &&) noexcept = delete;
    bool operator==(const PostOrderMappableContainer &) const noexcept = delete;
    bool operator!=(const PostOrderMappableContainer &) const noexcept = delete;

    using typename MappableContainer<Data>::MapFun;
    virtual void PostOrderMap(MapFun) = 0;
    void Map(MapFun) override;
  };

}

#include "mappable.cpp"

#endif
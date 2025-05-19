#ifndef LIST_HPP
#define LIST_HPP

#include "../container/linear.hpp"

namespace lasd
{

  /*******************************************************************************************************************************************************/
  template <typename Data>
  class List : virtual public MutableLinearContainer<Data>,
               virtual public ClearableContainer
  {

  protected:
    using Container::size;
    struct Node
    {
      Data data;
      Node *next = nullptr;

      Node() = default;
      explicit Node(const Data &value) : data(value) {}
      explicit Node(Data &&value) noexcept : data(std::move(value)) {}

      Node(const Node &other) : data(other.data), next(nullptr) {}

      Node(Node &&other) noexcept : data(std::move(other.data)), next(other.next)
      {
        other.next = nullptr;
      }

      virtual ~Node() = default;

      bool operator==(const Node &other) const noexcept
      {
        return (data == other.data);
      }

      bool operator!=(const Node &other) const noexcept
      {
        return !(*this == other);
      }
    };

    Node *head = nullptr;
    Node *tail = nullptr;

  public:
    List() = default;

    List(const TraversableContainer<Data> &);
    List(MappableContainer<Data> &&);

    List(const List &);

    List(List &&) noexcept;

    virtual ~List();

    List &operator=(const List &);

    List &operator=(List &&) noexcept;

    using LinearContainer<Data>::operator==;
    using LinearContainer<Data>::operator!=;

    bool operator==(const List &) const noexcept;
    bool operator!=(const List &) const noexcept;

    void InsertAtFront(const Data &);
    void InsertAtFront(Data &&) noexcept;
    void RemoveFromFront();
    Data FrontNRemove();

    void InsertAtBack(const Data &);
    void InsertAtBack(Data &&) noexcept;
    void RemoveFromBack();
    Data BackNRemove();

    Data &operator[](ulong) override;
    Data &Front() override;
    Data &Back() override;

    const Data &operator[](ulong) const override;
    const Data &Front() const override;
    const Data &Back() const override;

    using typename MappableContainer<Data>::MapFun;
    void Map(MapFun) override;

    void PreOrderMap(MapFun) override;
    void PostOrderMap(MapFun) override;

    using typename TraversableContainer<Data>::TraverseFun;
    void Traverse(TraverseFun) const override;

    void PreOrderTraverse(TraverseFun) const override;
    void PostOrderTraverse(TraverseFun) const override;

    void Clear() override;

  protected:
    Node *GetNodeAt(ulong index) const;
  };

  /*******************************************************************************************************************************************************/

}

#include "list.cpp"

#endif

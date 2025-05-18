
#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

/* ************************************************************************** */

#include "testable.hpp"
#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class DictionaryContainer : public TestableContainer<Data>
  {

  private:
  protected:
  public:
    // Destructor
    virtual ~DictionaryContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    DictionaryContainer &operator=(const DictionaryContainer &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    DictionaryContainer &operator=(const DictionaryContainer &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    DictionaryContainer &operator==(const DictionaryContainer &) = delete; // Comparison of abstract types is not possible.
    DictionaryContainer &operator!=(const DictionaryContainer &) = delete; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member functions
    virtual bool Insert(const Data &) = 0;
    virtual bool Insert(Data &&) = 0;
    virtual bool Remove(const Data &) = 0;

    virtual bool InsertAll(const TraversableContainer<Data> &); // Copy of the value; From TraversableContainer; True if all are inserted
    virtual bool InsertAll(MappableContainer<Data> &&);         // Move of the value; From MappableContainer; True if all are inserted
    virtual bool RemoveAll(const TraversableContainer<Data> &); // From TraversableContainer; True if all are removed

    virtual bool InsertSome(const TraversableContainer<Data> &); // Copy of the value; From TraversableContainer; True if some is inserted
    virtual bool InsertSome(MappableContainer<Data> &&);         // Move of the value; From MappableContainer; True if some is inserted
    virtual bool RemoveSome(const TraversableContainer<Data> &); // From TraversableContainer; True if some is removed
  };

  /* ************************************************************************** */

  template <typename Data>
  class OrderedDictionaryContainer : virtual public DictionaryContainer<Data>
  {
    // Must extend DictionaryContainer<Data>

  private:
  protected:
  public:
    virtual ~OrderedDictionaryContainer() = default;

    OrderedDictionaryContainer &operator=(const OrderedDictionaryContainer &) = delete;

    OrderedDictionaryContainer &operator=(OrderedDictionaryContainer &&) noexcept = delete;

    bool operator==(const OrderedDictionaryContainer &) const noexcept = delete;
    bool operator!=(const OrderedDictionaryContainer &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions

    virtual const Data &Min() const = 0; // (concrete function must throw std::length_error when empty)
    virtual Data MinNRemove();           // (concrete function must throw std::length_error when empty)
    virtual void RemoveMin();            // (concrete function must throw std::length_error when empty)

    virtual const Data &Max() const = 0; // (concrete function must throw std::length_error when empty)
    virtual Data MaxNRemove();           // (concrete function must throw std::length_error when empty)
    virtual void RemoveMax();            // (concrete function must throw std::length_error when empty)

    virtual const Data &Predecessor(const Data &) const = 0; // (concrete function must throw std::length_error when not found)
    virtual Data PredecessorNRemove(const Data &);           // (concrete function must throw std::length_error when not found)
    virtual void RemovePredecessor(const Data &);            // (concrete function must throw std::length_error when not found)

    virtual const Data &Successor(const Data &) const = 0; // (concrete function must throw std::length_error when not found)
    virtual Data SuccessorNRemove(const Data &);           // (concrete function must throw std::length_error when not found)
    virtual void RemoveSuccessor(const Data &);            // (concrete function must throw std::length_error when not found)
  };
  /* ************************************************************************** */
}

#include "dictionary.cpp"

#endif

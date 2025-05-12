
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
    ~DictionaryContainer() = default;

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

    bool Insert(Data &data);  // Copy of the value
    bool Insert(Data &&data); // Move of the value
    bool Remove(Data &data);

    // type InsertAll(argument) specifiers; // Copy of the value; From TraversableContainer; True if all are inserted
    // type InsertAll(argument) specifiers; // Move of the value; From MappableContainer; True if all are inserted
    // type RemoveAll(argument) specifiers; // From TraversableContainer; True if all are removed

    // type InsertSome(argument) specifiers; // Copy of the value; From TraversableContainer; True if some is inserted
    // type InsertSome(argument) specifiers; // Move of the value; From MappableContainer; True if some is inserted
    // type RemoveSome(argument) specifiers; // From TraversableContainer; True if some is removed
  };

  /* ************************************************************************** */

  template <typename Data>
  class OrderedDictionaryContainer
  {
    // Must extend DictionaryContainer<Data>

  private:
  protected:
  public:
    // Destructor
    // ~OrderedDictionaryContainer() specifiers

    /* ************************************************************************ */

    // Copy assignment
    // type operator=(argument); // Copy assignment of abstract types is not possible.

    // Move assignment
    // type operator=(argument); // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    // type operator==(argument) specifiers; // Comparison of abstract types is not possible.
    // type operator!=(argument) specifiers; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member functions

    // type Min(argument) specifiers; // (concrete function must throw std::length_error when empty)
    // type MinNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
    // type RemoveMin(argument) specifiers; // (concrete function must throw std::length_error when empty)

    // type Max(argument) specifiers; // (concrete function must throw std::length_error when empty)
    // type MaxNRemove(argument) specifiers; // (concrete function must throw std::length_error when empty)
    // type RemoveMax(argument) specifiers; // (concrete function must throw std::length_error when empty)

    // type Predecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
    // type PredecessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
    // type RemovePredecessor(argument) specifiers; // (concrete function must throw std::length_error when not found)

    // type Successor(argument) specifiers; // (concrete function must throw std::length_error when not found)
    // type SuccessorNRemove(argument) specifiers; // (concrete function must throw std::length_error when not found)
    // type RemoveSuccessor(argument) specifiers; // (concrete function must throw std::length_error when not found)
  };

  /* ************************************************************************** */

}

#include "dictionary.cpp"

#endif


#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  typedef unsigned long ulong;

  class Container
  {

  private:
  protected:
    // ...
    ulong size;

    /* ************************************************************************ */

    // Default constructor
    Container(const ulong s = 0) : size(s) {}

  public:
    // Destructor
    virtual ~Container() = default;

    /* ************************************************************************ */

    // Copy assignment
    Container &operator=(const Container &) = delete;

    // Move assignment
    Container &operator=(Container &&) = delete;

    /* ************************************************************************ */

    // Comparison operators
    Container &operator!=(Container &) = delete; // Comparison of abstract types is not possible.
    Container &operator==(Container &) = delete; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member functions

    bool Empty(); // (concrete function should not throw exceptions)
    uint Size();  // (concrete function should not throw exceptions)
  };

  /* ************************************************************************** */

  class ClearableContainer : public Container
  {
  private:
  protected:
  public:
    // Destructor
    virtual ~ClearableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    ClearableContainer &operator=(const ClearableContainer &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    ClearableContainer &operator=(const ClearableContainer &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    ClearableContainer &operator==(const ClearableContainer &) = delete; // Comparison of abstract types is not possible.
    ClearableContainer &operator!=(const ClearableContainer &) = delete; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member functions

    virtual void Clear();
  };

  /* ************************************************************************** */

  class ResizableContainer : public ClearableContainer
  {
  private:
  protected:
  public:
    // Destructor
    virtual ~ResizableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    ResizableContainer &operator=(const ResizableContainer &) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    ResizableContainer &operator=(const ResizableContainer &&) = delete; // Move assignment of abstract types is not possible.

    /* ************************************************************************ */

    // Comparison operators
    ResizableContainer &operator==(const ResizableContainer &) = delete; // Comparison of abstract types is not possible.
    ResizableContainer &operator!=(const ResizableContainer &) = delete; // Comparison of abstract types is not possible.

    /* ************************************************************************ */

    // Specific member functions

    void Resize(ulong s);

    /* ************************************************************************ */

    // Specific member function (inherited from ClearableContainer)

    void Clear() override;
  };

  /* ************************************************************************** */

}

#endif

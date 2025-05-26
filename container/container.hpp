#ifndef CONTAINER_HPP
#define CONTAINER_HPP
#define ulong unsigned long

namespace lasd
{

  class Container
  {
  protected:
    ulong size = 0;

    Container() = default;

  public:
    virtual ~Container() = default;

    Container &operator=(const Container &) = delete;
    Container &operator=(Container &&) noexcept = delete;

    bool operator==(const Container &) const noexcept = delete;
    bool operator!=(const Container &) const noexcept = delete;

    bool Empty() const noexcept
    {
      return (size == 0);
    }

    ulong Size() const noexcept
    {
      return size;
    }
  };

  class ClearableContainer : virtual public Container
  {

  public:
    virtual ~ClearableContainer() = default;

    ClearableContainer &operator=(const ClearableContainer &) = delete;
    ClearableContainer &operator=(ClearableContainer &&) noexcept = delete;

    bool operator==(const ClearableContainer &) const noexcept = delete;
    bool operator!=(const ClearableContainer &) const noexcept = delete;

    virtual void Clear() = 0;
  };

  class ResizableContainer : virtual public ClearableContainer
  {

  public:
    virtual ~ResizableContainer() = default;

    ResizableContainer &operator=(const ResizableContainer &) = delete;
    ResizableContainer &operator=(ResizableContainer &&) noexcept = delete;

    bool operator==(const ResizableContainer &) const noexcept = delete;
    bool operator!=(const ResizableContainer &) const noexcept = delete;

    virtual void Resize(ulong) = 0;

    void Clear() override
    {
      Resize(0);
    }
  };
}

#endif
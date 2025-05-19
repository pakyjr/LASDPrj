#include "list.hpp"
#include <stack>

namespace lasd
{

    /*******************************************************************************************************************************************************/

    // Constructor from TraversableContainer (copy)
    template <typename Data>
    List<Data>::List(const TraversableContainer<Data> &container)
    {
        container.Traverse([this](const Data &data)
                           { InsertAtBack(data); });
    }

    // Constructor from MappableContainer (move)
    template <typename Data>
    List<Data>::List(MappableContainer<Data> &&container)
    {
        container.Map([this](Data &data)
                      { InsertAtBack(std::move(data)); });
    }

    // Copy constructor
    template <typename Data>
    List<Data>::List(const List<Data> &other)
    {
        Node *current = other.head;
        while (current != nullptr)
        {
            InsertAtBack(current->data);
            current = current->next;
        }
    }

    // Move constructor
    template <typename Data>
    List<Data>::List(List &&other) noexcept
    {
        head = other.head;
        tail = other.tail;
        size = other.size;
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    // Destructor
    template <typename Data>
    List<Data>::~List()
    {
        Clear();
    }

    /*******************************************************************************************************************************************************/

    // Copy assignment operator
    template <typename Data>
    List<Data> &List<Data>::operator=(const List<Data> &other)
    {
        if (this != &other)
        {
            Clear();
            Node *current = other.head;
            while (current != nullptr)
            {
                InsertAtBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Move assignment operator
    template <typename Data>
    List<Data> &List<Data>::operator=(List &&other) noexcept
    {
        if (this != &other)
        {
            std::swap(head, other.head);
            std::swap(tail, other.tail);
            std::swap(size, other.size);
        }
        return *this;
    }

    /*******************************************************************************************************************************************************/

    // Comparison operators
    template <typename Data>
    bool List<Data>::operator==(const List<Data> &other) const noexcept
    {
        if (size != other.size)
            return false;

        Node *a = head;
        Node *b = other.head;
        while (a != nullptr)
        {
            if (a->data != b->data)
                return false;
            a = a->next;
            b = b->next;
        }
        return true;
    }

    template <typename Data>
    bool List<Data>::operator!=(const List<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    /*******************************************************************************************************************************************************/

    // Insert at front (copy)
    template <typename Data>
    void List<Data>::InsertAtFront(const Data &value)
    {
        Node *newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr)
            tail = head;
        size++;
    }

    // Insert at front (move)
    template <typename Data>
    void List<Data>::InsertAtFront(Data &&value) noexcept
    {
        Node *newNode = new Node(std::move(value));
        newNode->next = head;
        head = newNode;
        if (tail == nullptr)
            tail = head;
        size++;
    }

    // Remove from front
    template <typename Data>
    void List<Data>::RemoveFromFront()
    {
        if (Empty())
            throw std::length_error("Empty list");

        Node *temp = head;
        head = head->next;
        delete temp;
        if (head == nullptr)
            tail = nullptr;
        size--;
    }

    // Extract and remove front element
    template <typename Data>
    Data List<Data>::FrontNRemove()
    {
        if (Empty())
            throw std::length_error("Empty list");

        Data result = head->data;
        RemoveFromFront();
        return result;
    }

    /*******************************************************************************************************************************************************/

    // Insert at back (copy)
    template <typename Data>
    void List<Data>::InsertAtBack(const Data &value)
    {
        Node *newNode = new Node(value);
        if (tail == nullptr)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Insert at back (move)
    template <typename Data>
    void List<Data>::InsertAtBack(Data &&value) noexcept
    {
        Node *newNode = new Node(std::move(value));
        if (tail == nullptr)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Remove from back
    template <typename Data>
    void List<Data>::RemoveFromBack()
    {
        if (Empty())
            throw std::length_error("Empty list");

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node *current = head;
            while (current->next != tail)
            {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        size--;
    }

    // Extract and remove back element
    template <typename Data>
    Data List<Data>::BackNRemove()
    {
        if (Empty())
            throw std::length_error("Empty list");

        Data value;
        if (head == tail)
        {
            value = std::move(head->data);
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node *current = head;
            while (current->next != tail)
            {
                current = current->next;
            }
            value = std::move(tail->data);
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        size--;
        return value;
    }

    /*******************************************************************************************************************************************************/

    // Element access and modification (MutableLinearContainer)
    template <typename Data>
    Data &List<Data>::operator[](ulong index)
    {
        if (index >= size)
            throw std::out_of_range("Index out of range");
        return GetNodeAt(index)->data;
    }

    template <typename Data>
    Data &List<Data>::Front()
    {
        if (Empty())
            throw std::length_error("Empty list");
        return head->data;
    }

    template <typename Data>
    Data &List<Data>::Back()
    {
        if (Empty())
            throw std::length_error("Empty list");
        return tail->data;
    }

    // Read-only access (LinearContainer)
    template <typename Data>
    const Data &List<Data>::operator[](ulong index) const
    {
        if (index >= size)
            throw std::out_of_range("Index out of range");
        return GetNodeAt(index)->data;
    }

    template <typename Data>
    const Data &List<Data>::Front() const
    {
        if (Empty())
            throw std::length_error("Empty list");
        return head->data;
    }

    template <typename Data>
    const Data &List<Data>::Back() const
    {
        if (Empty())
            throw std::length_error("Empty list");
        return tail->data;
    }

    /*******************************************************************************************************************************************************/

    // Mapping
    template <typename Data>
    void List<Data>::Map(MapFun fun)
    {
        PreOrderMap(fun);
    }

    // Pre-order map
    template <typename Data>
    void List<Data>::PreOrderMap(MapFun fun)
    {
        Node *current = head;
        while (current != nullptr)
        {
            fun(current->data);
            current = current->next;
        }
    }

    // Post-order map
    template <typename Data>
    void List<Data>::PostOrderMap(MapFun fun)
    {
        std::stack<Node *> stack;
        Node *current = head;
        while (current != nullptr)
        {
            stack.push(current);
            current = current->next;
        }
        while (!stack.empty())
        {
            fun(stack.top()->data);
            stack.pop();
        }
    }

    /*******************************************************************************************************************************************************/

    // Traversals
    template <typename Data>
    void List<Data>::Traverse(TraverseFun fun) const
    {
        PreOrderTraverse(fun);
    }

    // Pre-order traversal
    template <typename Data>
    void List<Data>::PreOrderTraverse(TraverseFun fun) const
    {
        Node *current = head;
        while (current != nullptr)
        {
            fun(current->data);
            current = current->next;
        }
    }

    // Post-order traversal
    template <typename Data>
    void List<Data>::PostOrderTraverse(TraverseFun fun) const
    {
        std::stack<Node *> stack;
        Node *current = head;
        while (current != nullptr)
        {
            stack.push(current);
            current = current->next;
        }
        while (!stack.empty())
        {
            fun(stack.top()->data);
            stack.pop();
        }
    }

    /*******************************************************************************************************************************************************/

    // Clear container (ClearableContainer)
    template <typename Data>
    void List<Data>::Clear()
    {
        while (!Empty())
        {
            RemoveFromFront();
        }
    }

    /*******************************************************************************************************************************************************/

    // Auxiliary method
    template <typename Data>
    typename List<Data>::Node *List<Data>::GetNodeAt(ulong index) const
    {
        Node *current = head;
        for (ulong i = 0; i < index && current != nullptr; i++)
        {
            current = current->next;
        }
        return current;
    }

    /*******************************************************************************************************************************************************/
}
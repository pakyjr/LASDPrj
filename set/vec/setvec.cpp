#include "setvec.hpp"
namespace lasd
{

    /*******************************************************************************************************************************************************/
    /* Funzioni ausiliarie protette */

    // Trova l'indice esatto di un elemento nel vettore ordinato (ricerca binaria)
    template <typename Data>
    ulong SetVec<Data>::FindIndex(const Data &data) const
    {
        if (size == 0 || Vector<Data>::elements == nullptr)
            return size;

        ulong left = 0;
        ulong right = size - 1;

        while (left <= right)
        {
            ulong mid = left + (right - left) / 2;

            if (Vector<Data>::elements[mid] == data)
                return mid;

            if (Vector<Data>::elements[mid] < data)
                left = mid + 1;
            else
            {
                if (mid == 0)
                    break;
                right = mid - 1;
            }
        }

        return size; // Elemento non trovato
    }

    // Trova la posizione corretta per l'inserimento in ordine
    template <typename Data>
    ulong SetVec<Data>::FindInsertionIndex(const Data &data) const
    {
        if (size == 0 || Vector<Data>::elements == nullptr)
            return 0;

        ulong left = 0;
        ulong right = size - 1;

        while (left <= right)
        {
            ulong mid = left + (right - left) / 2;

            if (Vector<Data>::elements[mid] == data)
                return mid;

            if (Vector<Data>::elements[mid] < data)
                left = mid + 1;
            else
            {
                if (mid == 0)
                    break;
                right = mid - 1;
            }
        }

        return left;
    }

    // Sposta tutti gli elementi a destra dall'indice specificato
    template <typename Data>
    void SetVec<Data>::ShiftRight(ulong index)
    {
        ulong newSize = size + 1;
        Data *newElements = new Data[newSize]{};

        for (ulong i = 0; i < index && i < size; ++i)
            newElements[i] = Vector<Data>::elements[i];

        for (ulong i = index; i < size; ++i)
            newElements[i + 1] = Vector<Data>::elements[i];

        delete[] Vector<Data>::elements;
        Vector<Data>::elements = newElements;
        size = newSize;
    }

    // Sposta tutti gli elementi a sinistra dall'indice specificato
    template <typename Data>
    void SetVec<Data>::ShiftLeft(ulong index)
    {
        if (size == 0 || Vector<Data>::elements == nullptr)
            return;

        if (size == 1)
        {
            delete[] Vector<Data>::elements;
            Vector<Data>::elements = nullptr;
            size = 0;
            return;
        }

        ulong newSize = size - 1;
        Data *newElements = new Data[newSize]{};

        for (ulong i = 0; i < index && i < size; ++i)
            newElements[i] = Vector<Data>::elements[i];

        for (ulong i = index + 1; i < size; ++i)
            newElements[i - 1] = Vector<Data>::elements[i];

        delete[] Vector<Data>::elements;
        Vector<Data>::elements = newElements;
        size = newSize;
    }

    /*******************************************************************************************************************************************************/
    /* Costruttori specifici */

    template <typename Data>
    SetVec<Data>::SetVec(const TraversableContainer<Data> &container) : Vector<Data>()
    {
        std::vector<Data> temp;
        container.Traverse([&temp](const Data &val)
                           { temp.push_back(val); });

        for (const auto &val : temp)
            Insert(val);
    }

    template <typename Data>
    SetVec<Data>::SetVec(MappableContainer<Data> &&container) : Vector<Data>()
    {
        std::vector<Data> temp;
        container.Map([&temp](Data &val)
                      { temp.push_back(std::move(val)); });

        for (auto &val : temp)
            Insert(std::move(val));
    }

    /*******************************************************************************************************************************************************/
    /* Costruttori e assegnazioni */

    template <typename Data>
    SetVec<Data>::SetVec(const SetVec<Data> &other) : Vector<Data>(other) {}

    template <typename Data>
    SetVec<Data>::SetVec(SetVec<Data> &&other) noexcept : Vector<Data>(std::move(other)) {}

    template <typename Data>
    SetVec<Data> &SetVec<Data>::operator=(const SetVec<Data> &other)
    {
        Vector<Data>::operator=(other);
        return *this;
    }

    template <typename Data>
    SetVec<Data> &SetVec<Data>::operator=(SetVec<Data> &&other) noexcept
    {
        Vector<Data>::operator=(std::move(other));
        return *this;
    }

    /*******************************************************************************************************************************************************/
    /* Operatori di confronto */

    template <typename Data>
    bool SetVec<Data>::operator==(const SetVec<Data> &other) const noexcept
    {
        return Vector<Data>::operator==(other);
    }

    template <typename Data>
    inline bool SetVec<Data>::operator!=(const SetVec<Data> &other) const noexcept
    {
        return !(*this == other);
    }

    /*******************************************************************************************************************************************************/
    /* Funzioni specifiche (OrderedDictionaryContainer) */

    template <typename Data>
    const Data &SetVec<Data>::Min() const
    {
        if (size == 0)
            throw std::length_error("Empty set");
        return Vector<Data>::elements[0];
    }

    template <typename Data>
    Data SetVec<Data>::MinNRemove()
    {
        if (size == 0)
            throw std::length_error("Empty set");
        Data min = Vector<Data>::elements[0];
        ShiftLeft(0);
        return min;
    }

    template <typename Data>
    void SetVec<Data>::RemoveMin()
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ShiftLeft(0);
    }

    template <typename Data>
    const Data &SetVec<Data>::Max() const
    {
        if (size == 0)
            throw std::length_error("Empty set");
        return Vector<Data>::elements[size - 1];
    }

    template <typename Data>
    Data SetVec<Data>::MaxNRemove()
    {
        if (size == 0)
            throw std::length_error("Empty set");
        Data max = Vector<Data>::elements[size - 1];
        ShiftLeft(size - 1);
        return max;
    }

    template <typename Data>
    void SetVec<Data>::RemoveMax()
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ShiftLeft(size - 1);
    }

    template <typename Data>
    const Data &SetVec<Data>::Predecessor(const Data &data) const
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ulong index = FindInsertionIndex(data);
        if (index == 0)
            throw std::length_error("Predecessor not found");
        return Vector<Data>::elements[index - 1];
    }

    template <typename Data>
    Data SetVec<Data>::PredecessorNRemove(const Data &data)
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ulong index = FindInsertionIndex(data);
        if (index == 0)
            throw std::length_error("Predecessor not found");
        Data pred = Vector<Data>::elements[index - 1];
        ShiftLeft(index - 1);
        return pred;
    }

    template <typename Data>
    void SetVec<Data>::RemovePredecessor(const Data &data)
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ulong index = FindInsertionIndex(data);
        if (index == 0)
            throw std::length_error("Predecessor not found");
        ShiftLeft(index - 1);
    }

    template <typename Data>
    const Data &SetVec<Data>::Successor(const Data &data) const
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ulong index = FindInsertionIndex(data);

        if (index >= size || Vector<Data>::elements[index] == data)
        {
            if (++index >= size)
                throw std::length_error("Successor not found");
        }

        return Vector<Data>::elements[index];
    }

    template <typename Data>
    Data SetVec<Data>::SuccessorNRemove(const Data &data)
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ulong index = FindInsertionIndex(data);

        if (index >= size || Vector<Data>::elements[index] == data)
        {
            if (++index >= size)
                throw std::length_error("Successor not found");
        }

        Data succ = Vector<Data>::elements[index];
        ShiftLeft(index);
        return succ;
    }

    template <typename Data>
    void SetVec<Data>::RemoveSuccessor(const Data &data)
    {
        if (size == 0)
            throw std::length_error("Empty set");
        ulong index = FindInsertionIndex(data);

        if (index >= size || Vector<Data>::elements[index] == data)
        {
            if (++index >= size)
                throw std::length_error("Successor not found");
        }

        ShiftLeft(index);
    }

    /*******************************************************************************************************************************************************/
    /* Funzioni specifiche (DictionaryContainer) */

    template <typename Data>
    bool SetVec<Data>::Insert(const Data &data)
    {
        if (size > 0 && Vector<Data>::elements != nullptr)
        {
            ulong index = FindInsertionIndex(data);
            if (index < size && Vector<Data>::elements[index] == data)
                return false;

            ShiftRight(index);
            Vector<Data>::elements[index] = data;
        }
        else
        {
            Vector<Data>::elements = new Data[1];
            Vector<Data>::elements[0] = data;
            size = 1;
        }

        return true;
    }

    template <typename Data>
    bool SetVec<Data>::Insert(Data &&data)
    {
        if (size > 0 && Vector<Data>::elements != nullptr)
        {
            ulong index = FindInsertionIndex(data);
            if (index < size && Vector<Data>::elements[index] == data)
                return false;

            ShiftRight(index);
            Vector<Data>::elements[index] = std::move(data);
        }
        else
        {
            Vector<Data>::elements = new Data[1];
            Vector<Data>::elements[0] = std::move(data);
            size = 1;
        }

        return true;
    }

    template <typename Data>
    bool SetVec<Data>::Remove(const Data &data)
    {
        if (size == 0 || Vector<Data>::elements == nullptr)
            return false;

        ulong index = FindIndex(data);
        if (index >= size)
            return false;

        ShiftLeft(index);
        return true;
    }

    /*******************************************************************************************************************************************************/

}

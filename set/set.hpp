#ifndef SET_HPP
#define SET_HPP

#include "../container/dictionary.hpp"
#include "../container/traversable.hpp"

/*******************************************************************************************************************************************************/

namespace lasd
{

  /*******************************************************************************************************************************************************/

  template <typename Data>
  class Set : virtual public OrderedDictionaryContainer<Data>,
              virtual public LinearContainer<Data>,
              virtual public ClearableContainer
  {
  public:
    // Distruttore
    virtual ~Set() = default;

    /*******************************************************************************************************************************************************/

    // Assegnazione copia disabilitata (tipo astratto)
    Set &operator=(const Set &) = delete;

    // Assegnazione spostamento disabilitata (tipo astratto)
    Set &operator=(Set &&) noexcept = delete;
  };

  /*******************************************************************************************************************************************************/

}

#endif

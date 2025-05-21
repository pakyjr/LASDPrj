#ifndef SETVEC_HPP
#define SETVEC_HPP

#include "../set.hpp"
#include "../../vector/vector.hpp"

namespace lasd {

/*******************************************************************************************************************************************************/

// Classe SetVec
// Estende Set, Vector e ResizableContainer per rappresentare un insieme ordinato
// implementato con array dinamico ordinato (senza duplicati)

template <typename Data>
class SetVec : virtual public Set<Data>,
               virtual public Vector<Data>,
               virtual public ResizableContainer {

protected:

  using Container::size;

  // Funzione ausiliaria per trovare la posizione di un elemento (ricerca binaria)
  ulong FindIndex(const Data&) const;

public:

  // Costruttore di default
  SetVec() = default;

  // Costruttore da TraversableContainer (per copia)
  SetVec(const TraversableContainer<Data>&);

  // Costruttore da MappableContainer (per move)
  SetVec(MappableContainer<Data>&&);

  // Costruttore di copia
  SetVec(const SetVec&);

  // Costruttore di move
  SetVec(SetVec&&) noexcept;

  // Distruttore
  virtual ~SetVec() = default;

  // Assegnazione di copia
  SetVec& operator=(const SetVec&);

  // Assegnazione di move
  SetVec& operator=(SetVec&&) noexcept;

  using LinearContainer<Data>::operator==;
  using LinearContainer<Data>::operator!=;

  // Operatori di confronto
  bool operator==(const SetVec&) const noexcept;
  inline bool operator!=(const SetVec&) const noexcept;

/*******************************************************************************************************************************************************/

  // Funzioni specifiche (OrderedDictionaryContainer)

  const Data& Min() const override;             // Restituisce il minimo (lancia eccezione se vuoto)
  Data MinNRemove() override;                   // Restituisce e rimuove il minimo
  void RemoveMin() override;                    // Rimuove il minimo

  const Data& Max() const override;             // Restituisce il massimo (lancia eccezione se vuoto)
  Data MaxNRemove() override;                   // Restituisce e rimuove il massimo
  void RemoveMax() override;                    // Rimuove il massimo

  const Data& Predecessor(const Data&) const override;       // Restituisce il predecessore
  Data PredecessorNRemove(const Data&) override;             // Restituisce e rimuove il predecessore
  void RemovePredecessor(const Data&) override;              // Rimuove il predecessore

  const Data& Successor(const Data&) const override;         // Restituisce il successore
  Data SuccessorNRemove(const Data&) override;               // Restituisce e rimuove il successore
  void RemoveSuccessor(const Data&) override;                // Rimuove il successore

/*******************************************************************************************************************************************************/

  // Funzioni specifiche (DictionaryContainer)

  bool Insert(const Data&) override;      // Inserimento per copia (solo se non già presente)
  bool Insert(Data&&) override;           // Inserimento per move (solo se non già presente)
  bool Remove(const Data&) override;      // Rimozione (solo se presente)

protected:

  // Funzioni ausiliarie per mantenere l'ordinamento
  ulong FindInsertionIndex(const Data&) const;  // Trova la posizione corretta di inserimento
  void ShiftRight(ulong);                       // Sposta a destra gli elementi dall'indice dato
  void ShiftLeft(ulong);                        // Sposta a sinistra gli elementi dall'indice dato
};

/*******************************************************************************************************************************************************/

}

#include "setvec.cpp"

#endif

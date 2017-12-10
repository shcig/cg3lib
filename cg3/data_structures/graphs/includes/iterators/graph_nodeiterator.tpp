/**
    @author Stefano Nuvoli
*/
#include "graph_nodeiterator.h"

namespace cg3 {



/* ----- OPERATOR OVERLOAD ----- */


template <class T>
bool Graph<T>::NodeIterator::operator ==(
        const NodeIterator& otherIterator) const
{
    return (this->node == otherIterator.node);
}

template <class T>
bool Graph<T>::NodeIterator::operator !=(const NodeIterator& otherIterator) const
{
    return !(*this == otherIterator);
}



template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator ++()
{
    this->next();
    return *this;
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator ++(int)
{
    NodeIterator oldIt = *this;
    this->next();
    return oldIt;
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator --()
{
    this->prev();
    return *this;
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::NodeIterator::operator --(int)
{
    NodeIterator oldIt = *this;
    this->prev();
    return oldIt;
}


template <class T>
const T& Graph<T>::NodeIterator::operator *() const
{
    return node->value;
}



/* ----- PROTECTED METHODS FOR NAVIGATION ----- */

template <class T>
void Graph<T>::NodeIterator::next() {
    unsigned int newPos;
    node = graph->getNextNode(pos, newPos);
    pos = newPos;
}

template <class T>
void Graph<T>::NodeIterator::prev() {
    unsigned int newPos;
    node = graph->getPrevNode(pos, newPos);
    pos = newPos;
}





/* --------- RANGE BASED ITERATOR --------- */

template <class T>
Graph<T>::RangeBasedNodeIterator::RangeBasedNodeIterator(Graph<T>* graph) {
    this->graph = graph;
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::RangeBasedNodeIterator::begin() {
    return this->graph->nodeIteratorBegin();
}

template <class T>
typename Graph<T>::NodeIterator Graph<T>::RangeBasedNodeIterator::end() {
    return this->graph->nodeIteratorEnd();
}


}

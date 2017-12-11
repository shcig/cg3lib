/**
    @author Stefano Nuvoli
*/
#ifndef CG3_TREEGENERICITERATOR_H
#define CG3_TREEGENERICITERATOR_H

namespace cg3 {

/**
 * @brief The generic iterator for the binary search tree
 */
template <class B, class N>
class TreeGenericIterator {

    template <class T1, class T2, class T3>
    friend class TreeIterator;
    template <class T1, class T2, class T3>
    friend class TreeReverseIterator;

    template <class T1, class T2>
    friend class BSTInner;
    template <class T1, class T2>
    friend class BSTLeaf;
    template <class T1, class T2>
    friend class AVLInner;
    template <class T1, class T2>
    friend class AVLLeaf;
    template <class T1, class T2>
    friend class RangeTree;
    template <int T1, class T2, class T3>
    friend class AABBTree;

protected:

    /* Constructors */

    inline TreeGenericIterator(B* bst, N* node) :
        bst(bst), node(node) {}


    /* Fields */

    B* bst;
    N* node;

};


}

#endif // CG3_TREEGENERICITERATOR_H

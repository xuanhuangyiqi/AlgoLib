#include "Graph.h"

namespace Tree {
    class BaseTree
    {
        private:
        int depth, size;
        public:
        BaseTree()
        {
            depth = 0;
            size = 0;
        }
    };
    class BinaryTree
    {
        private:
        BinaryTree * lchild, rchild, father;
        int v, depth;
        public:
        BinaryTree(int v, BinaryTree * f)
        {
            value = v;
            lchild = NULL;
            rchild = NULL;
            father = f;
            if (f == NULL)
                depth = 1;
            else
                depth = f->getDepth() + 1;
        }
        bool hasLChild(){ return (lchild != NULL);}
        bool hasRChild(){ return (rchild != NULL);}
        bool isRoot(){ return (father == NULL);}

    };
}

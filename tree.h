namespace Tree {
    template <typename T>
    struct BinaryTreeNode
    {
        BinaryTreeNode<T> * lchild, * rchild, * father; 
        T val;
        BinaryTreeNode(T v): val(v), lchild(NULL), rchild(NULL), father(NULL) { }
    }

    class BaseTree
    {
        private:
        int _depth, _size;
        public:
        BaseTree()
        {
            _depth = 0;
            _size = 0;
        }
    };

    template <typename T>
    class BinaryTree : public BaseTree
    {
        private:
        BinaryTreeNode<T> * _root;
        public:
        BinaryTree(): _root(NULL)
        {
        }
        BinaryTree(T v)
        {
        }
    };
}

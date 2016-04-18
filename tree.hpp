namespace Tree {
    template <typename T>
    struct BinaryTreeNode
    {
        BinaryTreeNode<T> * lchild, * rchild, * father; 
        T val;
        int depth, num_children;
        BinaryTreeNode(T v): val(v), lchild(NULL), rchild(NULL), father(NULL), depth(0), num_children(0){ }
        BinaryTreeNode(T v, int d): val(v), lchild(NULL), rchild(NULL), father(NULL), depth(d), num_children(0){ }
    };

    template <typename T>
    class BinaryTree
    {
        private:
        Tree::BinaryTreeNode<T> * _root;
        public:
        BinaryTree(): _root(NULL) { }
        BinaryTree(T v)
        {
            _root = new Tree::BinaryTreeNode<T>(v);
        }
        BinaryTreeNode<T> * get_root() { return _root; }
        void add_lchild(BinaryTreeNode<T> *node, T v)
        {
            assert(node != NULL);
            assert(node->lchild == NULL);
            node->lchild = BinaryTreeNode<T>(v, node->depth + 1);
            node->lchild->father = node;
        }
        void add_rchild(BinaryTreeNode<T> *node, T v)
        {
            assert(node != NULL);
            assert(node->rchild == NULL);
            node->rchild = BinaryTreeNode<T>(v, node->depth + 1);
            node->rchild->father = node;
        }
    };
    template <typename T>
    class Heap
    {
        private:
        std::vector<T> heap;

        int switch_up(int idx)
        {
            while (idx > 0)
            {
                int father_idx = (idx + 1) / 2 - 1;
                if (cmp(heap[idx], heap[father_idx]))
                {
                    T temp = heap[idx];
                    heap[idx] = heap[father_idx];
                    heap[father_idx] = temp;
                }
                idx = father_idx;
            }
            return idx;
        }

        void switch_down(int idx)
        {
            int lchild, rchild, choice;
            while (true)
            {
                lchild = (idx + 1) * 2 - 1;
                rchild = (idx + 1) * 2;
                if (lchild >= heap.size())
                    break;
                if (rchild >= heap.size() || (cmp(heap[lchild], heap[rchild])))
                    choice = lchild;
                else
                    choice = rchild;
                if (cmp(heap[choice], heap[idx]))
                {
                    T temp = heap[choice];
                    heap[choice] = heap[idx];
                    heap[idx] = temp;
                    idx = choice;
                }
                else
                    break;
            }
        }

        bool cmp(T a, T b) { return (a < b); }

        public:
        void init()
        {
            //TODO: allocate space
        }

        Heap()
        {
            init();
        }

        Heap(std::vector<T> arr)
        {
            init();
            for (int i = 0; i < arr.size(); ++i)
                push(arr[i]);
        }

        T top()
        {
            return heap[0];
        }

        int size() { return heap.size(); }

        void pop()
        {
            assert(heap.size() > 0);
            if (heap.size() == 1)
                heap.pop_back();
            else
            {
                heap[0] = heap.back();
                heap.pop_back();
                switch_down(0);
            }
        }

        void del(int idx)
        {
            assert(idx < heap.size());
            heap[idx] = heap.back();
            heap.pop();
            if (idx < heap.size())
                switch_down(idx);
        }

        int push(T e)
        {
            heap.push_back(e);
            return switch_up(heap.size() - 1);
        }
    };

    template<typename T>
    class ReverseHeap: Tree::Heap<T>
    {
        public:
        bool cmp(T a, T b){ return a > b;}
    };

}

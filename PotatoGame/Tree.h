#if !defined(PG_TREE_H)
#define PG_TREE_H

#include "List.h"
namespace PG {
	namespace Core {

		template <class TreeNode>
		class TreeNode {
		protected:
			List<TreeNode> *child;
		public:
			TreeNode() {
				child = new List<TreeNode>(true);
			}
			virtual ~TreeNode() {
				delete(child);
			}
			void TreeNode::AddChild(TreeNode *new_node) {
				if (new_node != nullptr) {
					child->Add(new_node);
				}
			}
			void TreeNode::ChildAt(int location) {
				if (location >= child->element_count || location < 0) {
					return nullptr;
				}
				for (ListNode<TreeNode> *c_node = child->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
					if (location == 0) {
						return c_node->GetData();
					}
					else {
						location--;
					}

				}
			}

		};

		template <class TreeNode>
		class Tree {
		protected:

		public:
			List<TreeNode> *roots;
			Tree() {
				roots = new List<TreeNode>(true);
			}
			virtual ~Tree() {
				delete(roots);
			}
			void Tree::PushRoot(TreeNode* new_root) {
				if (new_root == nullptr) return;
				roots->Add(new_root);
			}

		};

	}
}
#endif
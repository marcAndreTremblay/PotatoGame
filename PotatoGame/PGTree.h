#if !defined(PG_TREE_H)
#define PG_TREE_H

#include "PGList.h"

namespace PGCore {

	template <class TreeNode>
	class TreeNode {
	protected:
		PGList<TreeNode> *child;
	public:
		TreeNode() {
			child = new PGList<TreeNode>(true);
		}
		~TreeNode() {
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
			for (PGListNode<TreeNode> *c_node = child->GetHead(); c_node != nullptr; c_node = c_node->GetNext()) {
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
		PGList<TreeNode> *roots;
		Tree() {
			roots = new PGList<TreeNode>(true);
		}
		~Tree() {
			delete(roots);
		}
		void Tree::PushRoot(TreeNode* new_root) {
			if (new_root == nullptr) return;
			roots->Add(new_root);
		}

	};

}

#endif
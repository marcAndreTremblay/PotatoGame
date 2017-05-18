#include "stdafx.h"
#include "AnimatorManager.h"


AnimatorManager::AnimatorManager() {
	
	animation_list = new List<IAnimation>(false);
}


AnimatorManager::~AnimatorManager() {
	delete(animation_list);
}

void AnimatorManager::Update(double delta_time) {
	ListNode<IAnimation> *c_node = animation_list->GetHead();
	for (c_node; c_node != nullptr; c_node = c_node->GetNext()) {
		IAnimation* c_animation = c_node->GetData();
			c_animation->Update(delta_time);
	}
}

void AnimatorManager::AttachAnimation(IAnimation *animation) {
	if (animation != nullptr) {
		animation_list->Add(animation);
	}
}

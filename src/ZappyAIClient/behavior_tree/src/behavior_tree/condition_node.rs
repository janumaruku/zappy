use crate::behavior_tree::{BehaviorNode, BlackBoard, NodeStatus};

pub struct ConditionNode<F: Fn(&BlackBoard) -> bool> {
    func: F,
}

impl<F: Fn(&BlackBoard) -> bool> ConditionNode<F> {
    pub fn new(predicate: F) -> Self {
        ConditionNode {
            func: predicate,
        }
    }
}

impl <F: Fn(&BlackBoard) -> bool> BehaviorNode for ConditionNode<F> {
    fn tick(&mut self, blackboard: &mut BlackBoard) -> NodeStatus {
        if (self.func)(blackboard) {
            NodeStatus::Success
        } else {
            NodeStatus::Failure
        }
    }
}

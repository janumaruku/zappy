use crate::behavior_tree::{BehaviorNode, BlackBoard, NodeStatus};

pub struct ActionNode<F: FnMut(&mut BlackBoard) -> NodeStatus> {
    func: F,
}

impl<F: FnMut(&mut BlackBoard) -> NodeStatus> ActionNode<F> {
    pub fn new(func: F) -> Self {
        ActionNode { func }
    }
}

impl<F: FnMut(&mut BlackBoard) -> NodeStatus> BehaviorNode for ActionNode<F> {
    fn tick(&mut self, blackboard: &mut BlackBoard) -> NodeStatus {
        (self.func)(blackboard)
    }
}

use crate::behavior_tree::{BehaviorNode, BlackBoard, NodeStatus};

pub struct RetryUntilNode<F: Fn(&mut BlackBoard) -> bool> {
    child: Box<dyn BehaviorNode>,
    predicate: F,
}

impl<F: Fn(&mut BlackBoard) -> bool> RetryUntilNode<F> {
    pub fn new(predicate: F, child: Box<dyn BehaviorNode>) -> Self {
        Self { child, predicate }
    }
}

impl<F: Fn(&mut BlackBoard) -> bool> BehaviorNode for RetryUntilNode<F> {
    fn tick(&mut self, blackboard: &mut BlackBoard) -> NodeStatus {
        if (self.predicate)(blackboard) {
            return NodeStatus::Success;
        }

        self.child.tick(blackboard);
        NodeStatus::Running
    }
}

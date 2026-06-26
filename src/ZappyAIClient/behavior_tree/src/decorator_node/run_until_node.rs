use crate::behavior_tree::{BehaviorNode, BlackBoard, NodeStatus};

pub struct RunUntilNode<F: Fn(&BlackBoard) -> bool> {
    predicate: F,
    child: Box<dyn BehaviorNode>,
}

impl<F: Fn(&BlackBoard) -> bool> RunUntilNode<F> {
    pub fn new(predicate: F, child: Box<dyn BehaviorNode>) -> Self {
        RunUntilNode { predicate, child }
    }
}

impl<F: Fn(&BlackBoard) -> bool> BehaviorNode for RunUntilNode<F> {
    fn tick(&mut self, bb: &mut BlackBoard) -> NodeStatus {
        loop {
            match self.child.tick(bb) {
                NodeStatus::Running => return NodeStatus::Running,
                NodeStatus::Failure => return NodeStatus::Failure,
                NodeStatus::Success => {
                    if (self.predicate)(bb) {
                        return NodeStatus::Success;
                    }
                }
            }
        }
    }
}

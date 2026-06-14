use crate::behavior_tree::{BehaviorNode, BlackBoard, NodeStatus};

pub struct SequenceNode {
    children: Vec<Box<dyn BehaviorNode>>,
    current: usize,
}

impl SequenceNode {
    pub fn new(children: Vec<Box<dyn BehaviorNode>>) -> Self {
        SequenceNode {
            children,
            current: 0,
        }
    }
}

impl BehaviorNode for SequenceNode {
    fn tick(&mut self, blackboard: &mut BlackBoard) -> NodeStatus {
        while self.current < self.children.len() {
            let status = self.children[self.current].tick(blackboard);
            if status == NodeStatus::Running {
                return status;
            }
            if status == NodeStatus::Failure {
                self.current = 0;
                return status;
            }
            self.current += 1;
        }

        self.current = 0;
        NodeStatus::Success
    }
}

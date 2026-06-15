use crate::behavior_tree::{BehaviorNode, BlackBoard, NodeStatus};

pub struct SelectorNode {
    children: Vec<Box<dyn BehaviorNode>>,
    current: usize,
}

impl SelectorNode {
    pub fn new(children: Vec<Box<dyn BehaviorNode>>) -> Self {
        SelectorNode {
            children,
            current: 0,
        }
    }
}

impl BehaviorNode for SelectorNode {
    fn tick(&mut self, blackboard: &mut BlackBoard) -> NodeStatus {
        while self.current < self.children.len() {
            let status = self.children[self.current].tick(blackboard);
            if status == NodeStatus::Success {
                self.current = 0;
                return status;
            }
            if status == NodeStatus::Running {
                return status;
            }

            self.current += 1;
        }

        self.current = 0;

        NodeStatus::Failure
    }
}

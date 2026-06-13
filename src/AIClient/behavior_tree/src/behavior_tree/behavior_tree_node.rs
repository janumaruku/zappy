use std::any::Any;
use std::collections::HashMap;

#[derive(Debug, Clone, PartialEq)]
pub enum NodeStatus {
    Success,
    Failure,
    Running,
}

pub struct BlackBoard {
    board: HashMap<String, Box<dyn Any>>,
}

pub trait BehaviorNode {
    fn tick(&mut self, blackboard: &mut BlackBoard) -> NodeStatus;
}

pub struct BehaviorTree {
    root_node: Box<dyn BehaviorNode>,
}

impl BlackBoard {
    pub fn new() -> Self {
        BlackBoard {
            board: HashMap::new(),
        }
    }

    pub fn get<T: Any>(&self, key: &str) -> Result<&T, String> {
        self.board
            .get(key)
            .ok_or_else(|| format!("Black board: key {} not found", key))?
            .downcast_ref::<T>()
            .ok_or_else(|| format!("Black board: wrong type for {}", key))
    }

    pub fn set<T: Any>(&mut self, key: &str, value: T) {
        self.board.insert(key.to_string(), Box::new(value));
    }
}

impl BehaviorTree {
    pub fn new(root_node: Box<dyn BehaviorNode>) -> Self {
        BehaviorTree {
            root_node
        }
    }
    pub fn tick(&mut self, blackboard: &mut BlackBoard) -> NodeStatus {
        self.root_node.tick(blackboard)
    }
}
